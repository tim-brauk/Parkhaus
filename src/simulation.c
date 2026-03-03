#include "simulation.h"

FUNKTION simuliere_zeitabschnitt(Parkhaus *p_parkhaus, Simulationsparameter *p_simulationsparameter, &id, &zeitpunkt):
    /*
     * FÜR Ganzzahl i = 0, i < p_parkhaus->anzahl_parkplaetze, i++:
     *     WENN p_parkhaus->p_parkplaetze[i].belegt
     *         p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer = p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer - 1
     *     ENDE WENN
     * ENDE FÜR
     *
     * Fließkommazahl zufall = 0
     * zufall = 0 + ((Fließkommazahl)rand() / RAND_MAX) * (1 - 0)
     *
     * entferne_kfzs_maximale_parkdauer(Parkhaus *p_parkhaus)
     *
     * WENN zufall <= p_simulationsparameter->wahrscheinlichkeit_neues_kfz:
     *     Kfz *p_neues_kfz = init_kfz(Parkhaus *p_parkhaus, Ganzzahl id)
     *     id = aktuelle_id(Ganzzahl id)
     *     kfz_hinzufuegen_warteschlange(Parkhaus *p_parkhaus, Kfz *p_neues_kfz)
     * ENDE WENN
     *
     * FÜR Ganzzahl i = 0, i < p_parkhaus->anzahl_parkplaetze, i++:
     *     WENN p_parkhaus->p_parkplaetze[i].belegt
     *         WENN p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer == 0:
     *             entferne_kfz(Parkhaus p_parkhaus, Kfz p_parkhaus->p_parkplaetze[i].p_kfz)
     *         ENDE WENN
     *     ENDE WENN
     * ENDE FÜR
     *
     * Ganzzahl freie_parkplaetze_wahrheitsvariable = platz_garage(Parkhaus *p_parkhaus)
     *
     * SOLANGE freie_parkplaetze_wahrheitsvariable AND p_parkhaus->p_erstes_kfz_in_der_warteschlange != NULL:
     *     Kfz *p_kfz_hinzufuegen_aus_queue = entferne_kfz_warteschlange(Parkhaus *p_parkhaus)
     *     fuege_kfz_hinzu(Parkhaus *p_parkhaus, Kfz *p_kfz_hinzufuegen_aus_queue)
     *     freie_parkplaetze_wahrheitsvariable = platz_garage(Parkhaus *p_parkhaus)
     * ENDE SOLANGE
     *
     * zeitpunkt = zeitpunkt + 1
     */

    //Die Funktion wird in Teil 2 des Projekts programmiert

ENDE FUNKTION