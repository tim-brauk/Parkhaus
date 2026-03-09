#include <stdio.h>
#include <assert.h>
#include "statistiken.h"
#include "parkhaus.h"

void test_init_statistik(){
    SimulationsStats *p_stats = init_statistik();

    assert(p_stats != NULL);
    assert(p_stats->auslastung_pro_zeitschritt != NULL);
    assert(p_stats->warteschlange_pro_zeitschritt != NULL);
    assert(p_stats->wartezeit_pro_zeitschritt != NULL);
    assert(p_stats->maximale_auslastung == 0.0f);
    assert(p_stats->maximale_warteschlangenlaenge == 0);
    assert(p_stats->zeitschritte == 0);
    assert(p_stats->durchlaufene_zeitschritte == 0);
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

    aktualisiere_groesse_statistik(p_stats, gesamte_zeitschritte);

    assert(p_stats->zeitschritte == 10); //bei init ist zeitschritte 0, also sollte es nach der Erweiterung 10 sein
    //Überprüfen, ob die Anzahl der Zeitschritte korrekt aktualisiert wurde
}

void test_aktualisiere_groesse_statistik_merhfacherweiterung(){
    SimulationsStats *p_stats = init_statistik();
    int zusätzliche_zeitschritte = 5;
    int gesamte_zeitschritte = 0;
    
    for(int i = 0; i < 3; i++){
        gesamte_zeitschritte = p_stats->zeitschritte + zusätzliche_zeitschritte;
        aktualisiere_groesse_statistik(p_stats, gesamte_zeitschritte);
        assert(p_stats->zeitschritte == 15); //nach 3 Erweiterungen mit jeweils 5 zusätzlichen Zeitschritten sollte die Anzahl der Zeitschritte 15 sein
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

void test_berechne_aktuelle_wartezeit_normal(){
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);

    p_parkhaus->p_erster_in_der_warteschlange = init_kfz(p_parkhaus, 1, 60);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster = init_kfz(p_parkhaus, 2, 61);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster->p_naechster = init_kfz(p_parkhaus, 3, 62);
    //Erstellen einer Warteschlange mit 3 Fahrzeugen
    int zeitpunkt = 70;
    float wartezeit = berechne_aktuelle_wartezeit(p_parkhaus, zeitpunkt);
    assert(wartezeit == 9.0f); //(70-60) + (70-61) + (70-62)) / 3 = 9.0f
    //Überprüfen, ob die Wartezeit korrekt berechnet wird

    free(p_parkhaus);
}

void test_berechne_aktuelle_wartezeit_leer(){
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);

    int zeitpunkt = 70;
    float wartezeit = berechne_aktuelle_wartezeit(p_parkhaus, zeitpunkt);
    assert(wartezeit == 0.0f);
    //Überprüfen, ob die Wartezeit korrekt berechnet wird, wenn keine Fahrzeuge in der Warteschlange sind

    free(p_parkhaus);
}

void test_aktualisiere_maximale_auslastung_normal(){
    SimulationsStats *p_stats = init_statistik();
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);

    p_parkhaus->belegte_plaetze = 5;
    p_stats->maximale_auslastung = 30.0f;

    aktualisiere_maximale_auslastung(p_stats, p_parkhaus);
    
    assert(p_stats->maximale_auslastung == 50.0f);
    //Überprüfen, ob die maximale Auslastung korrekt aktualisiert wird

    free(p_stats);
}

void test_aktualisiere_maximale_auslastung_unveraendert(){
    SimulationsStats *p_stats = init_statistik();
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);

    p_parkhaus->belegte_plaetze = 3;
    p_stats->maximale_auslastung = 40.0f;

    aktualisiere_maximale_auslastung(p_stats, p_parkhaus);

    assert(p_stats->maximale_auslastung == 40.0f);
    //Überprüfen, ob die maximale Auslastung nicht verändert wird

    free(p_parkhaus);
    free(p_stats);
}

void test_aktualisiere_maximale_warteschlangenlaenge_normal(){
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);
    SimulationsStats *p_stats = init_statistik();

    p_stats->maximale_warteschlangenlaenge = 2;
    
    p_parkhaus->p_erster_in_der_warteschlange = init_kfz(p_parkhaus, 1, 60);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster = init_kfz(p_parkhaus, 2, 61);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster->p_naechster = init_kfz(p_parkhaus, 3, 62);
    //Erstellen einer Warteschlange mit 3 Fahrzeugen

    aktualisiere_maximale_warteschlangenlaenge(p_stats, p_parkhaus);
    assert(p_stats->maximale_warteschlangenlaenge == 3);
    //Überprüfen, ob die maximale Warteschlangenlänge korrekt aktualisiert wird

    free(p_parkhaus);
    free(p_stats);
}

void test_aktualisiere_maximale_warteschlangenlaenge_unveraendert(){
    Parkhaus *p_parkhaus = init_parkhaus(10, 40);
    SimulationsStats *p_stats = init_statistik();

    p_stats->maximale_warteschlangenlaenge = 4;

    p_parkhaus->p_erster_in_der_warteschlange = init_kfz(p_parkhaus, 1, 60);
    p_parkhaus->p_erster_in_der_warteschlange->p_naechster = init_kfz(p_parkhaus, 2, 61);
    //Erstellen einer Warteschlange mit 2 Fahrzeugen

    aktualisiere_maximale_warteschlangenlaenge(p_stats, p_parkhaus);
    assert(p_stats->maximale_warteschlangenlaenge == 4);
    //Überprüfen, ob die maximale Warteschlangenlänge nicht verändert wird

    free(p_parkhaus);
    free(p_stats);
}

void test_berechne_durchschnitt_auslastung(){
    SimulationsStats *p_stats = init_statistik();

    p_stats->zeitschritte = 3;
    p_stats->p_auslastung_pro_zeitschritt[0] = 13.2f;
    p_stats->p_auslastung_pro_zeitschritt[1] = 17.0f;
    p_stats->p_auslastung_pro_zeitschritt[2] = 25.0f;

    float durchschnitt = berechne_durchschnitt_auslastung(p_stats);
    assert(durchschnitt == 18.4f); //(13.2f + 17.0f + 25.0f) / 3 = 18.4f
    //Überprüfen, ob der Durchschnitt der Auslastung korrekt berechnet wird

    free(p_stats);
}

void test_berechne_durchschnitt_auslastung_keine_werte(){
    SimulationsStats *p_stats = init_statistik();

    p_stats->zeitschritte = 3;
    p_stats->p_auslastung_pro_zeitschritt[0] = 0.0f;
    p_stats->p_auslastung_pro_zeitschritt[1] = 0.0f;
    p_stats->p_auslastung_pro_zeitschritt[2] = 0.0f;

    float durchschnitt = berechne_durchschnitt_auslastung(p_stats);
    assert(durchschnitt == 0.0f);
    //Überprüfen, ob der Durchschnitt der Auslastung korrekt berechnet wird, auch wenn alle Werte 0 nicht

    free(p_stats);
}

void test_berechne_durchschnitt_warteschlangenlaenge(){
    SimulationsStats *p_stats = init_statistik();

    p_stats->zeitschritte = 4;
    p_stats->p_warteschlange_pro_zeitschritt[0] = 2;
    p_stats->p_warteschlange_pro_zeitschritt[1] = 3;
    p_stats->p_warteschlange_pro_zeitschritt[2] = 1;
    p_stats->p_warteschlange_pro_zeitschritt[3] = 4;

    float durchschnitt = berechne_durchschnitt_warteschlangenlaenge(p_stats);
    assert(durchschnitt == 2.5f); //(2 + 3 + 1 + 4) / 4 = 2.5f
    //Überprüfen, ob der Durchschnitt der Warteschlangenlänge korrekt berechnet wird

    free(p_stats);
}

void test_berechne_durchschnitt_warteschlangenlaenge_keine_werte(){
    SimulationsStats *p_stats = init_statistik();

    p_stats->zeitschritte = 4;
    p_stats->p_warteschlange_pro_zeitschritt[0] = 0;
    p_stats->p_warteschlange_pro_zeitschritt[1] = 0;
    p_stats->p_warteschlange_pro_zeitschritt[2] = 0;
    p_stats->p_warteschlange_pro_zeitschritt[3] = 0;

    float durchschnitt = berechne_durchschnitt_warteschlangenlaenge(p_stats);
    assert(durchschnitt == 0.0f);
    //Überprüfen, ob der Durchschnitt der Warteschlangenlänge korrekt berechnet wird, auch wenn alle Werte 0 nicht

    free(p_stats);
}

void test_berechne_durchschnittliche_wartezeit(){
    SimulationsStats *p_stats = init_statistik();

    p_stats->zeitschritte = 3;
    p_stats->p_wartezeit_pro_zeitschritt[0] = 5.0f;
    p_stats->p_wartezeit_pro_zeitschritt[1] = 10.0f;
    p_stats->p_wartezeit_pro_zeitschritt[2] = 15.0f;

    float durchschnitt = berechne_durchschnittliche_wartezeit(p_stats);
    assert(durchschnitt == 10.0f); //(5.0f + 10.0f + 15.0f) / 3 = 10.0f
    //Überprüfen, ob der Durchschnitt der Wartezeit korrekt berechnet wird

    free(p_stats);
}


//Für die Ausgabe sehe ich es nicht als nötig eine Testfunktionen zu schreiben


int main(){
    test_init_statistik();
    test_init_statistik_pointer();
    test_aktualisiere_groesse_statistik_erweiterung();
    test_aktualisiere_groesse_statistik_merhfacherweiterung();
    test_berechne_aktuelle_auslastung_normal();
    test_berechne_aktuelle_auslastung_randwerte();
    test_berechne_aktuelle_warteschlangenlaenge_normal();
    test_berechne_aktuelle_warteschlangenlaenge_leer();
    test_berechne_aktuelle_wartezeit_normal();
    test_berechne_aktuelle_wartezeit_leer();
    test_aktualisiere_maximale_auslastung_normal();
    test_aktualisiere_maximale_auslastung_unveraendert();
    test_aktualisiere_maximale_warteschlangenlaenge_normal();
    test_aktualisiere_maximale_warteschlangenlaenge_unveraendert();
    test_berechne_durchschnitt_auslastung();
    test_berechne_durchschnitt_warteschlangenlaenge();  
    test_berechne_durchschnittliche_wartezeit();
    return 0;
}