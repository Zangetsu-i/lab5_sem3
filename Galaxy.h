#ifndef GALAXY_H
#define GALAXY_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Planet.h"
#include "Asteroid.h"

using namespace std;

class Galaxy
{
private:
    struct Node
    {
        Planet planet;
        double routeCost;      // Стоимость топлива
        int securityLevel;     // Уровень безопасности (1-5)
        Node * next;
        
        Node(const Planet & p, double c, int sec, Node * t) 
            : planet(p), routeCost(c), securityLevel(sec), next(t) {}
    };

    typedef Node * link;

    link *adjList;           // Список смежности
    vector<Asteroid> asteroids;  // Астероиды в галактике
    int planetCount;
    int routeCount;

    Galaxy(const Galaxy & g) {}
    Galaxy & operator=(const Galaxy & g) { return *this; }

public:
    Galaxy(int pn, int rn) : planetCount(pn), routeCount(rn)
    {
        adjList = new link[pn];
        for (int i = 0; i < pn; i++)
            adjList[i] = nullptr;

        srand(time(0));

        // Генерация торговых маршрутов
        for (int i = 0; i < rn; i++)
        {
            int top1 = rand() % pn;
            int top2 = rand() % pn;
            if (top1 == top2) continue;

            Planet pl;
            string resName = pl.getRes(rand() % 5);

            Planet temp1(top1, resName, rand() % 100 + 10,
                         1.0 * (rand() % 80 + 20),
                         1.0 * (rand() % 80 + 20),
                         rand() % 6);

            resName = pl.getRes(rand() % 5);

            Planet temp2(top2, resName, rand() % 100 + 10,
                         1.0 * (rand() % 80 + 20),
                         1.0 * (rand() % 80 + 20),
                         rand() % 6);

            double cost = rand() % 60 + 20;    // Топливо 20-80
            int security = rand() % 5 + 1;     // Безопасность 1-5

            adjList[top1] = new Node(temp2, cost, security, adjList[top1]);
            adjList[top2] = new Node(temp1, cost, security, adjList[top2]);
        }

        // Генерация астероидов (10% от числа планет)
        int asteroidCount = max(1, pn / 10);
        for (int i = 0; i < asteroidCount; i++)
        {
            Asteroid ast(i, "Пояс-" + to_string(i), "Руда",
                        rand() % 150 + 50,    // Цена 50-200
                        rand() % 50 + 20,     // Стоимость добычи
                        1.0 * (rand() % 50 + 30),
                        1.0 * (rand() % 30 + 10),
                        rand() % 4);
            asteroids.push_back(ast);
        }
    }

    ~Galaxy()
    {
        for (int i = 0; i < planetCount; i++)
        {
            link t = adjList[i];
            while (t != nullptr)
            {
                link tmp = t->next;
                delete t;
                t = tmp;
            }
        }
        delete [] adjList;
    }

    void print() const
    {
        cout << "|      ТОРГОВЫЕ МАРШРУТЫ ГАЛАКТИКИ      |\n";
        
        for (int i = 0; i < planetCount; i++)
        {
            link t = adjList[i];
            while (t != nullptr)
            {
                cout << "Планета " << i
                     << " → Планета " << t->planet.getNum()
                     << " [" << t->planet.getResourceName() << "]\n"
                     << "  Цена: " << t->planet.resourcePrice() << " кр."
                     << " | Топливо: " << t->routeCost << " кр."
                     << " | Безопасность: " << t->securityLevel << "/5\n";
                t = t->next;
            }
        }

        if (!asteroids.empty())
        {
            cout << "|          АСТЕРОИДНЫЕ ПОЯСА        |\n";
            
            for (const auto& ast : asteroids)
            {
                cout << ast.getName() << " [" << ast.getResourceName() << "]\n"
                     << "  Цена добычи: " << ast.resourcePrice() << " кр.\n";
            }
        }
    }

    // Симуляция хода: возвращает прибыль и безопасность
    pair<double, int> simulateTurn() const
    {
        double totalProfit = 0.0;
        int avgSecurity = 0;
        int routesCounted = 0;

        for (int i = 0; i < planetCount; i++)
        {
            link t = adjList[i];
            while (t != nullptr)
            {
                double profit = t->planet.resourcePrice() - t->routeCost;
                
                // Учитываем риски: низкая безопасность = потери
                if (t->securityLevel < 3)
                    profit *= 0.8;  // -20% из-за пиратов
                
                if (profit > 0)
                    totalProfit += profit;
                
                avgSecurity += t->securityLevel;
                routesCounted++;
                
                t = t->next;
            }
        }

        // Добавляем прибыль от астероидов
        for (const auto& ast : asteroids)
        {
            double astProfit = ast.resourcePrice() - ast.getMiningCost();
            if (astProfit > 0)
                totalProfit += astProfit * 0.5;  // Меньше, т.к. сложнее добывать
        }

        int security = (routesCounted > 0) ? avgSecurity / routesCounted : 3;
        return {totalProfit, security};
    }

    // Улучшение маршрута (снижение затрат топлива)
    bool upgradeRoute(int planetFrom, double investAmount)
    {
        if (planetFrom < 0 || planetFrom >= planetCount)
            return false;

        link t = adjList[planetFrom];
        if (t != nullptr)
        {
            // Снижаем стоимость топлива на 20%
            t->routeCost *= 0.8;
            cout << "✓ Маршрут от планеты " << planetFrom 
                 << " улучшен! Новая стоимость: " << t->routeCost << " кр.\n";
            return true;
        }
        return false;
    }

    // Развитие планеты (увеличение производительности)
    bool upgradePlanet(int planetIdx, double investAmount)
    {
        if (planetIdx < 0 || planetIdx >= planetCount)
            return false;

        link t = adjList[planetIdx];
        if (t != nullptr)
        {
            // Увеличиваем производительность на 15%
            t->planet.improvePerformance(t->planet.getPerformance() * 0.15);
            cout << "✓ Планета " << planetIdx 
                 << " улучшена! Новая производительность: " 
                 << t->planet.getPerformance() << "\n";
            return true;
        }
        return false;
    }

    int getPlanetCount() const { return planetCount; }
    int getRouteCount() const { return routeCount; }
    int getAsteroidCount() const { return asteroids.size(); }
};

#endif