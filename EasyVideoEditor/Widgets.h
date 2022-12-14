#pragma once

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenubar.h>

/*
2022-11-11. Created by Sohn Young Jin
Widgets class control all included widgets in QMainWindow. It is implemented as a singleton pattern, so it can be accessed from anywhere in your code.
*/
// test
class Widgets
{
private:
    static Widgets* instance;
private:
    Widgets();
    ~Widgets();
public:
    // Window.
    QMainWindow* window;

    // Window content area.
    QWidget* contentArea;

    // Window menu bar.
    QMenuBar* menuBar;
public:
    // Get instance of Widgets class.
    static Widgets* getInstance();

    // Initialize ui widgets from QMainWindow.
    void initWidgets(QMainWindow* mainWindow);
};