#include <Channel.h>
#include <iostream>

//Constructor
Channel::Channel(){
    m_channel.SetNeutralMode(NeutralMode::Brake);
    m_channel.SetSafetyEnabled(false);
}


//Periodic Function
void
Channel::Periodic(){
    switch(m_state){
        case State::IDLE:
            Stop();
            break;
        case State::RUN:
            Run();
            break;
        default:
            break;
    }
}


//Run function
void
Channel::Run(){
    m_channel.Set(ControlMode::PercentOutput, 0.35);
}


//Stop all channel movement
void
Channel::Stop(){
    m_channel.Set(ControlMode::PercentOutput, 0.0);
}


//set State of the Channel
void
Channel::setState(State newState){
    m_state = newState;
}