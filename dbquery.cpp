#include "dbquery.h"
#include <mysql/jdbc.h>
#include <qDebug>
#include <QMessageBox>
DbQuery::DbQuery(QObject *parent)
    : QObject{parent}
{}

int DbQuery::init_connect(string host, string port, string username, string password)
{
    try {
        driver = get_driver_instance();
        conn = driver->connect("tcp://" + host + ":" + port, username, password);
        if(!conn->isValid()) {
            cout<<"数据库连接无效"<<endl;
        } else {
            cout<<"数据库连接成功"<<endl;
        }
    } catch (sql::SQLException e) {
        emit exception(e.getSQLStateCStr());
        return -1;
    }
    return 0;

}

sql::ResultSet* DbQuery::exec(string sql)
{
    try {
        stm = conn->createStatement();
        rss = stm->executeQuery(sql);
        return rss;
    } catch (sql::SQLException e) {
        emit exception(e.getSQLStateCStr());
        return nullptr;
    }
}
