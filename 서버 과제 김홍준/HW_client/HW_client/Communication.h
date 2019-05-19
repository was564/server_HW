#pragma once
#include "header.h"
#include "initialization.h"
#include "error.h"

class Communication : public initialization
{
	char buf[BUFSIZE + 1];
	char data[BUFSIZE + 1];
	int retval;
	int share;
	int len;
public:
	void FirstSend();
	void FirstRecv();
	void SecondSend();
	void Send();
	void Recv();
	Communication();
	~Communication();
};

