#pragma once
#include <iostream>
#include "NavigatorEncoder.h"

class IPositionalStateManager
{
	public:
		virtual void UpdateState() = 0;
		virtual void SetEncoders(std::shared_ptr<NavigatorEncoders> encoders) = 0;
};
