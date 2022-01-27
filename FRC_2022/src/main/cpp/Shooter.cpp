#include <Shooter.h>

//Empty Constructor Cause why not maybe configure motors?
Shooter::Shooter(){

}


//Periodic Function
void
Shooter::Periodic(){
    switch(state){
        case State::ZERO:
            Zero();
            break;
        case State::IDLE:
            Stop();
            break;
        case State::LOAD:
            Load();
            break;
        case State::AIM:
            Aim();
            break;
        case State::SHOOT:
            Aim();
            Shoot();
            break;
        default:
            break;
    }
}


//Aim Function for Turret
void
Shooter::Aim(){

}


//Shoot Function 
void
Shooter::Shoot(){

}


//Zero Function
void
Shooter::Zero(){

}


//Load Function
void
Shooter::Load(){

}


//set the State of the shooter
void
Shooter::setState(State newState){
    state = newState;
}


//Check if the turret is aimed
bool
Shooter::Aimed(){

}


//Calibrate function
void
Shooter::Calibrate(){
    
}


//Stop All shooter movements
void
Shooter::Stop(){

}