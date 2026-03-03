#include "parkhaus.h"

Parkhaus *init_parkhaus(Parkplatz *p_parkplaetze, 
                        int anzahl_parkplaetze, 
                        int maximale_parkdauer)
    /*
     * Parkhaus *p_parkhaus = malloc(sizeof(Parkhaus))
     * WENN p_parkhaus == NULL:
     *     GIB NULL
     * ENDE WENN
     *
     * p_parkhaus->p_parkplaetze = malloc(sizeof(Parkplatz) * anzahl_parkplaetze)
     * WENN p_parkhaus->p_parkplaetze == NULL:
     *     free(p_parkhaus)
     *     GIB NULL
     * ENDE WENN
     *
     * FÜR Ganzzahl i = 0, i < anzahl_parkplaetze, i++:
     *     p_parkhaus->p_parkplaetze[i].belegt = 0
     *     p_parkhaus->p_parkplaetze[i].p_kfz = NULL
     * ENDE FÜR
     *
     * p_parkhaus->anzahl_parkplaetze = anzahl_parkplaetze
     * p_parkhaus->belegte_parkplaetze = 0
     * p_parkhaus->maximale_parkdauer = maximale_parkdauer
     * p_parkhaus->p_erstes_kfz_in_der_warteschlange = NULL
     *
     * GIB p_parkhaus
     */

    //Die Funktion wird in Teil 2 des Projekts programmiert

ENDE FUNKTION