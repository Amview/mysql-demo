#include "tableinfopage.h"
#include <QVBoxLayout>
#include <QLabel>
TableInfoPage::TableInfoPage(std::string table)
{
    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->setContentsMargins(0,0,0,0);
    setLayout(mainLay);

    QLabel *l = new QLabel(QString::fromStdString(table));
    mainLay->addWidget(l);
}
