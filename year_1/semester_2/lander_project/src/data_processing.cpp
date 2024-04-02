//===========================================================================
// Import necessary libraries
//===========================================================================

#include <math.h>

//===========================================================================
// Import other files for this project
//===========================================================================

#include "constants.hpp"
#include "data_processing.hpp"

//===========================================================================
// Define functions to be used elsewhere
//===========================================================================

void smoothAccelReading(MovingMultiWindow* window, Vector3* accelerometer_reading, Vector3* processed_output)
{
    // Read in new value
    window->x_readings[window->index] = accelerometer_reading->x;
    window->y_readings[window->index] = accelerometer_reading->y;
    window->z_readings[window->index] = accelerometer_reading->z;

    // Calculate the sum
    processed_output->x = 0.0f;
    processed_output->y = 0.0f;
    processed_output->z = 0.0f;

    for(int i = 0; i < WINDOW_SIZE; i++)
    {
        processed_output->x += window->x_readings[i];
        processed_output->y += window->y_readings[i];
        processed_output->z += window->z_readings[i];
    }

    // Store the smoothed values
    processed_output->x /= WINDOW_SIZE;
    processed_output->y /= WINDOW_SIZE;
    processed_output->z /= WINDOW_SIZE;
}

// CALCULATIONS ON SENSOR DATA

float calcAltitude(float temperature, float pressure)
{
    temperature += 273.15; // Convert temperature (C) to temperature (K)
    /*
        Formula: H = (((Po/P) ^ K) - 1) * T / C
        Where:
            H  = Current height above sea level
            Po = Sea level pressure in hPa
            P  = Pressure at current altitude in hPa
            K  = Constant (0.1902225604f) given by 1 / 5.257; From lecture 3 slides
            T  = Temperature in degrees Kelvin
            C  = Constant (0.0065f); From lecture 3 slides
    */
    return ((pow(SEALEVELPRESSURE_HPA / pressure, 0.1902225604f) - 1) * temperature) / 0.0065f;
}

void calcVelocity(Vector3* velocity, const Vector3* acceleration, unsigned long duration)
{
    /*
        Formula: V = U + AT
        Where:
            V = Final velocity in m/s
            U = Initial velocity in m/s
            A = Acceleration m/s^2
            T = Time over which the acceleration happens in seconds
    */
    velocity->x = velocity->x + acceleration->x * (duration / 1000.0f);
    velocity->y = velocity->y + acceleration->y * (duration / 1000.0f);
    velocity->z = velocity->z + acceleration->z * (duration / 1000.0f);
}

void calcForce(Vector3* force, const Vector3* acceleration)
{
    /*
        Formula: F = MA
        Where:
            F = Force in newtons
            M = Mass of rocket in kg
            A = Acceleration of the rocket in m/s^2
    */
    force->x = acceleration->x * ROCKET_MASS;
    force->y = acceleration->y * ROCKET_MASS;
    force->z = acceleration->z * ROCKET_MASS;
}