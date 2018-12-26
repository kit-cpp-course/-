#include "stdafx.h"
#include <iostream> // потоки ввода-вывода

#include <winsock2.h> // работа с сокетами

using namespace std;


class RC4{
	char S[256];
	unsigned int i,j;
	inline void Swap(int,int);
public:
	//само шифрование
	char GetXor();
	//инициализация ключа
	void Init(char *key,int len);
	//шифрование (для всех байтов)
	char* Crypt(char *data,int size);
};

//добавляется кусок ключа и заносится в рамки 255 битов
void RC4::Init(char *key,int len)
{
	if(!len) len=strlen((char*)key);
	for(i=0; i<256; i++) S[i]=i;
	for(i=j=0; i<256; i++) {
		j=(j+S[i]+key[i%len])&255;
		Swap(i,j);
	}
	i=j=0;
}


//работает как XOR операция ^ , но просто расписаная
char RC4::GetXor()
{
	i=(i+1)&255; j=(j+S[i])&255; Swap(i,j);
	return S[(S[i]+S[j])&255];
}

//меняем местами
void RC4::Swap(int i,int j)
{
	char t=S[i]; S[i]=S[j]; S[j]=t;
}

///шифруем по размеру поданного текста/ ну или дешифруем/ разницы никакой
char* RC4::Crypt(char *data,int size)
{
	int n;
	for(n=0; n<size; n++) data[n]^=GetXor();

	return data;
}

void main()
{
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
WORD wVersionRequested;
WSADATA wsaData;
//подключили сокеты
SOCKET s;
sockaddr_in addr;

int err;

wVersionRequested = MAKEWORD(2, 2);
err = WSAStartup(wVersionRequested, &wsaData);

if (err != 0) return;

//указали технологию подключения
//ip
//port
//инициализировали подключение
addr.sin_family = AF_INET;
addr.sin_port = htons(1280);
addr.sin_addr.s_addr = inet_addr("127.0.0.1");
s = socket(AF_INET, SOCK_STREAM, 0);

//законектились
connect(s, (sockaddr*) &addr, sizeof(addr));

cout << "Введите строку" << endl;


RC4 rc4;
char b[256];
cin.getline(b, sizeof(b), '\n');

int cnt = 0;
while(b[cnt] != '\0')
{
	cnt++;
}
rc4.Init((char*)"ключ",0);
char *cryptData = rc4.Crypt(b,cnt);
//передали серверу шифр
send(s, b, sizeof(b), 0);
//слушаем ответ
//если ответил, то читаем
if (recv(s, b, sizeof(b), 0) != 0)
	cout << b << endl;

system("pause");
closesocket(s);
WSACleanup();

}
