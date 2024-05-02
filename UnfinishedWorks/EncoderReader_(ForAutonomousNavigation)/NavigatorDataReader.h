// NavigatorDataReader.h

#ifndef NAVIGATOR_DATA_READER_H
#define NAVIGATOR_DATA_READER_H

#include <string>
#include <iostream>

#include "NavigatorConnectionEstablisher.h"
#include "AutonomousNavigatorGlobals.h"

class NavigatorDataReader {

    public:
        NavigatorDataReader();

        const char* ReadData();

    private:

        SOCKET _socket;
};

#endif // NAVIGATOR_DATA_READER_H