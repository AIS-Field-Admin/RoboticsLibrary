#include "pch.h"
#include "CppUnitTest.h"
#include "..\AutonomousNavigator\NavigatorSensorConstructor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NavigatorSensorConstructorTests
{
    TEST_CLASS(NavigatorSensorConstructorTests)
    {
        public:

            TEST_METHOD(SingletonInstanceTest)
            {
                // Test to ensure that GetInstance always returns the same instance
                NavigatorSensorConstructor& instance1 = NavigatorSensorConstructor::GetInstance();
                NavigatorSensorConstructor& instance2 = NavigatorSensorConstructor::GetInstance();

                Assert::IsTrue(&instance1 == &instance2, L"GetInstance should return the same instance");
            }

            TEST_METHOD(ConstructSensorsTest)
            {
                // Test to ensure ConstructSensors properly initializes the _encoders
                NavigatorSensorConstructor& instance = NavigatorSensorConstructor::GetInstance();
                instance.ConstructSensors();

                auto encoders = instance.GetEncoders();
                Assert::IsNotNull(encoders.get(), L"Encoders should not be null after construction");
            }

            TEST_METHOD(GetEncodersReturnsValidObject)
            {
                // Test to ensure GetEncoders returns a valid object after construction
                NavigatorSensorConstructor& instance = NavigatorSensorConstructor::GetInstance();
                instance.ConstructSensors();  // Make sure sensors are constructed

                auto encoders = instance.GetEncoders();
                Assert::IsNotNull(encoders.get(), L"GetEncoders should return a non-null shared_ptr after ConstructSensors");
            }
    };
}
