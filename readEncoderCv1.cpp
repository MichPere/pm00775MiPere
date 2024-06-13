#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstdlib>
#include "wiringPi.h"
//#include "headlines.h"



using namespace std;

class Encoder
{
private:
    volatile int encoderPos;//=160;
    volatile int encoderPosreturned;//=encoderPosCW/4;
    volatile int encoded;
    int lastEncoded=0;
    const int pinCLK;//=6;
    const int pinDT;//=5;
    const int pinSW;//=4; //pin momentSwitch w encoderze
    bool interruptFlag;//=false;
    std::string tempValue;// zmienna zapisywana do pliku
    
    static Encoder *instance; //wskaźnik na instancję (obiekt) klasy
    static Encoder *instance1; //wskaźnik na instancję (obiekt) klasy



public:

// Konstruktor ustawiający konfigurację pinów i wartości początkowe zmiennych
    Encoder(int pinCLK,int pinDT, int pinSW):pinCLK(pinCLK),pinDT(pinDT), pinSW(pinSW)
    {
        encoderPos=160;
        encoderPosreturned=encoderPos/4;
        lastEncoded=0;
        interruptFlag=false;

    pinMode(pinCLK,INPUT);
    pinMode(pinDT,INPUT);
    pinMode(pinSW,INPUT);

    pullUpDnControl(pinCLK, PUD_DOWN);
    pullUpDnControl(pinDT, PUD_DOWN);
    pullUpDnControl(pinSW, PUD_UP);
   
    }
    
// funkcja obsługująca przerwanie zliczanie z encodera    
void readEncoder() 
{
    int MSB=digitalRead(pinCLK); //najbardziej znaczący bit
    int LSB=digitalRead(pinDT); //najmniej znaczący bit

    int encodedEN1=(MSB<<1)|LSB; //kombinacja dwóch bitóœ do jednej liczby
    int sum=(lastEncoded<<2)|encodedEN1; //kombinacja poprzedniego stanu z aktualnym

    if(sum==0b1101|| sum==0b0100|| sum==0b0010|| sum==0b1011)encoderPos++;
    if(sum==0b1110|| sum==0b0111|| sum==0b0001|| sum==0b1000)encoderPos--;

    lastEncoded=encodedEN1; //zapisz stan aktualny jako poprzedni

    //ograniczenie wartości do przedziału 30-60
    if(encoderPos<120) encoderPos=120;
    if(encoderPos>240) encoderPos=240;
    encoderPosreturned=encoderPos/4; //tutaj jest to ograniczenie ponieważ encoder liczy co 4

}

// Metoda zapisująca do pliku wartość po naciśnięiu przycisku SW
void writeForFile(std::string path)
{
    int SW=digitalRead(pinSW);
    delay(100);
    if(SW==0)
    {
    tempValue=std::to_string(encoderPosreturned);//zamiana flout-a na string
    //zapis do pliku
    std::ofstream outputFile(path);
    if(outputFile.is_open())
    {
        outputFile<<tempValue;
        outputFile.close();
    }else
        {
            cerr<<"Open file fauld"<<endl;
        }
    }

}
//++++++++++++++++++++++  Metody do debugowania   ++++++++++++++++++++++++++++++++++++++++++++++++++

void showSW()
{
    int SW=digitalRead(pinSW);
    delay(100);
    if(SW==0)cout<<"Przycisk SW wciśnięty"<<endl;
    delay(500);
}

void showEN() //funkcja pokazująca wartość encodera
    {
        cout<<"EN= "<<encoderPosreturned<<endl;

    }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//_________________   Wszystkie metody i wskaźniki dotyczące obsługi wskaźnika przerwań  __________________________
   

    static void interruptHandlerWraper() //statyczna funkcja wywołująca metodę przerwania
    {
        instance->readEncoder();
        instance1->readEncoder();
    }

    static void interruptHandlerWraperWrite() //statyczna funkcja wywołująca metodę przerwania
    {
        instance->writeForFile("tempDataCO.txt");
        instance1->writeForFile("tempDataCW.txt");
    }

    static void setInstance(Encoder *inst, Encoder *inst1) // instancja klasy służaca do przechowywania wskaźnika na instancję klasy
    {
        instance=inst;
        instance1=inst1;
    }
//_______________________________________________________________________________________________________

};

// Wskaźniki globalne do przekazywania przerwań do instancji
Encoder* Encoder::instance=nullptr; // !!! To się musi znaleść w głównej pętli programu  !!!!!!!
Encoder* Encoder::instance1=nullptr; // !!! To się musi znaleść w głównej pętli programu  !!!!!!!



int main()
{
    const int pinEN1_CLK=28;
     const int pinEN1_DT=27;
      const int pinEN1_SW=26;

       const int pinEN2_CLK=6;
     const int pinEN2_DT=5;
      const int pinEN2_SW=4;

    if(wiringPiSetup()==-1) // wywołanie funkcji wiringPi
        {
            cerr<<"Initailing wirinPi failed"<<endl;
        }
     Encoder EN1(pinEN1_CLK,pinEN1_DT,pinEN1_SW);
    

    Encoder EN2(pinEN2_CLK,pinEN2_DT,pinEN2_SW);
    Encoder::setInstance(&EN1, &EN2); //ustawienie instancji

    wiringPiISR(pinEN1_CLK, INT_EDGE_BOTH, &Encoder::interruptHandlerWraper);
    wiringPiISR(pinEN1_DT, INT_EDGE_BOTH, &Encoder::interruptHandlerWraper);
   wiringPiISR(pinEN1_SW, INT_EDGE_FALLING, &Encoder::interruptHandlerWraperWrite);

   wiringPiISR(pinEN2_CLK, INT_EDGE_BOTH, &Encoder::interruptHandlerWraper);
    wiringPiISR(pinEN2_DT, INT_EDGE_BOTH, &Encoder::interruptHandlerWraper);
   wiringPiISR(pinEN2_SW, INT_EDGE_FALLING, &Encoder::interruptHandlerWraperWrite);


    while(true)
        {
            system("clear");
            
            EN1.showEN();
            EN2.showEN();
            delay(500);
            
        }

    return 0;
}
