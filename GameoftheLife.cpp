#include "GameoftheLife.h"
#include <iostream>

GameoftheLife::GameoftheLife(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.stackedWidget->setCurrentIndex(1);
}

GameoftheLife::~GameoftheLife()
{}


void GameoftheLife::resetMap() {
    ui.textBrowser->clear();
    ui.textBrowser->setFontPointSize(12);
    for (int i = 0; i < mapSize; i++)
    {
        QString tmp;
        for (int y = 0; y < mapSize; y++) {
            tmp += QString::fromStdWString(L"\u2b1c");
        }
        ui.textBrowser->append(tmp);
    }
}

void GameoftheLife::changeForNewCellState() {
    QVector<QVector<int>> newMap;
    int alive;
    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            if (map[x + 1][y - 1]) alive++;
            if (map[x + 1][y]) alive++;
            if (map[x + 1][y - 1]) alive++;

            if (map[x][y - 1]) alive++;
            if (map[x][y + 1]) alive++;

            if (map[x - 1][y - 1]) alive++;
            if (map[x - 1][y]) alive++;
            if (map[x - 1][y - 1]) alive++;

            if (alive == 3) newMap[x][y] = 1;
            //if (alive == 2) rien
            if (alive >= 3 || alive < 2) newMap[x][y] = 0;
        }
    }
    //map = copyMaps(map, newMap, mapSize);
}

void GameoftheLife::updateMap() {
    ui.textBrowser->clear();
    for (int i = 0; i < mapSize; i++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            QString string;
            for (int txt = 0; txt < mapSize; txt++)
            {
                if (map[i][y]) string += QString::fromStdWString(L"\u2b1c");
                if (!map[i][y]) string += QString::fromStdWString(L"\u2b1b");
            }
            ui.textBrowser->append(string);
        }
    }
}

QVector<QVector<int>> GameoftheLife::copyMaps(QVector<QVector<int>> oldMap, QVector<QVector<int>> newMap, int size = -1) {
    if (size == -1) size = mapSize;
    std::cout << "Copy in progress...\n";
    try
    {

        for (int i = 0; i < size; i++)
        {
            for (int y = 0; y < size; y++)
            {
                oldMap[i][y] = newMap[i][y];
            }
        }
        std::cout << "Copy finished.";
    }
    catch (const std::exception&)
    {
        std::cout << "[ERROR] Copy of the Maps failed : \n";
    }

    return oldMap;
}

void GameoftheLife::initializationTabMap() {
    resetMap();
    std::cout << "Initialization of the Map...\n";
    try
    {
        for (int i = 0; i < mapSize; i++)
        {
            QVector<int> tmp;
            for (int y = 0; y < mapSize; y++)
            {
                tmp.push_back(0);
            }
            map.push_back(tmp);
        }
        std::cout << "Initialization finished.\n";
    }
    catch (const std::exception&)
    {
        std::cout << "[ERROR] Initialization of the Map.\n";
    }
    
}


void GameoftheLife::on_pushButton_clicked() {
    ui.stackedWidget->setCurrentIndex(0);
    initializationTabMap();
}