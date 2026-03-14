#include "simulation.h"
#include <stdlib.h>
#include <stdio.h>
#include "statistiken.h"
#include "warteschlange.h"
#include "parkvorgang.h"

Simulationsparameter* init_simulationsparameter(
    int anzahl_parkplaetze,
    int maximale_parkdauer,
    float simulations_dauer,
    int seed,
    float wahrscheinlichkeit_neues_kfz)
{
   Simulationsparameter* p_parameter = malloc(sizeof(Simulationsparameter));
    if (p_parameter == NULL)
        return NULL;
    p_parameter->anzahl_parkplaetze = anzahl_parkplaetze;
    p_parameter->maximale_parkdauer = maximale_parkdauer;
    p_parameter->simulations_dauer = simulations_dauer;
    p_parameter->seed = seed;
    p_parameter->wahrscheinlichkeit_neues_kfz = wahrscheinlichkeit_neues_kfz;
    return p_parameter;
}

void simuliere_zeitabschnitt(Parkhaus *p_parkhaus, Simulationsparameter *p_simulationsparameter,SimulationsStats *p_statistik, 
                             int *p_id,
                             int *p_zeitpunkt)

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
    if(zufall <= p_simulationsparameter->wahrscheinlichkeit_neues_kfz)
    {
    Kfz *p_neues_kfz = init_kfz(p_parkhaus, *p_id, *p_zeitpunkt);

        *p_id = aktuelle_id(*p_id);
        kfz_hinzufuegen_warteschlange(p_parkhaus, p_neues_kfz);
    }

    for(int i = 0; i < p_parkhaus->anzahl_parkplaetze; i++)
    {
        if(p_parkhaus->p_parkplaetze[i].belegt)
        {
            if(p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer == 0)
            {
                entferne_kfz(p_parkhaus, p_parkhaus->p_parkplaetze[i].p_kfz);
            }
        }
    }

    int freie_plaetze = platz_garage(p_parkhaus);
    while(freie_plaetze && p_parkhaus->p_erstes_kfz_in_der_warteschlange != NULL)
    {
        Kfz *p_kfz = entferne_kfz_warteschlange(p_parkhaus);
        fuege_kfz_hinzu(p_parkhaus, p_kfz);
        freie_plaetze = platz_garage(p_parkhaus);
    }

    aktualisiere_groesse_statistik(p_statistik, 1);

    p_statistik->p_auslastung_pro_zeitschritt[*p_zeitpunkt] =
        berechne_aktuelle_auslastung(p_parkhaus);

    p_statistik->p_warteschlange_pro_zeitschritt[*p_zeitpunkt] =
        berechne_aktuelle_warteschlangenlaenge(p_parkhaus);

    p_statistik->p_wartezeit_pro_zeitschritt[*p_zeitpunkt] =
        berechne_aktuelle_wartezeit(p_parkhaus, *p_zeitpunkt);

    aktualisiere_maximale_auslastung(p_statistik, p_parkhaus);
    aktualisiere_maximale_warteschlangenlaenge(p_statistik, p_parkhaus);

    ausgabe_statistiken(p_statistik);
    p_statistik->durchlaufene_zeitschritte++;
    (*p_zeitpunkt)++;
}   