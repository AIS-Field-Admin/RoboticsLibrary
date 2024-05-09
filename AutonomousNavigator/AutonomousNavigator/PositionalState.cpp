#include "pch.h"
#include "PositionalState.h"

PositionalState::PositionalState()
{
    initialiseStateVariables();
}

PositionalState& PositionalState::GetInstance()
{
    static PositionalState instance;
    return instance;
}

void PositionalState::initialiseStateVariables()
{
    SetStartingPosition(0, 0);
    SetStartingAngle(0);
 
    UpdatePosition(0, 0);
    UpdateAngle(0);
}

void PositionalState::SetStartingPosition(double position_x, double position_y)
{
    _startPosition_x = position_x;
    _startPosition_y = position_y;
}

void PositionalState::SetStartingAngle(double angleDeg)
{
    _startAngleDeg = angleDeg;
}

void PositionalState::UpdatePosition(double position_mm_x, double position_mm_y)
{
    updatePosition(position_mm_x, position_mm_y);
}

void PositionalState::updatePosition(double position_mm_x, double position_mm_y)
{
    std::cout << "UpdatePosition:  positionX: " << position_mm_x << " startX: " << _startPosition_x << std::endl;
    _currentPosition_x.store(_startPosition_x + position_mm_x);
    _currentPosition_y.store(_startPosition_y + position_mm_y);
}

std::pair<double, double> PositionalState::GetPosition()
{
    // Copy atomic variables to standard variables to be able to make pairs
    double currentPosition_x = _currentPosition_x.load();
    double currentPosition_y = _currentPosition_y.load();

    std::cout << "PositionalState X: " << _currentPosition_x.load() << " Y: " << _currentPosition_y.load() << std::endl;
    return std::make_pair(currentPosition_x, currentPosition_y);
}

void PositionalState::UpdateAngle(double angleDeg)
{
    updateAngle(angleDeg);
}

void PositionalState::updateAngle(double angleDeg)
{
    _currentAngleDeg = fmod(fmod((_startAngleDeg + angleDeg), 360) + 360, 360);
}

double PositionalState::GetAngle()
{
    return _currentAngleDeg;
}
