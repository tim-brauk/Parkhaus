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
        printf("Fehler bei Speicherreservierung fuer warteschlange_pro_zeitschritt\n");
        return NULL;
    }

    int *p_wartezeit_pro_zeitschritt = malloc(sizeof(int));

    if(p_wartezeit_pro_zeitschritt == NULL)
    {
        printf("Fehler bei Speicherreservierung fuer wartezeit_pro_zeitschritt\n");
        return NULL;
    }

    SimulationsStats *p_statistik = malloc(sizeof(SimulationsStats));

    if(p_statistik == NULL)
    {
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

float berechne_aktuelle_auslastung(Parkhaus *p_parkhaus){
    
    return ((float) p_parkhaus->belegte_parkplaetze / p_parkhaus->anzahl_parkplaetze) * 100;
    //Berechnet die aktuelle Auslastung in % 
}

int berechne_aktuelle_warteschlangenlaenge(Parkhaus *p_parkhaus){
    /*
    Ganzzahl summe = 0
    WENN p_parkhaus->erstes_kfz_in_der_warteschlange == NULL:
        GIB summe
        //Falls keine KFZ in der Warteschlange ist die Summe = 0
        ENDE FUNKTION
    ENDE WENN
    Kfz *p_kfz_aktuell = p_parkhaus->erstes_kfz_in_der_warteschlange
    SOLANGE p_kfz_aktuell->p_naechstes_kfz != NULL:
        p_kfz_aktuell = p_aktuell_kfz->p_naechstes_kfz
        summe = summe + 1
        //Für jedes KFZ wird die summe um 1 erhöht
    ENDE SOLANGE 
    //+1 da das letzte KFZ nicht mitgerechnet wurde
    GIB summe + 1
    */
}

void aktualisiere_maximale_auslastung(SimulationsStats *p_statistik, Parkhaus *p_parkhaus){
    /*
    Ganzzahl aktuelle_auslastung = berechne_aktuelle_auslastung(Parkhaus p_parkhaus)
    WENN aktuelle_auslastung > p_statistik->maximale_auslastung
        p_statistik->maximale_auslastung = aktuelle_auslastung
    ENDE WENN
    */
}

void aktualisiere_maximale_warteschlangenlaenge(SimulationsStats *p_statistik, Parkhaus *p_parkhaus){
    /*
    Ganzzahl aktuelle_laenge = berechne_aktuelle_warteschlangenlaenge(Parkhaus p_parkhaus)
    WENN aktuelle_laenge > p_statistik->maximale_warteschlangenlaenge:
        p_statistik->maximale_warteschlangenlaenge = aktuelle_laenge
    ENDE WENN
    */
}

float berechne_durchschnitt_auslastung(SimulationsStats *p_statistik){
    /*
    Fließkommazahl durchschnittliche_auslastung = 0
    FÜR i = 0, i < p_statistik->durchlaufene_zeitschritte, i++:
        durchschnittliche_auslastung = durchschnittliche_auslastung + p_statistik->auslastung_pro_zeitschritt[i]
        //Addiert alle Auslastungen in eine Summe
    ENDE FÜR
    durchschnittliche_auslastung = durchschnittliche_auslastung / p_statistik->durchlaufene_zeitschritte
    //Die summe wird durch die Anzahl der durchlaufenen zeitschritte dividiert
    GIB durchschnittliche_auslastung
    */
}

float berechne_durchschnitt_warteschlangenlaenge(SimulationsStats *p_statistik){
    /* 
    Fließkommazahl durchschnittliche_warteschlangenlaenge = 0
    FÜR i = 0, i < p_statistik->durchlaufene_zeitschritte, i++:
        durchschnittliche_warteschlangenlaenge = durchschnittliche_warteschlangenlaenge + p_statistik->warteschlange_pro_zeitschritt[i]
        //Addiert alle warteschlangelaengen in eine Summe
    ENDE FÜR
    durchschnittliche_warteschlangenlaenge = durchschnittliche_warteschlangenlaenge / p_statistik->durchlaufene_zeitschritte
    //Die summe wird durch die Anzahl der durchlaufenen zeitschritte dividiert
    GIB durchschnittliche_warteschlangenlaenge
    */
}

float berechne_durchschnittliche_wartezeit(SimulationsStats *p_statistik){
    /*
    Fließkommazahl durchschnittliche_wartezeit = 0
    FÜR i = 0, i < p_statistik->durchlaufene_zeitschritte, i++:
        durchschnittliche_wartezeit = durchschnittliche_wartezeit + p_statistik->wartezeit_pro_zeitschritt[i]
        //Addiert alle wartezeiten in eine Summe
    ENDE FÜR
    durchschnittliche_wartezeit = durchschnittliche_wartezeit / p_statistik->durchlaufene_zeitschritte
    //Die summe wird durch die Anzahl der durchlaufenen zeitschritte dividiert
    GIB durchschnittliche_wartezeit
    */
}

void ausgabe_statistiken(SimulationsStats *p_statistik){
    /*
    Ausgabe: "\nDurchschnittliche Auslastung liegt bei: " + berechne_durchschnitt_auslastung(SimulationsStats *p_statistik)
    Ausgabe: "\nDurchschnittliche länge der Warteschlange liegt bei: " + berechne_durchschnitt_warteschlangenlaenge(SimulationsStats *p_statistik)
    Ausgabe: "\nDurchschnittliche Wartezeit liegt bei: " + berechne_durchschnittliche_wartezeit(SimulationsStats *p_statistik)
    Ausgabe: "\nMaximale Auslastung: " + p_statistik->maximale_auslastung
    Ausgabe: "\nMaximale Länge der Warteschlange: " + p_statistik->maximale_warteschlangenlaenge
    */
}