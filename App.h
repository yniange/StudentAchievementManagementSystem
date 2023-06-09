#pragma once

#include <vector>
#include "Student.h"
#include "Global.h"

class App
{
public:
	App();
	~App();
	void InputData(void);	//输入学生成绩信息
	void DelStu(void);	//删除一位同学的信息
	void ModifyScore(void);	//修改学生成绩
	void SortByScore(void);		//按成绩排序
	void Query(void);	//查询学生成绩信息
	void OutputAllInfo(void);	//输出全部学生成绩信息
	void OutputSingleInfo(int vIndex);//输出一个学生成绩信息
	int FindById(std::string str_id);	//从数据集中根据学号查找
	int FindByName(std::string str_name);//从数据集中根据姓名号查找
	void MainMenuReadFile();	//主菜单读文件功能函数
	void MainMenuWriteFile();	//主菜单写文件功能函数
	void ReadFile(std::string str_file_name = FileName);	//从数据文件中读取学生成绩信息
	void WriteFile(std::string str_file_name = FileName);	//将学生成绩信息写入数据文件中
	void InitDataSet();	//用初始数据初始化数据集，当系统是第一次运行时调用
	void Welcome();	//Welcome
	MSG MainMenu();	//主菜单（文本菜单）
private:
	std::vector<Student> StuDataSet;	//学生成绩信息数据集
};

