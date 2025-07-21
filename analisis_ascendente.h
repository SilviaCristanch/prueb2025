#ifndef ANALISIS_ASCENDENTE_H
#define ANALISIS_ASCENDENTE_H

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include "astrologia.h"

// Descripciones detalladas para cada signo en el ascendente
extern std::map<std::string, std::vector<std::string>> descripciones_ascendente;

/**
 * @brief Obtiene una descripción aleatoria del ascendente
 * @param signo El signo del ascendente
 * @return Una descripción aleatoria del comportamiento del ascendente
 */
std::string obtener_descripcion_aleatoria_ascendente(const std::string& signo);

/**
 * @brief Muestra un análisis completo del ascendente
 * @param signo_ascendente El signo del ascendente a analizar
 */
void mostrar_analisis_ascendente(const std::string& signo_ascendente);

/**
 * @brief Realiza un análisis interactivo del ascendente solicitando datos de nacimiento
 */
void analisis_interactivo_ascendente();

/**
 * @brief Realiza un análisis rápido del ascendente con un signo conocido
 */
void analisis_rapido_ascendente();

/**
 * @brief Función principal del módulo de análisis del ascendente
 */
void ejecutar_analisis_ascendente();

#endif // ANALISIS_ASCENDENTE_H