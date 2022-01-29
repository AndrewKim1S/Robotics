#include "Intake.h"

//Constructor
Intake::Intake(){
    // intakeMotor.SetNeutralMode(NeutralMode::Coast);
    // intakeMotor.SetSafetyEnabled(false);
}


//Periodic Function to execute intake states
void
Intake::Periodic(){
    switch(state){
        case State::IDLE:
            Retract();
            break;
        case State::RUN:
            Deploy();
            Run();
            break;
        case State::UNJAM:
            Unjam();
            break;
        case State::CLIMB:
            Retract();
            break;
        default:
            break;
    }
}


//Deploy the Intake
void
Intake::Deploy(){
    // pneumatics.Set(true);
}


//Run the Intake
void
Intake::Run(){
    // intakeMotor.Set(ControlMode::PercentOutput, 0.25);
}


//Retract the Intake
void
Intake::Retract(){
    // pneumatics.Set(false);
    // intakeMotor.Set(0);
}


//Unjam the Intake
//Assume that negative output is reverse
void
Intake::Unjam(){
    // intakeMotor.Set(ControlMode::PercentOutput, -0.25);
}


//Set the state of the intake
void
Intake::setState(State newstate){
    state = newstate;
}