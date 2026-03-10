#include "simulation.h"
#include <stdlib.h>
#include <stdio.h>
#include "statistiken.h"

void aktualisiere_groesse_statistik(SimulationsStats *p_statistik, int benoetigte_groesse)
{
    if (benoetigte_groesse <= p_statistik->durchlaufene_zeitschritte)
    {
        return; 
    }

    int neue_groesse = benoetigte_groesse;
    float *neu_auslastung = realloc(p_statistik->auslastung_pro_zeitschritt, sizeof(float) * neue_groesse);
    int *neu_warteschlange = realloc(p_statistik->warteschlange_pro_zeitschritt, sizeof(int) * neue_groesse);
    int *neu_wartezeit = realloc(p_statistik->wartezeit_pro_zeitschritt, sizeof(int) * neue_groesse);

    if (!neu_auslastung || !neu_warteschlange || !neu_wartezeit)
    {
        printf("Fehler beim Anpassen der Statistikarrays\n");
        return;
    }

    p_statistik->auslastung_pro_zeitschritt = neu_auslastung;
    p_statistik->warteschlange_pro_zeitschritt = neu_warteschlange;
    p_statistik->wartezeit_pro_zeitschritt = neu_wartezeit;

    p_statistik->durchlaufene_zeitschritte = neue_groesse;
}

void simuliere_zeitabschnitt(Parkhaus *p_parkhaus, Simulationsparameter *p_simulationsparameter, int *p_id, int *p_zeitpunkt, SimulationsStats *p_statistik)
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
        Kfz *p_neues_kfz = init_kfz(p_parkhaus, *p_id);

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

    aktualisiere_groesse_statistik(p_statistik, *p_zeitpunkt);

    p_statistik->auslastung_pro_zeitschritt[*p_zeitpunkt] =
        berechne_aktuelle_auslastung(p_parkhaus);

    p_statistik->warteschlange_pro_zeitschritt[*p_zeitpunkt] =
        berechne_aktuelle_warteschlangenlaenge(p_parkhaus);

    p_statistik->wartezeit_pro_zeitschritt[*p_zeitpunkt] =
        berechne_aktuelle_wartezeit(p_parkhaus, *p_zeitpunkt);

    aktualisiere_maximale_auslastung(p_parkhaus);
    aktualisiere_maximale_warteschlangenlaenge(p_parkhaus, *p_zeitpunkt);

    ausgabe_statistiken(p_statistik);
    p_statistik->durchlaufene_zeitschritte++;
    (*p_zeitpunkt)++;
}