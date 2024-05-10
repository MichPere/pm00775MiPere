#ifndef DS18B20_H
#define DS18B20_H

#include <iostream>
#include <string>

using namespace std;

// Deklaracja funkcji odczytu temperatury z sensora

float readTempSensor(const std::string& devicePath);

#endif //DS18B20_H
