#ifndef TABITEM_H
#define TABITEM_H

#include <QWidget>
#include <QMouseEvent>

class TabItem : public QWidget
{
    Q_OBJECT
private:

    /**
     * 标签名称
     * @brief name
     */
    std::string name;

    /**
     * 标签图标
     * @brief icon
     */
    QIcon icon;
public:
    // explicit TabItem(QWidget *parent = nullptr);

    TabItem() {}

    void setName(std::string name) {
        this->name = name;
    };

    void setIcon(QIcon& icon)  {
        this->icon = icon;
    };

    std::string getName() {
        return name;
    }

    QIcon getIcon() {
        return icon;
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            qDebug() << "Widget clicked at" << event->pos();
            this->setStyleSheet(R"(
            QWidget {
                border-right: 1px solid #dfdfdf;
                border-bottom: 1px solid #dfdfdf;
                background-color: white;
            }
            )");
            emit itemClicked(this);
        }
    }

signals:
    void itemClicked(TabItem* item);
    void itemClose(TabItem* item);
};

#endif // TABITEM_H
