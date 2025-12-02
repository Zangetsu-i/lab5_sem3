#ifndef ASTEROID_H
#define ASTEROID_H
#include "CelestialBody.h"
using namespace std;
class Asteroid : public CelestialBody
{
    private:
        string name;
        string resource;
        double price;
        double astPrice;
    public:
        Asteroid(string n, string res, double pri, double ap, double p, double dem, int tech) : CelestialBody(p, dem, tech)
        {
            price = pri;
            name = n;
            resource = res;
            astPrice = ap;
        }
        Asteroid(const Asteroid & as) : CelestialBody(as)
        {
            price = as.price;
            astPrice = as.astPrice;
            name = as.name;
            resource = as.resource;
        }
        Asteroid & operator=(const Asteroid & as)
        {
            if (this == &as)
                return *this;
            CelestialBody::operator=(as);
            price = as.price;
            astPrice = as.astPrice;
            name = as.name;
            resource = as.resource;
            return *this;
        }
        double AresourcePrice() {return (price + astPrice) * CelestialBody::demCo() * CelestialBody::techCo();}
};
#endif