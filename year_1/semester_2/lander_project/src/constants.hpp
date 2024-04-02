#pragma once
//===========================================================================
// Constants - These never change
//===========================================================================

#define USING_BATTERY
#define FINAL_DAY_TRANSMIT

// N.B. Every I2C device has a unique address/chip ID
#define I2CADDR                 0x76
#define CHIPID                  0x60 // 0x60 for BME and 0x58 for BMP.

// Mode Codes
#define MODE_NULL                  0
#define PRE_LAUNCH               100
#define ASCENDING                200
#define DESCENDING               300
#define LANDED                   400

// Constants for use in code
#define SEALEVELPRESSURE_HPA     965    // Pressure at sea level in hPa. Changes depending on the day
#define ROCKET_MASS             0.25    // Mass of rocket/capsule in kilograms
#define GRAVITY                 9.81    // Acceleration does to gravity in m/s^2

// Threashold for mode switching
#define STATIC_ACCEL_OFFSET    0.25f    // This will be added and subtracted from the static acceleration magnitude to create a threshold
#define STATIC_IDLE_TIME        5000    // Time in ms how long the capsule needs to be at rest to change modes

// For use when converting raw accelerometer values to m/s^2
#define ONE_G_DIFF              72.0    // ADC value difference between 0g and 1g

// The ADC value for zero G changes based on the voltage supplied
// Therefor we must change them depending on if we're using the battery or a laptop
#ifdef USING_BATTERY
    #define ZERO_G_POINT         335    // ADC value for 0g in the X and Y axis
    #define Z_ZERO_G_POINT       360    // ADC value for 0g in the Z axis
#else
    #define ZERO_G_POINT         355    // ADC value for 0g in the X and Y axis
    #define Z_ZERO_G_POINT       387    // ADC value for 0g in the Z axis
#endif

// Moving Average Filter size
#define WINDOW_SIZE 5