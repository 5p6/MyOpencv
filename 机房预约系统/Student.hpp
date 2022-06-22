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
	void OperMeu();//打开我的菜单
	void applyorder();//申请预约
	void showMyorder();//查看我的预约
	void DelAllorder();//去掉预约
	int id;//学生号
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
void Student::OperMeu()//打开我的菜单
{
	std::cout << "欢迎学生：" << this->user << "登录！" << std::endl;
	std::cout << "1.申请预约" << std::endl;
	std::cout << "2.查看预约" << std::endl;
	std::cout << "3.取消预约" << std::endl;
	std::cout << "0.退出登录" << std::endl;
}
void Student::applyorder()//申请预约
{
	std::cout << "机房开放时间为周一至周五" << std::endl;
	std::cout << "1.周一" << std::endl;
	std::cout << "2.周二" << std::endl;
	std::cout << "3.周三" << std::endl;
	std::cout << "4.周四" << std::endl;
	std::cout << "5.周五" << std::endl;
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
		std::cout << "输入有误，重新输入" << std::endl;
	}
	std::cout << "预约当天的时间" << std::endl;
	std::cout << "1.上午" << std::endl;
	std::cout << "2.下午" << std::endl;
	while (true)
	{
		std::cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		std::cout << "输入有误，重新输入" << std::endl;
	}
	std::cout << "输入你选择的机房的编号" << std::endl;
	for (auto it = sucm.begin(); it != sucm.end(); it++)
	{
		std::cout << "编号为" << it->m_id << "的电脑可用数量为：" << it->m_capacity<<std::endl;
	}
	while (true)
	{
		std::cin >> room;
		if (room >= 1 && room < sucm.size())
		{
			break;
		}
		std::cout << "输入错误，重新输入" << std::endl;
	}
	std::cout << "预约成功，请等待审核" << std::endl;
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
void Student::showMyorder()//查看我的预约
{
	Order order;
	std::string day;
	std::string interval;
	if (order.m_size == 0)
	{
		std::cout << "无预约" << std::endl;
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
		}
		std::string staus = " ";
		if (order.myOrder[i]["status"] == "1")
		{
			staus += "审核中";
		}
		else if(order.myOrder[i]["status"]=="-1")
		{
			staus += "未通过";
		}
		else if(order.myOrder[i]["status"]=="2")
		{
			staus += "已通过";
		}
		else
		{
			staus += "预约已取消";
		}
		std::cout << staus << std::endl;
	}
	system("pause");
	system("cls");
}
void Student::DelAllorder()//去掉预约
{
	Order Or ;
	if (Or.m_size == 0)
	{
		std::cout << "无预约记录" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "审核中和预约成功的预约可以取消" << std::endl;

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
				std::cout << "时期:" << Or.myOrder[i]["day"] << " ";
				std::cout << "时段:" << ((Or.myOrder[i]["interval"] == "1") ? "上午" : "下午") << " ";
				std::cout << "机房编号:" << Or.myOrder[i]["room"] << " ";
				std::cout << "状态:" << ((Or.myOrder[i]["status"] == "1") ? "审核中" : "已通过") << "\n";
			}
		}
	}
	if (index == 0)
	{
		std::cout << "无记录" << std::endl;
		return;
	}
	std::cout << "输入你要取消的记录" << std::endl;
	std::cout << "输入0则退出取消记录" << std::endl;
	int select;
	while (true)
	{
		std::cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				std::cout << "退出" << std::endl;
				system("cls");
				return;
			}
			else
			{
				Or.myOrder[v[select - 1]]["status"] = "0";
				Or.updataOrd();
				std::cout << "已取消预约" << "\n";
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
		std::cout << "文件打开失败" << std::endl;
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
