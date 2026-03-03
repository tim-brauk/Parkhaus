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
    ENDE WENN
    Ganzzahl *warteschlange_pro_zeitschritt = malloc(sizeof(Ganzzahl))
    WENN warteschlange_pro_zeitschritt == NULL:
        Ausgabe: "Fehler bei Speicherreservierung für warteschlange_pro_zeitschritt"
    ENDE WENN
    Ganzzahl *wartezeit_pro_zeitschritt = malloc(sizeof(Ganzzahl))
    WENN wartezeit_pro_zeitschritt == NULL:
        Ausgabe: "Fehler bei Speicherreservierung für wartezeit_pro_zeitschritt"
    ENDE WENN

    Fließkommazahl maximale_auslastung = 0
    Ganzzahl maximale_warteschlangenlaenge = 0
    Ganzzahl zeitschritte = 0
    Ganzzahl durchlaufene_zeitschritte = 0

    SimulationsStats *p_statistik = malloc(sizeof(SimulationsStats))
    WENN p_statistik == NULL
        Ausgabe: "Fehler bei Speicherreservierung für p_statistik"
    ENDE WENN

    p_statistik->auslastung_pro_zeitschritt = auslastung_pro_zeitschritt
    p_statistik->warteschlange_pro_zeitschritt = warteschlange_pro_zeitschritt
    p_statistik->wartezeit_pro_zeitschritt = wartezeit_pro_zeitschritt
    p_statistik->maximale_auslastung = maximale_auslastung
    p_statistik->maximale_warteschlangenlaenge = maximale_warteschlangenlaenge
    p_statistik->zeitschritte = zeitschritte
    p_statistik->durchlaufene_zeitschritte = durchlaufene_zeitschritte
    GIB p_statistik
    */
}

void aktualisiere_groesse_statistik(SimulationsStats *p_statistik, int zeitschritte){
    /*Ganzzahl neue_groesse = p_statistik->zeitschritte + zeitschritte
    
    Fließkommazahl *zwischenspeicher_auslastung = realloc(p_statistik->auslastung_pro_zeitschritt, sizeof(Fließkommazahl) * neue_groesse)
    WENN zwischenspeicher_auslastung == NULL:
        Ausgabe: "Fehler beim anpassen von auslastung_pro_zeitschritt"
    ENDE WENN
    SONST 
        p_statistik->auslastung_pro_zeitschritt = zwischenspeicher_auslastung
    ENDE SONST

    Ganzzahl *zwischenspeicher_warteschlange = realloc(p_statistik->warteschlange_pro_zeitschritt, sizeof(Ganzzahl) * neue_groesse)
    WENN zwischenspeicher_warteschlange == NULL:
        Ausgabe: "Fehler beim anpassen von warteschlange_pro_zeitschritt"
    ENDE WENN
    SONST 
        p_statistik->warteschlange_pro_zeitschritt = zwischenspeicher_warteschlange
    ENDE SONST

    Ganzzahl *zwischenspeicher_wartezeit = realloc(p_statistik->wartezeit_pro_zeitschritt, sizeof(Ganzzahl) * neue_groesse)
    WENN zwischenspeicher_wartezeit == NULL:
        Ausgabe: "Fehler beim anpassen von wartezeit_pro_zeitschritt"
    ENDE WENN
    SONST 
        p_statistik->wartezeit_pro_zeitschritt = zwischenspeicher_wartezeit
    ENDE SONST
    p_statistik->zeitschritte = neue_groesse
}