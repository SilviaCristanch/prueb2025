#include "astrologia.h"
#include <cmath>
#include <iomanip>
#include <stdexcept>

// Implementación de DateTime
DateTime::DateTime(int y, int m, int d, double h, int tz) 
    : year(y), month(m), day(d), hours(h), timezone(tz) {}

double DateTime::toUTC() const { return hours - timezone; }
int DateTime::getYear() const { return year; }
int DateTime::getMonth() const { return month; }
int DateTime::getDay() const { return day; }
double DateTime::getHours() const { return hours; }

// Funciones matemáticas básicas
double degrees(double rad) { return rad * (180.0 / PI); }
double radians(double deg) { return deg * (PI / 180.0); }

double normalize_degrees(double angle) {
    angle = fmod(angle, 360.0);
    return angle < 0 ? angle + 360.0 : angle;
}

// Calcula el Día Juliano (JD) - Corregido
double julian_date(const DateTime& dt) {
    int a = (14 - dt.getMonth()) / 12;
    int y = dt.getYear() + 4800 - a;
    int m = dt.getMonth() + 12 * a - 3;
    
    int jdn = dt.getDay() + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return jdn + (dt.toUTC() - 12.0) / 24.0;
}

// Tiempo Sidéreo en Greenwich (TSG) - Corregido
double greenwich_sidereal_time(double jd) {
    double T = (jd - 2451545.0) / 36525.0;
    double TSG = 280.46061837 + 360.98564736629 * (jd - 2451545.0) 
                 + 0.000387933 * T * T - T * T * T / 38710000.0;
    return normalize_degrees(TSG);
}

// Obtener nombres de signos zodiacales
std::string obtener_nombre_signo(int indice) {
    const std::string signs[] = {
        "Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo",
        "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius", "Pisces"
    };
    return signs[indice % 12];
}

// Información del zodíaco basada en longitud eclíptica
ZodiacInfo get_zodiac_info(double ecliptic_longitude) {
    ecliptic_longitude = normalize_degrees(ecliptic_longitude);
    int sign_index = static_cast<int>(ecliptic_longitude / 30.0);
    return {ecliptic_longitude, obtener_nombre_signo(sign_index)};
}

// Cálculo de casas astrológicas (método simplificado pero funcional)
void calcular_casas(double TSG, double latitud, double longitud, 
                    std::vector<Casa>& casas, std::string& ascendente) {
    // Tiempo Sidéreo Local
    double TSL = normalize_degrees(TSG - longitud);  // Nota: signo negativo para longitud oeste
    casas.clear();

    for (int i = 1; i <= 12; ++i) {
        // Cálculo básico de cúspides (30° por casa)
        double cuspide = normalize_degrees(TSL + (i - 1) * 30.0);
        
        // Aplicar corrección simplificada por latitud para las casas principales
        if (i == 1 || i == 4 || i == 7 || i == 10) {
            // Corrección básica por latitud (simplificada)
            double correction = sin(radians(latitud)) * 5.0; // Máximo 5° de corrección
            cuspide = normalize_degrees(cuspide + correction);
        }
        
        int sign_idx = static_cast<int>(cuspide / 30.0);
        std::string signo = obtener_nombre_signo(sign_idx);
        
        casas.push_back({i, cuspide, signo});

        // Casa 1 = Ascendente
        if (i == 1) ascendente = signo;
    }
}

// Calcular ascendente (signo que se levanta en el horizonte)
std::string calcular_ascendente(const DateTime& dt, double lat, double lon) {
    double jd = julian_date(dt);
    double TSG = greenwich_sidereal_time(jd);
    
    std::vector<Casa> casas;
    std::string ascendente;
    calcular_casas(TSG, lat, lon, casas, ascendente);
    
    return ascendente;
}

// Calcular signo solar (donde está el Sol) - NUEVA FUNCIÓN
std::string calcular_signo_solar(const DateTime& dt) {
    double jd = julian_date(dt);
    double T = (jd - 2451545.0) / 36525.0;
    
    // Longitud media del Sol (fórmula mejorada)
    double L0 = 280.46646 + 36000.76983 * T + 0.0003032 * T * T;
    
    // Anomalía media del Sol
    double M = 357.52911 + 35999.05029 * T - 0.0001537 * T * T;
    M = radians(M);
    
    // Ecuación del centro (corrección principal)
    double C = (1.914602 - 0.004817 * T - 0.000014 * T * T) * sin(M) +
               (0.019993 - 0.000101 * T) * sin(2 * M) +
               0.000289 * sin(3 * M);
    
    // Longitud verdadera del Sol
    double sun_lon = normalize_degrees(L0 + C);
    
    ZodiacInfo info = get_zodiac_info(sun_lon);
    return info.sign_name;
}

// Cálculo de posiciones planetarias (simplificado pero mejorado)
void calcular_posicion_planetas(double jd, std::vector<CelestialBody>& planetas) {
    double T = (jd - 2451545.0) / 36525.0;

    // Sol (longitud eclíptica geocéntrica) - usando la misma fórmula que calcular_signo_solar
    double L0 = 280.46646 + 36000.76983 * T + 0.0003032 * T * T;
    double M = 357.52911 + 35999.05029 * T - 0.0001537 * T * T;
    M = radians(M);
    double C = (1.914602 - 0.004817 * T - 0.000014 * T * T) * sin(M) +
               (0.019993 - 0.000101 * T) * sin(2 * M) +
               0.000289 * sin(3 * M);
    double sun_lon = normalize_degrees(L0 + C);

    // Luna (aproximación mejorada)
    double moon_L = 218.3164477 + 481267.88123421 * T - 0.0015786 * T * T;
    double moon_D = 297.8501921 + 445267.1114034 * T - 0.0018819 * T * T;
    double moon_M = 134.9633964 + 477198.8675055 * T + 0.0087414 * T * T;
    double moon_F = 93.2720950 + 483202.0175233 * T - 0.0036539 * T * T;
    
    // Correcciones principales para la Luna
    double moon_correction = 6.288774 * sin(radians(moon_M)) +
                           1.274027 * sin(radians(2 * moon_D - moon_M)) +
                           0.658314 * sin(radians(2 * moon_D));
    
    double moon_lon = normalize_degrees(moon_L + moon_correction);

    planetas.clear();
    planetas.push_back({"Sol", sun_lon, 0.0, 1.0});
    planetas.push_back({"Luna", moon_lon, 0.0, 60.2666});
    
    // Planetas adicionales (muy simplificados)
    double mercury_lon = normalize_degrees(252.25 + 149472.67 * T);
    double venus_lon = normalize_degrees(181.98 + 58517.82 * T);
    double mars_lon = normalize_degrees(355.43 + 19140.30 * T);
    double jupiter_lon = normalize_degrees(34.35 + 3034.74 * T);
    double saturn_lon = normalize_degrees(50.08 + 1222.11 * T);
    
    planetas.push_back({"Mercurio", mercury_lon, 0.0, 0.39});
    planetas.push_back({"Venus", venus_lon, 0.0, 0.72});
    planetas.push_back({"Marte", mars_lon, 0.0, 1.52});
    planetas.push_back({"Júpiter", jupiter_lon, 0.0, 5.20});
    planetas.push_back({"Saturno", saturn_lon, 0.0, 9.58});
}

// Funciones de validación
bool validar_fecha(int year, int month, int day) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (year < 1900 || year > 2100) return false;
    
    // Validación básica de días por mes
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Año bisiesto
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        days_in_month[1] = 29;
    }
    
    return day <= days_in_month[month - 1];
}

bool validar_coordenadas(double lat, double lon) {
    return (lat >= -90.0 && lat <= 90.0 && lon >= -180.0 && lon <= 180.0);
}