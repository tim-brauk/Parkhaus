#include <assert.h>
#include "parkhaus.h"
#include <stdlib.h>
#include "kfz.h"

//Testet die Initialisierung der ID von Kfz
void test_init_kfz_id(){
    Parkhaus *p_parkhaus = init_parkhaus(0, 40); //Erstellen eines Parkhauses mit 0 Parkplätzen, aber einer maximalen Parkdauer von 40
    Kfz *p_kfz = init_kfz(p_parkhaus, 1, 60); //Test Kfz erhält die ID 1 und die einfahrtzeitpunkt von 60
    
    assert(p_kfz->id == 1); //Überprüfen, ob die ID korrekt gesetzt wird
    
    free(p_kfz);
    free(p_parkhaus);
}

//Testet die Initialisierung der Parkdauer von Kfz
void test_init_kfz_parkdauer(){
    Parkhaus *p_parkhaus = init_parkhaus(0, 40); //Erstellen eines Parkhauses mit 0 Parkplätzen, aber einer maximalen Parkdauer von 40
    Kfz *p_kfz = init_kfz(p_parkhaus, 1, 60); //Test Kfz erhält die ID 1 und die einfahrtzeitpunkt von 60
    
    assert(p_kfz->parkdauer >= 1 && p_kfz->parkdauer <= 40); //Überprüfen, ob die Parkdauer innerhalb des erwarteten Bereichs liegt
    
    free(p_kfz);
    free(p_parkhaus);
}

int main() {
    test_init_kfz_id();
    test_init_kfz_parkdauer();
    return 0;
}