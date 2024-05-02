#include "pch.h"
#include "NavigatorSensorConstructor.h"


NavigatorSensorConstructor& NavigatorSensorConstructor::GetInstance()
{
    static NavigatorSensorConstructor instance;

    return instance;
}

NavigatorSensorConstructor::NavigatorSensorConstructor()
{

}

void NavigatorSensorConstructor::ConstructSensors()
{
	_encoders = std::make_shared<NavigatorEncoders>();	 
}

std::shared_ptr<NavigatorEncoders> NavigatorSensorConstructor::GetEncoders()
{
	return _encoders;
}
