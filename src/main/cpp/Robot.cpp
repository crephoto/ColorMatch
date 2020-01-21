/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>


#include <frc/smartdashboard/SmartDashboard.h>

#include <frc/util/Color.h>
#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>

#include "Robot.h"

clock_t check_time;
float interval = 0.0625; //not seconds; seems to be interval * 4 = seconds


void Robot::RobotInit() {
  Ticks = 0;
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  //added this 1/15/20, might make the shuffleboard display color, not tested yet
  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);
  PreviousColor = "Black"; //Arbitrary value
  std::cout << clock();
  frc::SmartDashboard::PutBoolean("Tick Reset", TickReset);
}  

void Robot::DisabledInit() {
  // SHUT UP!!
}
void Robot::DisabledPeriodic() {
  // SHUT UP!!!
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */

void Robot::RobotPeriodic() {

    /**
     * The method GetColor() returns a normalized color value from the sensor and can be
     * useful if outputting the color to an RGB LED or similar. To
     * read the raw color, use GetRawColor().
     * 
     * The color sensor works best when within a few inches from an object in
     * well lit conditions (the built in LED is a big help here!). The farther
     * an object is the more light from the surroundings will bleed into the 
     * measurements and make it difficult to accurately determine its color.
     */
    frc::Color detectedColor = m_colorSensor.GetColor();

    /**
     * Run the color match algorithm on our detected color
     */
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

  
    if (matchedColor == kBlueTarget) {
      colorString = "Blue";
    } else if (matchedColor == kRedTarget) {
      colorString = "Red";
    } else if (matchedColor == kGreenTarget) {
      colorString = "Green";
    } else if (matchedColor == kYellowTarget) {
      colorString = "Yellow";
    } else {
      colorString = "Unknown";
    }
    /* */
    /**
     * Open Smart Dashboard or Shuffleboard to see the color detected by the 
     * sensor.
     */

  
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);
    frc::SmartDashboard::PutString("Detected Color", colorString);
    frc::SmartDashboard::PutNumber("Matched R", matchedColor.red);
    frc::SmartDashboard::PutNumber("Matched G", matchedColor.green);
    frc::SmartDashboard::PutNumber("Matched B", matchedColor.blue);

    float elapsed_time = float(clock() - check_time) / float(CLOCKS_PER_SEC);

    if (elapsed_time > interval) {
      std::cout << "Time: ";
      std::cout << (float(clock()) / float(CLOCKS_PER_SEC));
      std::cout << "\n";
      check_time = clock();

        if (Ticks < 29) {
        CurrentColor = colorString;
        SpinnyBoi.Set(0.1);

          if (CurrentColor != PreviousColor) {
            PreviousColor = CurrentColor;
            Ticks += 1;
          }

      } else if (TickReset && frc::SmartDashboard::GetBoolean("Tick Reset", TickReset)) {
        Ticks = 1;

      } else {
        SpinnyBoi.Set(0);
      } 
    } 
    
 

  
    //counts how many times the color changes, then when it reaches 29 ticks, stops the SpinnyBoi
    
    frc::SmartDashboard::PutNumber("Ticks", (Ticks-1));
    frc::SmartDashboard::PutNumber("Rotations", (Ticks-1) / 8);
    frc::SmartDashboard::GetBoolean("Reset Ticks", TickReset);
    //frc::SmartDashboard::PutData("Reset Ticks", new ticksReset());

}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
