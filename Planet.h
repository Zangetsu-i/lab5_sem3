#ifndef PLANET_H
#define PLANET_H

#include "CelestialBody.h"
#include <string>

using namespace std;

class Planet : public CelestialBody
{
private:
    const string res[5] {"Energy", "Water", "Metal", "Construction", "Food"};
    int num;
    string resource;
    double price;

public:
    Planet(int n = 0, string resName = "non", double pri = 0.0,
           double p = 0.0, double dem = 0.0, int tech = 0) 
        : CelestialBody(p, dem, tech), num(n), resource(resName), price(pri) {}

    Planet(const Planet & pl) : CelestialBody(pl)
    {
        price = pl.price;
        num = pl.num;
        resource = pl.resource;
    }

    Planet & operator=(const Planet & pl)
    {
        if (this == &pl) return *this;
        CelestialBody::operator=(pl);
        price = pl.price;
        num = pl.num;
        resource = pl.resource;
        return *this;
    }

    string getRes(int ind) const
    {
        if (ind >= 0 && ind < 5)
            return res[ind];
        return "Unknown";
    }

    int getNum() const { return num; }
    string getResourceName() const { return resource; }
    double getBasePrice() const { return price; }

    bool operator<(const Planet & pl) const { return num < pl.num; }
    bool operator>(const Planet & pl) const { return num > pl.num; }

    // Эффективная цена ресурса с учётом экономики
    double resourcePrice() const { return price * demCo() * techCo(); }

    // Производство ресурсов за ход
    double produceResources() const { return performance * techCo(); }
};

#endif
