// infowindow.hh - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// Hyvin yksinkertainen ikkuna näyttämään
// ohjeet ja säännöt käyttäjälle.
// Avaa tiedoston resurssikansiosta ja näyttää sen.

#ifndef INFOWINDOW_HH
#define INFOWINDOW_HH

#include <QDialog>
#include <QTextBrowser>
#include <QString>

// Virheviesti, mikäli pyydettyä tiedostoa ei voida avata
const QString ERROR_TEXT = "Error: no input file";

class InfoWindow : public QDialog
{
public:
    /**
     * @brief InfoWindow
     * Rakentaja
     * @param filename - Avattavan tiedoston nimi.
     */
    InfoWindow(QString filename);
private:
    // Tähän kirjoitetaan infotiedosto.
    QTextBrowser* text_window_ = new QTextBrowser(this);


};

#endif // INFOWINDOW_HH
