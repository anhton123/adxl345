
/**
* Bus that the ADXL345 is attached to
*/
#define I2C_BUS ("/dev/i2c-1")

/**
* I2C address of ADXL345
*/
#define I2C_ADDR (0x53)

/**
* Calulates square of number
* @param[in] x: input number
* @return square of number 
*/
int square(int x); 


/**
* Struct to hold acceleromoter data
*/
typedef struct {
	float x_accl;
	float y_accl;
	float z_accl;
} accelerometer;

/**
* Intializes ADXL345 sensor with certain configs
* @return fd: file descripter of bus attached to the acceleromter
*/
int adxl345_init();


/**
* Obtains the accelerometer data
*/
void adxl345_get_accel(const int fd, accelerometer *a);
