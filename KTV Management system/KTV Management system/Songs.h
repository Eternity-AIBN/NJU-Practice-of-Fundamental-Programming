#pragma once
#include<string>
#include<vector>

struct Song
{
	int id;   //����ID(���)
	int serialNum;  //�����б�������
	std::string songName;  //������
	std::string singerName;  //������
	std::string songAbbreviation;  //��������д
	bool status;   //����״̬(0��ʾ���ڲ��ţ�1��ʾδ����)
	float score;   //�û�����
};