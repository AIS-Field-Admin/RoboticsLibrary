#pragma once
#define _USE_MATH_DEFINES

#include <cmath>

#include "INavigatorSensor.h"
#include "AutonomousNavigatorGlobals.h"

class NavigatorEncoders : public INavigatorSensor
{
	public:
		
		NavigatorEncoders();

		bool Calibrate() override;

		bool Reset() override;

		bool Process() override;

		virtual double GetVelocity();
		virtual double GetPositionDisplacement();
		virtual double GetRotationAngleChange();


    private:

		double _lastTime;
		double _lastTotalDisplacement_Vehicle;
		
		double _positionDisplacement;
		double _velocity;
		double _rotationAngleChange;

		double _lastTotalDisplacement_Left;
		double _lastTotalDisplacement_Right;

		double getTimeElapsed();

		double convertPulsesToMeters(double previousTotalDisplacement, double currentPulse);

		double getVehicleDisplacement(double leftDisplacement, double rightDisplacement);

		void updateVelocity(double displacement, double timeElapsed);

		void updateRotationChange(double leftDisplacement, double rightDisplacement);

		void updateLastStates(double displacement, double leftDisplacement, double rightDisplacement, double timeElapsed);




};

