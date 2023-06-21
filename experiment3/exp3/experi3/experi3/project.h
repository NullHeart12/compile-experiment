#pragma once
#ifndef PROJECT_H
#define PROJECT_H

#include <QChar>
#include <QString>
#include <QSet>
#include <algorithm>


class project
{
public:
	QChar head;
	QString tail;
	int dot_pos;
	QSet<QChar> lookahead;

	project() {}
	project(QChar h, QString t, int d, QSet<QChar> l) :head(h), tail(t), dot_pos(d), lookahead(l) {}
	project(const project& other)
	{
		head = other.head;
		tail = other.tail;
		dot_pos = other.dot_pos;
		lookahead = other.lookahead;
	}
	~project() { lookahead.clear(); }
	
	bool operator==(const project& other) const
	{
		return head == other.head && tail == other.tail && dot_pos == other.dot_pos && lookahead == other.lookahead;
	}
	
	bool operator<(const project& other) const
	{
        if (head != other.head) {
            return head < other.head;
        }
        if (tail != other.tail) {
            return tail < other.tail;
        }
        if (dot_pos != other.dot_pos) {
            return dot_pos < other.dot_pos;
        }
        // QSet 的比较可以直接使用小于运算符
		QVector<QChar> a, b;
		for (auto item : lookahead) a.emplace_back(item);
		for (auto item : other.lookahead) b.emplace_back(item);
		std::sort(a.begin(), a.end());
		std::sort(b.begin(), b.end());
		return a < b;
	}

	project& operator=(const project& other) 
	{
		if (this != &other)
		{
			head = other.head;
			tail = other.tail;
			dot_pos = other.dot_pos;
			lookahead = other.lookahead;
		}
		return *this;
	}

	int hash() const
	{
		int ret = 0;
		ret += head.toLatin1();
		ret += dot_pos;
		for (auto item : lookahead) ret += item.toLatin1();
		return ret;
	}
};

#endif