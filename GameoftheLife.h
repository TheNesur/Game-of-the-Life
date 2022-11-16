#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameoftheLife.h"

#include <QVector>

class GameoftheLife : public QMainWindow
{
    Q_OBJECT

public:
    GameoftheLife(QWidget* parent = nullptr);
    ~GameoftheLife();

public slots:
    void on_pushButtonStartGame_clicked();
    void on_pushButtonStopGame_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonClearMap_clicked();
    void on_pushButtonClearTable_clicked();
    void on_horizontalSliderTimeUpdate_valueChanged();
    void updateMap();


private:
    Ui::GameoftheLifeClass ui;
    double pixel = 23.8095;
    QVector<QVector<int>> map;
    int mapSize = 21;
    int widgetX = 500;
    int widgetY = 500;
    double timeUpdate = 1000;

    //void checkCellule();
    void changeForNewCellState();
    void updateTable();

    QTimer* timer;

public:
    /*      INITIALIZATION      */
    void initializationTabMap();
    void resetMap();
    void resetTable();

    /*      ????        */
    void displayMap();

};
