#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connectinfo.h"
#include "customtreewidget.h"
#include "dbquery.h"
#include "tab.h"
#include <QMainWindow>
#include <QToolButton>
#include <QStackedLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QToolButton *connBtn;
    QToolButton *queryBtn;
    CustomTreeWidget *dsTree;
    QStackedLayout *stackPage;
    Tab *tab;
    std::map<QTreeWidgetItem*, ConnectInfo*> itemInfoMap;
    std::map<QTreeWidgetItem*, DbQuery*> queryMap;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_ui();
    void init_data();
    void init_connect();
};
#endif // MAINWINDOW_H
