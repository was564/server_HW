#pragma once
#include "Init.h"

class Socket
{
public:
	Socket();
	~Socket();
	
	void socket1(char* buf, const char* id, const char* pw);
	void socket4(char* buf, int object, int p_x, int p_y, int e_x, int e_y);
	void socket5(char* buf, int object, int p_x, int p_y);
	void socket6(char* buf, int p_x, int p_y);
	void socket7(char* buf, const char* id, const char* pw);
};

