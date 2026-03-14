#ifndef SIMULATION_H
#define SIMULATION_H
#include "parkhaus.h"

typedef struct Simulationsparameter
{
    int anzahl_parkplaetze;
    int maximale_parkdauer; //parkdauer 
    float  simulations_dauer; //simulations_dauer
    int seed;
    float wahrscheinlichkeit_neues_kfz;
    float wahrscheinlichkeit_kfz_rausfahren;
} Simulationsparameter;

/**
 * @brief Aktualisiert die Parameter der Simulation und des Parkhauses.
 *
 * Setzt neue Werte für Parkhauskapazität, maximale Parkdauer und
 * Simulationsparameter wie Dauer, Zufalls-Seed und Wahrscheinlichkeit
 * für neu ankommende Fahrzeuge.
 * @param[in] p_parkhaus Zeiger auf das Parkhaus
 * @param[in] p_simulationsparamter Zeiger auf Simulationsparameter
 * @param[in] anzahl_parkplaetze Anzahl Parkplaetze im Parkhaus
 * @param[in] simulations_dauer Dauer der Simulation
 * @param[in] wahrscheinlichkeit_neues_kfz Wahrscheinlichkeit fuer ein ankommendes Kfz
 * @param[in] seed Zufallsgenrator
 * @return void
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
 * entfernt alle Kfz die die maximale Parkdauer überschritten haben.
 * initiiert neue Kfz (init_kfz) und fügt sie der Warteschlange hinzu (kfz_hinzfuegen_warteschlange).
 * Zählt die Anzahl der Autos im Parkhaus.
 * Fügt Autos aus der Warteschlange in das Parkhaus, wenn es freie Parkplätze gibt (platz_garage)
 * und entfernt sie aus der Warteschlange (entferne_kfz_warteschlange).
 * 
 *
 * @param[in] p_parkhaus Zeiger auf das Parkhaus
 * @return void
 */
void simuliere_zeitabschnitt(
        Parkhaus *p_parkhaus, 
        Simulationsparameter *p_simulationsparameter, 
        SimulationsStats *p_statistik,
        int *id,
        int *zeitpunkt);
#endif /* SIMULATION_H */