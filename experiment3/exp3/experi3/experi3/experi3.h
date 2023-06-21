#pragma once
#ifndef EXPERI3_H
#define EXPERI3_H

#include <QtWidgets/QMainWindow>
#include "ui_experi3.h"
#include "project.h"
#include "project.cpp"
#include <QStandardItemModel>

class experi3 : public QMainWindow
{
    Q_OBJECT

public:
    experi3(QWidget *parent = nullptr);
    ~experi3();

    QChar null;
    QChar S0;
    QString input;
    QStandardItemModel* model;
    QStandardItemModel* model_1;
    
    QHash<QChar, QSet<QString>> grammer;
    QHash<QString, int> order;
    QHash<QChar, QSet<QChar>> FIRST;
    QVector<project> zero;
    QVector<QHash<QChar,QVector<project>>> states;
    QHash<QPair<int, QChar>, int> DFA_table;
    QHash<QPair<int, QChar>, QString> ACTION;
    QHash<QPair<int, QChar>, int> GOTO;

public slots:
    void get_grammer();
    void get_input();
    void analyse();

private:
    Ui::experi3Class ui;
    void analyse_single(int& count, const QString& single);
    void show_grammer();
    void cre_FIRST();
    void FIRST_elem(const QChar& head);
    void show_FIRST();
    void cre_state();
    QHash<QChar, QVector<project>> cre_projects(const QVector<project>& sub_curs);
    void cre_project(QHash<QChar, QVector<project>>& curs, const project& pre);
    void cre_ACTION_GOTO();
    bool analyse_single(int step, QVector<int>& states_stack, QString& sign_stack, QString& input_string);

};
#endif