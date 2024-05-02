#include "pch.h"
#include "NavigatorStateKeeper.h"

NavigatorStateKeeper::NavigatorStateKeeper()
{
    acceleration_x = 0;
    acceleration_y = 0;
    acceleration_z = 0;

    gyrometer_roll = 0;
    gyrometer_pitch = 0;
    gyrometer_yaw = 0;

    angle_roll = 0;
    angle_pitch = 0;
    angle_yaw = 0;

    encoder_left_pulses = 0;
    encoder_left_time = 0;

    encoder_right_pulses = 0;
    encoder_right_time = 0;
}

NavigatorStateKeeper& NavigatorStateKeeper::GetInstance()
{
    static NavigatorStateKeeper instance;
    return instance;
}