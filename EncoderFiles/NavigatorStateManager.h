#pragma once
#include <iostream>

#include "INavigatorStateManager.h"
#include "NavigatorStateKeeper.h"
#include "NavigatorDataParser.h"  
#include "NavigatorDataStruct.h"  

class NavigatorStateManager : public INavigatorStateManager
{
    public:
        NavigatorStateManager();

        void UpdateStates(const char* data) override;

    private:

        void updateStateKeeper(const NavigatorDataStruct& data);
        
};

