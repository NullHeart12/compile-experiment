#include "experi3.h"
#include <QMessageBox>
#include <QStringListModel>
#include <QStandardItemModel>
using namespace std;

experi3::experi3(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);

    null = QChar(0x03B5);
    model = new QStandardItemModel();
    model_1 = new QStandardItemModel();

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(get_grammer()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(get_input()));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(analyse()));
}

experi3::~experi3()
{}

void experi3::get_grammer()
{
    grammer.clear();
    FIRST.clear();
    model->clear();
    model_1->clear();
    S0 = QChar::Null;
    order.clear();
    zero.clear();
    states.clear();
    DFA_table.clear();
    ACTION.clear();
    GOTO.clear();

    QString original_text = ui.textEdit_2->toPlainText();
    if (original_text.isEmpty())
    {
        QMessageBox::information(this, "error", "the grammer is empty");
        return;
    }
    else QMessageBox::information(this, "nice", "input successfully");
    QString single;
    int count = 0;
    if (original_text[3] == '-')
    {
        grammer['$'].insert(QString(original_text[2]));
        S0 = original_text[2];
        order[QString(S0)] = 0;
        QString::iterator it;
        for (it = original_text.begin(); it != original_text.end(); it++)
        {
            if ((*it) == '\n')
            {
                analyse_single(++count, single);
                single.clear();
            }
            else if ((*it).isSpace() || (*it).isDigit()) continue;
            else single.push_back(*it);
        }
        if ((*(it - 1)) != '\n' || it != original_text.end()) analyse_single(++count, single);
    }
    else
    {
        grammer['$'].insert(QString(original_text[6]));
        S0 = original_text[6];
        order[QString(S0)] = 0;
        QString::iterator it;
        for (it = original_text.begin() + 11; it != original_text.end(); it++)
        {
            if ((*it) == '\n')
            {
                analyse_single(++count, single);
                single.clear();
            }
            else if ((*it).isSpace() || (*it).isDigit()) continue;
            else single.push_back(*it);
        }
        if ((*(it - 1)) != '\n' || it != original_text.end()) analyse_single(++count, single);
    }
    zero = { project('$', *(grammer['$'].begin()), 0, { '#' }) };
    show_grammer();
    cre_FIRST();
    show_FIRST();
    cre_state();
    cre_ACTION_GOTO();
}

void experi3::analyse_single(int& count,const QString& single)
{
    QChar head = single[0];
    grammer[head].insert(single.mid(3));
    order[single.mid(3)] = count;
}

void experi3::show_grammer()
{
    for (QHash<QChar,QSet<QString>>::iterator it = grammer.begin(); it != grammer.end(); it++)
    {
        for (auto it2 = it->begin(); it2 != it->end(); it2++)
            qDebug() << order[*it2] << ":" << it.key() << "->" << (*it2);
    }
}

void experi3::cre_FIRST()
{
    for (auto it = grammer.begin(); it != grammer.end(); it++)
        if (it.key() != '$' && FIRST[it.key()].isEmpty()) FIRST_elem(it.key());
    if (!FIRST.isEmpty())
        QMessageBox::information(this, "nice", "the FIRST set has been made");
    else QMessageBox::information(this, "error", "the FIRST set is empty");
}

void experi3::FIRST_elem(const QChar& head)
{
    for (QSet<QString>::iterator it = grammer[head].begin(); it != grammer[head].end(); it++)
    {
        QString::const_iterator it2;
        for (it2 = it->begin(); it2 != it->end(); it2++)
        {
            if ((*it2) == head) break;
            if (!(*it2).isUpper())
            {
                FIRST[head] += {*it2};
                break;
            }
            if (FIRST[*it2].isEmpty()) FIRST_elem(*it2);
            QSet<QChar> copy = FIRST[*it2];
            copy.remove(null);
            FIRST[head] += copy;
            if (!FIRST[*it2].contains(null)) break;
        }
        if (it2 == it->end()) FIRST[head].insert(null);
    }
}

void experi3::show_FIRST()
{
    QStringList firsts;
    QString first;
    for (auto it = FIRST.begin(); it != FIRST.end(); it++)
    {
        first.append(it.key() + ':' + '\t');
        for (auto it2 = it->begin(); it2 != it->end(); it2++)
        {
            first.append('\'' + (*it2) + '\'' + '\t');
        }
        firsts.append(first);
        first.clear();
    }
    QStringListModel* model = new QStringListModel(firsts);
    ui.listView->setModel(model);
}

void experi3::cre_state()
{
    cre_projects(zero);
    QStringList Items;
    int len = states.size();
    for (int i = 0; i < len; i++)
    {
        Items.append("STATE." + QString::number(i));
        for (auto it = states[i].begin(); it != states[i].end(); it++)
        {
            for (auto pro : *it)
            {
                QString with_dot = pro.tail;
                with_dot.insert(pro.dot_pos, '.');
                Items.append(QString(pro.head) + "->" + with_dot + ' ' + *pro.lookahead.begin());
            }
        }
        Items.append(QString('\n'));
    }
    QStringListModel* model = new QStringListModel(Items);
    ui.listView_2->setModel(model);
    for (auto it = DFA_table.begin(); it != DFA_table.end(); it++)
        qDebug() << it.key() << ';' << it.value();
    qDebug();
    if (!states.isEmpty())
        QMessageBox::information(this, "nice", "the collections have been made");
    else QMessageBox::information(this, "error", "there is no collection");
}

QHash<QChar, QVector<project>> experi3::cre_projects(const QVector<project>& sub_curs)
{
    QHash<QChar, QVector<project>> curs;
    for (auto it = sub_curs.begin(); it != sub_curs.end(); it++)
        cre_project(curs, *it);
    if (!states.contains(curs))
    {
        states.emplace_back(curs);
        int cur_n = states.indexOf(curs);
        if (curs.contains('r'))
        {
            for (auto it = curs['r'].begin(); it != curs['r'].end(); it++)
            {
                if ((*it).head == '$')
                {
                    ACTION[{cur_n, '#'}] = "ACC";
                    continue;
                }
                project item = *it;
                for (auto sub_item : item.lookahead)
                    ACTION[{cur_n, sub_item}] = "R" + QString::number(order[item.tail]);
            }
        }
    }
    else return curs;
    auto copy(curs);
    for (auto it = copy.begin(); it != copy.end(); it++)
    {
        int cur_num = states.indexOf(curs);
        QChar next_char = it.key();

        bool ret = true;
        QVector<project> copy;
        for (auto it2 = it->begin(); it2 != it->end(); it2++)
        {
            if (it2->dot_pos < it2->tail.size())
            {
                ret=false;
                (*it2).dot_pos++;
                copy.emplace_back(*it2);
            }
            else continue;
        }
        if (ret) continue;
        std::sort(copy.begin(), copy.end());
        QHash<QChar, QVector<project>> next = cre_projects(copy);
        int next_num = states.indexOf(next);
        DFA_table[{cur_num, next_char}] = next_num;
    }
    return curs;
}

void experi3::cre_project(QHash<QChar, QVector<project>>& curs, const project& pre)
{
    if (pre.dot_pos == pre.tail.size() && !curs['r'].contains(pre)) curs['r'].emplace_back(pre);
    else if (pre.dot_pos < pre.tail.size() && !curs[pre.tail[pre.dot_pos]].contains(pre))
        curs[pre.tail[pre.dot_pos]].emplace_back(pre);
    if (pre.dot_pos >= pre.tail.size()|| !pre.tail[pre.dot_pos].isUpper()) return;
    QChar head = pre.tail[pre.dot_pos];
    for (auto it = grammer[head].begin(); it != grammer[head].end(); it++)
    {
        project cur;
        cur.head = head;
        cur.tail = (*it);
        cur.dot_pos = 0;
        if (pre.dot_pos == pre.tail.size() - 1) cur.lookahead = pre.lookahead;
        else if (!pre.tail[pre.dot_pos + 1].isUpper()) cur.lookahead = { pre.tail[pre.dot_pos + 1] };
        else cur.lookahead = FIRST[pre.tail[pre.dot_pos + 1]];
        if (!curs[cur.tail[cur.dot_pos]].contains(cur))
        {     
            //qDebug() << cur.dot_pos << ':' << cur.head << "->" << cur.tail << ',' << cur.lookahead;
            curs[cur.tail[cur.dot_pos]].emplace_back(cur);
            cre_project(curs, cur);
        }
        else return;
    }
}

void experi3::cre_ACTION_GOTO()
{
    for (auto it = DFA_table.begin(); it != DFA_table.end(); it++)
    {
        if (!it.key().second.isUpper())
        {
            
            ACTION[it.key()] = ("S" + QString::number(*it));
        }
        else GOTO[it.key()] = *it;
    }
    qDebug() << "ACTION";
    for (auto it = ACTION.begin(); it != ACTION.end(); it++)
        qDebug() << it.key() << ':' << *it;
    qDebug() << "GOTO";
    for (auto it = GOTO.begin(); it != GOTO.end(); it++)
        qDebug() << it.key() << ':' << *it;

    QStringList header;
    header.append("state");
    QVector<QChar> he;
    he.emplace_back('#');
    for (auto it = DFA_table.begin(); it != DFA_table.end(); it++)
    {
        if (!he.contains(it.key().second))
        {
            if (it.key().second.isUpper()) he.emplace_back(it.key().second);
            else he.insert(0, it.key().second);
        }
    }
    for (auto item : he)
    {
        header.append(QString(item));
    }
    ui.tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    model_1->setHorizontalHeaderLabels(header);
    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    int len_states = states.size();
    for (int i = 0; i < len_states; i++)
    {
        int len_he = he.size();
        QStandardItem* item1 = new QStandardItem(QString::number(i));
        model_1->setItem(i, 0, item1);
        for (int j = 0; j < len_he; j++)
        {
            if (ACTION.contains({ i,he[j] }))
            {
                QStandardItem* item2 = new QStandardItem(ACTION[{i, he[j]}]);
                model_1->setItem(i, j+1, item2);
            }
            else if (GOTO.contains({ i,he[j] }))
            {
                QStandardItem* item2 = new QStandardItem("G" + QString::number(GOTO[{i, he[j]}]));
                model_1->setItem(i, j+1, item2);
            }
        }
    }

    ui.tableView->verticalHeader()->setVisible(false);
    ui.tableView->setModel(model_1);
    if (!ACTION.isEmpty())
        QMessageBox::information(this, "nice", "the ACTION table has been made");
    else QMessageBox::information(this, "error", "the ACTION table is empty");
    if (!GOTO.isEmpty())
        QMessageBox::information(this, "nice", "the GOTO table has been made");
    else QMessageBox::information(this, "error", "the GOTO table is empty");
}

void experi3::get_input()
{
    input.clear();
    model->clear();
    input = ui.textEdit->toPlainText();
    if (input[input.size() - 1] != '#')
        QMessageBox::information(this, "error", "please enter once again");
    else QMessageBox::information(this, "nice", "input the string successfully");
}

void experi3::analyse()
{
    QStringList header;
    header << "steps" << "states stack" << "sign stack" << "input string" << "explain";
    ui.tableView_2->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    model->setHorizontalHeaderLabels(header);
    ui.tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    int step = 1;
    QVector<int> states_stack;
    states_stack.emplace_back(0);
    QString sign_stack = "#";
    QString rest_string = input;

    if (analyse_single(step, states_stack, sign_stack, rest_string))
        QMessageBox::information(this, "nice", "analyse successfully");
    else QMessageBox::information(this, "error", "analyse failed");

    ui.tableView_2->verticalHeader()->setVisible(false);
    ui.tableView_2->setModel(model);
}

bool experi3::analyse_single(int step, QVector<int>& states_stack, QString& sign_stack, QString& rest_string)
{
    QString str_step = QString::number(step);
    QStandardItem* item1 = new QStandardItem(str_step);
    model->setItem(step - 1, 0, item1);
    QString states;
    for (auto item : states_stack)
        states.append(QString::number(item) + ' ');
    QStandardItem* item2 = new QStandardItem(states);
    model->setItem(step - 1, 1, item2);
    QStandardItem* item3 = new QStandardItem(sign_stack);
    model->setItem(step - 1, 2, item3);
    QStandardItem* item4 = new QStandardItem(rest_string);
    model->setItem(step - 1, 3, item4);

    if (ACTION[{states_stack[states_stack.size() - 1], rest_string[0]}] == "ACC")
    {
        qDebug() << S0;
        QStandardItem* item5 = new QStandardItem("ACCEPT");
        model->setItem(step - 1, 4, item5);
        return true;
    }

    int state_top = states_stack[states_stack.size() - 1];
    QChar rest_top = rest_string[0];
    qDebug() << rest_top;
    QString action = ACTION[{state_top, rest_top}];
    if (action.isEmpty()) return false;
    QString explain;
    if (action[0] == 'S')
    {
        qDebug() << "s";
        explain = "ACTION[" + QString::number(state_top) + "," + rest_top + "]=" + action + ",PUSH STATE " + action.mid(1);
        states_stack.emplace_back(action.mid(1).toInt());
        sign_stack.push_back(rest_top);
        rest_string.remove(0, 1);
    }
    else if (action[0] == 'R')
    {
        qDebug() << "r";
        int order_ = action.mid(1).toInt();
        QString production = order.key(order_);
        QChar left;
        for (auto it = grammer.begin(); it != grammer.end(); it++)
        {
            for (auto item : *it)
            {
                if (item == production)
                    left = it.key();
            }
        }
        for (int i = 0; i < production.size(); i++)
        {
            states_stack.pop_back();
            sign_stack.chop(1);
        }
        int cur_state_top = states_stack[states_stack.size() - 1];
        sign_stack.push_back(left);
        states_stack.push_back(GOTO[{cur_state_top, left}]);
        explain = action + ":" + left + "->" + production + ",REDUCE,PUSH GOTO(" + QString::number(cur_state_top) + "," + left + ")=" + QString::number(GOTO[{cur_state_top, left}]);
    }
    QStandardItem* item5 = new QStandardItem(explain);
    model->setItem(step - 1, 4, item5);
    if (analyse_single(++step, states_stack, sign_stack, rest_string))
        return true;
    else return false;
}