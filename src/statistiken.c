/*
   @file statistiken.c
   @brief Funktionen zur Verwaltung und Berechnung von Simulationsstatistiken.
  
   Diese Datei implementiert Funktionen zur Initialisierung der
   Statistikstruktur, zur dynamischen Anpassung der Speichergröße
   sowie zur Berechnung verschiedener Kennzahlen der Parkhaus-
   Simulation, wie z.B. Auslastung, Warteschlangenlänge und
   durchschnittliche Wartezeit.
*/

#include "statistiken.h"
#include "parkhaus.h"
#include <stdio.h>
#include <stdlib.h>

SimulationsStats *init_statistik()
{
    float *p_auslastung_pro_zeitschritt = malloc(sizeof(float));
    if(p_auslastung_pro_zeitschritt == NULL)
    {
        printf("Fehler bei Speicherreservierung fuer auslastung_pro_zeitschritt\n");
        return NULL;
    }

    int *p_warteschlange_pro_zeitschritt = malloc(sizeof(int));

    if(p_warteschlange_pro_zeitschritt == NULL)
    {
        free(p_auslastung_pro_zeitschritt);
        printf("Fehler bei Speicherreservierung fuer warteschlange_pro_zeitschritt\n");
        return NULL;
    }

    float *p_wartezeit_pro_zeitschritt = malloc(sizeof(float));

    if(p_wartezeit_pro_zeitschritt == NULL)
    {
        free(p_auslastung_pro_zeitschritt);
        free(p_warteschlange_pro_zeitschritt);
        printf("Fehler bei Speicherreservierung fuer wartezeit_pro_zeitschritt\n");
        return NULL;
    }

    SimulationsStats *p_statistik = malloc(sizeof(SimulationsStats));

    if(p_statistik == NULL)
    {
        free(p_auslastung_pro_zeitschritt);
        free(p_warteschlange_pro_zeitschritt);
        free(p_wartezeit_pro_zeitschritt);
        printf("Fehler bei Speicherreservierung fuer p_statistik\n");
        return NULL;
    }

    float maximale_auslastung = 0.0f;
    int maximale_warteschlangenlaenge = 0;
    int zeitschritte = 0;
    int durchlaufene_zeitschritte = 0;

    p_statistik->p_auslastung_pro_zeitschritt = p_auslastung_pro_zeitschritt;
    p_statistik->p_warteschlange_pro_zeitschritt = p_warteschlange_pro_zeitschritt;
    p_statistik->p_wartezeit_pro_zeitschritt = p_wartezeit_pro_zeitschritt;
    p_statistik->maximale_auslastung = maximale_auslastung;
    p_statistik->maximale_warteschlangenlaenge = maximale_warteschlangenlaenge;
    p_statistik->zeitschritte = zeitschritte;
    p_statistik->durchlaufene_zeitschritte = durchlaufene_zeitschritte;
    return p_statistik;
}

void aktualisiere_groesse_statistik(SimulationsStats *p_statistik, int zeitschritte)
{
    int neue_groesse = p_statistik->zeitschritte + zeitschritte;
    float *p_zwischenspeicher_auslastung =
        realloc(p_statistik->p_auslastung_pro_zeitschritt, sizeof(float) * neue_groesse);

    if(p_zwischenspeicher_auslastung == NULL)
    {
        printf("Fehler beim Anpassen von auslastung_pro_zeitschritt\n");
    }
    else
    {
        p_statistik->p_auslastung_pro_zeitschritt = p_zwischenspeicher_auslastung;
    }

    int *p_zwischenspeicher_warteschlange =
        realloc(p_statistik->p_warteschlange_pro_zeitschritt, sizeof(int) * neue_groesse);

    if(p_zwischenspeicher_warteschlange == NULL)
    {
        printf("Fehler beim Anpassen von warteschlange_pro_zeitschritt\n");
    }
    else
    {
        p_statistik->p_warteschlange_pro_zeitschritt = p_zwischenspeicher_warteschlange;
    }

    int *p_zwischenspeicher_wartezeit =
        realloc(p_statistik->p_wartezeit_pro_zeitschritt, sizeof(int) * neue_groesse);

    if(p_zwischenspeicher_wartezeit == NULL)
    {
        printf("Fehler beim Anpassen von wartezeit_pro_zeitschritt\n");
    }
    else
    {
        p_statistik->p_wartezeit_pro_zeitschritt = p_zwischenspeicher_wartezeit;
    }

    p_statistik->zeitschritte = neue_groesse;
}

float berechne_aktuelle_auslastung(const Parkhaus *p_parkhaus)
{
    
    return ((float) p_parkhaus->belegte_parkplaetze / p_parkhaus->anzahl_parkplaetze) * 100;
}

int berechne_aktuelle_warteschlangenlaenge(const Parkhaus *p_parkhaus)
{
    int summe = 0;
    if(p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL)
    {    
        return summe;
    }
    
    Kfz *p_kfz_aktuell = p_parkhaus->p_erstes_kfz_in_der_warteschlange;
    while(p_kfz_aktuell->p_naechstes_kfz != NULL)
    {
        p_kfz_aktuell = p_kfz_aktuell->p_naechstes_kfz;
        summe = summe + 1;
    }
    
    return summe + 1;
}

float berechne_aktuelle_wartezeit(const Parkhaus *p_parkhaus, int p_zeitpunkt)
{
    if(p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL)
    {
        return 0;
    }

    int summe = 0;
    Kfz *p_kfz_zwischenspeicher = p_parkhaus->p_erstes_kfz_in_der_warteschlange;

    while(p_kfz_zwischenspeicher != NULL)
    {
       summe = summe + (p_zeitpunkt - p_kfz_zwischenspeicher->einfahrtszeitpunkt); 
       p_kfz_zwischenspeicher = p_kfz_zwischenspeicher->p_naechstes_kfz;
    }
    return summe / berechne_aktuelle_warteschlangenlaenge(p_parkhaus);
}

void aktualisiere_maximale_auslastung(SimulationsStats *p_statistik, Parkhaus *p_parkhaus)
{
    float aktuelle_auslastung = berechne_aktuelle_auslastung( p_parkhaus);
    if(aktuelle_auslastung > p_statistik->maximale_auslastung)
    {
        p_statistik->maximale_auslastung = aktuelle_auslastung;
    }
}

void aktualisiere_maximale_warteschlangenlaenge(SimulationsStats *p_statistik, Parkhaus *p_parkhaus)
{

    int aktuelle_laenge = berechne_aktuelle_warteschlangenlaenge( p_parkhaus);
    if(aktuelle_laenge > p_statistik->maximale_warteschlangenlaenge)
    {
        p_statistik->maximale_warteschlangenlaenge = aktuelle_laenge;
    }
}

float berechne_durchschnitt_auslastung(const SimulationsStats *p_statistik)
{
    if(p_statistik->durchlaufene_zeitschritte == 0)
    {
        return 0.0f; // noch nicht fertig
    }

    float durchschnittliche_auslastung = 0.0f;
    for(int i = 0; i < p_statistik->durchlaufene_zeitschritte; i++)
    {
        durchschnittliche_auslastung = durchschnittliche_auslastung + p_statistik->p_auslastung_pro_zeitschritt[i];
    }

    durchschnittliche_auslastung = durchschnittliche_auslastung / p_statistik->durchlaufene_zeitschritte;
    return durchschnittliche_auslastung;
}

float berechne_durchschnitt_warteschlangenlaenge(const SimulationsStats *p_statistik)
{
    if(p_statistik->durchlaufene_zeitschritte == 0)
    {
        return p_statistik->p_warteschlange_pro_zeitschritt[0]; // noch nicht fertig
    }

    float durchschnittliche_warteschlangenlaenge = 0.0f;
    for(int i = 0; i < p_statistik->durchlaufene_zeitschritte; i++)
    {
        durchschnittliche_warteschlangenlaenge = durchschnittliche_warteschlangenlaenge + p_statistik->p_warteschlange_pro_zeitschritt[i];
    }

    durchschnittliche_warteschlangenlaenge = durchschnittliche_warteschlangenlaenge / p_statistik->durchlaufene_zeitschritte;
    return durchschnittliche_warteschlangenlaenge;
}

float berechne_durchschnittliche_wartezeit(const SimulationsStats *p_statistik)
{
    if(p_statistik->durchlaufene_zeitschritte == 0)
    {
        return p_statistik->p_warteschlange_pro_zeitschritt[0]; // noch nicht fertig
    }

    float durchschnittliche_wartezeit = 0.0f;
    for(int i = 0; i < p_statistik->durchlaufene_zeitschritte; i++)
    {
        durchschnittliche_wartezeit = durchschnittliche_wartezeit + p_statistik->p_wartezeit_pro_zeitschritt[i];
    }
    
    durchschnittliche_wartezeit = durchschnittliche_wartezeit / p_statistik->durchlaufene_zeitschritte;
    return durchschnittliche_wartezeit;
}

void ausgabe_statistiken(SimulationsStats *p_statistik)
{
    printf("\nDurchschnittliche Auslastung liegt bei: %.2f", berechne_durchschnitt_auslastung( p_statistik));
    printf("\nDurchschnittliche Laenge der Warteschlange liegt bei: %.2f", berechne_durchschnitt_warteschlangenlaenge( p_statistik));
    printf("\nDurchschnittliche Wartezeit liegt bei: %.2f", berechne_durchschnittliche_wartezeit( p_statistik));
    printf("\nMaximale Auslastung: %.2f%%", p_statistik->maximale_auslastung);
    printf("\nMaximale Laenge der Warteschlange: %d\n", p_statistik->maximale_warteschlangenlaenge);
}