
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <assert.h>
#include <array>

using namespace std;

#include "Math.h"
#include "matrix3.h"
#include "matrix4.h"
#include "vector3.h"
#include "quaternion.h"
#include "euler.h"
#include "object_3d.h"

int main(int argc, char ** argv) {
	printf("Hello, world!\n");

	Vector3* v = new Vector3();
	printf("x: %f\n", v->x);

	vector<int> msg = { 1, 2, 3, 4, 5 };
	for (int i=0; i<msg.size(); ++i) {
		printf("msg: %d\n", msg[i]);
	}
}
