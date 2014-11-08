/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#include "board.h"
#include "global.h"
#include "global.cpp"
#include <QPixmap>
#include <QPropertyAnimation>
#include <iostream>


Board::Board(QWidget *parent, LVL lvl):QFrame(parent), lvl(lvl), animation(0)
{
	this->setParent(parent);

	this->setFixedSize(DIM*BUT_SIZE,DIM*BUT_SIZE);
	this->orgImg = new QPixmap(":/img.jpg");
	int j=0;
	for (int i=0; i<DIM*DIM-1; i++) {
		this->blocks[i] = new Block(this, QPixmap(orgImg->copy((i%DIM)*BUT_SIZE,
															 j*BUT_SIZE,BUT_SIZE,
															 BUT_SIZE)), i, i%DIM, j);
		this->blocks[i]->setGeometry((i%DIM)*BUT_SIZE, j*BUT_SIZE, BUT_SIZE,
							   BUT_SIZE);
		connect(blocks[i],SIGNAL(clicked()), this, SLOT(blockClicked()));
		if ((i%DIM)+1 == DIM)
			j++;
	}

	this->emptyBl = new Block(this, QPixmap(), DIM*DIM-1, DIM-1, DIM-1);
	this->emptyBl->setVisible(0);

	this->orgImg->~QPixmap();
}

Board::~Board()
{
	this->orgImg->~QPixmap();
	this->emptyBl->~Block();
	if (this->sol != nullptr) { //TU UNINITIALISED
		this->sol->clear();
		delete sol;
	}
	for (int i=0;i<DIM*DIM-1;i++) {
		blocks[i]->~Block();
	}
}

void Board::blockClicked()
{
	Block *send = qobject_cast<Block *>(sender());
	direction vec;
	vec={emptyBl->getX()-send->getX(),emptyBl->getY()-send->getY()};
	if ((vec.x==0 && abs(vec.y)==1) || (abs(vec.x)==1 && vec.y==0)) {
		send->animateMove(vec);
		vec*=(-1);
		emptyBl->rawMove(vec);
	}
}

void Board::shuffle()
{
	int i, random1, random2;
	i=0;
	do {
		i = 0;
		while (i < lvl) {
			random1 = rand()%(DIM*DIM);
			random2 = rand()%(DIM*DIM);
			if (random1 != random2) {
				swapBlocks(random1, random2);
				i++;
			}
		}
	} while (!isCorrect());
}

void Board::reset()
{
	for (int i=0; i<DIM*DIM-1; i++) {
		direction dir = {blocks[i]->getX() - i%DIM, blocks[i]->getY() - i/DIM };
		dir*=(-1);
		blocks[i]->rawMove(dir);
	}
}

void Board::swapBlocks(int b1, int b2)
{
	Block *block1, *block2;
	if (b1 < 15)
		block1 = blocks[b1];
	else
		block1 = emptyBl;
	if (b2 < 15)
		block2 = blocks[b2];
	else
		block2 = emptyBl;
	direction dir1, dir2;
	dir1 = { block2->getX()-block1->getX(), block2->getY()-block1->getY() };
	dir2=dir1*(-1);
	block1->rawMove(dir1);
	block2->rawMove(dir2);
}

bool Board::isCorrect()
{
	return 1-(DIM-emptyBl->getX()-1 + DIM-emptyBl->getY()-1)%2;
}

boardState Board::getState()
{
	boardState state = 0;
	short tab[DIM*DIM];
	for (int i=0; i<DIM*DIM; i++) {
		tab[blocks[i]->getX()+blocks[i]->getY()*DIM] = i;
	}
	//pusty blok
	tab[emptyBl->getX()+emptyBl->getY()*DIM] = DIM*DIM-1;
	for (int i=DIM*DIM-1; i>=0; i--) {
		state += tab[i];
		if (i>0)
			state = (state << 4);
	}
	return state;
}

/*void printState()
{
	boardState state = this->getState();
	for (int i=0; i<DIM*DIM; i++) {
		std::cerr<<state%16<<" ";
		if ((i+1)%4 == 0)
			std::cerr<<"\n";
		state = (state >> 4);
	}
}*/


void Board::showSolution()
{
	if (this->sol->size() > 0) {
		animation = 1;
		Block *b = blocks[this->sol->front()];
		this->sol->pop_front();
		direction vec;
		vec={ emptyBl->getX()-b->getX(),emptyBl->getY()-b->getY() };
		b->animateMove(vec);
		vec*=(-1);
		emptyBl->rawMove(vec);
	}
	else {
		animation = 0;
		this->animationOver();
	}
}

void Board::disableBlocks()
{
	for (int i = 0; i<DIM*DIM; i++)
		this->blocks[i]->setDisabled(1);
}

void Board::enableBlocks()
{
	for (int i = 0; i<DIM*DIM; i++)
		this->blocks[i]->setEnabled(1);
}
