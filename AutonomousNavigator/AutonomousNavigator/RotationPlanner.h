#pragma once
#define _USE_MATH_DEFINES

#include "IRotationPlanner.h"

class RotationPlanner : public IRotationPlanner
{
	public:

		RotationPlanner();

		std::pair<double, std::string> CreatePlan(double target_x, double target_y) override;

	private:

		double getTargetAngle(double current_x, double current_y, double target_x, double target_y);

		std::string getTurningDirection(double current_angle, double target_angle);

		double shortestAngularDistance(double from, double to);

		double normalizeAngle(double angle);
};

