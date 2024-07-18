#include "mainwindow.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QSplitter>
#include <QGraphicsBlurEffect>
void MainWindow::init_ui()
{
    // 主布局
    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->setContentsMargins(0,0,0,0);
    QWidget *mainWidget = new QWidget();
    mainWidget->setLayout(mainLay);
    setCentralWidget(mainWidget);
    setStyleSheet("background-color: #f8f8f8");

    // 工具栏
    QToolBar *toolBar = new QToolBar(this);
    toolBar->setStyleSheet(R"(border: none;)");
    addToolBar(toolBar);
    connBtn = new QToolButton();
    connBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // 设置按钮风格，使文字显示在图标下方
    connBtn->setIcon(QIcon(":/resource/newconnect.svg"));
    connBtn->setText("新建连接");
    queryBtn = new QToolButton();
    queryBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // 设置按钮风格，使文字显示在图标下方
    queryBtn->setIcon(QIcon(":/resource/query.svg"));
    queryBtn->setText("新建查询");
    toolBar->addWidget(connBtn);
    toolBar->addWidget(queryBtn);

    // 分栏
    QSplitter *split = new QSplitter(Qt::Horizontal);
    split->setStyleSheet(R"(
        QSplitter {
            border: 1px solid #dfdfdf;
        }
        QSplitter::handle {
            background-color: #dfdfdf;
            border-left: 1px solid #dfdfdf;
            image: url(:/resource/query.svg);
            height: 0px;
        }
        QSplitter::handle:vertical {

        }
    )");

    // 左侧布局
    QVBoxLayout *leftLay = new QVBoxLayout();
    leftLay->setContentsMargins(0, 0, 0, 0);
    QWidget *leftWidget = new QWidget();
    leftWidget->setMaximumWidth(300);
    leftWidget->setLayout(leftLay);
    leftWidget->setStyleSheet(R"(
        border: none;
    )");
    // 创建一个用于模糊的全屏透明QWidget
    setAttribute(Qt::WA_TranslucentBackground);

    // 右侧布局
    QVBoxLayout *rightLay = new QVBoxLayout();
    rightLay->setContentsMargins(0, 0, 0, 0);
    rightLay->setSpacing(0);
    QWidget *rightWidget = new QWidget();
    rightWidget->setLayout(rightLay);
    rightWidget->setStyleSheet(R"(
        border: none;
    )");

    // 数据树
    dsTree = new CustomTreeWidget();
    dsTree->setHeaderLabel("功能导航");
    dsTree->setHeaderHidden(true);
    dsTree->setIndentation(20);
    dsTree->setStyleSheet(R"(
        QTreeWidget {background-color: transparent;}
        /* 整个垂直滑动条的样式 */
        QScrollBar:vertical {
            border: none;
            background: #ececec;
            width: 8px; /* 滑动条的宽度 */
            margin: 0 0 0 0; /* 上下留空，左右不留空 */
        }
        QScrollBar::handle:vertical {
            /* 默认手柄样式 */
            background: #c2c2c2;
            min-height: 10px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical:hover {
            background: #7d7d7d;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px; /* 设置高度为0，隐藏滑块 */
        }
        QTreeWidget::item {
            height: 22px;
        }
        QTreeWidget::item:selected {
            background-color: #E6E6FA; /* 浅蓝色背景 */
            color: black; /* 黑色文字 */
        }
    )");

    // 标签
    tab = new Tab();

    // 右侧显示页面
    stackPage = new QStackedLayout();
    QWidget *stackWidget = new QWidget();
    stackWidget->setLayout(stackPage);

    mainLay->addWidget(split);

    split->addWidget(leftWidget);
    split->addWidget(rightWidget);

    leftLay->addWidget(dsTree);

    rightLay->addWidget(tab);
    rightLay->addWidget(stackWidget);

}
