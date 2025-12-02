#ifndef CORPORATION_H
#define CORPORATION_H
#include "CelestialBody.h"
using namespace std;
class Corporation
{
    private:
        string typeBody;
        int technology;
    public:
        Corporation(int tech = 2, string tb = "All")
        {
            typeBody = tb;
            technology = tech;
        }
        Corporation(const Corporation & cor)
        {
            typeBody = cor.typeBody;
            technology = cor.technology;
        }
        Corporation & operator=(const Corporation & cor)
        {
            if (this == &cor)
                return *this;
            typeBody = cor.typeBody;
            technology = cor.technology;
            return *this;
        }
};
class LogisticsCompany : public Corporation
{
    public:
        LogisticsCompany() : Corporation() { };
        LogisticsCompany(const LogisticsCompany & log) : Corporation(log) {};
        LogisticsCompany & operator=(const LogisticsCompany & log)
        {
            if (this == &log)
                return *this;
            Corporation::operator=(log);
            return *this;
        }
};
class TechTrader : public Corporation
{
    public:
        TechTrader(int tech = 1) : Corporation(tech) {};
        TechTrader(const TechTrader & tech) : Corporation(tech) {};
        TechTrader & operator=(const TechTrader & tech)
        {
            if (this == &tech)
                return *this;
            Corporation::operator=(tech);
            return *this;
        }
};
class MinerCompany : public Corporation
{
    public:
        MinerCompany(int tech = 2, string mine) : Corporation(tech, mine) {};
        MinerCompany(const MinerCompany & mine) : Corporation(mine) {};
        MinerCompany & operator=(const MinerCompany & mine)
        {
            if (this == &mine)
                return *this;
            Corporation::operator=(mine);
            return *this;
        }
};
#endif