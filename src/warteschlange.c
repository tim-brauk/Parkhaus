#include <stdio.h>
#include <stdlib.h>
#include "../include/warteschlange.h"
#include "../include/parkhaus.h"

void kfz_hinzufuegen_warteschlange(Parkhaus *p_parkhaus, Kfz *p_kfz)
{ 
    if 
    (p_parkhaus == NULL || p_kfz == NULL)
    {
        printf("Fehler: NULL-Pointer in kfz_hinzufuegen_warteschlange in warteschlange.c\n");
        return;
    }
    if(p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL)
    {
         p_parkhaus->p_erstes_kfz_in_der_warteschlange = p_kfz;
         p_kfz->p_naechstes_kfz = NULL;
         return;
    }
    
    Kfz *p_aktuelles_kfz = p_parkhaus->p_erstes_kfz_in_der_warteschlange;
    while(p_aktuelles_kfz->p_naechstes_kfz != NULL)
    {
        p_aktuelles_kfz = p_aktuelles_kfz->p_naechstes_kfz;
    }
    p_aktuelles_kfz->p_naechstes_kfz = p_kfz;
    p_kfz->p_naechstes_kfz = NULL;
}


Kfz* entferne_kfz_warteschlange(Parkhaus *p_parkhaus)
{   
    
    if(p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL)
    {
        printf("Keine kfzs in der Warteschlange\n");
        return NULL;
    }
    
    if(p_parkhaus->p_erstes_kfz_in_der_warteschlange->p_naechstes_kfz == NULL)
    {
        Kfz *p_kfz_zwischenspeicher = p_parkhaus->p_erstes_kfz_in_der_warteschlange;
        p_parkhaus->p_erstes_kfz_in_der_warteschlange = NULL;
        return p_kfz_zwischenspeicher;
    }
    
    Kfz *p_kfz_zwischenspeicher = p_parkhaus->p_erstes_kfz_in_der_warteschlange;
    p_parkhaus->p_erstes_kfz_in_der_warteschlange = p_kfz_zwischenspeicher->p_naechstes_kfz;
    p_kfz_zwischenspeicher->p_naechstes_kfz = NULL;
    return p_kfz_zwischenspeicher;
}