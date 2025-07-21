
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cmath>
#include <iomanip>
#include "astrologia.h"
#include "analisis_ascendente.h"

using namespace std;

// -----------------------------
// Frases motivacionales por signo
// -----------------------------
map<string, string> frases_por_signo = {
    {"Aries", "La energia que tienes rompe cualquier limite."},
    {"Taurus", "Tu constancia construye futuros solidos."},
    {"Gemini", "Tu curiosidad te lleva por caminos fascinantes."},
    {"Cancer", "Tu sensibilidad es tu mayor fuerza."},
    {"Leo", "Naciste para brillar, no lo olvides."},
    {"Virgo", "El orden que traes al mundo es vital."},
    {"Libra", "Tu equilibrio inspira a otros."},
    {"Scorpio", "Tu intensidad transforma realidades."},
    {"Sagittarius", "Tu espiritu libre ilumina nuevos caminos."},
    {"Capricorn", "Tu disciplina logra lo imposible."},
    {"Aquarius", "Tu originalidad cambia el mundo."},
    {"Pisces", "Sueñas con fuerza y eso te hace imparable."}
};

// -----------------------------
// Funciones de esperanza de vida
// -----------------------------
void contar_vida_restante(int anios) {
    for (int i = anios; i >= 0; --i) {
        cout << "[Te quedan: " << i << " años...]" << endl;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    cout << "[Disfruta cada instante]" << endl;
}

int calcular_esperanza_vida(string sexo) {
    transform(sexo.begin(), sexo.end(), sexo.begin(), ::tolower);
    if (sexo[0] == 'h') return 75;
    if (sexo[0] == 'm') return 81;
    return 78; // Valor por defecto
}

// -----------------------------
// Funciones de gráficos
// -----------------------------
void mostrar_grafico_barras(int edad_actual, int esperanza_total) {
    cout << "\nGrafico de barras (simulado):\n";
    for (int edad = 0; edad <= 100; edad += 5) {
        int vida_restante = max(esperanza_total - edad, 0);
        cout << "Edad " << setw(2) << edad << ": ";
        for (int i = 0; i < vida_restante / 2; ++i) cout << "█";
        if (edad == (edad_actual / 5) * 5) cout << " <-- Cerca de tu edad";
        cout << endl;
    }
}

void mostrar_grafico_pastel(int edad, int restante) {
    int total = edad + restante;
    double por_vivida = (double)edad / total * 100;
    double por_restante = 100 - por_vivida;

    cout << "\nGrafico de pastel (simulado):\n";
    cout << "Años vividos        : " << fixed << setprecision(1) << por_vivida << "%\n";
    cout << "Esperanza restante  : " << fixed << setprecision(1) << por_restante << "%\n";
}

// -----------------------------
// Funciones auxiliares
// -----------------------------
double obtener_hora_nacimiento() {
    int hora, minuto;
    cout << "Hora de nacimiento (0-23): ";
    cin >> hora;
    cout << "Minutos de nacimiento (0-59): ";
    cin >> minuto;
    
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        cout << "Hora invalida, usando 12:00 por defecto.\n";
        return 12.0;
    }
    
    return hora + minuto / 60.0;
}

void obtener_coordenadas(double& lat, double& lon) {
    cout << "¿Conoces las coordenadas de tu lugar de nacimiento? (s/n): ";
    char respuesta;
    cin >> respuesta;
    
    if (respuesta == 's' || respuesta == 'S') {
        cout << "Latitud (ej: 4.6097 para Bogotá): ";
        cin >> lat;
        cout << "Longitud (ej: -74.0817 para Bogotá): ";
        cin >> lon;
        
        if (!validar_coordenadas(lat, lon)) {
            cout << "Coordenadas inválidas, usando Bogotá por defecto.\n";
            lat = 4.6097;
            lon = -74.0817;
        }
    } else {
        cout << "Usando coordenadas de Bogotá por defecto.\n";
        lat = 4.6097;
        lon = -74.0817;
    }
}

// -----------------------------
// Funciones de resultados astrológicos (modificada)
// -----------------------------
void mostrar_resultados_astrologicos(const DateTime& dt, double lat, double lon) {
    try {
        // 1. Convertir a UTC y calcular JD
        double jd = julian_date(dt);

        // 2. Calcular Tiempo Sidéreo en Greenwich
        double TSG = greenwich_sidereal_time(jd);

        // 3. Calcular casas y ascendente
        vector<Casa> casas;
        string ascendente;
        calcular_casas(TSG, lat, lon, casas, ascendente);

        // 4. Calcular posiciones planetarias
        vector<CelestialBody> planetas;
        calcular_posicion_planetas(jd, planetas);

        // Mostrar resultados
        cout << "\n=== CARTA ASTRAL COMPLETA ===\n";
        cout << "Fecha: " << dt.getYear() << "-" << setfill('0') << setw(2) << dt.getMonth() 
             << "-" << setw(2) << dt.getDay() << " " << fixed << setprecision(2) 
             << dt.getHours() << " horas (UTC" << (dt.toUTC() >= 0 ? "+" : "") << dt.toUTC() << ")\n";
        cout << "Ubicación: Lat " << fixed << setprecision(4) << lat << "°, Lon " << lon << "°\n";
        cout << "Día Juliano: " << fixed << setprecision(2) << jd << "\n";
        
        cout << "\n--- SIGNOS PRINCIPALES ---\n";
        cout << "ASCENDENTE: " << ascendente << " (como te ven los demás)\n";
        
        // Mostrar signo solar
        string signo_solar = calcular_signo_solar(dt);
        cout << "SIGNO SOLAR: " << signo_solar << " (tu esencia)\n";

        // Mostrar análisis detallado del ascendente
        mostrar_analisis_ascendente(ascendente);

        cout << "\n--- CÚSPIDES DE CASAS ---\n";
        for (const auto& casa : casas) {
            cout << "Casa " << setw(2) << casa.numero << ": " 
                 << setw(12) << casa.signo << " (" 
                 << fixed << setprecision(2) << casa.longitude << "°)\n";
        }

        cout << "\n--- POSICIONES PLANETARIAS ---\n";
        for (const auto& body : planetas) {
            ZodiacInfo info = get_zodiac_info(body.longitude);
            double grado_en_signo = fmod(body.longitude, 30.0);
            cout << setw(10) << body.name << ": " << setw(12) << info.sign_name << " " << fixed << setprecision(2) << grado_en_signo << "°\n";
        }
        
    } catch (const exception& e) {
        cout << "Error calculando carta astral: " << e.what() << endl;
    }
}

// -----------------------------
// Funciones de menú y ejecución (modificada)
// -----------------------------
void mostrar_menu() {
    cout << "\n===============================================\n";
    cout << "  SISTEMA INTEGRADO DE ASTROLOGÍA Y VIDA\n";
    cout << "===============================================\n";
    cout << "1. Calcular esperanza de vida y carta astral\n";
    cout << "2. Solo carta astral\n";
    cout << "3. Solo esperanza de vida\n";
    cout << "4. Análisis detallado del ascendente\n";
    cout << "5. Salir\n";
    cout << "===============================================\n";
}

void procesar_opcion_completa() {
    try {
        int dia, mes, anio;
        string sexo;
        
        cout << "\n--- DATOS DE NACIMIENTO ---\n";
        cout << "Día de nacimiento (1-31): ";
        cin >> dia;
        cout << "Mes de nacimiento (1-12): ";
        cin >> mes;
        cout << "Año de nacimiento (ej: 1995): ";
        cin >> anio;
        
        if (!validar_fecha(anio, mes, dia)) {
            cout << "Fecha inválida. Intenta nuevamente.\n";
            return;
        }
        
        cout << "Sexo (Hombre/Mujer): ";
        cin >> sexo;

        // Obtener hora de nacimiento
        double hora_nacimiento = obtener_hora_nacimiento();
        
        // Obtener coordenadas
        double lat, lon;
        obtener_coordenadas(lat, lon);

        // Calcular edad actual
        time_t t = time(0);
        tm* now = localtime(&t);
        int current_year = now->tm_year + 1900;
        int edad = current_year - anio;

        // Calcular esperanza de vida
        int esperanza = calcular_esperanza_vida(sexo);
        int restante = max(esperanza - edad, 0);
        
        // Crear objeto DateTime
        int tz = -5; // Huso horario de Colombia
        DateTime dt(anio, mes, dia, hora_nacimiento, tz);

        // Obtener signos
        string signo_solar = calcular_signo_solar(dt);
        string ascendente = calcular_ascendente(dt, lat, lon);
        string frase = frases_por_signo.count(signo_solar) ? 
                      frases_por_signo[signo_solar] : 
                      "Tu signo es único y especial.";

        // Mostrar resultados de vida
        cout << "\n=== RESULTADOS DE ESPERANZA DE VIDA ===\n";
        cout << "Edad actual: " << edad << " años\n";
        cout << "Signo zodiacal (Sol): " << signo_solar << "\n";
        cout << "Ascendente: " << ascendente << "\n";
        cout << "Esperanza de vida total: " << esperanza << " años\n";
        cout << "Vida restante estimada: " << restante << " años\n";
        cout << "Frase motivacional: " << frase << "\n";

        // Animación de cuenta regresiva
        cout << "\nContando tu vida restante...\n";
        contar_vida_restante(min(restante, 5)); // Máximo 5 para no ser muy lenta

        // Mostrar gráficos
        mostrar_grafico_barras(edad, esperanza);
        mostrar_grafico_pastel(edad, restante);

        // Mostrar información astrológica completa
        mostrar_resultados_astrologicos(dt, lat, lon);

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    } catch (...) {
        cout << "Error: entrada inválida.\n";
    }
}

void procesar_solo_astrologia() {
    try {
        int dia, mes, anio;
        
        cout << "\n--- DATOS PARA CARTA ASTRAL ---\n";
        cout << "Día de nacimiento (1-31): ";
        cin >> dia;
        cout << "Mes de nacimiento (1-12): ";
        cin >> mes;
        cout << "Año de nacimiento (ej: 1995): ";
        cin >> anio;
        
        if (!validar_fecha(anio, mes, dia)) {
            cout << "Fecha inválida. Intenta nuevamente.\n";
            return;
        }
        
        double hora_nacimiento = obtener_hora_nacimiento();
        
        double lat, lon;
        obtener_coordenadas(lat, lon);
        
        int tz = -5;
        DateTime dt(anio, mes, dia, hora_nacimiento, tz);
        
        mostrar_resultados_astrologicos(dt, lat, lon);
        
    } catch (...) {
        cout << "Error procesando datos astrológicos.\n";
    }
}

void procesar_solo_esperanza() {
    try {
        int anio;
        string sexo;
        
        cout << "\n--- CÁLCULO DE ESPERANZA DE VIDA ---\n";
        cout << "Año de nacimiento: ";
        cin >> anio;
        cout << "Sexo (Hombre/Mujer): ";
        cin >> sexo;
        
        time_t t = time(0);
        tm* now = localtime(&t);
        int current_year = now->tm_year + 1900;
        int edad = current_year - anio;
        
        int esperanza = calcular_esperanza_vida(sexo);
        int restante = max(esperanza - edad, 0);
        
        cout << "\nEdad actual: " << edad << " años\n";
        cout << "Esperanza de vida total: " << esperanza << " años\n";
        cout << "Vida restante estimada: " << restante << " años\n";
        
        mostrar_grafico_barras(edad, esperanza);
        mostrar_grafico_pastel(edad, restante);
        
    } catch (...) {
        cout << "Error procesando esperanza de vida.\n";
    }
}

void ejecutar_aplicacion() {
    srand(time(0)); // Inicializar semilla para números aleatorios
    
    cout << "¡Bienvenido al Sistema de Astrología y Esperanza de Vida!\n";
    
    while (true) {
        mostrar_menu();
        string opcion;
        cout << "Elige una opción (1-5): ";
        cin >> opcion;

        if (opcion == "1") {
            procesar_opcion_completa();
        } else if (opcion == "2") {
            procesar_solo_astrologia();
        } else if (opcion == "3") {
            procesar_solo_esperanza();
        } else if (opcion == "4") {
            ejecutar_analisis_ascendente();
        } else if (opcion == "5") {
            cout << "¡Gracias por usar el sistema! Que tengas un buen día.\n";
            break;
        } else {
            cout << "Opción no válida. Elige entre 1 y 5.\n";
        }
        
        cout << "\nPresiona Enter para continuar...";
        cin.ignore();
        cin.get();
    }
}

int main() {
    try {
        ejecutar_aplicacion();
    } catch (const exception& e) {
        cout << "Error fatal: " << e.what() << endl;
        return 1;
    }
    return 0;
}


// ...existing code...
