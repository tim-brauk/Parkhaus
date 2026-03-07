#ifndef WARTESCHLANGE_H
#define WARTESCHLANGE_H
#include "parkhaus.h"
/**
 * @brief Fügt ein Kfz ans Ende der Warteschlange hinzu.
 *
 * ...
 *
 * @param[in] p_parkhaus Zeiger auf das Parkhaus
 * @param[in] p_kfz Zeiger auf das hinzuzufuegende Kfz
 * @return void
 */
void kfz_hinzufuegen_warteschlange(Parkhaus *p_parkhaus, Kfz *p_kfz);

/**
 * @brief Entfernt das erste Kfz aus der Warteschlange und gibt es zurück.
 *
 * Setzt den Kopf der Warteschlange auf das nächste Kfz.
 * Das  entfernte Kfz wird zurückgegeben, damit es weiterverarbeitet werden kann (z.B. zum Parken).
 * 
 * @param[in] p_parkhaus Zeiger auf das Parkhaus
 * @retval    p_kfz      Zeiger auf das entfernte Kfz
 * @retval    NULL       Wenn die Warteschlange leer ist
 */
Kfz *entferne_kfz_warteschlange(Parkhaus *p_parkhaus);
#endif /* WARTESCHLANGE_H */