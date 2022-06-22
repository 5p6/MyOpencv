#pragma once
#include"Identity.hpp"
#include"OrderFile.hpp"
class Teacher:public Identity
{
public:
	Teacher();
	Teacher(int id, std::string user, std::string password);
	void OperMeu();//�˵�ҳ��
	void Check();//���ԤԼ
	void showAllorder();//�鿴����ԤԼ
	int id;//ְ����
};
Teacher::Teacher()
{
}
Teacher::Teacher(int id, std::string user, std::string password)
{
	this->id = id;
	this->user = user;
	this->password = password;
}
void Teacher::OperMeu()//�˵�ҳ��
{
	std::cout << "��ӭ��ʦ" << this->user << "��¼��" << std::endl;
	std::cout << "1.���ԤԼ" << std::endl;
	std::cout << "2.�鿴����ԤԼ" << std::endl;
	std::cout << "0.�˳���¼" << std::endl;
}
void Teacher::Check()//���ԤԼ
{
	Order order;
	std::string day;
	if (!order.m_size)
	{
		std::cout << "��ԤԼ��¼" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "��ԤԼ�ļ�¼����" << std::endl;
	std::vector<int> v;
	int index=0;
	for (int i = 0; i < order.m_size; i++)
	{
		if (atoi(order.myOrder[i]["status"].c_str()) == 1)
		{
			v.push_back(i);
			std::cout <<++index << "." << " ";
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
			std::cout << "ѧ��:" << order.myOrder[i]["id"] << " ";
			std::cout << "����:" << order.myOrder[i]["user"] << " ";
			std::cout << "�����" << std::endl;
		}
	}
	int select;
	int ret;
	while (true)
	{
		if (v.empty())
		{
			std::cout << "�޿���˵�ԤԼ��¼" << std::endl;
			system("pause");
			system("cls");
			return;
		}
		std::cout << "ѡ����Ҫ�����ԤԼ��¼" << std::endl;
		std::cout << "0.���ص�¼" << std::endl;
		std::cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				return; 
				system("cls");
			}
			std::cout << "������˽��" << std::endl;
			std::cout << "1.ͨ��" << std::endl;
			std::cout << "2.��ͨ��" << std::endl;
			std::cout << "0.���ص�¼" << std::endl;
			std::cin >> ret;
			switch (ret)
			{
			case 1:
			{
				order.myOrder[v[select - 1]]["status"] = "2";
				break;
			}
			case 2:
			{
				order.myOrder[v[select - 1]]["status"] = "-1";
				break;
			}
			case 0:
			{
				system("cls");
				return;
			}
			default:
			{
				std::cout << "�����������������" << std::endl;
				system("cls");
			}
			}
			order.updataOrd();
			break;
		}
	}
	system("pause");
	system("cls");
}
void Teacher::showAllorder()//�鿴����ԤԼ
{
	Order order;
	std::string  day;
	if (!order.m_size)
	{
		std::cout << "��ԤԼ��¼" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < order.m_size; i++)
{
	  std::cout << i + 1 << "." << " ";
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
	std::cout << "ѧ��:" << order.myOrder[i]["id"] << " ";
	std::cout << "����:" << order.myOrder[i]["user"] << " ";
	std::string status=" ";

	if (order.myOrder[i]["status"] == "1")
	{
		status += "�����";
	}
	else if (order.myOrder[i]["status"] == "-1")
	{
		status += "δͨ��";
	}
	else if (order.myOrder[i]["status"] == "2")
	{
		status += "��ͨ��";
	}
	else 
	{
		status += "ԤԼ��ȡ��";
	}
	std::cout << status << std::endl;
}
		system("pause");
		system("cls");
}
void TeacherMeu(Identity*& t)
{
	while (true)
	{
		t->OperMeu();
		Teacher* teacher = (Teacher*)t;
		std::cout << "�������ѡ��" << std::endl;
		int select;
		std::cin >> select;
		switch (select)
		{
		case 1:teacher->Check(); break;
		case 2:teacher->showAllorder(); break;
		case 0:
		{
			delete t;
			std::cout << "�˳�ע��" << std::endl;
			system("pause");
			system("cls");
			return;
		}
		}
	}
}