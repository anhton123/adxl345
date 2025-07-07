## ADXL345

This code reads accelerometer data from an [ADXL345](https://www.adafruit.com/product/1231?srsltid=AfmBOor_9QODrvvVQmg_ze4qzYp7RrGCFvxcl0hvC4oOAOO5H5hRJ3ZV) from user-space using Rust.

## Code Structure

This code is divided into the following:
- `src/adxl345.c`: C source code that defines/implements the interface to interact with the ADXL345 sensor
- `build.rs`: build script to create the `libadxl345.a` static archive using the implementation of `src/adxl345.c`
- `src/main.rs`: high-level rust code that uses the `libadxl345.a` static archive to obtain accelerometer data 

## Run instructions

1. Obtain a Raspberry Pi 4/5 and an ADXL345 accelerometer sensor
2. Connect the ADXL345 to the I2C-1 bus of the RPI
3. Confirm that the ADXL is properly enumerated on the RPI by checking if address `0x53` is on I2C-1:
```bash
$ i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- 53 -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --
```
4. Run the application. You should see output similar to the following:
```bash
$ cargo run
[2025-07-07T01:07:45Z INFO  adxl345] Sucessfully obtained fd 3 for I2C bus
[2025-07-07T01:07:45Z INFO  adxl345] Starting accelerometer data collection...
[2025-07-07T01:07:45Z DEBUG adxl345] -----------------------------
[2025-07-07T01:07:45Z DEBUG adxl345] Iteration 0
[2025-07-07T01:07:45Z DEBUG adxl345] X-axis acceleration: 9.6176
[2025-07-07T01:07:45Z DEBUG adxl345] Y-axis acceleration: 2.5775
[2025-07-07T01:07:45Z DEBUG adxl345] Z -axis acceleration: -0.1539
[2025-07-07T01:07:45Z DEBUG adxl345] -----------------------------
[2025-07-07T01:07:50Z INFO  adxl345] Accelerometer data collection finished!
```
