#include "Climber.h"

//Constructor
Climber::Climber(){

}


//Periodic Function
void
Climber::Periodic(){
    switch(state){
        case State::IDLE:
            break;
        case State::INITIALIZE:
            break;
        case State::CLIMB:
            break;
        default:
            break;
    }
}


//Idle function
void
Climber::Idle(){

}


//Initialization function
void
Climber::Initialize(){

}


//Climb function
void
Climber::Climb(){

}


//set new state function
void
Climber::setState(State newState){
    state = newState;
}


//Calibration function for whatever
void
Climber::Calibrate(){
    
}