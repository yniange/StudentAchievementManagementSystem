#pragma once

#include <string>
#include <fstream>

class Student
{
public:
	Student(std::string str_id = "",
		std::string str_name = "",
		float f_score = 0.0f);
	~Student() = default;
	void SetId(std::string str_id);
	void SetName(std::string str_name);
	void SetScore(float f_score);
	std::string GetId();
	std::string GetName();
	float GetScore();
	static bool CompareByScore(Student& s1, Student& s2);

	friend std::ofstream& operator<<(std::ofstream& ofs, Student& stu);
	friend std::ifstream& operator>>(std::ifstream& ifs, Student& stu);
private:
	std::string id;
	std::string name;
	float score;
};

