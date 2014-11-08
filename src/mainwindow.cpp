/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#include "mainwindow.h"
#include <iostream>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->resize(600,450);
	createActions();
	createMenus();

	cenWidget = new CenWidget(this);
	this->setCentralWidget(cenWidget);
	statusBar()->showMessage(tr("Ready"), 1000);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setMessage(int x)
{
	QString begin(tr("Found solution in "));
	QString mid(x);
	QString end(tr(" moves."));

	statusBar()->showMessage(begin.append(mid).append(end), 5000);
}

void MainWindow::createActions()
{
	easyG = new QAction(tr("&Easy"), this);
	mediumG = new QAction(tr("&Medium"), this);
	hardG = new QAction(tr("&Hard"), this);
	undoG = new QAction(tr("&Undo move"), this);
	redoG = new QAction(tr("&Redo move"), this);
	showSol = new QAction(tr("&Show solution"), this);
	exitG = new QAction(tr("&Exit"), this);

	levelG = new QActionGroup(this);

	levelG->addAction(easyG);
	levelG->addAction(mediumG);
	levelG->addAction(hardG);
	//std::cerr<<levelG->checkedAction()->isChecked();
	//std::cerr<<levelG->checkedAction()//->text().QString::toStdString();

	connect(exitG, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
	gameMenu = this->menuBar()->addMenu(tr("&Game"));
	newGameMenu = gameMenu->addMenu(tr("&New"));
	newGameMenu->addAction(easyG);
	newGameMenu->addAction(mediumG);
	newGameMenu->addAction(hardG);
	gameMenu->addAction(undoG);
	gameMenu->addAction(redoG);
	gameMenu->addAction(showSol);
	gameMenu->addAction(exitG);

}
