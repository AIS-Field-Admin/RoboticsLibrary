#include "pch.h"
#include "AutonomousNavigatorSettingsReader.h"

bool AutonomousNavigatorSettingsReader::ReadSettings(std::string filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath <<std::endl;
        return false;
    }

    try
    {
        nlohmann::json j;
        file >> j;

        AutonomousNavigatorGlobals::NAVIGATION_TOLERENCE_MILIMETERS = j.at("navigationTolerence_milimeters").get<double>();
        AutonomousNavigatorGlobals::ROTATION_TOLERENCE_DEGREE = j.at("rotationTolerence_degree").get<double>();
    }
    catch (nlohmann::json::parse_error& e)
    {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return false;
    }
    catch (nlohmann::json::out_of_range& e)
    {
        std::cerr << "Out of range error: " << e.what() << std::endl;
        return false;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;

}