/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#ifndef A_STAR_H
#define A_STAR_H

#include "global.h"
#include "board.h"
#include <list>
#include <set>
#include <queue>

using namespace std;

typedef set<boardState> examinedStates;
typedef	pair<int, pair<boardState, solution> > entry;

class A_star
{
public:
	A_star();
	void reset();

	solution* findSolution(boardState state);

private:
	examinedStates exSt;
	priority_queue<entry> queue;

	void examineState(entry &ex);
	int rateState(boardState state);

};

#endif // A_STAR_H
