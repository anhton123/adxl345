/** filename: main.rs
* This code calls the libadxl345.a library to collect accelerometer data
*/

use std::{thread, time};

/* structures exposed by libadxl345.a */
#[repr(C)]
pub struct accelerometer {
    pub x_accl: cty::c_float,
    pub y_accl: cty::c_float,
    pub z_accl: cty::c_float,
}

/* functions exposed by libadxl345.a */
unsafe extern "C" {
    fn adxl345_init() -> i32;
    fn adxl345_get_accel(fd: i32, a: *mut accelerometer);
}

fn main() {
    /* setup logging */
    use log::{error, info, debug};
    env_logger::init();

    unsafe {
        /* setup accelerometer data collection */
        let mut a: accelerometer = accelerometer { x_accl:0.0, y_accl:1.1, z_accl:2.2 };
        let accel: *mut accelerometer = &mut a;
        let num_samples: i32 = 10;
        let time_delay = time::Duration::from_millis(500); // 100ms delay
        
        /* get fd for i2c bus */
        let fd: i32 = adxl345_init();
        if fd == -1 {
            error!("Unable to open I2C bus device file")
        } else {
            info!("Sucessfully obtained fd {fd} for I2C bus")
        }

        /* read num_samples amount of acceleromter data */
        info!("Starting accelerometer data collection...");
        for i in 0..num_samples {
            adxl345_get_accel(fd, accel);
            debug!("-----------------------------");
            debug!("Iteration {i}");
            debug!("X-axis acceleration: {:.4}", (*accel).x_accl);
            debug!("Y-axis acceleration: {:.4}", (*accel).y_accl);
            debug!("Z -axis acceleration: {:.4}", (*accel).z_accl);
            debug!("-----------------------------");
            thread::sleep(time_delay);
        }
        info!("Accelerometer data collection finished!");
    }
}
