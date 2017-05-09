
#ifndef _OBJECT_3D_H_
#define _OBJECT_3D_H_

#include "three.h"

namespace THREE {

class Object3D : public EventDispatcher {
public:
	static THREE::Vector3* DefaultUp;
	static bool DefaultMatrixAutoUpdate;
	static int object3DId;

	bool isObject3D = true;
	int id;
	std::string uuid;
	std::string name;
	std::string type;
	THREE::Object3D* parent;
	std::vector<THREE::Object3D*> children;
	THREE::Vector3* up;

	THREE::Vector3* _position;
	THREE::Euler* _rotation;
	THREE::Quaternion* _quaternion;
	THREE::Vector3* _scale;
	THREE::Matrix4* _modelViewMatrix;
	THREE::Matrix3* _normalMatrix;

	THREE::Matrix4* matrix;
	THREE::Matrix4* matrixWorld;

	bool matrixAutoUpdate;
	bool matrixWorldNeedsUpdate;

	//Layers* layers;
	bool visible;

	bool castShadow;
	bool receiveShadow;

	bool frustumCulled;
	int renderOrder;

	std::string userData;

	//this->onBeforeRender = function () {};
	//this->onAfterRender = function () {};

	THREE::Vector3* position();
	THREE::Euler* rotation();
	THREE::Quaternion* quaternion();
	THREE::Vector3* scale();
	THREE::Matrix4* modelViewMatrix();
	THREE::Matrix3* normalMatrix();

	Object3D();

	void applyMatrix(THREE::Matrix4* matrix );

	void setRotationFromAxisAngle(THREE::Vector3* axis, float angle );

	void setRotationFromEuler(THREE::Euler* euler );

	void setRotationFromMatrix(THREE::Matrix4* m );

	void setRotationFromQuaternion(THREE::Quaternion* q );

	THREE::Object3D* rotateOnAxis(THREE::Vector3* axis, float angle);

	THREE::Object3D* rotateX(float angle);

	THREE::Object3D* rotateY(float angle);

	THREE::Object3D* rotateZ(float angle);

	THREE::Object3D* translateOnAxis(THREE::Vector3* axis, float distance);

	THREE::Object3D* translateX(float distance);

	THREE::Object3D* translateY(float distance);

	THREE::Object3D* translateZ(float distance);

	THREE::Vector3* localToWorld(THREE::Vector3* vector );

	THREE::Vector3* worldToLocal(THREE::Vector3* vector);

	void lookAt(THREE::Vector3* vector);

	THREE::Object3D* add(THREE::Object3D* object );

	void remove(THREE::Object3D* object );

	THREE::Object3D* getObjectById(int id );

	THREE::Object3D* getObjectByName(std::string name );

	THREE::Object3D* getObjectByProperty(std::string name, std::string value );

	THREE::Vector3* getWorldPosition(THREE::Vector3* optionalTarget );

	THREE::Quaternion* getWorldQuaternion(THREE::Quaternion* optionalTarget);

	THREE::Euler* getWorldRotation(THREE::Euler* optionalTarget);

	THREE::Vector3* getWorldScale(THREE::Vector3* optionalTarget);

	THREE::Vector3* getWorldDirection(THREE::Vector3* optionalTarget);

	void raycast();
/*
	void traverse( callback );

	void traverseVisible( callback );

	void traverseAncestors( callback );
*/
	void updateMatrix();

	void updateMatrixWorld(bool force );
/*
	toJSON( meta );
*/
	THREE::Object3D* clone();

	THREE::Object3D* clone(bool recursive );

	THREE::Object3D* copy(THREE::Object3D* source);

	THREE::Object3D* copy(THREE::Object3D* source, bool recursive );
};

};

#endif // _OBJECT_3D_H_
