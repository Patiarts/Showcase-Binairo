// infowindow.cpp - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// Infoikkuna hakee tiedoston resurssikansiosta, ja
// näyttää sen rivi riviltä QTextBrowserissa.

#include "infowindow.hh"
#include <QScrollBar>
#include <QFile>
#include <QTextStream>

InfoWindow::InfoWindow(QString filename)
{
    setWindowTitle("INFO");

    text_window_->setMinimumSize(QSize(512, 512));

    // Tämä ikkuna hakee tiedostoja resurssikansiosta.
    // Polku on siis oletusarvoisesti resurssikansioon.
    QString file_path = ":/resources/" + filename;

    // Yritetään avata tiedostoa. Mikäli se ei suju, asiasta ilmoitetaan
    // Virhetekstillä ja rakentaja keskeytyy.
    QFile info_file(file_path);
    if(not info_file.open(QFile::ReadOnly)) {
        text_window_->setText(ERROR_TEXT);
        info_file.close();
        return;
    }

    // Jos tiedosto avattiin onnistuneesti, siitä luetaan teksti rivi kerrallaan
    // ja lisätään ne text_window_iin.
    QTextStream info(&info_file);

    while(!info.atEnd()) {
        QString line = info.readLine();
        text_window_->append(line);
    }

    info_file.close();
    text_window_->moveCursor(QTextCursor::Start);   // append() ilmeisesti siirtää QTextBrowserin view portin loppuun.
    text_window_->show();
}
