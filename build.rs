// filename: build.rs
// This file creates a static archive libmpu6050.a.
// libmpu6050.a provides an API used by main.rs to interact with the mpu6050 device

fn main() {
    println!("cargo::rerun-if-changed=src/mpu6050.c");
    cc::Build::new()
        .file("src/mpu6050.c")
        .compile("mpu6050");
}
