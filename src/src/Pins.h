#ifndef PINS_H
#define PINS_H

// Buttons
#define BUTTON_1 16   // Active LOW (press = GND)
#define BUTTON_2 15   // Active HIGH (press = 3V3)
#define BUTTON_OK 0   // Active LOW (press = GND)

// Status LED
#define STATUS_LED 2  // Active LOW (LOW = ON)

// Relays
#define RELAY_1 14
#define RELAY_2 12

// OneWire (Temperature Sensors)
#define ONE_WIRE_BUS 13

// I2C (Display)
#define I2C_SCL 5
#define I2C_SDA 4

#endif
