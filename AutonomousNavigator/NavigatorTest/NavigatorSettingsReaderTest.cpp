#include "CppUnitTest.h"
#include "..\AutonomousNavigator\NavigatorSettingsReader.h" // Adjust the path to where your NavigatorSettingsReader is located
#include "..\AutonomousNavigator\AutonomousNavigatorGlobals.h" // Adjust the path to where your NavigatorGlobals is located

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SettingReaderTests
{
	TEST_CLASS(NavigatorSettingsReaderTests)
	{
	public:

		TEST_METHOD(TestReadSettingsSuccess)
		{
			// Arrange
			NavigatorSettingsReader settingsReader;

			// Act
			bool result = settingsReader.ReadSettings("../../Settings/settings.json");

			// Assert
			Assert::IsTrue(result, L"Failed to read settings.json");
			Assert::IsTrue(AutonomousNavigatorGlobals::NAVIGATION_TOLERENCE_METERS > 0, L"NAVIGATION_TOLERENCE_METERS was not read");
		}

		TEST_METHOD(TestReadSettingsFail)
		{
			// Arrange
			NavigatorSettingsReader settingsReader;

			// Act
			// Before this test runs, ensure that the settings.json file is not present or is invalid
			bool result = settingsReader.ReadSettings("../asd/asd.json");

			// Assert
			Assert::IsFalse(result, L"ReadSettings should have failed due to missing or invalid settings.json");
		}
	};
}
