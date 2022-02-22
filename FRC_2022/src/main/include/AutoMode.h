#include <iostream>
#include <vector>
#include <frc/smartdashboard/SmartDashboard.h>
// #include "Intake.h"
// #include "Shooter.h"
// #include "SwerveDrive.h"

class AutoMode{
    public:
        AutoMode();

        enum State{
            SHOOT,
            INTAKE,
            DRIVE,
            IDLE,
            DRIVEnINTAKE
        };

        std::vector<State> actions = {DRIVEnINTAKE, IDLE, SHOOT, IDLE};
        std::vector<double> times = {2.3, 2.4, 5.4, 15.0};

        void ResetAuto();
        void Periodic(double time);
        State getState();

    private:
        State state;
        size_t index;
};