#pragma once


namespace
GeneralConstants{
    const double timeStep = 0.02;

    //In meters
    const double goalHeight = 2.641;
    const double cameraHeight = 0.4572;
    const double cameraPitch = 50;
}


namespace
OIConstants{
    //Joystick & xbox input ports
    const int l_joy_port = 0;
    const int r_joy_port = 1;
    const int O_joy_port = 2;
}


namespace
DriveConstants{
    //Dimensions of the Robot - SwerveDrive.h
    const double Width = 29;
    const double Length = 29;

    //Absolute Encoder offsets
    const double FLOFF = -108.5;
    const double FROFF = 157.0;
    const double BLOFF = 7.91;
    const double BROFF = -18.98;

    //Ports for Back Right Swerve Module - SwerveDrive.h
    const int BRanglePort = 18;
    const int BRspeedPort = 17;
    const int BRencoder = 8;
    //const int BRencoderPortA = 6;
    //const int BRencoderPortB = 7;
    //const int BRencoderPWM = 13;

    //Ports for Back Left Swerve Module - SwerveDrive.h
    const int BLanglePort = 16;
    const int BLspeedPort = 15;
    const int BLencoder = 42;
    //const int BLencoderPortA = 4;
    //const int BLencoderPortB = 5;
    //const int BLencoderPWM = 12;

    //Ports for Front Right Swerve Module - SwerveDrive.h
    const int FRanglePort = 14;
    const int FRspeedPort = 13;
    const int FRencoder = 62;
    //const int FRencoderPortA = 2;
    //const int FRencoderPortB = 3;
    //const int FRencoderPWM = 11;

    //Ports for Front Left Swerve Module - SwerveDrive.h
    const int FLanglePort = 12;
    const int FLspeedPort = 11;
    const int FLencoder = 10;
    //const int FLencoderPortA = 0;
    //const int FLencoderPortB = 1;
    //const int FLencoderPWM = 10;

    //Wheeldrive 
    constexpr double MAX_VOLTS = 1.0;
    const double speedGearRatio = 1/6.12;
    const double angleGearRatio = 1/12.8;
    const double P = 0.006;
    const double I = 0.001;
    const double D = 0.0002;
    const double Pinit = 0.008;
    const double Iinit = 0.001;
    const double Dinit = 0.0001;

    //Swerve Controller
    const double fwdstrP = 0.45;
    const double fwdstrI = 0.0;
    const double fwdstrD = 0.0;
    const double rotP = 0.0006;
    const double rotI = 0.00004;
    const double rotD = 0.0;
}


//None of these values have been set yet
namespace
ShooterConstants{

    //TalonFX MotorID
    const int shootMotorPortMaster = 22; //confirmed
    const int shootMotorPortSlave = 23; //confirmed
    const int turretMotorPort = 20; //confirmed
    const int hoodMotorPort = 19; //confirmed
    const int kickerMotorPort = 21; //confirmed

    //Limit Switch
    const int turretLimitSwitch = 9; //confirmed

    //Photogate
    const int photogate = 8; 

    //Turret Controller
    const double turretP = 0.021; //fairly good
    const double turretI = 0.00006;
    const double turretD = 0.0005;

    //Flywheel Controller
    const double flywheelF = 0.03;
    const double flywheelP = 0.02;
    const double flywheelI = 0.0002;
    const double flywheelD = 0.0;

    //Hood Controller
    const double hoodP = 0.08; 
    const double hoodI = 0.0002;
    const double hoodD = 0.0;

    //Turret limit values;
    const double turretMax = -1000.0; //confirmed
    const double turretMin = -63000.0; //confirmed

    const double hoodMax = 5500; //confirmed
    const double hoodMin = 0; //confirmed

    const double angleOff = 300;

    const double zeroingcurrent = 2.75; //confirmed

    const double TalonFXunitsperrot = 2048;
}


namespace
IntakeConstants{
    const int intakeMotorPort = 50; //confirmed

    const int solenoidPort = 0;
}


//None of these values are set yet
namespace
ClimbConstants{
    const int gearboxPort1 = 30; //confirmed
    const int gearboxPort2 = 31; //confirmed
    const int solenoid1Port = 1;
    const int solenoid2Port = 2;
}


namespace
ChannelConstants{
    const int channelMotorPort = 40; //confirmed
}


//0 is intkae
//1 is disk brake for climber gearbox
// 2 is climb first stage
// 3 is climb 2nd stage