#ifndef KFZ_H
#define KFZ_H
struct Parkhaus ; // Vorwärtsdeklaration der Struktur Parkhaus, da sie in der Funktion init_auto verwendet wird
typedef struct Kfz 
{
    int *p_id; //Zeiger auf die Variable ID
    int einfahrtszeitpunkt; //einfahrtszeit
    int verbleibende_parkdauer;
    struct Kfz *p_naechstes_kfz;
} Kfz;
/**
* @brief Erstellt ein neues Kfz und reserviert den Speicher dafür.
*
*Reserviert Speicher für ein Kfz initialisiert alle Werte und setzt p_naechstes_kfz auf NULL.
* 
* @param[in] id des Kfz
* @param[in] zeitpunkt der Einfahrt des Kfz
* @return p_kfz Zeiger auf das neu erstellte Kfz
*/
Kfz* init_kfz(struct Parkhaus *p_parkhaus, int *p_id, int zeitpunkt);

#endif  /*KFZ_H*/