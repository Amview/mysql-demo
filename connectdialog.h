#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ConnectDialog : public QDialog
{
public:
    QLineEdit *name;
    QLineEdit *host;
    QLineEdit *port;
    QLineEdit *username;
    QLineEdit *passwd;

    ConnectDialog();

private slots:
    void checkBeforeClosing();
};

#endif // CONNECTDIALOG_H
