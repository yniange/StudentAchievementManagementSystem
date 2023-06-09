#pragma once

#include <vector>
#include "Student.h"
#include "Global.h"

class App
{
public:
	App();
	~App();
	void InputData(void);	//����ѧ���ɼ���Ϣ
	void DelStu(void);	//ɾ��һλͬѧ����Ϣ
	void ModifyScore(void);	//�޸�ѧ���ɼ�
	void SortByScore(void);		//���ɼ�����
	void Query(void);	//��ѯѧ���ɼ���Ϣ
	void OutputAllInfo(void);	//���ȫ��ѧ���ɼ���Ϣ
	void OutputSingleInfo(int vIndex);//���һ��ѧ���ɼ���Ϣ
	int FindById(std::string str_id);	//�����ݼ��и���ѧ�Ų���
	int FindByName(std::string str_name);//�����ݼ��и��������Ų���
	void MainMenuReadFile();	//���˵����ļ����ܺ���
	void MainMenuWriteFile();	//���˵�д�ļ����ܺ���
	void ReadFile(std::string str_file_name = FileName);	//�������ļ��ж�ȡѧ���ɼ���Ϣ
	void WriteFile(std::string str_file_name = FileName);	//��ѧ���ɼ���Ϣд�������ļ���
	void InitDataSet();	//�ó�ʼ���ݳ�ʼ�����ݼ�����ϵͳ�ǵ�һ������ʱ����
	void Welcome();	//Welcome
	MSG MainMenu();	//���˵����ı��˵���
private:
	std::vector<Student> StuDataSet;	//ѧ���ɼ���Ϣ���ݼ�
};

