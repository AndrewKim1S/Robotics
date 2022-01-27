#include <Channel.h>

//Constructor is empty for now
Channel::Channel(){}


//Periodic Function
void
Channel::Periodic(){
    switch(state){
        case State::IDLE:
            break;
        case State::RUN:
            break;
        default:
            break;
    }
}


//Run function
void
Channel::Run(){

}


//Stop all channel movement
void
Channel::Stop(){

}


//set State of the Channel
void
Channel::setState(State newState){
    state = newState;
}