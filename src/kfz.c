/*
 * File: kfz.c
 * Description: initialisiert Kfz und definiert die Struktur Kfz
 */
#include <stdio.h>
#include <stdlib.h>
#include "../include/kfz.h"
#include "../include/parkhaus.h"

Kfz* init_kfz(struct Parkhaus *p_parkhaus, int id, int zeitpunkt)
{   
    if(p_parkhaus == NULL)
    {
        printf("Fehler: Null-Pointer in init_kfz in kfz.c\n");
        return NULL;
    } 
    Kfz *p_kfz = malloc(sizeof(Kfz));
    if(p_kfz == NULL)
    {       
        printf("Malloc Fehler in init_kfz\n");
        return NULL;
    }
    p_kfz->id = id;
    p_kfz->einfahrtszeitpunkt = zeitpunkt;
    int min = 1;
    int max = p_parkhaus->maximale_parkdauer;
    p_kfz->verbleibende_parkdauer = min + rand() % (max - min + 1);
    p_kfz->p_naechstes_kfz = NULL;
    return p_kfz;
    
}