#include "pch.h"
#include "NavigatorEncoder.h"

NavigatorEncoders::NavigatorEncoders()
{
	_lastTime = 0;

	_lastTotalDisplacement_Vehicle = 0;
	_lastTotalDisplacement_Left = 0;
	_lastTotalDisplacement_Right = 0;

	_positionDisplacement = 0;

	_rotationAngleChange = 0;
	_velocity = 0;
}

bool NavigatorEncoders::Calibrate()
{
	return true;
}

bool NavigatorEncoders::Reset()
{
	return true;
}

bool NavigatorEncoders::Process()
{
	double timeElapsed = getTimeElapsed();

	double leftDisplacement = convertPulsesToMeters(_lastTotalDisplacement_Left, NavigatorStateKeeper::GetInstance().encoder_left_pulses);
	
	double righDisplacement = convertPulsesToMeters(_lastTotalDisplacement_Right, NavigatorStateKeeper::GetInstance().encoder_right_pulses);
	
	_positionDisplacement = getVehicleDisplacement(leftDisplacement, righDisplacement);

	updateVelocity(_positionDisplacement, timeElapsed);

	updateRotationChange(leftDisplacement, righDisplacement);

	updateLastStates(_positionDisplacement, leftDisplacement, righDisplacement ,timeElapsed);

	return true;
}

double NavigatorEncoders::GetVelocity()
{
	return _velocity;
}

double NavigatorEncoders::GetPositionDisplacement()
{
	return _positionDisplacement;
}

double NavigatorEncoders::GetRotationAngleChange()
{

	return _rotationAngleChange;
}

double NavigatorEncoders::getTimeElapsed()
{
	double timeLeft = NavigatorStateKeeper::GetInstance().encoder_left_time;
	double timeRight = NavigatorStateKeeper::GetInstance().encoder_right_time;

	double curTime = (timeLeft + timeRight) / 2;

	return (curTime - _lastTime); // time is in microseconds, need to be multiplied by 0.000001 to be used in seconds
}

double NavigatorEncoders::convertPulsesToMeters(double previousTotalDisplacement, double currentPulse)
{
	double ppr = AutonomousNavigatorGlobals::ENCODER_PPR;
	double wheelDiameter = AutonomousNavigatorGlobals::ENCODER_WHEEL_DIAMETER;

	double totalDisplacement = double((currentPulse / ppr) * (M_PI * wheelDiameter));
	
	return totalDisplacement - previousTotalDisplacement;
}

double NavigatorEncoders::getVehicleDisplacement(double leftDisplacement, double rightDisplacement)
{
	double averageDisplacement = (leftDisplacement + rightDisplacement) / 2;

	return averageDisplacement - _lastTotalDisplacement_Vehicle;
}

void NavigatorEncoders::updateVelocity(double displacement, double timeElapsed)
{
	double microsecondsToSecondsMultiplier = 0.000001;

	_velocity = displacement / (timeElapsed * microsecondsToSecondsMultiplier); // meters per second
}

void NavigatorEncoders::updateRotationChange(double leftDisplacement, double rightDisplacement)
{
	double distanceBetweenWheels = AutonomousNavigatorGlobals::DISTANCE_BETWEEN_PALETTES;

	double thetaRadians = (rightDisplacement - leftDisplacement) / distanceBetweenWheels;
	_rotationAngleChange = thetaRadians * (180.0 / M_PI);
}

void NavigatorEncoders::updateLastStates(double displacement, double leftDisplacement, double rightDisplacement ,double timeElapsed)
{
	_lastTime = _lastTime + timeElapsed;

	_lastTotalDisplacement_Left = _lastTotalDisplacement_Left + leftDisplacement;

	_lastTotalDisplacement_Right = _lastTotalDisplacement_Right + rightDisplacement;

	_lastTotalDisplacement_Vehicle = _lastTotalDisplacement_Vehicle + displacement;

}




