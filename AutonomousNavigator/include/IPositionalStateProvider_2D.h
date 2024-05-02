#pragma once

#include <iostream>

class IPositionalStateProvider_2D
{
	public:

		virtual double GetPositionX() = 0; 

		virtual double GetPositionY() = 0; 

		virtual double GetAngle() = 0; 
};
