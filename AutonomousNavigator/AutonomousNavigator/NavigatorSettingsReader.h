#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "AutonomousNavigatorGlobals.h"
#include <nlohmann/json.hpp>

class NavigatorSettingsReader
{
	public:
		static bool ReadSettings(std::string filePath);
};

