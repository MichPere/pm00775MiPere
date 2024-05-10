#include "writeToFile.h"
#include <iostream>
#include <fstream>

using namespace std;

void writeSetTemperatureToFile(const std::string& filePath, float temperature){
    // Otwarcie pliku do zapisu
    ofstream plik(filePath);
    // Sprawdzenie czy plik jest otwarty
    if(!plik.good()){
        cerr<<"Nie można otworzyć pliku"<<endl;
    }
    // Zapis zmiennej do pliku
    plik<<temperature<<endl;
    // Zamknięcie pliku
    plik.close();

}