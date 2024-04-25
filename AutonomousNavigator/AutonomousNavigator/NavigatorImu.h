#pragma once
#include "INavigatorSensor.h"

class NavigatorImu : public INavigatorSensor
{
	public:
		
		NavigatorImu();

		bool Calibrate() override;

		bool Reset() override;

		bool Process() override;
};

