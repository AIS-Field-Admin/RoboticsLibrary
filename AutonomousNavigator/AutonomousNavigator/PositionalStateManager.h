#pragma once
#include "IPositionalStateManager.h"
#include "PositionalState.h"
#include "IPositionalStateProvider_2D.h"

class PositionalStateManager : public IPositionalStateManager
{
	public:

		PositionalStateManager(std::shared_ptr<IPositionalStateProvider_2D> positionalStateProvider);

		void UpdateState() override;

		void SetStartingPositions(double startingPosition_x, double startingPosition_y) override;
		void SetStartingAngle(double startingAngle) override;


	private:

		std::shared_ptr<IPositionalStateProvider_2D> _positionalStateProvider;

		void updateAngle();

		void updatePosition();


};

