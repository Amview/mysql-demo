#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidget>

class CustomTreeWidget : public QTreeWidget
{
public:

    enum ItemType {
        CONNECT = 0,
        DATABASE = 10,
        TABLE = 20
    };

    explicit CustomTreeWidget(QWidget *parent = nullptr);

    void enterEvent(QEnterEvent *event) override {
        QTreeWidget::enterEvent(event);
        // 当鼠标进入时显示滚动条
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }

    void leaveEvent(QEvent *event) override {
        QWidget::leaveEvent(event);
        // 当鼠标离开时隐藏滚动条
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

private slots:
    void showContextMenu(const QPoint &pos);
};

#endif // CUSTOMTREEWIDGET_H
