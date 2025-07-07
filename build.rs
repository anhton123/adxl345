/**
* filename: build.rs
* This file creates the static archive libadxl345.a which provides an API
* for `src/main.rs` to interface with with the ADXL345 accelerometer
*/

fn main() {
    println!("cargo::rerun-if-changed=src/adxl345.c");
    cc::Build::new()
        .file("src/adxl345.c")
        .compile("adxl345");
}
