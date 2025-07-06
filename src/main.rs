// filename: main.rs
// this code calls the libmpu6050.a library to collect accelerometer data
use log::{error, warn, info, debug, trace};
unsafe extern "C" {
    fn square(x: i32) -> i32;
}

fn main() {
    env_logger::init();
    error!("Hello, error!");
    warn!("Hello, warn!");
    info!("Hello, info!");
    debug!("Hello, debug!");
    trace!("Hello, trace!");

    unsafe {
        let n1 = 1;
        let sq1: i32 = square(n1);
        info!("n1 {n1} -> sq1 {sq1}");
        let n2 = 2;
        let sq2: i32 = square(n2);
        info!("n2 {n2} -> sq2 {sq2}");
        let n3 = 3;
        let sq3: i32 = square(n3);
        info!("n3 {n3} -> sq3 {sq3}");
    }
}
