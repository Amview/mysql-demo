#include "customtreewidget.h"
#include <QMenu>
CustomTreeWidget::CustomTreeWidget(QWidget *parent)
    : QTreeWidget{parent}
{
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &QTreeWidget::customContextMenuRequested,this, &CustomTreeWidget::showContextMenu);
}

void CustomTreeWidget::showContextMenu(const QPoint &pos)
{
    QMenu menu(this);
    QTreeWidgetItem *item = this->itemAt(pos);
    if (item != nullptr && item->type() == CONNECT) {
        QAction *action1 = menu.addAction("删除");
        // 连接动作的触发信号到槽函数
        connect(action1, &QAction::triggered, this, [this, &item](){
            delete item;
        });
    }

    // 获取鼠标点击位置
    QPoint globalPos = this->viewport()->mapToGlobal(pos);
    menu.exec(globalPos);

}
