#pragma once

#include "Constants.h"
#include "Limelight.h"
#include <ctre/Phoenix.h>
#include <frc/controller/PIDController.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Channel.h"
#include <vector>
#include <unordered_map>


class Shooter{
    public:
        enum State{
            IDLE,
            SHOOT,
            ZERO,
            AIM,
            LOAD,
            CLIMB,
            MANUAL
        };

        Shooter();
        void Periodic();
        void Aim();
        void Shoot();
        bool withinRange(std::vector<double> array, double p, double p1, double p2);
        void Zero();
        void Load();
        void Stop();
        void setState(State newState);
        bool Aimed();
        void Calibrate();
        void setPID();
        void Manual(double input);
        double convertToRPM(double ticks);

    private:
        //TalonFX in ticks - 0 - 20,000
        //in rpm - 0 -6000

        WPI_TalonFX m_flywheelMaster{ShooterConstants::shootMotorPortMaster};
        WPI_TalonFX m_flywheelSlave{ShooterConstants::shootMotorPortSlave};
        WPI_TalonFX m_turret{ShooterConstants::turretMotorPort};
        WPI_TalonFX m_hood{ShooterConstants::hoodMotorPort};
        WPI_TalonFX m_kicker{ShooterConstants::kickerMotorPort};

        frc::DigitalInput m_turretLimitSwitch{ShooterConstants::turretLimitSwitch};
        frc::DigitalInput m_photogate{ShooterConstants::photogate};

        frc2::PIDController m_turretController{ShooterConstants::turretP,
            ShooterConstants::turretI, ShooterConstants::turretD};
        // frc2::PIDController m_flywheelController{ShooterConstants::flywheelP,
        //     ShooterConstants::flywheelI, ShooterConstants::flywheelD};
        // frc2::PIDController m_hoodController{ShooterConstants::hoodP,
        //     ShooterConstants::hoodI, ShooterConstants::hoodD};

        State m_state;

        Limelight * m_limelight = new Limelight();

        Channel m_channel;

        double m_angle;
        double m_speed;

        bool m_hoodZero = false;
        bool m_turretZero = false;

        //For storing hood and angle values for shooting
        //angle , speed
        std::vector<double> dataPoints = {
            -16.7, -15.4, -14.5, -12.6, -11.2, -9.7, -8.0, -6.2, -5.0,
            -2.5, -0.5, 5.5, 9.1, 12.4, 16.5, 18.7
        };
        std::unordered_map <double, std::pair<double, double>> dataMap;

};