#include<iostream>
#include<string>
#include<bitset>
#include<iomanip>
#include<fstream>
#include<unordered_set>
#include<unordered_map>
using namespace std;

unordered_set<string> k;
unordered_map<string, pair<int, string>> s;
unordered_set<string> id;
unordered_set<string> ci;

//初始化关键字表
void new_k()
{
	cout << "please enter the keyword to new the board:";
	string keyword;
	while (cin >> keyword)
	{
		k.insert(keyword);
		cout << "please enter the keyword to new the board:";
	}
	cin.clear();
	return;
}

//初始化分界符表（包含算术运算符，关系运算符）
void new_s()
{
	cout << "please enter the delimiter and the type to new the board:";
	string delimiter, type;
	int type_num;
	while (cin >> delimiter && cin >> type && cin >> type_num)
	{
		s.insert({ delimiter,{type_num, type} });
		cout << "please enter the delimiter and the type to new the board:";
	}
	cin.clear();
	return;
}

void posi(int& row, int& line, char cur)
{
	if (cur == '\n')
	{
		row++;
		line = 0;
	}
	else line++;
	return;
}

void show()
{
	cout << setw(10) << left << "单词" << setw(15) << left << "二元序列" << setw(12) << left << "类型" << "位置" << endl;
	ifstream ifs;
	ifs.open("D:/vs2019/compile/experiment1/code.txt", ios::in);
	string word = "";
	int row = 1, line = 0;
	char cur;
	while (ifs.get(cur))
	{
		posi(row, line, cur);
		if (cur == '\n' || isspace(cur))
		{
			word.clear();
			continue;
		}
		else if (isalpha(cur))
		{
			word.push_back(cur);
			while (ifs.get(cur))
			{
				if (isalnum(cur))
				{
					posi(row, line, cur);
					word.push_back(cur);
				}
				else
				{
					if (k.find(word) != k.end())
						cout << setw(10) << left << word  << "(" << 1 << "," << word << setw(12 - word.size()) << left << ")" << setw(12) << left << "关键字"  << '(' << row << ',' << line << ')' << endl;
					else if (id.find(word) != id.end()) 
						cout << setw(10) << left << word  << "(" << 6 << "," << word << setw(12 - word.size()) << left << ")" << setw(12) << left << "标识符"  << '(' << row << "," << line << ')' << endl;
					else
					{
						id.insert(word);
						cout << setw(10) << left << word  << "(" << 6 << "," << word << setw(12 - word.size()) << left << ")" << setw(12) << left << "标识符"  << '(' << row << "," << line << ')' << endl;
					}
					break;
				}
			}
			ifs.seekg(-1, ios::cur);
			word.clear();
		}
		else if (isdigit(cur))
		{
			word.push_back(cur);
			while (ifs.get(cur))
			{
				if (isdigit(cur))
				{
					posi(row, line, cur);
					word.push_back(cur);
				}
				else if (isalpha(cur))
				{
					posi(row, line, cur);
					word.push_back(cur);
					cout << setw(10) << left << word << setw(15) << left << "ERROR" << setw(12) << left << "ERROR"  << '(' << row << ',' << line << ')' << endl;
					break;
				}
				else
				{
					cout << setw(10) << left << word << '(' << 5 << ',' << word << setw(12 - word.size()) << left << ')' << setw(12) << left << "常数" << '(' << row << ',' << line << ')' << endl;
					int num = stoi(word);
					word = bitset<8>(num).to_string();
					if (ci.find(word) != ci.end()) ci.insert(word);
					ifs.seekg(-1, ios::cur);
					break;
				}
			}
			word.clear();
		}
		else
		{
			word.push_back(cur);
			if (s.find(word) != s.end())
			{
				char pre = cur;
				cur = ifs.get();
				word.push_back(cur);
				if (((pre == '<' || pre == '>') && (cur == '=')) || (pre == '<' && cur == '>'))
				{
					posi(row, line, cur);
					cout << setw(10) << left << word << '(' << s[word].first << ',' << word << setw(12 - word.size()) << left << ')' << setw(12) << left << s[word].second << '(' << row << ',' << line << ')' << endl;
				}
				else if (pre == '/')
				{
					posi(row, line, cur);
					if (cur == '*')
					{
						while (ifs.get(cur))
						{
							posi(row, line, cur);
							if (cur == '*')
							{
								cur = ifs.get();
								posi(row, line, cur);
								if (cur == '/') break;
							}
						}
					}
					else if (cur == '/')
					{
						posi(row, line, cur);
						while (ifs.get(cur))
						{
							posi(row, line, cur);
							if (cur == '\n') break;
						}
					}
				}
				else
				{
					if (cur != '\n' && !isspace(cur) && !isalnum(cur) && cur != ';' && !ifs.eof())
					{
						posi(row, line, cur);
						cout << setw(10) << left << word << setw(15) << left << "ERROR" << setw(12) << left << "ERROR" << '(' << row << ',' << line << ')' << endl;
					}
					else
					{
						word.pop_back();
						cout << setw(10) << left << word << '(' << s[word].first << ',' << word << setw(12 - word.size()) << left << ')' << setw(12) << left << s[word].second << '(' << row << ',' << line << ')' << endl;
						ifs.seekg(-1, ios::cur);
					}
				}
			}
			else 
				cout << setw(10) << left << word << setw(15) << left << "ERROR" << setw(12) << left << "ERROR" << '(' << row << ',' << line << ')' << endl;
			word.clear();
		}
	}
	ifs.close();
}

int main()
{
	new_k();
	new_s();
	show();
	return 0;
}