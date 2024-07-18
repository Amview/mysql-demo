#include "tableinfotabitem.h"
#include "QtWidgets/qlabel.h"

TableInfoTabItem::TableInfoTabItem(std::string name) {
    setName(name);
    itemLay = new QHBoxLayout();
    itemLay->setContentsMargins(0,0,0,0);
    itemLay->setSpacing(0);
    this->setStyleSheet(R"(
        QWidget {
            border-right: 1px solid #dfdfdf;
            border-bottom: 1px solid #dfdfdf;
            background-color: #f8f8f8;
        }

    )");
    setFixedHeight(30);
    setFixedWidth(200);
    closeBtn = new QPushButton("");
    closeBtn->setIcon(QIcon(":/resource/close.svg"));
    closeBtn->setFixedSize(30, 30);
    closeBtn->setStyleSheet("border-right: none;");
    QLabel *label = new QLabel(QString::fromStdString(name));
    label->setStyleSheet("border-left: none;");
    itemLay->addWidget(closeBtn);
    itemLay->addWidget(label);
    setLayout(itemLay);

    QObject::connect(closeBtn, &QPushButton::clicked, [this]() -> void {
        emit itemClose(this);
    });
}
