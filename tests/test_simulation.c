#include <assert.h>
#include <stdlib.h>
#include "simulation.h"
#include "parkhaus.h"
#include "kfz.h"

void test_init_simulationsparameter()
{
    Simulationsparameter *p_simulationsparameter = init_simulationsparameter(10, 5, 10, 7, 0.6f);
    if(p_simulationsparameter == NULL)
    {
        free(p_simulationsparameter);
        return;
    }

    assert(p_simulationsparameter != NULL);
    assert(p_simulationsparameter->anzahl_parkplaetze != NULL);
    assert(p_simulationsparameter->maximale_parkdauer != NULL);
    assert(p_simulationsparameter->simulations_dauer == 10);
    assert(p_simulationsparameter->seed != NULL);
    assert(p_simulationsparameter->wahrscheinlichkeit_neues_kfz == 0.6f);

    free(p_simulationsparameter);
}

void test_init_simulationsparameter_pointer()
{
    Simulationsparameter *p_simulationsparameter = init_simulationsparameter(5, 40, 100, 42, 0.5f);
    if(p_simulationsparameter == NULL)
    {
        free(p_simulationsparameter);
        return;
    }

    assert((void*)p_simulationsparameter->anzahl_parkplaetze != (void*)p_simulationsparameter->maximale_parkdauer);
    assert((void*)p_simulationsparameter->anzahl_parkplaetze != (void*)p_simulationsparameter->seed);
    assert(p_simulationsparameter->anzahl_parkplaetze != p_simulationsparameter->wahrscheinlichkeit_neues_kfz);
    //Überprüfen, ob die Zeiger auf verschiedene Speicherbereiche zeigen
}

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
    
    int id = 1;
    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, &id, 10); //Kfz mit ID 1 und Einfahrtzeitpunkt 10
    p_parkhaus->p_parkplaetze[0].belegt = 1;
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, &id, 20); //Kfz mit ID 2 und Einfahrtzeitpunkt 20
    p_parkhaus->p_parkplaetze[1].belegt = 1;
    p_parkhaus->p_parkplaetze[2].p_kfz = init_kfz(p_parkhaus, &id, 30); //Kfz mit ID 3 und Einfahrtzeitpunkt 30
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
    
    int id = 1;
    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, &id, 10); //Kfz mit ID 1 und Einfahrtzeitpunkt 10
    p_parkhaus->p_parkplaetze[0].belegt = 1;
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, &id, 20); //Kfz mit ID 2 und Einfahrtzeitpunkt 20
    p_parkhaus->p_parkplaetze[1].belegt = 1;
    p_parkhaus->p_parkplaetze[2].p_kfz = init_kfz(p_parkhaus, &id, 30); //Kfz mit ID 3 und Einfahrtzeitpunkt 30
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

void test_aktualisiere_parameter_parkplaetze_erhoehen()
{
    Parkhaus *p_parkhaus = init_parkhaus(3, 10);
    Simulationsparameter *p_simulationsparameter = malloc(sizeof(Simulationsparameter));
    if(p_simulationsparameter == NULL) {
        free(p_parkhaus->p_parkplaetze);
        free(p_parkhaus);
        return;
    }

    p_simulationsparameter->anzahl_parkplaetze = 3;
    p_simulationsparameter->maximale_parkdauer = 10;
    p_simulationsparameter->simulations_dauer = 30;
    p_simulationsparameter->seed = 1;
    p_simulationsparameter->wahrscheinlichkeit_neues_kfz = 0.5;

    aktualisiere_parameter(p_parkhaus, p_simulationsparameter, 6, 10, 30, 0.5f, 1);

    assert(p_parkhaus->anzahl_parkplaetze == 6);
    assert(p_parkhaus->p_parkplaetze[3].belegt == 0); // Neue Parkplätze leer initialisiert
    assert(p_parkhaus->p_parkplaetze[4].belegt == 0);
    assert(p_parkhaus->p_parkplaetze[5].belegt == 0);
    assert(p_parkhaus->p_parkplaetze[3].p_kfz  == NULL);
    assert(p_parkhaus->p_parkplaetze[4].p_kfz  == NULL);
    assert(p_parkhaus->p_parkplaetze[5].p_kfz  == NULL);

    free(p_simulationsparameter);
    free(p_parkhaus->p_parkplaetze);
    free(p_parkhaus);
}

void test_aktualisiere_parameter_belegte_parkplaetze_verringern()
{
    Parkhaus *p_parkhaus = init_parkhaus(5, 40);
    Simulationsparameter *p_simulationsparameter = malloc(sizeof(Simulationsparameter));
    if(p_simulationsparameter == NULL) {
        free(p_parkhaus->p_parkplaetze);
        free(p_parkhaus);
        return;
    }

    p_simulationsparameter->anzahl_parkplaetze = 5;
    p_simulationsparameter->maximale_parkdauer = 40;
    p_simulationsparameter->simulations_dauer = 100;
    p_simulationsparameter->seed = 42;
    p_simulationsparameter->wahrscheinlichkeit_neues_kfz = 0.5;

    p_parkhaus->p_parkplaetze[3].p_kfz = init_kfz(p_parkhaus, 1, 10); // Parkplatz 3 belegen
    p_parkhaus->p_parkplaetze[3].belegt = 1;
    p_parkhaus->p_parkplaetze[4].p_kfz = init_kfz(p_parkhaus, 2, 20); // Parkplatz 4 belegen
    p_parkhaus->p_parkplaetze[4].belegt = 1;
    p_parkhaus->belegte_parkplaetze = 2;

    aktualisiere_parameter(p_parkhaus, p_simulationsparameter, 3, 40, 100, 0.5f, 42);

    assert(p_parkhaus->anzahl_parkplaetze == 3);
    assert(p_parkhaus->belegte_parkplaetze == 0); // Beide KFZ aus Parkplätzen entfernt
    assert(p_parkhaus->p_erstes_kfz_in_der_warteschlange != NULL); // KFZ in Warteschlange gelandet

    free(p_simulationsparameter);
    free(p_parkhaus->p_parkplaetze);
    free(p_parkhaus);
}

int main()
{
    test_init_simulationsparameter();
    test_init_simulationsparameter_pointer();
    test_simuliere_simuliere_zeitabschnitt();
    test_simuliere_simuliere_zeitabschnitt_kfz_entfernt();
    test_aktualisiere_parameter_parkplaetze_erhoehen();
    test_aktualisiere_parameter_belegte_parkplaetze_verringern();
    return 0;
}