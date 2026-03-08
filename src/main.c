#include "kfz.h"
#include "parkhaus.h"
#include "parkvorgang.h"    
#include "simulation.h"
#include "warteschlange.h"
#include "statistiken.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int id = 0;
    int zeitpunkt = 0;
    int anzahl_parkplaetze = 0;
    int maximale_parkdauer = 0;
    int seed = 0;
    int aendern = 0;
    float simulations_dauer = 0.0f;
    float wahrscheinlichkeit_neues_kfz = 0.0f;
    
    printf("Anzahl Parkplaetze eingeben: ");
    scanf("%d", &anzahl_parkplaetze);

    while(anzahl_parkplaetze <= 0)
    {
        printf("Ungueltige Eingabe. Anzahl Parkplaetze muss groesser als 0 sein: ");
        scanf("%d", &anzahl_parkplaetze);
    }

    printf("Maximale Parkdauer eingeben (in Stunden): ");
    scanf("%d", &maximale_parkdauer);

    while(maximale_parkdauer <= 0)
    {
        printf("Ungueltige Eingabe. Maximale Parkdauer muss groesser als 0 sein: ");
        scanf("%d", &maximale_parkdauer);
    }

    printf("Simulationsdauer eingeben (in Stunden): ");
    scanf("%f", &simulations_dauer);

    while(simulations_dauer <= 0.0f)
    {
        printf("Ungueltige Eingabe. Simulationsdauer muss groesser als 0 sein: ");
        scanf("%f", &simulations_dauer);
    }

    printf("Seed eingeben: ");
    scanf("%d", &seed);

    printf("Ankunftswahrscheinlichkeit neues Kfz eingeben (0.0 - 1.0): ");
    scanf("%f", &wahrscheinlichkeit_neues_kfz);

    while(wahrscheinlichkeit_neues_kfz < 0.0f || wahrscheinlichkeit_neues_kfz > 1.0f)
    {
        printf("Ungueltige Eingabe. Wahrscheinlichkeit muss zwischen 0.0 und 1.0 liegen: ");
        scanf("%f", &wahrscheinlichkeit_neues_kfz);
    }

    srand(seed);

    Simulationsparameter *p_simulationsparameter =
        init_simulationsparameter(
            anzahl_parkplaetze,
            maximale_parkdauer,
            simulations_dauer,
            seed,
            wahrscheinlichkeit_neues_kfz);

    if(p_simulationsparameter == NULL)
    {
        printf("Fehler bei der Initialisierung der Simulationsparameter.\n");
        return 1;
    }

    Parkhaus *p_parkhaus =
        init_parkhaus(
            p_simulationsparameter->anzahl_parkplaetze,
            p_simulationsparameter->maximale_parkdauer,
            p_simulationsparameter->simulations_dauer);

    if(p_parkhaus == NULL)
    {
        printf("Fehler bei der Initialisierung des Parkhauses.\n");
        return 1;
    }

    SimulationsStats *p_statistik = init_statistik();

    if(p_statistik == NULL)
    {
        printf("Fehler bei der Initialisierung der Statistiken.\n");
        return 1;
    }

    FILE *p_datei = fopen("simulation_ausgabe.txt", "w");

    if(p_datei == NULL)
    {
        printf("Fehler beim Oeffnen der Ausgabedatei\n");
        return 1;
    }

    while(zeitpunkt < simulations_dauer)
    {
        printf("Parameter aendern? (1 = ja, 0 = nein)\n");
        scanf("%d", &aendern);

        if(aendern == 1)
        {
            scanf("%d", &anzahl_parkplaetze);

            while(anzahl_parkplaetze <= 0)
            {
                printf("Ungueltige Eingabe. Anzahl Parkplaetze muss groesser als 0 sein: ");
                scanf("%d", &anzahl_parkplaetze);
            }

            scanf("%d", &maximale_parkdauer);

            while(maximale_parkdauer <= 0)
            {
                printf("Ungueltige Eingabe. Maximale Parkdauer muss groesser als 0 sein: ");
                scanf("%d", &maximale_parkdauer);
            }

            scanf("%f", &simulations_dauer);

            while(simulations_dauer <= zeitpunkt)
            {
                printf("Ungueltige Eingabe. Simulationsdauer muss groesser als aktueller Zeitpunkt sein: ");
                scanf("%f", &simulations_dauer);
            }

            scanf("%d", &seed);
            scanf("%f", &wahrscheinlichkeit_neues_kfz);

            while(wahrscheinlichkeit_neues_kfz < 0.0f || wahrscheinlichkeit_neues_kfz > 1.0f)
            {
                printf("Ungueltige Eingabe. Wahrscheinlichkeit muss zwischen 0.0 und 1.0 liegen: ");
                scanf("%f", &wahrscheinlichkeit_neues_kfz);
            }

            aktualisiere_parameter(
                p_parkhaus,
                p_simulationsparameter,
                anzahl_parkplaetze,
                maximale_parkdauer,
                simulations_dauer,
                wahrscheinlichkeit_neues_kfz,
                seed);
        }

            simuliere_zeitabschnitt(
                p_parkhaus,
                p_simulationsparameter,
                &id,
                &zeitpunkt);

        fprintf(p_datei, "Zeitschritt: %d\n", p_statistik->durchlaufene_zeitschritte);
        fprintf(p_datei, "Durchschnittliche Auslastung: %.2f%%\n", berechne_durchschnitt_auslastung(p_statistik));
        fprintf(p_datei, "Durchschnittliche Warteschlangenlaenge: %.2f\n", berechne_durchschnitt_warteschlangenlaenge(p_statistik));
        fprintf(p_datei, "Maximale Auslastung: %.2f%%\n", p_statistik->maximale_auslastung);
        fprintf(p_datei, "Maximale Warteschlangenlaenge: %d\n", p_statistik->maximale_warteschlangenlaenge);
        fprintf(p_datei, "Durchschnittliche Wartezeit: %.2f\n", berechne_durchschnittliche_wartezeit(p_statistik));
    }

    fprintf(p_datei, "\n--- Finale Statistiken ---\n");
    fprintf(p_datei, "Durchschnittliche Auslastung: %.2f%%\n", berechne_durchschnitt_auslastung(p_statistik));
    fprintf(p_datei, "Maximale Auslastung: %.2f%%\n", p_statistik->maximale_auslastung);
    fprintf(p_datei, "Maximale Warteschlangenlaenge: %d\n", p_statistik->maximale_warteschlangenlaenge);
    fprintf(p_datei, "Durchschnittliche Wartezeit: %.2f\n", berechne_durchschnittliche_wartezeit(p_statistik));
    fprintf(p_datei, "Durchschnittliche Warteschlangenlaenge: %.2f\n", berechne_durchschnitt_warteschlangenlaenge(p_statistik));
    fclose(p_datei);

    free(p_statistik->auslastung_pro_zeitschritt);
    free(p_statistik->warteschlange_pro_zeitschritt);
    free(p_statistik->wartezeit_pro_zeitschritt);
    free(p_statistik);
    free(p_parkhaus->p_parkplaetze);
    free(p_parkhaus);
    free(p_simulationsparameter);
    return 0;
}