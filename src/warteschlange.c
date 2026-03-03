#include "warteschlange.h"
#include "parkhaus.h"

kfz_hinzufuegen_warteschlange(Parkhaus *p_parkhaus, Kfz *p_kfz)
{ 
    /*
     * WENN p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL:
     *     p_parkhaus->p_erstes_kfz_in_der_warteschlange = p_kfz
     *     p_kfz->p_naechstes_kfz = NULL
     *     ENDE FUNKTION
     * ENDE WENN
     *
     * Kfz *p_aktuelles_kfz = p_parkhaus->p_erstes_kfz_in_der_warteschlange
     * SOLANGE p_aktuelles_kfz->p_naechstes_kfz != NULL:
     *     p_aktuelles_kfz = p_aktuelles_kfz->p_naechstes_kfz
     * ENDE SOLANGE
     * p_aktuelles_kfz->p_naechstes_kfz = p_kfz
     * p_kfz->p_naechstes_kfz = NULL
     */

    //Die Funktion wird in Teil 2 des Projekts programmiert
}


Kfz* entferne_kfz_warteschlange(Parkhaus *p_parkhaus):
{   
    /*
     * WENN p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL:
     *     Ausgabe: "Keine kfzs in der Warteschlange"
     *     GIB NULL
     *     ENDE FUNKTION
     * ENDE WENN
     *
     * WENN p_parkhaus->p_erstes_kfz_in_der_warteschlange->p_naechstes_kfz == NULL:
     *     Kfz *p_kfz_zwischenspeicher = p_parkhaus->p_erstes_kfz_in_der_warteschlange
     *     p_parkhaus->p_erstes_kfz_in_der_warteschlange = NULL
     *     GIB p_kfz_zwischenspeicher
     *     ENDE FUNKTION
     * ENDE WENN
     *
     * Kfz *p_kfz_zwischenspeicher = p_parkhaus->p_erstes_kfz_in_der_warteschlange
     * p_parkhaus->p_erstes_kfz_in_der_warteschlange = p_kfz_zwischenspeicher->p_naechstes_kfz
     * p_kfz_zwischenspeicher->p_naechstes_kfz = NULL
     * GIB p_kfz_zwischenspeicher
     */

    //Die Funktion wird in Teil 2 des Projekts programmiert
}