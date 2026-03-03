#ifndef STATISTIKEN_H
#define STATISTIKEN_H

#include "parkhaus.h"

/**
 * @file statistik.h
 * @brief Verwaltung und Berechnung aller Simulationsstatistiken.
 */


/**
 * @struct SimulationStats
 * @brief Speichert alle statistischen Werte der Simulation.
 */
typedef struct
{
    float *auslastung_pro_zeitschritt;
    int   *warteschlange_pro_zeitschritt;
    int   *wartezeit_pro_zeitschritt;
    float maximale_auslastung;
    int maximale_warteschlangenlaenge;

} SimulationStats;

/**
 * @brief Initialisiert die Statistik-Struktur.
 *
 * Reserviert Speicher für alle Arrays entsprechend
 * der Anzahl an Zeitschritten.
 *
 * @return Zeiger auf initialisierte Statistikstruktur
 */
SimulationStats* init_statistik();

/**
 * @brief Berechnet die aktuelle Auslastung in Prozent.
 *
 * @param[in] parkhaus Zeiger auf Parkhaus
 * @return Auslastung in Prozent
 */
float berechne_aktuelle_auslastung(const Parkhaus *parkhaus);


/**
 * @brief Berechnet aktuelle Warteschlangenlänge.
 *
 * @param[in] parkhaus Zeiger auf Parkhaus
 * @return Anzahl wartender Fahrzeuge
 */
int berechne_aktuelle_warteschlangenlaenge(const Parkhaus *parkhaus);


/**
 * @brief aktualisiert die maximale Auslastung.
 *
 * @param[in] stats Statistikstruktur
 * @param[in] aktuelle_auslastung Aktuelle Auslastung
 */
void aktualisiere_maximale_auslastung(
    SimulationStats *stats,
    float aktuelle_auslastung
);


/**
 * @brief aktualisiert die maximale Warteschlangenlänge.
 *
 * @param[in] stats Statistikstruktur
 * @param[in] aktuelle_laenge Aktuelle Warteschlangenlänge
 */
void aktualisiere_maximale_warteschlangenlaenge(
    SimulationStats *stats,
    int aktuelle_laenge
);


/**
 * @brief berechnet den Durchschnitt der Auslastung.
 *
 * @param[in] stats Statistikstruktur
 * @return Durchschnittliche Auslastung in Prozent
 */
float berechne_durchschnitt_auslastung(
    const SimulationStats *stats
);


/**
 * @brief berechnet den Durchschnitt der Warteschlangenlänge.
 *
 * @param[in] stats Statistikstruktur
 * @return Durchschnittliche Warteschlangenlänge
 */
float berechne_durchschnitt_warteschlangenlaenge(
    const SimulationStats *stats
);


/**
 * @brief berechnet die durchschnittliche Wartezeit.
 *
 * @param[in] stats Statistikstruktur
 * @return Durchschnittliche Wartezeit in Minuten
 */
float berechne_durchschnittliche_wartezeit(
    const SimulationStats *stats
);

#endif /* STATISTIKEN_H */