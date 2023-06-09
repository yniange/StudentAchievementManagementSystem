#include "App.h"
#include <iostream>
#include <algorithm>
#include "Global.h"
#include <io.h>
#include <array>

App::App()
{
	//�ж������ļ��Ƿ��Ѵ���
	if (0 != _access_s(FileName.c_str(), 0))
	{//��������ļ������ڣ����ó�ʼ��������StuDataSet
		InitDataSet();
	}
	else
	{//��������ļ����ڣ���������ļ��ж�ȡ�洢���ļ��е�����
		ReadFile(FileName);
	}
}

App::~App()
{
	WriteFile(FileName);
}

void App::InitDataSet()
{
	StuDataSet.clear();

	const int IniLen{ 7 };
	std::array<std::string, IniLen>NumA{
		"220101", "220102", "220103", "220104", "220105", "L220106", "L220107" };
	std::array<std::string, IniLen>NameA{
		"����", "����", "����", "����", "Ǯ��", "Jessi", "Elon Musk" };
	std::array<float, IniLen>ScoreA{ 92.0f, 85.0f, 70.0f, 60.0f, 80.0f, 90.0f, 55.0f };
	Student stu;
	for (int i = 0; i < IniLen; ++i)
	{
		stu.SetId(NumA[i]);
		stu.SetName(NameA[i]);
		stu.SetScore(ScoreA[i]);
		StuDataSet.push_back(stu);
	}
}

void App::InputData()
{
	std::cout << "������ѧ���ɼ���Ϣ��\n";
	char c_contine_input;
	std::string str_id{ "" };
	std::string str_name{ "" };
	std::string str_score{ "" };
	float f_score{ 0.0f };
	Student stu;
	while (true)
	{
		while (true)
		{
			std::cout << "ѧ�ţ�";
			std::cin >> str_id;
			// ��֤ѧ�ŵ�Ψһ��
			if (-1 == FindById(str_id))
			{//�����ѧ�������ݼ��в����ڣ�����ʹ��
				break;
			}
			else
			{//�����ѧ�������ݼ������У�Ӧ���Ѳ�Ҫ����������
				std::cout << "ѧ���ѱ�ռ�ã����������롣\n";
			}
		}

		// ����ѧ��ʱ��ͨ������س���ʵ����������
		// ���ύ����ˣ�֮ǰ�Ļ�����������ĩβһ
		// ����һ�����з�\n����������ѧ�Ų�������
		// �������ж�ȡ�ַ�ʱ�����հ׷����ո�Tab
		// �ַ������з�����ֹͣ���������ѧ�Ų���
		// �����󣬻�����������ʵ����Ϊ�գ�������
		// ��һ�����з�'\n'��
		// ��Ϊ����getline���Զ�ȡ�����������еĿհ�
		// ������ʱֱ�ӵ���getline��getline����ȴ���
		// �����룬����ֱ�Ӷ���֮ǰ�����������������
		// ������з�'\n'������ʹ�ö�ȡ�Ľ�����һ����
		// �ַ�����Ҳ����˵����������£�getline�޷�
		// ʵ������һ����Ч�ַ������������ĵ���Ŀ�ġ�
		// �����ڵ���getline����ǰ��Ҫȷ��֮ǰ��������
		// �С��ɾ������Ա�֤getline������ʱ����������
		// �յġ�����������ʱ������ͣ�������ȴ��û���
		// ����Ч���ַ���ͨ������ignore��������һ�ֳ�
		// ������ջ������İ취��
		// ע�⣬����һ���cin�������������Ի���������
		// ��ǰ�����еĿհ׷�����˲��������������⡣
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "������";
		std::getline(std::cin, str_name);

		// cin����ʱ�����ϣ���û����������ֵ��������
		// ��������ʵ��֮�ࣩ���������ַ����ַ������ݣ�
		// ����Ҫ����һ�����⣺���û�����Ĳ���һ���Ϸ�
		// ����ֵʱ��Ʃ����������ʱ����С�ļ����˷�����
		// �ַ����ֻ�������ʵ��ʱ��С������������һ����
		// cin������ʧ�ܣ��޷���ȡ��һ������������ֵ����
		// �ң�cinҲ�ᱻ��־Ϊbad������֮������������
		// ������ִ�С����ң����ڴ�ʱ��cin����ʧ�ܣ�����
		// �������е��ַ���Ȼ����ԭ�������ͨ������cin��
		// clear������bad״̬�ָ���֮������������Ȼ����
		// ԭ�����������У���ǰ����ȥ��ȡ��Ҫ�����ݡ����
		// �����Ķ�ȡ����ͬ������ͼ��ȡ��ֵ�����ݣ����ֻ�
		// �ظ�����֮ǰ�����⡣
		// ��ˣ���������cinһ����ֵ������ʱ�����������ַ�
		// ������ʽ���룬Ȼ���жϸ��ַ����Ƿ���һ���Ϸ���
		// ��ֵ�����ݵ���ʽ������ǣ�������atoi��atof�Ⱥ�
		// ���������ַ���ת��ΪĿ����ֵ�����ݣ�������ǣ�
		// ����ʾ�û�������󣬲�Ҫ������������ȷ����ʽ��
		// ��ȷ������Ľ�׳�ԡ�
		std::cout << "�ɼ���";
		while (true)
		{
			std::cin >> str_score;
			if (isFloat(str_score))
			{
				f_score = static_cast<float>(atof(str_score.c_str()));
				if (f_score >= 0 && f_score <= 100)
					break;
			}
			std::cout << "������������������һ��0��100֮�����Ч������";
		}
		stu.SetId(str_id);
		stu.SetName(str_name);
		stu.SetScore(f_score);
		StuDataSet.push_back(stu);	//��stuѹ��StuDataSet

		std::cout << "����������һλͬѧ����Ϣ��\n";
		std::cout << "��������Y�����������밴��N������������\n";
		std::cin >> c_contine_input;
		if ('Y' != c_contine_input && 'y' != c_contine_input)
			break;
	}
}

void App::DelStu(void)
{
	if (StuDataSet.empty())
	{
		std::cout << "ѧ���ɼ���Ϣ���ݿ�Ϊ�գ��������ԡ�\n";
		return;
	}

	std::cout << "��ѡ�����ṩ��ɾ��ͬѧ��ѧ�ţ�����������\n";
	char cSelect;
	while (true)
	{
		std::cout << "ѧ�Ż����������ṩѧ���밴��I�����ṩ�����밴��N��\n";
		std::cin >> cSelect;
		if ('I' == cSelect || 'i' == cSelect || 'N' == cSelect || 'n' == cSelect)
			break;
		else
		{
			std::cout << "������������������ѡ��\n";
		}
	}
	int vTarIndex{ -1 };
	switch (cSelect)
	{
	case 'I':
	case 'i':
	{
		std::cout << "�����ɾ��ͬѧ��ѧ�ţ�";
		std::string str_id;
		std::cin >> str_id;
		vTarIndex = FindById(str_id);
		if (-1 == vTarIndex)
		{
			std::cout << "δ�ҵ�ѧ��Ϊ " << str_id << " ��ͬѧ����Ϣ\n";
			return;
		}
		break;
	}
	case 'N':
	case 'n':
	{
		std::cout << "�����ɾ��ͬѧ��������";
		std::string str_name;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::getline(std::cin, str_name);
		vTarIndex = FindByName(str_name);
		if (-1 == vTarIndex)
		{
			std::cout << "δ�ҵ� " << str_name << " ͬѧ����Ϣ\n";
			return;
		}
		break;
	}
	}
	std::cout << "��ɾ��ͬѧ����Ϣ���£�\n";
	OutputSingleInfo(vTarIndex);
	std::cout << "ȷ��ɾ����ͬѧ����Ϣ��ȷ�ϰ���Y������������N������������";
	std::cin >> cSelect;
	if ('Y' == cSelect || 'y' == cSelect)
	{
		StuDataSet.erase(std::begin(StuDataSet) + vTarIndex);
	}
	else
	{
		std::cout << "�ѷ���ɾ��������\n";
	}
}

void App::ModifyScore(void)
{//ֻ�ṩ�ɼ��޸ģ������޸�ѧ�š�����
	if (StuDataSet.empty())
	{
		std::cout << "ѧ���ɼ���Ϣ���ݿ�Ϊ�գ��������ԡ�\n";
		return;
	}

	std::cout << "��ѡ�����ṩ��Ҫ�޸ĳɼ���ͬѧ��ѧ�ţ�����������\n";
	char cSelect;
	while (true)
	{
		std::cout << "ѧ�Ż����������ṩѧ���밴��I�����ṩ�����밴��N��\n";
		std::cin >> cSelect;
		if ('I' == cSelect || 'i' == cSelect || 'N' == cSelect || 'n' == cSelect)
			break;
		else
		{
			std::cout << "������������������ѡ��\n";
		}
	}
	int vTarIndex{ -1 };
	switch (cSelect)
	{
	case 'I':
	case 'i':
	{
		std::cout << "�������ͬѧ��ѧ�ţ�";
		std::string str_id;
		std::cin >> str_id;
		vTarIndex = FindById(str_id);
		if (-1 == vTarIndex)
		{
			std::cout << "δ�ҵ�ѧ��Ϊ " << str_id << " ��ͬѧ����Ϣ\n";
			return;
		}
		break;
	}
	case 'N':
	case 'n':
	{
		std::cout << "�������ͬѧ��������";
		std::string str_name;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::getline(std::cin, str_name);
		vTarIndex = FindByName(str_name);
		if (-1 == vTarIndex)
		{
			std::cout << "δ�ҵ� " << str_name << " ͬѧ����Ϣ\n";
			return;
		}
		break;
	}
	}
	std::cout << "���޸ĳɼ���ͬѧ����Ϣ���£�\n";
	OutputSingleInfo(vTarIndex);
	std::cout << "�� " << StuDataSet[vTarIndex].GetName() << " �ĳɼ��޸�Ϊ��";
	std::string str_score;
	float f_score;
	while (true)
	{
		std::cin >> str_score;
		if (isFloat(str_score))
		{
			f_score = static_cast<float>(atof(str_score.c_str()));
			if (f_score >= 0 && f_score <= 100)
				break;
		}
		std::cout << "������������������һ��0��100֮�����Ч������";
	}
	std::cout << "ȷ���޸���ȷ�ϰ���Y������������N������������";
	std::cin >> cSelect;
	if ('Y' == cSelect || 'y' == cSelect)
	{
		StuDataSet[vTarIndex].SetScore(f_score);
	}
	else
	{
		std::cout << "�޸ĳɼ������ѷ�����\n";
	}
}

void App::SortByScore()
{
	if (StuDataSet.empty())
	{
		return;
	}
	std::sort(StuDataSet.begin(), StuDataSet.end(), Student::CompareByScore);
}

void App::Query(void)
{
	char cSelect;
	while (true)
	{
		std::cout << "����ѧ�Ż���������ѯ��\n";
		std::cout << "����ѧ�ţ���ѡ��I����\n";
		std::cout << "������������ѡ��N����\n";

		std::cin >> cSelect;
		if ('I' == cSelect || 'i' == cSelect || 'N' == cSelect || 'n' == cSelect)
			break;
		else
		{
			std::cout << "������������������ѡ��\n";
		}
	}
	int vTarIndex{ -1 };
	switch (cSelect)
	{
	case 'I':
	case 'i':
	{
		std::cout << "�������ͬѧ��ѧ�ţ�";
		std::string str_id;
		std::cin >> str_id;
		vTarIndex = FindById(str_id);
		if (-1 == vTarIndex)
		{
			std::cout << "δ�ҵ�ѧ��Ϊ " << str_id << " ��ͬѧ����Ϣ\n";
			return;
		}
		break;
	}
	case 'N':
	case 'n':
	{
		std::cout << "�������ͬѧ��������";
		std::string str_name;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::getline(std::cin, str_name);
		vTarIndex = FindByName(str_name);
		if (-1 == vTarIndex)
		{
			std::cout << "δ�ҵ� " << str_name << " ͬѧ����Ϣ\n";
			return;
		}
		break;
	}
	}

	OutputSingleInfo(vTarIndex);
}

void App::OutputAllInfo()
{
	if (StuDataSet.empty())
	{
		std::cout << "ѧ���ɼ���Ϣ���ݿ�Ϊ�գ��������ԡ�\n";
		return;
	}

	//�ȸ��ݳɼ���StuDataSet��������
	SortByScore();

	//ȷ���ɼ��ϸ��벻�ϸ��ѧ����Χ
	size_t total_number = StuDataSet.size();
	size_t theFirstFailIndex{ total_number - static_cast<size_t>(total_number * 0.3f) };
	std::cout << "ѧ��\t" << "����\t" << "�ɼ�\t" << "�Ƿ�ϸ�\n";
	for (size_t i = 0; i < total_number; ++i)
	{
		std::cout << StuDataSet[i].GetId() << '\t'
			<< StuDataSet[i].GetName() << '\t'
			<< StuDataSet[i].GetScore() << '\t';
		if (i < theFirstFailIndex)
		{
			std::cout << "Pass\n";
		}
		else
		{
			std::cout << "Fail\n";
		}
	}
}

void App::OutputSingleInfo(int vIndex)
{
	if (StuDataSet.empty())
	{
		std::cout << "ѧ���ɼ���Ϣ���ݿ�Ϊ�ա�\n";
		return;
	}
	if (vIndex >= StuDataSet.size())
	{
		std::cout << "�������ݴ���\n";
		return;
	}

	std::cout << "ѧ��\t" << "����\t" << "�ɼ�\n";
	std::cout << StuDataSet[vIndex].GetId() << '\t'
		<< StuDataSet[vIndex].GetName() << '\t'
		<< StuDataSet[vIndex].GetScore() << '\n';
}

int App::FindById(std::string str_id)
{
	size_t total_number = StuDataSet.size();
	for (size_t t = 0; t < total_number; ++t)
	{
		if (str_id == StuDataSet[t].GetId())
			return static_cast<int>(t);
	}
	return -1;
}

int App::FindByName(std::string str_name)
{//��ϵͳ��һ��ȱ�ݣ�û�п��ǵ�ѧ�����������������
	size_t total_number = StuDataSet.size();
	for (size_t t = 0; t < total_number; ++t)
	{
		if (str_name == StuDataSet[t].GetName())
			return static_cast<int>(t);
	}
	return -1;
}

void App::MainMenuReadFile()
{
	//�ж������ļ��Ƿ��Ѵ��ڣ������ڣ�Ӧ���ѡ�
	//_access_s�ж������ļ��Ƿ����
	if (0 != _access_s(FileName.c_str(), 0))
	{
		StuDataSet.clear();
		std::cout << "û�ҵ������ļ���"
			<< FileName << "�����ļ���ȡ���ԡ�\n";
		return;
	}

	char cSelect;
	std::cout << "������´��ļ��ж�ȡ���ݣ�ϵͳ�е�ǰ���ݽ�����գ�\n";
	std::cout << "ȷ�����´������ļ��ж�ȡ������\n";
	std::cout << "ȷ���밴��Y�������򰴡�N������������\n";
	std::cin >> cSelect;
	if ('Y' != cSelect && 'y' != cSelect)
	{
		std::cout << "���¶�ȡ�����ļ�����ȡ����\n";
		return;
	}
	ReadFile(FileName);
	std::cout << "���´������ļ��ж�ȡ����Ϣ��ϵͳ�С�\n";
}

void App::ReadFile(std::string str_file_name)
{
	StuDataSet.clear();

	char aLine[LineMaxLen]{ "" };
	std::ifstream iFile(FileName);

	iFile.getline(aLine, sizeof(aLine));//�ļ���һ�У���Ч������

	iFile.getline(aLine, sizeof(aLine));//�ļ��ڶ��У�һ������������ѧ������
	std::string str(aLine);
	int iCount = stoi(str);//��ϵѧ������
	Student stu;
	for (int i = 0; i < iCount; ++i)
	{
		iFile >> stu;
		StuDataSet.push_back(stu);
	}

	iFile.close();
}

void App::MainMenuWriteFile()
{
	WriteFile(FileName);
}

void App::WriteFile(std::string str_file_name)
{
	std::ofstream oFile(FileName, std::ios_base::out);

	//�ļ���ͷһ��˵��������
	std::string strTmp = "��ľ��ȫ����ţ���ѧ���ɼ�\n";
	oFile << strTmp;
	strTmp = std::to_string(StuDataSet.size()) + "\n";
	oFile << strTmp;

	for (auto stu : StuDataSet)
	{
		oFile << stu;
	}

	oFile.close();
}

void App::Welcome()
{
	std::cout << "��ӭ���� ѧ���ɼ�����ϵͳ V1.0��\n";
}

MSG App::MainMenu()
{
	char cSelect;
	MSG msg = msgNULL;
	while (msgNULL == msg)
	{
		std::cout << "����ѧ���ɼ�---------------I\n";
		std::cout << "�޸�ѧ���ɼ�---------------M\n";
		std::cout << "ɾ��ѧ���ɼ�---------------E\n";
		std::cout << "���ݳɼ�����---------------S\n";
		std::cout << "��ѯ��Ϣ-------------------Q\n";
		std::cout << "���ѧ���ɼ�---------------P\n";
		std::cout << "���ļ���ȡ��Ϣ-------------R\n";
		std::cout << "����Ϣд���ļ�-------------W\n";
		std::cout << "����-----------------------C\n";
		std::cout << "�˳�-----------------------X\n";
		std::cout << "��ѡ��\n";
		std::cin >> cSelect;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		switch (cSelect)
		{
		case 'I':
		case 'i':
		{
			msg = msgAdd;
			break;
		}
		case 'M':
		case 'm':
		{
			msg = msgModify;
			break;
		}
		case 'E':
		case 'e':
		{
			msg = msgDelete;
			break;
		}
		case 'S':
		case 's':
		{
			msg = msgSort;
			break;
		}
		case 'Q':
		case 'q':
		{
			msg = msgQuery;
			break;
		}
		case 'P':
		case 'p':
		{
			msg = msgShow;
			break;
		}
		case 'R':
		case 'r':
		{
			msg = msgReadFile;
			break;
		}
		case 'W':
		case 'w':
		{
			msg = msgWriteFile;
			break;
		}
		case 'C':
		case 'c':
		{
			msg = msgClearScreen;
			break;
		}
		case 'X':
		case 'x':
		{
			msg = msgQuit;
			break;
		}
		default:
		{
			std::cout << "�����������ݲ˵���ʾѡ��\n";
		}
		}
	}

	return msg;
}
