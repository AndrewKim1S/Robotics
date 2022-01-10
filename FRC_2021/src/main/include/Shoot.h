#pragma once

#include <ctre/Phoenix.h>
#include "frc/WPILib.h"
#include <frc/XboxController.h>
#include "Limelight.h"
#include <frc/Servo.h>
#include "sdb_types.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <cmath>
#include <vector>
#include <unordered_map>
#include "Channel.h"

class Shoot{
    public:
        enum State {
            Idle,
            Aiming,
            Shooting,
            Calibrate
        };

        Shoot();
        //~Shoot();
        
        //Periodic
        void Periodic(double robot_yaw);
        void Manual_Turret(double turret_rot);
        //void Zero();
        void Manual_Zero();

        void Auto();
        void setState(State newState);
        void ShootState();
        
        //Shooting & Aiming
        void Aim(double robot_yaw);
        void FindTarget(double robot_yaw);
        bool interpolate(std::vector<double>& array, double p, double& p1, double& p2);
        double GetLimelightY();
        double GetLimelightX();

        //Calibrating Shooter
        void Shooter_Calibrate();
        void Turret_Calibrate();
    

        bool target_found = false;

    private:
        WPI_TalonFX * turret = new WPI_TalonFX(4);
        WPI_TalonFX * shoot_master = new WPI_TalonFX(5);
        WPI_TalonFX * shoot_slave = new WPI_TalonFX(6);

        frc::Servo servo_left{3};
        frc::Servo servo_right{4};

        Limelight * limelight = new Limelight();

        State state;

        double turret_rot_limit = -20480;

        double TKi, TKp, TKd, x_off;
        double flywheel_out, hood_out, kicker_out;
        double turret_yaw;
        double total_yaw;

        frc::DigitalInput *turret_limit_switch = new frc::DigitalInput(1);

        std::vector<double> dataPoints = {-10, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 
            1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 20};
	    // hash map: data points => {angle, speed}
	    std::unordered_map<double, std::pair<double, double>> dataMap;
};