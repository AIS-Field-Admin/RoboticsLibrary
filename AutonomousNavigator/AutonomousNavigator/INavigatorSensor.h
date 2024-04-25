#pragma once
#include<iostream>
#include<any>

#include "NavigatorStateKeeper.h"

class INavigatorSensor
{
	public:

		virtual bool Calibrate() = 0;
		virtual bool Reset() = 0;
		virtual bool Process() = 0;
};