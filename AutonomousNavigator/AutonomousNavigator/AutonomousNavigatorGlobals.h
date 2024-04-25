#pragma once
#include <iostream>
class AutonomousNavigatorGlobals 
{
	public:		
		static constexpr int DEFAULT_BUFFER_LENGTH = 8096;

		static std::string IP_ADDRESS;
		static std::string PORT;

		static double ENCODER_PPR;
		static double ENCODER_WHEEL_DIAMETER;
		static double DISTANCE_BETWEEN_PALETTES;

		static double NAVIGATION_TOLERENCE_METERS;
		static double ROTATION_TOLERENCE_DEGREE;

};