#include "pch.h"
#include "NavigatorStateManager.h"

NavigatorStateManager::NavigatorStateManager()
{

}

void NavigatorStateManager::UpdateStates(const char* data)
{
    NavigatorDataStruct parsedData = NavigatorDataParser::GetInstance().ParseData(data);

    updateStateKeeper(parsedData);
}

void NavigatorStateManager::updateStateKeeper(const NavigatorDataStruct& data)
{
    NavigatorStateKeeper& stateKeeper = NavigatorStateKeeper::GetInstance();

    stateKeeper.acceleration_x = data.acceleration_x;
    stateKeeper.acceleration_y = data.acceleration_y;
    stateKeeper.acceleration_z = data.acceleration_z;

    stateKeeper.gyrometer_roll = data.gyrometer_roll;
    stateKeeper.gyrometer_pitch = data.gyrometer_pitch;
    stateKeeper.gyrometer_yaw = data.gyrometer_yaw;

    stateKeeper.angle_roll = data.angle_roll;
    stateKeeper.angle_pitch = data.angle_pitch;
    stateKeeper.angle_yaw = data.angle_yaw;

    stateKeeper.encoder_left_pulses = data.encoder_left_pulses;
    stateKeeper.encoder_left_time = data.encoder_left_time;

    stateKeeper.encoder_right_pulses = data.encoder_right_pulses;
    stateKeeper.encoder_right_time = data.encoder_right_time;
}