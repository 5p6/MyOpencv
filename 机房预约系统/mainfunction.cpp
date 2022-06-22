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
		std::cout << "�ļ���ʧ�ܣ������´��ļ�" << std::endl;
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
		std::cout << "�������ѧ��" << std::endl;
		std::cin >> id;
		break;
	}
   case 2:
	{
	std::cout << "������Ľ�ʦְ����" << std::endl;
	std::cin >> id;
	break;
	}
	default:break;
	}
	
	std::cout << "����������û�������" << std::endl;
	std::cin >> user;
	std::cout << "������������룺" << std::endl;
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
			std::cout << "ѧ����֤�ɹ�" << std::endl;
			system("cls");
			person = new Student(fid, fuser, fpassword);
			StudentMeu(person);
			system("cls");//�������
			//�Ӳ˵�
			return;
		}
	}
		break;//ѧ�������֤
	}
	case 2: {
		int fid;
		std::string fuser;
		std::string fpassword;
		while (f >> fid && f >> fuser && f >> fpassword)
		{
			if (fid == id  && user == fuser && fpassword == password)
			{
				std::cout << "��ʦ��֤�ɹ�" << std::endl;
				person =new Teacher(fid,fuser,fpassword);
				system("pause");
				system("cls");
				TeacherMeu(person);
				///�Ӳ˵�
				return;
			}
		}
		break; 
	}//��ʦ�����֤
	case 3:
	{
		std::string fuser;
		std::string fpassword;
		while (f >> fuser && f >> fpassword)
		{
			if (user == fuser && fpassword == password)
			{
				std::cout << "����Ա��֤�ɹ�" << std::endl;
				system("pause");
				system("cls");
				person = new Oganizer(fuser, fpassword);
				///�Ӳ˵�
				MangerMeu(person);
				return;
			}
		}
		break;
	}//����Ա�����֤
	default:break;
	}
	std::cout << "��֤ʧ�ܣ����������룬����ԤԼ." << std::endl; 
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
		std::cout << "=====1.ѧ��=====" << std::endl;
		std::cout << "=====2.��ʦ=====" << std::endl;
		std::cout << "=====3.����Ա=====" << std::endl;
		std::cout << "=====4.�˳�=====" << std::endl;
		std::cout << "���������ѡ��" <<std::endl;
		std::cin >> select;
		switch (select)
		{
		case 1:Login(STUDENT_FILE,select); break;//ѧ������;
		case 2:Login(TEACHER_FILE, select); break;//��ʦ����
		case 3:Login(ADMIN_FILE, select); break;//����Ա����
		case 4:
		{
			std::cout << "ԤԼ�������˳�." << std::endl; return 0;//�˳�
		}
		default:
		{
			std::cout << "pause" << std::endl; std::cout << "��������" << std::endl; break;
		}
		
		}
	}
}
