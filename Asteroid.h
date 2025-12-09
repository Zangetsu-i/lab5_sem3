#ifndef ASTEROID_H
#define ASTEROID_H

#include "CelestialBody.h"
#include <string>

using namespace std;

class Asteroid : public CelestialBody
{
private:
    int num;
    string name;
    string resource;
    double price;
    double miningCost;  // Дополнительная плата за добычу

public:
    Asteroid(int n = 0, string nm = "Belt", string res = "Ore", 
             double pri = 0.0, double mc = 0.0,
             double p = 0.0, double dem = 0.0, int tech = 0) 
        : CelestialBody(p, dem, tech), num(n), name(nm), 
          resource(res), price(pri), miningCost(mc) {}

    Asteroid(const Asteroid & as) : CelestialBody(as)
    {
        price = as.price;
        miningCost = as.miningCost;
        num = as.num;
        name = as.name;
        resource = as.resource;
    }

    Asteroid & operator=(const Asteroid & as)
    {
        if (this == &as) return *this;
        CelestialBody::operator=(as);
        price = as.price;
        miningCost = as.miningCost;
        num = as.num;
        name = as.name;
        resource = as.resource;
        return *this;
    }

    int getNum() const { return num; }
    string getName() const { return name; }
    string getResourceName() const { return resource; }
    double getMiningCost() const { return miningCost; }

    // Цена ресурса с учётом затрат на добычу
    double resourcePrice() const 
    { 
        return (price + miningCost) * demCo() * techCo(); 
    }
};

#endif
