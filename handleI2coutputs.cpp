#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "handleI2coutputs.h"


#define PCF8574_ADDR 0x27 

using namespace std;

int handleI2Coutput(int file, int8_t config,int8_t dataIoSend){

    //Otwarcie interfejsu I2C
    if((file=open("/dev/i2c-1",O_RDWR))<0){
        cerr<<"Nie można otoworzyć interfejsu I2C"<<endl;
        return 1;
    }

    // Ustawienie adresu urządzenia 
    if(ioctl(file, I2C_SLAVE, PCF8574_ADDR)<0){
        cerr<<"Błąd ustawienia urządzenia"<<endl;
        return 1;
    }

    //Konfiguracja PCF8574
    //Ustawienia wszystkich pinów jako wyjścia
    config=0xFF; //wszystkie piny ustawione na 1 jako wyjścia
    if(write(file, &dataIoSend, sizeof(dataIoSend))!=sizeof(dataIoSend)){
        cerr<<"Błąd wysyłania danych przez I2C"<<endl;
        return 1;
    }
    // Zamknięcie interfejsu I2C
    close(file);
    return 0;
}