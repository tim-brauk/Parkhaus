#include "kfz.h"
#include "parkhaus.h"
#include "parkvorgang.h"    
#include "simulation.h"
#include "warteschlange.h"

FUNKTION main
{
    //variablen Deklaration
    Ganzzahl id = 0
    Ganzzahl zeitpunkt = 0
    Ganzzahl  = 0
    Ganzzahl maximale_parkdauer = 0
    float simulations_dauer = 0
    Ganzzahl seed = 0
    float wahscheinlichkeit_neues_kfz = 0

    //Parameter über Terminal eingeben
    Eingabe: anzahl_parkplaetze
    Eingabe: maximale_parkdauer
    Eingabe: simuations_dauer
    Eingabe: seed
    Eingabe: wahscheinlichkeit_neues_kfz

    //zufallszahlengenerator initialisieren
    srand(seed);
    //initalisieren Parkhaus/simulation
    Simulationsparameter *p_simulationsparameter = init_simulationsparameter(anzahl_parkplaetze, maximale_parkdauer, simulations_dauer, seed, wahscheinlichkeit_neues_kfz);
    Parkhaus *p_parkhaus = init_parkhaus(p_simulationsparameter->anzahl_parkplaetze);

    // Simulationsschleife:
    SOLANGE zeitpunkt < simulations_dauer:
        simuliere_zeitabschnitt(p_parkhaus, p_simulationsparameter, &id, &zeitpunkt)
        // Statisken werden eingefügt sobald sie klar sind.
    ENDE SOLANGE 
     // Speicher freigeben:
    free(p_parkhaus->p_parkplaetze)
    free(p_parkhaus)
    free(p_simulationsparameter)
    GIB 0 

}