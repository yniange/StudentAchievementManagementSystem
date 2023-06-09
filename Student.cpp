#include "Student.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

Student::Student(std::string str_id,
	std::string str_name, float f_score)
	:id(str_id),
	name(str_name),
	score(f_score)
{
}

void Student::SetId(std::string str_id)
{
	id = str_id;
}

void Student::SetName(std::string str_name)
{
	name = str_name;
}

void Student::SetScore(float f_score)
{
	score = f_score;
}

std::string Student::GetId()
{
	return id;
}

std::string Student::GetName()
{
	return name;
}

float Student::GetScore()
{
	return score;
}

std::ofstream& operator<<(std::ofstream& ofs, Student& stu)
{
	ofs << stu.id;
	ofs << ',';
	ofs << stu.name;
	ofs << ',';
	ofs << stu.score;
	ofs << '\n';

    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, Student& stu)
{
	getline(ifs, stu.id, ',');
	getline(ifs, stu.name, ',');
	std::string str_score;
	getline(ifs, str_score, '\n');
	stu.score = static_cast<float>(stod(str_score));

	return ifs;
}

bool Student::CompareByScore(Student& s1, Student& s2)
{//ע�⣬������ββ��ܼ�const����Ϊ�ڱ�����
 //����Ҫ�����βζ���ĳ�Ա��������������ֻ��
 //�����䳣��Ա���������ܵ�������ͨ��Ա������
	return s1.GetScore() > s2.GetScore();//���ݳɼ��ɸߵ������������� >
}