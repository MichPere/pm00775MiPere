#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "readFromFile.h"

using namespace std; 

int readTemperatureFromFile(std::string& fileName){
    int value_T;
    ifstream plik(fileName);

    if(!plik.good()){
        cerr<<"Nie można otworzyć pliku"<<endl;
    }
    
    while(!plik.eof()){
        plik>>value_T;
    }
    plik.close();
    return value_T;
}