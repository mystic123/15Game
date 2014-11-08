/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#include "block.h"
#include "global.h"
#include <QPainter>
#include <iostream>

Block::Block(QWidget *parent, QPixmap img, short int id, short int x, short int y)
	:QAbstractButton(parent), pixmap(img), animation(this, "geometry"), id(id), x(x), y(y)
{
    this->setMinimumSize(BUT_SIZE, BUT_SIZE);
    this->update();
	this->animation.setDuration(300);
}


void Block::move(direction dir)
{
    this->x+=dir.x;
    this->y+=dir.y;
}

void Block::animateMove(direction dir)
{
	this->animation.setStartValue(QRect(this->x*BUT_SIZE, this->y*BUT_SIZE,
										BUT_SIZE, BUT_SIZE));
	QRect tmp(this->geometry());
	tmp.moveTo(tmp.x()+dir.x*BUT_SIZE, tmp.y()+dir.y*BUT_SIZE);
	this->animation.setEndValue(tmp);
	this->animation.start();
	this->move(dir);
}

void Block::rawMove(direction dir)
{
    this->move(dir);
    this->setGeometry(this->x*BUT_SIZE, this->y*BUT_SIZE, BUT_SIZE,
                                                                BUT_SIZE);
    this->update();
}

void Block::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
	painter.drawPixmap(0,0,pixmap);
}
