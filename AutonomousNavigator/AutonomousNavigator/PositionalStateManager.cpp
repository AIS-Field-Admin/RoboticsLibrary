#include "pch.h"
#include "PositionalStateManager.h"

PositionalStateManager::PositionalStateManager()
{

}

void PositionalStateManager::UpdateState()
{
	_encoders->Process();

	updateAngle();

	updatePosition();
}

void PositionalStateManager::SetEncoders(std::shared_ptr<NavigatorEncoders> encoders)
{
	_encoders = encoders;
}

void PositionalStateManager::updateAngle()
{
	double currentAngle = PositionalState::GetInstance().angleDeg.load();
	double newAngle = currentAngle + _encoders->GetRotationAngleChange();

	PositionalState::GetInstance().angleDeg.store(newAngle);
}

void PositionalStateManager::updatePosition()
{
	double angleRadians = PositionalState::GetInstance().angleDeg.load();

	double delta_x = _encoders->GetPositionDisplacement() * std::cos(angleRadians);
	double delta_y = _encoders->GetPositionDisplacement() * std::sin(angleRadians);

	double updated_x = PositionalState::GetInstance().position_x.load() + delta_x;
	double updated_y = PositionalState::GetInstance().position_y.load() + delta_y;

	PositionalState::GetInstance().position_x.store(updated_x);
	PositionalState::GetInstance().position_y.store(updated_y);
}
