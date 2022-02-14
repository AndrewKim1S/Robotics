#pragma once

#include "Constants.h"
#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>

class Intake{
    public:
        enum State {
            IDLE,
            RUN,
            UNJAM,
            CLIMB,
            STOP,
            ZERO
        };

        Intake();
        void Periodic();
        void Deploy();
        void Run();
        void Stop();
        void Retract();
        void Unjam();
        void setState(State newstate);

    private:
        WPI_TalonFX m_intakeMotor{IntakeConstants::intakeMotorPort};

        //frc::Solenoid pneumatics{frc::PneumaticsModuleType::REVPH, 
            //IntakeConstants::solenoidPort};

        State m_state;
};