#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <string>
class CelestialBody
{
    private:
        double perfomance;
        double demand;
        int technology;
    public:
        CelestialBody(double p = 0.0, double dem = 0.0, int tec = 0) {perfomance = p; demand = dem; technology = tec;}
        CelestialBody(const CelestialBody & c)
        {
            perfomance = c.perfomance;
            demand = c.demand;
            technology = c.technology;
        }
        CelestialBody & operator=(const CelestialBody & c)
        {
            if (this == &c)
                return *this;
            perfomance = c.perfomance;
            demand = c.demand;
            technology = c.technology;
            return *this;
        }
        
        double techCo() const {return 1 + technology / 10;}
        double demCo() const {return demand / perfomance;}
};
#endif