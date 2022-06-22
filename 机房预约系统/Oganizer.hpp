#pragma once
#include"Computer.hpp"
#include"Student.hpp"
#include"Teacher.hpp"
#include"Identity.hpp"
#include"globalfile.hpp"
class Oganizer :public Identity
{
public:
	Oganizer();
	Oganizer(std::string user, std::string password);
	void OperMeu();
	void addPerson();
	void CheckPerson();
	void clearfile();
	void InitVector();
	void showcomputer();
	bool checkRepeat(int id,int type);
     std::vector<Student> fsu;
	 std::vector<Teacher> ftea;
	 std::vector<Computer> fcm;
};
template<class T> 
void Printuser(T& s)
{
	for (auto it = s.begin(); it != s.end(); it++)
	{
		std::cout << it->id << "  " << it->user << "  " << it->password << std::endl;
	}
}
Oganizer::Oganizer()
{

}
Oganizer::Oganizer(std::string user, std::string password)
{
	this->user = user;
	this->password = password;
	this->InitVector();
}
void Oganizer::OperMeu()
{
	std::cout << "欢迎管理员" << this->user << "登录！" << std::endl;
	std::cout << "1.添加账号" << std::endl;
	std::cout << "2.机房记录" << std::endl;
	std::cout << "3.查看账号" << std::endl;
	std::cout << "4.清空预约" << std::endl;
	std::cout << "0.退出登录" << std::endl;
}
void Oganizer::addPerson()
{
	std::cout << "输入添加的数据类型:" << std::endl;
	std::cout << "1.学生" << std::endl;
	std::cout << "2.老师" << std::endl;
	int select = -1;
	std::ofstream f;
	do {
		std::cin >> select;
		switch (select)
		{
		case 1:f.open(STUDENT_FILE, std::ios::out | std::ios::app); break;
		case 2:f.open(TEACHER_FILE, std::ios::out | std::ios::app); break;
		default:std::cout << "输入错误，请重新输入." << std::endl;
		}
	} while (select!= 1  &&  select != 2);
	std::string user;
	std::string password;
	std::string errortip;
	int id;
	while (true)
	{
		switch (select)
		{
		case 1:
		{
			errortip = "学生学号重复，请重新输入";
			std::cout << "学生学号:" << std::endl;
			break;
		}
		case 2:
		{
			errortip = "教师职工号输入重复，请重新输入";
			std::cout << "教师职工号" << std::endl;
			break;
		}
		}
		std::cin >> id;
		bool repeat=this->checkRepeat(id, select);
		if (repeat)
		{
			std::cout << errortip << std::endl;
		}
		else
		{
			break;
		}
	}
	std::cout << "用户名：" << std::endl;
	std::cin >> user;
	std::cout << "密码：" << std::endl;
	std::cin >> password;
	f <<  id << " " << " " << user << " " << password<<" \n";
	std::cout << "添加成功" << std::endl;
	f.close();
	system("cls");
	this->InitVector();
}
void Oganizer::CheckPerson()
{
	int select;
	std::cout << "选择你想要查看的预约记录" << std::endl;
	std::cout << "1.学生" << std::endl;
	std::cout << "2.教师" << std::endl;
	std::cin >> select;
	printf("\n");
	switch (select)
	{
	case 1:
	{
		std::cout << "所有学生信息如下：" << std::endl;
		Printuser(fsu);
		break;
	}
	case 2:
	{
		std::cout << "所有教师信息如下：" << std::endl;
		Printuser(ftea);
		break;
	}
	default:
		break;
	}
}
void Oganizer::clearfile()
{
	std::ofstream ifs;
	ifs.open(ORDER_FILE, std::ios::trunc);
	ifs.close();
	std::cout << "清空成功" << std::endl;
}
void Oganizer::showcomputer()
{
	std::cout << "机房记录如下：" << std::endl;
	for (auto it = fcm.begin(); it != fcm.end(); it++)
	{
		std::cout << "第" <<it->m_id << "号机房" << "的电脑台数：" <<it->m_capacity << std::endl;
	}
}
void MangerMeu(Identity*& o)
{
	while (true)
	{
		o->OperMeu();
		Oganizer* O = (Oganizer*)o;
		std::cout << "输入你想要做的操作" << std::endl;
		int select;
		std::cin >> select;
		switch (select)
		{
		case 1:
		{
			std::cout << "添加账号" << std::endl;
			O->addPerson();
			break;
		}
		case 2:
		{
			std::cout << "机房记录" << std::endl;
			system("cls");
			O->showcomputer(); 
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			std::cout << "查看账号" << std::endl;
			O->CheckPerson();
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			std::cout << "清空预约" << std::endl;
			O->clearfile(); 
			system("pause");
			system("cls");
			break;
		}
		case 0:
		{
			delete o;
			system("cls");
			return;
		}
		default:
		{
			break;
		}
		}
	}
}
void Oganizer::InitVector()
{
	fsu.clear();
	ftea.clear();
	fcm.clear();
	std::ifstream ifs;
	//学生
	ifs.open(STUDENT_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "文件读取失败" << std::endl;
		return;
	}
	Student s;
	while (ifs >> s.id && ifs >> s.user && ifs >> s.password)
	{
		fsu.push_back(s);
	}
	std::cout << "当前学生数量为：" << fsu.size() << std::endl;
	ifs.close();

	//老师
	ifs.open(TEACHER_FILE);
	Teacher st;
	while (ifs >> st.id && ifs >> st.user && ifs >> st.password)
	{
		ftea.push_back(st);
	}
	std::cout << "当前老师数量为：" << ftea.size() << std::endl;
	ifs.close();

	ifs.open(COMPUTER_FILE);
	Computer cm;
	while (ifs >> cm.m_id && ifs >> cm.m_capacity)
	{
		fcm.push_back(cm);
	}
	ifs.close();
}
bool Oganizer::checkRepeat(int id,int select)
{
	switch (select)
	{
	case 1:
	{
		for (std::vector<Student>::iterator it = fsu.begin(); it != fsu.end(); it++)
		{
			if (id == it->id)
			{
				return true;
			}
		}
	}
	case 2:
	{
		for (std::vector<Teacher>::iterator it = ftea.begin(); it != ftea.end(); it++)
		{
			if (id == it->id)
			{
				return true;
			}
		}
	}
	}
	return false;
}