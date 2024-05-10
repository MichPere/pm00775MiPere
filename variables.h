#include <iostream>

using namespace std;

#ifndef variable
#define variable
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

 





#endif