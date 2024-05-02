#pragma once
#include <iostream>

class PositionalState
{
    public:
        static PositionalState& GetInstance();

        PositionalState(const PositionalState&) = delete;
        PositionalState& operator=(const PositionalState&) = delete;

        void SetStartingPosition(double position_mm_x, double position_mm_y);
        void SetStartingAngle(double angleDeg);

        void UpdatePosition(double position_mm_x, double position_mm_y);
        void UpdateAngle(double angleDeg);

        std::pair<double, double> GetPosition();
        double GetAngle();
        

    private:

        PositionalState();

        // State variables
        std::atomic<double> _currentPosition_x; // milimeters
        std::atomic<double> _currentPosition_y; // milimeters
        std::atomic<double> _currentAngleDeg; // degree

        std::atomic<double> _startPosition_x; // meters
        std::atomic<double> _startPosition_y; // meters
        std::atomic<double> _startAngleDeg; // degree

        void initialiseStateVariables();

        void updatePosition(double position_mm_x, double position_mm_y);
        void updateAngle(double angleDeg);
};

