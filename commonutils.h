#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QObject>

class CommonUtils : public QObject
{
    Q_OBJECT
public:
    explicit CommonUtils(QObject *parent = nullptr);
    static QStringList vector2QStringList(std::vector<std::string> vec);
signals:
};

#endif // COMMONUTILS_H
