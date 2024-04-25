#pragma once
#include<iostream>
#include"NavigatorEncoder.h"

class NavigatorSensorConstructor
{
	public:

		static NavigatorSensorConstructor& GetInstance();
		NavigatorSensorConstructor(const NavigatorSensorConstructor&) = delete;
		void operator=(const NavigatorSensorConstructor&) = delete;

		void ConstructSensors() ;

		std::shared_ptr<NavigatorEncoders> GetEncoders() ;

	private:

		NavigatorSensorConstructor();

		std::shared_ptr<NavigatorEncoders> _encoders;
};

