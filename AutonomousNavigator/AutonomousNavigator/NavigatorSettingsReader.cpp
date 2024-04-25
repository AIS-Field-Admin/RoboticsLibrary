#include "pch.h"
#include "NavigatorSettingsReader.h"

bool NavigatorSettingsReader::ReadSettings(std::string filePath)
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

        AutonomousNavigatorGlobals::IP_ADDRESS = j.at("ip").get<std::string>();
        AutonomousNavigatorGlobals::PORT = j.at("port").get<std::string>();

        AutonomousNavigatorGlobals::ENCODER_PPR = j.at("encoder_ppr").get<double>();
        AutonomousNavigatorGlobals::ENCODER_WHEEL_DIAMETER = j.at("encoder_wheel_diameter").get<double>();
        AutonomousNavigatorGlobals::DISTANCE_BETWEEN_PALETTES = j.at("distance_between_palettes").get<double>();

        AutonomousNavigatorGlobals::NAVIGATION_TOLERENCE_METERS = j.at("navigationTolerence_meters").get<double>();
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