#include <stdio.h>
#include <stdlib.h>
#include "parkvorgang.h"

void fuege_kfz_hinzu(Parkhaus *p_parkhaus, Kfz *p_kfz)
{
    int freie_parkplaetze = (p_parkhaus->anzahl_parkplaetze) - (p_parkhaus->belegte_parkplaetze);
    int min = 0;
    int max = freie_parkplaetze - 1;
    int zufaelliger_parkplatz = 0;
    zufaelliger_parkplatz = min + (rand() % (max - min + 1));

    for(int i = 0; i < p_parkhaus->anzahl_parkplaetze; i++)
    {
        if(!p_parkhaus->p_parkplaetze[i].belegt)
        {
            if(zufaelliger_parkplatz == 0)
            {
                p_parkhaus->p_parkplaetze[i].belegt = 1;
                p_parkhaus->p_parkplaetze[i].p_kfz = p_kfz;
                p_parkhaus->belegte_parkplaetze++;
                return;
            }
        zufaelliger_parkplatz--;
        }
    
        if(!p_parkhaus->p_parkplaetze[i].belegt)
        {
            freie_parkplaetze = freie_parkplaetze - 1;
        }
    }
}


entferne_kfz(Parkhaus *p_parkhaus, Kfz *p_kfz)
{    
    for(int i = 0; i < p_parkhaus->anzahl_parkplaetze; i++)
    {
        if(p_kfz == p_parkhaus->p_parkplaetze[i].p_kfz)
        {
            p_parkhaus->p_parkplaetze[i].belegt = 0;
            free(p_kfz);
            p_parkhaus->p_parkplaetze[i].p_kfz = NULL;
            p_parkhaus->belegte_parkplaetze = p_parkhaus->belegte_parkplaetze - 1;
            return;
        }
    }
    printf("Dieses Kfz wurde im Parkhaus nicht gefunden\n");
}


entferne_kfzs_maximale_parkdauer(Parkhaus *p_parkhaus):
{    
    /*FÜR Ganzzahl i = 0, i < p_parkhaus->anzahl_parkplaetze, i++:
     *  WENN p_parkhaus->p_parkplaetze[i].p_kfz != NULL:
     *       WENN p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer < 0:
     *           p_parkhaus->p_parkplaetze[i].belegt = 0
     *           free(p_parkhaus->p_parkplaetze[i].p_kfz)
     *           p_parkhaus->p_parkplaetze[i].p_kfz = NULL
     *           Ausgabe: "Ein KFZ musste aufgrund zu hoher Parkzeit entfernt werden oder aufgrund von Bauarbeiten"
     *       ENDE WENN
     *   ENDE WENN
     * ENDE FÜR
     */

    //Die Funktion wird in Teil 2 des Projekts programmiert
}