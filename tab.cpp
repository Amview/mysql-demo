#include "tab.h"
#include "QtWidgets/qlabel.h"
#include <QScrollBar>
#include <QFrame>
Tab::Tab(QWidget *parent)
    : QScrollArea{parent} {

    QFrame *frame = new QFrame;
    frame->setFrameShape(QFrame::NoFrame);
    mainLay = new QHBoxLayout(frame);
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->setSpacing(0);
    mainLay->setAlignment(Qt::AlignLeft);
    // setLayout(mainLay);
    setWidget(frame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QScrollBar *hbar = this->horizontalScrollBar();
    hbar->setStyleSheet(R"(
        QScrollBar:horizontal {
            border: none;
            background: #ececec;
            height: 4px;
        }
        QScrollBar::handle:horizontal {
            background: #c2c2c2;
            min-width: 4px;
            border-radius: 2px;
        }
        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            height: 0px; /* 设置高度为0，隐藏滑块 */
        }
    )");
    this->setFixedHeight(30);
    // 创建一个滚动区域
    this->setWidgetResizable(true); // 允许滚动区域根据内容大小调整
}

void Tab::addItem(TabItem* tabItem)
{
    connect(tabItem, &TabItem::itemClicked, [this](TabItem *item) -> void {
        for (int i = 0; i < this->tabItems.size(); ++i) {
            if (this->tabItems[i] == item) {
                qDebug() << i;
                emit currentItemClicked(i);
                break;
            }
        }
    });
    connect(tabItem, &TabItem::itemClose, [this](TabItem *item) -> void {
        qDebug() << "点击关闭" << item << this->tabItems.size();
        int pos = -1;
        for (int i = 0; i < this->tabItems.size(); ++i) {
            if (this->tabItems[i] == item) {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            qDebug() << "关闭11";
            this->tabItems.erase(this->tabItems.begin() + pos);
            QLayoutItem *item = this->mainLay->takeAt(pos);
            if (item != nullptr) {
                qDebug() << "删除组件";
                delete item->widget();
                delete item;
                this->mainLay->update();
                emit currentItemClose(pos);
            }
        }
    });
    this->tabItems.push_back(tabItem);
    this->mainLay->addWidget(tabItem);
    this->update();
}

int Tab::getItem(std::string name) {
    for (int i = 0; i < this->tabItems.size(); ++i) {
        if (this->tabItems[i]->getName() == name) {
            return i;
        }
    }
    return -1;
}
