#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->init_ui();
    this->init_data();
    this->init_connect();
}

MainWindow::~MainWindow() {}
