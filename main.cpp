

//#include <stdio.h>
/*
extern print(char *message);
extern jsClearRect(int x, int y, int width, int height);
extern jsFillRect(int x, int y, int width, int height);
extern setInterval(int (*callback)());

int runCallback(int (*callback)()) { return callback(); }
*/

extern "C" void Herp(int derps);

extern "C" int doubler(int x) {
	Herp(x);
	//printf("fuuuuuuuuuuu: %d\n", 76);
	return 2 * x;
}
