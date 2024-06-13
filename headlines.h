#include <iostream>

using namespace std;

#ifndef headlines_H
#define Headlines_H

#define pathDS1_CO "/sys/bus/w1/devices/28-21c1d4466afd/w1_slave" // adres sprzętowy sensora DS1_CO
#define pathDS2_CW "/sys/bus/w1/devices/28-do poprawy/w1_slave" // adres sprzętowy sensora DS1_CW


//=====   Zmienne globalne sprzętowe CO & CW ===================

// Zmienne encodera CO

    volatile int encoderPosCO=160;
    volatile int encoderPosreturnedCO=encoderPosCO/4;
    volatile int encodedCO;
    int lastEncodedCO=0;
    const int pinCO_CLK=28;
    const int pinCO_DT=27;
    const int pinCO_SW=26; //pin momentSwitch w encoderze
    bool interruptFlagCO=false;

// Zmienne encodera CW
    volatile int encoderPosCW=160;
    volatile int encoderPosreturnedCW=encoderPosCW/4;
    volatile int encodedCW;
    int lastEncodedCW=0;
    const int pinCW_CLK=6;
    const int pinCW_DT=5;
    const int pinCW_SW=4; //pin momentSwitch w encoderze
    bool interruptFlagCW=false;

void readEncoderCO(void); //Czyta i zapiuje wartość z encoderów
void readEncoderCW(void); //Czyta i zapiuje wartość z encoderów
void setPinINPUTS(int pinCLK, int pinDT, int pinSW, void read1(void),void read2(void)); // definiuje i konfiguruje piny oraz przerwania
//void interruptsPins(int pinCLK, int pinDT, int pinSW, void read(void)); //funkcja wywołująca przerwania
static void interruptsPins(void);
void foo(void); // taka mała funkcja do debugowania

//____________________  KOniec Encoder  ____________________________


//===================  Czujniki temperatury DS18B20 class  ================

class DS18B20
{
private:
    std::string devicePath;
    std::string tempStr;
    std::string line;
    std::string temp;
    float temperature;

public:
    DS18B20(string devicePath);
    float readSensor();
    
};




/*zmienne temperaturowe czytane*/
float tempCo_r;
float tempCw_r;
bool tempRoom_r;

/*zmienne temperaturowe ustawiane*/
int tempCo_s;
int tempCw_s;

/*tryb pracy/ sygnalizacja*/
bool winterSumer_s; // false -summer; true -winter
bool waterCwOff_s; // true- wyłaczenie CW

/*czujniki zewnętrzne/ sygnały inputs*/
bool sweepSensor_r; // czujnik kominowy
bool tempLimiter_r; // termostat bezpieczeństwa
bool pressureWater_r; //czujnik ciśnienia minimalnego w obiegu
bool burnerError_r; // błąd palnika

/*wyjście żądanie */
bool burnerOn_s; // true- żądanie pracy palnika
float burnerPwm_s; // modulacja pracy palnika
bool pumpCo_s; // true- żądanie praca pompy CO
bool pumpCw_s; // true- żądanie praca pompy CW

 





#endif //headlines_H