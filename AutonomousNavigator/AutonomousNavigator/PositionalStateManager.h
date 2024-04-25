#pragma once
#include "IPositionalStateManager.h"
#include "NavigatorSensorConstructor.h"
#include "NavigatorEncoder.h"
#include "PositionalState.h"

class PositionalStateManager : public IPositionalStateManager
{
	public:

		PositionalStateManager();

		void UpdateState() override;

		void SetEncoders(std::shared_ptr<NavigatorEncoders> encoders) override;


	private:

		std::shared_ptr<NavigatorEncoders> _encoders;

		void updateAngle();

		void updatePosition();


};

