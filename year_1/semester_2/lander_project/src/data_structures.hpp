#pragma once

struct EnvironmentData
{
    float temperature;
    float pressure;
};

struct Timer
{
    unsigned long start             = 0;
    unsigned long now               = 0;
    unsigned long previous          = 0;
    unsigned long difference        = 0;
    unsigned long landed_stopwatch  = 0;
    unsigned long last_transmit     = 0;
    unsigned long launch            = 0;
    unsigned long descent           = 0;
    unsigned long land              = 0;
};

struct Vector3
{
    float x;
    float y;
    float z;
};

struct MovingMultiWindow
{
    int index;
    float* x_readings;
    float* y_readings;
    float* z_readings;
};

struct StatTracker
{
    float min;
    float max;
    float avg;
    float now;
    float total;
    unsigned long data_point_count;
    unsigned long min_timestamp;
    unsigned long max_timestamp;
};

struct Vector3StatTracker
{
    StatTracker x;
    StatTracker y;
    StatTracker z;
};