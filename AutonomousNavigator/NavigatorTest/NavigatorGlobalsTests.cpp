#include "CppUnitTest.h"
#include "../AutonomousNavigator/AutonomousNavigatorSettingsReader.h" // Adjust the path to where your NavigatorSettingsReader is located
#include "../AutonomousNavigator/AutonomousNavigatorGlobals.h" // Adjust the path to where your NavigatorGlobals is located

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GlobalsTests
{
	TEST_CLASS(NavigatorGlobalsTests)
	{
	public:
		TEST_METHOD_INITIALIZE(MethodInitialize)
		{
			// Arrange
			AutonomousNavigatorSettingsReader settingsReader;

			// Act
			bool result = settingsReader.ReadSettings("../../Settings/settings.json");
		}
		TEST_METHOD(TestGlobalsIsSet)
		{
			Assert::IsTrue(AutonomousNavigatorGlobals::NAVIGATION_TOLERENCE_MILIMETERS > 0, L"NAVIGATION_TOLERENCE_METERS was not set");
			Assert::IsTrue(AutonomousNavigatorGlobals::ROTATION_TOLERENCE_DEGREE > 0, L"ROTATION_TOLERENCE_DEGREE was not set");
		}
	};
}
