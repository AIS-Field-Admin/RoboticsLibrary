#include "pch.h"
#include "PositionalState.h"

PositionalState::PositionalState()
{
    position_x = 0; 
    position_y = 0; 
    angleDeg = 0; 
}

PositionalState& PositionalState::GetInstance()
{
    static PositionalState instance;
    return instance;
}