#include "CppUnitTest.h"
#include "..\AutonomousNavigator\RotationPlanner.h"
#include "..\AutonomousNavigator\PositionalState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RoboticsNavigationTests
{
    TEST_CLASS(RotationPlannerTests)
    {
        public:

            TEST_METHOD(TestMethod_CreatePlan_WhenTargetEast)
            {
                // Arrange
                PositionalState::GetInstance().position_x = 0;
                PositionalState::GetInstance().position_y = 0;
                PositionalState::GetInstance().angleDeg = 0;
                RotationPlanner rotationPlanner;

                // East target should be 0 degrees from origin
                double target_x = 10.0;
                double target_y = 0.0;
                std::pair<double, std::string> expectedPlan = { 0.0, "Right" };

                // Act
                auto plan = rotationPlanner.CreatePlan(target_x, target_y);

                // Assert
                Assert::AreEqual(expectedPlan.first, plan.first, L"Target angle should be 0 for East");
                Assert::AreEqual(expectedPlan.second, plan.second, L"Should turn right to face East");
            }

            TEST_METHOD(TestMethod_CreatePlan_WhenTargetNorth)
            {
                // Arrange
                PositionalState::GetInstance().position_x = 0;
                PositionalState::GetInstance().position_y = 0;
                PositionalState::GetInstance().angleDeg = 0;
                RotationPlanner rotationPlanner;

                // North target should be 90 degrees from origin
                double target_x = 0.0;
                double target_y = 10.0;
                std::pair<double, std::string> expectedPlan = { 90.0, "Right" };

                // Act
                auto plan = rotationPlanner.CreatePlan(target_x, target_y);

                // Assert
                Assert::AreEqual(expectedPlan.first, plan.first, L"Target angle should be 90 for North");
                Assert::AreEqual(expectedPlan.second, plan.second, L"Should turn right to face North");
            }

        // Additional test methods for other scenarios (e.g., target South, West)
        // ...

    };
}
