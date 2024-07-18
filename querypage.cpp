#include "querypage.h"
#include "dbquery.h"
#include "resultutils.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QTableWidget>
QueryPage::QueryPage(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->setSpacing(0);
    setLayout(mainLay);
    // this->setStyleSheet(R"(
    //     QPushButton {
    //         border: 1px solid black;
    //     }
    // )");

    QHBoxLayout *btnsLay = new QHBoxLayout();
    btnsLay->setContentsMargins(10,10,10,10);
    btnsLay->setSpacing(10);
    QWidget *btnsWidget = new QWidget();
    btnsWidget->setLayout(btnsLay);

    QPushButton *runBtn = new QPushButton("运行");
    runBtn->setIcon(QIcon(":/resource/run.svg"));
    runBtn->setIconSize(QSize(15, 15));
    runBtn->setCursor(Qt::PointingHandCursor);
    // runBtn->setStyleSheet(R"(
    //     QPushButton {
    //         border: 1px solid black;
    //     }
    // )");

    connectBox = new QComboBox();
    connectBox->setMinimumWidth(150);
    connectBox->setFixedHeight(18);
    // connectBox->addItem("1212");
    connectBox->addItem("localhost");
    connectBox->setStyleSheet(R"(
        QComboBox {
            border: 1px solid #dfdfdf;
            border-radius: 6px;
        }
        QComboBox::drop-down {
            width: 0px;
            border-style: none;
        }
        QComboBox:on {
            background-color: #E6E6FA;
            color: black;
            width: 150px;
        }
        QComboBox QAbstractItemView {
            /* 背景颜色 */
            background-color: #F0F0F0;
            /* 边框 */
            border: none;
            /* 内边距 */
            padding: 4px;
            /* 字体大小 */
            font-size: 12px;
            /* 字体颜色 */
            color: black;
            border-radius: 3px;

        }
        QComboBox QAbstractItemView::item {
            /* 高度 */
            height: 30px;
            /* 对齐方式 */
            text-align: left;
            background-color: black;
        }
        QComboBox QAbstractItemView::item:hover {
            /* 背景颜色 */
            background-color: #E6E6FA;
            color: blue;
        }
    )");

    textEdit = new QTextEdit();
    textEdit->setStyleSheet(R"(
        background-color: white;
    )");

    resultTable = new QTableWidget();

    mainLay->addWidget(btnsWidget);
    mainLay->addWidget(textEdit);
    mainLay->addWidget(resultTable);

    btnsLay->addWidget(runBtn);
    btnsLay->addWidget(connectBox);
    btnsLay->addStretch(1);

    connect(runBtn, &QPushButton::clicked, [this]() {
        resultTable->clear();
        resultTable->setRowCount(0);
        QString host = this->connectBox->currentText();
        QString sql = this->textEdit->toPlainText();
        DbQuery *query = new DbQuery();
        int conn = query->init_connect(host.toStdString(), "3306", "root", "12345678");
        sql::ResultSet* rss;

        rss = query->exec(sql.toStdString());
        if (rss != nullptr) {
            QStringList labels;
            int i = 0;
            while (rss->next()) {
                ResultSetMetaData *metaData = rss->getMetaData();
                int colCount = metaData->getColumnCount();
                if (i == 0) {
                    for (int i = 1; i <= colCount; ++i) {
                        labels << QString::fromStdString(metaData->getColumnName(i).asStdString());
                    }
                    resultTable->setColumnCount(colCount);
                    resultTable->setHorizontalHeaderLabels(labels);
                    qDebug() << labels;
                }
                resultTable->insertRow(i);
                for (int j = 0; j < colCount; ++j) {
                    SQLString s = rss->getString(j+1);
                    resultTable->setItem(i, j, new QTableWidgetItem(QString::fromStdString(s.asStdString())));
                }
                i++;
            }
        }
    });
}
