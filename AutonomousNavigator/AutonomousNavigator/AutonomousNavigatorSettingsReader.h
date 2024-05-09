#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "AutonomousNavigatorGlobals.h"
#include <nlohmann/json.hpp>

class AutonomousNavigatorSettingsReader
{
	public:
		static bool ReadSettings(std::string filePath);
};

