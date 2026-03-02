#include "kfz.h"

Kfz* init_kfz(struct Parkhaus *p_parkhaus, int id, int zeitpunkt)
{
    Kfz *p_kfz = NULL;

    p_kfz = (Kfz*)malloc(sizeof(Kfz));

    if (p_kfz == NULL)
    {
        return NULL;

        p_kfz->id = id;
        p_kfz->parkdauer = 0;
        p_kfz->einfahrtszeit = zeitpunkt;
        p_kfz->verbleibende_parkdauer = 0;
        p_kfz->p_naechstes_kfz = NULL;
    }
    
    return p_kfz;
    
}
