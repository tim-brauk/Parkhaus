#ifndef AUTO_H
#define AUTO_H
struct Parkhaus ; // Vorwärtsdeklaration der Struktur Parkhaus, da sie in der Funktion init_auto verwendet wird
typedef struct Auto
{
    int id; //ID für jedes Auto int da eine zahl ausreicht
    int parkdauer; //parkdauer in sekunden 
    int einfahrtszeit; //einfahrtszeit
    int verbleibende_parkdauer;
    Auto *p_naechstes_auto;
} Auto;
/**
* @brief Erstellt ein neues Auto und reserviert den Speicher dafür.
*
*Reserviert Speicher für ein Auto initialiesiert alle Werte und setzt p_naechstes_auto auf NULL.
* 
* @param[in] id des Autos
* @return p_auto Zeiger auf das neu erstellte Auto
*/
Auto* init_auto(struct Parkhaus *p_parkhaus, int id);

#endif  /*AUTO_H*/