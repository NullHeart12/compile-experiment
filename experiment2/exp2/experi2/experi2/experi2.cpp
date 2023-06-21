#include "experi2.h"
#include <qsizepolicy.h>
#include <QTextStream>
#include <QString>
#include <QVector>
#include <QMap>
#include <QSet>
#include <QChar>
#include <QList>
#include <QStringList>
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>
using namespace std;

experi2::experi2(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    model = new QStandardItemModel();

    QChar temp(0x03B5);
    null = temp;
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(cre_grammer()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(get_input()));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(analyse()));
}

experi2::~experi2()
{}

void experi2::cre_grammer()
{
    grammer.clear();
    FIRST.clear();
    FOLLOW.clear();
    M.clear();
    QString text = ui.textEdit_2->toPlainText();
    S0 = text[0];
    QString single;
    QString::iterator it;
    for (it = text.begin(); it != text.end(); it++)
    {
        if ((*it) != '\n') single.push_back(*it);
        else
        {
            analyse_single(single);
            single.clear();
        }
    }
    if ((*(it - 1)) != '\n' && it == text.end()) analyse_single(single);
    if (it == text.end())
        QMessageBox::information(this, "nice", "the grammer has been inputted");
    if (cre_FIRST())
        QMessageBox::information(this, "nice", "the FIRST set has been established");
    if(cre_FOLLOW())
        QMessageBox::information(this, "nice", "the FOLLOW set has been established");
    cre_M();
    return;
}

void experi2::analyse_single(QString single)
{
    QChar head = single[0];
    QString one;
    for (QString::iterator it = single.begin() + 3; it != single.end(); it++)
    {
        if ((*it) != '|') one.push_back(*it);
        else
        {
            grammer[head].push_back(one);
            one.clear();
        }
    }
    grammer[head].push_back(one);
    return;
}

bool experi2::cre_FIRST()
{
    for (QHash<QChar, QVector<QString>>::iterator it = grammer.begin(); it != grammer.end(); it++)
        if (FIRST[it.key()].isEmpty()) FIRST_elem(it.key());
    QHash<QChar, QVector<QString>>::iterator it = grammer.end();
    //for (it = grammer.begin(); it != grammer.end(); it++)
    //{
    //    for (QVector<QString>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
    //    {
    //        QString::iterator it3;
    //        for (it3 = (*it2).begin(); it3 != (*it2).end(); it3++)
    //        {
    //            QChar elem = (*it3);
    //            if (!elem.isUpper()) break;
    //            else
    //            {
    //                if (FIRST[elem].find(QChar('\u03B5')) != FIRST[elem].end()) continue;
    //                else FIRST[it.key()] += FIRST[elem];
    //            }
    //        }
    //        if (it3 == (*it2).end()) FIRST[it.key()].insert(QChar('\u03B5'));
    //    }
    //}
    if (it == grammer.end()) return true;
    else return false;
}

void experi2::FIRST_elem(QChar head)
{
    QVector<QString> elem = grammer[head];
    for (QVector<QString>::iterator it = elem.begin(); it != elem.end(); it++)
    {
        QChar e_head = (*it)[0];
        if(!e_head.isUpper()) FIRST[head].insert(e_head); 
        else
        {
            if (FIRST[e_head].isEmpty()) FIRST_elem(e_head);
            if (FIRST[e_head].find(null) == FIRST[e_head].end()) FIRST[head] += FIRST[e_head];
            else
            {
                QSet<QChar> copy = FIRST[e_head];
                copy.remove(null);
                FIRST[head] += copy;
            }
        }
    }
}

bool experi2::cre_FOLLOW()
{
    QHash<QChar, QVector<QString>>::iterator it;
    for (it = grammer.begin(); it != grammer.end(); it++)
    {
        if (FOLLOW[it.key()].isEmpty())
            FOLLOW_elem(it.key());
    }
    if (it == grammer.end()) return true;
    else return false;
}

void experi2::FOLLOW_elem(QChar head)
{
    if (head == S0) FOLLOW[head].insert('#');
    for (QHash<QChar, QVector<QString>>::iterator it = grammer.begin(); it != grammer.end(); it++)
    {
        for (QVector<QString>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            if ((*it2) == "\u03B5") continue;
            for (QString::iterator it3 = (*it2).begin(); it3 != (*it2).end(); it3++)
            {
                if (head == (*it3) && it3 != (*it2).end() - 1)
                {
                    QChar succ = *(it3 + 1);
                    if (!succ.isUpper()) FOLLOW[head].insert(succ);
                    else
                    {
                        QSet<QChar> copy = FIRST[succ];
                        if (copy.find(null) != copy.end())
                        {
                            copy.remove(null);
                            if (FOLLOW[it.key()].isEmpty() && it.key() != head) FOLLOW_elem(it.key());
                            FOLLOW[head] += FOLLOW[it.key()];
                        }
                        FOLLOW[head] += copy;
                    }
                }
                else if (head == (*it3) && it3 == (*it2).end() - 1)
                {
                    if (FOLLOW[it.key()].isEmpty() && it.key() != head) FOLLOW_elem(it.key());
                    FOLLOW[head] += FOLLOW[it.key()];
                }
            }
        }
    }
}

void experi2::get_input()
{
    input = ui.textEdit->toPlainText();
    QString::iterator it = input.end()-1;
    if ((*it) == '#') QMessageBox::information(this, "nice", "input the text successfully");
    else
    {
        QMessageBox::information(this, "error", "please input it once again");
        input.clear();
    }
}

void experi2::cre_M()
{
    QHash<QChar, QVector<QString>>::iterator it;
    for (it = grammer.begin(); it != grammer.end(); it++)
        cre_M_elem(it.key());
    //M[{'F', 'i'}] = "i";
    if (it == grammer.end())
        QMessageBox::information(this, "nice", "the analyse table has been establish");
}

void experi2::cre_M_elem(QChar head)
{
    for (QSet<QChar>::iterator it = FIRST[head].begin(); it != FIRST[head].end(); it++)
    {
        if ((*it) == null)
        {
            for (QSet<QChar>::iterator it2 = FOLLOW[head].begin(); it2 != FOLLOW[head].end(); it2++)
                M[{head, (*it2)}].push_back(null);
            continue;
        }
        QVector<QString> copy = grammer[head];
        if (copy.size() == 1)
        {
            M[{head, * it}].append(copy[0]);
            continue;
        }
        else if (copy.size() == 2 && copy.indexOf("\u03B5") != -1)
        {
            copy.removeOne("\u03B5");
            M[{head, * it}].append(copy[0]);
            continue;
        }
        for (QVector<QString>::iterator it2 = grammer[head].begin(); it2 != grammer[head].end(); it2++)
        {
            if ((*it2)[0] == (*it))
            {
                M[{head, * it}].append((*it2));
                break;
            }
            for (QString::iterator it3 = it2->begin(); it3 != it2->end(); it3++)
            {
                if (!(*it3).isUpper()) break;
                if (FIRST[*it3].find(*it) != FIRST[*it3].end())
                {
                    M[{head, * it}].append(*it2);
                    goto label;
                }
                else if (FIRST[*it3].find(null) != FIRST[*it3].end()) continue;
                else break;
            }
        }
    label:
        continue;
    }
}

void experi2::analyse()
{
    model->clear();

    QStringList header;
    header << "step" << "analyse stack" << "rest string" << "production" << "action";
    model->setHorizontalHeaderLabels(header);
    ui.tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    QString ana_stack;
    QString res_string = input;
    ana_stack.push_back('#'); ana_stack.push_back(S0);

    QStandardItem* item1 = new QStandardItem("0");
    model->setItem(0, 0, item1);
    QStandardItem* item2 = new QStandardItem(ana_stack);
    model->setItem(0, 1, item2);
    QStandardItem* item3 = new QStandardItem(res_string);
    model->setItem(0, 2, item3);
    QStandardItem* item4 = new QStandardItem("initialize");
    model->setItem(0, 4, item4);

    int step = 1;
    ana_step(step, ana_stack, res_string);

    ui.tableView->verticalHeader()->setVisible(false);
    ui.tableView->setModel(model);
    test_show();
}

QString experi2::reverse(QString str)
{
    int i = 0, j = str.size() - 1;
    while (i < j)
    {
        swap(str[i], str[j]);
        i++; j--;
    }
    return str;
}

void experi2::ana_step(int& step, QString& ana_stack, QString& res_string)
{
    QChar stack_top = *(ana_stack.end() - 1);
    QChar string_head = res_string[0];
    QString production, action;
    if (stack_top == '#' && string_head == '#') return;
    if (stack_top == string_head)
    {
        ana_stack.chop(1);
        res_string.remove(0, 1);
        action = "GETNEXT(I)";
        QStandardItem* item4 = new QStandardItem(action);
        model->setItem(step, 4, item4);
    }
    else
    {
        if (M[{stack_top, string_head}].isEmpty())
        {
            QMessageBox::information(this, "error", "you input an error sentence");
            return;
        }
        QString sub_pro = M[{stack_top, string_head}];
        QString re_pro = reverse(sub_pro);
        production.push_back(stack_top);
        production.append("->");
        production.append(sub_pro);
        if (sub_pro == "\u03B5")
        {
            ana_stack.chop(1);
            action.append("POP");
        }
        else
        {
            action.append("POP,PUSH(");
            action.append(re_pro);
            action.push_back(')');
            ana_stack.chop(1);
            ana_stack.append(re_pro);
        }

        QStandardItem* item3 = new QStandardItem(production);
        model->setItem(step, 3, item3);
        QStandardItem* item4 = new QStandardItem(action);
        model->setItem(step, 4, item4);
    }
    QString str_step = QString::number(step);
    QStandardItem* item1 = new QStandardItem(str_step);
    model->setItem(step, 0, item1);
    QStandardItem* item2 = new QStandardItem(ana_stack);
    model->setItem(step, 1, item2);
    QStandardItem* item3 = new QStandardItem(res_string);
    model->setItem(step, 2, item3);
    qDebug() << step << ';' << ana_stack << ';' << res_string << ';' << production << ';' << action;
    ana_step(++step, ana_stack, res_string);
}

void experi2::test_show()
{
    QChar a(0x03B5);
    qDebug() << a;
    qDebug() << "grammer:";
    for (QHash<QChar, QVector<QString>>::iterator it = grammer.begin(); it != grammer.end(); it++)
    {
        qDebug() << it.key() << ':';
        QVector<QString> vector = *it;
        for (QVector<QString>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            qDebug() << "->" << (*it2);
        }
    }
    qDebug();
    qDebug() << "FIRST:";
    for (QHash<QChar, QSet<QChar>>::iterator it = FIRST.begin(); it != FIRST.end(); it++)
    {
        qDebug() << it.key();
        for (QSet<QChar>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            qDebug() << "first" << QString(*it2);
            if ((*it2) == a) qDebug() << "TRUE";
        }
    }
    qDebug();
    qDebug() << "FOLLOW:";
    for (QHash<QChar, QSet<QChar>>::iterator it = FOLLOW.begin(); it != FOLLOW.end(); it++)
    {
        qDebug() << it.key();
        for (QSet<QChar>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            qDebug() << "follow" << (*it2);
        }
    }
    qDebug();
    qDebug() << "M:";
    for (QHash<QPair<QChar, QChar>, QString>::iterator it = M.begin(); it != M.end(); it++)
    {
        qDebug() << it.key() << ':' << it.value();
    }
}