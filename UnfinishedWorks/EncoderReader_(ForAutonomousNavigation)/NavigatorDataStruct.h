#pragma once
struct NavigatorDataStruct
{
	public:
		double acceleration_x; 
		double acceleration_y;
		double acceleration_z;

		double gyrometer_roll;
		double gyrometer_pitch;
		double gyrometer_yaw;

		double angle_roll;
		double angle_pitch;
		double angle_yaw;

		double encoder_left_pulses;
		double encoder_left_time;

		double encoder_right_pulses;
		double encoder_right_time;
};