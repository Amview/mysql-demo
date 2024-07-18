#include "connectdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QBoxLayout>
#include <QMessageBox>
ConnectDialog::ConnectDialog() {
    QVBoxLayout *mainLay = new QVBoxLayout(this);
    setLayout(mainLay);

    QFormLayout *formLay = new QFormLayout();
    QWidget *formWidget = new QWidget();
    formWidget->setLayout(formLay);

    name = new QLineEdit("demo");
    host = new QLineEdit("127.0.0.1");
    port = new QLineEdit("3306");
    username = new QLineEdit("root");
    passwd = new QLineEdit();
    formLay->addRow("名称", name);
    formLay->addRow("主机", host);
    formLay->addRow("端口", port);
    formLay->addRow("用户", username);
    formLay->addRow("密码", passwd);

    // 创建按钮框
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    // 连接按钮框的 accepted 和 rejected 信号到 QDialog 的 accept 和 reject 槽
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &ConnectDialog::checkBeforeClosing);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    // 将按钮框添加到布局
    mainLay->addWidget(formWidget);
    mainLay->addWidget(buttonBox);
    setWindowTitle("新建连接");
}

void ConnectDialog::checkBeforeClosing()
{
    if (name->text().isEmpty() || host->text().isEmpty() || port->text().isEmpty()
        || username->text().isEmpty() || passwd->text().isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("不能输入为空"));
    } else {
        // 如果文本不为空，则正常关闭对话框
        accept();
    }
}
