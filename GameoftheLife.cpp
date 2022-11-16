#include "GameoftheLife.h"
#include <iostream>

GameoftheLife::GameoftheLife(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.stackedWidget->setCurrentIndex(1);
    mapSize = 21;
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


void GameoftheLife::initializationTabMap() {
    resetMap();
    std::cout << "Initialization of the Map...\n";
    try
    {
        map.clear();
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





void GameoftheLife::changeForNewCellState() {
    
    QVector<QVector<int>> newMap = map;
    int alive = 0;
   

    for (int x = 0; x < mapSize-1; x++)
    {
        for (int y = 0; y < mapSize-1; y++)
        {
            /*      TOP     */
            if ((x - 1 >= 0) && (y - 1 >= 0)) {
                if (map[x - 1][y - 1] == 1) alive++; // Top Left
            }
            if ((x - 1 >= 0)) {
                if (map[x - 1][y] == 1) alive++; // Top Centre
            }
            if ((x - 1 >= 0) && (y + 1 < mapSize)) {
                if (map[x - 1][y + 1] == 1) alive++; // Top Right
            }


            /*      CENTER     */
            if ((x >= 0) && (y - 1 >= 0)) {
                if (map[x][y - 1] == 1) alive++;
            }
            if ((x >= 0) && (y + 1 >= 0)) {
                if (map[x][y + 1] == 1) alive++;
            }

            /*      BOTTOM     */
            if ((x + 1 >= 0) && (y - 1 >= 0)) {
                if (map[x + 1][y - 1] == 1) alive++; // Top Left
            }
            if ((x + 1 >= 0)) {
                if (map[x + 1][y] == 1) alive++; // Top Centre
            }
            if ((x + 1 >= 0) && (y + 1 < mapSize)) {
                if (map[x + 1][y + 1] == 1) alive++; // Top Right
            }
            if (alive != 2) {
                if (alive == 3) newMap[x][y] = 1;
                if (alive > 3 || alive < 2) newMap[x][y] = 0;
            }
            alive = 0;
            

        }
    }


    
    //copyMaps(map, newMap, mapSize);
    // A modifier 
    std::cout << "Copy in progress...\n";
    try
    {
        for (int i = 0; i < mapSize; i++)
        {
            for (int y = 0; y < mapSize; y++)
            {
                map[i][y] = newMap[i][y];
            }
        }
        std::cout << "Copy finished.";
    }
    catch (const std::exception&)
    {
        std::cout << "[ERROR] Copy of the Maps failed : \n";
    }
    
}

void GameoftheLife::updateMap() {
	changeForNewCellState();
    displayMap();
}

void GameoftheLife::displayMap() {
    ui.textBrowser->clear();
    for (int i = 0; i < mapSize; i++)
    {
        QString string;
        for (int y = 0; y < mapSize; y++)
        {
            if (!map[i][y]) string += QString::fromStdWString(L"\u2b1c");
            if (map[i][y]) string += QString::fromStdWString(L"\u2b1b");

        }
        ui.textBrowser->append(string);
    }
}


/*QVector<QVector<int>> GameoftheLife::copyMaps(QVector<QVector<int>> oldMap, QVector<QVector<int>> newMap, int size = -1) {
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
}*/


void GameoftheLife::on_pushButton_clicked() {
    ui.stackedWidget->setCurrentIndex(0);
    initializationTabMap();
    map[1][1] = 1;
    map[1][2] = 1;
    map[2][1] = 1;
    map[2][2] = 1;

    changeForNewCellState();
    displayMap();

}