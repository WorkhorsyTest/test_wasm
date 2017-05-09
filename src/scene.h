

#ifndef _SCENE_H_
#define _SCENE_H_

#include "three.h"

namespace THREE {

class Scene : public Object3D {
public:
	Object* background;
	THREE::Fog* fog;
	//Material* overrideMaterial;
	bool autoUpdate;

	Scene();

	THREE::Scene* copy(THREE::Scene* source, bool recursive );

	//std::string toJSON( meta );
};

};

#endif // _SCENE_H_
