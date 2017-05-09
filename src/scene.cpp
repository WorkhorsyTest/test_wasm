
#include "three.h"

namespace THREE {

Scene::Scene() : Object3D() {
	this->type = "Scene";

	this->background = nullptr;
	this->fog = nullptr;
//	this->overrideMaterial = nullptr;

	this->autoUpdate = true; // checked by the renderer
}

THREE::Scene* Scene::copy(THREE::Scene* source, bool recursive ) {
	Object3D::copy(source, recursive );

	if ( source->background != nullptr ) this->background = source->background->clone();
	if ( source->fog != nullptr ) this->fog = source->fog->clone();
//	if ( source->overrideMaterial != nullptr ) this->overrideMaterial = source->overrideMaterial->clone();

	this->autoUpdate = source->autoUpdate;
	this->matrixAutoUpdate = source->matrixAutoUpdate;

	return this;
}
/*
std::string Scene::toJSON( meta ) {
	std::string data = Object3D::toJSON( meta );

	if ( this->background != nullptr ) data.object.background = this->background.toJSON( meta );
	if ( this->fog != nullptr ) data.object.fog = this->fog.toJSON();

	return data;
}
*/
};
