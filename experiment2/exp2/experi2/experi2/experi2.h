#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_experi2.h"
#include <QStandardItemModel>

class experi2 : public QMainWindow
{
    Q_OBJECT

public:
    experi2(QWidget *parent = nullptr);
    ~experi2();
    QStandardItemModel* model;
    QChar null;
    QChar S0;
    QHash<QChar, QVector<QString>> grammer;
    QHash<QChar, QSet<QChar>> FIRST;
    QHash<QChar, QSet<QChar>> FOLLOW;
    QString input;
    QHash<QPair<QChar, QChar>, QString> M;

    void test_show();


public slots:
    void cre_grammer();
    void get_input();
    void analyse();

private:
    Ui::experi2Class ui;
    void analyse_single(QString single);
    bool cre_FIRST();
    void FIRST_elem(QChar head);
    bool cre_FOLLOW();
    void FOLLOW_elem(QChar head);
    void cre_M();
    void cre_M_elem(QChar head);
    QString reverse(QString str);
    void ana_step(int& step, QString& ana_stack, QString& res_str);
    
};
