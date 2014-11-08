/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#ifndef CENWIDGET_H
#define CENWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QTimer>
#include <list>
#include "board.h"
#include "global.h"
#include "a_star.h"

class CenWidget : public QWidget
{
    Q_OBJECT
public:
	explicit CenWidget(QWidget *parent = 0);

public slots:
	void endTimer();

private:
    QHBoxLayout *layout;
	QVBoxLayout *vlayout;
	QPushButton *new_gameB, *hintB, *solB, *helpB;
	QTimer myTimer;
    Board *board;

	A_star astar;

	QGroupBox* createLevelGroupBox();
	QLayout* createButtons();

private slots:
	void newGameButton();
	void hintButton();
	void solutionButton();
	void helpButton();
	void setLvl();
};

#endif // CENWIDGET_H
