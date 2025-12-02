#ifndef PLANET_H
#define PLANET_H
#include "CelestialBody.h"
using namespace std;
class Planet : public CelestialBody
{
    private:
        int num;
        string resource;
        double price;
    public:
        Planet(int n = 0, string res = "met", double pri = 0.0, double p = 0.0, double dem = 0.0, int tech = 0) : CelestialBody(p, dem, tech)
        {
            price = pri;
            num = n;
            resource = res;
        }
        Planet(const Planet & pl) : CelestialBody(pl)
        {
            price = pl.price;
            num = pl.num;
            resource = pl.resource;
        }
        Planet & operator=(const Planet & pl)
        {
            if (this == &pl)
                return *this;
            CelestialBody::operator=(pl);
            price = pl.price;
            num = pl.num;
            resource = pl.resource;
            return *this;
        }
        bool operator<(const Planet & pl) {return num < pl.num;}
        bool operator>(const Planet & pl) {return num > pl.num;}
        double resourcePrice() {return price * CelestialBody::demCo() * CelestialBody::techCo();}
};
class Asteroid : public CelestialBody
{
    private:
        int num;
        string resource;
        double price;
        double astPrice;
    public:
        Asteroid(int n, string res, double pri, double ap, double p, double dem, int tech) : CelestialBody(p, dem, tech)
        {
            price = pri;
            num = n;
            resource = res;
            astPrice = ap;
        }
        Asteroid(const Asteroid & as) : CelestialBody(as)
        {
            price = as.price;
            astPrice = as.astPrice;
            num = as.num;
            resource = as.resource;
        }
        Asteroid & operator=(const Asteroid & as)
        {
            if (this == &as)
                return *this;
            CelestialBody::operator=(as);
            price = as.price;
            astPrice = as.astPrice;
            num = as.num;
            resource = as.resource;
            return *this;
        }
        
        double AresourcePrice() {return (price + astPrice) * CelestialBody::demCo() * CelestialBody::techCo();}
};
#endif