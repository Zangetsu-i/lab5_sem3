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
        Corporation(string tb = "All", int tech = 10)
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

};
#endif