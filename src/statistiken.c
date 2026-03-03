#include "statistik.h"
#include "parkhaus.h"
#include <stdio.h>
#include <stdlib.h>

//Die im Pseudocode geschriebene Logik wird im Teil 2 der Projekts implementiert. Hier werden die Funktionen definiert, die in der Header-Datei deklariert wurden.

SimulationsStats *init_statistik(){
    /*
    Fließkommazahl *auslastung_pro_zeitschritt = malloc(sizeof(Fließkommazahl))
    WENN auslastung_pro_zeitschritt == NULL:
        Ausgabe: "Fehler bei Speicherreservierung für auslastung_pro_zeitschritt"
        //Sicherheitsüberprüfung
    ENDE WENN
    Ganzzahl *warteschlange_pro_zeitschritt = malloc(sizeof(Ganzzahl))
    WENN warteschlange_pro_zeitschritt == NULL:
        Ausgabe: "Fehler bei Speicherreservierung für warteschlange_pro_zeitschritt"
        //Sicherheitsüberprüfung
    ENDE WENN
    Ganzzahl *wartezeit_pro_zeitschritt = malloc(sizeof(Ganzzahl))
    WENN wartezeit_pro_zeitschritt == NULL:
        Ausgabe: "Fehler bei Speicherreservierung für wartezeit_pro_zeitschritt"
        //Sicherheitsüberprüfung
    ENDE WENN

    Fließkommazahl maximale_auslastung = 0
    Ganzzahl maximale_warteschlangenlaenge = 0
    Ganzzahl zeitschritte = 0
    Ganzzahl durchlaufene_zeitschritte = 0
    //Alle Werte mit 0 Initialisieren, da noch kein Zeitabschnitt simuliert wurde

    SimulationsStats *p_statistik = malloc(sizeof(SimulationsStats))
    WENN p_statistik == NULL
        Ausgabe: "Fehler bei Speicherreservierung für p_statistik"
        //Sicherheitsüberprüfung
    ENDE WENN

    p_statistik->auslastung_pro_zeitschritt = auslastung_pro_zeitschritt
    p_statistik->warteschlange_pro_zeitschritt = warteschlange_pro_zeitschritt
    p_statistik->wartezeit_pro_zeitschritt = wartezeit_pro_zeitschritt
    p_statistik->maximale_auslastung = maximale_auslastung
    p_statistik->maximale_warteschlangenlaenge = maximale_warteschlangenlaenge
    p_statistik->zeitschritte = zeitschritte
    p_statistik->durchlaufene_zeitschritte = durchlaufene_zeitschritte
    //Initialisierung von statistik
    GIB p_statistik
    */
}

void aktualisiere_groesse_statistik(SimulationsStats *p_statistik, int zeitschritte){
    Ganzzahl neue_groesse = p_statistik->zeitschritte + zeitschritte
    
    Fließkommazahl *zwischenspeicher_auslastung = realloc(p_statistik->auslastung_pro_zeitschritt, sizeof(Fließkommazahl) * neue_groesse)
    WENN zwischenspeicher_auslastung == NULL:
        Ausgabe: "Fehler beim anpassen von auslastung_pro_zeitschritt"
        //Sicherheitsüberprüfung
    ENDE WENN
    SONST 
        p_statistik->auslastung_pro_zeitschritt = zwischenspeicher_auslastung
        //Falls Sicherheitsüberprüfung erfolgreich wird aktualisiert
    ENDE SONST

    Ganzzahl *zwischenspeicher_warteschlange = realloc(p_statistik->warteschlange_pro_zeitschritt, sizeof(Ganzzahl) * neue_groesse)
    WENN zwischenspeicher_warteschlange == NULL:
        Ausgabe: "Fehler beim anpassen von warteschlange_pro_zeitschritt"
        //Sicherheitsüberprüfung
    ENDE WENN
    SONST 
        p_statistik->warteschlange_pro_zeitschritt = zwischenspeicher_warteschlange
        //Falls Sicherheitsüberprüfung erfolgreich wird aktualisiert
    ENDE SONST

    Ganzzahl *zwischenspeicher_wartezeit = realloc(p_statistik->wartezeit_pro_zeitschritt, sizeof(Ganzzahl) * neue_groesse)
    WENN zwischenspeicher_wartezeit == NULL:
        Ausgabe: "Fehler beim anpassen von wartezeit_pro_zeitschritt"
        //Sicherheitsüberprüfung
    ENDE WENN
    SONST 
        p_statistik->wartezeit_pro_zeitschritt = zwischenspeicher_wartezeit
        //Falls Sicherheitsüberprüfung erfolgreich wird aktualisiert
    ENDE SONST
    p_statistik->zeitschritte = neue_groesse
    //Aktualisierung der groesse
}

float berechne_aktuelle_auslastung(Parkhaus *p_parkhaus){
    /*
    GIB ((Fließkommazahl) p_parkhaus->belegte_parkplaetze / p_parkhaus->anzahl_parkplaetze) * 100
    //Berechnet die aktuelle Auslastung in % 
    */
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

float berechne_durchschnitt_auslastung(SimulationStats *p_statistik){
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