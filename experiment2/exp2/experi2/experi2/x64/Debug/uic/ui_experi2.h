/********************************************************************************
** Form generated from reading UI file 'experi2.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPERI2_H
#define UI_EXPERI2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_experi2Class
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QTableView *tableView;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QMenuBar *menuBar;
    QMenu *menuLL_1;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *experi2Class)
    {
        if (experi2Class->objectName().isEmpty())
            experi2Class->setObjectName("experi2Class");
        experi2Class->resize(661, 405);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(experi2Class->sizePolicy().hasHeightForWidth());
        experi2Class->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(experi2Class);
        centralWidget->setObjectName("centralWidget");
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 511, 361));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        tableView = new QTableView(frame);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(0, 0, 511, 361));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(530, 0, 111, 104));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame_2);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(510, 100, 151, 31));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(510, 130, 151, 221));
        experi2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(experi2Class);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 661, 22));
        menuLL_1 = new QMenu(menuBar);
        menuLL_1->setObjectName("menuLL_1");
        experi2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(experi2Class);
        mainToolBar->setObjectName("mainToolBar");
        experi2Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(experi2Class);
        statusBar->setObjectName("statusBar");
        experi2Class->setStatusBar(statusBar);

        menuBar->addAction(menuLL_1->menuAction());

        retranslateUi(experi2Class);

        QMetaObject::connectSlotsByName(experi2Class);
    } // setupUi

    void retranslateUi(QMainWindow *experi2Class)
    {
        experi2Class->setWindowTitle(QCoreApplication::translate("experi2Class", "experi2", nullptr));
        pushButton->setText(QCoreApplication::translate("experi2Class", "\350\276\223\345\205\245\346\226\207\346\263\225", nullptr));
        pushButton_2->setText(QCoreApplication::translate("experi2Class", "\350\276\223\345\205\245\345\255\227\347\254\246\344\270\262", nullptr));
        pushButton_3->setText(QCoreApplication::translate("experi2Class", "\345\274\200\345\247\213\345\210\206\346\236\220", nullptr));
        menuLL_1->setTitle(QCoreApplication::translate("experi2Class", "LL(1)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class experi2Class: public Ui_experi2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPERI2_H
