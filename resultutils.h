#ifndef RESULTUTILS_H
#define RESULTUTILS_H

#include <QObject>
#include <mysql/jdbc.h>
using namespace std;
using namespace sql;
class ResultUtils : public QObject
{
    Q_OBJECT
public:
    explicit ResultUtils(QObject *parent = nullptr);
    static vector<string> getColumnString(ResultSet* rss, int colNum);

signals:
};

#endif // RESULTUTILS_H
