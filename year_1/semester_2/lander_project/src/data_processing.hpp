#pragma once

//===========================================================================
// Import other files for this project
//===========================================================================

#include "data_structures.hpp"

//===========================================================================
// Declare functions to be used elsewhere
//===========================================================================

/*
    Calculates the average / smoothed acceleration values of a moving window
    @param window The moving window from which to take data from
    @param accelerometer_reading Vector containing new readings from an accelerometer
    @param processed_output Destination for average / smoothed acceleration
*/
void smoothAccelReading(MovingMultiWindow* window, Vector3* accelerometer_reading, Vector3* processed_output);
/*
    Converts temperature and pressure into altitude using the Hypsometric equation
    @param temperature The current temperature
    @param pressure The current pressure
*/
float calcAltitude(float temperature, float pressure);
/*
    Calculates the velocity in all axes
    @param velocity Vector of current velocity and destination for new velocity
    @param acceleration Acceleration vector
    @param duration The time between the last reading and now in ms
*/
void calcVelocity(Vector3* velocity, const Vector3* acceleration, unsigned long duration);
/*
    Calculates the forces on the rocket in all axes
    @param force Vector destination for the force
    @param acceleration Acceleration vector
*/
void calcForce(Vector3* force, const Vector3* acceleration);
/*
    Calculates the magnitude of a given vector
    @param vector The vector to get the magnitude of
    @return The magnitude of that vector
*/
inline float calcVectorMagnitude(const Vector3* vector)
{
    /*
        Formula: M = sqrt(x^2 + y^2 + z^2)
        Where:
            M = Total Magnitude
            x = Magnitude in the x direction
            y = Magnitude in the y direction
            z = Magnitude in the z direction
    */
    return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}