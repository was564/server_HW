#include "main_client.h"


int main(int argc, char* argv[])
{
	initialization init;
	Communication com;
	
	com.FirstSend();
	com.FirstRecv();
	com.SecondSend();

	while (1) {
		com.Send();
		com.Recv();
	}
	
	return 0;
}