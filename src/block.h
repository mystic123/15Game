/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#ifndef BLOCK_H
#define BLOCK_H

#include "global.h"
#include <QAbstractButton>
#include <QPixmap>
#include <QPropertyAnimation>

class Block : public QAbstractButton
{
    Q_OBJECT
public:
	Block(QWidget *parent, QPixmap img, short int id, short int x, short int y);
    void rawMove(direction dir);
	void animateMove(direction dir);
	QSize sizeHint() const { return pixmap.size(); }
    void paintEvent(QPaintEvent *e);
    int getId() { return this->id; }
    int getX() { return this->x; }
    int getY() { return this->y; }

private:
	QPixmap pixmap;
	QPropertyAnimation animation;

    int id;
    int x,y;
    void move(direction dir);


};

#endif // BLOCK_H
