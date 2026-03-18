#include <assert.h>
#include <stdlib.h>
#include "parkvorgang.h"
#include "parkhaus.h"
#include "kfz.h"

void test_fuege_kfz_hinzu_leer()
{
    Parkhaus *p_parkhaus = init_parkhaus(5, 40); //Erstellen eines Parkhauses mit 5 Parkplätzen und einer maximalen Parkdauer von 40 
    int id = 1;
    Kfz *p_kfz = init_kfz(p_parkhaus, &id, 60); //Test Kfz erhält die ID 1 und die einfahrtzeitpunkt von 60
    
    fuege_kfz_hinzu(p_parkhaus, p_kfz); //Fügt das Kfz zum Parkhaus hinzu
    
    assert(p_parkhaus->belegte_parkplaetze == 1); //Überprüft, ob das Kfz einen Parkplatz zugewiesen bekommen hat
    
    for(int i = 0; i < p_parkhaus->anzahl_parkplaetze; i++)
    {
        if(p_parkhaus->p_parkplaetze[i].belegt)
        {
            assert(p_parkhaus->p_parkplaetze[i].p_kfz == p_kfz); //Überprüft, ob das Kfz auch im Parkhaus angekommen ist
        }
    }
    
    free(p_kfz);
    free(p_parkhaus->p_parkplaetze);    
    free(p_parkhaus);
}

void test_fuege_kfz_hinzu_belegt()
{
    Parkhaus *p_parkhaus = init_parkhaus(5, 40); //Erstellen eines Parkhauses mit 5 Parkplätzen und einer maximalen Parkdauer von 40
    int id = 3;
    Kfz *p_kfz1 = init_kfz(p_parkhaus, &id, 60); //Test Kfz erhält die ID 3 und die einfahrtzeitpunkt von 60
    
    id = 1;
    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, &id, 60);
    p_parkhaus->p_parkplaetze[0].belegt = 1; //Belegt den ersten Parkplatz
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, &id, 60);
    p_parkhaus->p_parkplaetze[1].belegt = 1; //Belegt den zweiten Parkplatz
    
    fuege_kfz_hinzu(p_parkhaus, p_kfz1); //Fügt das Kfz zum Parkhaus hinzu
    
    for(int i = 0; i < 2; i++)
    {
        if(p_parkhaus->p_parkplaetze[i].belegt == 1)
        {
            assert(p_parkhaus->p_parkplaetze[i].p_kfz != p_kfz1); //Überprüft, ob das Kfz nicht auf einem belegten Parkplatz gelandet ist
        }
    }
    
    for(int i = 2; i < p_parkhaus->anzahl_parkplaetze; i++)
    {
        if(p_parkhaus->p_parkplaetze[i].belegt == 1)
        {
            assert(p_parkhaus->p_parkplaetze[i].p_kfz == p_kfz1); //Überprüft, ob das Kfz auf einem freien Parkplatz gelandet ist
        }
    }
    
    free(p_parkhaus->p_parkplaetze[0].p_kfz); //Gibt den Speicher des ersten Kfz frei
    free(p_parkhaus->p_parkplaetze[1].p_kfz); //Gibt den Speicher des zweiten Kfz frei
    free(p_kfz1);
    free(p_parkhaus->p_parkplaetze); //Gibt den Speicher der Parkplätze frei
    free(p_parkhaus);
}


void test_entferne_kfz_normalfall()
{
    Parkhaus *p_parkhaus = init_parkhaus(5, 40); //Erstellen eines Parkhauses mit 5 Parkplätzen und einer maximalen Parkdauer von 40 
    int id = 1;
    Kfz *p_kfz = init_kfz(p_parkhaus, &id, 60); //Test Kfz erhält die ID 1 und die einfahrtzeitpunkt von 60

    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, &id, 60);
    p_parkhaus->p_parkplaetze[0].belegt = 1;
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, &id, 60);
    p_parkhaus->p_parkplaetze[1].belegt = 1;
    p_parkhaus->p_parkplaetze[2].p_kfz = p_kfz;
    p_parkhaus->p_parkplaetze[2].belegt = 1;
    p_parkhaus->belegte_parkplaetze = 3;
    //Volles Parkhaus davon 2 Plätze belegt und 1 Platz mit dem Test Kfz belegt
    
    entferne_kfz(p_parkhaus, p_kfz); //Entfernt das Kfz aus dem Parkhaus (gibt p_kfz intern frei)
    
    assert(p_parkhaus->p_parkplaetze[2].belegt == 0); //Überprüft, ob der Parkplatz des Kfz jetzt frei ist
    assert(p_parkhaus->belegte_parkplaetze == 2); //Überprüft, ob die Anzahl der belegten Parkplätze um 1 reduziert wurde

    free(p_parkhaus->p_parkplaetze[0].p_kfz); //Gibt den Speicher des ersten Kfz frei
    free(p_parkhaus->p_parkplaetze[1].p_kfz); //Gibt den Speicher des zweiten Kfz frei
    free(p_parkhaus->p_parkplaetze); //Gibt den Speicher der Parkplätze frei
    free(p_parkhaus);
}

void test_entferne_kfz_nicht_vorhanden()
{
    Parkhaus *p_parkhaus = init_parkhaus(5, 40); //Erstellen eines Parkhauses mit 5 Parkplätzen und einer maximalen Parkdauer von 40 
    int id = 1;
    Kfz *p_kfz = init_kfz(p_parkhaus, &id, 60); //Test Kfz erhält die ID 1 und die einfahrtzeitpunkt von 60

    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, &id, 60);
    p_parkhaus->p_parkplaetze[0].belegt = 1;
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, &id, 60);
    p_parkhaus->p_parkplaetze[1].belegt = 1;
    p_parkhaus->belegte_parkplaetze = 2;
    //Parkhaus mit 2 belegten Parkplätzen aber das Test Kfz ist nicht im Parkhaus

    entferne_kfz(p_parkhaus, p_kfz); //Versucht das Kfz zu entfernen, obwohl es nicht im Parkhaus ist
    
    assert(p_parkhaus->p_parkplaetze[0].belegt == 1); //Überprüft, ob der erste Parkplatz weiterhin belegt ist
    assert(p_parkhaus->p_parkplaetze[1].belegt == 1); //Überprüft, ob der zweite Parkplatz weiterhin belegt ist
    assert(p_parkhaus->belegte_parkplaetze == 2); //Überprüft, ob die Anzahl der belegten Parkplätze unverändert geblieben ist

    free(p_parkhaus->p_parkplaetze[0].p_kfz); //Gibt den Speicher des ersten Kfz frei
    free(p_parkhaus->p_parkplaetze[1].p_kfz); //Gibt den Speicher des zweiten Kfz frei
    free(p_parkhaus->p_parkplaetze); //Gibt den Speicher der Parkplätze frei
    free(p_kfz);
    free(p_parkhaus);
}

void test_entferne_kfzs_maximale_parkdauer()
{
    Parkhaus *p_parkhaus = init_parkhaus(3, 40); //Erstellen eines Parkhauses mit 3 Parkplätzen und einer maximalen Parkdauer von 40
    int id = 1;
    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, &id, 10); //Kfz mit ID 1 und Einfahrtzeitpunkt 10
    p_parkhaus->p_parkplaetze[0].belegt = 1;
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, &id, 10); //Kfz mit ID 2 und Einfahrtzeitpunkt 20
    p_parkhaus->p_parkplaetze[1].belegt = 1;
    p_parkhaus->p_parkplaetze[2].p_kfz = init_kfz(p_parkhaus, &id, 10); //Kfz mit ID 3 und Einfahrtzeitpunkt 30
    p_parkhaus->p_parkplaetze[2].belegt = 1;
    p_parkhaus->belegte_parkplaetze = 3;
    //Parkhaus mit 3 belegten Parkplätzen

    p_parkhaus->p_parkplaetze[2].p_kfz->verbleibende_parkdauer = -1; //Setzt die verbleibende Parkzeit des Kfz auf -1, damit es die maximale Parkdauer überschreitet
    entferne_kfzs_maximale_parkdauer(p_parkhaus); //Entfernt Kfz, die die maximale Parkdauer überschritten haben
    assert(p_parkhaus->p_parkplaetze[0].belegt == 1);
    assert(p_parkhaus->p_parkplaetze[1].belegt == 1);
    assert(p_parkhaus->p_parkplaetze[2].belegt == 0); //Überprüft, ob das Kfz mit der überschrittenen Parkdauer entfernt wurde
    assert(p_parkhaus->belegte_parkplaetze == 2); //Überprüft, ob die Anzahl der belegten Parkplätze um 1 reduziert wurde

    free(p_parkhaus->p_parkplaetze[0].p_kfz);
    free(p_parkhaus->p_parkplaetze[1].p_kfz);
    free(p_parkhaus->p_parkplaetze);
    free(p_parkhaus);
}

void test_entferne_kfzs_maximale_parkdauer_keine_ueberschreitung()
{
    Parkhaus *p_parkhaus = init_parkhaus(3, 40); //Erstellen eines Parkhauses mit 3 Parkplätzen und einer maximalen Parkdauer von 40
    int id = 1;
    p_parkhaus->p_parkplaetze[0].p_kfz = init_kfz(p_parkhaus, &id, 10); //Kfz mit ID 1 und Einfahrtzeitpunkt 10
    p_parkhaus->p_parkplaetze[0].belegt = 1;
    p_parkhaus->p_parkplaetze[1].p_kfz = init_kfz(p_parkhaus, &id, 10); //Kfz mit ID 2 und Einfahrtzeitpunkt 20
    p_parkhaus->p_parkplaetze[1].belegt = 1;
    p_parkhaus->p_parkplaetze[2].p_kfz = init_kfz(p_parkhaus, &id, 10); //Kfz mit ID 3 und Einfahrtzeitpunkt 30
    p_parkhaus->p_parkplaetze[2].belegt = 1;
    p_parkhaus->belegte_parkplaetze = 3;
    //Parkhaus mit 3 belegten Parkplätzen

    entferne_kfzs_maximale_parkdauer(p_parkhaus); //Entfernt Kfz, die die maximale Parkdauer überschritten haben
    
    for(int i = 0; i < p_parkhaus->anzahl_parkplaetze; i++)
    {
        if(p_parkhaus->p_parkplaetze[i].belegt == 1)
        {
            assert(p_parkhaus->p_parkplaetze[i].p_kfz != NULL); //Überprüft, ob alle Kfz weiterhin im Parkhaus sind
        }
    }
    
    assert(p_parkhaus->belegte_parkplaetze == 3); //Überprüft, ob die Anzahl der belegten Parkplätze unverändert geblieben ist
    free(p_parkhaus->p_parkplaetze[0].p_kfz); //Gibt den Speicher des ersten Kfz frei
    free(p_parkhaus->p_parkplaetze[1].p_kfz); //Gibt den Speicher des zweiten Kfz frei
    free(p_parkhaus->p_parkplaetze[2].p_kfz); //Gibt den Speicher des dritten Kfz frei
    free(p_parkhaus->p_parkplaetze); //Gibt den Speicher der Parkplätze frei
    free(p_parkhaus);
}

int main()
{
    test_fuege_kfz_hinzu_leer();
    test_fuege_kfz_hinzu_belegt();
    test_entferne_kfz_normalfall();
    test_entferne_kfz_nicht_vorhanden();
    test_entferne_kfzs_maximale_parkdauer();
    test_entferne_kfzs_maximale_parkdauer_keine_ueberschreitung();
    return 0;
}