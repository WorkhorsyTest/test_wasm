

#include "three.h"

Matrix4::Matrix4() {
	this->elements = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	//if ( arguments.length > 0) {
	//	console.error( 'THREE.Matrix4: the constructor no longer reads arguments. use .set() instead.' );
	//}
}

Matrix4* Matrix4::set(float n11, float n12, float n13, float n14, float n21, float n22, float n23, float n24, float n31, float n32, float n33, float n34, float n41, float n42, float n43, float n44) {
	auto te = this->elements;

	te[ 0 ] = n11; te[ 4 ] = n12; te[ 8 ] = n13; te[ 12 ] = n14;
	te[ 1 ] = n21; te[ 5 ] = n22; te[ 9 ] = n23; te[ 13 ] = n24;
	te[ 2 ] = n31; te[ 6 ] = n32; te[ 10 ] = n33; te[ 14 ] = n34;
	te[ 3 ] = n41; te[ 7 ] = n42; te[ 11 ] = n43; te[ 15 ] = n44;

	return this;
}

Matrix4* Matrix4::identity() {
	this->set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	return this;
}

Matrix4* Matrix4::clone() {
	return (new Matrix4())->fromArray( this->elements );
}

Matrix4* Matrix4::copy(Matrix4*  m) {
	auto te = this->elements;
	auto me = m->elements;

	te[ 0 ] = me[ 0 ]; te[ 1 ] = me[ 1 ]; te[ 2 ] = me[ 2 ]; te[ 3 ] = me[ 3 ];
	te[ 4 ] = me[ 4 ]; te[ 5 ] = me[ 5 ]; te[ 6 ] = me[ 6 ]; te[ 7 ] = me[ 7 ];
	te[ 8 ] = me[ 8 ]; te[ 9 ] = me[ 9 ]; te[ 10 ] = me[ 10 ]; te[ 11 ] = me[ 11 ];
	te[ 12 ] = me[ 12 ]; te[ 13 ] = me[ 13 ]; te[ 14 ] = me[ 14 ]; te[ 15 ] = me[ 15 ];

	return this;
}

Matrix4* Matrix4::copyPosition(Matrix4*  m) {
	auto te = this->elements;
	auto me = m->elements;

	te[ 12 ] = me[ 12 ];
	te[ 13 ] = me[ 13 ];
	te[ 14 ] = me[ 14 ];

	return this;
}

Matrix4* Matrix4::extractBasis(Vector3* xAxis, Vector3* yAxis, Vector3* zAxis) {
	xAxis->setFromMatrixColumn( this, 0 );
	yAxis->setFromMatrixColumn( this, 1 );
	zAxis->setFromMatrixColumn( this, 2 );

	return this;
}

Matrix4* Matrix4::makeBasis(Vector3* xAxis, Vector3* yAxis, Vector3* zAxis) {
	this->set(
		xAxis->x, yAxis->x, zAxis->x, 0,
		xAxis->y, yAxis->y, zAxis->y, 0,
		xAxis->z, yAxis->z, zAxis->z, 0,
		0,       0,       0,       1
	);

	return this;
}

Matrix4* Matrix4::extractRotation(Matrix4* m) {
	auto v1 = new Vector3();

	auto te = this->elements;
	auto me = m->elements;

	auto scaleX = 1 / v1->setFromMatrixColumn( m, 0 )->length();
	auto scaleY = 1 / v1->setFromMatrixColumn( m, 1 )->length();
	auto scaleZ = 1 / v1->setFromMatrixColumn( m, 2 )->length();

	te[ 0 ] = me[ 0 ] * scaleX;
	te[ 1 ] = me[ 1 ] * scaleX;
	te[ 2 ] = me[ 2 ] * scaleX;

	te[ 4 ] = me[ 4 ] * scaleY;
	te[ 5 ] = me[ 5 ] * scaleY;
	te[ 6 ] = me[ 6 ] * scaleY;

	te[ 8 ] = me[ 8 ] * scaleZ;
	te[ 9 ] = me[ 9 ] * scaleZ;
	te[ 10 ] = me[ 10 ] * scaleZ;

	return this;
}

Matrix4* Matrix4::makeRotationFromEuler(Euler* euler) {
	auto te = this->elements;

	auto x = euler->x();
	auto y = euler->y();
	auto z = euler->z();
	auto a = Math::Cos( x );
	auto b = Math::Sin( x );
	auto c = Math::Cos( y );
	auto d = Math::Sin( y );
	auto e = Math::Cos( z );
	auto f = Math::Sin( z );

	if ( euler->order() == "XYZ") {
		auto ae = a * e, af = a * f, be = b * e, bf = b * f;

		te[ 0 ] = c * e;
		te[ 4 ] = - c * f;
		te[ 8 ] = d;

		te[ 1 ] = af + be * d;
		te[ 5 ] = ae - bf * d;
		te[ 9 ] = - b * c;

		te[ 2 ] = bf - ae * d;
		te[ 6 ] = be + af * d;
		te[ 10 ] = a * c;
	} else if ( euler->order() == "YXZ") {
		auto ce = c * e, cf = c * f, de = d * e, df = d * f;

		te[ 0 ] = ce + df * b;
		te[ 4 ] = de * b - cf;
		te[ 8 ] = a * d;

		te[ 1 ] = a * f;
		te[ 5 ] = a * e;
		te[ 9 ] = - b;

		te[ 2 ] = cf * b - de;
		te[ 6 ] = df + ce * b;
		te[ 10 ] = a * c;
	} else if ( euler->order() == "ZXY") {
		auto ce = c * e, cf = c * f, de = d * e, df = d * f;

		te[ 0 ] = ce - df * b;
		te[ 4 ] = - a * f;
		te[ 8 ] = de + cf * b;

		te[ 1 ] = cf + de * b;
		te[ 5 ] = a * e;
		te[ 9 ] = df - ce * b;

		te[ 2 ] = - a * d;
		te[ 6 ] = b;
		te[ 10 ] = a * c;
	} else if ( euler->order() == "ZYX") {
		auto ae = a * e, af = a * f, be = b * e, bf = b * f;

		te[ 0 ] = c * e;
		te[ 4 ] = be * d - af;
		te[ 8 ] = ae * d + bf;

		te[ 1 ] = c * f;
		te[ 5 ] = bf * d + ae;
		te[ 9 ] = af * d - be;

		te[ 2 ] = - d;
		te[ 6 ] = b * c;
		te[ 10 ] = a * c;
	} else if ( euler->order() == "YZX") {
		auto ac = a * c, ad = a * d, bc = b * c, bd = b * d;

		te[ 0 ] = c * e;
		te[ 4 ] = bd - ac * f;
		te[ 8 ] = bc * f + ad;

		te[ 1 ] = f;
		te[ 5 ] = a * e;
		te[ 9 ] = - b * e;

		te[ 2 ] = - d * e;
		te[ 6 ] = ad * f + bc;
		te[ 10 ] = ac - bd * f;
	} else if ( euler->order() == "XZY") {
		auto ac = a * c, ad = a * d, bc = b * c, bd = b * d;

		te[ 0 ] = c * e;
		te[ 4 ] = - f;
		te[ 8 ] = d * e;

		te[ 1 ] = ac * f + bd;
		te[ 5 ] = a * e;
		te[ 9 ] = ad * f - bc;

		te[ 2 ] = bc * f - ad;
		te[ 6 ] = b * e;
		te[ 10 ] = bd * f + ac;
	}

	// last column
	te[ 3 ] = 0;
	te[ 7 ] = 0;
	te[ 11 ] = 0;

	// bottom row
	te[ 12 ] = 0;
	te[ 13 ] = 0;
	te[ 14 ] = 0;
	te[ 15 ] = 1;

	return this;
}

Matrix4* Matrix4::makeRotationFromQuaternion(Quaternion* q) {
	auto te = this->elements;

	auto x = q->_x; auto y = q->_y; auto z = q->_z; auto w = q->_w;
	auto x2 = x + x; auto y2 = y + y; auto z2 = z + z;
	auto xx = x * x2; auto xy = x * y2; auto xz = x * z2;
	auto yy = y * y2; auto yz = y * z2; auto zz = z * z2;
	auto wx = w * x2; auto wy = w * y2; auto wz = w * z2;

	te[ 0 ] = 1 - ( yy + zz );
	te[ 4 ] = xy - wz;
	te[ 8 ] = xz + wy;

	te[ 1 ] = xy + wz;
	te[ 5 ] = 1 - ( xx + zz );
	te[ 9 ] = yz - wx;

	te[ 2 ] = xz - wy;
	te[ 6 ] = yz + wx;
	te[ 10 ] = 1 - ( xx + yy );

	// last column
	te[ 3 ] = 0;
	te[ 7 ] = 0;
	te[ 11 ] = 0;

	// bottom row
	te[ 12 ] = 0;
	te[ 13 ] = 0;
	te[ 14 ] = 0;
	te[ 15 ] = 1;

	return this;
}

Matrix4* Matrix4::lookAt(Vector3* eye, Vector3* target, Vector3* up) {
	auto x = new Vector3();
	auto y = new Vector3();
	auto z = new Vector3();

	auto te = this->elements;

	z->subVectors( eye, target );

	if ( z->lengthSq() == 0) {
		// eye and target are in the same position

		z->z = 1;
	}

	z->normalize();
	x->crossVectors( up, z );

	if ( x->lengthSq() == 0) {
		// eye and target are in the same vertical

		z->z += 0.0001;
		x->crossVectors( up, z );
	}

	x->normalize();
	y->crossVectors( z, x );

	te[ 0 ] = x->x; te[ 4 ] = y->x; te[ 8 ] = z->x;
	te[ 1 ] = x->y; te[ 5 ] = y->y; te[ 9 ] = z->y;
	te[ 2 ] = x->z; te[ 6 ] = y->z; te[ 10 ] = z->z;

	return this;
}

Matrix4* Matrix4::multiply(Matrix4* m, Matrix4* n) {
	if ( n != nullptr) {
		//console.warn( 'THREE.Matrix4: .multiply() now only accepts one argument. Use .multiplyMatrices( a, b ) instead.' );
		return this->multiplyMatrices( m, n );
	}

	return this->multiplyMatrices( this, m );
}

Matrix4* Matrix4::premultiply(Matrix4* m) {
	return this->multiplyMatrices( m, this );
}

Matrix4* Matrix4::multiplyMatrices(Matrix4* a, Matrix4* b) {
	auto ae = a->elements;
	auto be = b->elements;
	auto te = this->elements;

	auto a11 = ae[ 0 ], a12 = ae[ 4 ], a13 = ae[ 8 ], a14 = ae[ 12 ];
	auto a21 = ae[ 1 ], a22 = ae[ 5 ], a23 = ae[ 9 ], a24 = ae[ 13 ];
	auto a31 = ae[ 2 ], a32 = ae[ 6 ], a33 = ae[ 10 ], a34 = ae[ 14 ];
	auto a41 = ae[ 3 ], a42 = ae[ 7 ], a43 = ae[ 11 ], a44 = ae[ 15 ];

	auto b11 = be[ 0 ], b12 = be[ 4 ], b13 = be[ 8 ], b14 = be[ 12 ];
	auto b21 = be[ 1 ], b22 = be[ 5 ], b23 = be[ 9 ], b24 = be[ 13 ];
	auto b31 = be[ 2 ], b32 = be[ 6 ], b33 = be[ 10 ], b34 = be[ 14 ];
	auto b41 = be[ 3 ], b42 = be[ 7 ], b43 = be[ 11 ], b44 = be[ 15 ];

	te[ 0 ] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
	te[ 4 ] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
	te[ 8 ] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
	te[ 12 ] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

	te[ 1 ] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
	te[ 5 ] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
	te[ 9 ] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
	te[ 13 ] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

	te[ 2 ] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
	te[ 6 ] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
	te[ 10 ] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
	te[ 14 ] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

	te[ 3 ] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
	te[ 7 ] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
	te[ 11 ] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
	te[ 15 ] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

	return this;
}

Matrix4* Matrix4::multiplyScalar(float s) {
	auto te = this->elements;

	te[ 0 ] *= s; te[ 4 ] *= s; te[ 8 ] *= s; te[ 12 ] *= s;
	te[ 1 ] *= s; te[ 5 ] *= s; te[ 9 ] *= s; te[ 13 ] *= s;
	te[ 2 ] *= s; te[ 6 ] *= s; te[ 10 ] *= s; te[ 14 ] *= s;
	te[ 3 ] *= s; te[ 7 ] *= s; te[ 11 ] *= s; te[ 15 ] *= s;

	return this;
}
/*
BufferAttribute* Matrix4::applyToBufferAttribute(BufferAttribute* attribute) {
	auto v1 = new Vector3();

	for ( auto i = 0, l = attribute.count; i < l; i ++) {
		v1.x = attribute.getX( i );
		v1.y = attribute.getY( i );
		v1.z = attribute.getZ( i );

		v1.applyMatrix4( this );

		attribute.setXYZ( i, v1.x, v1.y, v1.z );
	}
	return attribute;
}
*/
float Matrix4::determinant() {
	auto te = this->elements;

	auto n11 = te[ 0 ], n12 = te[ 4 ], n13 = te[ 8 ], n14 = te[ 12 ];
	auto n21 = te[ 1 ], n22 = te[ 5 ], n23 = te[ 9 ], n24 = te[ 13 ];
	auto n31 = te[ 2 ], n32 = te[ 6 ], n33 = te[ 10 ], n34 = te[ 14 ];
	auto n41 = te[ 3 ], n42 = te[ 7 ], n43 = te[ 11 ], n44 = te[ 15 ];

	//TODO: make this more efficient
	//( based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm )

	return (
		n41 * (
			+ n14 * n23 * n32
			 - n13 * n24 * n32
			 - n14 * n22 * n33
			 + n12 * n24 * n33
			 + n13 * n22 * n34
			 - n12 * n23 * n34
		) +
		n42 * (
			+ n11 * n23 * n34
			 - n11 * n24 * n33
			 + n14 * n21 * n33
			 - n13 * n21 * n34
			 + n13 * n24 * n31
			 - n14 * n23 * n31
		) +
		n43 * (
			+ n11 * n24 * n32
			 - n11 * n22 * n34
			 - n14 * n21 * n32
			 + n12 * n21 * n34
			 + n14 * n22 * n31
			 - n12 * n24 * n31
		) +
		n44 * (
			- n13 * n22 * n31
			 - n11 * n23 * n32
			 + n11 * n22 * n33
			 + n13 * n21 * n32
			 - n12 * n21 * n33
			 + n12 * n23 * n31
		)
	);
}

Matrix4* Matrix4::transpose() {
	auto te = this->elements;
	float tmp = 0;

	tmp = te[ 1 ]; te[ 1 ] = te[ 4 ]; te[ 4 ] = tmp;
	tmp = te[ 2 ]; te[ 2 ] = te[ 8 ]; te[ 8 ] = tmp;
	tmp = te[ 6 ]; te[ 6 ] = te[ 9 ]; te[ 9 ] = tmp;

	tmp = te[ 3 ]; te[ 3 ] = te[ 12 ]; te[ 12 ] = tmp;
	tmp = te[ 7 ]; te[ 7 ] = te[ 13 ]; te[ 13 ] = tmp;
	tmp = te[ 11 ]; te[ 11 ] = te[ 14 ]; te[ 14 ] = tmp;

	return this;
}

Matrix4* Matrix4::setPosition(Vector3* v) {
	auto te = this->elements;

	te[ 12 ] = v->x;
	te[ 13 ] = v->y;
	te[ 14 ] = v->z;

	return this;
}

Matrix4* Matrix4::getInverse(Matrix4* m) {
	return this->getInverse(m, false);
}

Matrix4* Matrix4::getInverse(Matrix4* m, bool throwOnDegenerate) {
	// based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
	auto te = this->elements;
	auto me = m->elements;

	auto n11 = me[ 0 ]; auto n21 = me[ 1 ]; auto n31 = me[ 2 ]; auto n41 = me[ 3 ];
	auto n12 = me[ 4 ]; auto n22 = me[ 5 ]; auto n32 = me[ 6 ]; auto n42 = me[ 7 ];
	auto n13 = me[ 8 ]; auto n23 = me[ 9 ]; auto n33 = me[ 10 ]; auto n43 = me[ 11 ];
	auto n14 = me[ 12 ]; auto n24 = me[ 13 ]; auto n34 = me[ 14 ]; auto n44 = me[ 15 ];

	auto t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
	auto t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
	auto t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
	auto t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

	auto det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

	if ( det == 0) {
		if ( throwOnDegenerate == true) {
			throw "THREE.Matrix4.getInverse(): can't invert matrix, determinant is 0";
		} else {
			//console.warn( msg );
		}

		return this->identity();
	}

	auto detInv = 1 / det;

	te[ 0 ] = t11 * detInv;
	te[ 1 ] = ( n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44 ) * detInv;
	te[ 2 ] = ( n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44 ) * detInv;
	te[ 3 ] = ( n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43 ) * detInv;

	te[ 4 ] = t12 * detInv;
	te[ 5 ] = ( n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44 ) * detInv;
	te[ 6 ] = ( n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44 ) * detInv;
	te[ 7 ] = ( n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43 ) * detInv;

	te[ 8 ] = t13 * detInv;
	te[ 9 ] = ( n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44 ) * detInv;
	te[ 10 ] = ( n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44 ) * detInv;
	te[ 11 ] = ( n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43 ) * detInv;

	te[ 12 ] = t14 * detInv;
	te[ 13 ] = ( n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34 ) * detInv;
	te[ 14 ] = ( n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34 ) * detInv;
	te[ 15 ] = ( n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33 ) * detInv;

	return this;
}

Matrix4* Matrix4::scale(Vector3* v) {
	auto te = this->elements;
	auto x = v->x;
	auto y = v->y;
	auto z = v->z;

	te[ 0 ] *= x; te[ 4 ] *= y; te[ 8 ] *= z;
	te[ 1 ] *= x; te[ 5 ] *= y; te[ 9 ] *= z;
	te[ 2 ] *= x; te[ 6 ] *= y; te[ 10 ] *= z;
	te[ 3 ] *= x; te[ 7 ] *= y; te[ 11 ] *= z;

	return this;
}

float Matrix4::getMaxScaleOnAxis() {
	auto te = this->elements;

	auto scaleXSq = te[ 0 ] * te[ 0 ] + te[ 1 ] * te[ 1 ] + te[ 2 ] * te[ 2 ];
	auto scaleYSq = te[ 4 ] * te[ 4 ] + te[ 5 ] * te[ 5 ] + te[ 6 ] * te[ 6 ];
	auto scaleZSq = te[ 8 ] * te[ 8 ] + te[ 9 ] * te[ 9 ] + te[ 10 ] * te[ 10 ];

	return Math::Sqrt( Math::Max( scaleXSq, scaleYSq, scaleZSq ) );
}

Matrix4* Matrix4::makeTranslation(float x, float y, float z) {
	this->set(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	);

	return this;
}

Matrix4* Matrix4::makeRotationX(float theta) {
	auto c = Math::Cos( theta ), s = Math::Sin( theta );

	this->set(
		1, 0,  0, 0,
		0, c, - s, 0,
		0, s,  c, 0,
		0, 0,  0, 1
	);

	return this;
}

Matrix4* Matrix4::makeRotationY(float theta) {
	auto c = Math::Cos( theta ), s = Math::Sin( theta );

	this->set(
		 c, 0, s, 0,
		 0, 1, 0, 0,
		- s, 0, c, 0,
		 0, 0, 0, 1
	);

	return this;
}

Matrix4* Matrix4::makeRotationZ(float theta) {
	auto c = Math::Cos( theta ), s = Math::Sin( theta );

	this->set(
		c, - s, 0, 0,
		s,  c, 0, 0,
		0,  0, 1, 0,
		0,  0, 0, 1
	);

	return this;
}

Matrix4* Matrix4::makeRotationAxis(Vector3* axis, float angle) {
	// Based on http://www.gamedev.net/reference/articles/article1199.asp
	auto c = Math::Cos( angle );
	auto s = Math::Sin( angle );
	auto t = 1 - c;
	auto x = axis->x;
	auto y = axis->y;
	auto z = axis->z;
	auto tx = t * x;
	auto ty = t * y;

	this->set(
		tx * x + c, tx * y - s * z, tx * z + s * y, 0,
		tx * y + s * z, ty * y + c, ty * z - s * x, 0,
		tx * z - s * y, ty * z + s * x, t * z * z + c, 0,
		0, 0, 0, 1
	);

	 return this;
}

Matrix4* Matrix4::makeScale(float x, float y, float z) {
	this->set(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	);

	return this;
}

Matrix4* Matrix4::makeShear(float x, float y, float z) {
	this->set(
		1, y, z, 0,
		x, 1, z, 0,
		x, y, 1, 0,
		0, 0, 0, 1
	);

	return this;
}

Matrix4* Matrix4::compose(Vector3* position, Quaternion* quaternion, Vector3* scale) {
	this->makeRotationFromQuaternion( quaternion );
	this->scale( scale );
	this->setPosition( position );

	return this;
}

Matrix4* Matrix4::decompose(Vector3* position, Quaternion* quaternion, Vector3* scale) {
	auto vector = new Vector3();
	auto matrix = new Matrix4();

	auto te = this->elements;

	auto sx = vector->set( te[ 0 ], te[ 1 ], te[ 2 ] )->length();
	auto sy = vector->set( te[ 4 ], te[ 5 ], te[ 6 ] )->length();
	auto sz = vector->set( te[ 8 ], te[ 9 ], te[ 10 ] )->length();

	// if determine is negative, we need to invert one scale
	auto det = this->determinant();
	if ( det < 0 ) sx = - sx;

	position->x = te[ 12 ];
	position->y = te[ 13 ];
	position->z = te[ 14 ];

	// scale the rotation part
	matrix->copy( this );

	auto invSX = 1 / sx;
	auto invSY = 1 / sy;
	auto invSZ = 1 / sz;

	matrix->elements[ 0 ] *= invSX;
	matrix->elements[ 1 ] *= invSX;
	matrix->elements[ 2 ] *= invSX;

	matrix->elements[ 4 ] *= invSY;
	matrix->elements[ 5 ] *= invSY;
	matrix->elements[ 6 ] *= invSY;

	matrix->elements[ 8 ] *= invSZ;
	matrix->elements[ 9 ] *= invSZ;
	matrix->elements[ 10 ] *= invSZ;

	quaternion->setFromRotationMatrix( matrix );

	scale->x = sx;
	scale->y = sy;
	scale->z = sz;

	return this;
}

Matrix4* Matrix4::makePerspective(float left, float right, float top, float bottom, float near, float far) {
	auto te = this->elements;
	auto x = 2 * near / ( right - left );
	auto y = 2 * near / ( top - bottom );

	auto a = ( right + left ) / ( right - left );
	auto b = ( top + bottom ) / ( top - bottom );
	auto c = - ( far + near ) / ( far - near );
	auto d = - 2 * far * near / ( far - near );

	te[ 0 ] = x;	te[ 4 ] = 0;	te[ 8 ] = a;	te[ 12 ] = 0;
	te[ 1 ] = 0;	te[ 5 ] = y;	te[ 9 ] = b;	te[ 13 ] = 0;
	te[ 2 ] = 0;	te[ 6 ] = 0;	te[ 10 ] = c;	te[ 14 ] = d;
	te[ 3 ] = 0;	te[ 7 ] = 0;	te[ 11 ] = - 1;	te[ 15 ] = 0;

	return this;
}

Matrix4* Matrix4::makeOrthographic(float left, float right, float top, float bottom, float near, float far) {
	auto te = this->elements;
	auto w = 1.0 / ( right - left );
	auto h = 1.0 / ( top - bottom );
	auto p = 1.0 / ( far - near );

	auto x = ( right + left ) * w;
	auto y = ( top + bottom ) * h;
	auto z = ( far + near ) * p;

	te[ 0 ] = 2 * w;	te[ 4 ] = 0;	te[ 8 ] = 0;	te[ 12 ] = - x;
	te[ 1 ] = 0;	te[ 5 ] = 2 * h;	te[ 9 ] = 0;	te[ 13 ] = - y;
	te[ 2 ] = 0;	te[ 6 ] = 0;	te[ 10 ] = - 2 * p;	te[ 14 ] = - z;
	te[ 3 ] = 0;	te[ 7 ] = 0;	te[ 11 ] = 0;	te[ 15 ] = 1;

	return this;
}

bool Matrix4::equals(Matrix4* matrix) {
	auto te = this->elements;
	auto me = matrix->elements;

	for ( int i = 0; i < 16; i ++) {
		if ( te[ i ] != me[ i ] ) return false;
	}

	return true;
}

Matrix4* Matrix4::fromArray(vector<float> &array) {
	return this->fromArray(array, 0);
}

Matrix4* Matrix4::fromArray(vector<float> &array, int offset) {
	for ( int i = 0; i < 16; i ++) {
		this->elements[ i ] = array[ i + offset ];
	}

	return this;
}

vector<float> Matrix4::toArray(vector<float> &array, int offset) {
	//if ( array == nullptr ) array = {};
	//if ( offset == nullptr ) offset = 0;

	auto te = this->elements;

	array[ offset ] = te[ 0 ];
	array[ offset + 1 ] = te[ 1 ];
	array[ offset + 2 ] = te[ 2 ];
	array[ offset + 3 ] = te[ 3 ];

	array[ offset + 4 ] = te[ 4 ];
	array[ offset + 5 ] = te[ 5 ];
	array[ offset + 6 ] = te[ 6 ];
	array[ offset + 7 ] = te[ 7 ];

	array[ offset + 8 ] = te[ 8 ];
	array[ offset + 9 ] = te[ 9 ];
	array[ offset + 10 ] = te[ 10 ];
	array[ offset + 11 ] = te[ 11 ];

	array[ offset + 12 ] = te[ 12 ];
	array[ offset + 13 ] = te[ 13 ];
	array[ offset + 14 ] = te[ 14 ];
	array[ offset + 15 ] = te[ 15 ];

	return array;
}
