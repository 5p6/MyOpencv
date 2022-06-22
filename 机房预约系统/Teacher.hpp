#pragma once
#include"Identity.hpp"
#include"OrderFile.hpp"
class Teacher:public Identity
{
public:
	Teacher();
	Teacher(int id, std::string user, std::string password);
	void OperMeu();//菜单页面
	void Check();//审核预约
	void showAllorder();//查看所有预约
	int id;//职工号
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
void Teacher::OperMeu()//菜单页面
{
	std::cout << "欢迎教师" << this->user << "登录！" << std::endl;
	std::cout << "1.审核预约" << std::endl;
	std::cout << "2.查看所有预约" << std::endl;
	std::cout << "0.退出登录" << std::endl;
}
void Teacher::Check()//审核预约
{
	Order order;
	std::string day;
	if (!order.m_size)
	{
		std::cout << "无预约记录" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "待预约的记录如下" << std::endl;
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
				day = "周一";
			}
			else if (order.myOrder[i]["day"] == "2")
			{
				day = "周二";
			}
			else if (order.myOrder[i]["day"] == "3")
			{
				day = "周三";
			}
			else if (order.myOrder[i]["day"] == "4")
			{
				day = "周四";
			}
			else if (order.myOrder[i]["day"] == "5")
			{
				day = "周五";
			}
			std::cout << "预约时间:" << day << " ";
			std::cout << "预约时段:" << ((order.myOrder[i]["interval"] == "1") ? "上午" : "下午") << " ";
			std::cout << "预约机房:" << order.myOrder[i]["room"] << " ";
			std::cout << "学号:" << order.myOrder[i]["id"] << " ";
			std::cout << "姓名:" << order.myOrder[i]["user"] << " ";
			std::cout << "审核中" << std::endl;
		}
	}
	int select;
	int ret;
	while (true)
	{
		if (v.empty())
		{
			std::cout << "无可审核的预约记录" << std::endl;
			system("pause");
			system("cls");
			return;
		}
		std::cout << "选择你要处理的预约记录" << std::endl;
		std::cout << "0.返回登录" << std::endl;
		std::cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				return; 
				system("cls");
			}
			std::cout << "输入审核结果" << std::endl;
			std::cout << "1.通过" << std::endl;
			std::cout << "2.不通过" << std::endl;
			std::cout << "0.返回登录" << std::endl;
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
				std::cout << "输入错误，请重新输入" << std::endl;
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
void Teacher::showAllorder()//查看所有预约
{
	Order order;
	std::string  day;
	if (!order.m_size)
	{
		std::cout << "无预约记录" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < order.m_size; i++)
{
	  std::cout << i + 1 << "." << " ";
	    if (order.myOrder[i]["day"] == "1")
	{
		day = "周一";
	}
	else if (order.myOrder[i]["day"] == "2")
	{
		day = "周二";
	}
	else if (order.myOrder[i]["day"] == "3")
	{
		day = "周三";
	}
	else if (order.myOrder[i]["day"] == "4")
	{
		day = "周四";
	}
	else if (order.myOrder[i]["day"] == "5")
	{
		day = "周五";
	}
	std::cout << "预约时间:" << day << " ";
	std::cout << "预约时段:" << ((order.myOrder[i]["interval"] == "1") ? "上午" : "下午") << " ";
	std::cout << "预约机房:" << order.myOrder[i]["room"] << " ";
	std::cout << "学号:" << order.myOrder[i]["id"] << " ";
	std::cout << "姓名:" << order.myOrder[i]["user"] << " ";
	std::string status=" ";

	if (order.myOrder[i]["status"] == "1")
	{
		status += "审核中";
	}
	else if (order.myOrder[i]["status"] == "-1")
	{
		status += "未通过";
	}
	else if (order.myOrder[i]["status"] == "2")
	{
		status += "已通过";
	}
	else 
	{
		status += "预约已取消";
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
		std::cout << "输入你的选择" << std::endl;
		int select;
		std::cin >> select;
		switch (select)
		{
		case 1:teacher->Check(); break;
		case 2:teacher->showAllorder(); break;
		case 0:
		{
			delete t;
			std::cout << "退出注销" << std::endl;
			system("pause");
			system("cls");
			return;
		}
		}
	}
}