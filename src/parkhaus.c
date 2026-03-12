#include <stdlib.h>
#include <stdio.h>
#include "parkhaus.h"

Parkhaus* init_parkhaus(int anzahl_parkplaetze, int maximale_parkdauer)
{
    Parkhaus *p_parkhaus = malloc(sizeof(Parkhaus));
    if(p_parkhaus == NULL)
    {
        printf("Malloc Fehler in init_parkhaus\n");
        return NULL;
    }

    p_parkhaus->p_parkplaetze = malloc(sizeof(Parkplatz) * anzahl_parkplaetze);
    if(p_parkhaus->p_parkplaetze == NULL)
    {
        printf("Malloc Fehler in init_parkhaus (Parkplaetze)\n");
        free(p_parkhaus);
        return NULL;
    }

    for(int i = 0; i < anzahl_parkplaetze; i++)
    {
        p_parkhaus->p_parkplaetze[i].belegt = 0;
        p_parkhaus->p_parkplaetze[i].p_kfz = NULL;
    }

    p_parkhaus->anzahl_parkplaetze = anzahl_parkplaetze;
    p_parkhaus->belegte_parkplaetze = 0;
    p_parkhaus->maximale_parkdauer = maximale_parkdauer;
    p_parkhaus->p_erstes_kfz_in_der_warteschlange = NULL;

    return p_parkhaus;
}

int platz_garage(Parkhaus *p_parkhaus){
    if(p_parkhaus->anzahl_parkplaetze == p_parkhaus->belegte_parkplaetze)
    {
        return 0;
    }

    else
    {
        return 1;
    }
}