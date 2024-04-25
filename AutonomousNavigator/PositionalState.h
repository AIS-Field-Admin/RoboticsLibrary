#pragma once
#include <atomic>

class PositionalState
{
    public:
        static PositionalState& GetInstance();

        PositionalState(const PositionalState&) = delete;
        PositionalState& operator=(const PositionalState&) = delete;

        // State variables
        std::atomic<double> position_x; // meters
        std::atomic<double> position_y; // meters
        std::atomic<double> angleDeg; // degree


    private:

        PositionalState();
};

