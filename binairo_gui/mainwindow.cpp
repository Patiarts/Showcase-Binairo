// mainwindow.cpp - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// Määrittelee pääikkunan toimintalogiikan, jonka mukaan
// käyttäjän syöte välitetään ohjelman muihin moduuleihin,
// etenkin Binairo-peliä pyörittävään GameBoard-olioon.

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "binairocell.hh"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer_(new TimerLabel)
    , gameboard_(new GameBoard(SetCommand()))   // Pelilauta alustetaan oletusarvoisen SetCommandin mukaisesti.
    , info_window_(new InfoWindow("instructions.txt"))  // Info-ikkunan tekstitiedosto syötetään rakentajaan.
    , game_state_(PAUSED)
    , seed_(0)
    , input_("")
{
    ui->setupUi(this);

    // Lisätään ajastin pelilaudan yläpuolelle, reset-napin viereen.
    ui->mainGrid->addWidget(timer_, 0, 6);

    // Alustetaan pelilaudan ruutujen BinairoCellit.
    init_cells();

    // Pause()n kutsuminen varmistaa, että ohjelma on valmis käyttöön.
    pause();
}

MainWindow::~MainWindow()
{
    // En osaa ajaa Valgrindia Windows-koneellani, joten poistan varmuuden vuoksi kaiken.
    // Näitä QObjectien pitäisi kai poistua Qt:n parent-child-mekanismin kautta, mutta en ole varma.
    delete gameboard_;
    delete timer_;
    delete info_window_;
    emit board_deleted();   // Signaali poistattaa BinairoCellit
    delete ui;
}

bool MainWindow::set_new_board()
{
    // Palautetaan pelilauta alkutilanteeseen. Etenkin ajastimen nollaus on tarpeen.
    reset();

    // Luodaan uusi GameBoard. Tämän oikeellisuuden perusteella uuden laudan asetus onnistuu.
    GameBoard* new_board = new GameBoard({set_mode(), seed_, input_, board_size()});

    // Virheviesti määräytyy valitun Set_moden perusteella, ei niinkään GameBoardissa
    // pieleen menevän toiminnon perusteella.
    QString error_text = "";
    switch(set_mode()){
    case RANDOM: error_text = "Error: bad seed"; break;
    case INPUT: error_text = "Error: bad input"; break;
    default: error_text = "Error: this error shouldn't be shown"; break;
    }

    // Epäsopiva pelilauta hylätään, ja uuden lautan asetus epäonnistuu.
    if(not new_board->seems_valid()){
        delete new_board;
        ui->errorLabel->setText(error_text);
        return false;
    }

    if(gameboard_ != nullptr){
        delete gameboard_;
        emit board_deleted();   // Edellisen laudan BinairoCellit on poistettava.
    }

    // Sopiva lauta asetetaan päälaudaksi. Uuden laudan asettaminen on helppo tapa
    // toteuttaa laudan koon säätö.
    gameboard_ = new_board;
    init_cells();

    if(set_mode() == MANUAL){
        start_editing();
    }

    ui->errorLabel->clear();
    emit board_updated();
    return true;
}

void MainWindow::init_cells()
{
    unsigned int size = gameboard_->get_size();
    // Tämän avulla solut vaihtelevat tumman ja vaalean taustan välillä.
    // lauseke ((i+j)%2 == 0) silmukassa olisi myös voinut määrätä taustavärin :)
    bool light_colored = false;

    // Pelilaudan joka ruutua vastaamaan luodaan uusi BinairoCell-widgetti.
    for(unsigned int i = 0 ; i < size ; i++){

        for(unsigned int j = 0 ; j < size ; j++){

            Element_type* board_cell_ptr = gameboard_->get_cellptr(i,j);
            BinairoCell* new_cell = new BinairoCell(board_cell_ptr, light_colored);

            // Yhdistetään syntyvät solut pääikkunan signaaleihin käskyjen välittämiseksi.
            connect(this, &MainWindow::board_updated, new_cell, &BinairoCell::refresh);
            connect(this, &MainWindow::freeze_board, new_cell, &BinairoCell::freeze);
            connect(this, &MainWindow::unfreeze_board, new_cell, &BinairoCell::unfreeze);
            connect(this, &MainWindow::board_deleted, new_cell, &BinairoCell::on_board_delete);

            ui->cellGrid->addWidget(new_cell, i, j);

            light_colored = !light_colored;
        }

        light_colored = !light_colored;
    }
    emit board_updated();
}

void MainWindow::play()
{
    // Seuraavat käyttöliittymän ja pelitilan muutokset määrittävät "päällä olemisen" tilan.
    timer_->start();
    game_state_ = PLAYING;
    ui->playPauseButton->setText("Pause");
    ui->checkPushButton->setEnabled(true);
    emit unfreeze_board();
}

void MainWindow::pause()
{
    // Nämä puolestaan määrittävät "tauolla olemisen" tilan.
    timer_->stop();
    game_state_ = PAUSED;
    ui->playPauseButton->setText("Play");
    ui->checkPushButton->setDisabled(true);
    // Kun peli on tauolla, lautaan ei saa tehdä muutoksia. Sehän olisi huijaamista!
    emit freeze_board();
}

void MainWindow::reset()
{
    pause();
    this->setStyleSheet("background-color: window;");   // Jos peli on voitettu, tausta on keltainen.
    ui->winLabel->clear();
    timer_->reset();
    gameboard_->set_board();    // Tämä käsky asettaa laudan takaisin alkuasetelmaansa.
    emit board_updated();
}

void MainWindow::win()
{
    // Nämä käyttöliittymämuutokset määrittävät "voittaneen" pelitilan.
    pause();    // Voittotila on hyvin samankaltainen kuin paussitila.
    game_state_ = WON;
    ui->playPauseButton->setText("Play again");

    QString wintext = "You win! - Time: " + timer_->text();
    ui->winLabel->setText(wintext);
    this->setStyleSheet("background-color: gold;");
}

void MainWindow::start_editing()
{
    // MANUAL-moodissa alustettu lauta on valmiiksi tyhjä, mutta varmistus ei haittaa.
    gameboard_->clear_board();
    game_state_ = EDITING;
    ui->playPauseButton->setText("Set");
    emit board_updated();
    emit unfreeze_board();  // Lautaa voi muokata vain, jos solut ovat epälukittuja.
}

void MainWindow::stop_editing()
{
    // Lukitaan käyttäjän asettama lauta aloitusasetelmaksi. Jos se ei ole
    // sopiva, lauta tyhjennetään jälleen, ja muokkausta saa jatkaa.
    gameboard_->lock_placement();
    if(not gameboard_->seems_valid()){
        gameboard_->clear_board();
        emit board_updated();
        ui->errorLabel->setText("Error: board set unsolvably");
        return;
    }

    ui->errorLabel->clear();
    pause();    // En halunnut, että laudan asetus aloittaa pelin heti, muuten tässä olisi play()-kutsu.
    emit board_updated();
}

void MainWindow::check_for_win()
{
    if(not board_is_full()){
        ui->winLabel->setText("Board is not full!");
        return;
    }   // Laudan oikeellisuus tarkistetaan vasta, kun se on täytetty kokonaan.
    if(not board_is_valid()){
        ui->winLabel->setText("Invalid solution!");
        return;
    }
    win();  // Jos lauta on voittava, voitat!
}

// bool MainWindow::fill_from_seed()
// {
//     if(not gameboard_->fill_randomly(seed_)){
//         return false;
//     }

//     emit board_updated();
//     return true;
// }

// bool MainWindow::fill_from_input()
// {
//     if(not gameboard_->fill_from_input(input_)){
//         qDebug() << "no";
//         return false;
//     }
//     emit board_updated();
//     return true;
// }

bool MainWindow::board_is_full()
{
    // Koodipohjan "is_game_over()"-metodi vastaa kätevästi laudan täyteyden tarkistusta.
    return gameboard_->is_game_over();
}

bool MainWindow::board_is_valid()
{
    return gameboard_->ok_amount_of_symbols() and
           gameboard_->ok_adjacent_symbols() and
           gameboard_->ok_unique_rows_and_columns();
}

void MainWindow::on_inputLine_textChanged(const QString &arg1)
{
    // Tämä toimii, koska jos syöte ei ole lukuarvoinen, QString::toInt() palauttaa nollan (joka on luku).
    seed_ = arg1.toInt();
    input_ = arg1.toStdString();
    // Huomattavaa on, että siemen ja syöte ovat samat. Muuttujia on kaksi selkeyden vuoksi.
}

void MainWindow::on_setBoardButton_clicked()
{
    set_new_board();
}

void MainWindow::on_playPauseButton_clicked()
{
    // playPauseButton tekee sekä vaikka että mitä, riippuen pelitilasta.
    // Tämä on suurin syy sille, että pelitila on enum-rakenne, eikä vaan joukko
    // bool-muuttujia.
    switch(game_state_){
    case WON: reset(); break;   // Kun peli on voitettu,play-nappi aloittaa sen uudelleen.
    case PAUSED: play(); break;
    case PLAYING: pause(); break;
    case EDITING: stop_editing(); break;    // Kun käyttäjä asettaa lautaa, play-nappi on oikeasti set-nappi.
    default: break; // häh
    }
}

void MainWindow::on_resetButton_clicked()
{
    reset();
}

void MainWindow::on_checkPushButton_clicked()
{
    check_for_win();
}

void MainWindow::on_manualRadioButton_toggled(bool checked)
{
    // Kun käyttäjä valitsee manuaalisen asetustilan, setBoardButton
    // ei oikeasti aseta lautaa, vaan se  virka siirtyy playPausebuttonille.
    if(checked){
        ui->setBoardButton->setText("Clear board");
    }
    else{
        ui->setBoardButton->setText("Set board");
    }
}

Set_mode MainWindow::set_mode() const
{
    // Asetustila on luonnollisesti se, mitä käyttäjä
    // on valinnut.
    if(ui->randomRadioButton->isChecked()){
        return RANDOM;
    }
    if(ui->inputRadioButton->isChecked()){
        return INPUT;
    }
    if(ui->manualRadioButton->isChecked()){
        return MANUAL;
    }
    // häh 2: mitä
    return RANDOM;
}

unsigned int MainWindow::board_size() const
{
    return ui->boardSizeSpinBox->value();
}


void MainWindow::on_infoButton_clicked() const
{
    info_window_->show();
}

