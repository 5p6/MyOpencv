#include"Student.hpp"
#include"Teacher.hpp"
#include"Oganizer.hpp"
#include"globalfile.hpp"
void Login(std::string filename, int type)
{
	Identity* person = NULL;
	std::ifstream f(filename, std::ios::in);
	if (!f.is_open())
	{
		std::cout << "文件打开失败，请重新打开文件" << std::endl;
		f.close();
		return;
	}
	int id;
	std::string user;
	std::string password;
	switch (type)
	{
	case 1:
	{
		std::cout << "输入你的学号" << std::endl;
		std::cin >> id;
		break;
	}
   case 2:
	{
	std::cout << "输入你的教师职工号" << std::endl;
	std::cin >> id;
	break;
	}
	default:break;
	}
	
	std::cout << "请输入你的用户号名：" << std::endl;
	std::cin >> user;
	std::cout << "请输入你的密码：" << std::endl;
	std::cin >> password;

	switch (type)
	{
	case 1:
	{	
	int fid;
	std::string fuser;
	std::string fpassword;
	while (f >> fid && f >> fuser && f >> fpassword)
	{
		if (fid == id && user == fuser && fpassword == password)
		{
			std::cout << "学生验证成功" << std::endl;
			system("cls");
			person = new Student(fid, fuser, fpassword);
			StudentMeu(person);
			system("cls");//缓存清除
			//子菜单
			return;
		}
	}
		break;//学生身份验证
	}
	case 2: {
		int fid;
		std::string fuser;
		std::string fpassword;
		while (f >> fid && f >> fuser && f >> fpassword)
		{
			if (fid == id  && user == fuser && fpassword == password)
			{
				std::cout << "老师验证成功" << std::endl;
				person =new Teacher(fid,fuser,fpassword);
				system("pause");
				system("cls");
				TeacherMeu(person);
				///子菜单
				return;
			}
		}
		break; 
	}//老师身份验证
	case 3:
	{
		std::string fuser;
		std::string fpassword;
		while (f >> fuser && f >> fpassword)
		{
			if (user == fuser && fpassword == password)
			{
				std::cout << "管理员验证成功" << std::endl;
				system("pause");
				system("cls");
				person = new Oganizer(fuser, fpassword);
				///子菜单
				MangerMeu(person);
				return;
			}
		}
		break;
	}//管理员身份验证
	default:break;
	}
	std::cout << "验证失败，请重新输入，或者预约." << std::endl; 
	f.close();
	system("pause");
	system("cls");
	return;

}
int main(int argc, char** argv)
{
	while (true)
	{
		int select;
		std::cout << "=====1.学生=====" << std::endl;
		std::cout << "=====2.教师=====" << std::endl;
		std::cout << "=====3.管理员=====" << std::endl;
		std::cout << "=====4.退出=====" << std::endl;
		std::cout << "请输入你的选择：" <<std::endl;
		std::cin >> select;
		switch (select)
		{
		case 1:Login(STUDENT_FILE,select); break;//学生功能;
		case 2:Login(TEACHER_FILE, select); break;//教师功能
		case 3:Login(ADMIN_FILE, select); break;//管理员功能
		case 4:
		{
			std::cout << "预约结束，退出." << std::endl; return 0;//退出
		}
		default:
		{
			std::cout << "pause" << std::endl; std::cout << "重新输入" << std::endl; break;
		}
		
		}
	}
}
