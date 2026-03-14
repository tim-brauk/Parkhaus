#ifndef PARKHAUS_H
#define PARKHAUS_H
#include "kfz.h"
typedef struct Parkplatz
{
    int belegt;
    Kfz *p_kfz;
} Parkplatz;
typedef struct Parkhaus
{
    int maximale_parkdauer;
    Parkplatz *p_parkplaetze;
    Kfz *p_erstes_kfz_in_der_warteschlange;
    int anzahl_parkplaetze;
    int belegte_parkplaetze; //belegte_parkplaetze !< parkplaetze
} Parkhaus;
/**
* @brief Initialisiert das Parkhaus und reserviert den Speicher dafür.
*
* Reserviert Speichert für das Parkhaus und setzt p_erstes_kfz_in_der_warteschlange auf NULL.
* @param[in]  anzahl_parkplaetze Anzahl der Parkplaetze
* @param[in]  maximale_parkdauer maximale Parkdauer 
* @return p_parkhaus Zeiger auf das Parkhaus
*/
Parkhaus *init_parkhaus(int anzahl_parkplaetze, int maximale_parkdauer, float simulations_dauer);

/**
 * Prüft ob freie Parkplätze vorhanden sind.
 * @param p_parkhaus Zeiger auf das Parkhaus
 * @return 1 wenn freie Parkplätze vorhanden, 0 wenn voll
 */
int platz_garage(Parkhaus *p_parkhaus);
#endif /* PARKHAUS_H */