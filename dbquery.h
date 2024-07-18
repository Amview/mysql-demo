#ifndef DBQUERY_H
#define DBQUERY_H

#include <QObject>
#include <string>
#include <mysql/jdbc.h>

using namespace std;
class DbQuery : public QObject
{
    Q_OBJECT
public:
    explicit DbQuery(QObject *parent = nullptr);
    string const host;
    string const port;
    string const username;
    string const password;
    sql::Driver *driver;
    sql::Connection *conn;
    sql::Statement *stm;
    sql::ResultSet *rss;

    int init_connect(string host, string port, string username, string password);
    sql::ResultSet* exec(string sql);

    ~DbQuery() {
        delete stm;
        delete rss;
    }

signals:
    void exception(string e);

};

#endif // DBQUERY_H
