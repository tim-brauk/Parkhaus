#include <stdio.h>
#include <assert.h>
#include "statistiken.h"
#include "parkhaus.h"

void test_init_statistik(){
    SimulationsStats *p_stats = init_statistik();

    assert(stats != NULL);
    assert(stats->auslastung_pro_zeitschritt != NULL);
    assert(stats->warteschlange_pro_zeitschritt != NULL);
    assert(stats->wartezeit_pro_zeitschritt != NULL);
    assert(stats->maximale_auslastung == 0.0f);
    assert(stats->maximale_warteschlangenlaenge == 0);
    assert(stats->zeitschritte == 0);
    assert(stats->durchlaufene_zeitschritte == 0);
    //Überprüfen, ob die Werte richtig initialisiert wurden
}

void test_init_statistik_pointer(){
    SimulationsStats *p_stats = init_statistik();

    assert(p_stats->p_auslastung_pro_zeitschritt != p_stats->p_warteschlange_pro_zeitschritt);
    assert(p_stats->p_auslastung_pro_zeitschritt != p_stats->p_wartezeit_pro_zeitschritt);
    assert(p_stats->p_warteschlange_pro_zeitschritt != p_stats->p_wartezeit_pro_zeitschritt);
    //Überprüfen, ob die Zeiger auf verschiedene Speicherbereiche zeigen
}

void test_aktualisiere_groesse_statistik_erweiterung(){
    SimulationsStats *p_stats = init_statistik();
    int zusätzliche_zeitschritte = 10;
    int gesamte_zeitschritte = p_stats->zeitschritte + zusätzliche_zeitschritte;

    aktualisiere_groesse_statistik(p_stats, gresamte_zeitschritte);

    assert(p_stats->zeitschritte == gesamte_zeitschritte);
    //Überprüfen, ob die Anzahl der Zeitschritte korrekt aktualisiert wurde
}

void test_aktualisiere_groesse_statistik_merhfacherweiterung(){
    SimulationsStats *p_stats = init_statistik();
    int zusätzliche_zeitschritte = 5;
    int gesamte_zeitschritte = 0;
    
    for(int i = 0; i < 3; i++){
        gesamte_zeitschritte = p_stats->zeitschritte + zusätzliche_zeitschritte;
        aktualisiere_groesse_statistik(p_stats, gesamte_zeitschritte);
        assert(p_stats->zeitschritte == gesamte_zeitschritte);
    }
    //Überprüfen, ob die Anzahl der Zeitschritte korrekt aktualisiert wurde, auch nach mehreren Erweiterungen
}

void test_berechne_aktuelle_auslastung_normal(){
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);

    p_parkhaus->belegte_plaetze = 5;
    float auslastung = berechne_aktuelle_auslastung(p_parkhaus);
    assert(auslastung == 50.0f);

    p_parkhaus->belegte_plaetze = 7;
    auslastung = berechne_aktuelle_auslastung(p_parkhaus);
    assert(auslastung == 70.0f);
    //Überprüfen, ob die Auslastung korrekt berechnet wird

    free(p_parkhaus);
}

void test_berechne_aktuelle_auslastung_randwerte(){
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);

    p_parkhaus->belegte_plaetze = 0;
    float auslastung = berechne_aktuelle_auslastung(p_parkhaus);
    assert(auslastung == 0.0f);

    p_parkhaus->belegte_plaetze = 10;
    auslastung = berechne_aktuelle_auslastung(p_parkhaus);
    assert(auslastung == 100.0f);
    //Überprüfen, ob die Auslastung korrekt berechnet wird, wenn das Parkhaus leer ist

    free(p_parkhaus);
}

void test_berechne_aktuelle_warteschlangenlaenge_normal(){
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);

    p_parkhaus->p_erster_in_der_warteschlange = init_kfz(p_parkhaus, 1, 60);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster = init_kfz(p_parkhaus, 2, 61);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster->p_naechster = init_kfz(p_parkhaus, 3, 62);
    //Erstellen einer Warteschlange mit 3 Fahrzeugen
    int warteschlangenlaenge = berechne_aktuelle_warteschlangenlaenge(p_parkhaus);
    assert(warteschlangenlaenge == 3);
    //Überprüfen, ob die Warteschlangenlänge korrekt berechnet wird

    free(p_parkhaus);
}

void test_berechne_aktuelle_warteschlangenlaenge_leer(){
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);

    int warteschlangenlaenge = berechne_aktuelle_warteschlangenlaenge(p_parkhaus);
    assert(warteschlangenlaenge == 0);
    //Überprüfen, ob die Warteschlangenlänge korrekt berechnet wird, wenn keine Fahrzeuge in der Warteschlange sind

    free(p_parkhaus);
}