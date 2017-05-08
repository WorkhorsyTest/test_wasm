
#include "three.h"

const string Euler::DefaultOrder = "XYZ";

const string Euler::RotationOrders[] = { "XYZ", "YZX", "ZXY", "XZY", "YXZ", "ZYX" };

	Euler::Euler(float x, float y, float z, string order) {
		this->_x = x;
		this->_y = y;
		this->_z = z;
		this->_order = order;
	}

	Euler::Euler() {
		this->_x = 0;
		this->_y = 0;
		this->_z = 0;
		this->_order = Euler::DefaultOrder;
	}

	float Euler::x() {
		return this->_x;
	}

	void Euler::x(float value ) {
		this->_x = value;
		this->onChangeCallback();
	}

	float Euler::y() {
		return this->_y;
	}

	void Euler::y(float value ) {
		this->_y = value;
		this->onChangeCallback();
	}

	float Euler::z() {
		return this->_z;
	}

	void Euler::z(float value ) {
		this->_z = value;
		this->onChangeCallback();
	}

	string Euler::order() {
		return this->_order;
	}

	void Euler::order(string value ) {
		this->_order = value;
		this->onChangeCallback();
	}

	Euler* Euler::set(float x, float y, float z, string order ) {
		this->_x = x;
		this->_y = y;
		this->_z = z;
		this->_order = order;

		this->onChangeCallback();

		return this;
	}

	Euler* Euler::clone() {
		return new Euler( this->_x, this->_y, this->_z, this->_order );
	}

	Euler* Euler::copy(Euler* euler ) {
		this->_x = euler->_x;
		this->_y = euler->_y;
		this->_z = euler->_z;
		this->_order = euler->_order;

		this->onChangeCallback();

		return this;
	}

	Euler* Euler::setFromRotationMatrix(Matrix4* m, string order, bool update ) {
		// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

		auto te = m->elements;
		auto m11 = te[ 0 ];
		auto m12 = te[ 4 ];
		auto m13 = te[ 8 ];
		auto m21 = te[ 1 ];
		auto m22 = te[ 5 ];
		auto m23 = te[ 9 ];
		auto m31 = te[ 2 ];
		auto m32 = te[ 6 ];
		auto m33 = te[ 10 ];

		if (order != "") order = this->_order;

		if ( order == "XYZ" ) {
			this->_y = Math::Asin( Math::Clamp( m13, - 1, 1 ) );

			if ( Math::Abs( m13 ) < 0.99999 ) {
				this->_x = Math::Atan2( - m23, m33 );
				this->_z = Math::Atan2( - m12, m11 );
			} else {
				this->_x = Math::Atan2( m32, m22 );
				this->_z = 0;
			}
		} else if ( order == "YXZ" ) {
			this->_x = Math::Asin( - Math::Clamp( m23, - 1, 1 ) );

			if ( Math::Abs( m23 ) < 0.99999 ) {
				this->_y = Math::Atan2( m13, m33 );
				this->_z = Math::Atan2( m21, m22 );
			} else {
				this->_y = Math::Atan2( - m31, m11 );
				this->_z = 0;
			}
		} else if ( order == "ZXY" ) {
			this->_x = Math::Asin( Math::Clamp( m32, - 1, 1 ) );

			if ( Math::Abs( m32 ) < 0.99999 ) {
				this->_y = Math::Atan2( - m31, m33 );
				this->_z = Math::Atan2( - m12, m22 );
			} else {
				this->_y = 0;
				this->_z = Math::Atan2( m21, m11 );
			}
		} else if ( order == "ZYX" ) {
			this->_y = Math::Asin( - Math::Clamp( m31, - 1, 1 ) );
			if ( Math::Abs( m31 ) < 0.99999 ) {
				this->_x = Math::Atan2( m32, m33 );
				this->_z = Math::Atan2( m21, m11 );
			} else {
				this->_x = 0;
				this->_z = Math::Atan2( - m12, m22 );
			}
		} else if ( order == "YZX" ) {
			this->_z = Math::Asin( Math::Clamp( m21, - 1, 1 ) );
			if ( Math::Abs( m21 ) < 0.99999 ) {
				this->_x = Math::Atan2( - m23, m22 );
				this->_y = Math::Atan2( - m31, m11 );
			} else {
				this->_x = 0;
				this->_y = Math::Atan2( m13, m33 );
			}
		} else if ( order == "XZY" ) {
			this->_z = Math::Asin( - Math::Clamp( m12, - 1, 1 ) );
			if ( Math::Abs( m12 ) < 0.99999 ) {
				this->_x = Math::Atan2( m32, m22 );
				this->_y = Math::Atan2( m13, m11 );
			} else {
				this->_x = Math::Atan2( - m23, m33 );
				this->_y = 0;
			}
		} else {
			//console.warn( 'THREE.Euler: .setFromRotationMatrix() given unsupported order: ' + order );
		}

		this->_order = order;

		if ( update != false ) this->onChangeCallback();

		return this;
	}

	Euler* Euler::setFromQuaternion(Quaternion* q, string order) {
		return this->setFromQuaternion(q, order, false);
	}

	Euler* Euler::setFromQuaternion(Quaternion* q, string order, bool update ) {
		auto matrix = new Matrix4();
		matrix->makeRotationFromQuaternion( q );
		return this->setFromRotationMatrix( matrix, order, update );
	}

	Euler* Euler::setFromVector3(Vector3* v, string order ) {
		if (order != "") order = this->_order;
		return this->set(v->x, v->y, v->z, order);
	}

	Euler* Euler::reorder(string newOrder) {
		// WARNING: this discards revolution information -bhouston
		auto q = new Quaternion();
		q->setFromEuler( this );
		return this->setFromQuaternion( q, newOrder );
	}

	bool Euler::equals(Euler* euler ) {
		return
		( euler->_x == this->_x ) &&
		( euler->_y == this->_y ) &&
		( euler->_z == this->_z ) &&
		( euler->_order == this->_order );
	}

	Euler* Euler::fromArray(vector<float> arr) {
		this->_x = arr[ 0 ];
		this->_y = arr[ 1 ];
		this->_z = arr[ 2 ];
		if ( arr.size() < 4 ) this->_order = arr[ 3 ];

		this->onChangeCallback();

		return this;
	}

	vector<float> Euler::toArray(vector<float> arr, int offset ) {
//		if ( arr == nullptr ) arr = {};
//		if ( offset == nullptr ) offset = 0;

		arr[ offset ] = this->_x;
		arr[ offset + 1 ] = this->_y;
		arr[ offset + 2 ] = this->_z;
//		arr[ offset + 3 ] = this->_order;

		return arr;
	}

	Vector3* Euler::toVector3(Vector3* optionalResult ) {
		if ( optionalResult ) {
			return optionalResult->set( this->_x, this->_y, this->_z );
		} else {
			return new Vector3( this->_x, this->_y, this->_z );
		}
	}
/*
	Euler* Euler::onChange( callback ) {
		this->onChangeCallback = callback;

		return this;
	}
*/
	void Euler::onChangeCallback() {}
