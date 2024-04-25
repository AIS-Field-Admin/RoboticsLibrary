#include "pch.h"

#include "NavigatorDataParser.h"
#include <iostream>
#include <string>

NavigatorDataParser& NavigatorDataParser::GetInstance()
{
    static NavigatorDataParser instance;

    return instance;
}

NavigatorDataParser::NavigatorDataParser() 
{

}

NavigatorDataStruct NavigatorDataParser::ParseData(const char* data)
{
    NavigatorDataStruct navData;  

    const char* p_curLine = data;

    while (*p_curLine)
    {
        const char* nextLine = strchr(p_curLine, '\n');
        const char* lineEnd = nextLine ? nextLine : p_curLine + strlen(p_curLine);

        const char* numDataDelim = strchr(p_curLine, ':');

        if (numDataDelim && numDataDelim < lineEnd)
        {
            std::string sensorType(p_curLine, numDataDelim);
            std::string data(numDataDelim + 1, lineEnd);

            parseSensorData(sensorType.c_str(), data.c_str(), navData);
        }

        p_curLine = nextLine ? nextLine + 1 : lineEnd;
    }

    return navData; 
}

void NavigatorDataParser::parseSensorData(const char* sensorType, 
                                          const char* data, 
                                          NavigatorDataStruct& navData)
{
    if (!strcmp("acc", sensorType))
    {
        parseAcc(data, navData);
    }
    else if (!strcmp("gyro", sensorType))
    {
        parseGyro(data, navData);
    }
    else if (!strcmp("angle", sensorType))
    {
        parseAngle(data, navData);
    }
    else if (!strcmp("encoder1", sensorType))
    {
        parseEncoderLeft(data, navData);
    }
    else if (!strcmp("encoder2", sensorType))
    {
        parseEncoderRight(data, navData);
    }
}

void NavigatorDataParser::parseData(const char* data, int count, std::function<void(double, int)> updateFunc) 
{
    std::istringstream iss(data);
    double val;
    int i = 0;
    for (std::string token; std::getline(iss, token, ' ') && i < count; ++i) {
        try {
            val = std::stod(token);
            updateFunc(val, i);
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to parse data: " << e.what() << std::endl;
            return;
        }
    }
}

void NavigatorDataParser::parseAcc(const char* data, NavigatorDataStruct& navData) 
{
    parseData(data, 3, [&](double val, int index) {
        switch (index) {
        case 0: navData.acceleration_x = val; break;
        case 1: navData.acceleration_y = -val; break;  // Apply transformation directly here
        case 2: navData.acceleration_z = val; break;
        }
        });
}

void NavigatorDataParser::parseGyro(const char* data, NavigatorDataStruct& navData) 
{
    parseData(data, 3, [&](double val, int index) {
        switch (index) {
        case 0: navData.gyrometer_pitch = val; break;
        case 1: navData.gyrometer_roll = val; break;
        case 2: navData.gyrometer_yaw = val; break;
        }
        });
}

void NavigatorDataParser::parseAngle(const char* data, NavigatorDataStruct& navData) 
{
    parseData(data, 3, [&](double val, int index) {
        switch (index) {
        case 0: navData.angle_roll = val; break;
        case 1: navData.angle_pitch = val; break;
        case 2: navData.angle_yaw = val; break;
        }
        });
}

void NavigatorDataParser::parseEncoderRight(const char* data, NavigatorDataStruct& navData)
{
    parseData(data, 2, [&](double val, int index) {
        if (index == 0) navData.encoder_right_pulses = val;
        if (index == 1) navData.encoder_right_time = val;
        });
}

void NavigatorDataParser::parseEncoderLeft(const char* data, NavigatorDataStruct& navData)
{
    parseData(data, 2, [&](double val, int index) {
        if (index == 0) navData.encoder_left_pulses = val;
        if (index == 1) navData.encoder_left_time = val;
        });
}