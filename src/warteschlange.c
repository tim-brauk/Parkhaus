#include "warteschlange.h"

void add_car_queue(Parkhaus *p_parkhaus, Kfz *p_kfz)
{
    if (p_parkhaus->p_erstes_kfz_in_der_warteschlange == NULL)
    {
        p_parkhaus->p_erstes_kfz_in_der_warteschlange = p_kfz;
        p_kfz->p_naechstes_kfz = NULL;
        return;
    }

}