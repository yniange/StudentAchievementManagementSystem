#include "App.h"
#include <iostream>
#include <algorithm>
#include "Global.h"
#include <io.h>
#include <array>

App::App()
{
	//判断数据文件是否已存在
	if (0 != _access_s(FileName.c_str(), 0))
	{//如果数据文件不存在，利用初始数据设置StuDataSet
		InitDataSet();
	}
	else
	{//如果数据文件存在，则从数据文件中读取存储在文件中的数据
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
		"张三", "李四", "王五", "陈六", "钱七", "Jessi", "Elon Musk" };
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
	std::cout << "请输入学生成绩信息：\n";
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
			std::cout << "学号：";
			std::cin >> str_id;
			// 验证学号的唯一性
			if (-1 == FindById(str_id))
			{//输入的学号在数据集中不存在，可以使用
				break;
			}
			else
			{//输入的学号在数据集中已有，应提醒并要求重新输入
				std::cout << "学号已被占用，请重新输入。\n";
			}
		}

		// 输入学号时，通过键入回车键实现输入数据
		// 的提交，因此，之前的缓冲区队列最末尾一
		// 定有一个换行符\n。由于输入学号操作，从
		// 缓冲区中读取字符时遇到空白符（空格、Tab
		// 字符、换行符）即停止，因此输入学号操作
		// 结束后，缓冲区队列其实并不为空，而是留
		// 有一个换行符'\n'。
		// 因为函数getline可以读取缓冲区队列中的空白
		// 符，此时直接调用getline，getline不会等待用
		// 户输入，而是直接读走之前输入操作残留下来的
		// 这个换行符'\n'，并且使得读取的结束是一个空
		// 字符串。也就是说在这种情况下，getline无法
		// 实现输入一个有效字符串（姓名）的调用目的。
		// 所以在调用getline函数前，要确保之前缓冲区队
		// 列“干净”，以保证getline被调用时，缓冲区是
		// 空的。程序能在这时正常暂停下来，等待用户输
		// 入有效的字符。通过调用ignore函数，是一种常
		// 见的清空缓冲区的办法。
		// 注意，对于一般的cin操作，它将忽略缓冲区队列
		// 中前面所有的空白符，因此不会存在这里的问题。
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "姓名：";
		std::getline(std::cin, str_name);

		// cin操作时，如果希望用户输入的是数值类型数据
		// （整数、实数之类），而不是字符、字符串数据，
		// 则需要警惕一个问题：当用户输入的不是一个合法
		// 的数值时，譬如输入整数时，不小心键入了非数字
		// 字符，又或者输入实数时，小数点数量多于一个，
		// cin操作将失败，无法获取到一个正常输入数值，并
		// 且，cin也会被标志为bad，导致之后的输入操作无
		// 法正常执行。而且，由于此时的cin操作失败，缓冲
		// 区队列中的字符依然保持原样，如果通过调用cin的
		// clear方法将bad状态恢复，之后的输入操作依然将从
		// 原缓冲区队列中，从前往后去读取需要的数据。如果
		// 后续的读取操作同样是试图读取数值型数据，则又会
		// 重复出现之前的问题。
		// 因此，当我们在cin一个数值型数据时，建议先以字符
		// 串的形式输入，然后判断该字符串是否是一个合法的
		// 数值型数据的形式。如果是，则利用atoi、atof等函
		// 数，将该字符串转换为目的数值型数据，如果不是，
		// 则提示用户输入错误，并要求重新输入正确的形式。
		// 以确保程序的健壮性。
		std::cout << "成绩：";
		while (true)
		{
			std::cin >> str_score;
			if (isFloat(str_score))
			{
				f_score = static_cast<float>(atof(str_score.c_str()));
				if (f_score >= 0 && f_score <= 100)
					break;
			}
			std::cout << "您的输入有误，请输入一个0～100之间的有效分数：";
		}
		stu.SetId(str_id);
		stu.SetName(str_name);
		stu.SetScore(f_score);
		StuDataSet.push_back(stu);	//将stu压入StuDataSet

		std::cout << "继续输入下一位同学的信息吗？\n";
		std::cout << "继续按“Y”，结束输入按“N”或其它键。\n";
		std::cin >> c_contine_input;
		if ('Y' != c_contine_input && 'y' != c_contine_input)
			break;
	}
}

void App::DelStu(void)
{
	if (StuDataSet.empty())
	{
		std::cout << "学生成绩信息数据库为空，操作忽略。\n";
		return;
	}

	std::cout << "请选择是提供待删除同学的学号，还是姓名。\n";
	char cSelect;
	while (true)
	{
		std::cout << "学号还是姓名？提供学号请按“I”，提供姓名请按“N”\n";
		std::cin >> cSelect;
		if ('I' == cSelect || 'i' == cSelect || 'N' == cSelect || 'n' == cSelect)
			break;
		else
		{
			std::cout << "您的输入有误！请重新选择。\n";
		}
	}
	int vTarIndex{ -1 };
	switch (cSelect)
	{
	case 'I':
	case 'i':
	{
		std::cout << "输入待删除同学的学号：";
		std::string str_id;
		std::cin >> str_id;
		vTarIndex = FindById(str_id);
		if (-1 == vTarIndex)
		{
			std::cout << "未找到学号为 " << str_id << " 的同学的信息\n";
			return;
		}
		break;
	}
	case 'N':
	case 'n':
	{
		std::cout << "输入待删除同学的姓名：";
		std::string str_name;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::getline(std::cin, str_name);
		vTarIndex = FindByName(str_name);
		if (-1 == vTarIndex)
		{
			std::cout << "未找到 " << str_name << " 同学的信息\n";
			return;
		}
		break;
	}
	}
	std::cout << "待删除同学的信息如下：\n";
	OutputSingleInfo(vTarIndex);
	std::cout << "确认删除该同学的信息吗？确认按“Y”，放弃按“N”或其它键：";
	std::cin >> cSelect;
	if ('Y' == cSelect || 'y' == cSelect)
	{
		StuDataSet.erase(std::begin(StuDataSet) + vTarIndex);
	}
	else
	{
		std::cout << "已放弃删除操作。\n";
	}
}

void App::ModifyScore(void)
{//只提供成绩修改，不可修改学号、姓名
	if (StuDataSet.empty())
	{
		std::cout << "学生成绩信息数据库为空，操作忽略。\n";
		return;
	}

	std::cout << "请选择是提供需要修改成绩的同学的学号，还是姓名。\n";
	char cSelect;
	while (true)
	{
		std::cout << "学号还是姓名？提供学号请按“I”，提供姓名请按“N”\n";
		std::cin >> cSelect;
		if ('I' == cSelect || 'i' == cSelect || 'N' == cSelect || 'n' == cSelect)
			break;
		else
		{
			std::cout << "您的输入有误！请重新选择。\n";
		}
	}
	int vTarIndex{ -1 };
	switch (cSelect)
	{
	case 'I':
	case 'i':
	{
		std::cout << "输入待查同学的学号：";
		std::string str_id;
		std::cin >> str_id;
		vTarIndex = FindById(str_id);
		if (-1 == vTarIndex)
		{
			std::cout << "未找到学号为 " << str_id << " 的同学的信息\n";
			return;
		}
		break;
	}
	case 'N':
	case 'n':
	{
		std::cout << "输入待查同学的姓名：";
		std::string str_name;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::getline(std::cin, str_name);
		vTarIndex = FindByName(str_name);
		if (-1 == vTarIndex)
		{
			std::cout << "未找到 " << str_name << " 同学的信息\n";
			return;
		}
		break;
	}
	}
	std::cout << "待修改成绩的同学的信息如下：\n";
	OutputSingleInfo(vTarIndex);
	std::cout << "将 " << StuDataSet[vTarIndex].GetName() << " 的成绩修改为：";
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
		std::cout << "您的输入有误，请输入一个0～100之间的有效分数：";
	}
	std::cout << "确认修改吗？确认按“Y”，放弃按“N”或其它键：";
	std::cin >> cSelect;
	if ('Y' == cSelect || 'y' == cSelect)
	{
		StuDataSet[vTarIndex].SetScore(f_score);
	}
	else
	{
		std::cout << "修改成绩操作已放弃。\n";
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
		std::cout << "根据学号还是姓名查询？\n";
		std::cout << "根据学号，请选“I”，\n";
		std::cout << "根据姓名，请选“N”。\n";

		std::cin >> cSelect;
		if ('I' == cSelect || 'i' == cSelect || 'N' == cSelect || 'n' == cSelect)
			break;
		else
		{
			std::cout << "您的输入有误！请重新选择。\n";
		}
	}
	int vTarIndex{ -1 };
	switch (cSelect)
	{
	case 'I':
	case 'i':
	{
		std::cout << "输入待查同学的学号：";
		std::string str_id;
		std::cin >> str_id;
		vTarIndex = FindById(str_id);
		if (-1 == vTarIndex)
		{
			std::cout << "未找到学号为 " << str_id << " 的同学的信息\n";
			return;
		}
		break;
	}
	case 'N':
	case 'n':
	{
		std::cout << "输入待查同学的姓名：";
		std::string str_name;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::getline(std::cin, str_name);
		vTarIndex = FindByName(str_name);
		if (-1 == vTarIndex)
		{
			std::cout << "未找到 " << str_name << " 同学的信息\n";
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
		std::cout << "学生成绩信息数据库为空，操作忽略。\n";
		return;
	}

	//先根据成绩对StuDataSet进行排序
	SortByScore();

	//确定成绩合格与不合格的学生范围
	size_t total_number = StuDataSet.size();
	size_t theFirstFailIndex{ total_number - static_cast<size_t>(total_number * 0.3f) };
	std::cout << "学号\t" << "姓名\t" << "成绩\t" << "是否合格\n";
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
		std::cout << "学生成绩信息数据库为空。\n";
		return;
	}
	if (vIndex >= StuDataSet.size())
	{
		std::cout << "参数传递错误！\n";
		return;
	}

	std::cout << "学号\t" << "姓名\t" << "成绩\n";
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
{//本系统有一个缺陷：没有考虑到学生可能重名的情况。
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
	//判断数据文件是否已存在，不存在，应提醒。
	//_access_s判断数据文件是否存在
	if (0 != _access_s(FileName.c_str(), 0))
	{
		StuDataSet.clear();
		std::cout << "没找到数据文件“"
			<< FileName << "”，文件读取忽略。\n";
		return;
	}

	char cSelect;
	std::cout << "如果重新从文件中读取数据，系统中当前数据将被清空！\n";
	std::cout << "确认重新从数据文件中读取数据吗？\n";
	std::cout << "确认请按“Y”，否则按“N”或其它键：\n";
	std::cin >> cSelect;
	if ('Y' != cSelect && 'y' != cSelect)
	{
		std::cout << "重新读取数据文件操作取消。\n";
		return;
	}
	ReadFile(FileName);
	std::cout << "重新从数据文件中读取了信息至系统中。\n";
}

void App::ReadFile(std::string str_file_name)
{
	StuDataSet.clear();

	char aLine[LineMaxLen]{ "" };
	std::ifstream iFile(FileName);

	iFile.getline(aLine, sizeof(aLine));//文件第一行，无效文字行

	iFile.getline(aLine, sizeof(aLine));//文件第二行，一个整数，代表学生人数
	std::string str(aLine);
	int iCount = stoi(str);//联系学生人数
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

	//文件开头一行说明性文字
	std::string strTmp = "土木安全类最牛班的学生成绩\n";
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
	std::cout << "欢迎进入 学生成绩管理系统 V1.0。\n";
}

MSG App::MainMenu()
{
	char cSelect;
	MSG msg = msgNULL;
	while (msgNULL == msg)
	{
		std::cout << "输入学生成绩---------------I\n";
		std::cout << "修改学生成绩---------------M\n";
		std::cout << "删除学生成绩---------------E\n";
		std::cout << "根据成绩排序---------------S\n";
		std::cout << "查询信息-------------------Q\n";
		std::cout << "输出学生成绩---------------P\n";
		std::cout << "从文件读取信息-------------R\n";
		std::cout << "将信息写入文件-------------W\n";
		std::cout << "清屏-----------------------C\n";
		std::cout << "退出-----------------------X\n";
		std::cout << "请选择：\n";
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
			std::cout << "输入错误！请根据菜单提示选择。\n";
		}
		}
	}

	return msg;
}
