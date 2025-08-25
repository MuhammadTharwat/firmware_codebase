
/*No Error Occured*/
#define GENERIC_SUCCESS 0

/*Generic error codes*/
#define GENERIC_ERR -1
#define GENERIC_ERR_HW GENERIC_ERR - 1
#define GENERIC_ERR_HW_UNINIT GENERIC_ERR - 2
#define GENERIC_ERR_HW_UNSUPPORTED GENERIC_ERR - 3
#define GENERIC_ERR_INVALID_ARGUMENTS GENERIC_ERR - 4
#define GENERIC_ERR_UNINIT GENERIC_ERR - 5
#define GENERIC_ERR_TIMEOUT GENERIC_ERR - 6
#define GENERIC_ERR_UNSUPPORTED_FEATURE GENERIC_ERR - 7
#define GENERIC_ERR_SLAVE_NOT_PRESENT GENERIC_ERR - 8
#define GENERIC_ERR_BUSY GENERIC_ERR - 9

/*Specific Error Code Base*/
#define I2C_ERR_BASE -50

/*Generic Memory Error codes*/
#define MEM_ERR_BASE -100
#define MEM_ERR_ADDR_OUT_OF_RANGE MEM_ERR_BASE - 1
#define MEM_ERR_ADDR_ALIGNMENT MEM_ERR_BASE - 2
#define MEM_ERR_NO_FREE_MEM MEM_ERR_BASE - 3
#define MEM_ERR_CORRUPTED_MEM MEM_ERR_BASE - 4
#define MEM_ERR_BUSY MEM_ERR_BASE - 5
#define MEM_ERR_ERASE_FAILED MEM_ERR_BASE - 6
#define MEM_ERR_MEM_UNINIT MEM_ERR_BASE - 7
#define MEM_ERR_MEM_TIMEOUT MEM_ERR_BASE - 8
#define MEM_ERR_DATA_LEN_ALIGNMENT MEM_ERR_BASE - 9

/*FIFO error code base*/
#define FIFO_ERROR_BASE -125

/*TLV error code base*/
#define TLV_ERR_BASE -150

/*CRC32 code base*/
#define CRC32_ERROR_BASE -175

/*ADS125x ADC error code base*/
#define ADS125x_ERROR_BASE -200

/*ADS111x ADC error base*/
#define ADS111x_ERROR_BASE -250

/*ICM motion sensor error base*/
#define ICM_ERR_BASE -300

/*LIS sensor error base*/
#define LIS_ERR_BASE -350

/*SCD30 sensor error base*/
#define SCD30_ERROR_BASE -400

/*SGP30 sensor error base*/
#define SGP30_ERROR_BASE -450

/*SHT30 sensor error base*/
#define SHT30_ERROR_BASE -500

/*SPS30 sensor error base*/
#define SPS30_ERROR_BASE -550

/*Xbee S3B error base*/
#define XBEE_ERROR_BASE -600

/*OEM pH Sensor error base*/
#define OEM_PH_ERROR_BASE -650

/*OEM ORP Sensor error base*/
#define OEM_ORP_ERROR_BASE -700

/*NCD ORP Sensor error base*/
#define NCD_ORP_ERROR_BASE -750

/*ADFT_TH Sensor error base*/
#define ADFT_TH_ERROR_BASE -800

/*NCD PH Sensor error base*/
#define NCD_PH_ERROR_BASE -850

/*KX13x error base*/
#define KX13x_ERR_BASE -900

/*KS222 error base*/
#define KX222_ERR_BASE -950

/*OEM EC Sensor error base*/
#define OEM_EC_ERROR_BASE -1000

/*DS2431 EEPROM Device error base*/
#define DS2431_EEPROM_ERROR_BASE -1050

/*OEM DO Sensor error base*/
#define OEM_DO_ERROR_BASE -1100

#define LSM9DS1_ERR_BASE -1150

/*SFA30 Sensor error base*/
#define SFA30_ERROR_BASE -1200

/*Serial Port error base*/
#define SERIAL_ERR_BASE -1250

/*OSAL error base*/
#define OSAL_ERR_BASE -1300

/*TDR Soil Sensor error base*/
#define TDR_ERROR_BASE -1350

/*Current Monitor error base*/
#define CURRENT_MONITOR_ERROR_BASE -1400

/*Time management unit error base*/
#define TM_ERROR_BASE -1450

/* Linked list error base*/
#define LLIST_ERROR_BASE -1500

/*SHT4x error base*/
#define SHT4X_ERROR_BASE -1550

/*SCD4x ERROR_BASE*/
#define SCD4x_ERROR_BASE -1600

/*ADXL357 ERROR_BASE*/
#define ADXL357_ERROR_BASE -1650

/*SGP40 error base*/
#define SGP40_ERROR_BASE -1700

/*SDB8xx error base*/
#define SDB8xx_ERROR_BASE -1750

/*VL53L1x error base*/
#define VL53L1x_ERROR_BASE -1755

/*Board Support Package error base*/
#define BSP_ERROR_BASE -1800

/*AT25SF081 error base*/
#define AT25SF081_ERROR_BASE -1850

/*SAVP501 Error Base*/
#define SAVP501_ERROR_BASE -1900

/*Oil Sensor Error*/
#define OIL_SENSOR_ERROR_BASE -1950

/*OIL Quality Error Base*/
#define OIL_QUALITY_ERROR_BASE -2000

/*OIL Quality Error Base*/
#define OIL_QUALITY_MONITOR_ERROR_BASE -2050

/*Aqua Sensor Error Base*/
#define AQUA_ERROR_BASE -2100

/*SDI-12 Protocol Error Base*/
#define SDI_ERROR_BASE -2150

/*S20_CO Protocol Error Base*/
#define S20_CO_ERROR_BASE -2200

/*S300_CO2 Sensor Error Base*/
#define S300_CO2_ERROR_BASE -2250

/*MB7853 Tank Level sensor Error base*/
#define MB7853_TANK_ERROR_BASE -2300

/*Weight scale sensor Error base*/
#define WEIGHT_SCALE_412XXX_ERROR_BASE -2350

/*LSM6DSOX sensor Error base*/
#define LSM6DSOX_ERROR_BASE -2400

/*IAM20380 sensor Error base*/
#define IAM20380_ERROR_BASE -2450

/*S-light-01 sensor Error base*/
#define SLIGHT01_ERROR_BASE -2500

/*Radiation sensors Error base*/
#define RAD_SENSORS_ERROR_BASE -2550

/*HX711 sensors Error base*/
#define HX711_ERROR_BASE -2600

/*AMS5915 Error base*/
#define AMS5915_SENSORS_ERROR_BASE -2650

/*Optical OD sensor Error base*/
#define OPTOD_ERROR_BASE -2700

/*MF5619 flow meter Error base*/
#define MF5619_ERROR_BASE -2750

/*ADXL380 Sensor Error base*/
#define ADXL380_ERROR_BASE -2800

/*Hach DO Sensor Error base*/
#define HACH_DO_ERROR_BASE -2850

/*BLE Error base*/
#define BLE_ERROR_BASE -2900
#define NCD_BLE_TX_NOT_ALLOWED_ERR BLE_ERROR_BASE - 1

/*C4E Conductivity Sensor Error base*/
#define C4E_ERROR_BASE -2950

/*MAX_M10S GPS receiver Error base*/
#define MAX_M10S_ERROR_BASE -3000

/*  receiver Error base*/
#define FLOWMETER_ERROR_BASE -3050

/*MaxLidar MB8000 Error base*/
#define MAXLIDAR_MB8000_ERROR_BASE -3100

/*MB85RS Fram Error Base*/
#define MB85RS_ERROR_BASE -3150

/* System config error base */
#define SYS_CFG_ERROR_BASE -3200

/*SSD1309 Sensor Error base*/
#define SSD1309_ERROR_BASE -3250