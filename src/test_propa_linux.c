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
extern double XPD(double A_rain, double to,double f, double elev, double p);
extern double noise_temperature(double A_total, double Tmr);
extern double TMR(double Ts);
extern double EFSR(double f1, double f2, double A1);

int main(void)
{
double lat, lon, f1, p, E, hs, to, eta, D, f2;
  double Temp, ro, WVC, LWC,  hr, R001, Nwet, XPOL, NoiseTemp, MeanRTemp;
  double Agaseous, Agaseous_exc, Aclouds, Arain, Arain2, Iscint, Atotal;


  lat = 46.217;		// Latitude (�)
  lon = 6.12;		// Logitude (�)

  hs = 0.8140;			// Earth station altitude (km)
  E = 33.0*M_PI/180;	// Link elevation angle (�)

  f1= 12.0;			// Link frequency (GHz)
  f2 = 30; 			// Second link frequency f2 > f1 (for Frequency scaling) (GHz) 
  to = 45.0;		// Tilt polarization angle (�)

  D = 1.0;			// Earth station antenna diameter (m)
  eta = 0.5;		// Earth station antenna efficiency

  p = 1;			// Percentage of the time

  // Intermediate parameters computation
  hr = rain_height(lat,lon);
  R001 = rain_intensity(lat,lon,0.01);
  Temp = temperature(lat,lon);
  ro = SWVD(lat,lon);
  if (p>=1) {
	WVC = IWVC(lat,lon,p);
	LWC = LWCC(lat,lon,p);
  }
  else {
	WVC= IWVC(lat,lon,1);
    LWC = LWCC(lat,lon,1);
  }
  Nwet = NWET(lat,lon);


printf("\n==========================\n" ); 
  printf("Link frequency %.2lf GHz \n", f1); 
  printf("==========================\n" ); 
  
  // GASEOUS ATTENUATION
  Agaseous = gaseous_attenuation(f1,E,Temp,ro);
  printf("\nGaseous attenuation = %.2lf dB\n",Agaseous);

  // GASEOUS ATTENUATION EXCEEDED FOR p% OF THE TIME
  Agaseous_exc = gaseous_attenuation_exc(f1,E,Temp,WVC);
  printf("\nGaseous attenuation exceeded for %.2lf %% of the time = %.2lf dB\n",p,Agaseous_exc);

  // CLOUD ATTENUATION EXCEEDED FOR p% OF THE TIME
  Aclouds = cloud_attenuation(f1,E,LWC);
  printf("\nClouds attenuation exceeded for %.2lf %% of the time = %.2lf dB\n",p,Aclouds);

  // IMPAIRMENT DUE TO SCINTILLATION EXCEEDED FOR p% OF THE TIME
  Iscint = scintillation(Nwet,f1,E,p,hs,eta,D);
  printf("\nScintillation impairment exceeded for %.2lf %% of the time = %.2lf dB\n",p,Iscint);

  // RAIN ATTENUATION EXCEEDED FOR p% OF THE TIME
  Arain = rain_attenuation(lat,f1,E,p,hs,hr,R001,to);
  printf("\nRain attenuation exceeded for %.2lf %% of the time = %.2lf dB\n",p,Arain);
  
  // TOTAL ATTENUATION 
  Atotal = Agaseous_exc + sqrt((Arain+ Aclouds)*(Arain+ Aclouds) + Iscint*Iscint); 
  printf("\nTotal attenuation exceeded for %.2lf %% of the time = %.2lf dB\n", p, Atotal);
  
  // SKY NOISE TEMPERATURE FOR A GIVEN TOTAL ATTENUATION 
  MeanRTemp = TMR(Temp); 
  NoiseTemp =noise_temperature (Atotal,MeanRTemp); 
  printf("\nSky noise temperature for the given total attenuation %.2lf dB = %.2lf K\n", Atotal, NoiseTemp);
  
  // CROSS POLAR DISCRIMINATION EXCEEDED FOR p% OF THE TIME 
  XPOL = XPD(Arain,to,f1,E,p);
  printf("\nCross polar discrimination exceeded for %.2lf %% of the time = %.2lf dB\n", p, XPOL);
  
  printf("\n====================================\n" ); 
  printf("Link frequency scaling to %.2lf GHz \n", f2); 
  printf("====================================\n" ); 
  // RAIN ATTENUATION ON FREQ 2 FROM FREQ 1 (using frequency scaling) 
  Arain2 = EFSR(f1, f2, Arain); 
  printf("\nRain attenuation exceeded on freq. %.2lf GHZ based on freq. %.2lf GHZ = %.2lf dB\n",f2, f1, Arain2);



return 1;

}
