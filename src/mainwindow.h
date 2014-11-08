/*
 * 15Game
 * 
 * Author: Paweł Kapica
 * 
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include "cenwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void setMessage(int x);

protected:

private slots:

private:
    QMenu *gameMenu, *newGameMenu;
    QActionGroup *levelG;
    QAction *easyG, *mediumG, *hardG, *undoG, *redoG, *showSol, *exitG;
    QPushButton *newGameBut, *undoB, *redoB, *showSolB, *showHintB;

    CenWidget *cenWidget;

    void createActions();
    void createMenus();


};

#endif // MAINWINDOW_H
