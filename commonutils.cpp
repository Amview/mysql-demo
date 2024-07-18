#include "commonutils.h"

CommonUtils::CommonUtils(QObject *parent)
    : QObject{parent}
{}

QStringList CommonUtils::vector2QStringList(std::vector<std::string> vec) {
    QStringList qList;
    for (const auto& str : vec) {
        qList.append(QString::fromStdString(str));
    }
    return qList;
}
