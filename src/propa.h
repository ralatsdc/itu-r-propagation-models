#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern double NWET(double lat, double lon);
extern double rain_height(double lat, double lon);
extern double temperature(double lat,double lon);
extern double rain_intensity(double lat, double lon, double p);
extern double rain_probability(double lat, double lon);
extern double LWCC(double lat, double lon, double p);
extern double IWVC(double lat, double lon, double p) ;
extern double SWVD(double lat, double lon);
extern double gaseous_attenuation(double f,double E,double Temp, double ro);
extern double gaseous_attenuation_exc(double f,double E,double Temp, double WVC);
extern double cloud_attenuation(double f,double E,double L);
extern double rain_attenuation(double lat,double f,double E,double p,double hs,double hr,double R001, double to);
extern double scintillation(double Nwet, double f,double E,double p,double hs,double eta, double D);
extern double EFSR(double f1, double f2, double A1);
extern double XPD(double A_rain, double tilt_deg,double f, double elev_deg, double p);
extern double noise_temperature(double A_total, double Tmr);
extern double TMR(double Ts);

