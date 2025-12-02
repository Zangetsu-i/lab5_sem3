#ifndef PLANET_H
#define PLANET_H
#include "CelestialBody.h"
using namespace std;
class Planet : public CelestialBody
{
    private:
        string name;
        string resource;
        double price;
    public:
        Planet(string n, string res, double pri, double p, double dem, int tech) : CelestialBody(p, dem, tech)
        {
            price = pri;
            name = n;
            resource = res;
        }
        Planet(const Planet & pl) : CelestialBody(pl)
        {
            price = pl.price;
            name = pl.name;
            resource = pl.resource;
        }
        Planet & operator=(const Planet & pl)
        {
            if (this == &pl)
                return *this;
            CelestialBody::operator=(pl);
            price = pl.price;
            name = pl.name;
            resource = pl.resource;
            return *this;
        }
        double resourcePrice() {return price * CelestialBody::demCo() * CelestialBody::techCo();}
};
#endif