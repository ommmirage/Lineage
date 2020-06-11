#include "MultiClientListener.h"

int main()
{
	MultiClientListener listener("127.0.0.1", 54000);
	if (listener.init() != 0)
		return -1;

	listener.run();
}