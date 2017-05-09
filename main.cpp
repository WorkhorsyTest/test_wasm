
#include "src/three.h"

int main(int argc, char ** argv) {
	printf("Hello, world!\n");

	auto v = new THREE::Vector3();
	printf("x: %f\n", v->x);

	std::vector<int> msg = { 1, 2, 3, 4, 5 };
	for (int i=0; i<msg.size(); ++i) {
		printf("msg: %d\n", msg[i]);
	}
/*
	// Clock
	auto g_clock = new Clock();

	// Scene
	auto g_scene = new Scene();

	// Renderer
	auto g_screen = document.getElementById( 'screen' );
	auto g_renderer = new WebGLRenderer({ canvas: g_screen, antialias: true });
//	OnResize();

	// Camera
	float VIEW_ANGLE = 45;
	float NEAR = 0.1;
	float FAR = 20000;
	g_camera = new THREE.PerspectiveCamera( VIEW_ANGLE, ASPECT_RATIO, NEAR, FAR);
	g_camera.camera_offset_x = 0;
	g_scene.add(g_camera);
	g_camera.position.set(0, 150, 500);
	g_camera.lookAt(g_scene.position);
*/
}
