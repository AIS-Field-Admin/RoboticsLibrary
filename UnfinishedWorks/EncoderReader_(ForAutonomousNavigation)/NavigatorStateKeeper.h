#pragma once
#include <atomic>

class NavigatorStateKeeper
{
    public:
        static NavigatorStateKeeper& GetInstance();

        // Delete copy constructor and assignment operator
        NavigatorStateKeeper(const NavigatorStateKeeper&) = delete;
        NavigatorStateKeeper& operator=(const NavigatorStateKeeper&) = delete;

        // State variables
        std::atomic<double> acceleration_x;
        std::atomic<double> acceleration_y;
        std::atomic<double> acceleration_z;

        std::atomic<double> gyrometer_roll;
        std::atomic<double> gyrometer_pitch;
        std::atomic<double> gyrometer_yaw;

        std::atomic<double> angle_roll;
        std::atomic<double> angle_pitch;
        std::atomic<double> angle_yaw;

        std::atomic<double> encoder_left_pulses;
        std::atomic<double> encoder_left_time;

        std::atomic<double> encoder_right_pulses;
        std::atomic<double> encoder_right_time;

    private:

        NavigatorStateKeeper(); 
};