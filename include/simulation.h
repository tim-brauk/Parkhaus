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

Simulationsparameter* init_simulationsparameter(
    int anzahl_parkplaetze,
    int maximale_parkdauer,
    float simulations_dauer,
    int seed,
    float wahrscheinlichkeit_neues_kfz
);

/**
 * @brief Macht einen Simulationsschritt.
 *
 * Erhöht die Parkzeit jedes geparkten Kfz um 1.
 * entfernt alle Kfz die die maximale Parkdauer überschritten haben.
 * initiiert neue Kfz (init_car) und fügt sie der Warteschlange hinzu(add_car_queue).
 * Zählt die Anzahl der Autos im Parkhaus.
 * Fügt Autos aus der Warteschlange in das Parkhaus, wenn es freie Parkplätze gibt (check_garage_for_space)
 * und entfernt sie aus der Warteschlange (remove_car_queue).
 * 
 *
 * @param[in] p_parkhaus Zeiger auf das Parkhaus
 * @return void
 */
void simuliere_zeitabschnitt(Parkhaus *p_parkhaus, Simulationsparameter *p_simulationsparameter);
#endif /* SIMULATION_H */