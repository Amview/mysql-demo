#ifndef QUERYPAGE_H
#define QUERYPAGE_H

#include <QTextEdit>
#include <QWidget>
#include <QComboBox>
#include <QTableWidget>

class QueryPage : public QWidget
{
    Q_OBJECT
public:
    QTextEdit *textEdit;
    QComboBox *connectBox;
    QTableWidget *resultTable;
    explicit QueryPage(QWidget *parent = nullptr);

signals:
};

#endif // QUERYPAGE_H
