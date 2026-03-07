#include <assert.h>
#include <stdlib.h>
#include "parkhaus.h"

//Testet die Initialisierung der Warteschlange im Parkhaus
void test_init_parkhaus_warteschlange(){
    Parkhaus *p_parkhaus = init_parkhaus(0, 40); //Erstellen eines Parkhauses mit 0 Parkplätzen, aber einer maximalen Parkdauer von 40 Sekunden
    
    assert(p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL); //Überprüfen, ob die Warteschlange korrekt initialisiert wird
    
    free(p_parkhaus);
}

//Testet die Initialisierung der Parkplätze im Parkhaus
void test_init_parkhaus_parkplaetze(){
    Parkhaus *p_parkhaus = init_parkhaus(5, 40); //Erstellen eines Parkhauses mit 5 Parkplätzen und einer maximalen Parkdauer von 40 Sekunden

    assert(p_parkhaus->anzahl_parkplaetze == 5); //Überprüfen, ob die Anzahl der Parkplätze korrekt gesetzt wird

    for(int i = 0; i < 3; i++) {
        p_parkhaus->p_parkplaetze[i].belegt = 1; //Belegen der ersten 3 Parkplätze
        p_parkhaus->belegte_parkplaetze++; //Erhöhen der Anzahl der belegten Parkplätze
    }
    assert(p_parkhaus->belegte_parkplaetze == 3); //Überprüfen, ob die Anzahl der belegten Parkplätze korrekt initialisiert wird
    free(p_parkhaus);
    free(p_parkplaetze);
}

int main() {
    test_init_parkhaus_warteschlange();
    test_init_parkhaus_parkplaetze();
    return 0;
}