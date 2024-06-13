#include <iostream>
#include <unistd.h>
#include "wiringPiI2C.h"
#include "wiringPi.h"
//#include "headlines.h"
#include <bitset>
#include <csignal> // biblioteka ustawiająca wszystkie piny w stan niski po zakończeniu programu

#define PCF8574_ADR 0x20 //adres PCF-a
#define IMPUT_MASK 0b00000111
uint8_t outputState=0b00000111;


using namespace std;

int fd; // file description dla I2C


void setOutputs(uint8_t states)
{
    wiringPiI2CWrite(fd,states);
}

uint8_t readImputs()
{
    uint8_t data=wiringPiI2CRead(fd);
    return data&IMPUT_MASK;
}


void setOutputsHigh(int pin)
{
    outputState |= (1<<pin);
    setOutputs(outputState);
}

void setOuputsLow(int pin)
{
    outputState &= ~(1<<pin);
    setOutputs(outputState);
}

void handleSignal(int signal)
{
    setOutputs(0b11111000);
    exit(0);
}

int main()
{
    // Inicjowanie wiringPi
    if(wiringPiSetup()<0)
    {
        cerr<<"Faild to initialize wiringPi"<<endl;
    }
    
    fd=wiringPiI2CSetup(PCF8574_ADR);
    if(fd<0)
    {
        cerr<<"Filed to initialize I2C"<<endl;
    }
    setOutputs(outputState);
    signal(SIGINT,handleSignal); //uruchomienie programu ustawiającego wszystko na zero

    // Ustawienie początkowych stanów wejść
    while(true)
    {
        setOutputsHigh(4);
        uint8_t inputs=readImputs();
        system("clear");
        cout<<"PD0: "<<((inputs& 0b00000001)?"HIGH":"LOW")<<"  PD1: "<<((inputs& 0b00000010)?"HIGH":"LOW")<<"  PD2: "<<((inputs& 0b00000100)?"HIGH":"LOW")<<endl;
       (inputs& 0b00000100)?setOutputsHigh(5):setOuputsLow(5);
       setOutputsHigh(6);
        delay(1000);
    }

       
    
    return 0;
}
