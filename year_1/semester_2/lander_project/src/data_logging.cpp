//===========================================================================
// Import necessary libraries
//===========================================================================

#include <Arduino.h>

//===========================================================================
// Import other files for this project
//===========================================================================

#include "constants.hpp"
#include "data_logging.hpp"

//===========================================================================
// Define functions to be used elsewhere
//===========================================================================

// Functions for reading data from the sensors
void readFromAccelerometer(Vector3* vec)
{
    // Read raw values from accelerometer on the analog pins
    int raw_x = analogRead(A1);
    int raw_y = analogRead(A2);
    int raw_z = analogRead(A3);

    // Convert the raw values from the accelerometer into m/s^2
    vec->x = ((raw_x - ZERO_G_POINT) / ONE_G_DIFF) * GRAVITY;
    vec->y = ((raw_y - ZERO_G_POINT) / ONE_G_DIFF) * GRAVITY;
    vec->z = ((raw_z - Z_ZERO_G_POINT) / ONE_G_DIFF) * GRAVITY;
}

void readEnvironmental(Adafruit_BMP280* sensor, EnvironmentData* data_out)
{
    // Read Environmental Sensor
    sensors_event_t temp_event, pressure_event;

    sensor->getTemperatureSensor()->getEvent(&temp_event);
    sensor->getPressureSensor()->getEvent(&pressure_event);

    // Store value into variables: temperature (Celcius), pressure (hPa)
    data_out->temperature = temp_event.temperature;
    data_out->pressure = pressure_event.pressure;
}

// Functions for tracking readings

void trackAltitude(unsigned long time_now, StatTracker* alt_stats)
{
    alt_stats->total += alt_stats->now;     // Add current reading to the total
    alt_stats->data_point_count++;          // Increment the number of data points gathered

    if(alt_stats->now < alt_stats->min)
    {
        alt_stats->min = alt_stats->now;
        alt_stats->min_timestamp = time_now;
    }
    if(alt_stats->now > alt_stats->max)
    {
        alt_stats->max = alt_stats->now;
        alt_stats->max_timestamp = time_now;
    }
}

void trackTemperature(unsigned long time_now, float temperature, StatTracker* temperature_stats)
{
    temperature_stats->total += temperature;    // Add current reading to the total
    temperature_stats->data_point_count++;      // Increment the number of data points gathered

    if(temperature < temperature_stats->min)
    {
        temperature_stats->min = temperature;
        temperature_stats->min_timestamp = time_now;
    }
    if(temperature > temperature_stats->max)
    {
        temperature_stats->max = temperature;
        temperature_stats->max_timestamp = time_now;
    }
}

void trackPressure(unsigned long time_now, float pressure, StatTracker* pressure_stats)
{
    pressure_stats->total += pressure;      // Add current reading to the total
    pressure_stats->data_point_count++;     // Increment the number of data points gathered

    if(pressure < pressure_stats->min)
    {
        pressure_stats->min = pressure;
        pressure_stats->min_timestamp = time_now;
    }
    if(pressure > pressure_stats->max)
    {
        pressure_stats->max = pressure;
        pressure_stats->max_timestamp = time_now;
    }
}

void trackVector1(unsigned long time_now, float vector, StatTracker* vector_stats)
{
    vector_stats->total += vector;              // Add current reading to the total
    vector_stats->data_point_count++;           // Increment the number of data points gathered

    if(vector < vector_stats->min)
    {
        vector_stats->min = vector;
        vector_stats->min_timestamp = time_now;
    }
    if(vector > vector_stats->max)
    {
        vector_stats->max = vector;
        vector_stats->max_timestamp = time_now;
    }
}

void trackVector3(unsigned long time_now, const Vector3* vector, Vector3StatTracker* vector_stats)
{
    trackVector1(time_now, vector->x, &vector_stats->x); // Track in X direction
    trackVector1(time_now, vector->y, &vector_stats->y); // Track in Y direction
    trackVector1(time_now, vector->z, &vector_stats->z); // Track in Z direction
}