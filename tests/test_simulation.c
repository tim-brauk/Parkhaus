#include <assert.h>
#include <stdlib.h>
#include "simulation.h"
#include "parkhaus.h"
#include "kfz.h"

void test_simuliere_simuliere_zeitabschnitt()
{
    Parkhaus *p_parkhaus = init_parkhaus(3, 40); //Erstellen eines Parkhauses mit 3 Parkplätzen und einer maximalen Parkdauer von 40
    SimulationsStats *p_statistik = init_statistik();
    Simulationsparameter *p_simulationsparameter = malloc(sizeof(Simulationsparameter)); //Erstellen eines Simulationsparameters
    if(p_simulationsparameter == NULL) {
        free(p_parkhaus);
        return; // Fehlerbehandlung für malloc-Fehlschlag
    }
    p_simulationsparameter->anzahl_parkplaetze = 3;
    p_simulationsparameter->maximale_parkdauer = 40;
    p_simulationsparameter->simulations_dauer = 100;
    p_simulationsparameter->seed = 42;
    p_simulationsparameter->wahrscheinlichkeit_neues_kfz = 0.5;
    
    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, 1, 10); //Kfz mit ID 1 und Einfahrtzeitpunkt 10
    p_parkhaus->p_parkplaetze[0].belegt = 1;
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, 2, 20); //Kfz mit ID 2 und Einfahrtzeitpunkt 20
    p_parkhaus->p_parkplaetze[1].belegt = 1;
    p_parkhaus->p_parkplaetze[2].p_kfz = init_kfz(p_parkhaus, 3, 30); //Kfz mit ID 3 und Einfahrtzeitpunkt 30
    p_parkhaus->p_parkplaetze[2].belegt = 1;
    p_parkhaus->belegte_parkplaetze = 3;
    //Parkhaus mit 3 belegten Parkplätzen

    p_parkhaus->p_parkplaetze[0].p_kfz->verbleibende_parkdauer = 5; //Setzt die verbleibende Parkzeit des Kfz auf 5
    p_parkhaus->p_parkplaetze[1].p_kfz->verbleibende_parkdauer = 15; //Setzt die verbleibende Parkzeit des Kfz auf 15
    p_parkhaus->p_parkplaetze[2].p_kfz->verbleibende_parkdauer = 25; //Setzt die verbleibende Parkzeit des Kfz auf 25

    int id = 4;
    int zeitpunkt = 0;
    simuliere_zeitabschnitt(p_parkhaus, p_simulationsparameter, p_statistik, &id, &zeitpunkt); //Simuliert einen Zeitabschnitt

    assert(p_parkhaus->p_parkplaetze[0].p_kfz->verbleibende_parkdauer == 4);
    assert(p_parkhaus->p_parkplaetze[1].p_kfz->verbleibende_parkdauer == 14);
    assert(p_parkhaus->p_parkplaetze[2].p_kfz->verbleibende_parkdauer == 24); //Überprüft, ob die verbleibende Parkzeit jedes Kfz um 1 reduziert wurde
    assert(p_parkhaus->belegte_parkplaetze == 3); //Überprüft, ob die Anzahl der belegten Parkplätze unverändert geblieben ist
    assert(zeitpunkt == 1); //Überprüft, ob der Zeitpunkt um 1 erhöht wurde

    free(p_simulationsparameter);
    free(p_parkhaus->p_parkplaetze[0].p_kfz);
    free(p_parkhaus->p_parkplaetze[1].p_kfz);
    free(p_parkhaus->p_parkplaetze[2].p_kfz);
    free(p_parkhaus->p_parkplaetze);
    free(p_parkhaus);
    free(p_statistik->p_auslastung_pro_zeitschritt);
    free(p_statistik->p_warteschlange_pro_zeitschritt);
    free(p_statistik->p_wartezeit_pro_zeitschritt);
    free(p_statistik);
}

void test_simuliere_simuliere_zeitabschnitt_kfz_entfernt()
{
    Parkhaus *p_parkhaus = init_parkhaus(3, 40); //Erstellen eines Parkhauses mit 3 Parkplätzen und einer maximalen Parkdauer von 40
    SimulationsStats *p_statistik = init_statistik();
    Simulationsparameter *p_simulationsparameter = malloc(sizeof(Simulationsparameter)); //Erstellen eines Simulationsparameters
    if(p_simulationsparameter == NULL) {
        free(p_parkhaus);
        return; // Fehlerbehandlung für malloc-Fehlschlag
    }
    p_simulationsparameter->anzahl_parkplaetze = 3;
    p_simulationsparameter->maximale_parkdauer = 40;
    p_simulationsparameter->simulations_dauer = 100;
    p_simulationsparameter->seed = 42;
    p_simulationsparameter->wahrscheinlichkeit_neues_kfz = 0.5;
    
    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, 1, 10); //Kfz mit ID 1 und Einfahrtzeitpunkt 10
    p_parkhaus->p_parkplaetze[0].belegt = 1;
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, 2, 20); //Kfz mit ID 2 und Einfahrtzeitpunkt 20
    p_parkhaus->p_parkplaetze[1].belegt = 1;
    p_parkhaus->p_parkplaetze[2].p_kfz = init_kfz(p_parkhaus, 3, 30); //Kfz mit ID 3 und Einfahrtzeitpunkt 30
    p_parkhaus->p_parkplaetze[2].belegt = 1;
    p_parkhaus->belegte_parkplaetze = 3;
    //Parkhaus mit 3 belegten Parkplätzen

    p_parkhaus->p_parkplaetze[0].p_kfz->verbleibende_parkdauer = 0; //Setzt die verbleibende Parkzeit des Kfz auf 0, damit es entfernt wird
    p_parkhaus->p_parkplaetze[1].p_kfz->verbleibende_parkdauer = 15;
    p_parkhaus->p_parkplaetze[2].p_kfz->verbleibende_parkdauer = 25;

    int id = 4;
    int zeitpunkt = 0;

    simuliere_zeitabschnitt(p_parkhaus, p_simulationsparameter, p_statistik, &id, &zeitpunkt); //Simuliert einen Zeitabschnitt

    assert(p_parkhaus->p_parkplaetze[0].p_kfz == NULL); //Überprüft, ob das Kfz mit der überschrittenen Parkzeit entfernt wurde
    assert(p_parkhaus->p_parkplaetze[1].p_kfz->verbleibende_parkdauer == 14);
    assert(p_parkhaus->p_parkplaetze[2].p_kfz->verbleibende_parkdauer == 24); //Überprüft, ob die verbleibende Parkzeit der anderen Kfz um 1 reduziert wurde
    assert(p_parkhaus->belegte_parkplaetze == 2); //Überprüft, ob die Anzahl der belegten Parkplätze um 1 reduziert wurde
    assert(zeitpunkt == 1); //Überprüft, ob der Zeitpunkt um 1 erhöht wurde

    free(p_simulationsparameter);
    free(p_parkhaus->p_parkplaetze[1].p_kfz);
    free(p_parkhaus->p_parkplaetze[2].p_kfz);
    free(p_parkhaus->p_parkplaetze);
    free(p_parkhaus);
    free(p_statistik->p_auslastung_pro_zeitschritt);
    free(p_statistik->p_warteschlange_pro_zeitschritt);
    free(p_statistik->p_wartezeit_pro_zeitschritt);
    free(p_statistik);
}

int main()
{
    test_simuliere_simuliere_zeitabschnitt();
    test_simuliere_simuliere_zeitabschnitt_kfz_entfernt();
    return 0;
}