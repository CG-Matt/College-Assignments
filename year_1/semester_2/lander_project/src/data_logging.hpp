#pragma once

//===========================================================================
// Import necessary libraries
//===========================================================================

#include <Adafruit_BMP280.h>

//===========================================================================
// Import other files for this project
//===========================================================================

#include "data_structures.hpp"

//===========================================================================
// Declare functions to be used elsewhere
//===========================================================================

// Read data from sensors

/*
    Reads acceleration values from the accelerometer
    @param vec Pointer to vector into which the acceleration values will be stored
*/
void readFromAccelerometer(Vector3* vec);
/*
    Reads temperature and pressure values from the environmental sensor
    @param sensor Pointer to the BMP280 module
    @param data_out Pointer to struct into which the temperature and pressure data will be stored
*/
void readEnvironmental(Adafruit_BMP280* sensor, EnvironmentData* data_out);

// Track calculated readings

/*
    Tracks the minimum, maximum and average, altitude recorded and the timestamp of when it occured
    @param time_now Current timestamp
    @param alt_stats StatTracker struct holding altitude record data
*/
void trackAltitude(unsigned long time_now, StatTracker* alt_stats);
/*
    Tracks the minimum, maximum and average, temperature recorded and the timestamp of when it occured
    @param time_now Current timestamp
    @param temperature Current temperature
    @param temperature_stats StatTracker struct holding temperature record data
*/
void trackTemperature(unsigned long time_now, float temperature, StatTracker* temperature_stats);
/*
    Tracks the minimum, maximum and average, pressure recorded and the timestamp of when it occured
    @param time_now Current timestamp
    @param temperature Current pressure
    @param temperature_stats StatTracker struct holding pressure record data
*/
void trackPressure(unsigned long time_now, float pressure, StatTracker* pressure_stats);
/*
    Tracks a vector in a given plane
    @param time_now Current timestamp
    @param vector The vector in a given plane
    @param vector_stats StatTracker struct holding record data for the given vector
*/
void trackVector1(unsigned long time_now, float vector, StatTracker* vector_stats);
/*
    Tracks a vector in the 3D plane
    @param time_now Current timestamp
    @param velocity The vector to track
    @param velocity_stats Vector3StatTracker struct holding record data for the given vector
*/
void trackVector3(unsigned long time_now, const Vector3* vector, Vector3StatTracker* vector_stats);
/*
    Tracks the velocity in the 3D plane
    @param time_now Current timestamp
    @param current_velocity The current velocity vector
    @param velocity_stats Vector3StatTracker struct holding velocity record data
*/
inline void trackVelocity(unsigned long time_now, const Vector3* current_velocity, Vector3StatTracker* velocity_stats){
    trackVector3(time_now, current_velocity, velocity_stats);
}
/*
    Tracks the force in the 3D plane
    @param time_now Current timestamp
    @param current_force The current force vector
    @param force_stats Vector3StatTracker struct holding force record data
*/
inline void trackForce(unsigned long time_now, const Vector3* current_force, Vector3StatTracker* force_stats){
    trackVector3(time_now, current_force, force_stats);
}
/*
    Tracks the accleration in the 3D plane
    @param time_now Current timestamp
    @param current_force The current acceleration vector
    @param force_stats Vector3StatTracker struct holding acceleration record data
*/
inline void trackAcceleration(unsigned long time_now, const Vector3* current_acceleration, Vector3StatTracker* acceleration_stats){
    trackVector3(time_now, current_acceleration, acceleration_stats);
}