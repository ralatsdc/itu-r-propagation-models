#include <stdio.h>
#include <math.h>
#include <string.h>

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

int main( int argc, char *argv[] )  {

    if( ! strcmp(argv[1], "nwet")) {
        double lat, lon;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)

        double result = NWET(lat, lon);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "rain_height")) {
        double lat, lon;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)

        double result = rain_height(lat,lon);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "temperature")) {
        double lat, lon;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)

        double result = temperature(lat, lon);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "rain_intensity")) {
        double lat, lon, p;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)
        sscanf(argv[4],"%lf",&p); // Percentage of the time

        double result = rain_intensity(lat, lon, p);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "rain_probability")) {
        double lat, lon;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)

        double result = rain_probability(lat, lon);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "lwcc")) {
        double lat, lon, p;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)
        sscanf(argv[4],"%lf",&p); // Percentage of the time

        double result = LWCC(lat, lon, p);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "iwvc")) {
        double lat, lon, p;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)
        sscanf(argv[4],"%lf",&p); // Percentage of the time

        double result = IWVC(lat, lon, p);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "swvd")) {
        double lat, lon;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)

        double result = SWVD(lat, lon);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "gaseous_attenuation")) {
        double f1, E, lat, lon;

        sscanf(argv[2],"%lf",&f1); // Link frequency (GHz)
        sscanf(argv[3],"%lf",&E); // Link elevation angle (�)
        sscanf(argv[4],"%lf",&lat); // Latitude (�)
        sscanf(argv[5],"%lf",&lon); // Logitude (�)

        double Temp = temperature(lat,lon);
        double ro = SWVD(lat,lon);
        double result = gaseous_attenuation(f1, E, Temp, ro);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "gaseous_attenuation_exc")) {
        double f1, E, lat, lon, p;

        sscanf(argv[2],"%lf",&f1); // Link frequency (GHz)
        sscanf(argv[3],"%lf",&E); // Link elevation angle (�)
        sscanf(argv[4],"%lf",&lat); // Latitude (�)
        sscanf(argv[5],"%lf",&lon); // Logitude (�)
        sscanf(argv[6],"%lf",&p); // Percentage of the time

        double Temp = temperature(lat,lon);
        double WVC = IWVC(lat,lon,p);
        double result = gaseous_attenuation_exc(f1, E, Temp, WVC);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "cloud_attenuation")) {
        double f1, E, lat, lon, p;

        sscanf(argv[2],"%lf",&f1); // Link frequency (GHz)
        sscanf(argv[3],"%lf",&E); // Link elevation angle (�)
        sscanf(argv[4],"%lf",&lat); // Latitude (�)
        sscanf(argv[5],"%lf",&lon); // Logitude (�)
        sscanf(argv[6],"%lf",&p); // Percentage of the time

        double LWC = LWCC(lat,lon,p);
        double result = cloud_attenuation(f1, E, LWC);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "rain_attenuation")) {
        double f1, E, lat, lon, p, hs, to;

        sscanf(argv[2],"%lf",&f1); // Link frequency (GHz)
        sscanf(argv[3],"%lf",&E); // Link elevation angle (�)
        sscanf(argv[4],"%lf",&lat); // Latitude (�)
        sscanf(argv[5],"%lf",&lon); // logitude (�)
        sscanf(argv[6],"%lf",&p); // Percentage of the time
        sscanf(argv[7],"%lf",&hs); // logitude (�)
        sscanf(argv[8],"%lf",&to); // Percentage of the time

        double hr = rain_height(lat,lon);
        double R001 = rain_intensity(lat,lon,0.01);
        double result = rain_attenuation(lat,f1,E,p,hs,hr,R001,to);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "scintillation")) {
        double f1, E, lat, lon, p, hs, eta, D;

        sscanf(argv[2],"%lf",&f1); // Link frequency (GHz)
        sscanf(argv[3],"%lf",&E); // Link elevation angle (�)
        sscanf(argv[4],"%lf",&lat); // Latitude (�)
        sscanf(argv[5],"%lf",&lon); // logitude (�)
        sscanf(argv[6],"%lf",&p); // Percentage of the time
        sscanf(argv[7],"%lf",&hs); // logitude (�)
        sscanf(argv[8],"%lf",&eta); // logitude (�)
        sscanf(argv[9],"%lf",&D); // Percentage of the time

        double Nwet = NWET(lat,lon);
        double result = scintillation(Nwet,f1,E,p,hs,eta,D);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "xpd")) {
        double f1, E, lat, lon, p, hs, to;

        sscanf(argv[2],"%lf",&f1); // Link frequency (GHz)
        sscanf(argv[3],"%lf",&E); // Link elevation angle (�)
        sscanf(argv[4],"%lf",&lat); // Latitude (�)
        sscanf(argv[5],"%lf",&lon); // logitude (�)
        sscanf(argv[6],"%lf",&p); // Percentage of the time
        sscanf(argv[7],"%lf",&hs); // Earth station altitude (km)
        sscanf(argv[8],"%lf",&to); // Tilt polarization angle (�)

        double hr = rain_height(lat,lon);
        double R001 = rain_intensity(lat,lon,0.01);
        double Arain = rain_attenuation(lat,f1,E,p,hs,hr,R001,to);
        double result = XPD(Arain,to,f1,E,p);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "noise_temperature")) {
        double f1, E, lat, lon, p, hs, to, eta, D;

        sscanf(argv[2],"%lf",&f1); // Link frequency (GHz)
        sscanf(argv[3],"%lf",&E); // Link elevation angle (�)
        sscanf(argv[4],"%lf",&lat); // Latitude (�)
        sscanf(argv[5],"%lf",&lon); // logitude (�)
        sscanf(argv[6],"%lf",&p); // Percentage of the time
        sscanf(argv[7],"%lf",&hs); // logitude (�)
        sscanf(argv[8],"%lf",&to); // Percentage of the time
        sscanf(argv[7],"%lf",&eta); // logitude (�)
        sscanf(argv[8],"%lf",&D); // Percentage of the time

        double Temp = temperature(lat,lon);
        double hr = rain_height(lat,lon);
        double R001 = rain_intensity(lat,lon,0.01);
        double Nwet = NWET(lat,lon);
        double WVC = IWVC(lat,lon,p);
        double LWC = LWCC(lat,lon,p);

        double Agaseous_exc = gaseous_attenuation_exc(f1,E,Temp,WVC);
        double Arain = rain_attenuation(lat,f1,E,p,hs,hr,R001,to);
        double Aclouds = cloud_attenuation(f1,E,LWC);
        double Iscint = scintillation(Nwet,f1,E,p,hs,eta,D);

        // TOTAL ATTENUATION
        double Atotal = Agaseous_exc + sqrt((Arain+ Aclouds)*(Arain+ Aclouds) + Iscint*Iscint);
        // SKY NOISE TEMPERATURE FOR A GIVEN TOTAL ATTENUATION
        double MeanRTemp = TMR(Temp);
        double result = noise_temperature (Atotal,MeanRTemp);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "tmr")) {
        double lat, lon;

        sscanf(argv[2],"%lf",&lat); // Latitude (�)
        sscanf(argv[3],"%lf",&lon); // Logitude (�)

        double Temp = temperature(lat,lon);

        double result = TMR(Temp);
        printf("%lf\n", result);
    }
    else if( ! strcmp(argv[1], "efsr")) {
        double f1, E, lat, lon, p, hs, to, f2;

        sscanf(argv[2],"%lf",&f1); // Link frequency (GHz)
        sscanf(argv[3],"%lf",&E); // Link elevation angle (�)
        sscanf(argv[4],"%lf",&lat); // Latitude (�)
        sscanf(argv[5],"%lf",&lon); // logitude (�)
        sscanf(argv[6],"%lf",&p); // Percentage of the time
        sscanf(argv[7],"%lf",&hs); // logitude (�)
        sscanf(argv[8],"%lf",&to); // Percentage of the time
        sscanf(argv[9],"%lf",&f2); // Percentage of the time

        double hr = rain_height(lat,lon);
        double R001 = rain_intensity(lat,lon,0.01);

        double Arain = rain_attenuation(lat,f1,E,p,hs,hr,R001,to);

        double result = EFSR(f1, f2, Arain);
        printf("%lf\n", result);
    }
    else {
        printf("need arg.\n");
    }
}