#include <assert.h>
#include <stdlib.h>
#include "parkvorgang.h"
#include "parkhaus.h"

void test_fuege_kfz_hinzu_leer(){
    Parkhaus *p_parkhaus = init_parkhaus(5, 40); //Erstellen eines Parkhauses mit 5 Parkplätzen und einer maximalen Parkdauer von 40 Sekunden
    Kfz *p_kfz = init_kfz(p_parkhaus, 1, 60); //Test Kfz erhält die ID 1 und die einfahrtzeitpunkt von 60
    fuege_kfz_hinzu(p_parkhaus, p_kfz); //Fügt das Kfz zum Parkhaus hinzu
    assert(p_kfz->belegte_parkplaetze == 1); //Überprüft, ob das Kfz einen Parkplatz zugewiesen bekommen hat
    for(int i = 0; i < p_parkhaus->anzahl_parkplaetze; i++){
        if(p_parkhaus->parkplaetze[i] != NULL){
            assert(p_parkhaus->parkplaetze[i]->p_kfz == p_kfz); //Überprüft, ob das Kfz auch im Parkhaus angekommen ist
        }
    }
    free(p_kfz);
    free(p_parkhaus);
}

void test_fuege_kfz_hinzu_belegt(){
    Parkhaus *p_parkhaus = init_parkhaus(5, 40); //Erstellen eines Parkhauses mit 5 Parkplätzen und einer maximalen Parkdauer von 40 Sekunden
    Kfz *p_kfz1 = init_kfz(p_parkhaus, 3, 60); //Test Kfz erhält die ID 3 und die einfahrtzeitpunkt von 60
    Parkhaus->parkplaetze[0] = init_kfz(p_parkhaus, 1, 60);
    Parkhaus->parkplaetze[0]->belegt = 1; //Belegt den ersten Parkplatz
    Parkhaus->parkplaetze[1] = init_kfz(p_parkhaus, 2, 60);
    Parkhaus->parkplaetze[1]->belegt = 1; //Belegt den zweiten Parkplatz
    fuege_kfz_hinzu(p_parkhaus, p_kfz1); //Fügt das Kfz zum Parkhaus hinzu
    for(int i = 0; i < 2; i++){
        if(p_parkhaus->parkplaetze[i] != NULL){
            assert(p_parkhaus->parkplaetze[i]->p_kfz != p_kfz1); //Überprüft, ob das Kfz nicht auf einem belegten Parkplatz gelandet ist
        }
    }
    for(int i = 2; i < p_parkhaus->anzahl_parkplaetze; i++){
        if(p_parkhaus->parkplaetze[i] != NULL){
            assert(p_parkhaus->parkplaetze[i]->p_kfz == p_kfz1); //Überprüft, ob das Kfz auf einem freien Parkplatz gelandet ist
        }
    }
    free(p_kfz1);
    free(p_parkhaus);
}

int main(){
    test_fuege_kfz_hinzu_leer();
    test_fuege_kfz_hinzu_belegt();
    return 0;
}