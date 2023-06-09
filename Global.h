#pragma once

#include <string>
#include <stdbool.h>

bool isFloat(std::string f_str);

const std::string FileName{ "Stu.dat" };//数据文件文件名
const int LineMaxLen{ 1024 };	//一行最大字符数

using MSG = unsigned long;
#define msgNULL		0UL		//空消息
#define msgAdd		1UL		//输入
#define msgModify	2UL		//修改
#define msgDelete   3UL		//删除
#define msgSort		4UL		//排序
#define msgQuery	5UL		//查询
#define msgShow		6UL		//输出
#define msgReadFile 7UL		//读文件
#define msgWriteFile 8UL	//写文件
#define msgClearScreen 9UL	//清屏
#define msgQuit		100UL	//退出系统
