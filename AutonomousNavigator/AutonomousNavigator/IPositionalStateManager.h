#pragma once
#include <iostream>

class IPositionalStateManager
{
	public:

		virtual void UpdateState() = 0;

		virtual void SetStartingPositions(double startingPosition_x, double startingPosition_y) = 0;
		virtual void SetStartingAngle(double startingAngle) = 0;
};
