/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#ifndef global_H
#define global_H

#include <list>

typedef unsigned long boardState;
typedef std::list<int> solution;

const short int DIM = 4;
const short int BUT_SIZE = 100;

enum LVL { EASY=10, MED=100, HARD=300 };

typedef struct {
    int x;
    int y;
} direction;

//inline direction operator*(direction dir, int a);
//inline direction& operator*=(direction &dir, int a);

int sgn(int x);

#endif // global_H
