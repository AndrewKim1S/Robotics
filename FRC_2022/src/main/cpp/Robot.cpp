#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  try{
    navx = new AHRS(frc::SPI::Port::kMXP);
  } catch(const std::exception& e){
    std::cout << e.what() <<std::endl;
  }
}


void Robot::RobotPeriodic() {}
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}


void Robot::TeleopInit() {
  m_time_step = 0;
  navx->Reset();
}


void Robot::TeleopPeriodic() {
  frc::SmartDashboard::PutNumber("timestep", m_time_step);
  m_time_step += 0.02;
  if(m_time_step <= 2.00){
    std::cout << "Initializing" << std::endl;
    m_swerve.Initialize();
  }
  if(m_time_step > 2.00 && m_time_step < 2.10){
    std::cout << "Encoder reset" << std::endl;
    m_swerve.ResetEncoders();
  } else if(m_time_step > 2.10){

    //Deadband 
    double x1, y1, x2;
    x1 = l_joy.GetRawAxis(0);
    y1 = l_joy.GetRawAxis(1) * 0.6;
    x2 = r_joy.GetRawAxis(0);
    x1 = abs(x1) < 0.05 ? 0.0: x1;
    y1 = abs(y1) < 0.05 ? 0.0: y1;
    x2 = abs(x2) < 0.05 ? 0.0: x2;

    m_swerve.Drive(-x1, -y1, -x2, navx->GetYaw(), true);

    m_swerve.UpdateOdometry(navx->GetRate(), navx->GetYaw());
    m_swerve.debug();
    
    //Button (A)
    if(xbox.GetRawButton(1)){
      std::cout << "reset Odometry" << std::endl;
      m_swerve.ResetOdometry();
    }
  }
}


void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}


void Robot::TestInit() {
  //navx->Reset();
  //m_timer.Reset();
  m_time_step = 0;
}


void Robot::TestPeriodic() {
  frc::SmartDashboard::PutNumber("timestep", m_time_step);
  m_time_step += 0.02;
  if(m_time_step <= 2.00){
    m_swerve.Initialize();
  }
  if(m_time_step > 2.00 && m_time_step < 2.10){
    m_swerve.ResetEncoders();
  } else if(m_time_step > 2.10){
  }
}


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif