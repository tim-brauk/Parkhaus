#include "simulation.h"
#include <stdlib.h>

void simuliere_zeitabschnitt(Parkhaus *p_parkhaus,
                             Simulationsparameter *p_simulationsparameter,
                             int *p_id,
                             int *p_zeitpunkt,
                             SimulationsStats *p_statistik)
{
    for(int i = 0; i < p_parkhaus->anzahl_parkplaetze; i++)
    {
        if(p_parkhaus->p_parkplaetze[i].belegt)
        {
            p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer =
                p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer - 1;
        }
    }

    float zufall = (float)rand() / (float)RAND_MAX;

    entferne_kfzs_maximale_parkdauer(p_parkhaus);

    if(zufall <= p_simulationsparameter->wahrscheinlichkeit_neues_kfz)
    {
        Kfz *p_neues_kfz = init_kfz(p_parkhaus, *p_id, *p_zeitpunkt);
        *p_id = aktuelle_id(*p_id);
        kfz_hinzufuegen_warteschlange(p_parkhaus, p_neues_kfz);
    }

     * WENN zufall <= p_simulationsparameter->wahrscheinlichkeit_neues_kfz:
     *     // ">=" statt ">" da falls Wahrscheinlichkeit = 1 und zufall = 1 soll trotzdem Kfz rein. Bei 100% wahrscheinlichkeit MUSS eine Kfz rein
     *     Kfz *p_neues_kfz = init_kfz(Parkhaus *p_parkhaus, Ganzzahl id, Ganzzahl zeitpunkt)
     *     id = aktuelle_id(Ganzzahl id)
     *     kfz_hinzufuegen_warteschlange(Parkhaus *p_parkhaus, Kfz *p_neues_kfz)
     * ENDE WENN
     *
     * FÜR Ganzzahl i = 0, i < p_parkhaus->anzahl_parkplaetze, i++:
     *     WENN p_parkhaus->p_parkplaetze[i].belegt
     *         WENN p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer == 0:
     *             entferne_kfz(Parkhaus p_parkhaus, Kfz p_parkhaus->p_parkplaetze[i].p_kfz)
     *         ENDE WENN
     *     ENDE WENN
     * ENDE FÜR
     * //Bei allen KFZ wird die verbleibende parkdauer überprüft. Falls diese 0 erreicht werden sie entfernt
     *
     * Ganzzahl freie_parkplaetze_wahrheitsvariable = 0; // 0 = keine freien Parkplaetze. 1 = freie Parkplaetze
     *
     * SOLANGE freie_parkplaetze_wahrheitsvariable AND p_parkhaus->p_erstes_kfz_in_der_warteschlange != NULL:
     *     Kfz *p_kfz_hinzufuegen_aus_queue = entferne_kfz_warteschlange(Parkhaus *p_parkhaus)
     *     fuege_kfz_hinzu(Parkhaus *p_parkhaus, Kfz *p_kfz_hinzufuegen_aus_queue)
     *     freie_parkplaetze_wahrheitsvariable = platz_garage(Parkhaus *p_parkhaus)
     * ENDE SOLANGE
     * //Es werden alle KFZs aus der Warteschlange hinzugefügt solange platz im Parkhaus vorhanden ist. 
     * 
     * p_statistik->auslastung_pro_zeitschritt[zeitpunkt] = berechne_aktuelle_auslastung(Parkhaus *p_parkhaus)
     * p_statistik->warteschlange_pro_zeitschritt[zeitpunkt] = berechne_aktuelle_warteschlangenlaenge(Parkhaus *p_parkhaus)
     * p_statistik->wartezeit_pro_zeitschritt[zeitpunkt] = berechne_aktuelle_wartezeit(Parkhaus *p_parkhaus)
     * aktualisiere_maximale_auslastung(Parkhaus *p_parkhaus)
     * aktualisiere_maximale_warteschlangenlaenge(Parkhaus *p_parkhaus)
     * ausgabe_statistiken(SimulationsStats *p_statistik)
     * p_statistik->durchlaufene_zeitschritte = p_statistik->durchlaufene_zeitschritte + 1
     *
     * zeitpunkt = zeitpunkt + 1
     */

    //Die Funktion wird in Teil 2 des Projekts programmiert
}