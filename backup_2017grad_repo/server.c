#include "windows.h"
#include "locale.h"
#include <stdio.h>

int BreakHan(wchar_t *str, wchar_t *buffer, UINT nSize)
{
	//�ʼ� 
	static const wchar_t wcHead[] = { L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��' };

	//�߼� 
	static const wchar_t wcMid[] = { L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��', L'��' };

	//���� 
	static const wchar_t wcTail[] = { L' ', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��' };

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
	wchar_t *str = L"�γ���";
	wchar_t buffer[4096];

	BreakHan(str, buffer, sizeof buffer);
	setlocale(LC_ALL, "Korean");
	printf("%S", buffer);
	return 0;
}

