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
    unsigned int belegte_parkplaetze; //belegte_parkplaetze !< parkplaetze
} Parkhaus;
/**
* @brief Initialisiert das Parkhaus und reserviert den Speicher dafür.
*
* Reserviert Speichert für das Parkhaus und setzt p_erstes_kfz_in_der_warteschlange auf NULL.
* @param[in]  p_parkplaetze Zeiger auf das Array der Parkplaetze
* @param[in]  anzahl_parkplaetze Anzahl der Parkplaetze
* @param[in]  maximale_parkdauer in Stunden 
* @return p_parkhaus Zeiger auf das Parkhaus
*/
Parkhaus *init_parkhaus(Parkplatz *p_parkplaetze, int anzahl_parkplaetze, int maximale_parkdauer);
#endif /* PARKHAUS_H */