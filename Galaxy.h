#ifndef GALAXY_H
#define GALAXY_H
#include <string>
#include <ctime>
#include <cstdlib>
#include "Planet.h"
using namespace std;
class Galaxy
{
    private:
        struct Node
        {
            Planet v;
            Node * next;
            Node(Planet & x, Node * t) {v = x; next = t;}
        };
        typedef Node * link;

        link *array;
        int Planetn;
        int Routen;

        Galaxy(const Galaxy & g) {};
        Galaxy & operator=(const Galaxy & g) {return *this;}
    public:
        Galaxy(int pn, int rn) : Planetn(pn), Routen(rn)
        {
            array = new link[pn];
            for (int i = 0; i < pn; i++)
                array[i] = nullptr;
            srand(time(0));
            for (int i = 0; i < pn; i++)
            {
                int top1 = rand() % pn + 1;
                int top2 = rand() & pn + 1;
                Planet pl;
                string name = pl.getRes(rand() % 5 + 1);
                Planet temp1(top1, name, rand() % 100, 1.0 * (rand() % 100), 1.0 * (rand() % 100), rand() % 2);
                name = pl.getRes(rand() % 5 + 1);
                Planet temp2(top2, name, rand() % 100, 1.0 * (rand() % 100), 1.0 * (rand() % 100), rand() % 2);
                array[top1] = new Node(temp2, array[top1]);
                array[top2] = new Node(temp1, array[top2]);
            }
        }
};
#endif