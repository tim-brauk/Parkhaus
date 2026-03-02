#include "warteschlange.h"
#include "parkhaus.h"

void kfz_hinzufuegen_warteschlange(Parkhaus *p_parkhaus, Kfz *p_kfz)
{
    if (p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL)
    {
        p_parkhaus->p_erstes_kfz_in_der_warteschlange = p_kfz;
        p_kfz->p_naechstes_kfz = NULL;
        return;
    }

    Kfz *p_aktuelles_kfz = p_parkhaus->p_erste_kfz_in_der_warteschlange;

    while (p_aktuelles_kfz->p_naechstes_kfz != NULL)
    {
        p_aktuelles_kfz = p_aktuelles_kfz->p_naechstes_kfz;
        //p_aktuelles_kfz wird hier irgendwie nicht deklariert
    }

    p_aktuelles_kfz->p_naechstes_kfz = p_kfz;
    p_kfz->p_naechstes_kfz = NULL;
    
}