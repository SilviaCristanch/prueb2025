#ifndef ASTROLOGIA_H
#define ASTROLOGIA_H

#include <string>
#include <vector>

// Constantes astronómicas
const double PI = 3.14159265358979323846;
const double OBLIQUITY_J2000 = 23.43928;
const double SECS_PER_HOUR = 3600.0;

// Estructuras de datos
struct CelestialBody {
    std::string name;
    double longitude;
    double latitude;
    double distance;
};

struct Casa {
    int numero;
    double longitude;
    std::string signo;
};

struct ZodiacInfo {
    double longitude;
    std::string sign_name;
};

class DateTime {
private:
    int year, month, day;
    double hours;
    int timezone;

public:
    DateTime(int y, int m, int d, double h, int tz);
    double toUTC() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    double getHours() const;
};

// Funciones astronómicas básicas
double degrees(double rad);
double radians(double deg);
double normalize_degrees(double angle);
double julian_date(const DateTime& dt);
double greenwich_sidereal_time(double jd);

// Funciones de zodíaco y casas
ZodiacInfo get_zodiac_info(double ecliptic_longitude);
void calcular_casas(double TSG, double latitud, double longitud, 
                   std::vector<Casa>& casas, std::string& ascendente);
std::string calcular_ascendente(const DateTime& dt, double lat, double lon);
std::string calcular_signo_solar(const DateTime& dt);

// Funciones planetarias
void calcular_posicion_planetas(double jd, std::vector<CelestialBody>& planetas);

// Funciones auxiliares
std::string obtener_nombre_signo(int indice);
bool validar_fecha(int year, int month, int day);
bool validar_coordenadas(double lat, double lon);

#endif