// timerlabel.hh - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// Esittelee ajastimeksi erikoistuneen QLabel-alaluokan,
// TimerLabelin. Ajastimen tarkkuus on sekunnin sadasosa,
// jotta edistynyt Binairomestarikin saisi riittävän tarkkaa
// palvelua.
// Ajastin näyttää minuutteja, sekunteja, ja sekunnin sadasosia.

#ifndef TIMERLABEL_HH
#define TIMERLABEL_HH

#include <QLabel>
#include <QTimer>

class TimerLabel : public QLabel
{
public:
    // Rakentaja
    TimerLabel();

public slots:
    // Näillä ajastinta voidaan ohjata käyttöliittymästä käsin.
    void timer_update();
    void start();
    void stop();
    void reset();

private:
    void increment_timer();
    QString disp_text();

    // Ajastimen ajastin-jäsenolio.
    QTimer* timer_;

    unsigned int sec100s_ = 0;
    unsigned int secs_ = 0;
    unsigned int mins_ = 0;


};

#endif // TIMERLABEL_HH
