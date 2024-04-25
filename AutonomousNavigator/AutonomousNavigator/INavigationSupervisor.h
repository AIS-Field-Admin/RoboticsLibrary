#pragma once
#include <iostream>

class INavigationSupervisor
{
	public:

		virtual bool IsTargetReached() = 0;

		virtual void Rotate(double targetAngle, std::string direction) = 0;
		virtual void Navigate(double target_x, double target_y) = 0;
		virtual bool Stop() = 0;

		virtual std::string GetNavigationStatus() = 0;

};

