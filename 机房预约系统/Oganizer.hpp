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
	std::cout << "��ӭ����Ա" << this->user << "��¼��" << std::endl;
	std::cout << "1.����˺�" << std::endl;
	std::cout << "2.������¼" << std::endl;
	std::cout << "3.�鿴�˺�" << std::endl;
	std::cout << "4.���ԤԼ" << std::endl;
	std::cout << "0.�˳���¼" << std::endl;
}
void Oganizer::addPerson()
{
	std::cout << "������ӵ���������:" << std::endl;
	std::cout << "1.ѧ��" << std::endl;
	std::cout << "2.��ʦ" << std::endl;
	int select = -1;
	std::ofstream f;
	do {
		std::cin >> select;
		switch (select)
		{
		case 1:f.open(STUDENT_FILE, std::ios::out | std::ios::app); break;
		case 2:f.open(TEACHER_FILE, std::ios::out | std::ios::app); break;
		default:std::cout << "�����������������." << std::endl;
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
			errortip = "ѧ��ѧ���ظ�������������";
			std::cout << "ѧ��ѧ��:" << std::endl;
			break;
		}
		case 2:
		{
			errortip = "��ʦְ���������ظ�������������";
			std::cout << "��ʦְ����" << std::endl;
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
	std::cout << "�û�����" << std::endl;
	std::cin >> user;
	std::cout << "���룺" << std::endl;
	std::cin >> password;
	f <<  id << " " << " " << user << " " << password<<" \n";
	std::cout << "��ӳɹ�" << std::endl;
	f.close();
	system("cls");
	this->InitVector();
}
void Oganizer::CheckPerson()
{
	int select;
	std::cout << "ѡ������Ҫ�鿴��ԤԼ��¼" << std::endl;
	std::cout << "1.ѧ��" << std::endl;
	std::cout << "2.��ʦ" << std::endl;
	std::cin >> select;
	printf("\n");
	switch (select)
	{
	case 1:
	{
		std::cout << "����ѧ����Ϣ���£�" << std::endl;
		Printuser(fsu);
		break;
	}
	case 2:
	{
		std::cout << "���н�ʦ��Ϣ���£�" << std::endl;
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
	std::cout << "��ճɹ�" << std::endl;
}
void Oganizer::showcomputer()
{
	std::cout << "������¼���£�" << std::endl;
	for (auto it = fcm.begin(); it != fcm.end(); it++)
	{
		std::cout << "��" <<it->m_id << "�Ż���" << "�ĵ���̨����" <<it->m_capacity << std::endl;
	}
}
void MangerMeu(Identity*& o)
{
	while (true)
	{
		o->OperMeu();
		Oganizer* O = (Oganizer*)o;
		std::cout << "��������Ҫ���Ĳ���" << std::endl;
		int select;
		std::cin >> select;
		switch (select)
		{
		case 1:
		{
			std::cout << "����˺�" << std::endl;
			O->addPerson();
			break;
		}
		case 2:
		{
			std::cout << "������¼" << std::endl;
			system("cls");
			O->showcomputer(); 
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			std::cout << "�鿴�˺�" << std::endl;
			O->CheckPerson();
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			std::cout << "���ԤԼ" << std::endl;
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
	//ѧ��
	ifs.open(STUDENT_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "�ļ���ȡʧ��" << std::endl;
		return;
	}
	Student s;
	while (ifs >> s.id && ifs >> s.user && ifs >> s.password)
	{
		fsu.push_back(s);
	}
	std::cout << "��ǰѧ������Ϊ��" << fsu.size() << std::endl;
	ifs.close();

	//��ʦ
	ifs.open(TEACHER_FILE);
	Teacher st;
	while (ifs >> st.id && ifs >> st.user && ifs >> st.password)
	{
		ftea.push_back(st);
	}
	std::cout << "��ǰ��ʦ����Ϊ��" << ftea.size() << std::endl;
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