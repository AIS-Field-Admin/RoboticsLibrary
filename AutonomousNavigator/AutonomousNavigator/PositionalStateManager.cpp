#include "pch.h"
#include "PositionalStateManager.h"

PositionalStateManager::PositionalStateManager(std::shared_ptr<IPositionalStateProvider_2D> positionalStateProvider)
{
	_positionalStateProvider = positionalStateProvider;
}

void PositionalStateManager::UpdateState()
{
	updateAngle();

	updatePosition();
}

void PositionalStateManager::SetStartingPositions(double startingPosition_x, double startingPosition_y)
{
	PositionalState::GetInstance().SetStartingPosition(startingPosition_x, startingPosition_y);
}

void PositionalStateManager::SetStartingAngle(double startingAngle)
{
	PositionalState::GetInstance().SetStartingAngle(startingAngle);
}

void PositionalStateManager::updateAngle()
{
	double angleReadFromProvider = _positionalStateProvider->GetAngle();

	std::cout << angleReadFromProvider << std::endl;
	PositionalState::GetInstance().UpdateAngle(angleReadFromProvider);
}

void PositionalStateManager::updatePosition()
{
	double positionReadFromProvider_x = _positionalStateProvider->GetPositionX();
	double positionReadFromProvider_y = _positionalStateProvider->GetPositionY();

	PositionalState::GetInstance().UpdatePosition(positionReadFromProvider_x, positionReadFromProvider_y);
}
