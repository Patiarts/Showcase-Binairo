// binairocell.hh - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// binairocell.hh esitelee BinairoCell-widgetin.
// BinairoCell vastaa binairo-pelilaudan yhtä ruutua.
// Ruutu voi olla yhdessä kolmesta tilasta: tyhjä, nolla tai ykkönen.
// BinairoCell edustaa nollaa ja ykköstä valkoisella ja mustalla
// "kivellä" eli ympyrällä. Tyhjään BinairoCelliin ei piirretä kiveä.
// Lisäksi BinairoCell voi olla lukittu, jolloin sitä ei voi muuttaa
// pelin aikana. Binairolaudan alkuasetelman kivet lukitaan.

#ifndef BINAIROCELL_HH
#define BINAIROCELL_HH

#include <QWidget>
#include <QMouseEvent>
#include "gameboard.hh"

class BinairoCell : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief BinairoCell
     * rakentaja.
     * @param state - Osoitin GameBoard-laudan ruutuun on pakollinen.
     * @param light_bg - Onko solun taustaväri vaalea?
     * @param parent
     */
    explicit BinairoCell(Element_type* state, bool light_bg = false,
                         QWidget *parent = nullptr);

    void set_state(const Element_type& state);

public slots:
    /**
     * @brief refresh
     * Päivittää solun (etenkin koska tämä kutsuu drawEventin),
     * ja lukitsee sen, mikäli se kuuluu alkuasetelmaan.
     */
    void refresh();

    // Nämä lukitsevat ja vapauttavat solun, kun peliä pausetetaan tai jatketaan.
    void freeze();
    void unfreeze();

    // Solu on poistettava, kun sitä vastaava GameBoard poistetaan.
    void on_board_delete();

protected:
    /**
     * @brief mousePressEvent
     * Asettaa solun tilan hiiren syötteen mukaan.
     * @param click - QMouseEvent* kai kertoo, mitä hiiri teki.
     */
    void mousePressEvent(QMouseEvent* click) override;

    /**
     * @brief paintEvent
     * Piirtää solun oikein ikkunaan.
     * @param paint - QPaintEvent* kai kertoo, mihin piirretään.
     * Qt tarvitsee tätä varmaan myös käyttöliittymän piirtämisen optimointiin.
     */
    void paintEvent(QPaintEvent* paint) override;

private:
    // BinairoCell on määritelty GameBoard.board_-muuttujan perusteella.
    // Ilman osoitinta solulla ei ole tilaa EMPTY, ZERO, tai edes ONE.
    Element_type* state_;

    // Määrittää solun lukituksi, jos se on osa alkuasetelmaa.
    bool locked_ = false;

    QColor bg_color_ = QColor(115,75,65);
    const QColor zero_color_ = QColor(230, 215, 200);
    const QColor one_color_ = QColor(35, 15, 5);
    const QColor nail_color_ = QColor("gray");
};

#endif // BINAIROCELL_HH
