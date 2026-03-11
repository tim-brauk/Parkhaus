#ifndef PARKVORGANG_H
#define PARKVORGANG_H
#include "parkhaus.h"


/**
 * @brief Parkt ein Kfz auf einem zufaelligen freien Parkplatz ein.
 *
 * Sucht einen zufaelligen freien Parkplatz und weist dem Kfz
 * diesen Platz zu. Es wird außerdem gespeichert an wie vielen Parkplätzen es bis dahin vorbeigekommen ist.
 *
 * @param[in] p_parkhaus Zeiger auf das Parkhaus
 * @param[in] p_kfz  Zeiger auf das einzuparkende Kfz
 * @return void
 */
void fuege_kfz_hinzu(Parkhaus *p_parkhaus, Kfz *p_kfz);

/**
 * @brief Entfernt ein Kfz von seinem Parkplatz.
 *
 *Entfernt das Kfz und gibt den Speicher frei. Der parkplatz wird als frei markiert.
 * 
 * @param[in] p_parkhaus Zeiger auf das Parkhaus
 * @param[in] p_kfz  Zeiger auf das zu entfernende Kfz
 * @return void
 */
void entferne_kfz(Parkhaus *p_parkhaus, Kfz *p_kfz);

/**
 * @brief Entfernt Kfz mit die die maximale Parkdauer überschritten haben.
 *
 * Überprüft alle geparkten kfz und entfernt die die die maximale Parkdauer überschritten haben (remove_car).
 * 
 * @param[in] p_parkhaus Zeiger auf das Parkhaus
 * @return void
 */
void entferne_kfzs_maximale_parkdauer(Parkhaus *p_parkhaus);
#endif /* PARKVORGANG_H */