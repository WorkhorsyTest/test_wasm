
#include "three.h"

namespace THREE {

THREE::Vector3* Object3D::DefaultUp = new Vector3( 0, 1, 0 );
bool Object3D::DefaultMatrixAutoUpdate = true;
int Object3D::object3DId = 0;

THREE::Vector3* Object3D::position() {
	return this->_position;
}
THREE::Euler* Object3D::rotation() {
	return this->_rotation;
}
THREE::Quaternion* Object3D::quaternion() {
	return this->_quaternion;
}
THREE::Vector3* Object3D::scale() {
	return this->_scale;
}
THREE::Matrix4* Object3D::modelViewMatrix() {
	return this->_modelViewMatrix;
}
THREE::Matrix3* Object3D::normalMatrix() {
	return this->_normalMatrix;
}

Object3D::Object3D() : EventDispatcher() {
	this->id = Object3D::object3DId++;

	this->uuid = Math::generateUUID();

	this->name = "";
	this->type = "Object3D";

	this->parent = nullptr;
	this->children = {};

	this->up = Object3D::DefaultUp->clone();

	this->_position = new Vector3();
	this->_rotation = new Euler();
	this->_quaternion = new Quaternion();
	this->_scale = new Vector3( 1, 1, 1 );
	this->_modelViewMatrix = new Matrix4();
	this->_normalMatrix = new Matrix3();

/*
	function onRotationChange() {
		quaternion.setFromEuler( rotation, false );
	}

	function onQuaternionChange() {
		rotation.setFromQuaternion( quaternion, nullptr, false );
	}

	rotation.onChange( onRotationChange );
	quaternion.onChange( onQuaternionChange );
*/

	this->matrix = new Matrix4();
	this->matrixWorld = new Matrix4();

	this->matrixAutoUpdate = Object3D::DefaultMatrixAutoUpdate;
	this->matrixWorldNeedsUpdate = false;

	//this->layers = new Layers();
	this->visible = true;

	this->castShadow = false;
	this->receiveShadow = false;

	this->frustumCulled = true;
	this->renderOrder = 0;

	this->userData = "";
/*
	this->onBeforeRender = function () {};
	this->onAfterRender = function () {};
*/
}

void Object3D::applyMatrix(THREE::Matrix4* matrix ) {
	this->matrix->multiplyMatrices( matrix, this->matrix );
	this->matrix->decompose( this->position(), this->quaternion(), this->scale() );
}

void Object3D::setRotationFromAxisAngle(THREE::Vector3* axis, float angle ) {
	// assumes axis is normalized
	this->quaternion()->setFromAxisAngle( axis, angle );
}

void Object3D::setRotationFromEuler(THREE::Euler* euler ) {
	this->quaternion()->setFromEuler( euler, true );
}

void Object3D::setRotationFromMatrix(THREE::Matrix4* m ) {
	// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)
	this->quaternion()->setFromRotationMatrix( m );
}

void Object3D::setRotationFromQuaternion(THREE::Quaternion* q ) {
	// assumes q is normalized
	this->quaternion()->copy( q );
}

THREE::Object3D* Object3D::rotateOnAxis(THREE::Vector3* axis, float angle) {
	// rotate object on axis in object space
	// axis is assumed to be normalized
	auto q1 = new Quaternion();
	q1->setFromAxisAngle( axis, angle );
	this->quaternion()->multiply( q1 );
	return this;
}

THREE::Object3D* Object3D::rotateX(float angle) {
	auto v1 = new Vector3( 1, 0, 0 );
	return this->rotateOnAxis( v1, angle );
}

THREE::Object3D* Object3D::rotateY(float angle) {
	auto v1 = new Vector3( 0, 1, 0 );
	return this->rotateOnAxis( v1, angle );
}

THREE::Object3D* Object3D::rotateZ(float angle) {
	auto v1 = new Vector3( 0, 0, 1 );
	return this->rotateOnAxis( v1, angle );
}

THREE::Object3D* Object3D::translateOnAxis(THREE::Vector3* axis, float distance) {
	// translate object by distance along axis in object space
	// axis is assumed to be normalized
	auto v1 = new Vector3();
	v1->copy( axis )->applyQuaternion( this->quaternion() );
	this->position()->add( v1->multiplyScalar( distance ) );
	return this;
}

THREE::Object3D* Object3D::translateX(float distance) {
	auto v1 = new Vector3( 1, 0, 0 );
	return this->translateOnAxis( v1, distance );
}

THREE::Object3D* Object3D::translateY(float distance) {
	auto v1 = new Vector3( 0, 1, 0 );
	return this->translateOnAxis( v1, distance );
}

THREE::Object3D* Object3D::translateZ(float distance) {
	auto v1 = new Vector3( 0, 0, 1 );
	return this->translateOnAxis( v1, distance );
}

THREE::Vector3* Object3D::localToWorld(THREE::Vector3* vector ) {
	return vector->applyMatrix4( this->matrixWorld );
}

THREE::Vector3* Object3D::worldToLocal(THREE::Vector3* vector) {
	auto m1 = new Matrix4();
	return vector->applyMatrix4( m1->getInverse( this->matrixWorld ) );
}

void Object3D::lookAt(THREE::Vector3* vector) {
	// This routine does not support objects with rotated and/or translated parent(s)
	auto m1 = new Matrix4();
//	if ( this->isCamera ) {
//		m1->lookAt( this->position(), vector, this->up );
//	} else {
		m1->lookAt( vector, this->position(), this->up );
//	}
	this->quaternion()->setFromRotationMatrix( m1 );
}

THREE::Object3D* Object3D::add(THREE::Object3D* object ) {
//	if ( arguments.length > 1 ) {
//		for ( int i = 0; i < arguments.length; i ++ ) {
//			this->add( arguments[ i ] );
//		}

//		return this;
//	}

	if ( object == this ) {
		//console.error( "THREE.Object3D.add: object can't be added as a child of itself.", object );
		return this;
	}

	if ( ( object && object->isObject3D ) ) {
		if ( object->parent != nullptr ) {
			object->parent->remove( object );
		}

		object->parent = this;
		object->dispatchEvent( Event("added") );

		this->children.push_back( object );
	} else {
		//console.error( "THREE.Object3D.add: object not an instance of THREE.Object3D.", object );
	}
	return this;
}

void Object3D::remove(THREE::Object3D* object ) {
//	if ( arguments.length > 1 ) {
//		for ( int i = 0; i < arguments.length; i ++ ) {
//			this->remove( arguments[ i ] );
//		}
//	}

	auto iter = std::find_if(
		this->children.begin(),
		this->children.end(),
		[object](THREE::Object3D* other) { return object == other; }
	);
	int index = std::distance(this->children.begin(), iter);
	if (index != this->children.size()) {
		object->parent = nullptr;

		object->dispatchEvent( Event("removed") );

		this->children.erase(this->children.begin() + index);
	}
}
/*
THREE::Object3D* Object3D::getObjectById(int id ) {
	return this->getObjectByProperty( "id", id );
}

THREE::Object3D* Object3D::getObjectByName(std::string name ) {
	return this->getObjectByProperty( "name", name );
}

THREE::Object3D* Object3D::getObjectByProperty(std::string name, std::string value ) {
	if ( this[ name ] == value ) return this;

	for ( auto i = 0, l = this->children.length; i < l; i ++ ) {
		auto child = this->children[ i ];
		auto object = child.getObjectByProperty( name, value );

		if ( object != nullptr ) {
			return object;
		}
	}

	return nullptr;
}
*/
THREE::Vector3* Object3D::getWorldPosition(THREE::Vector3* optionalTarget ) {
	THREE::Vector3* result = (optionalTarget ? optionalTarget : new Vector3());

	this->updateMatrixWorld( true );

	return result->setFromMatrixPosition( this->matrixWorld );
}

THREE::Quaternion* Object3D::getWorldQuaternion(THREE::Quaternion* optionalTarget) {
	auto position = new Vector3();
	auto scale = new Vector3();

	auto result = (optionalTarget ? optionalTarget : new Quaternion());

	this->updateMatrixWorld( true );

	this->matrixWorld->decompose( position, result, scale );

	return result;
}

THREE::Euler* Object3D::getWorldRotation(THREE::Euler* optionalTarget) {
	auto quaternion = new Quaternion();

	auto result = (optionalTarget ? optionalTarget : new Euler());

	this->getWorldQuaternion( quaternion );

	return result->setFromQuaternion( quaternion, this->rotation()->order(), false );
}

THREE::Vector3* Object3D::getWorldScale(THREE::Vector3* optionalTarget) {
	auto position = new Vector3();
	auto quaternion = new Quaternion();

	auto result = (optionalTarget ? optionalTarget : new Vector3());

	this->updateMatrixWorld( true );

	this->matrixWorld->decompose( position, quaternion, result );

	return result;
}

THREE::Vector3* Object3D::getWorldDirection(THREE::Vector3* optionalTarget) {
	auto quaternion = new Quaternion();

	auto result = (optionalTarget ? optionalTarget : new Vector3());

	this->getWorldQuaternion( quaternion );

	return result->set( 0, 0, 1 )->applyQuaternion( quaternion );
}

void Object3D::raycast() {

}
/*
void Object3D::traverse( callback ) {
	callback( this );

	auto children = this->children;

	for ( auto i = 0, l = children.length; i < l; i ++ ) {
		children[ i ].traverse( callback );
	}
}

void Object3D::traverseVisible( callback ) {
	if ( this->visible == false ) return;

	callback( this );

	auto children = this->children;

	for ( auto i = 0, l = children.length; i < l; i ++ ) {
		children[ i ].traverseVisible( callback );
	}
}

void Object3D::traverseAncestors( callback ) {
	auto parent = this->parent;

	if ( parent != nullptr ) {
		callback( parent );

		parent.traverseAncestors( callback );
	}
}
*/
void Object3D::updateMatrix() {
	this->matrix->compose( this->position(), this->quaternion(), this->scale() );

	this->matrixWorldNeedsUpdate = true;
}

void Object3D::updateMatrixWorld(bool force ) {
	if ( this->matrixAutoUpdate ) this->updateMatrix();

	if ( this->matrixWorldNeedsUpdate || force ) {
		if ( this->parent == nullptr ) {
			this->matrixWorld->copy( this->matrix );
		} else {
			this->matrixWorld->multiplyMatrices( this->parent->matrixWorld, this->matrix );
		}

		this->matrixWorldNeedsUpdate = false;

		force = true;
	}

	// update children
	auto children = this->children;

	for (int i=0; i<children.size(); ++i) {
		children[ i ]->updateMatrixWorld( force );
	}
}
/*
Object3D::toJSON( meta ) {
	// meta is '' when called from JSON.stringify
	auto isRootObject = ( meta == nullptr || meta == '' );

	auto output = {};

	// meta is a hash used to collect geometries, materials.
	// not providing it implies that this is the root object
	// being serialized.
	if ( isRootObject ) {
		// initialize meta obj
		meta = {
			geometries: {},
			materials: {},
			textures: {},
			images: {}
		};

		output.metadata = {
			version: 4.5,
			type: 'Object',
			generator: 'Object3D.toJSON'
		};
	}

	// standard Object3D serialization

	auto object = {};

	object.uuid = this->uuid;
	object.type = this->type;

	if ( this->name != '' ) object.name = this->name;
	if ( JSON.stringify( this->userData ) != '{}' ) object.userData = this->userData;
	if ( this->castShadow == true ) object.castShadow = true;
	if ( this->receiveShadow == true ) object.receiveShadow = true;
	if ( this->visible == false ) object.visible = false;

	object.matrix = this->matrix.toArray();

	//

	function serialize( library, element ) {
		if ( library[ element.uuid ] == nullptr ) {
			library[ element.uuid ] = element.toJSON( meta );
		}

		return element.uuid;
	}

	if ( this->geometry != nullptr ) {
		object.geometry = serialize( meta.geometries, this->geometry );
	}

	if ( this->material != nullptr ) {
		if ( Array.isArray( this->material ) ) {
			auto uuids = [];

			for ( auto i = 0, l = this->material.length; i < l; i ++ ) {
				uuids.push( serialize( meta.materials, this->material[ i ] ) );
			}

			object.material = uuids;
		} else {
			object.material = serialize( meta.materials, this->material );
		}
	}

	//
	if ( this->children.length > 0 ) {
		object.children = [];

		for ( auto i = 0; i < this->children.length; i ++ ) {
			object.children.push( this->children[ i ].toJSON( meta ).object );
		}
	}

	if ( isRootObject ) {
		auto geometries = extractFromCache( meta.geometries );
		auto materials = extractFromCache( meta.materials );
		auto textures = extractFromCache( meta.textures );
		auto images = extractFromCache( meta.images );

		if ( geometries.length > 0 ) output.geometries = geometries;
		if ( materials.length > 0 ) output.materials = materials;
		if ( textures.length > 0 ) output.textures = textures;
		if ( images.length > 0 ) output.images = images;
	}

	output.object = object;

	return output;

	// extract data from the cache hash
	// remove metadata on each item
	// and return as array
	function extractFromCache( cache ) {
		auto values = [];
		for ( auto key in cache ) {
			auto data = cache[ key ];
			delete data.metadata;
			values.push( data );
		}
		return values;
	}
}
*/
THREE::Object3D* Object3D::clone() {
	return (new Object3D())->copy( this, false );
}

THREE::Object3D* Object3D::clone(bool recursive ) {
	return (new Object3D())->copy( this, recursive );
}

THREE::Object3D* Object3D::copy(THREE::Object3D* source) {
	return copy(source, true);
}

THREE::Object3D* Object3D::copy(THREE::Object3D* source, bool recursive ) {
	this->name = source->name;

	this->up->copy( source->up );

	this->position()->copy( source->position() );
	this->quaternion()->copy( source->quaternion() );
	this->scale()->copy( source->scale() );

	this->matrix->copy( source->matrix );
	this->matrixWorld->copy( source->matrixWorld );

	this->matrixAutoUpdate = source->matrixAutoUpdate;
	this->matrixWorldNeedsUpdate = source->matrixWorldNeedsUpdate;

	//this->layers.mask = source.layers.mask;
	this->visible = source->visible;

	this->castShadow = source->castShadow;
	this->receiveShadow = source->receiveShadow;

	this->frustumCulled = source->frustumCulled;
	this->renderOrder = source->renderOrder;

	//this->userData = JSON.parse( JSON.stringify( source.userData ) );

	if (recursive == true) {
		for (int i=0; i < source->children.size(); ++i) {
			auto child = source->children[ i ];
			this->add( child->clone() );
		}
	}

	return this;
}

};
