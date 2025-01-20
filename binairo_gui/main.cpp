// COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// BINAIRO_GUI
// Tämä ohjelma on Binairo-peli.
// ohjelma avaa ikkunan, jossa on oikealla Binairolauta,
// ja vasemmalla työkaluja uuden Binairolaudan asettamiseksi.
//
// Peli aloitetaan pelilaudan yläpuolella olevasta "Play"-
// napista. Pelin saa myös keskeytettyä samasta napista.
// Binairolauta on neliöruudukko, joka tulee täyttää nollilla
// ja ykkösillä, tai tämän ohjelman tapauksessa, valkoisilla ja
// mustilla ympyröillä, noudattaen tiettyjä sääntöjä.
// "Kiviä" asetetaan laudalle hiiren oikealla ja vasemmalla
// näppäimellä, ja poistetaan painamalla uudestaan kiven
// väriä vastaanaa hiiren näppäintä.
// Kun lauta on täytetty Binairon sääntöjen mukaisesti,
// peli lopetetaan ja voitetaan painamalla "Check"-nappia
// laudan alapuolella. Voittajalle näytetään suoritukseen
// kulunut aina tarkistusnapin vieressä.
// Laudan yläpuolella on myös "Reset"-nappi, jolla pelin voi
// palauttaa alkuasetelmaan.
//
// Ikkunan vasemmalla puolella on työkaluja, joilla käyttäjä
// voi asettaa tahtoessaan uuden pelilaudan. Vaihtoehtoja on
// laudan koon säätämiselle ja erilaisten asetustapojen välillä.
// Lauta voidaan generoida satunnaisesti siemenluvun avulla,
// merkki merkiltä käyttäjän oman syötteen perusteella, tai
// pelilaudalle voi asettaa suoraan toivotun alkuasetelman.
// Ohjelma ei kuitenkaan salli alkuasetelmia, jotka rikkovat
// suoraan jotain Binairon säännöistä.
// Siemenluvut ja syöterivit syötetään "Input seed"-
// rivieditoriin.
// Syöterivin täytyy alkaa ja loppua lainausmerkkiin, ja niiden
// välissä pitää olla täsmälleen sama määrä merkkejä kuin mitä
// pyydetyn kokoisessa laudassa on ruutuja. Syöterivillä tyhjää
// ruutua merkitään välilöynnillä, valkoista kiveä nollalla, ja
// mustaa kiveä ykkösellä.
//
// BINAIRON SÄÄNNÖT:
// - Laudalla saa olla peräkkäin enintään kaksi samanväristä
//   kiveä, pystyssä tai rivissä.
// - Joka rivillä ja sarakkeella on oltava sama määrä valkoisia
//   ja mustia kiviä.
// - Joka rivin/sarakkeen pitää olla ainutlaatuinen, eli
//   sen kivet eivät saa olla samassa järjestyksessä kuin
//   yhdenkään toisen rivin/sarakkeen (rivi ja sarake saavat kuitenkin
//   olla samat (niiden vertailussa ei välttämättä ole järkeä)).
//
// Ikkunassa on myös "?"-infonappi otsikon vieressä, sekä "Quit"-
// nappi alareudassa, mistä ohjelman voi sulkea.


#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
