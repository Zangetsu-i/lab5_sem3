#ifndef GALAXY_H
#define GALAXY_H
#include <string>
#include <ctime>
#include <cstdlib>
#include "bintree.h"
#include "Planet.h"
using namespace std;
class Galaxy
{
    private:
        struct Node
        {
            Planet n1;
            double route;
            Node * left;
            Node * right;

            Node(Planet pl, double rou) {n1 = pl; route = rou; left = nullptr; right = nullptr;}
        };
        typedef Node * link;
        Tree::link h = nullptr;
        int Planetn;
        int Routen;

        Galaxy(const Galaxy & g) {};
        Galaxy & operator=(const Galaxy & g) {return *this;}
    public:
        Galaxy(int pn, int rn)
        {
            srand(time(0));
            for (int i = 0; i < pn; i++)
            {

            }
        }
};
#endif