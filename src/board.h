/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#ifndef BOARD_H
#define BOARD_H

#include "global.h"
#include "block.h"
#include <QFrame>
#include <iostream>

using namespace std;

class Board : public QFrame
{
    Q_OBJECT
public:
	Board(QWidget *parent, LVL lvl);
    ~Board();
    void setLvl(LVL lvl) { this->lvl = lvl; }
	boardState getState();
	void setSolution(solution *sol) { this->sol = sol; }
	void disableBlocks();
	void enableBlocks();
	void shuffle();
	void reset();
	bool getAnimation() { return this->animation; }
	void setAnimation(bool a) { this->animation = a; }

public slots:
    void blockClicked();
	void showSolution();

private:
    Block *blocks[DIM*DIM-1], *emptyBl;
    QPixmap *orgImg;

	solution *sol;

    LVL lvl;
	bool animation;

    void swapBlocks(int b1, int b2);
    bool isCorrect();

signals:
	void animationOver();

};

#endif // BOARD_H
