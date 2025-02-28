#ifndef SETPOINTS_H
#define SETPOINTS_H

struct Setpoints {
  float temperatureSetpoint = 20.0;
  float heatingDifferential = 2.0;
  float coolingDifferential = 2.0;
  float compressorDelay = 1.0;
  float calibration = 0.0;
  char temperatureUnit = 'C';
};

#endif