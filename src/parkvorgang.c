/*
 * File: parkvorgang.c
 * Description: Implementierung der Funktionen zur Verwaltung der Parkvorgänge im Parkhaus
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/parkvorgang.h"

void fuege_kfz_hinzu(Parkhaus *p_parkhaus, Kfz *p_kfz)
{
    if(p_parkhaus == NULL || p_kfz == NULL)
    {
        printf("Fehler: NULL-Pointer in fuege_kfz_hinzu in parkvorgang.c\n");
        return;
    }
    int freie_parkplaetze = (p_parkhaus->anzahl_parkplaetze) - (p_parkhaus->belegte_parkplaetze);
    int min = 0;
    int max = freie_parkplaetze - 1;
     if (freie_parkplaetze == 0)
    {
        printf("Kein freier Parkplatz verfügbar. Das KFZ kann nicht hinzugefügt werden.\n");
        return;
    }
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


void entferne_kfz(Parkhaus *p_parkhaus, Kfz *p_kfz)
{  
     if(p_parkhaus == NULL || p_kfz == NULL)
    {
        printf("Fehler: NULL-Pointer in entferne_kfz in parkvorgang.c\n");
        return;
    }
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


void entferne_kfzs_maximale_parkdauer(Parkhaus *p_parkhaus)
{    
        if(p_parkhaus == NULL)
        {
            printf("Fehler: NULL-Pointer in entferne_kfzs_maximale_parkdauer in parkvorgang.c\n");
            return;
        }
    for(int i = 0; i < p_parkhaus->anzahl_parkplaetze; i++)
    {
        if(p_parkhaus->p_parkplaetze[i].p_kfz != NULL)
        {
            if(p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer < 0)
            {
                p_parkhaus->p_parkplaetze[i].belegt = 0;
                free(p_parkhaus->p_parkplaetze[i].p_kfz);
                p_parkhaus->p_parkplaetze[i].p_kfz = NULL;
                p_parkhaus->belegte_parkplaetze--;
                printf("Ein KFZ musste aufgrund zu hoher Parkzeit entfernt werden oder aufgrund von Bauarbeiten\n");
            }
        }
    }
}