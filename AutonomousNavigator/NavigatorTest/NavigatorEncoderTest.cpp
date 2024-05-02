#define _USE_MATH_DEFINES

#include "CppUnitTest.h"
#include "..\AutonomousNavigator\NavigatorEncoder.h"
#include "..\AutonomousNavigator\NavigatorStateKeeper.h"
#include "..\AutonomousNavigator\AutonomousNavigatorGlobals.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NavigatorTests
{
    TEST_CLASS(NavigatorEncoderTests)
    {
    public:

        TEST_METHOD(CalculateDisplacementCorrectly)
        {
            // Arrange
            NavigatorEncoders encoder;
            // Set initial pulses to zero and initial time to zero
            NavigatorStateKeeper::GetInstance().encoder_left_pulses = 0;
            NavigatorStateKeeper::GetInstance().encoder_right_pulses = 0;
            NavigatorStateKeeper::GetInstance().encoder_left_time = 0;
            NavigatorStateKeeper::GetInstance().encoder_right_time = 0;
            encoder.Process();

            // Act - Simulate 11300 pulses on both encoders after 1 second
            NavigatorStateKeeper::GetInstance().encoder_left_pulses = 11300;
            NavigatorStateKeeper::GetInstance().encoder_right_pulses = 11300;
            NavigatorStateKeeper::GetInstance().encoder_left_time = 1000000; // 1 second later in microseconds
            NavigatorStateKeeper::GetInstance().encoder_right_time = 1000000;
            encoder.Process();

            // Expected displacement calculation
            double wheelCircumference = M_PI * AutonomousNavigatorGlobals::ENCODER_WHEEL_DIAMETER;
            double pulsesPerRevolution = AutonomousNavigatorGlobals::ENCODER_PPR;
            double expectedDisplacement = (11300 / pulsesPerRevolution) * wheelCircumference;

            // Assert
            double actualDisplacement = encoder.GetPositionDisplacement();
            Assert::AreEqual(expectedDisplacement, actualDisplacement, 0.001, L"Displacement calculation error");
        }

        TEST_METHOD(CalculateVelocityCorrectly)
        {
            // Arrange
            NavigatorEncoders encoder;
            // Reset initial states
            NavigatorStateKeeper::GetInstance().encoder_left_pulses = 0;
            NavigatorStateKeeper::GetInstance().encoder_right_pulses = 0;
            NavigatorStateKeeper::GetInstance().encoder_left_time = 0;
            NavigatorStateKeeper::GetInstance().encoder_right_time = 0;
            encoder.Process();

            // Act - Simulate pulses and time as before
            NavigatorStateKeeper::GetInstance().encoder_left_pulses = 11300;
            NavigatorStateKeeper::GetInstance().encoder_right_pulses = 11300;
            NavigatorStateKeeper::GetInstance().encoder_left_time = 1000000; // 1 second in microseconds
            NavigatorStateKeeper::GetInstance().encoder_right_time = 1000000;
            encoder.Process();

            // Expected velocity calculation
            double wheelCircumference = M_PI * AutonomousNavigatorGlobals::ENCODER_WHEEL_DIAMETER;
            double pulsesPerRevolution = AutonomousNavigatorGlobals::ENCODER_PPR;
            double expectedDisplacement = (11300 / pulsesPerRevolution) * wheelCircumference;
            double expectedVelocity = expectedDisplacement / 1.0;  // time elapsed is 1 second

            // Assert
            double actualVelocity = encoder.GetVelocity();
            Assert::AreEqual(expectedVelocity, actualVelocity, 0.001, L"Velocity calculation error");
        }

        TEST_METHOD(CalculateRotationCorrectly)
        {
            // Arrange
            NavigatorEncoders encoder;
            // Reset initial states
            NavigatorStateKeeper::GetInstance().encoder_left_pulses = 0;
            NavigatorStateKeeper::GetInstance().encoder_right_pulses = 0;
            NavigatorStateKeeper::GetInstance().encoder_left_time = 0;
            NavigatorStateKeeper::GetInstance().encoder_right_time = 0;
            encoder.Process();

            // Act - Simulate different pulses on left and right for rotation
            NavigatorStateKeeper::GetInstance().encoder_left_pulses = 11300;
            NavigatorStateKeeper::GetInstance().encoder_right_pulses = 12000;
            NavigatorStateKeeper::GetInstance().encoder_left_time = 1000000;
            NavigatorStateKeeper::GetInstance().encoder_right_time = 1000000;
            encoder.Process();

            // Expected rotation calculation
            double wheelCircumference = M_PI * AutonomousNavigatorGlobals::ENCODER_WHEEL_DIAMETER;
            double pulsesPerRevolution = AutonomousNavigatorGlobals::ENCODER_PPR;
            double leftDisplacement = (11300 / pulsesPerRevolution) * wheelCircumference;
            double rightDisplacement = (12000 / pulsesPerRevolution) * wheelCircumference;
            double distanceBetweenWheels = AutonomousNavigatorGlobals::DISTANCE_BETWEEN_PALETTES;
            double expectedRotationRadians = (rightDisplacement - leftDisplacement) / distanceBetweenWheels;
            double expectedRotationDegrees = expectedRotationRadians * (180.0 / M_PI);

            // Assert
            double actualRotationDegrees = encoder.GetRotationAngleChange();
            Assert::AreEqual(expectedRotationDegrees, actualRotationDegrees, 0.001, L"Rotation calculation error");
        }
    };
}