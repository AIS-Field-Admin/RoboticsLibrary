#pragma once

#include<iostream>

class IRotationPlanner
{
	public:	

		virtual std::pair<double, std::string> CreatePlan(double target_x, double target_y) = 0; // item1 : Target angle, item2: turn direction "left" or "right"


};