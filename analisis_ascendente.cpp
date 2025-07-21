#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>  // ← Header necesario para find()
#include "astrologia.h"

using namespace std;

// Descripciones detalladas para cada signo en el ascendente
map<string, vector<string>> descripciones_ascendente = {
    {"Aries", {
        "Tienes una personalidad dinámica y enérgica que impacta a los demás",
        "Te presentas como una persona decidida y directa en tus acciones",
        "Posees un carisma natural que te hace destacar en cualquier grupo",
        "Irradias confianza y valentía, inspirando a otros a seguir tu liderazgo",
        "Tu presencia física es fuerte y transmites una energía pionera",
        "Eres visto como alguien que no teme a los retos y siempre va hacia adelante",
        "Tu apariencia refleja determinación y una actitud de 'puedo con todo'",
        "Los demás te perciben como una persona independiente y autosuficiente"
    }},
    {"Taurus", {
        "Proyectas una imagen de estabilidad y confiabilidad que tranquiliza",
        "Tu presencia es calmada y sólida, como una roca en la que otros se apoyan",
        "Irradias sensualidad y una conexión especial con los placeres de la vida",
        "Te ven como alguien práctico y con los pies en la tierra",
        "Tu apariencia refleja buen gusto y una elegancia natural",
        "Posees una voz agradable que cautiva y tranquiliza a quienes te escuchan",
        "Transmites paciencia y perseverancia en todo lo que emprendes",
        "Los demás te perciben como una persona leal y en la que se puede confiar"
    }},
    {"Gemini", {
        "Tienes una personalidad versátil y comunicativa que fascina a otros",
        "Te presentas como alguien intelectual y siempre lleno de ideas nuevas",
        "Posees una agilidad mental que te permite adaptarte a cualquier situación",
        "Irradias curiosidad y un deseo constante de aprender y compartir conocimiento",
        "Tu presencia es vivaz y mantienes conversaciones interesantes con facilidad",
        "Eres visto como una persona sociable que conecta fácilmente con otros",
        "Tu apariencia refleja juventud y una energía mental muy activa",
        "Los demás te perciben como alguien ingenioso y con gran capacidad de comunicación"
    }},
    {"Cancer", {
        "Proyectas una imagen maternal y protectora que hace sentir seguros a otros",
        "Tu presencia es emotiva y empática, conectando profundamente con los sentimientos",
        "Irradias sensibilidad y una intuición especial para entender a las personas",
        "Te ven como alguien hogareño y que valora profundamente la familia",
        "Tu apariencia refleja ternura y una calidez emocional muy especial",
        "Posees una memoria emocional extraordinaria que te permite recordar detalles importantes",
        "Transmites cuidado y protección hacia aquellos que consideras importantes",
        "Los demás te perciben como una persona comprensiva y emocionalmente disponible"
    }},
    {"Leo", {
        "Tienes una personalidad magnética y regia que naturalmente atrae la atención",
        "Te presentas con dignidad y un porte que refleja nobleza interior",
        "Posees un carisma teatral que hace que otros quieran estar cerca de ti",
        "Irradias confianza y una energía solar que ilumina cualquier ambiente",
        "Tu presencia es dramática y sabes cómo hacer una entrada memorable",
        "Eres visto como alguien generoso y con un gran corazón",
        "Tu apariencia refleja elegancia y un estilo personal muy distintivo",
        "Los demás te perciben como una persona creativa y con talento artístico natural"
    }},
    {"Virgo", {
        "Proyectas una imagen de organización y perfección que inspira confianza",
        "Tu presencia es meticulosa y detallista, notando cosas que otros pasan por alto",
        "Irradias practicidad y una capacidad especial para resolver problemas",
        "Te ven como alguien confiable y que siempre tiene todo bajo control",
        "Tu apariencia es pulcra y refleja un cuidado especial por los detalles",
        "Posees una inteligencia analítica que te permite ver soluciones claras",
        "Transmites eficiencia y una dedicación admirable hacia tus responsabilidades",
        "Los demás te perciben como una persona servicial y siempre dispuesta a ayudar"
    }},
    {"Libra", {
        "Tienes una personalidad encantadora y diplomática que crea armonía",
        "Te presentas con gracia y elegancia, siendo naturalmente atractivo para otros",
        "Posees un sentido estético refinado que se refleja en tu apariencia",
        "Irradias equilibrio y una capacidad especial para mediar en conflictos",
        "Tu presencia es suave y agradable, haciendo que otros se sientan cómodos",
        "Eres visto como alguien justo y que siempre busca el bien común",
        "Tu apariencia refleja buen gusto y una armonía natural en tu estilo",
        "Los demás te perciben como una persona sociable y con gran capacidad de relacionarse"
    }},
    {"Scorpio", {
        "Proyectas una imagen intensa y misteriosa que intriga profundamente a otros",
        "Tu presencia es magnética y poderosa, con una energía que no pasa desapercibida",
        "Irradias profundidad emocional y una capacidad de transformación extraordinaria",
        "Te ven como alguien con una fuerza interior inquebrantable",
        "Tu apariencia refleja misterio y una intensidad que cautiva y respeta",
        "Posees una intuición penetrante que te permite ver más allá de las apariencias",
        "Transmites pasión y una autenticidad que pocos pueden igualar",
        "Los demás te perciben como una persona transformadora y con gran poder personal"
    }},
    {"Sagittarius", {
        "Tienes una personalidad aventurera y optimista que inspira a explorar nuevos horizontes",
        "Te presentas como alguien libre y con una visión amplia de la vida",
        "Posees una energía jovial y entusiasta que contagia a quienes te rodean",
        "Irradias sabiduría y una perspectiva filosófica que enriquece las conversaciones",
        "Tu presencia es expansiva y siempre estás buscando nuevas experiencias",
        "Eres visto como alguien honesto y directo, sin filtros ni pretensiones",
        "Tu apariencia refleja libertad y una conexión especial con la aventura",
        "Los demás te perciben como una persona culta y con gran conocimiento del mundo"
    }},
    {"Capricorn", {
        "Proyectas una imagen de autoridad y responsabilidad que inspira respeto",
        "Tu presencia es seria y determinada, mostrando una madurez natural",
        "Irradias ambición y una capacidad extraordinaria para alcanzar metas",
        "Te ven como alguien confiable y que siempre cumple con sus compromisos",
        "Tu apariencia refleja dignidad y un estilo clásico que nunca pasa de moda",
        "Posees una paciencia y perseverancia que te permite construir cosas duraderas",
        "Transmites estabilidad y una sabiduría práctica muy valiosa",
        "Los demás te perciben como una persona exitosa y con gran potencial de liderazgo"
    }},
    {"Aquarius", {
        "Tienes una personalidad única y original que fascina por su autenticidad",
        "Te presentas como alguien innovador y con ideas que están adelantadas a su tiempo",
        "Posees una energía revolucionaria que inspira cambios positivos",
        "Irradias independencia y una libertad de pensamiento que admiran otros",
        "Tu presencia es excéntrica y siempre aportas una perspectiva diferente",
        "Eres visto como alguien humanitario y preocupado por el bienestar colectivo",
        "Tu apariencia refleja originalidad y un estilo personal muy distintivo",
        "Los demás te perciben como una persona visionaria y con gran capacidad de innovación"
    }},
    {"Pisces", {
        "Proyectas una imagen sensible y espiritual que toca el alma de otros",
        "Tu presencia es etérea y misteriosa, con una conexión especial con lo invisible",
        "Irradias compasión y una empatía extraordinaria hacia todos los seres",
        "Te ven como alguien artístico y con una sensibilidad especial para la belleza",
        "Tu apariencia refleja suavidad y una gracia natural que cautiva",
        "Posees una intuición profunda que te permite sentir lo que otros no perciben",
        "Transmites paz y una sabiduría emocional que sana y reconforta",
        "Los demás te perciben como una persona soñadora y con gran capacidad de inspiración"
    }}
};

// Función para obtener una descripción aleatoria del ascendente
string obtener_descripcion_aleatoria_ascendente(const string& signo) {
    if (descripciones_ascendente.find(signo) == descripciones_ascendente.end()) {
        return "Tu ascendente es único y especial.";
    }
    
    const vector<string>& descripciones = descripciones_ascendente[signo];
    if (descripciones.empty()) return "Sin descripción disponible.";
    
    int indice = rand() % descripciones.size();
    return descripciones[indice];
}

// Función para verificar si un número existe en un vector
bool numero_existe_en_vector(const vector<int>& vec, int numero) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == numero) {
            return true;
        }
    }
    return false;
}

// Función para mostrar análisis completo del ascendente
void mostrar_analisis_ascendente(const string& signo_ascendente) {
    cout << "                    ANÁLISIS DEL ASCENDENTE\n";
    
    cout << "\n Tu ascendente: " << signo_ascendente << "\n";
    
    cout << "\n¿Qué es el Ascendente?\n";
    cout << "El ascendente es el signo zodiacal que se estaba levantando en el horizonte\n";
    cout << "oriental en el momento exacto de tu nacimiento. Representa:\n";
    cout << "• Tu personalidad exterior y cómo te presentas al mundo\n";
    cout << "• La primera impresión que causas en los demás\n";
    cout << "• Tu apariencia física y energía vital\n";
    cout << "• Tu manera instintiva de reaccionar ante situaciones nuevas\n";
    
    cout << "\nCaracterísticas de tu ascendente " << signo_ascendente << ":\n";
    
    if (descripciones_ascendente.find(signo_ascendente) != descripciones_ascendente.end()) {
        const vector<string>& descripciones = descripciones_ascendente[signo_ascendente];
        
        // Mostrar 1 descripcion aleatorias sin repetición
        vector<int> indices_usados;
        for (int i = 0; i < min(1, (int)descripciones.size()); i++) {
            int indice;
            do {
                indice = rand() % descripciones.size();
            } while (numero_existe_en_vector(indices_usados, indice));  // ← Línea corregida
            
            indices_usados.push_back(indice);
            cout << "• " << descripciones[indice] << "\n";
        }
    }
    
    cout << "\n INFLUENCIA EN TU VIDA:\n";

    // Información específica por signo sobre su influencia
    map<string, string> influencias = {
        {"Aries", "Tu ascendente Aries te da una energía pioneera y te impulsa a liderar en todas las situaciones. Otros te ven como alguien valiente y decidido."},
        {"Taurus", "Tu ascendente Tauro te otorga una presencia estable y confiable. Las personas se sienten seguras a tu lado y confían en tu criterio."},
        {"Gemini", "Tu ascendente Géminis te hace ver como alguien intelectual y comunicativo. Otros buscan tu compañía para conversaciones estimulantes."},
        {"Cancer", "Tu ascendente Cáncer te da una apariencia maternal y protectora. Las personas se sienten cómodas compartiendo sus emociones contigo."},
        {"Leo", "Tu ascendente Leo te otorga una presencia regia y magnética. Naturalmente atraes la atención y otros te ven como alguien especial."},
        {"Virgo", "Tu ascendente Virgo te hace ver como alguien organizado y confiable. Otros recurren a ti cuando necesitan ayuda práctica."},
        {"Libra", "Tu ascendente Libra te da una apariencia encantadora y diplomática. Las personas se sienten atraídas por tu gracia natural."},
        {"Scorpio", "Tu ascendente Escorpio te otorga una presencia intensa y misteriosa. Otros sienten tu poder personal y te respetan profundamente."},
        {"Sagittarius", "Tu ascendente Sagitario te hace ver como alguien aventurero y sabio. Otros se inspiran con tu optimismo y visión amplia."},
        {"Capricorn", "Tu ascendente Capricornio te da una apariencia seria y respetable. Las personas te ven como alguien exitoso y confiable."},
        {"Aquarius", "Tu ascendente Acuario te otorga una presencia única y original. Otros se sienten intrigados por tu personalidad innovadora."},
        {"Pisces", "Tu ascendente Piscis te da una apariencia sensible y espiritual. Las personas se sienten inspiradas por tu compasión natural."}
    };
    
    if (influencias.find(signo_ascendente) != influencias.end()) {
        cout << influencias[signo_ascendente] << "\n";
    }
    
    cout << "\n💡 CONSEJOS PARA TU ASCENDENTE:\n";
    
    // Consejos específicos por signo
    map<string, string> consejos = {
        {"Aries", "Canaliza tu energía pionera de manera constructiva. Tu liderazgo natural es un regalo, úsalo para inspirar a otros positivamente."},
        {"Taurus", "Aprovecha tu estabilidad natural para crear seguridad en tu entorno. Tu presencia calmada es sanadora para otros."},
        {"Gemini", "Utiliza tu don comunicativo para conectar con diversas personas. Tu versatilidad mental es tu mayor fortaleza."},
        {"Cancer", "Confía en tu intuición emocional, te guiará correctamente. Tu capacidad de cuidar a otros es un don especial."},
        {"Leo", "Brilla con autenticidad y comparte tu luz con otros. Tu carisma natural puede inspirar y elevar a quienes te rodean."},
        {"Virgo", "Tu atención al detalle es valiosa, pero no seas demasiado crítico contigo mismo. Tu capacidad de servir es admirable."},
        {"Libra", "Usa tu don diplomático para crear armonía a tu alrededor. Tu sentido estético puede embellecer el mundo."},
        {"Scorpio", "Canaliza tu intensidad hacia transformaciones positivas. Tu poder personal puede ser una fuerza sanadora."},
        {"Sagittarius", "Comparte tu sabiduría y optimismo con otros. Tu visión amplia puede ayudar a muchas personas a crecer."},
        {"Capricorn", "Tu disciplina y ambición son admirables, pero no olvides disfrutar el camino. Tu ejemplo inspira a otros."},
        {"Aquarius", "Tu originalidad es un regalo para el mundo. No tengas miedo de ser diferente, tu innovación es necesaria."},
        {"Pisces", "Confía en tu intuición y sensibilidad. Tu compasión puede sanar heridas que otros no pueden ver."}
    };
    
    if (consejos.find(signo_ascendente) != consejos.end()) {
        cout << consejos[signo_ascendente] << "\n";
    }
    
    cout << "\n═══════════════════════════════════════════════════════════════\n";
    cout << "Recuerda: Tu ascendente es tu máscara social, la cara que muestras\n";
    cout << "al mundo. Trabajar conscientemente con estas características te\n";
    cout << "ayudará a proyectar la mejor versión de ti mismo.\n";
    cout << "═══════════════════════════════════════════════════════════════\n";
}

// Función para análisis interactivo del ascendente
void analisis_interactivo_ascendente() {
    int dia, mes, anio;
    double lat, lon;
    
    cout << "\n--- ANÁLISIS DETALLADO DEL ASCENDENTE ---\n";
    cout << "Para calcular tu ascendente necesito datos precisos:\n\n";
    
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
    
    cout << "\nHora de nacimiento (0-23): ";
    int hora;
    cin >> hora;
    cout << "Minutos de nacimiento (0-59): ";
    int minuto;
    cin >> minuto;
    
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        cout << "Hora inválida, usando 12:00 por defecto.\n";
        hora = 12;
        minuto = 0;
    }
    
    double hora_decimal = hora + minuto / 60.0;
    
    cout << "\n¿Conoces las coordenadas de tu lugar de nacimiento? (s/n): ";
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
    
    // Crear objeto DateTime y calcular ascendente
    int tz = -5; // Huso horario de Colombia
    DateTime dt(anio, mes, dia, hora_decimal, tz);
    
    string ascendente = calcular_ascendente(dt, lat, lon);
    
    // Mostrar análisis completo
    mostrar_analisis_ascendente(ascendente);
}

// Función para análisis rápido con signo conocido
void analisis_rapido_ascendente() {
    cout << "\n--- ANÁLISIS RÁPIDO DEL ASCENDENTE ---\n";
    cout << "Si ya conoces tu signo ascendente, puedes obtener un análisis inmediato.\n\n";
    
    cout << "Signos disponibles:\n";
    cout << "1. Aries        7. Libra\n";
    cout << "2. Taurus       8. Scorpio\n";
    cout << "3. Gemini       9. Sagittarius\n";
    cout << "4. Cancer      10. Capricorn\n";
    cout << "5. Leo         11. Aquarius\n";
    cout << "6. Virgo       12. Pisces\n";
    
    int opcion;
    cout << "\nSelecciona tu signo ascendente (1-12): ";
    cin >> opcion;
    
    string signos[] = {"Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo",
                       "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius", "Pisces"};
    
    if (opcion >= 1 && opcion <= 12) {
        string signo_elegido = signos[opcion - 1];
        mostrar_analisis_ascendente(signo_elegido);
    } else {
        cout << "Opción inválida. Debe ser entre 1 y 12.\n";
    }
}

// Función principal del módulo
void ejecutar_analisis_ascendente() {
    srand(time(0));
    
    cout << "\n╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║                     ANÁLISIS DEL ASCENDENTE                      ║\n";
    cout << "║                        (Primera Casa)                           ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    
    cout << "\n¿Cómo quieres proceder?\n";
    cout << "1. Calcular mi ascendente con datos de nacimiento\n";
    cout << "2. Analizar un signo ascendente conocido\n";
    cout << "3. Información general sobre el ascendente\n";
    
    int opcion;
    cout << "\nElige una opción (1-3): ";
    cin >> opcion;
    
    switch (opcion) {
        case 1:
            analisis_interactivo_ascendente();
            break;
        case 2:
            analisis_rapido_ascendente();
            break;
        case 3:
            cout << "\n EL ASCENDENTE EN ASTROLOGÍA\n";
            cout << "El ascendente es uno de los elementos más importantes en tu carta natal.\n";
            cout << "Representa tu personalidad externa, la máscara que usas en sociedad\n";
            cout << "y cómo otros te perciben en el primer encuentro.\n\n";
            cout << "A diferencia del signo solar (que es tu esencia), el ascendente es\n";
            cout << "tu presentación al mundo. Cambia cada 2 horas aproximadamente,\n";
            cout << "por lo que la hora exacta de nacimiento es crucial para calcularlo.\n\n";
            cout << "Conocer tu ascendente te ayuda a:\n";
            cout << "• Entender por qué otros te ven de cierta manera\n";
            cout << "• Trabajar conscientemente en tu imagen personal\n";
            cout << "• Aprovechar tus fortalezas naturales de presentación\n";
            cout << "• Mejorar tus primeras impresiones\n";
            break;
        default:
            cout << "Opción no válida.\n";
    }
}