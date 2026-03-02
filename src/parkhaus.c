#include "parkhaus.h"

Parkhaus *init_parkhaus(Parkplatz *p_parkplaetze, 
                        int anzahl_parkplaetze, 
                        int maximale_parkdauer)
{    
    Parkhaus *p_parkplaetze = NULL;

    p_parkhaus = (Parkhaus*)malloc(sizeof(Parkhaus));

    if (p_parkhaus == NULL)
        return NULL;

    return p_parkhaus;

    for (int i = 0; i < anzahl_parkplaetze; i++)
    {
        p_parkhaus->p_parkplaetze[i].belegt = 0;
        p_parkhaus->p_parkplaetze[i].p_kfz = NULL;
    }

    p_parkhaus->maximale_parkdauer = maximale_parkdauer;
    p_parkhaus->p_erstes_kfz_in_der_warteschlange = NULL
    p_parkhaus->anzahl_parkplaetze = anzahl_parkplaetze;
    p_parkhaus->belegte_parkplaetze = 0;

    return p_parkhaus;
}