// binairocell.cpp - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// Määrittelee BinairoCell-luokan operaatiot.
// Tärkeitä ovat mousePressEvent()- ja paintEvent()-
// metodit.

#include "binairocell.hh"
#include <QPainter>
#include <QDebug>

BinairoCell::BinairoCell(Element_type* state, bool light_bg, QWidget *parent)
    : QWidget{parent}
    , state_(state)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    setDisabled(true);

    // Tehdään solun taustaväristä vähän vaaleampi, jos sen pitäisi olla.
    if(light_bg){
        bg_color_ = QColor(135,95,85);
    }
}

void BinairoCell::mousePressEvent(QMouseEvent *click)
{
    // Solu vastaa eri tavoin hiiren eri nappeihin. Tämä on
    // suurin syy, miksi edes on olemassa BinairoCell-luokka.
    if(click->button() == Qt::LeftButton){
        set_state(ZERO);
    }
    else if(click->button() == Qt::RightButton){
        set_state(ONE);
    }
}

void BinairoCell::paintEvent(QPaintEvent *paint)
{
    // Lukuja ympyrän piirtämistä varten.
    // Solun keskelle pitää piirtää ympyrä, ei soikiota.
    // Näillä laskuilla saadaan solunkeskisen ympyrän koko.
    int h = geometry().height();
    int w = geometry().width();
    int mindim = std::min({h,w});

    int circle_diameter = (9*mindim)/10;
    int h_offset = (h - circle_diameter)/2;
    int w_offset = (w - circle_diameter)/2;

    // QPainter::drawellipse piirtää tietysti ympyrän, jos sille syöttää neliön
    // ellipsiä määrittämään.
    QRect ellipse_rect = paint->rect().adjusted(w_offset, h_offset,
                                               -w_offset, -h_offset);

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::transparent, Qt::SolidPattern));

    painter.fillRect(paint->rect(), bg_color_);

    // Solun tila (nolla vai yksi) määrittää, piirretäänkö soluun
    // valkoinen vai musta ympyrä.
    switch(*state_){
    case ZERO: painter.setBrush(zero_color_); break;
    case ONE: painter.setBrush(one_color_); break;
    default: break;
    }

    // Vain epätyhjään soluun piirretään muuta kuin tausta.
    if(*state_ != EMPTY){
        painter.drawEllipse(ellipse_rect);
    }

    // Lisäksi lukittuun soluun piirretään "naula" keskelle,
    // käytännössä samalla tavalla kuin suuri ympyräkin.
    if(locked_){
        circle_diameter = mindim/10;
        h_offset = (h - circle_diameter)/2;
        w_offset = (w - circle_diameter)/2;

        QRect nail_rect = paint->rect().adjusted(w_offset, h_offset,
                                                -w_offset, -h_offset);

        painter.setBrush(nail_color_);
        painter.drawEllipse(nail_rect);
    }
}

void BinairoCell::set_state(const Element_type &state)
{
    // Tämä pikku metodi tekee pelistä hyvän pelattavan.
    // Näin sekä solujen täyttäminen että tyhjentäminen
    // käy intuitiivisesti ja yksinkertaisesti ainoastaan
    // hiiren painikkeilla.
    if(*state_ == state){
        *state_ = EMPTY;
    }
    else{
        *state_ = state;
    }

    update();
}

void BinairoCell::refresh()
{
    if(*state_ != EMPTY){
        locked_ = true;
    }
    else{
        locked_ = false;
    }
    update();
}

void BinairoCell::freeze()
{
    setDisabled(true);
}

void BinairoCell::unfreeze()
{
    if(not locked_){
        setEnabled(true);
    }
}

void BinairoCell::on_board_delete()
{
    delete this;
}
