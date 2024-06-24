use std::error::Error;

mod load;

fn main() -> Result<(), Box<dyn Error>> {
    load::run_tests()
}
