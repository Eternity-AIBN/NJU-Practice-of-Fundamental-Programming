#include"InfoHandle.h"

/*LPCWSTR stringToLPCWSTR(std::string orig)   //将string类型的歌名转化为wcstring以便播放
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
		mciSendStringA(lpc, NULL, 0, NULL);   //打开MP3文件
		mciSendString(TEXT("play song"), NULL, 0, NULL);   //播放歌曲
		while (1)  //持续播放
			if (cutSongFlag == true)   //切歌
			{
				mciSendString(TEXT("close song"), NULL, 0, NULL);   //关闭上一首歌
				cutSongFlag = false;
				break;
			}
		if (switchAdmin == true)
			return;
	}
}
