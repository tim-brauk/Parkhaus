#include "kfz.h"
#include "parkhaus.h"
#include "parkvorgang.h"    
#include "simulation.h"
#include "warteschlange.h"
#include "statistiken.h"

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

    // Zufallszahlengenerator initialisieren
    srand(seed)

    // Simulationsparameter initialisieren
    SimulationsParameter *p_simulationsparameter = init_simulationsparameter(anzahl_parkplaetze, maximale_parkdauer, simulations_dauer, seed, wahrscheinlichkeit_neues_kfz)
    WENN p_simulationsparameter == NULL:
        Ausgabe: "Fehler bei der Initialisierung der Simulationsparameter."
        GIB 1
    ENDE WENN

    // Parkhaus initialisieren
    Parkhaus *p_parkhaus = init_parkhaus(p_simulationsparameter->maximale_parkdauer, p_simulationsparameter->anzahl_parkplaetze)
    WENN p_parkhaus == NULL:
        Ausgabe: "Fehler bei der Initialisierung des Parkhauses."
        GIB 1
    ENDE WENN

    // Statistiken initialisieren
    SimulationsStats *p_statistik = init_statistik()
    WENN p_statistik == NULL:
        Ausgabe: "Fehler bei der Initialisierung der Statistiken."
        GIB 1
    ENDE WENN

    // Datei oeffnen
    Datei *p_datei = fopen("simulation_ausgabe.txt", "w")
    WENN p_datei == NULL:
        Ausgabe: "Fehler beim Oeffnen der Ausgabedatei"
        GIB 1
    ENDE WENN

    // Simulationsschleife
    SOLANGE zeitpunkt < simulations_dauer:

        // Nutzer fragen ob Parameter geaendert werden sollen
        Ausgabe: "Parameter aendern? (1 = ja, 0 = nein)"
        Eingabe: aendern
        WENN aendern == 1:
            Eingabe: anzahl_parkplaetze
            SOLANGE anzahl_parkplaetze <= 0:
                Ausgabe: "Ungueltige Eingabe. Anzahl Parkplaetze muss groesser als 0 sein: "
                Eingabe: anzahl_parkplaetze
            ENDE SOLANGE
            Eingabe: maximale_parkdauer
            SOLANGE maximale_parkdauer <= 0:
                Ausgabe: "Ungueltige Eingabe. Maximale Parkdauer muss groesser als 0 sein: "
                Eingabe: maximale_parkdauer
            ENDE SOLANGE
            Eingabe: simulations_dauer
            SOLANGE simulations_dauer <= zeitpunkt:
                Ausgabe: "Ungueltige Eingabe. Simulationsdauer muss groesser als aktueller Zeitpunkt sein: "
                Eingabe: simulations_dauer
            ENDE SOLANGE
            Eingabe: seed
            Eingabe: wahrscheinlichkeit_neues_kfz
            SOLANGE wahrscheinlichkeit_neues_kfz < 0 ODER wahrscheinlichkeit_neues_kfz > 1:
                Ausgabe: "Ungueltige Eingabe. Wahrscheinlichkeit muss zwischen 0.0 und 1.0 liegen: "
                Eingabe: wahrscheinlichkeit_neues_kfz
            ENDE SOLANGE
            aktualisiere_parameter(p_parkhaus, p_simulationsparameter, anzahl_parkplaetze, maximale_parkdauer, simulations_dauer, wahrscheinlichkeit_neues_kfz, seed)
        ENDE WENN

        // Zeitschritt simulieren
        simuliere_zeitabschnitt(p_parkhaus, p_simulationsparameter, &id, &zeitpunkt)

        // Statistiken fuer diesen Zeitschritt aktualisieren
        aktualisiere_maximale_auslastung(p_statistik, p_parkhaus)
        aktualisiere_maximale_warteschlangenlaenge(p_statistik, p_parkhaus)
        p_statistik->auslastung_pro_zeitschritt[p_statistik->durchlaufene_zeitschritte] = berechne_aktuelle_auslastung(p_parkhaus)
        p_statistik->warteschlange_pro_zeitschritt[p_statistik->durchlaufene_zeitschritte] = berechne_aktuelle_warteschlangenlaenge(p_parkhaus)
        p_statistik->durchlaufene_zeitschritte = p_statistik->durchlaufene_zeitschritte + 1

        //Statistiken in der Konsole ausgeben 
        ausgabe_statistiken(p_statistik)


        // Statistiken des aktuellen Zeitschritts in Datei und Konsole schreiben
        fprintf(p_datei, "Zeitschritt: %d\n", p_statistik->durchlaufene_zeitschritte)
        fprintf(p_datei, "Aktuelle Auslastung: %.2f%%\n", berechne_aktuelle_auslastung(p_parkhaus))
        fprintf(p_datei, "Durchschnittliche Auslastung: %.2f%%\n", berechne_durchschnitt_auslastung(p_statistik))
        fprintf(p_datei, "Durchschnittliche Warteschlangenlaenge: %.2f\n", berechne_durchschnitt_warteschlangenlaenge(p_statistik))
        fprintf(p_datei, "Maximale Auslastung: %.2f%%\n", p_statistik->maximale_auslastung)
        fprintf(p_datei, "Maximale Warteschlangenlaenge: %d\n", p_statistik->maximale_warteschlangenlaenge)
        fprintf(p_datei, "Durchschnittliche Wartezeit: %.2f\n", berechne_durchschnittliche_wartezeit(p_statistik))

    ENDE SOLANGE

    // Finale Statistiken in Datei schreiben
    fprintf(p_datei, "\n--- Finale Statistiken ---\n")
    fprintf(p_datei, "Durchschnittliche Auslastung: %.2f%%\n", berechne_durchschnitt_auslastung(p_statistik))
    fprintf(p_datei, "Maximale Auslastung: %.2f%%\n", p_statistik->maximale_auslastung)
    fprintf(p_datei, "Maximale Warteschlangenlaenge: %d\n", p_statistik->maximale_warteschlangenlaenge)
    fprintf(p_datei, "Durchschnittliche Wartezeit: %.2f\n", berechne_durchschnittliche_wartezeit(p_statistik))
    fprintf(p_datei, "Durchschnittliche Warteschlangenlaenge: %.2f\n", berechne_durchschnitt_warteschlangenlaenge(p_statistik))
    fclose(p_datei)

    // Speicher freigeben
    free(p_statistik->auslastung_pro_zeitschritt)
    free(p_statistik->warteschlange_pro_zeitschritt)
    free(p_statistik->wartezeit_pro_zeitschritt)
    free(p_statistik)
    free(p_parkhaus->p_parkplaetze)
    free(p_parkhaus)
    free(p_simulationsparameter)
    GIB 0
}