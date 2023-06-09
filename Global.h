#pragma once

#include <string>
#include <stdbool.h>

bool isFloat(std::string f_str);

const std::string FileName{ "Stu.dat" };//�����ļ��ļ���
const int LineMaxLen{ 1024 };	//һ������ַ���

using MSG = unsigned long;
#define msgNULL		0UL		//����Ϣ
#define msgAdd		1UL		//����
#define msgModify	2UL		//�޸�
#define msgDelete   3UL		//ɾ��
#define msgSort		4UL		//����
#define msgQuery	5UL		//��ѯ
#define msgShow		6UL		//���
#define msgReadFile 7UL		//���ļ�
#define msgWriteFile 8UL	//д�ļ�
#define msgClearScreen 9UL	//����
#define msgQuit		100UL	//�˳�ϵͳ
