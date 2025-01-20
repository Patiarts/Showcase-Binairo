/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *mainGrid;
    QPushButton *checkPushButton;
    QFrame *line;
    QSpinBox *boardSizeSpinBox;
    QRadioButton *randomRadioButton;
    QLabel *errorLabel;
    QLineEdit *inputLine;
    QRadioButton *inputRadioButton;
    QPushButton *quitButton;
    QPushButton *resetButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *infoButton;
    QLabel *winLabel;
    QRadioButton *manualRadioButton;
    QPushButton *setBoardButton;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *playPauseButton;
    QLabel *titleLabel;
    QFrame *boardFrame;
    QGridLayout *gridLayout_3;
    QGridLayout *cellGrid;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(786, 598);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        mainGrid = new QGridLayout();
        mainGrid->setObjectName(QString::fromUtf8("mainGrid"));
        checkPushButton = new QPushButton(centralwidget);
        checkPushButton->setObjectName(QString::fromUtf8("checkPushButton"));

        mainGrid->addWidget(checkPushButton, 8, 7, 1, 1);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMinimumSize(QSize(25, 0));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        mainGrid->addWidget(line, 0, 3, 9, 1);

        boardSizeSpinBox = new QSpinBox(centralwidget);
        boardSizeSpinBox->setObjectName(QString::fromUtf8("boardSizeSpinBox"));
        boardSizeSpinBox->setMinimum(4);
        boardSizeSpinBox->setMaximum(20);
        boardSizeSpinBox->setSingleStep(2);
        boardSizeSpinBox->setValue(6);

        mainGrid->addWidget(boardSizeSpinBox, 2, 2, 1, 1);

        randomRadioButton = new QRadioButton(centralwidget);
        randomRadioButton->setObjectName(QString::fromUtf8("randomRadioButton"));
        randomRadioButton->setChecked(true);

        mainGrid->addWidget(randomRadioButton, 1, 0, 1, 1);

        errorLabel = new QLabel(centralwidget);
        errorLabel->setObjectName(QString::fromUtf8("errorLabel"));
        errorLabel->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0);"));
        errorLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        mainGrid->addWidget(errorLabel, 5, 0, 1, 3);

        inputLine = new QLineEdit(centralwidget);
        inputLine->setObjectName(QString::fromUtf8("inputLine"));

        mainGrid->addWidget(inputLine, 4, 0, 1, 3);

        inputRadioButton = new QRadioButton(centralwidget);
        inputRadioButton->setObjectName(QString::fromUtf8("inputRadioButton"));

        mainGrid->addWidget(inputRadioButton, 2, 0, 1, 1);

        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));

        mainGrid->addWidget(quitButton, 8, 2, 1, 1);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        mainGrid->addWidget(resetButton, 0, 7, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mainGrid->addItem(horizontalSpacer, 6, 0, 2, 3);

        infoButton = new QPushButton(centralwidget);
        infoButton->setObjectName(QString::fromUtf8("infoButton"));

        mainGrid->addWidget(infoButton, 0, 2, 1, 1);

        winLabel = new QLabel(centralwidget);
        winLabel->setObjectName(QString::fromUtf8("winLabel"));
        winLabel->setAlignment(Qt::AlignCenter);

        mainGrid->addWidget(winLabel, 8, 5, 1, 2);

        manualRadioButton = new QRadioButton(centralwidget);
        manualRadioButton->setObjectName(QString::fromUtf8("manualRadioButton"));

        mainGrid->addWidget(manualRadioButton, 3, 0, 1, 1);

        setBoardButton = new QPushButton(centralwidget);
        setBoardButton->setObjectName(QString::fromUtf8("setBoardButton"));

        mainGrid->addWidget(setBoardButton, 3, 2, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        mainGrid->addWidget(label, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mainGrid->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        playPauseButton = new QPushButton(centralwidget);
        playPauseButton->setObjectName(QString::fromUtf8("playPauseButton"));

        mainGrid->addWidget(playPauseButton, 0, 4, 1, 1);

        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setStyleSheet(QString::fromUtf8("font: 300 18pt \"Segoe UI Light\";\n"
"color: rgb(0, 0, 0);\n"
""));

        mainGrid->addWidget(titleLabel, 0, 0, 1, 1);

        boardFrame = new QFrame(centralwidget);
        boardFrame->setObjectName(QString::fromUtf8("boardFrame"));
        boardFrame->setMinimumSize(QSize(512, 512));
        boardFrame->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(40, 29, 3, 255), stop:0.0852273 rgba(46, 28, 7, 255), stop:0.159091 rgba(73, 47, 10, 255), stop:0.238636 rgba(48, 36, 17, 255), stop:0.318182 rgba(57, 31, 9, 255), stop:0.386364 rgba(39, 25, 6, 255), stop:0.477273 rgba(62, 36, 15, 255), stop:0.568182 rgba(48, 33, 13, 255), stop:0.642045 rgba(53, 32, 13, 255), stop:0.695 rgba(41, 25, 14, 255), stop:0.721591 rgba(73, 49, 34, 255), stop:0.789773 rgba(43, 25, 4, 255), stop:0.857955 rgba(58, 37, 16, 255), stop:0.982955 rgba(41, 26, 8, 255), stop:1 rgba(41, 28, 3, 255));"));
        boardFrame->setFrameShape(QFrame::StyledPanel);
        boardFrame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(boardFrame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        cellGrid = new QGridLayout();
        cellGrid->setSpacing(0);
        cellGrid->setObjectName(QString::fromUtf8("cellGrid"));
        cellGrid->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_3->addLayout(cellGrid, 0, 0, 1, 1);


        mainGrid->addWidget(boardFrame, 1, 4, 7, 4);


        gridLayout_2->addLayout(mainGrid, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(quitButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BINAIRO", nullptr));
        checkPushButton->setText(QCoreApplication::translate("MainWindow", "Check", nullptr));
        randomRadioButton->setText(QCoreApplication::translate("MainWindow", "Generate random", nullptr));
        errorLabel->setText(QString());
        inputLine->setInputMask(QString());
        inputLine->setText(QString());
        inputLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Input seed", nullptr));
        inputRadioButton->setText(QCoreApplication::translate("MainWindow", "Fill from input", nullptr));
        quitButton->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        infoButton->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        winLabel->setText(QString());
        manualRadioButton->setText(QCoreApplication::translate("MainWindow", "Set manually", nullptr));
        setBoardButton->setText(QCoreApplication::translate("MainWindow", "Set board", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Board size:", nullptr));
        playPauseButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "B I N A I R O", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
