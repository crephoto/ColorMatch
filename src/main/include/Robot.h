/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <time.h>

#include <rev/CANSparkMax.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {

/**
 * Change the I2C port below to match the connection of your color sensor
 */
static constexpr auto i2cPort = frc::I2C::Port::kOnboard;

/**
 * A Rev Color Sensor V3 object is constructed with an I2C port as a 
 * parameter. The device will be automatically initialized with default 
 * parameters.
 */
rev::ColorSensorV3 m_colorSensor{i2cPort};


  /**
   * A Rev Color Match object is used to register and detect known colors. This can 
   * be calibrated ahead of time or during operation.
   * 
   * This object uses a simple euclidian distance to estimate the closest match
   * with given confidence range.
   */
  rev::ColorMatch m_colorMatcher;
  rev::CANSparkMax SpinnyBoi{1, rev::CANSparkMax::MotorType::kBrushless};

  /**
   * Note: Any example colors should be calibrated as the user needs, these
   * are here as a basic example.
   */
  
  /* Starting REV calibration values */
  /*
  static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
  static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
  static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
  static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
  /* */
  /* 2020-01-14 Calibrated "LED ON" values */
  static constexpr frc::Color kBlueTarget = frc::Color(0.125, 0.427, 0.449);
  static constexpr frc::Color kGreenTarget = frc::Color(0.166, 0.581, 0.253);
  static constexpr frc::Color kRedTarget = frc::Color(0.523, 0.343, 0.130);
  static constexpr frc::Color kYellowTarget = frc::Color(0.320, 0.559, 0.120);
 public:
 
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  bool TickReset = false; //resets ticks when reaches 29 ticks
  std::string m_autoSelected;
  int Ticks; //Starts at 1
  std::string PreviousColor;
  std::string CurrentColor;
};
