#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameoftheLife.h"

class GameoftheLife : public QMainWindow
{
    Q_OBJECT

public:
    GameoftheLife(QWidget *parent = nullptr);
    ~GameoftheLife();

public slots:
    void on_pushButton_clicked();


private:
    Ui::GameoftheLifeClass ui;
    double pixel = 23.8095;
    QVector<QVector<int>> map;
    int mapSize = 21;
    int widgetX = 500;
    int widgetY = 500;

    //QVector<QVector<int>> copyMaps(QVector<QVector<int>> oldMap, QVector<QVector<int>> newMap, int);

    void checkCellule();
    void changeForNewCellState();

public:
    /*      INITIALIZATION      */
    void initializationTabMap();
    void resetMap();

    /*      ????        */
    void updateMap();
    void displayMap();


};
