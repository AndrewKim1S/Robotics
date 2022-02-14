#include <Shooter.h>
#include <iostream>


Shooter::Shooter(){
    m_flywheelMaster.SetNeutralMode(NeutralMode::Coast);
    m_flywheelSlave.SetNeutralMode(NeutralMode::Coast);
    m_hood.SetNeutralMode(NeutralMode::Coast);
    m_kicker.SetNeutralMode(NeutralMode::Brake);

    m_flywheelMaster.SetSafetyEnabled(false);
    m_flywheelSlave.SetSafetyEnabled(false);
    m_turret.SetSafetyEnabled(false);
    
    m_flywheelMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);
    m_flywheelSlave.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);

    m_flywheelMaster.Config_kF(0, ShooterConstants::flywheelF);
    m_flywheelMaster.Config_kP(0, ShooterConstants::flywheelP);
    m_flywheelMaster.Config_kI(0, ShooterConstants::flywheelI);

    m_flywheelSlave.Config_kF(0, ShooterConstants::flywheelF);
    m_flywheelSlave.Config_kP(0, ShooterConstants::flywheelP);
    m_flywheelSlave.Config_kI(0, ShooterConstants::flywheelI);

    m_hood.Config_kP(0, ShooterConstants::hoodP);
    m_hood.Config_kI(0, ShooterConstants::hoodI);

    dataMap[-16.7] = {5400, 17000}; // from 2 - 19 ft go to 26
    dataMap[-15.4] = {4900, 15700};
    dataMap[-14.5] = {4600, 15500};
    dataMap[-12.6] = {4500, 14500};
    dataMap[-11.2] = {4400, 13800};
    dataMap[-9.7] = {4300, 13600};
    dataMap[-8.0] = {4100, 13500};
    dataMap[-6.2] = {3900, 13500};
    dataMap[-5.0] = {3500, 13500};
    dataMap[-2.5] = {2900, 13900};
    dataMap[-0.5] = {2200, 13200};
    dataMap[5.5] = {1900, 12300};
    dataMap[9.1] = {1700, 12300};
    dataMap[12.4] = {1500, 12300};
    dataMap[16.5] = {1000, 12200};
    dataMap[18.7] = {1000, 12000};

    m_hoodZero = false;
    m_turretZero = false;
}


//Periodic Function
void
Shooter::Periodic(){
    switch(m_state){
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
        case State::CLIMB:
            break;
        case State::MANUAL:
            break;
        default:
            break;
    }
    m_channel.Periodic();
}


//Aim Function for Turret
void
Shooter::Aim(){
    m_limelight->setLEDMode("ON");

    //Check if the limelight sees the target
    // double point = m_limelight->calculateDistance();
    // auto data = dataMap.find(point);
    // if(data != dataMap.end()){
    //     m_angle = data->second.first;
    //     m_speed = data->second.second;
    // } else {
    //     double point1, point2;
    //     if(withinRange(dataPoints, point, point1, point2)){
    //         auto data1 = dataMap[point1];
    //         auto data2 = dataMap[point2];
    //         double angle1, speed1;
    //         double angle2, speed2;
    //         angle1 = data1.first;
    //         speed1 = data1.second;
    //         angle2 = data2.first;
    //         speed2 = data2.second;

    //         m_angle = (angle1 + angle2)/2;
    //         m_speed = (speed1 + speed2)/2;
    //     }else{
    //         m_angle = 0;
    //         m_speed = 0;
    //     }
    // }
    
    // Set Turret movement
    double x_off = m_limelight->getXOff();
    double output = -m_turretController.Calculate(x_off);
    output = output > 0  && output > 0.4 ? 0.4: output;
    output = output < 0 && output < -0.4 ? -0.4: output;
    if(m_turret.GetSelectedSensorPosition() > ShooterConstants::turretMax &&
        output > 0){
        m_turret.Set(ControlMode::PercentOutput, 0.0);  
        return;
    }
    if(m_turret.GetSelectedSensorPosition() < ShooterConstants::turretMin &&
        output < 0){
        m_turret.Set(ControlMode::PercentOutput, 0.0);
        return;
    }
    else {
        //m_turret.Set(output);
    }

    // Set Flywheel Velocity
    m_flywheelMaster.Set(ControlMode::Velocity, m_speed);
    m_flywheelSlave.Set(ControlMode::Velocity, -m_speed);

    // Set Hood Position
    m_hood.Set(ControlMode::Position, m_angle);
    if(m_hood.GetSupplyCurrent() >= ShooterConstants::zeroingcurrent){
        m_hood.Set(ControlMode::PercentOutput, 0.0);
    }

    frc::SmartDashboard::PutNumber("velocity", m_flywheelMaster.GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("position", m_hood.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("yOff", m_limelight->getYOff());
}


//Interpolate shooter point values
bool
Shooter::withinRange(std::vector<double> array, double p, double p1, double p2){
    int left =0;
    int right = array.size() -1;
    if(p < array[left] || p > array[right]){
        return false;
    }
    int mid = (left + right)/2;
    while(left < right){
        if(array[mid] <= p && p <= array[mid+1]){
            p1 = array[mid];
            p2 = array[mid+1];
            return true;
        } else if(array[mid] <= p){
            left = mid;
        } else if(array[mid] >= p){
            right = mid;
        }
        mid = (left + right)/2;
    }
    return false;
}


//Shoot Function 
void
Shooter::Shoot(){
    if(Aimed()){
        m_channel.setState(Channel::State::RUN);
        Load();
    } else {
        m_channel.setState(Channel::State::IDLE);
    }
}


//Zero Function
//fix
void
Shooter::Zero(){
    if(!m_turretLimitSwitch.Get()){
        m_turret.Set(ControlMode::PercentOutput, 0.0);
        m_turret.SetSelectedSensorPosition(0);
        m_turretZero = true;
    }
    if(m_hood.GetSupplyCurrent() >= ShooterConstants::zeroingcurrent){
        m_hood.Set(ControlMode::PercentOutput, 0.0);
        m_hood.SetSelectedSensorPosition(0);
        m_hoodZero = true;
    }

    if(!m_turretZero){
        m_turret.Set(ControlMode::PercentOutput, 0.20);
    }
    if(!m_hoodZero){
        m_hood.Set(ControlMode::PercentOutput, -0.20);   
    }
}


//Load Function
void
Shooter::Load(){
    if(m_state == State::SHOOT){
        m_kicker.Set(ControlMode::PercentOutput, 0.2);
    } 
    else if(m_state == State::LOAD){
        if(!m_photogate.Get()){
            m_kicker.Set(ControlMode::PercentOutput, 0.0);
            m_channel.setState(Channel::State::IDLE);
        } else {
            m_kicker.Set(ControlMode::PercentOutput, 0.2);
            m_channel.setState(Channel::State::RUN);
        }
    }
}


//set the State of the shooter
void
Shooter::setState(State newState){
    m_state = newState;
}


//Check if the turret is aimed
bool
Shooter::Aimed(){
    if(abs(m_flywheelMaster.GetSelectedSensorVelocity() - m_speed) < 600
        && abs(m_hood.GetSelectedSensorPosition() - m_angle) < 100){
        return true;
    } else {
        return false;
    }
}


//Calibrate function
void
Shooter::Calibrate(){
    m_speed = frc::SmartDashboard::GetNumber("speed", 0.0);
    m_angle = frc::SmartDashboard::GetNumber("angle", 0.0);
    frc::SmartDashboard::PutNumber("speed", m_speed);
    frc::SmartDashboard::PutNumber("angle", m_angle);
}


//Set PID values
void
Shooter::setPID(){
    double P = frc::SmartDashboard::GetNumber("P", 0.0);
    frc::SmartDashboard::PutNumber("P", P);
    double I = frc::SmartDashboard::GetNumber("I", 0.0);
    frc::SmartDashboard::PutNumber("I", I);
    double D = frc::SmartDashboard::GetNumber("D", 0.0);
    frc::SmartDashboard::PutNumber("D", D);

    //m_turretController.SetPID(P, I, D);
    //m_flywheelController.SetPID(P,I,D);
    //m_hoodController.SetPID(P,I,D);
    m_hood.Config_kP(0, P);
    m_hood.Config_kI(0, I);
    m_hood.Config_kD(0, D);
}


//Stop All shooter movements
void
Shooter::Stop(){
    m_turret.Set(0);
    m_flywheelSlave.Set(0);
    m_flywheelMaster.Set(0);
    m_kicker.Set(0);
    m_hood.Set(0);
    m_limelight->setLEDMode("OFF");
    m_channel.setState(Channel::State::IDLE);
}


//Manual turret movement
void
Shooter::Manual(double turret_rot){
    if(abs(turret_rot) <= 0.05){
        turret_rot = 0;
    }
    if(turret_rot > 0 && m_turret.GetSelectedSensorPosition() > ShooterConstants::turretMax){
        turret_rot = 0;
    }
    if(turret_rot < 0 && m_turret.GetSelectedSensorPosition() < ShooterConstants::turretMin){
        turret_rot = 0;
    }
    //frc::SmartDashboard::PutNumber("manual", turret_rot * 0.2);
    m_turret.Set(ControlMode::PercentOutput, turret_rot*0.2);
}


//Convert unit per 100 ms to rpm 
double
Shooter::convertToRPM(double ticks){
    return ticks/ShooterConstants::TalonFXunitsperrot*600;
}