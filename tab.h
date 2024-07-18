#ifndef TAB_H
#define TAB_H
#include "tabitem.h"
#include <QScrollArea>
#include <QHBoxLayout>

class Tab : public QScrollArea
{
    Q_OBJECT
public:
    std::vector<TabItem*> tabItems;
    QHBoxLayout *mainLay;
    explicit Tab(QWidget *parent = nullptr);
    void addItem(TabItem* item);
    int getItem(std::string name);
    void enterEvent(QEnterEvent *event) override {
        QWidget::enterEvent(event);
        // 当鼠标进入时显示滚动条
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }

    void leaveEvent(QEvent *event) override {
        QWidget::leaveEvent(event);
        // 当鼠标离开时隐藏滚动条
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }


signals:
    void currentItemClicked(int index);
    void currentItemClose(int index);
};

#endif // TAB_H
