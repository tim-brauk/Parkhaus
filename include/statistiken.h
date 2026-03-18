#ifndef STATISTIKEN_H
#define STATISTIKEN_H

#include "parkhaus.h"

/**
 * @file statistik.h
 * @brief Verwaltung und Berechnung aller Simulationsstatistiken.
 */


/**
 * @struct SimulationsStats
 * @brief Speichert alle statistischen Werte der Simulation.
 */
typedef struct
{
    float *p_auslastung_pro_zeitschritt;
    int   *p_warteschlange_pro_zeitschritt;
    float *p_wartezeit_pro_zeitschritt;
    float maximale_auslastung;
    int maximale_warteschlangenlaenge;
    int zeitschritte;
    int durchlaufene_zeitschritte;

} SimulationsStats;

/**
 * @brief Initialisiert die Statistik-Struktur.
 *
 * Reserviert Speicher für alle Arrays entsprechend
 * der Anzahl an Zeitschritten.
 *
 * @return Zeiger auf initialisierte Statistikstruktur
 */
SimulationsStats* init_statistik();


 /**
 * @brief Aktualisiert die groessen der Statistik-Arrays.
 * 
 * @param[in] p_statistik Zeiger auf Statistikstruktur
 * @param[in] zeitschritte Anzahl der neuen Zeitschritte
 */
void aktualisiere_groesse_statistik(
    SimulationsStats *p_statistik, 
    int zeitschritte
);


/**
 * @brief Berechnet die aktuelle Auslastung in Prozent.
 *
 * @param[in] parkhaus Zeiger auf Parkhaus
 * @return Auslastung in Prozent
 */
float berechne_aktuelle_auslastung(const Parkhaus *parkhaus);

/**
* @brief Berechnet die aktuelle durchschnittliche Wartezeit in Minuten.
 *
 * @param[in] parkhaus Zeiger auf Parkhaus
 * @return aktuelle Durchschnittliche Wartezeit in Minuten
 */
float berechne_aktuelle_wartezeit(const Parkhaus *parkhaus, int p_zeitpunkt);


/**
 * @brief Berechnet aktuelle Warteschlangenlänge.
 *
 * @param[in] parkhaus Zeiger auf Parkhaus
 * @param[in] zeitpunkt Aktueller Zeitpunkt der Simulation
 * @return Anzahl wartender Fahrzeuge
 */
int berechne_aktuelle_warteschlangenlaenge(const Parkhaus *parkhaus);


/**
 * @brief aktualisiert die maximale Auslastung.
 *
 * @param[in] stats Statistikstruktur
 * @param[in] p_parkhaus Zeiger auf Parkhaus
 */
void aktualisiere_maximale_auslastung(
    SimulationsStats *stats,
    Parkhaus *p_parkhaus
);


/**
 * @brief aktualisiert die maximale Warteschlangenlänge.
 *
 * @param[in] stats Statistikstruktur
 * @param[in] p_parkhaus Zeiger auf Parkhaus
 */
void aktualisiere_maximale_warteschlangenlaenge(
    SimulationsStats *stats,
    Parkhaus *p_parkhaus
);


/**
 * @brief berechnet den Durchschnitt der Auslastung.
 *
 * @param[in] stats Statistikstruktur
 * @return Durchschnittliche Auslastung in Prozent
 */
float berechne_durchschnitt_auslastung(
    const SimulationsStats *stats
);


/**
 * @brief berechnet den Durchschnitt der Warteschlangenlänge.
 *
 * @param[in] stats Statistikstruktur
 * @return Durchschnittliche Warteschlangenlänge
 */
float berechne_durchschnitt_warteschlangenlaenge(
    const SimulationsStats *stats
);


/**
 * @brief berechnet die durchschnittliche Wartezeit.
 *
 * @param[in] stats Statistikstruktur
 * @return Durchschnittliche Wartezeit in Minuten
 */
float berechne_durchschnittliche_wartezeit(
    const SimulationsStats *stats
);

/**
* @brief Gibt alle gesammelten Statistiken aus.
*
* @param[in] p_statistik Zeiger auf Statistikstruktur
*/
void ausgabe_statistiken(SimulationsStats *p_statistik);


#endif /* STATISTIKEN_H */