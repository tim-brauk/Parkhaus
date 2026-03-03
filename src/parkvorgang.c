#include "parkvorgang.h"

fuege_kfz_hinzu(Parkhaus *p_parkhaus, Kfz *p_kfz):
{
  /* Ganzzahl freie_parkplaetze = (p_parkhaus->anzahl_parkplaetze) - (p_parkhaus->belegte_parkplaetze)
   *
   * Ganzzahl min = 0
   * Ganzzahl max = freie_parkplaetze - 1
   * Ganzzahl zufaelliger_parkplatz = 0
   * zufaelliger_parkplatz = min + (rand() % (max - min + 1))
   *
   * FÜR Ganzzahl i = 0, i < p_parkhaus->anzahl_parkplaetze, i++:
   *     WENN !zufaelliger_parkplatz
   *         p_parkhaus->p_parkplaetze[i].belegt = 1
   *         p_parkhaus->p_parkplaetze[i].p_kfz = p_kfz
   *         p_parkhaus->belegte_parkplaetze = p_parkhaus->belegte_parkplaetze + 1
   *         ENDE FUNKTION
   *     ENDE WENN
   *
   *     WENN !p_parkhaus->p_parkplaetze[i].belegt
   *         freie_parkplaetze = freie_parkplaetze - 1
   *    ENDE WENN
   * ENDE FÜR
   */

   //Die Funktion wird in Teil 2 des Projekts programmiert

}


entferne_kfz(Parkhaus *p_parkhaus, Kfz *p_kfz):
{    
    /*FÜR Ganzzahl i = 0, i < p_parkhaus->anzahl_parkplaetze, i++:
     *  WENN p_kfz == p_parkhaus->p_parkplaetze[i].p_kfz:
     *       p_parkhaus->p_parkplaetze[i].belegt = 0
     *       free(p_kfz)
     *       p_parkhaus->p_parkplaetze[i].p_kfz = NULL
     *       p_parkhaus->belegte_parkplaetze = p_parkhaus->belegte_parkplaetze - 1
     *       ENDE FUNKTION
     *   ENDE WENN
     * ENDE FÜR
     *
     * Ausgabe: "Dieses Kfz wurde im Parkhaus nicht gefunden"
     */

    //Die Funktion wird in Teil 2 des Projekts programmiert
}


entferne_kfzs_maximale_parkdauer(Parkhaus *p_parkhaus):
{    
    /*FÜR Ganzzahl i = 0, i < p_parkhaus->anzahl_parkplaetze, i++:
     *  WENN p_parkhaus->p_parkplaetze[i].p_kfz != NULL:
     *       WENN p_parkhaus->p_parkplaetze[i].p_kfz->verbleibende_parkdauer < 0:
     *           p_parkhaus->p_parkplaetze[i].belegt = 0
     *           free(p_parkhaus->p_parkplaetze[i].p_kfz)
     *           p_parkhaus->p_parkplaetze[i].p_kfz = NULL
     *           Ausgabe: "Ein KFZ musste aufgrund zu hoher Parkzeit entfernt werden oder aufgrund von Bauarbeiten"
     *       ENDE WENN
     *   ENDE WENN
     * ENDE FÜR
     */

    //Die Funktion wird in Teil 2 des Projekts programmiert
}