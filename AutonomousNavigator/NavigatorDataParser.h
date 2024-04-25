#pragma once
#include <cstring>
#include <sstream>
#include <functional>

#include "NavigatorDataStruct.h" 

class NavigatorDataParser
{
    public:

        static NavigatorDataParser& GetInstance();
        NavigatorDataParser(const NavigatorDataParser&) = delete;
        NavigatorDataParser& operator=(const NavigatorDataParser&) = delete;

        NavigatorDataStruct ParseData(const char* payload);

    private:

        NavigatorDataParser();  


        void parseSensorData(const char* sensorType, const char* data, NavigatorDataStruct& navData);
        void parseData(const char* data, int count, std::function<void(double, int)> updateFunc);
        void parseAcc(const char* data, NavigatorDataStruct& navData);
        void parseGyro(const char* data, NavigatorDataStruct& navData);
        void parseAngle(const char* data, NavigatorDataStruct& navData);
        void parseEncoderRight(const char* data, NavigatorDataStruct& navData);
        void parseEncoderLeft(const char* data, NavigatorDataStruct& navData);

};
