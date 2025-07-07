/**
* filename: adxl345.c
* This is the implementation libadxl345.a which is a C-API
* that allows `src.main.rs` to interact with the ADXL345 sensor
* To compile locally:
*    gcc adxl345.c -D RUN_C -o adxl345
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "adxl345.h"

int adxl345_init() {
	int fd;
	char config[2]={0};
	
	/* get fd of I2C bus */
	if ((fd = open(I2C_BUS, O_RDWR)) < 0) {
		printf("ERROR: Failed to open the bus. \n");
		return -1;
	}
	
	/* make fd a I2C slave */
	ioctl(fd, I2C_SLAVE, I2C_ADDR);

	/* Set Bandwidth register (0x2C) with Output Data Rate 100Hz (0x0A) */
	config[0] = 0x2C;
	config[1] = 0x0A;
	write(fd, config, 2);
	
	/* Set Power control register (0x2D) to Auto-sleep disable (0x08) */
	config[0] = 0x2D;
	config[1] = 0x08;
	write(fd, config, 2);
	
	/* Select Data format register (0x31) to Self test disabled, 4-wire interface, Full resolution, range = +/-2g(0x08) */
	config[0] = 0x31;
	config[1] = 0x08;
	write(fd, config, 2);
	
	sleep(1);
	return fd;
}

void adxl345_get_accel(const int fd, accelerometer *a) {
	/**
	* Read 6 bytes of data from register(0x32)
	*  - xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
	*/
	char reg[1] = {0x32};
	write(fd, reg, 1);
	char data[6] ={0};
	if(read(fd, data, 6) != 6) {
		printf("ERROR : Input/output Erorr \n");
		exit(1);
	} else {
		// Convert accelerometer to be between -9.81 to 9.81
		a->x_accl = ((data[1] & 0x03) * 256 + (data[0] & 0xFF));
		if(a->x_accl > 511) a->x_accl -= 1024;
		a->x_accl = ((a->x_accl * 9.81)/ 255);

		a->y_accl = ((data[3] & 0x03) * 256 + (data[2] & 0xFF));
		if(a->y_accl > 511) a->y_accl -= 1024;
		a->y_accl = ((a->y_accl * 9.81)/ 255);

		a->z_accl = ((data[5] & 0x03) * 256 + (data[4] & 0xFF));
		if(a->z_accl > 511) a->z_accl -= 1024;
		a->z_accl = ((a->z_accl * 9.81) / 255);
	}
}

int square(int x) {
  return x*x;
}


/**
* RUN_C is a build flag that enables the user to run this C application
* You need to explicitly pass in the RUN_C flag because `src/main.rs` also
* defines the `main` symbol which leads to overlapping `main` calls
*/
#ifdef RUN_C
/* read num_samples amount of accelerometer data and print it out */
int main() 
{
	int fd, sleep_duration_us, num_samples;
	accelerometer *accl;
	
	
	sleep_duration_us = 1000*500; // 500ms sleep
	num_samples = 100;
	accl = (accelerometer *)malloc(sizeof(accelerometer));
	if (accl == NULL){
		printf("Could not create accl pointer\n");
		exit(1);
	}
	
	fd = adxl345_init();
	if (fd == -1) {
		printf("ERROR: unable to open i2c bus\n");
		exit(1);
	}

	for (int i=0; i<num_samples; i++) {
		adxl345_get_accel(fd, accl);
		printf("-----------------------------\n");
		printf("Iteration %d\n", i);
		printf("X-Axis Acceleration: %.4f\n", accl->x_accl);
		printf("Y-Axis Acceleration: %.4f\n", accl->y_accl);
		printf("Z-Axis Acceleration: %.4f\n", accl->z_accl);
		printf("-----------------------------\n");
		usleep(sleep_duration_us);
	}

	free(accl);
	return 0;
}
#endif
