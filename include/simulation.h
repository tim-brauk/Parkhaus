#ifndef SIMULATION_H
#define SIMULATION_H
#include "parkhaus.h"
#include "statistiken.h"

/**
 * @brief Struktur mit allen Simulationsparametern.
 *
 * Diese Struktur enthält Parameter, die für die
 * Durchführung der Simulation notwendig sind.
 * Bsp: Anzahl der Parkplätze, maximale Parkdauer,
 * Simulationsdauer, Zufalls-Seed
 */
typedef struct Simulationsparameter
{
    int anzahl_parkplaetze;          // Anzahl der verfügbaren Parkplätze
    int maximale_parkdauer;          // Maximale Parkdauer
    float simulations_dauer;         // Simulationsdauer
    int seed;                        // Seed für den Zufallszahlgenerator
    float wahrscheinlichkeit_neues_kfz; // Wahrscheinlichkeit, dass in einem Zeitschritt ein neues Kfz ankommt
} Simulationsparameter;

/**
 * @brief Initialisiert die Simulationsparameter.
 *
 * Reserviert Speicher und setzt die übergebenen Werte in der Parameterstruktur.
 * @param[in] anzahl_parkplaetze Anzahl der Parkplätze
 * @param[in] maximale_parkdauer Maximale Parkdauer (Stunden)
 * @param[in] simulations_dauer Gesamtdauer der Simulation (Stunden)
 * @param[in] seed Zufalls-Seed
 * @param[in] wahrscheinlichkeit_neues_kfz Wahrscheinlichkeit für neu ankommende Fahrzeuge
 * @return Zeiger auf die initialisierte Struktur oder NULL bei Fehler
 */
Simulationsparameter *init_simulationsparameter(
    int anzahl_parkplaetze,
    int maximale_parkdauer,
    float simulations_dauer,
    int seed,
    float wahrscheinlichkeit_neues_kfz
);

/**
 * @brief Aktualisiert die Parameter der Simulation und des Parkhauses.
 *
 * Setzt neue Werte für Parkhauskapazität, maximale Parkdauer und
 * Simulationsparameter wie Dauer, Zufalls-Seed und Wahrscheinlichkeit
 * für neu ankommende Fahrzeuge.
 * @param[in,out] p_parkhaus Zeiger auf das Parkhaus
 * @param[in,out] p_simulationsparameter Zeiger auf Simulationsparameter
 * @param[in] anzahl_parkplaetze Anzahl Parkplaetze im Parkhaus
 * @param[in] maximale_parkdauer Maximale Parkdauer eines Kfz
 * @param[in] simulations_dauer Dauer der Simulation
 * @param[in] wahrscheinlichkeit_neues_kfz Wahrscheinlichkeit fuer ein ankommendes Kfz
 * @param[in] seed Zufallsgenerator
 */
void aktualisiere_parameter(
        Parkhaus *p_parkhaus, 
        Simulationsparameter *p_simulationsparameter, 
        int anzahl_parkplaetze, 
        int maximale_parkdauer, 
        float simulations_dauer, 
        float wahrscheinlichkeit_neues_kfz, 
        int seed);

/**
 * @brief Macht einen Simulationsschritt.
 *
 * Erhöht die Parkzeit jedes geparkten Kfz um 1.
 * Entfernt alle Kfz die die maximale Parkdauer überschritten haben.
 * Initiiert neue Kfz (init_kfz) und fügt sie der Warteschlange hinzu (kfz_hinzfuegen_warteschlange).
 * Zählt die Anzahl der Autos im Parkhaus.
 * Fügt Autos aus der Warteschlange in das Parkhaus, wenn es freie Parkplätze gibt (platz_garage)
 * und entfernt sie aus der Warteschlange (entferne_kfz_warteschlange).
 *
 * @param[in,out] p_parkhaus Zeiger auf das Parkhaus
 * @param[in] p_simulationsparameter Zeiger auf Simulationsparameter
 * @param[in,out] p_statistik Zeiger auf die Simulationsstatistik
 * @param[in,out] id Zeiger auf die aktuelle Kfz-ID
 * @param[in,out] zeitpunkt Zeiger auf den aktuellen Zeitpunkt
 */
void simuliere_zeitabschnitt(
        Parkhaus *p_parkhaus, 
        Simulationsparameter *p_simulationsparameter, 
        SimulationsStats *p_statistik,
        int *id,
        int *zeitpunkt);

#endif /* SIMULATION_H */