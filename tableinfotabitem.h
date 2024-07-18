#ifndef TABLEINFOTABITEM_H
#define TABLEINFOTABITEM_H

#include <QHBoxLayout>
#include <QPushButton>
#include "tabitem.h"

class TableInfoTabItem : public TabItem
{
public:
    QHBoxLayout *itemLay;
    QPushButton *closeBtn;
    TableInfoTabItem(std::string name);
};

#endif // TABLEINFOTABITEM_H
