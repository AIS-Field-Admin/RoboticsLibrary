#include "CppUnitTest.h"
#include <memory>
#include <cmath>
#include <gmock/gmock.h>
#include "..\AutonomousNavigator\PositionalStateManager.h"
#include "..\AutonomousNavigator\PositionalState.h"
#include "..\AutonomousNavigator\NavigatorEncoder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using ::testing::Return;

class MockNavigatorEncoders : public NavigatorEncoders
{
public:
    MOCK_METHOD(double, GetPositionDisplacement, (), (override));
    MOCK_METHOD(double, GetRotationAngleChange, (), (override));
};

namespace PositionalStateManagerTests
{
    TEST_CLASS(PositionalStateManagerTests)
    {
    public:
        TEST_METHOD(UpdateState_CorrectlyUpdatesAngle)
        {
            // Arrange
            auto mockEncoders = make_shared<MockNavigatorEncoders>();
            EXPECT_CALL(*mockEncoders, GetRotationAngleChange())
                .WillOnce(Return(10.0)); // Return 10 degrees rotation

            PositionalStateManager manager;
            manager.SetEncoders(mockEncoders); // Assuming you add a method to inject mock encoders

            // Act
            manager.UpdateState();

            // Assert
            double expectedAngle = 10.0; // Assuming initial angle is 0
            double actualAngle = PositionalState::GetInstance().angleDeg.load();
            Assert::AreEqual(expectedAngle, actualAngle, 0.001, L"Angle update incorrect.");

        }

        TEST_METHOD(UpdateState_CorrectlyUpdatesPosition)
        {
            // Arrange
            auto mockEncoders = make_shared<MockNavigatorEncoders>();
            EXPECT_CALL(*mockEncoders, GetPositionDisplacement())
                .WillOnce(Return(5.0)); // Return 5 meters displacement
            EXPECT_CALL(*mockEncoders, GetRotationAngleChange())
                .WillOnce(Return(0.0)); // No rotation for simplicity

            PositionalStateManager manager;
            manager.SetEncoders(mockEncoders); // Inject mock encoders

            // Initial angle is 0, thus moving along x-axis
            PositionalState::GetInstance().angleDeg.store(0.0);

            // Act
            manager.UpdateState();

            // Assert
            double expectedX = 5.0; // 5 meters along the x-axis
            double expectedY = 0.0; // No movement along the y-axis
            double actualX = PositionalState::GetInstance().position_x.load();
            double actualY = PositionalState::GetInstance().position_y.load();
            Assert::AreEqual(expectedX, actualX, 0.001, L"X position update incorrect.");
            Assert::AreEqual(expectedY, actualY, 0.001, L"Y position update incorrect.");
        }
    };
}
