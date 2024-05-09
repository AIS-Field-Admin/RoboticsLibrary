#include "pch.h"

#include "RotationPlanner.h"
#include "PositionalState.h"
#include <cmath>
#include <utility>

RotationPlanner::RotationPlanner()
{

}

std::pair<double, std::string> RotationPlanner::CreatePlan(double target_x, double target_y)
{
    std::pair <double, double> currentPosition = PositionalState::GetInstance().GetPosition();

    double current_x = currentPosition.first;
    double current_y = currentPosition.second;

    double current_angle = PositionalState::GetInstance().GetAngle();

    double target_angle = getTargetAngle(current_x, current_y, target_x, target_y);

    std::string direction = getTurningDirection(current_angle, target_angle);

    return std::make_pair(target_angle, direction);
}

double RotationPlanner::getTargetAngle(double current_x, double current_y, double target_x, double target_y)
{
    double angleRadians = std::atan2(target_y - current_y, target_x - current_x);

    double angleDegrees = angleRadians * (180.0 / M_PI);

    return normalizeAngle(angleDegrees);
}

std::string RotationPlanner::getTurningDirection(double current_angle, double target_angle)
{
    double angle_distance = shortestAngularDistance(current_angle, target_angle);

    if (angle_distance < 0)
    {
        return "Right";
    }
    else
    {
        return "Left";
    }  
}

double RotationPlanner::normalizeAngle(double angle)
{
    double newAngle = std::fmod(angle, 360.0);

    if (newAngle < 0)
    {
        newAngle += 360.0;
    }

    return newAngle;
}

double RotationPlanner::shortestAngularDistance(double from, double to)
{
    double delta = normalizeAngle(to - from);

    if (delta > 180.0)
    {
        delta -= 360.0;
    }

    return delta;
}