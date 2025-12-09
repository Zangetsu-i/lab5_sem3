#ifndef CORPORATION_H
#define CORPORATION_H

#include "CelestialBody.h"
#include <string>

using namespace std;

class Corporation
{
protected:
    string name;
    string typeBody;
    int technology;
    double capital;
    double totalProfit;

public:
    Corporation(string nm = "Corp", int tech = 2, string tb = "All", double cap = 1000.0)
        : name(nm), typeBody(tb), technology(tech), capital(cap), totalProfit(0.0) {}

    Corporation(const Corporation & cor)
        : name(cor.name), typeBody(cor.typeBody), technology(cor.technology),
          capital(cor.capital), totalProfit(cor.totalProfit) {}

    Corporation & operator=(const Corporation & cor)
    {
        if (this == &cor) return *this;
        name = cor.name;
        typeBody = cor.typeBody;
        technology = cor.technology;
        capital = cor.capital;
        totalProfit = cor.totalProfit;
        return *this;
    }

    virtual ~Corporation() {}

    virtual double calculateProfit(double baseProfit, int securityLevel) 
    {
        return baseProfit * (1.0 + technology / 10.0);
    }

    string getName() const { return name; }
    string getType() const { return typeBody; }
    int getTech() const { return technology; }
    double getCapital() const { return capital; }
    double getTotalProfit() const { return totalProfit; }

    void addProfit(double profit) { totalProfit += profit; capital += profit; }
    bool canInvest(double amount) const { return capital >= amount; }
    void invest(double amount) { capital -= amount; }
};

class LogisticsCompany : public Corporation
{
public:
    LogisticsCompany(string nm = "Логистика-1") 
        : Corporation(nm, 2, "Логистика", 1200.0) {}

    LogisticsCompany(const LogisticsCompany & log) : Corporation(log) {}

    LogisticsCompany & operator=(const LogisticsCompany & log)
    {
        if (this == &log) return *this;
        Corporation::operator=(log);
        return *this;
    }

    // ИСПРАВЛЕНО: стабильная средняя прибыль
    double calculateProfit(double baseProfit, int securityLevel) override
    {
        // Бонус от высокой безопасности (до +35%)
        double securityBonus = 1.0 + (securityLevel * 0.07);
        return baseProfit * securityBonus;
    }
};

class TechTrader : public Corporation
{
public:
    TechTrader(string nm = "ТехТрейдер-1") 
        : Corporation(nm, 5, "Высокие технологии", 1500.0) {}

    TechTrader(const TechTrader & tt) : Corporation(tt) {}

    TechTrader & operator=(const TechTrader & tt)
    {
        if (this == &tt) return *this;
        Corporation::operator=(tt);
        return *this;
    }

    // ИСПРАВЛЕНО: высокие требования, но меньший бонус
    double calculateProfit(double baseProfit, int securityLevel) override
    {
        // Торгует только если прибыль >= 60 (было 40)
        if (baseProfit < 60.0) return baseProfit * 0.3; // 30% от низкой прибыли
        
        // Бонус снижен с 1.6 до 1.35
        return baseProfit * 1.35;
    }
};

class MinerCompany : public Corporation
{
public:
    MinerCompany(string nm = "Горнодобыча-1") 
        : Corporation(nm, 3, "Добыча на астероидах", 2000.0) {}

    MinerCompany(const MinerCompany & mc) : Corporation(mc) {}

    MinerCompany & operator=(const MinerCompany & mc)
    {
        if (this == &mc) return *this;
        Corporation::operator=(mc);
        return *this;
    }

    // ИСПРАВЛЕНО: стабильный доход + бонус от низкой безопасности
    double calculateProfit(double baseProfit, int securityLevel) override
    {
        // Добыча работает даже в опасных зонах
        // Низкая безопасность = больше свободных астероидов
        double riskBonus = 1.0 + ((5 - securityLevel) * 0.05);
        return baseProfit * 1.25 * riskBonus;
    }
};

#endif