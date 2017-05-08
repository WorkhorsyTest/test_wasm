

#ifndef _SCENE_H_
#define _SCENE_H_

#include "three.h"

class Scene : public Object3D {
public:
	Object* background;
	Fog* fog;
	//Material* overrideMaterial;
	bool autoUpdate;

	Scene();

	Scene* copy(Scene* source, bool recursive );

	//string toJSON( meta );
};

#endif // _SCENE_H_
