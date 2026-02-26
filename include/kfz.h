#ifndef KFZ_H
#define KFZ_H
struct Parkhaus ; // Vorwärtsdeklaration der Struktur Parkhaus, da sie in der Funktion init_auto verwendet wird
typedef struct Kfz 
{
    int id; //ID für jedes Auto int da eine zahl ausreicht
    int parkdauer; //parkdauer in sekunden 
    int einfahrtszeit; //einfahrtszeit
    int verbleibende_parkdauer;
    Kfz *p_naechstes_kfz;
} Kfz;
/**
* @brief Erstellt ein neues Auto und reserviert den Speicher dafür.
*
*Reserviert Speicher für ein Auto initialiesiert alle Werte und setzt p_naechstes_auto auf NULL.
* 
* @param[in] id des Autos
* @return p_kfz Zeiger auf das neu erstellte Kfz
*/
Kfz* init_kfz(struct Parkhaus *p_parkhaus, int id);

#endif  /*KFZ_H*/