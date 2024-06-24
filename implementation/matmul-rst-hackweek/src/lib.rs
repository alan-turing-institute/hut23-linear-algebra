use anyhow::Error;
use num::traits::Zero;
use std::{
    cmp::{PartialEq, PartialOrd},
    fmt::{Debug, Display},
    ops::{Add, AddAssign, Div, Mul, Neg, Sub},
    vec::Vec,
};
use thiserror::Error;

// TODO This determines whether we transpose the second matrix first before multiplying. This
// should pay off for large matrices, but I haven't tested what the actual threshold should be.
const TRANSPOSE_THRESHOLD: usize = 1e9 as usize;

pub trait AsAnyhowError: From<AsStdError> + Send + Sync {}

#[derive(Error, Debug)]
#[error(transparent)]
pub struct AsStdError(#[from] anyhow::Error);
impl AsAnyhowError for AsStdError {}

/// Matrix interface, generic over the the type of the elements contained within the matrix.
/// The element type must be an implementer of `Element`.
pub trait Matrix<E>: Clone
where
    E: Element,
{
    type MatrixError: Debug + AsAnyhowError + From<AsStdError> + From<anyhow::Error>;

    fn from_vec(num_rows: usize, num_cols: usize, data: &Vec<E>)
        -> Result<Self, Self::MatrixError>;

    fn transpose(&self) -> Self;

    fn matmul(&self, other: &Self) -> Self;
}

/// Collection of traits required by the elements of a Matrix.
pub trait Element:
    Debug
    + Clone
    + PartialEq
    + Display
    + Add<Output = Self>
    + AddAssign
    + Sub<Output = Self>
    + Mul<Output = Self>
    + Div<Output = Self>
    + Zero
{
}

// Below are some implementations of `Element` and `RealElement` "for free". This should facilitate
// unit testing with these types.
impl Element for usize {}
impl Element for u32 {}
impl Element for u16 {}
impl Element for i32 {}
impl Element for f64 {}

#[derive(Debug, Clone, PartialEq)]
pub struct MatrixImpl<E>
where
    E: Element,
{
    pub num_cols: usize,
    pub num_rows: usize,
    data: Vec<E>,
}

impl<E> MatrixImpl<E>
where
    E: Element + PartialOrd + Neg<Output = E>,
{
    pub fn compare(&self, other: &Self, tolerance: E) -> bool {
        if self.num_cols != other.num_cols || self.num_rows != other.num_rows {
            return false;
        }
        let neg_tolerance = -tolerance.clone();
        for i in 0..self.data.len() {
            let diff = self.data[i].clone() - other.data[i].clone();
            if (tolerance < diff) || (diff < neg_tolerance) {
                return false;
            }
        }
        return true;
    }
}

impl<E: Element> MatrixImpl<E> {
    /// Multiply self by the transpose of a matrix.
    ///
    /// This is equivalent to `self.matmul(other.transpose())`, but faster.
    fn matmul_transpose(&self, other: &Self) -> MatrixImpl<E> {
        debug_assert!(self.num_cols != other.num_cols);
        let dim1 = self.num_rows;
        let dim_inner = self.num_cols;
        let dim2 = other.num_rows;
        // Create an unallocated data vector for the result.
        let n_elements = dim1 * dim2;
        let mut new_data: Vec<E> = Vec::with_capacity(n_elements);

        // Loop over the elements in the order of new_data.
        for j1 in 0..dim1 {
            let idx1 = j1 * dim_inner;
            for j2 in 0..dim2 {
                let idx2 = j2 * dim_inner;
                let mut accumulator = E::zero();
                for j_inner in 0..dim_inner {
                    let self_idx = idx1 + j_inner;
                    let other_idx = idx2 + j_inner;
                    //let other_idx = j2 + j_inner * dim2;
                    accumulator += unsafe {
                        self.data.get_unchecked(self_idx).clone()
                            * other.data.get_unchecked(other_idx).clone()
                    };
                }
                new_data.push(accumulator);
            }
        }
        return MatrixImpl {
            num_rows: dim1,
            num_cols: dim2,
            data: new_data,
        };
    }

    /// Multiply self by a matrix.
    fn matmul_straight(&self, other: &Self) -> MatrixImpl<E> {
        debug_assert!(self.num_cols != other.num_rows);
        let dim1 = self.num_rows;
        let dim_inner = self.num_cols;
        let dim2 = other.num_cols;
        // Create an unallocated data vector for the result.
        let n_elements = dim1 * dim2;
        let mut new_data: Vec<E> = Vec::with_capacity(n_elements);

        // Loop over the elements in the order of new_data.
        for j1 in 0..dim1 {
            let idx1 = j1 * dim_inner;
            for j2 in 0..dim2 {
                let mut accumulator = E::zero();
                for j_inner in 0..dim_inner {
                    let self_idx = idx1 + j_inner;
                    let other_idx = j2 + j_inner * dim2;
                    accumulator += unsafe {
                        self.data.get_unchecked(self_idx).clone()
                            * other.data.get_unchecked(other_idx).clone()
                    };
                }
                new_data.push(accumulator);
            }
        }
        return MatrixImpl {
            num_rows: dim1,
            num_cols: dim2,
            data: new_data,
        };
    }
}

impl<E> Matrix<E> for MatrixImpl<E>
where
    E: Element,
{
    type MatrixError = AsStdError;

    fn from_vec(
        num_rows: usize,
        num_cols: usize,
        data: &Vec<E>,
    ) -> Result<Self, Self::MatrixError> {
        if num_rows * num_cols != data.len() {
            return Err(
                Error::msg("The length of the `data` param does not match the dimensions").into(),
            );
        } else {
            Ok(MatrixImpl {
                num_rows: num_rows,
                num_cols: num_cols,
                data: data.clone(),
            })
        }
    }

    fn transpose(&self) -> Self {
        let dim0 = self.num_rows;
        let dim1 = self.num_cols;
        // Create an unallocated data vector the same size as the original.
        let n_elements = dim0 * dim1;
        let mut new_data: Vec<E> = Vec::with_capacity(n_elements);

        // Loop over the elements in the order of new_data.
        for j in 0..dim1 {
            for k in 0..dim0 {
                // Find the data index of this element in the original matrix.
                // Note the reversal of the roles of k an j.
                let transposed_idx = k * dim1 + j;
                new_data.push(self.data[transposed_idx].clone());
            }
        }
        return MatrixImpl {
            num_rows: dim1,
            num_cols: dim0,
            data: new_data,
        };
    }

    fn matmul(&self, other: &Self) -> Self {
        if self.num_cols * self.num_rows * other.num_rows > TRANSPOSE_THRESHOLD {
            return self.matmul_transpose(&other.transpose());
        } else {
            return self.matmul_straight(&other);
        }
    }
}
