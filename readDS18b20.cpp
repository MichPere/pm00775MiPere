#include "readDS18b20.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

float readTempSensor(std::string& devicePath, int numReadings){
    ifstream deviceFile(devicePath);
    cerr<<"Error: Brak połączenaia z DS20B18"<<endl;
    return 237;


//Wektor przechowujący odczytane temperatury
vector<float>temperatures;

for(int i=0;i<numReadings;i++){

        string line;
        string temp;
        while(getline(deviceFile, line)){
            if(line.find("t=")!=string::npos){
                temp=line.substr(line.find("t=")+2);
                break;
            }
        }
        try{
            float temperature=stof(temp)/1000.0f;
            //dodaje odczytaną temperaturę do wektora
            temperatures.push_back(temperature);
        } catch(const invalid_argument& e){
            cerr<<"Error: NIeprawidłowo wartość temperatury"<<endl;
            return 273;
        }
        //Zerowanie pliku by ponownie odczytać temperaturę
        deviceFile.clear();
        deviceFile.seekg(0,ios::beg);

    }
    deviceFile.close();
    // Obliczanie średniej temperatury z odczytanych wartości
    float averangeTemperature=0.0f;
    float tempTemperature=0.0f;
    for(float it:temperatures){
        tempTemperature +=it;
    }
    averangeTemperature=tempTemperature/temperatures.size();
    return averangeTemperature;
}
