#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>


void 
Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  try{
    navx = new AHRS(frc::SPI::Port::kMXP);
  } catch(const std::exception& e){
    std::cout << e.what() <<std::endl;
  }
}


void 
Robot::RobotPeriodic() {
  //m_compressor.EnableDigital();
}


void 
Robot::AutonomousInit() {}


void 
Robot::AutonomousPeriodic() {}


void
Robot::TeleopInit() {
  m_time = 0;
  navx->Reset();
  m_shooter.setState(Shooter::State::IDLE);
  m_intake.setState(Intake::State::IDLE);
  m_shooter.Periodic();
  m_intake.Periodic();
}


void 
Robot::TeleopPeriodic() {
  m_time += m_timeStep;
  //frc::SmartDashboard::PutNumber("time", m_time);
  if(m_time <= 1.8){
    m_swerve.Initialize();
    m_shooter.Zero();
  }
  else if(m_time > 1.80 && m_time < 1.90){
    m_swerve.ResetEncoders();
  } 

  //else if
  if(m_time > 1.90){
    double x1, y1, x2;
    x1 = l_joy.GetRawAxis(0) * 0.7;
    y1 = l_joy.GetRawAxis(1);
    x2 = r_joy.GetRawAxis(0);
    x1 = abs(x1) < 0.05 ? 0.0: x1;
    y1 = abs(y1) < 0.05 ? 0.0: y1;
    x2 = abs(x2) < 0.05 ? 0.0: x2;
    
    m_swerve.Drive(-x1, -y1, -x2, navx->GetYaw(), true);
    
    if(r_joy.GetTrigger()){
      m_intake.setState(Intake::State::RUN);
      m_shooter.setState(Shooter::State::LOAD);
    }
    else if(l_joy.GetTrigger()){
      m_shooter.setState(Shooter::State::SHOOT);
    }
    else if(abs(xbox.GetRawAxis(4)) > 0.2 ){
      m_shooter.Manual(xbox.GetRawAxis(4));
      m_shooter.setState(Shooter::State::MANUAL);
    }
    else if(xbox.GetRawButton(1)){
      //m_swerve.ResetOdometry();
      //m_swerve.SetDriveControllerPID();
      //m_swerve.SetDriveControllerROTPID();
      m_shooter.setPID();
      m_shooter.Calibrate();
      //m_swerve.SetPID();
    } else {
      m_shooter.setState(Shooter::State::IDLE);
      m_intake.setState(Intake::State::IDLE);
    }

    m_intake.Periodic();
    m_shooter.Periodic();
  }
}


void 
Robot::TestInit() {
  m_time = 0;
  navx->Reset();
  m_swerve.ResetOdometry();
  m_swerve.GenerateTrajectory_1();
}


void 
Robot::TestPeriodic() {
  m_time += m_timeStep;
  frc::SmartDashboard::PutNumber("Y", m_swerve.GetYPosition());
  frc::SmartDashboard::PutNumber("X", m_swerve.GetXPostion());

  if(m_time <= 1.20){
    m_swerve.Initialize();
  }
  else if(m_time > 1.20 && m_time < 1.40){
    m_swerve.ResetEncoders();
  } 
  else if(m_time > 1.40){
    m_swerve.UpdateOdometry(navx->GetYaw());
    m_swerve.TrajectoryFollow(navx->GetYaw(), false);
  }
}


void 
Robot::DisabledInit() {}


void 
Robot::DisabledPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif