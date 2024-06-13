#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstdlib>
#include "wiringPi.h"
#include "headlines.h"


using namespace std;

DS18B20::DS18B20(string devicePath):devicePath(devicePath){}

float DS18B20::readSensor()
{
    fstream plik;
        plik.open(devicePath,ios::in);
        if(!plik.is_open())
        {
            cerr<<"Nie można otworzyć pliku"<<endl;
        }
        
        while(!plik.eof())
        {
        plik>>tempStr;
        if(tempStr.find("t=")!=string::npos){
                temp=tempStr.substr(tempStr.find("t=")+2);
                break;
            }
        }
   
     temperature=stof(temp)/1000.0f;
      
      plik.close();

      return temperature;
}


int main()
{   
    DS18B20 DS1(pathDS1_CO);

    while(true)
    {
        cout<<"TemDS1: "<<DS1.readSensor()<<endl;
        delay(1000);
    }
    
    return 0;
}