#pragma once

#include "Constants.h"
#include <ctre/Phoenix.h>
#include <frc/controller/PIDController.h>
#include <frc/DigitalInput.h>


class Shooter{
    public:
        enum State{
            IDLE,
            SHOOT,
            ZERO,
            AIM,
            LOAD
        };

        Shooter();
        void Periodic();
        void Aim();
        void Shoot();
        void Zero();
        void Load();
        void Stop();
        void setState(State newState);
        bool Aimed();
        void Calibrate();

    private:
        // WPI_TalonFX m_flywheelMaster{ShooterConstants::shootMotorPortMaster};
        // WPI_TalonFX m_flywheelSlave{ShooterConstants::shootMotorPortSlave};
        // WPI_TalonFX m_turret{ShooterConstants::turretMotorPort};
        // WPI_TalonFX m_hood{ShooterConstants::hoodMotorPort};
        // WPI_TalonFX m_kicker{ShooterConstants::kickerMotorPort};

        // frc::DigitalInput m_turretLimitSwitch{ShooterConstants::turretLimitSwitch};

        frc2::PIDController m_turretController{ShooterConstants::turretP,
            ShooterConstants::turretI, ShooterConstants::turretD};
        frc2::PIDController m_flywheelController{ShooterConstants::flywheelP,
            ShooterConstants::flywheelI, ShooterConstants::flywheelD};
        frc2::PIDController m_hoodController{ShooterConstants::hoodP,
            ShooterConstants::hoodI, ShooterConstants::hoodD};

        State state;

        const double turretLimitMin = ShooterConstants::Min;
        const double turretLimitMax = ShooterConstants::Max;
};