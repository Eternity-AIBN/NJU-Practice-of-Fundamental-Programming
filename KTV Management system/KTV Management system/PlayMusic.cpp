#include"InfoHandle.h"

/*LPCWSTR stringToLPCWSTR(std::string orig)   //��string���͵ĸ���ת��Ϊwcstring�Ա㲥��
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = new wchar_t[sizeof(wchar_t)*(orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}*/

void InfoHandle::playMusic()
{
	while (1) {
		string tmp = "open " + nowTheSong + ".mp3 alias song";
		LPCSTR lpc = tmp.c_str();
		mciSendStringA(lpc, NULL, 0, NULL);   //��MP3�ļ�
		mciSendString(TEXT("play song"), NULL, 0, NULL);   //���Ÿ���
		while (1)  //��������
			if (cutSongFlag == true)   //�и�
			{
				mciSendString(TEXT("close song"), NULL, 0, NULL);   //�ر���һ�׸�
				cutSongFlag = false;
				break;
			}
		if (switchAdmin == true)
			return;
	}
}
