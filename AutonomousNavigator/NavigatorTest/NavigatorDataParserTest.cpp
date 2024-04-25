#include "CppUnitTest.h"
#include "..\AutonomousNavigator\NavigatorDataParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NavigatorDataParserTest
{
    TEST_CLASS(NavigatorDataParserTests)
    {
    public:

        TEST_METHOD(TestParseAcc)
        {
            NavigatorDataParser& parser = NavigatorDataParser::GetInstance();
            NavigatorDataStruct navData;

            // Payload includes accelerometer data
            const char* payload = "acc:1.0 -2.0 3.0\n";

            // Act
            navData = parser.ParseData(payload);

            // Assert
            Assert::AreEqual(1.0, navData.acceleration_x);
            Assert::AreEqual(2.0, navData.acceleration_y);
            Assert::AreEqual(3.0, navData.acceleration_z);
        }

        TEST_METHOD(TestParseGyro)
        {
            NavigatorDataParser& parser = NavigatorDataParser::GetInstance();
            NavigatorDataStruct navData;

            // Payload includes gyroscope data
            const char* payload = "gyro:0.1 0.2 0.3\n";

            // Act
            navData = parser.ParseData(payload);

            // Assert
            Assert::AreEqual(0.1, navData.gyrometer_pitch);
            Assert::AreEqual(0.2, navData.gyrometer_roll);
            Assert::AreEqual(0.3, navData.gyrometer_yaw);
        }

        TEST_METHOD(TestParseAngle)
        {
            NavigatorDataParser& parser = NavigatorDataParser::GetInstance();
            NavigatorDataStruct navData;

            // Payload includes angle data
            const char* payload = "angle:10.0 20.0 30.0\n";

            // Act
            navData = parser.ParseData(payload);

            // Assert
            Assert::AreEqual(10.0, navData.angle_roll);
            Assert::AreEqual(20.0, navData.angle_pitch);
            Assert::AreEqual(30.0, navData.angle_yaw);
        }

        TEST_METHOD(TestParseEncoderLeft)
        {
            NavigatorDataParser& parser = NavigatorDataParser::GetInstance();
            NavigatorDataStruct navData;

            // Payload includes left encoder data
            const char* payload = "encoder1:100.0 5.0\n";

            // Act
            navData = parser.ParseData(payload);

            // Assert
            Assert::AreEqual(100.0, navData.encoder_left_pulses);
            Assert::AreEqual(5.0, navData.encoder_left_time);
        }

        TEST_METHOD(TestParseEncoderRight)
        {
            NavigatorDataParser& parser = NavigatorDataParser::GetInstance();
            NavigatorDataStruct navData;

            // Payload includes right encoder data
            const char* payload = "encoder2:150.0 10.0\n";

            // Act
            navData = parser.ParseData(payload);

            // Assert
            Assert::AreEqual(150.0, navData.encoder_right_pulses);
            Assert::AreEqual(10.0, navData.encoder_right_time);
        }

        TEST_METHOD(TestParseMultipleSensors)
        {
            NavigatorDataParser& parser = NavigatorDataParser::GetInstance();
            NavigatorDataStruct navData;

            // Payload includes multiple sensor data
            const char* payload = "acc:1.0 -2.0 3.0\ngyro:0.1 0.2 0.3\nangle:10.0 20.0 30.0\n";

            // Act
            navData = parser.ParseData(payload);

            // Assert
            // Accelerometer assertions
            Assert::AreEqual(1.0, navData.acceleration_x);
            Assert::AreEqual(2.0, navData.acceleration_y);
            Assert::AreEqual(3.0, navData.acceleration_z);

            // Gyroscope assertions
            Assert::AreEqual(0.1, navData.gyrometer_pitch);
            Assert::AreEqual(0.2, navData.gyrometer_roll);
            Assert::AreEqual(0.3, navData.gyrometer_yaw);

            // Angle assertions
            Assert::AreEqual(10.0, navData.angle_roll);
            Assert::AreEqual(20.0, navData.angle_pitch);
            Assert::AreEqual(30.0, navData.angle_yaw);
        }
    };
}