#include "kfz.h"
#include "parkhaus.h"
#include "parkvorgang.h"    
#include "simulation.h"
#include "warteschlange.h"
#include  "statisken.h"

FUNKTION main
{
    // Variablen Deklaration
    Ganzzahl id = 0
    Ganzzahl zeitpunkt = 0
    Ganzzahl anzahl_parkplaetze = 0
    Ganzzahl maximale_parkdauer = 0
    float simulations_dauer = 0
    Ganzzahl seed = 0
    float wahrscheinlichkeit_neues_kfz = 0
    Ganzzahl aendern = 0

    // Parameter ueber Terminal eingeben mit Sicherheitsabfragen
    Ausgabe: "Anzahl Parkplaetze eingeben: "
    Eingabe: anzahl_parkplaetze
    SOLANGE anzahl_parkplaetze <= 0:
        Ausgabe: "Ungueltige Eingabe. Anzahl Parkplaetze muss groesser als 0 sein: "
        Eingabe: anzahl_parkplaetze
    ENDE SOLANGE

    Ausgabe: "Maximale Parkdauer eingeben (in Stunden): "
    Eingabe: maximale_parkdauer
    SOLANGE maximale_parkdauer <= 0:
        Ausgabe: "Ungueltige Eingabe. Maximale Parkdauer muss groesser als 0 sein: "
        Eingabe: maximale_parkdauer
    ENDE SOLANGE

    Ausgabe: "Simulationsdauer eingeben (in Stunden): "
    Eingabe: simulations_dauer
    SOLANGE simulations_dauer <= 0:
        Ausgabe: "Ungueltige Eingabe. Simulationsdauer muss groesser als 0 sein: "
        Eingabe: simulations_dauer
    ENDE SOLANGE

    Ausgabe: "Seed eingeben: "
    Eingabe: seed

    Ausgabe: "Ankunftswahrscheinlichkeit neues Kfz eingeben (0.0 - 1.0): "
    Eingabe: wahrscheinlichkeit_neues_kfz
    SOLANGE wahrscheinlichkeit_neues_kfz < 0 ODER wahrscheinlichkeit_neues_kfz > 1:
        Ausgabe: "Ungueltige Eingabe. Wahrscheinlichkeit muss zwischen 0.0 und 1.0 liegen: "
        Eingabe: wahrscheinlichkeit_neues_kfz
    ENDE SOLANGE
    
    //zufallszahlengenerator initialisieren
    srand(seed);

    // Parkhaus und Simulationsparameter initialisieren
    Simulationsparameter *p_simulationsparameter = init_simulationsparameter(anzahl_parkplaetze, maximale_parkdauer, simulations_dauer, seed, wahrscheinlichkeit_neues_kfz)
    Parkhaus *p_parkhaus = init_parkhaus(p_simulationsparameter->maximale_parkdauer, p_simulationsparameter->anzahl_parkplaetze)

    // Simulationsschleife
    SOLANGE zeitpunkt < simulations_dauer:

        // Nutzer fragen ob Parameter geaendert werden sollen
        Ausgabe: "Parameter aendern? (1 = ja, 0 = nein)"
        Eingabe: aendern
        WENN aendern == 1:
            Eingabe: anzahl_parkplaetze
            Eingabe: maximale_parkdauer
            Eingabe: simulations_dauer
            Eingabe: seed
            Eingabe: wahrscheinlichkeit_neues_kfz
            aktualisiere_parameter(p_parkhaus, p_simulationsparameter, anzahl_parkplaetze, maximale_parkdauer, simulations_dauer, wahrscheinlichkeit_neues_kfz, seed)
        ENDE WENN

        simuliere_zeitabschnitt(p_parkhaus, p_simulationsparameter, &id, &zeitpunkt)
        // Statistiken werden eingefuegt sobald sie klar sind.

    ENDE SOLANGE

    // Speicher freigeben
    free(p_parkhaus->p_parkplaetze)
    free(p_parkhaus)
    free(p_simulationsparameter)
    GIB 0
}