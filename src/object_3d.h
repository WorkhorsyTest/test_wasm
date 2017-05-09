
#ifndef _OBJECT_3D_H_
#define _OBJECT_3D_H_

#include "three.h"


class Object3D : public EventDispatcher {
public:
	static Vector3* DefaultUp;
	static bool DefaultMatrixAutoUpdate;
	static int object3DId;

	bool isObject3D = true;
	int id;
	string uuid;
	string name;
	string type;
	Object3D* parent;
	vector<Object3D*> children;
	Vector3* up;

	Vector3* _position;
	Euler* _rotation;
	Quaternion* _quaternion;
	Vector3* _scale;
	Matrix4* _modelViewMatrix;
	Matrix3* _normalMatrix;

	Matrix4* matrix;
	Matrix4* matrixWorld;

	bool matrixAutoUpdate;
	bool matrixWorldNeedsUpdate;

	//Layers* layers;
	bool visible;

	bool castShadow;
	bool receiveShadow;

	bool frustumCulled;
	int renderOrder;

	string userData;

	//this->onBeforeRender = function () {};
	//this->onAfterRender = function () {};

	Vector3* position();
	Euler* rotation();
	Quaternion* quaternion();
	Vector3* scale();
	Matrix4* modelViewMatrix();
	Matrix3* normalMatrix();

	Object3D();

	void applyMatrix(Matrix4* matrix );

	void setRotationFromAxisAngle(Vector3* axis, float angle );

	void setRotationFromEuler(Euler* euler );

	void setRotationFromMatrix(Matrix4* m );

	void setRotationFromQuaternion(Quaternion* q );

	Object3D* rotateOnAxis(Vector3* axis, float angle);

	Object3D* rotateX(float angle);

	Object3D* rotateY(float angle);

	Object3D* rotateZ(float angle);

	Object3D* translateOnAxis(Vector3* axis, float distance);

	Object3D* translateX(float distance);

	Object3D* translateY(float distance);

	Object3D* translateZ(float distance);

	Vector3* localToWorld(Vector3* vector );

	Vector3* worldToLocal(Vector3* vector);

	void lookAt(Vector3* vector);

	Object3D* add(Object3D* object );

	void remove(Object3D* object );

	Object3D* getObjectById(int id );

	Object3D* getObjectByName(string name );

	Object3D* getObjectByProperty(string name, string value );

	Vector3* getWorldPosition(Vector3* optionalTarget );

	Quaternion* getWorldQuaternion(Quaternion* optionalTarget);

	Euler* getWorldRotation(Euler* optionalTarget);

	Vector3* getWorldScale(Vector3* optionalTarget);

	Vector3* getWorldDirection(Vector3* optionalTarget);

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
	Object3D* clone();

	Object3D* clone(bool recursive );

	Object3D* copy(Object3D* source);

	Object3D* copy(Object3D* source, bool recursive );
};

#endif // _OBJECT_3D_H_
