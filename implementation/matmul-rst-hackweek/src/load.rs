use core::iter::zip;
use itertools::izip;
use matrix_library_hackweek::{Matrix, MatrixImpl};
use npyz::NpyFile;
use std::error::Error;
use std::fs::File;
use std::io;
use std::time::Instant;

const BENCHMARK_REPEAT: usize = 32768;

// Load an npy file as a Matrix
pub fn load(filename: &str) -> Result<MatrixImpl<f64>, Box<dyn std::error::Error>> {
    let bytes = std::fs::read(filename)?;
    let npy = npyz::NpyFile::new(&bytes[..])?;
    read(npy)
}

// Convert an npy input stream into a Matrix
fn read<R: std::io::Read>(npy: NpyFile<R>) -> Result<MatrixImpl<f64>, Box<dyn std::error::Error>> {
    let shape: Vec<usize> = npy.shape().iter().map(| &i | i as usize).collect();
    let data: Vec<f64> = npy.data::<f64>().unwrap().into_iter().map(| d | d.unwrap()).collect();
    Ok(MatrixImpl::from_vec(shape[0], shape[1], &data).unwrap())
}

// Neat approach by budziq from rust-lang.org
// See https://users.rust-lang.org/t/how-to-parse-an-int-from-string/12456/12
fn parse_int(input: &str) -> Option<u32> {
    input
        .chars()
        .skip_while(|ch| !ch.is_digit(10))
        .take_while(|ch| ch.is_digit(10))
        .fold(None, |acc, ch| {
            ch.to_digit(10).map(|b| acc.unwrap_or(0) * 10 + b)
        })
}

// Load in the test data from the npz file
fn load_tests(
    filename: &str,
) -> Result<
    (
        Vec<MatrixImpl<f64>>,
        Vec<MatrixImpl<f64>>,
        Vec<MatrixImpl<f64>>,
    ),
    Box<dyn std::error::Error>,
> {
    let mut a = Vec::<MatrixImpl<f64>>::new();
    let mut b = Vec::<MatrixImpl<f64>>::new();
    let mut c = Vec::<MatrixImpl<f64>>::new();

    println!("Reading test matrices from file");

    let file = io::BufReader::new(File::open(filename)?);

    let mut zip = zip::ZipArchive::new(file)?;

    for i in 0..zip.len() {
        let file = zip.by_index(i)?;
        let name = file.name();
        let prefix = file.name().chars().next();
        let num: usize = parse_int(name).unwrap().try_into().unwrap();
        let npy = NpyFile::new(file)?;
        let matrix = read(npy)?;
        match prefix {
            Some('a') => a.insert(num, matrix.clone()),
            Some('b') => b.insert(num, matrix.clone()),
            Some('c') => c.insert(num, matrix.clone()),
            Some(_) => println!("Error"),
            None => println!("Error"),
        }
    }

    Ok((a, b, c))
}

// Run simple unit and benchmarking tests
pub fn run_tests() -> Result<(), Box<dyn Error>> {
    println!("Example matrix manipulation...");
    let a = load("../testdata/matrix-a.npy")?;
    let b = load("../testdata/matrix-b.npy")?;
    let c = load("../testdata/matrix-c.npy")?;

    let d = a.matmul(&b);
    let result = c.compare(&d, 1e-10);

    println!("Result of A * B:");
    println!("Size: {}, {}", d.num_rows, d.num_cols);

    println!(
        "Matches expected result: {}",
        if result { "Yes" } else { "No" }
    );

    // Perform 512 multiplications and compare against the results from NumPy
    println!("Performing unit tests...");
    let (a, b, c) = load_tests("../testdata/matrices.npz")?;

    let total = a.len();
    let mut passed = 0;
    for (mata, matb, matc) in izip!(&a, &b, &c) {
        let matd = mata.matmul(&matb);
        if matc.compare(&matd, 1e-10) {
            passed += 1;
        } else {
            println!("Incorrect result");
        }
    }
    println!("Multiplication tests passed: {} out of {}", passed, total);

    println!("Benchmarking...");
    let start_time = Instant::now();
    for _count in 0..BENCHMARK_REPEAT {
        for (mata, matb) in zip(&a, &b) {
            let _matd = mata.matmul(&matb);
        }
    }
    let elapsed = start_time.elapsed();
    let operations = total * BENCHMARK_REPEAT;
    println!(
        "Time taken to perform {} multiply operations: {:.02} seconds\n",
        operations,
        elapsed.as_millis() as f64 / 1000.0
    );
    let ops_per_sec: f64 = 1000.0 * operations as f64 / elapsed.as_millis() as f64;
    println!("Equivalent to {:.02} operations per second", ops_per_sec);

    Ok(())
}
