#include "windows.h"
#include "locale.h"
#include <stdio.h>

int BreakHan(wchar_t *str, wchar_t *buffer, UINT nSize)
{
	//檬己 
	static const wchar_t wcHead[] = { L'ぁ', L'あ', L'い', L'ぇ',
		L'え', L'ぉ', L'け', L'げ',
		L'こ', L'さ', L'ざ', L'し',
		L'じ', L'す', L'ず', L'せ',
		L'ぜ', L'そ', L'ぞ' };

	//吝己 
	static const wchar_t wcMid[] = { L'た', L'だ', L'ち', L'ぢ',
		L'っ', L'つ', L'づ', L'て',
		L'で', L'と', L'ど', L'な',
		L'に', L'ぬ', L'ね', L'の',
		L'は', L'ば', L'ぱ', L'ひ', L'び' };

	//辆己 
	static const wchar_t wcTail[] = { L' ', L'ぁ', L'あ', L'ぃ',
		L'い', L'ぅ', L'う', L'ぇ',
		L'ぉ', L'お', L'か', L'が',
		L'き', L'ぎ', L'く', L'ぐ',
		L'け', L'げ', L'ご', L'さ',
		L'ざ', L'し', L'じ', L'ず',
		L'せ', L'ぜ', L'そ', L'ぞ' };

	UINT    pos = 0;

	while (*str != '\0')
	{
		if (*str < 256)
		{
			if (pos + 2 >= nSize - 1)
				break;

			buffer[pos] = *str;
			++pos;
		}
		else
		{
			if (pos + 4 >= nSize - 1)
				break;

			buffer[pos] = wcHead[(*str - 0xAC00) / (21 * 28)];
			buffer[pos + 1] = wcMid[(*str - 0xAC00) % (21 * 28) / 28];
			buffer[pos + 2] = wcTail[(*str - 0xAC00) % 28];

			pos += 3;
		}

		++str;
	}

	buffer[pos] = '\0';
	return pos;
}

int main(int argc, char* argv[])
{
	wchar_t *str = L"撐唱府";
	wchar_t buffer[4096];

	BreakHan(str, buffer, sizeof buffer);
	setlocale(LC_ALL, "Korean");
	printf("%S", buffer);
	return 0;
}

