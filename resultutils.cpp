#include "resultutils.h"
#include "QtCore/qdebug.h"

ResultUtils::ResultUtils(QObject *parent)
    : QObject{parent}
{}

vector<string> ResultUtils::getColumnString(ResultSet* rss, int colNum) {
    vector<string> data;
    while (rss->next()) {
        ResultSetMetaData *metaData = rss->getMetaData();
        int colCount = metaData->getColumnCount();
        for (int i = 1; i <= colCount; ++i) {
            qDebug() << i;
            if (i == colNum) {
                // cout << rss->getString(i) << endl;
                data.push_back(rss->getString(i));
            }
        }
    }
    return data;
}
