#pragma once
#include<iostream>
#include"globalfile.hpp"
#include<string>
#include<map>
#include<fstream>
class Order
{
public:
	Order();
	void updataOrd();
	int m_size;
	std::map<int, std::map<std::string, std::string>> myOrder;
};
Order::Order()
{
	
	std::ifstream ifs(ORDER_FILE);
	this->m_size = 0;
	std::string day;
	std::string interval;
	std::string room;
	std::string id;
	std::string user;
	std::string status;
	while (ifs >> day && ifs >> interval && ifs >> room && ifs >> id && ifs >> user && ifs>>status) {
		std::string key;
		std::string str;
		std::map<std::string, std::string> map;


		auto posd = day.find(":");
		key = day.substr(0, posd);
		str = day.substr(posd+1, day.size() - posd - 1);
		map.insert(std::pair<std::string,std::string>(key, str));

		auto posi = interval.find(":");
		key = interval.substr(0, posi);
		str = interval.substr(posi + 1, interval.size() - posi - 1);
		map.insert(std::pair<std::string, std::string>(key, str));

		auto posr = room.find(":");
		key = room.substr(0, posr);
		str = room.substr(posr + 1, room.size() - posr - 1);
		map.insert(std::pair<std::string, std::string>(key, str));

		auto posid = id.find(":");
		key = id.substr(0, posid);
		str = id.substr(posid + 1, id.size() - posid - 1);
		map.insert(std::pair<std::string, std::string>(key, str));

		auto posu = user.find(":");
		key = user.substr(0, posu);
		str = user.substr(posu + 1, user.size() - posu - 1);
		map.insert(std::pair<std::string, std::string>(key, str));

		auto pos = status.find(":");
		key = status.substr(0, pos);
		str = status.substr(pos + 1,status.size() - pos - 1);
		map.insert(std::pair<std::string, std::string>(key, str));


		this->myOrder.insert(std::pair<int,std::map<std::string,std::string>>(m_size, map));
		
		this->m_size++;
	}
	ifs.close();
}
void Order::updataOrd()
{
	if (m_size == 0)
	{
		return;
	}
	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::out | std::ios::trunc);
	for (int i = 0; i < m_size; i++)
	{
		ofs << "day:" << this->myOrder[i]["day"] << " ";
		ofs << "interval:" << this->myOrder[i]["interval"] << " ";
		ofs << "room:" << this->myOrder[i]["room"] << " ";
		ofs << "id:" << this->myOrder[i]["id"] << " ";
		ofs << "user:" << this->myOrder[i]["user"] << " ";
		ofs << "status:" << this->myOrder[i]["status"] << "\n";
	}
	ofs.close();
}