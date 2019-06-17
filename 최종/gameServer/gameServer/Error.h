#pragma once
#include "Init.h"

class Error
{
public:
	void err_quit(const char* msg);
	void err_display(const char* msg);
	Error();
	~Error();
};

