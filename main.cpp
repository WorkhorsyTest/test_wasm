
#include "three.h"

int main(int argc, char ** argv) {
	printf("Hello, world!\n");

	Vector3* v = new Vector3();
	printf("x: %f\n", v->x);

	vector<int> msg = { 1, 2, 3, 4, 5 };
	for (int i=0; i<msg.size(); ++i) {
		printf("msg: %d\n", msg[i]);
	}
}
