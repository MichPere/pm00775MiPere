#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

// Namespace dla biblioteki json
using json=nlohmann::json;
using namespace std;

class ReadConfig
{
    private:
        json configData;



    public:
        ReadConfig(std::string &filePath)
        {
            ifstream configFile(filePath);
             if(!configFile)
                {
                    cerr<<"Fauld open file"<<endl;
                }
                configFile>>configData;
        }
    std::string getDS18B20Path()const
    {
        return configData[]

    }


};

 
 int main()
 {
    ifstream configFile("config.json");
    if(!configFile)
    {
        cerr<<"Fauld open file"<<endl;
    }
    //Parsowanie json
    json config;
    configFile>>config;

    //Pobieranie wartości z pliku Json
    std::string ds18b20PathCO=config["DS18B20_CO"]["path"];
    std::string ds18b20PathCW=config["DS18B20_CW"]["path"];
    std::string pcf8574_01=config["PCF8574_01"]["address"];

    // Konwersja string do int
    int pcf8574_01INT=stoi(pcf8574_01,nullptr,16);

    cout<<"DS1:"<<ds18b20PathCO<<endl<<"DS2:"<<ds18b20PathCW<<endl
        <<"PCF:"<<pcf8574_01INT<<endl;
        
        //g++ -o readConfig readConfig.cpp -lnlohmann_json **teoretycznie bez ostatniej części
 }
