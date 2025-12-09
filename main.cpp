#include <iostream>
#include <vector>
#include <iomanip>
#include "CelestialBody.h"
#include "Galaxy.h"
#include "Planet.h"
#include "Asteroid.h"
#include "Corporation.h"

using namespace std;

void printSeparator()
{
    cout << "\n════════════════════════════════════════════════════\n";
}

int main()
{
    cout << "|      ГАЛАКТИЧЕСКАЯ ЭКОНОМИКА: ИМПЕРИЯ ЗВЁЗД     |\n";

    int planetCount, corpCount, routeCount;
    cout << "Введите количество планет: ";
    cin >> planetCount;
    cout << "Введите количество корпораций: ";
    cin >> corpCount;
    cout << "Введите количество маршрутов: ";
    cin >> routeCount;

    int moves;
    cout << "Введите количество ходов: ";
    cin >> moves;

    printSeparator();

    // Создание галактики
    Galaxy galaxy(planetCount, routeCount);
    galaxy.print();

    // Создание корпораций
    vector<Corporation*> corporations;
    for (int i = 0; i < corpCount; ++i)
    {
        if (i % 3 == 0)
            corporations.push_back(new LogisticsCompany("Логистика-" + to_string(i/3 + 1)));
        else if (i % 3 == 1)
            corporations.push_back(new TechTrader("ТехТрейдер-" + to_string(i/3 + 1)));
        else
            corporations.push_back(new MinerCompany("Горнодобыча-" + to_string(i/3 + 1)));
    }

    cout << "|      КОРПОРАЦИИ     |\n";
    for (size_t i = 0; i < corporations.size(); ++i)
    {
        cout << (i+1) << ". " << corporations[i]->getName() 
             << " [" << corporations[i]->getType() << "]"
             << " (Капитал: " << corporations[i]->getCapital() << " кр.)\n";
    }

    double playerTotalProfit = 0.0;

    // ИГРОВОЙ ЦИКЛ
    for (int turn = 1; turn <= moves; ++turn)
    {
        printSeparator();
        cout << "╔════════════════ ХОД " << turn << " ════════════════╗\n";
        printSeparator();

        // Базовая экономика галактики
        pair<double, int> result = galaxy.simulateTurn();
        double baseProfit = result.first;
        int avgSecurity = result.second;

        
        cout << "\nЭкономика галактики:\n";
        cout << "   Базовая прибыль: " << fixed << setprecision(2) 
             << baseProfit << " кр.\n";
        cout << "   Средний уровень безопасности: " << avgSecurity << "/5\n\n";

        playerTotalProfit += baseProfit;

        // Распределение прибыли между корпорациями (с конкуренцией)
        cout << "Прибыль корпораций:\n";
        
        double sharePerCorp = baseProfit / corpCount;
        
        for (size_t i = 0; i < corporations.size(); ++i)
        {
            double profit = corporations[i]->calculateProfit(sharePerCorp, avgSecurity);
            corporations[i]->addProfit(profit);
            
            cout << "   " << (i+1) << ". " << corporations[i]->getName()
                 << ": +" << profit << " кр."
                 << " (Всего: " << corporations[i]->getTotalProfit() << " кр.)\n";
        }

        // Инвестиции (каждые 2 хода)
        if (turn % 2 == 0 && turn < moves)
        {
            printSeparator();
            cout << "ВОЗМОЖНОСТЬ ИНВЕСТИРОВАНИЯ\n\n";
            cout << "Ваш капитал: " << playerTotalProfit << " кр.\n\n";
            cout << "1. Улучшить маршрут (стоимость: 200 кр, -20% топлива)\n";
            cout << "2. Развить планету (стоимость: 300 кр, +15% производства)\n";
            cout << "3. Пропустить инвестиции\n";
            cout << "Выбор: ";
            
            int choice;
            cin >> choice;

            if (choice == 1 && playerTotalProfit >= 200)
            {
                int planetIdx = rand() % planetCount;
                if (galaxy.upgradeRoute(planetIdx, 200))
                {
                    playerTotalProfit -= 200;
                    cout << "✓ Инвестировано 200 кр.\n";
                }
            }
            else if (choice == 2 && playerTotalProfit >= 300)
            {
                int planetIdx = rand() % planetCount;
                if (galaxy.upgradePlanet(planetIdx, 300))
                {
                    playerTotalProfit -= 300;
                    cout << "✓ Инвестировано 300 кр.\n";
                }
            }
            else if (choice != 3)
            {
                cout << "Недостаточно средств или неверный выбор.\n";
            }
        }
    }

    // ИТОГИ ИГРЫ
    printSeparator();
    cout << "|      ИТОГИ       |\n";

    cout << "Ваша прибыль: " << playerTotalProfit << " кр.\n\n";

    // Поиск победителя среди корпораций
    int winnerIdx = 0;
    for (size_t i = 1; i < corporations.size(); ++i)
    {
        if (corporations[i]->getTotalProfit() > corporations[winnerIdx]->getTotalProfit())
            winnerIdx = i;
    }

    cout << "ЛИДЕР СРЕДИ КОРПОРАЦИЙ:\n";
    cout << "   " << corporations[winnerIdx]->getName()
         << " [" << corporations[winnerIdx]->getType() << "]\n"
         << "   Прибыль: " << corporations[winnerIdx]->getTotalProfit() << " кр.\n\n";

    cout << "Рейтинг корпораций:\n";
    for (size_t i = 0; i < corporations.size(); ++i)
    {
        cout << "   " << (i+1) << ". " << corporations[i]->getName()
             << " — " << corporations[i]->getTotalProfit() << " кр.\n";
    }

    printSeparator();

    // Очистка памяти
    for (auto corp : corporations)
        delete corp;

    return 0;
}
