//#include "project.h"
//using namespace std;

//project::project() {}
//
//project::project(QChar h, QString t, int d, QSet<QChar> l) :head(h), tail(t), dot_pos(d), lookahead(l) {}
//
//project::project(const project& other)
//{
//	head = other.head;
//	tail = other.tail;
//	dot_pos = other.dot_pos;
//	lookahead = other.lookahead;
//}
//
//project::~project(){}
//
//bool project::operator==(project& other)
//{
//	return head == other.head && tail == other.tail && dot_pos == other.dot_pos && lookahead == other.lookahead;
//}
//
//project& project::operator=(const project& other)
//{
//	head = other.head;
//	tail = other.tail;
//	dot_pos = other.dot_pos;
//	lookahead = other.lookahead;
//	return *this;
//}
//
