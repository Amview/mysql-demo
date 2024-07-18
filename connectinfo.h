#ifndef CONNECTINFO_H
#define CONNECTINFO_H

#include <QObject>

class ConnectInfo : public QObject
{
    Q_OBJECT
public:
    explicit ConnectInfo(QObject *parent = nullptr);

    std::string name;
    std::string host;
    std::string port;
    std::string username;
    std::string passwd;

signals:
};

#endif // CONNECTINFO_H
