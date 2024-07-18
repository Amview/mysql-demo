#include "connectdialog.h"
#include "dbquery.h"
#include "mainwindow.h"
#include "querypage.h"
#include "resultutils.h"
#include "tableinfopage.h"
#include "tableinfotabitem.h"
#include "commonutils.h"
#include <QLabel>
#include <QMessageBox>
void MainWindow::init_connect()
{
    // 双击
    connect(dsTree, &QTreeWidget::itemDoubleClicked, [this](QTreeWidgetItem *item) -> void {
        qDebug() << "双击：" << item->text(0);
        if (CustomTreeWidget::CONNECT == item->type()) {
            DbQuery *query = new DbQuery();
            this->queryMap.insert(std::pair(item, query));
            auto it = itemInfoMap.find(item);
            if (it != itemInfoMap.end()) {
                ConnectInfo* conn = it->second;
                int success = query->init_connect(conn->host, conn->port, conn->username, conn->passwd);
                if (success == -1) {
                    QMessageBox::warning(this, tr("警告"), tr("连接信息错误"));
                } else {
                    sql::ResultSet* rss = query->exec("show databases");
                    vector<string> names = ResultUtils::getColumnString(rss, 1);
                    cout << names[0] << endl;
                    for (int i = 0; i < names.size(); ++i) {
                        QTreeWidgetItem *childItem = new QTreeWidgetItem(item, QStringList(QString::fromStdString(names[i])), CustomTreeWidget::DATABASE);
                        childItem->setIcon(0, QIcon(":/resource/database.svg"));
                    }
                }
            }
        } else if (CustomTreeWidget::DATABASE == item->type()) {
            std::string sql = "show tables from `" + item->text(0).toStdString() + "`";
            auto it = this->queryMap.find(item->parent());
            if (it != this->queryMap.end()) {
                DbQuery *query = it->second;
                sql::ResultSet* rss = query->exec(sql);
                vector<string> vec = ResultUtils::getColumnString(rss, 1);
                QStringList list = CommonUtils::vector2QStringList(vec);
                for (const auto &str : vec) {
                    QTreeWidgetItem *childItem = new QTreeWidgetItem(item, QStringList(QString::fromStdString(str)), CustomTreeWidget::TABLE);
                    childItem->setIcon(0, QIcon(":/resource/table.svg"));
                }
            }
        } else if (CustomTreeWidget::TABLE == item->type()) {
            qDebug() << "双击表" << item->text(0);
            string table = item->text(0).toStdString();
            string database = item->parent()->text(0).toStdString();
            string connect = item->parent()->parent()->text(0).toStdString();
            int index = this->tab->getItem(item->text(0).toStdString());
            if (index == -1) {
                qDebug() << "11";
                this->tab->addItem(new TableInfoTabItem(table));
                TableInfoPage *tablePage = new TableInfoPage(table);
                stackPage->addWidget(tablePage);
                stackPage->setCurrentIndex(stackPage->currentIndex() + 1);
            } else {
                stackPage->setCurrentIndex(index);
            }
        }
    });

    connect(tab, &Tab::currentItemClicked, [this](int index) -> void {
        this->stackPage->setCurrentIndex(index);
    });

    connect(tab, &Tab::currentItemClose, [this](int index) -> void {
        QWidget *w = this->stackPage->widget(index);
        this->stackPage->removeWidget(w);
    });

    connect(queryBtn, &QPushButton::clicked, [this](){
        qDebug() << "新查询";
        this->tab->addItem(new TableInfoTabItem("新查询"));
        QueryPage *page = new QueryPage();
        stackPage->addWidget(page);
        stackPage->setCurrentIndex(stackPage->currentIndex() + 1);

    });

    connect(connBtn, &QPushButton::clicked, [this](){
        qDebug() << "新查询";
        ConnectDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            ConnectInfo *info = new ConnectInfo();
            info->name = dialog.name->text().toStdString();
            info->host = dialog.host->text().toStdString();
            info->port = dialog.port->text().toStdString();
            info->username = dialog.username->text().toStdString();
            info->passwd = dialog.passwd->text().toStdString();
            string itemLabel =  info->name + "（" + info->host + "）";
            QTreeWidgetItem *item = new QTreeWidgetItem(dsTree, QStringList(QString::fromStdString(itemLabel)), CustomTreeWidget::CONNECT);
            itemInfoMap.insert(std::make_pair(item, info));
            item->setIcon(0, QIcon(":/resource/connect.svg"));
        }
    });


}
