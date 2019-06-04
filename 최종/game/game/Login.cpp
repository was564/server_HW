#include "Login.h"



Login::Login()
{
}


Login::~Login()
{
}

void Login::input()
{
	cout << "id를 입력하세요 : ";
	cin >> id;
	cout << "Password를 입력하세요 : ";
	cin >> password;
}

void Login::send()
{
	
}

bool Login::recv()
{
	return false;
}
