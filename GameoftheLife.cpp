#include "GameoftheLife.h"
#include <iostream>
#include <QTimer>


GameoftheLife::GameoftheLife(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mapSize = 21;
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    initializationTabMap();
    timer->setTimerType(Qt::PreciseTimer);
    ui.horizontalSliderTimeUpdate->setValue(65);


}

GameoftheLife::~GameoftheLife() {
    timer->deleteLater();
}

void GameoftheLife::on_pushButtonStartGame_clicked() {
    ui.pushButtonClearMap->setEnabled(false);
    ui.pushButtonClearTable->setEnabled(false);
    timer->start(timeUpdate);
}

void GameoftheLife::on_pushButtonStopGame_clicked() {
    ui.pushButtonClearMap->setEnabled(true);
    ui.pushButtonClearTable->setEnabled(true);
    timer->stop();
}

void GameoftheLife::on_pushButtonUpdate_clicked() {
    updateTable();
}

void GameoftheLife::on_pushButtonClearMap_clicked() {
    initializationTabMap();
}

void GameoftheLife::on_pushButtonClearTable_clicked() {
    ui.textEditCell->clear();
    resetTable();
}

void GameoftheLife::on_horizontalSliderTimeUpdate_valueChanged() {
    timeUpdate = (3000-((double)ui.horizontalSliderTimeUpdate->value()*30))+1;
    if (timer->isActive()) {
        timer->stop();
        timer->start(timeUpdate);
    }
    ui.label->setText("Timer Update : " + QString::number(timeUpdate/1000) + "s");
}


void GameoftheLife::resetMap() {
    ui.textBrowser->clear();
    ui.textBrowser->setFontPointSize(12);
    for (int x = 0; x < mapSize; x++)
    {
        QString tmp;
        for (int y = 0; y < mapSize; y++) {
            tmp += QString::fromStdWString(L"\u2b1c");
        }
        ui.textBrowser->append(tmp);
    }
}

void GameoftheLife::resetTable() {
    std::cout << "Reset Table Started...\n";
    map.clear();
    for (int x = 0; x < mapSize; x++)
    {
        QVector<int> tmp;
        for (int y = 0; y < mapSize; y++)
        {
            tmp.push_back(0);
        }
        map.push_back(tmp);
    }
    std::cout << "Reset Table finished.\n";
}


void GameoftheLife::initializationTabMap() {
    resetMap();
    std::cout << "Initialization of the Map...\n";
    try
    {
        resetTable();
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


    for (int x = 0; x < mapSize - 1; x++)
    {
        for (int y = 0; y < mapSize - 1; y++)
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


    try {
        map = newMap;
    }
    catch (const std::exception&) {
        std::cout << "ERROR: copy failed > size not valid\n";
    }

}

void GameoftheLife::updateTable() {
    QString data = ui.textEditCell->toPlainText();
    QStringList strList = data.split(QRegExp("\n"), QString::SkipEmptyParts);
    for (int i = 0; i < strList.size(); i++)
    {
        QString tmpString = strList[i];
        QStringList tmpStringList = tmpString.split(QRegExp(","), QString::SkipEmptyParts); // vérifier le . et ,

        map[tmpStringList[1].toInt()][tmpStringList[0].toInt()] = 1;

    }
    displayMap();
}

void GameoftheLife::updateMap() {
    changeForNewCellState();
    displayMap();
}

void GameoftheLife::displayMap() {
    ui.textBrowser->clear();
    for (int x = 0; x < mapSize; x++)
    {
        QString string;
        for (int y = 0; y < mapSize; y++)
        {
            if (!map[x][y]) string += QString::fromStdWString(L"\u2b1c");
            if (map[x][y]) string += QString::fromStdWString(L"\u2b1b");

        }
        ui.textBrowser->append(string);
    }
}
