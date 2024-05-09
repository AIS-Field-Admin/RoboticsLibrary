#ifndef IPOSITIONALSTATEPROVIDER_2D_H
#define IPOSITIONALSTATEPROVIDER_2D_H

#pragma once

#include <iostream>

class IPositionalStateProvider_2D
{
	public:

		virtual double GetPositionX() = 0; 

		virtual double GetPositionY() = 0; 

		virtual double GetAngle() = 0; 
};

#endif // IPOSITIONALSTATEPROVIDER_2D_H