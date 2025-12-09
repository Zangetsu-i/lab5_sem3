#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <iostream>
#include <string>

class CelestialBody
{
protected:
    double performance;  // Производительность (объем производства)
    double demand;       // Спрос (потребление)
    int technology;      // Уровень технологии (0-10)

public:
    CelestialBody(double p = 0.0, double dem = 0.0, int tec = 0) 
        : performance(p), demand(dem), technology(tec) {}

    CelestialBody(const CelestialBody & c)
        : performance(c.performance), demand(c.demand), technology(c.technology) {}

    CelestialBody & operator=(const CelestialBody & c)
    {
        if (this == &c) return *this;
        performance = c.performance;
        demand = c.demand;
        technology = c.technology;
        return *this;
    }

    virtual ~CelestialBody() {}

    // Коэффициент технологии
    double techCo() const { return 1.0 + technology / 10.0; }
    
    // Коэффициент спроса/предложения
    double demCo() const { return (performance == 0.0 ? 1.0 : demand / performance); }

    // Геттеры
    double getPerformance() const { return performance; }
    double getDemand() const { return demand; }
    int getTechnology() const { return technology; }

    // Сеттеры для улучшения
    void improvePerformance(double delta) { performance += delta; }
    void improveTechnology(int delta) { technology += delta; }
};

#endif
