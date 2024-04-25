#include "CppUnitTest.h"
#include "../AutonomousNavigator/NavigatorSettingsReader.h" // Adjust the path to where your NavigatorSettingsReader is located
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
			NavigatorSettingsReader settingsReader;

			// Act
			bool result = settingsReader.ReadSettings("../../Settings/settings.json");
		}
		TEST_METHOD(TestGlobalsIsSet)
		{
			Assert::AreNotEqual(std::string(""), AutonomousNavigatorGlobals::IP_ADDRESS, L"IP_ADDRESS was not set");
			Assert::AreNotEqual(std::string(""), AutonomousNavigatorGlobals::PORT, L"PORT was not set");
			Assert::IsTrue(AutonomousNavigatorGlobals::ENCODER_PPR > 0,L"ENCODER_PPR was not set");
			Assert::IsTrue(AutonomousNavigatorGlobals::ENCODER_WHEEL_DIAMETER > 0, L"ENCODER_WHEEL_DIAMETER was not set");
			Assert::IsTrue(AutonomousNavigatorGlobals::DISTANCE_BETWEEN_PALETTES > 0, L"DISTANCE_BETWEEN_PALETTES was not set");
			Assert::IsTrue(AutonomousNavigatorGlobals::NAVIGATION_TOLERENCE_METERS > 0, L"NAVIGATION_TOLERENCE_METERS was not set");
			Assert::IsTrue(AutonomousNavigatorGlobals::ROTATION_TOLERENCE_DEGREE > 0, L"ROTATION_TOLERENCE_DEGREE was not set");
		}
	};
}
