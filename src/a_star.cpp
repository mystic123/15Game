/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#include "a_star.h"
#include "global.h"
#include <iostream>


A_star::A_star(): exSt(), queue()
{
}

void A_star::reset()
{
	exSt.clear();
	while (!queue.empty()) {
		//delete queue.top().second.second;
		queue.pop();
	}
}

/*A_star::~A_star()
{
	this->exSt->clear();
	this->exSt->~set();
	delete this->exSt;
	while (!this->queue->empty()) {
		//entry *e = &this->queue->top();
		//delete e;
		this->queue->pop();
	}
}*/

void printState(boardState state)
{
	cerr<<"-----------------------------------\n";
	for (int i=0; i<DIM*DIM; i++) {
		if (state%16<10)
			cerr<<" ";
		cerr<<state%16<<"|";
		if ((i+1)%4 == 0)
			cerr<<"\n";
		state = (state >> 4);
	}
	cerr<<"-----------------------------------\n";
}

solution* A_star::findSolution(boardState state)
{
	//cerr<<"findSolution\n";
	solution s;
	entry e = make_pair(rateState(state)*(-1),make_pair(state,s));
	this->queue.push(e);
	bool found = 0;
	while (this->queue.size() > 0 && !found) {
		e = this->queue.top();
		this->queue.pop();
		if (e.first == 0) {
			/*cerr<<"znaleziono rozwiazanie!"<<endl;
			for (solution::iterator it = e.second.second.begin(); it != e.second.second.end(); it++) {
				cerr<<*it<<" ";
			}*/
			found = 1;
		}
		else
			examineState(e);
	}
	//cerr<<"\nkoniec findsolution\n";
	solution *res = new solution(e.second.second);
	reset();
	return res;
}

boardState createState(const short tab[])
{
	boardState result = 0;
	for (int i=DIM*DIM-1; i>=0; i--) {
		result += tab[i];
		if (i>0)
			result = (result << 4);
	}
	return result;
}

void A_star::examineState(entry &ex)
{
	boardState state = ex.second.first;
	//cerr<<"examineState "<<state<<" rate: "<<rateState(state)<<endl;
	this->exSt.insert(state);
	//cerr<<"pocz\n";
	//printState(state);
	short tab[DIM*DIM];
	for (int i=0; i<DIM*DIM; i++) {
		int block = state%16;
		state = (state >> 4);
		tab[i] = block;
	}
	//znajdowanie pustego
	int x=0;
	int y=0;
	while (tab[x+y*DIM]!=DIM*DIM-1) {
		if ((x+1)%DIM == 0) {
			x=-1;
			y++;
		}
		x++;
	}
	//x i y to wsp pustego
	if (x>0) {
		//ruch w lewo
		swap(tab[x-1+y*DIM],tab[x+y*DIM]);
		boardState st = createState(tab);
		//cerr<<"w lewo:\n";
		//printState(st);
		//cerr<<"rate: "<<rateState(st);
		if (this->exSt.find(st) == this->exSt.end()) {
			solution s(ex.second.second);
			s.push_back(tab[x+y*DIM]);
			entry ent = make_pair(rateState(st)*(-1),make_pair(st,s));
			this->queue.push(ent);
		}
		swap(tab[x+y*DIM],tab[x-1+y*DIM]);
	}
	if (x<DIM-1) {
		//ruch w prawo
		swap(tab[x+1+y*DIM],tab[x+y*DIM]);
		boardState st = createState(tab);
		//cerr<<"w prawo:\n";
		//printState(st);
		//cerr<<"rate: "<<rateState(st);
		if (this->exSt.find(st) == this->exSt.end()) {
			solution s(ex.second.second);
			s.push_back(tab[x+y*DIM]);
			entry ent = make_pair(rateState(st)*(-1),make_pair(st,s));
			this->queue.push(ent);
		}
		swap(tab[x+y*DIM],tab[x+1+y*DIM]);
	}
	if (y>0) {
		//ruch w gore
		swap(tab[x+y*DIM-DIM],tab[x+y*DIM]);
		boardState st = createState(tab);
		//cerr<<"w gore:\n";
		//printState(st);
		//cerr<<"rate: "<<rateState(st);
		if (this->exSt.find(st) == this->exSt.end()) {
			solution s(ex.second.second);
			s.push_back(tab[x+y*DIM]);
			entry ent = make_pair(rateState(st)*(-1),make_pair(st,s));
			this->queue.push(ent);
		}
		swap(tab[x+y*DIM],tab[x+y*DIM-DIM]);
	}
	if (y<DIM-1) {
		//ruch w dol
		swap(tab[x+y*DIM+DIM],tab[x+y*DIM]);
		boardState st = createState(tab);
		//cerr<<"w dol:\n";
		//printState(st);
		//cerr<<"rate: "<<rateState(st);
		if (this->exSt.find(st) == this->exSt.end()) {
			solution s(ex.second.second);
			s.push_back(tab[x+y*DIM]);
			entry ent = make_pair(rateState(st)*(-1),make_pair(st,s));
			this->queue.push(ent);
		}
		swap(tab[x+y*DIM],tab[x+y*DIM+DIM]);
	}
}

int A_star::rateState(boardState state)
{
	int x = 0;
	int y = 0;
	int result = 0;
	for (int i=0; i<DIM*DIM; i++) {
		int block = state%16;
		if (block != x + y*DIM) {
			result+=abs(x-block%DIM)+abs(y-block/DIM);
		}
		if ((i+1)%DIM == 0) {
			x=-1;
			y++;
		}
		state = (state >> 4);
		x++;
	}
	return result;
}
