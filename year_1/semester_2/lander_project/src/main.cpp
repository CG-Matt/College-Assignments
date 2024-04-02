//===========================================================================
// Import necessary libraries
//===========================================================================

#include <SoftwareSerial.h>
#include <Adafruit_BMP280.h>

//===========================================================================
// Import other files for this project
//===========================================================================

#include "constants.hpp"
#include "data_processing.hpp"
#include "data_logging.hpp"
#include "data_structures.hpp"

//===========================================================================
// Initialising variables and peripherals
//===========================================================================

// HC-12 Wireless Transceiver
SoftwareSerial HC12(7, 6); // HC-12 TX Pin, HC-12 RX Pin

// Bosch Environmental Sensor (BME/BMP280)
Adafruit_BMP280 env_sensor; // use I2C interface

// Struct to hold acceleration readings in m/s^2
Vector3 accel_data;

// Struct to hold the environmental sensor readings (degrees C & hPa)
EnvironmentData env_data;
float launch_altitude = 0.0f;

// Struct to store relevent time data
Timer timer;

// Mode change variables
int prev_mode, mode = 0;
float baseline_acceleration_magnitude = 0.0f;

// Moving average filter variables
float x_readings[WINDOW_SIZE];
float y_readings[WINDOW_SIZE];
float z_readings[WINDOW_SIZE];
MovingMultiWindow window{ 0, x_readings, y_readings, z_readings };

// calcuated variables
Vector3 velocity;
Vector3 force;

// min/max variables
StatTracker st_temperature;
StatTracker st_pressure;
StatTracker st_altitude{ 0, 0, 0, 0, 0 };
Vector3StatTracker st_velocity{ { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };
Vector3StatTracker st_acceleration;
Vector3StatTracker st_force{ { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };

//===========================================================================
// Setup code - Housekeeping code
//===========================================================================

void transmit(String& data_to_send); // Declaring function which will be defined later

void setup()
{
    // Code has started, start timestamp.
    timer.start = millis();

    // Setup serial connections between arduino and HC-12 / PC
    HC12.begin(9600);
    Serial.begin(9600);

    // Give console time to get running
    while(!Serial)
        continue;

    // Setup for the Environmental Sensor
    if(!env_sensor.begin(I2CADDR, CHIPID))
    {
        Serial.println(F("Could not find a valid BME/BMP280 (Environmental) sensor, check CHIPID/libraries/wiring!"));
        while(true){}
    }

    // Default Adafruit_BMP280 settings from datasheet
    env_sensor.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                           Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                           Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                           Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                           Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    // Initialise times
    timer.previous      = timer.start;
    timer.last_transmit = timer.start;

    prev_mode = MODE_NULL;  // Set the previous mode to a know value
    mode      = PRE_LAUNCH; // Set the current mode to a know value

    for(size_t i = 0; i < WINDOW_SIZE; i++) // Initialise the moving window with values from the accelerometer
    {
        readFromAccelerometer(&accel_data);
        smoothAccelReading(&window, &accel_data, &accel_data);
        window.index = (window.index + 1) % WINDOW_SIZE; // Increment the index, and wrap to 0 if it exceeds the window size
    }

    // Log the acceleration vector components and magnitude
    Serial.print("Accelerometer values: X: ");
    Serial.print(accel_data.x);
    Serial.print(", Y:");
    Serial.print(accel_data.y);
    Serial.print(", Z:");
    Serial.print(accel_data.z);
    Serial.print(", Mag:");
    Serial.println(calcVectorMagnitude(&accel_data));

    HC12.print("Accelerometer values: X: ");
    HC12.print(accel_data.x);
    HC12.print(", Y:");
    HC12.print(accel_data.y);
    HC12.print(", Z:");
    HC12.print(accel_data.z);
    HC12.print(", Mag:");
    HC12.println(calcVectorMagnitude(&accel_data));

    // Initialise acceleration values
    st_acceleration.x.min = accel_data.x;
    st_acceleration.x.max = accel_data.x;
    st_acceleration.x.min_timestamp = timer.now;
    st_acceleration.x.max_timestamp = timer.now;

    st_acceleration.y.min = accel_data.y;
    st_acceleration.y.max = accel_data.y;
    st_acceleration.y.min_timestamp = timer.now;
    st_acceleration.y.max_timestamp = timer.now;

    st_acceleration.z.min = accel_data.z;
    st_acceleration.z.max = accel_data.z;
    st_acceleration.z.min_timestamp = timer.now;
    st_acceleration.z.max_timestamp = timer.now;

    // Initialise environmental reading data
    readEnvironmental(&env_sensor, &env_data);

    st_temperature.min = env_data.temperature;
    st_temperature.min_timestamp = timer.now;
    st_temperature.max = env_data.temperature;
    st_temperature.max_timestamp = timer.now;

    st_pressure.min = env_data.pressure;
    st_pressure.min_timestamp = timer.now;
    st_pressure.max = env_data.pressure;
    st_pressure.max_timestamp = timer.now;

    /*
        Get baseline acceleration magnitude.
        This is the acceleration value when only gravity acts on the rocket.
        It will be used later to detect if we have landed.
        Use 10 samples for more accurate data
    */
    for(int i = 0; i < 10; i++)
    {
        baseline_acceleration_magnitude += calcVectorMagnitude(&accel_data);
    }
    baseline_acceleration_magnitude /= 10.0f;

    // Get the altitude from which the the rocket is launching
    // The value is offset by 30cm to account for the arduino begin elevated inside the rocket
    launch_altitude = calcAltitude(env_data.temperature, env_data.pressure) - 0.3f;
}

// Define Functions - To be called in Loop Code

void detectMode()
{
    // Positive Y points away from the ground i.e. UP

    // If we are already landed there is no need for mode detection
    if(mode == LANDED) return;

    // FAIL SAFE
    // In the event that mode switching fail always switch to LANDED after 10s from launch
    if(mode == ASCENDING && timer.now - timer.launch > 10000)
    {
        timer.descent = timer.now;
        timer.land    = timer.now;
    }

    // Switch from PRE_LAUNCH to ASCENDING
    if(mode == PRE_LAUNCH)
    {
        // Check if the acceleration in the Y direction is greater than -10
        if(accel_data.y < -10) return;

        // If yes then we are ascending
        prev_mode    = PRE_LAUNCH;
        mode         = ASCENDING;
        timer.launch = timer.now;
    }

    // Switch from ASCENDING to DESCENDING
    if(mode == ASCENDING)
    {
        // Switch modes when velocity goes negative
        if(velocity.y >= 0) return;

        // // If all checks pass switch modes
        prev_mode     = ASCENDING;
        mode          = DESCENDING;
        timer.descent = timer.now;
    }

    // Switch from DESCENDING to LANDED
    if(mode == DESCENDING)
    {
        float acceleration_magnitude = calcVectorMagnitude(&accel_data); // Store acceleration magnitude in variable for convenient usage

        if(!timer.landed_stopwatch) timer.landed_stopwatch = timer.now; // If we have not started a stopwatch start it

        if(acceleration_magnitude > (baseline_acceleration_magnitude + STATIC_ACCEL_OFFSET) || acceleration_magnitude < (baseline_acceleration_magnitude - STATIC_ACCEL_OFFSET)) // If the magnitude of the acceleration vector is outside the threashold reset timer
        {
            timer.landed_stopwatch = 0;
            return;
        }

        if(timer.now - timer.landed_stopwatch < STATIC_IDLE_TIME)   // If not static for STATIC_IDLE_TIME ms dont switch modes
            return;

        // If all checks pass switch modes
        prev_mode  = DESCENDING;
        mode       = LANDED;
        timer.land = timer.now;

        // Run any once off calculations

        // Calculate averages of all tracked data
        st_altitude.avg = st_altitude.total / st_altitude.data_point_count;
        st_acceleration.x.avg = st_acceleration.x.total / st_acceleration.x.data_point_count;
        st_acceleration.y.avg = st_acceleration.y.total / st_acceleration.y.data_point_count;
        st_acceleration.z.avg = st_acceleration.z.total / st_acceleration.z.data_point_count;
        st_temperature.avg = st_temperature.total / st_temperature.data_point_count;
        st_pressure.avg = st_pressure.total / st_pressure.data_point_count;
        st_velocity.x.avg = st_velocity.x.total / st_velocity.x.data_point_count;
        st_velocity.y.avg = st_velocity.y.total / st_velocity.y.data_point_count;
        st_velocity.z.avg = st_velocity.z.total / st_velocity.z.data_point_count;
        st_force.x.avg = st_force.x.total / st_force.x.data_point_count;
        st_force.y.avg = st_force.y.total / st_force.y.data_point_count;
        st_force.z.avg = st_force.z.total / st_force.z.data_point_count;
    }
}

void transmit(String& data_to_send)
{
    // Send data to PC for debugging
    Serial.print(data_to_send);

    // Send to HC-12 for wireless transmission
    HC12.print(data_to_send);

    // Reset the string
    data_to_send = "";

    // Give some time for the data to be sent
    delay(10);
}

inline void MakeTransmitString(String* buffer, int mode)
{
    *buffer = "";
    // FORMAT: TIMESTAMP, MODE, ACCELERATION (X,Y,Z), PRESSURE, ALTITUDE, TEMPERATURE
    // Use commas to separate values to generate transmssion string
#ifdef FINAL_DAY_TRANSMIT
    *buffer = *buffer + timer.now + "," + mode + "," + velocity.y + "," + calcVectorMagnitude(&accel_data) + "," + env_data.pressure + "," + st_altitude.now + "," + env_data.temperature + "\n";
#else    
    *buffer = *buffer + timer.now + "," + mode + "," + accel_data.x + "," + accel_data.y + "," + accel_data.z + "," + env_data.pressure + "," + st_altitude.now + "," + env_data.temperature + "\n";
#endif
}

void TransmitStatTrackSummary(String& data_to_send, StatTracker& stat_tracker, const char* title)
{
    data_to_send += title;
    transmit(data_to_send);
    data_to_send = data_to_send + "\tMin:\t" + stat_tracker.min + "\t@ T+" + stat_tracker.min_timestamp / 1000.0f + "s\n";
    transmit(data_to_send);
    data_to_send = data_to_send + "\tMax:\t" + stat_tracker.max + "\t@ T+" + stat_tracker.max_timestamp / 1000.0f + "s\n";
    transmit(data_to_send);
    data_to_send = data_to_send + "\tAvg:\t" + stat_tracker.avg + "\n";
    transmit(data_to_send);
}

inline void TransmitSummary(String& data_to_send)
{
    // Provide summary e.g. of maximum values
    data_to_send = data_to_send + "Summary of results:\n";
    transmit(data_to_send);
    data_to_send = data_to_send + "- Mode switches:\n";
    transmit(data_to_send);
    data_to_send = data_to_send + "\tPRE to ASC:\t" + timer.launch / 1000.0f + "s\n";
    transmit(data_to_send);
    data_to_send = data_to_send + "\tASC to DEC:\t" + timer.descent / 1000.0f + "s\n";
    transmit(data_to_send);
    data_to_send = data_to_send + "\tDEC to LND:\t" + timer.land / 1000.0f + "s\n";
    transmit(data_to_send);

    data_to_send = data_to_send + "- Flight time:\n";
    transmit(data_to_send);
    data_to_send = data_to_send + "\tFrom start to landing:\t" + (timer.land - timer.start) / 1000.0f + "s\n";
    transmit(data_to_send);
    data_to_send = data_to_send + "\tFrom launch to landing:\t" + (timer.land - timer.launch) / 1000.0f + "s\n";
    transmit(data_to_send);

    TransmitStatTrackSummary(data_to_send, st_altitude, "- Altitude (m):\n");
    data_to_send = data_to_send + "\tRel Max:\t" + (st_altitude.max - launch_altitude) + "\n";

    TransmitStatTrackSummary(data_to_send, st_pressure, "- Pressure (hPa):\n");

    TransmitStatTrackSummary(data_to_send, st_temperature, "- Temperature (C):\n");

    TransmitStatTrackSummary(data_to_send, st_acceleration.x, "- Acceleration X (m/s^2):\n");
    TransmitStatTrackSummary(data_to_send, st_acceleration.y, "- Acceleration Y (m/s^2):\n");
    TransmitStatTrackSummary(data_to_send, st_acceleration.z, "- Acceleration Z (m/s^2):\n");

    TransmitStatTrackSummary(data_to_send, st_velocity.x, "- Velocity X (m/s):\n");
    TransmitStatTrackSummary(data_to_send, st_velocity.y, "- Velocity Y (m/s):\n");
    TransmitStatTrackSummary(data_to_send, st_velocity.z, "- Velocity Z (m/s):\n");

    TransmitStatTrackSummary(data_to_send, st_force.x, "- Force X: (N)\n");
    TransmitStatTrackSummary(data_to_send, st_force.y, "- Force Y: (N)\n");
    TransmitStatTrackSummary(data_to_send, st_force.z, "- Force Z: (N)\n");
}

// Loop Code - Main functionality
void loop()
{
    // 1. READ FROM SENSORS.

    // Get current timestamp
    timer.now = millis();
    // Calculate the difference between last time stamp and current timestamp
    timer.difference = timer.now - timer.previous;
    // Set previous timestamp as current time
    timer.previous = timer.now;

    // Read Accelerometer and then Smooth
    readFromAccelerometer(&accel_data);
    smoothAccelReading(&window, &accel_data, &accel_data);
    // After finsihed smoothing, increment index
    window.index = (window.index + 1) % WINDOW_SIZE; // Increment the index, and wrap to 0 if it exceeds the window size

    // Read Environmental Sensor
    readEnvironmental(&env_sensor, &env_data);

    // 2. RUN CALCULATIONS ON SENSOR DATA

    // Calculate Altitude
    st_altitude.now = calcAltitude(env_data.temperature, env_data.pressure);
    // Calculate velocity for each axis using calcVelocity.
    calcVelocity(&velocity, &accel_data, timer.difference);
    // Calculate Force
    calcForce(&force, &accel_data);

    // Velocity and will be zero if we are pre launch or landed
    if(mode == PRE_LAUNCH || mode == LANDED)
    {
        velocity.x = velocity.y = velocity.z = 0;
        force.x    = force.y    = force.z    = 0;
    }

    // 3. Detect Mode i.e. launch, ascending, descending, landed etc.
    detectMode();

    // 4. TRACK MIN, MAX, AVG VALUES for Altitude, Force, Velocity, etc. Only if ascending or descending
    if(mode == ASCENDING || mode == DESCENDING)
    {
        trackAltitude(timer.now, &st_altitude);
        trackAcceleration(timer.now, &accel_data, &st_acceleration);
        trackTemperature(timer.now, env_data.temperature, &st_temperature);
        trackPressure(timer.now, env_data.pressure, &st_pressure);
        trackVelocity(timer.now, &velocity, &st_velocity);
        trackForce(timer.now, &force, &st_force);
    }

    // 5. Transmit different telemetry depending on mode
    
    // Initialise transmission string
    String data_to_send = "";

    // Depending on mode - run certain calculations / transmit particular data at different intervals
    switch(mode)
    {
        case PRE_LAUNCH:
            // Only transmit once every 5s
            if((timer.now - timer.last_transmit) < 5000)
                break;

            Serial.print("5 seconds since last PRE_LAUNCH transmit - transmit since start: ");
            Serial.println(timer.now);

            // Package data into a string
            MakeTransmitString(&data_to_send, mode);

            // Transmit data
#ifdef FINAL_DAY_TRANSMIT
            Serial.print(data_to_send);
#else
            transmit(data_to_send);
#endif
            // Record PRE_LAUNCH transmission time
            timer.last_transmit = timer.now;
            break;

        case ASCENDING:
        case DESCENDING:
            // Transmit as fast as possible
            // Package data into a string
            MakeTransmitString(&data_to_send, mode);
            // Transmit data
#ifdef FINAL_DAY_TRANSMIT
            Serial.print(data_to_send);
#else
            transmit(data_to_send);
#endif
            break;

        case LANDED:
            if ((timer.now - timer.last_transmit) < 10000) break;
            // Provide summary e.g. of maximum values
            TransmitSummary(data_to_send);
            timer.last_transmit = timer.now;
            break;

        default:
            Serial.println("ARDUINO IN UNEXPECTED MODE!");
            break;
    }
}