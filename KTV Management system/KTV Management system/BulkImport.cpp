#include"InfoHandle.h"
#include<fstream>

vector<Song> importSong;

bool fileImport(const string &name)
{
	ifstream fin(name);
	if (!fin.is_open())   //�ļ���ʧ��
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		Draw::gotoxy(32, 15);
		cerr << "Error";
		Sleep(500);
		Draw::gotoxy(32, 15);
		cout << "     ";
		return false;
	}
	Song tmp;
	string str;
	int n;
	bool m;
	float a;
	while (fin >> n)
	{
		tmp.id = n;
		fin >> str;
		tmp.songName = str;
		fin >> str;
		tmp.singerName = str;
		fin >> str;
		tmp.songAbbreviation = str;
		fin >> m;
		tmp.status = m;
		fin >> a;
		tmp.score = a;
		importSong.push_back(tmp);
	}
	fin.close();
	return true;
}

void InfoHandle::bulkImport()
{
	system("cls");
	Song tmp;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 12);
	Draw::gotoxy(40, 8);
	cout << "***��������***";
	Draw::gotoxy(28, 10);
	cout << "�����뵼����ļ�����";
	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		Draw::gotoxy(48, 10);
		cout << "          ";
		string fileName;
		Draw::gotoxy(48, 10);
		cin >> fileName;
		if (fileImport(fileName))
		{
			int sum = importSong.size(); //�������������
			int success = 0; //�ɹ������������
			for (auto tmp : importSong)
				if (!judgeExist(tmp))
				{
					tmp.id = songs.size() + 1;
					songs.push_back(tmp);
					success++;
				}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			Draw::gotoxy(28, 12);
			cout << "������ɣ��ܹ�����" << sum << "�׸���";
			Draw::gotoxy(30, 13);
			cout << success << "�׵���ɹ�!!!";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			Draw::gotoxy(30, 14);
			cout << sum - success << "�׵���ʧ��(�������Ѵ���)";
			Draw::gotoxy(30, 15);
			cout << "�Ƿ��������(y/n):";
			char c;
			while (1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				cin >> c;
				if (c == 'n')return;
				else if (c == 'y')break;
				else {
					Draw::gotoxy(48, 15);
					cout << "       ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					Draw::gotoxy(32, 17);
					cout << "��Чָ�����������...";
					Sleep(250);
					Draw::gotoxy(32, 17);
					cout << "                       ";
					Draw::gotoxy(31, 16);
					cout << "                       ";
					Draw::gotoxy(48, 15);
				}
			}
			Draw::gotoxy(28, 12);
			cout << "                              ";
			Draw::gotoxy(28, 13);
			cout << "                              ";
			Draw::gotoxy(30, 14);
			cout << "                               ";
			Draw::gotoxy(30, 15);
			cout << "                       ";
		}
	}
}