// mainwindow.hh - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// mainwindow.hh esittelee ohjelman pääikkunan ja peliä ohjaavia
// komentoja ja muuttujia.
// Käyttöliittymä on suunniteltu pääosin Qt Designerilla ja
// määritelty tiedostossa mainwindow.ui.
// Pääikkuna on aseteltu QGridLayoutin avulla sopivan näköiseksi.
// Huomioitavaa on, että toinen QGridLayout, johon BinairoCell-
// oliot lisätään, on itse QFramen sisällä. Tämä QFrame varmistaa,
// että pelilauta säilyy aina vähintään 512x512-pikselin kokoisena.

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "timerlabel.hh"
#include "infowindow.hh"
#include <QMainWindow>
#include <string>

// Game_state-muuttuja korvaa tarpeen käyttää erillisiä bool-muuttujia
// kuten "bool paused_" ja "bool editing_" pelin hetkellisen tilan
// kuvaamiseksi.
enum Game_state{PAUSED, PLAYING, WON, EDITING};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slotteja käyttäjän syötteen havaitsemiseksi. Kutsuvat
    // pääasiallisesti luokan muita metodeja.
    void on_inputLine_textChanged(const QString &arg1);
    void on_setBoardButton_clicked();
    void on_playPauseButton_clicked();
    void on_resetButton_clicked();
    void on_checkPushButton_clicked();
    void on_manualRadioButton_toggled(bool checked);
    void on_infoButton_clicked() const;

signals:
    // Signaaleja pelilaudan BinairoCell-olioiden ohjaamiseksi.
    // BinairoCell-olioihin voidaan lähettää koodista käskyjä vain
    // signaalein, sillä niiden ainoa muunlainen yhteys muihin
    // ohjelman olioihin ja muuttujiin on osoitin erääseen
    // GameBoard-olion jäsenmuuttujataulukon soluun.
    void board_updated();   // Kutsutaan aina, kun lautaa muutetaan koodista käsin.
    void board_deleted();
    void freeze_board();
    void unfreeze_board();

private:

    /**
     * @brief set_new_board
     * Yrittää asettaa uuden pelilaudan käyttäjän
     * asetusten perusteella.
     * @return asetettava lauta ei riko sääntöjä.
     */
    bool set_new_board();

    /**
     * @brief init_cells
     * Luo BinairoCell-widgettejä pelilaudalle
     * gameBoard_-olion mukaan.
     */
    void init_cells();

    // Jengi metodeja pelitilan ohjaamiseen. Näitä kutsutaan
    // erityisesti käyttäjän syötettä seuraavista sloteista,
    // esim. kun käyttäjä painaa jotain nappia.
    void play();
    void pause();
    void reset();
    void win();
    void start_editing();
    void stop_editing();
    void check_for_win();

    // Näillä metodeilla tutkitaan, onko peli voitettu.
    // Peli on voitettu, mikäli lauta on täynnä niin,
    // että se ei riko sääntöjä.
    bool board_is_full();
    bool board_is_valid();

    // Käyttöliittymäolio, joka sisältää käyttöliittymäkomponentit.
    Ui::MainWindow *ui;

    // TimerLabel-olio, jonka avulla ohjelma tutkii ja viestii
    // peliin käytettyä aikaa.
    TimerLabel* timer_;

    // GameBoard-olio sisältää Binairo-pelin abstraktiot ja logiikan,
    // joilla peliä pelataan. Käytännössä ohjelman Binairo-pelimoottori.
    GameBoard* gameboard_ = nullptr;

    // QDialog-ikkuna, joka kertoo käyttäjälle pelin säännöt ja
    // ohjelman käyttöohjeen.
    InfoWindow* info_window_;

    // Enum-muuttuja, jolla seurataan pelin tilaa. Tärkeä kussakin hetkessä
    // sopivien toimintojen kutsumiseksi.
    Game_state game_state_;

    // Tämä metodi on käytännössä jäsenmuuttuja siitä, mikä käyttöliittymän
    // radioButtoneista on valittuna. Määrittää, millä tavalla uusi pelilauta
    // tulee asettaa.
    Set_mode set_mode() const;

    // Siemenluku pelilaudan satunnaiseen asettamiseen.
    unsigned int seed_;

    // Syöterivi pelilaudan syötteen mukaan asettamiseen.
    std::string input_;

    // Tämä metodi on käytännössä jäsenmuuttuja, jonka mukaan uuden laudan
    // koko määrätään. Hakee käyttöliittymän sizeSpinBox-widgetin arvon.
    unsigned int board_size() const;


};
#endif // MAINWINDOW_HH
