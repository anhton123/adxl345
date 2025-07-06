// filename: build.rs
// This file creates a static archive libadxl345.a.
// libadxl345.a provides an API used by main.rs to interact with the adxl345 device

fn main() {
    println!("cargo::rerun-if-changed=src/adxl345.c");
    cc::Build::new()
        .file("src/adxl345.c")
        .compile("adxl345");
}
