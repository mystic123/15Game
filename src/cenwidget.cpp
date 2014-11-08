/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#include "cenwidget.h"
#include <QTimer>
#include <QRadioButton>
#include <QGroupBox>
#include <cstdlib>
#include <iostream>

CenWidget::CenWidget(QWidget *parent) :
	QWidget(parent), myTimer(this)
{
	layout = new QHBoxLayout(this);
	vlayout = new QVBoxLayout();
	board = new Board(this, EASY);


	this->vlayout->addWidget(createLevelGroupBox());
	this->vlayout->addLayout(createButtons());

	layout->addLayout(vlayout);
	layout->addWidget(board);

	this->myTimer.setInterval(350);
	connect(this->board, SIGNAL(animationOver()), this, SLOT(endTimer()));
}

QGroupBox* CenWidget::createLevelGroupBox()
{
	QGroupBox *gb = new QGroupBox(tr("Difficulty:"));
	QVBoxLayout *vbox = new QVBoxLayout;
	QRadioButton *easy = new QRadioButton(tr("&Easy"));
	QRadioButton *medium = new QRadioButton(tr("&Medium"));
	QRadioButton *hard = new QRadioButton(tr("&Hard"));
	easy->setChecked(1);

	easy->setObjectName("1");
	medium->setObjectName("2");
	hard->setObjectName("3");

	connect(easy, SIGNAL(clicked()), this, SLOT(setLvl()));
	connect(medium, SIGNAL(clicked()), this, SLOT(setLvl()));
	connect(hard, SIGNAL(clicked()), this, SLOT(setLvl()));

	vbox->addWidget(easy);
	vbox->addWidget(medium);
	vbox->addWidget(hard);
	vbox->addStretch(1);

	gb->setLayout(vbox);

	return gb;
}

QLayout* CenWidget::createButtons()
{
	this->new_gameB = new QPushButton(tr("&New Game"), this);
	this->hintB = new QPushButton(tr("&Show hint"), this);
	this->solB = new QPushButton(tr("&Show solution"), this);
	this->helpB = new QPushButton(tr("&Help"), this);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(new_gameB);
	vbox->addWidget(hintB);
	vbox->addWidget(solB);
	vbox->addWidget(helpB);

	connect(new_gameB, SIGNAL(clicked()), this, SLOT(newGameButton()));
	connect(hintB, SIGNAL(clicked()), this, SLOT(hintButton()));
	connect(solB, SIGNAL(clicked()), this, SLOT(solutionButton()));
	connect(helpB, SIGNAL(clicked()), this, SLOT(helpButton()));

	return vbox;
}

void CenWidget::newGameButton()
{
	astar.reset();
	board->reset();
	board->shuffle();
}

void CenWidget::hintButton()
{
	this->board->disableBlocks();
	hintB->setDisabled(1);
	this->hintB->setText(tr("&Please wait..."));
	solution *sol = this->astar.findSolution(this->board->getState());
	this->board->setSolution(sol);
	board->showSolution();
	this->board->setAnimation(0);
	sol->clear();
	this->board->setSolution(nullptr);
	this->board->enableBlocks();
	this->hintB->setText(tr("&Show hint"));
	hintB->setEnabled(1);
}

void CenWidget::solutionButton()
{
	if (!this->board->getAnimation()) {
		hintB->setDisabled(1);
		new_gameB->setDisabled(1);
		this->board->disableBlocks();
		this->solB->setText(tr("&Stop"));
		solution *sol = this->astar.findSolution(this->board->getState());
		this->board->setSolution(sol);
//		parent.setMessage(sol->size());
		connect(&myTimer, SIGNAL(timeout()), this->board, SLOT(showSolution()));
		this->myTimer.start();
	}
	else {
		endTimer();
	}
}

void CenWidget::helpButton()
{
}

void CenWidget::setLvl()
{
	QRadioButton *send = qobject_cast<QRadioButton *>(sender());
	switch (send->objectName().toInt()) {
		case 1:
			board->setLvl(EASY);
			break;
		case 2:
			board->setLvl(MED);
			break;
		case 3:
			board->setLvl(HARD);
			break;
	}
}


void CenWidget::endTimer()
{
	new_gameB->setEnabled(1);
	hintB->setEnabled(1);
	this->myTimer.stop();
	this->solB->setText(tr("&Show solution"));
	this->board->enableBlocks();
	this->board->setAnimation(false);
}
