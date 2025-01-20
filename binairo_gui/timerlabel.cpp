// timerlabel.cpp - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// Määrittelee TimerLabelin toiminnan.
// Pääpiirteittäin TimerLabel kokoaa joka kymmenes millisekunti
// uuden QStringin kuluneen ajan perusteella, ja näyttää sen
// graafisesti QLabelin keinoin.

#include "timerlabel.hh"

TimerLabel::TimerLabel()
    : timer_(new QTimer)
{
    // Ajastimen fontin on oltava monospace, jotta ajastimen koko ei vaihtelisi
    // muuttuvien numeroiden mukaan.
    QFont mono("Courier new", 16);
    mono.setStyleHint(QFont::Monospace);

    setFont(mono);
    setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setText("0:00.00");

    // TimerLabelin tarkkuus on sekunnin sadasosa, eli 10ms. Taitava
    // Binairon pelaaja saattaa hyvinkin välittää näin tarkasta ajastuksesta!
    timer_->setInterval(10);
    connect(timer_, &QTimer::timeout, this, &TimerLabel::timer_update);
}

void TimerLabel::timer_update()
{
    increment_timer();
    // Tässä aika näytetään tekstinä QLabelissa.
    setText(disp_text());
}

void TimerLabel::start()
{
    timer_->start();
}

void TimerLabel::stop()
{
    timer_->stop();
}

void TimerLabel::reset()
{
    timer_->stop();
    sec100s_ = 0;
    secs_ = 0;
    mins_ = 0;
    setText("0:00.00");
}

void TimerLabel::increment_timer()
{
    // Tässä käytetään aikaista returnia ohjelman nopeuttamiseksi?
    // en tiedä onko hyötyä, mutta tykkään aikaisesta returnaamisesta :D
    sec100s_++;

    if(not (sec100s_ > 99)){
        return;
    }

    sec100s_ = 0;
    secs_++;

    if(not (secs_ > 59)){
        return;
    }

    secs_ = 0;
    mins_++;
}

QString TimerLabel::disp_text()
{
    // Näytettävä teksti kootaan ajastimen sisäisten numeroiden
    // perusteella.
    QString disp_str = QString::number(mins_) + ":";

    if(secs_ < 10){
        disp_str += "0";
    }
    disp_str += QString::number(secs_) + ".";

    if(sec100s_ < 10){
        disp_str += "0";
    }
    disp_str += QString::number(sec100s_);

    return disp_str;
}
