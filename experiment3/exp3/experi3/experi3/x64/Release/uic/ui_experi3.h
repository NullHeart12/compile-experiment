/********************************************************************************
** Form generated from reading UI file 'experi3.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPERI3_H
#define UI_EXPERI3_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_experi3Class
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QTableView *tableView_2;
    QWidget *tab_3;
    QTableView *tableView;
    QWidget *tab_2;
    QListView *listView_2;
    QWidget *tab;
    QListView *listView;
    QFrame *frame_2;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QMenuBar *menuBar;
    QMenu *menuLR_1;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *experi3Class)
    {
        if (experi3Class->objectName().isEmpty())
            experi3Class->setObjectName("experi3Class");
        experi3Class->resize(900, 590);
        centralWidget = new QWidget(experi3Class);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 691, 541));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        tabWidget = new QTabWidget(frame);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 691, 541));
        tabWidget->setTabBarAutoHide(false);
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tableView_2 = new QTableView(tab_4);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(0, 0, 691, 521));
        tableView_2->setSortingEnabled(true);
        tableView_2->horizontalHeader()->setCascadingSectionResizes(false);
        tableView_2->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableView_2->horizontalHeader()->setStretchLastSection(true);
        tabWidget->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tableView = new QTableView(tab_3);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(0, 0, 691, 521));
        tableView->horizontalHeader()->setStretchLastSection(false);
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        listView_2 = new QListView(tab_2);
        listView_2->setObjectName("listView_2");
        listView_2->setGeometry(QRect(0, 0, 691, 521));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tab->setEnabled(true);
        listView = new QListView(tab);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(0, 0, 691, 521));
        tabWidget->addTab(tab, QString());
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(690, 0, 211, 541));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 0, 211, 141));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        pushButton = new QPushButton(frame_3);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame_3);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        textEdit = new QTextEdit(frame_2);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 140, 211, 41));
        textEdit_2 = new QTextEdit(frame_2);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(0, 180, 211, 361));
        experi3Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(experi3Class);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 900, 22));
        menuLR_1 = new QMenu(menuBar);
        menuLR_1->setObjectName("menuLR_1");
        experi3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(experi3Class);
        mainToolBar->setObjectName("mainToolBar");
        experi3Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(experi3Class);
        statusBar->setObjectName("statusBar");
        experi3Class->setStatusBar(statusBar);

        menuBar->addAction(menuLR_1->menuAction());

        retranslateUi(experi3Class);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(experi3Class);
    } // setupUi

    void retranslateUi(QMainWindow *experi3Class)
    {
        experi3Class->setWindowTitle(QCoreApplication::translate("experi3Class", "experi3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("experi3Class", "PROCESS", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("experi3Class", "ANALYSIS TABLE", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("experi3Class", "COLLECTION", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("experi3Class", "FIRST SET", nullptr));
        pushButton->setText(QCoreApplication::translate("experi3Class", "get the grammer", nullptr));
        pushButton_2->setText(QCoreApplication::translate("experi3Class", "get tht string", nullptr));
        pushButton_3->setText(QCoreApplication::translate("experi3Class", "scan", nullptr));
        menuLR_1->setTitle(QCoreApplication::translate("experi3Class", "LR(1)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class experi3Class: public Ui_experi3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPERI3_H
