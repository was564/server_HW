#pragma once
#include "header.h"

class error
{
public:
	void err_display(const char* msg);
	void err_quit(const char* msg);
	error();
	~error();
};

