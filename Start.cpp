// 系统开发要求见Readme.txt文件

#include "Global.h"
#include "App.h"
#include <iostream>

int main(void)
{
	App theApp;
	theApp.Welcome();

	MSG msg;
	while (msg = theApp.MainMenu(), msgQuit != msg)
	{
		switch (msg)
		{
		case msgAdd:
		{
			theApp.InputData();
			break;
		}
		case msgModify:
		{
			theApp.ModifyScore();
			break;
		}
		case msgDelete:
		{
			theApp.DelStu();
			break;
		}
		case msgSort:
		{
			theApp.SortByScore();
			theApp.OutputAllInfo();
			break;
		}
		case msgQuery:
		{
			theApp.Query();
			break;
		}
		case msgShow:
		{
			theApp.OutputAllInfo();
			break;
		}
		case msgReadFile:
		{
			theApp.MainMenuReadFile();
			break;
		}
		case msgWriteFile:
		{
			theApp.MainMenuWriteFile();
			break;
		}
		case msgClearScreen:
		{
			system("cls");
			break;
		}
		}
	}

    return 0;
}