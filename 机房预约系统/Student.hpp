#pragma once
#include"Identity.hpp"
#include"Computer.hpp"
#include"globalfile.hpp"
#include"OrderFile.hpp"
class Student :public Identity
{
public:
	Student();
	Student(int id, std::string name, std::string password);
	void OperMeu();//���ҵĲ˵�
	void applyorder();//����ԤԼ
	void showMyorder();//�鿴�ҵ�ԤԼ
	void DelAllorder();//ȥ��ԤԼ
	int id;//ѧ����
	std::vector<Computer>  sucm;
	void InitVector();
	Order Myo;
};
Student::Student()
{  };
Student::Student(int id, std::string user, std::string password)
{
	this->id = id;
	this->user = user;
	this->password = password;
	this->InitVector();
}
void Student::OperMeu()//���ҵĲ˵�
{
	std::cout << "��ӭѧ����" << this->user << "��¼��" << std::endl;
	std::cout << "1.����ԤԼ" << std::endl;
	std::cout << "2.�鿴ԤԼ" << std::endl;
	std::cout << "3.ȡ��ԤԼ" << std::endl;
	std::cout << "0.�˳���¼" << std::endl;
}
void Student::applyorder()//����ԤԼ
{
	std::cout << "��������ʱ��Ϊ��һ������" << std::endl;
	std::cout << "1.��һ" << std::endl;
	std::cout << "2.�ܶ�" << std::endl;
	std::cout << "3.����" << std::endl;
	std::cout << "4.����" << std::endl;
	std::cout << "5.����" << std::endl;
	int interval;
	int day;
	int room;
	while (true)
	{
		std::cin >> day;
		if (day >= 1 && day <= 5)
		{
			break;
		}
		std::cout << "����������������" << std::endl;
	}
	std::cout << "ԤԼ�����ʱ��" << std::endl;
	std::cout << "1.����" << std::endl;
	std::cout << "2.����" << std::endl;
	while (true)
	{
		std::cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		std::cout << "����������������" << std::endl;
	}
	std::cout << "������ѡ��Ļ����ı��" << std::endl;
	for (auto it = sucm.begin(); it != sucm.end(); it++)
	{
		std::cout << "���Ϊ" << it->m_id << "�ĵ��Կ�������Ϊ��" << it->m_capacity<<std::endl;
	}
	while (true)
	{
		std::cin >> room;
		if (room >= 1 && room < sucm.size())
		{
			break;
		}
		std::cout << "���������������" << std::endl;
	}
	std::cout << "ԤԼ�ɹ�����ȴ����" << std::endl;
	std::ofstream ofs(ORDER_FILE,std::ios::app);
	ofs << "day:"<<day << " " 
		<<"interval:" <<interval << " " 
		<<"room:" << room << " " 
		"id:"<< this->id << " " 
		<<"user:" << this->user <<" "
		<<"status:"<<"1" << "\n";
	ofs.close();
	system("pause");
	system("cls");
}
void Student::showMyorder()//�鿴�ҵ�ԤԼ
{
	Order order;
	std::string day;
	std::string interval;
	if (order.m_size == 0)
	{
		std::cout << "��ԤԼ" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	int index=0;
	for (int i = 0; i < order.m_size; i++)
	{
		if (atoi(order.myOrder[i]["id"].c_str()) == id)
		{
			std::cout << ++index << "." <<" ";
			if (order.myOrder[i]["day"] == "1")
			{
				day = "��һ";
			}
			else if (order.myOrder[i]["day"] == "2")
			{
				day = "�ܶ�";
			}
			else if (order.myOrder[i]["day"] == "3")
			{
				day = "����";
			}
			else if (order.myOrder[i]["day"] == "4")
			{
				day = "����";
			}
			else if (order.myOrder[i]["day"] == "5")
			{
				day = "����";
			}

			std::cout << "ԤԼʱ��:" << day << " ";
			std::cout << "ԤԼʱ��:" << ((order.myOrder[i]["interval"] == "1") ? "����" : "����") << " ";
			std::cout << "ԤԼ����:" << order.myOrder[i]["room"] << " ";
		}
		std::string staus = " ";
		if (order.myOrder[i]["status"] == "1")
		{
			staus += "�����";
		}
		else if(order.myOrder[i]["status"]=="-1")
		{
			staus += "δͨ��";
		}
		else if(order.myOrder[i]["status"]=="2")
		{
			staus += "��ͨ��";
		}
		else
		{
			staus += "ԤԼ��ȡ��";
		}
		std::cout << staus << std::endl;
	}
	system("pause");
	system("cls");
}
void Student::DelAllorder()//ȥ��ԤԼ
{
	Order Or ;
	if (Or.m_size == 0)
	{
		std::cout << "��ԤԼ��¼" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "����к�ԤԼ�ɹ���ԤԼ����ȡ��" << std::endl;

	std::vector<int> v;
	int index = 0;
	for (int i = 0; i < Or.m_size; i++)
	{
		if (atoi(Or.myOrder[i]["id"].c_str()) == id)
		{
			if (Or.myOrder[i]["status"] == "1" || Or.myOrder[i]["status"] == "2")
			{
				v.push_back(i);
				index++;
				std::cout << "ʱ��:" << Or.myOrder[i]["day"] << " ";
				std::cout << "ʱ��:" << ((Or.myOrder[i]["interval"] == "1") ? "����" : "����") << " ";
				std::cout << "�������:" << Or.myOrder[i]["room"] << " ";
				std::cout << "״̬:" << ((Or.myOrder[i]["status"] == "1") ? "�����" : "��ͨ��") << "\n";
			}
		}
	}
	if (index == 0)
	{
		std::cout << "�޼�¼" << std::endl;
		return;
	}
	std::cout << "������Ҫȡ���ļ�¼" << std::endl;
	std::cout << "����0���˳�ȡ����¼" << std::endl;
	int select;
	while (true)
	{
		std::cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				std::cout << "�˳�" << std::endl;
				system("cls");
				return;
			}
			else
			{
				Or.myOrder[v[select - 1]]["status"] = "0";
				Or.updataOrd();
				std::cout << "��ȡ��ԤԼ" << "\n";
				break;
			}
		}
	}
	system("pause");
	system("cls");
}
void Student::InitVector()
{
	std::ifstream ifs;
	ifs.open(COMPUTER_FILE);
	if (!ifs.is_open())
	{
		std::cout << "�ļ���ʧ��" << std::endl;
		return;
	}
	Computer cm;
	while (ifs>>cm.m_id&&ifs>>cm.m_capacity)
	{
		sucm.push_back(cm);
	}
	ifs.close();
}
void StudentMeu(Identity*& s)
{
	while (true)
	{
		s->OperMeu();
		Student* st = (Student*)s;
		int select=-1;
		std::cin >> select;
		switch (select)
		{
		case 1:st->applyorder(); break;
		case 2:st->showMyorder(); break;
		case 3:st->DelAllorder(); break;
		case 0:
		{
			delete s;
			system("cls");
			return;
		}
	}
	}
}
