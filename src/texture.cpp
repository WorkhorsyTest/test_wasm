

#include "three.h"

long Texture::textureId = 0;
Image* Texture::DEFAULT_IMAGE = nullptr;
int Texture::DEFAULT_MAPPING = UVMapping;

Texture::Texture() :
	Texture(
		Texture::DEFAULT_IMAGE,
		Texture::DEFAULT_MAPPING,
		ClampToEdgeWrapping,
		ClampToEdgeWrapping,
		LinearFilter,
		LinearMipMapLinearFilter,
		RGBAFormat,
		UnsignedByteType,
		1,
		LinearEncoding) {
}

Texture::Texture(Image* image, int mapping, int wrapS, int wrapT, int magFilter, int minFilter, int format, int type, int anisotropy, int encoding)
: EventDispatcher() {
	this->id = textureId++;
	this->uuid = Math::generateUUID();
	this->name = "";

	this->image = (image ? image : Texture::DEFAULT_IMAGE);
	this->mipmaps = {};

	this->mapping = mapping; //Texture::DEFAULT_MAPPING;

	this->wrapS = wrapS; //ClampToEdgeWrapping;
	this->wrapT = wrapT; //ClampToEdgeWrapping;

	this->magFilter = magFilter; //LinearFilter;
	this->minFilter = minFilter; //LinearMipMapLinearFilter;

	this->anisotropy = anisotropy; //1;

	this->format = format; //RGBAFormat;
	this->type = type; //UnsignedByteType;

	this->offset = new Vector2( 0, 0 );
	this->repeat = new Vector2( 1, 1 );

	this->generateMipmaps = true;
	this->premultiplyAlpha = false;
	this->flipY = true;
	this->unpackAlignment = 4;	// valid values: 1, 2, 4, 8 (see http://www.khronos.org/opengles/sdk/docs/man/xhtml/glPixelStorei.xml)

	// Values of encoding != THREE.LinearEncoding only supported on map, envMap and emissiveMap.
	//
	// Also changing the encoding after already used by a Material will not automatically make the Material
	// update.  You need to explicitly call Material.needsUpdate to trigger it to recompile.
	this->encoding = encoding; //LinearEncoding;

	this->version = 0;
//	this->onUpdate = nullptr;
}

void Texture::needsUpdate(bool value) {
	this->_value = value;
	if (this->_value) {
		this->version ++;
	}
}

Texture* Texture::clone() {
	return (new Texture())->copy( this );
}

Texture* Texture::copy(Texture* source ) {
	this->name = source->name;

	this->image = source->image;
	this->mipmaps = std::vector<int>(source->mipmaps);

	this->mapping = source->mapping;

	this->wrapS = source->wrapS;
	this->wrapT = source->wrapT;

	this->magFilter = source->magFilter;
	this->minFilter = source->minFilter;

	this->anisotropy = source->anisotropy;

	this->format = source->format;
	this->type = source->type;

	this->offset->copy( source->offset );
	this->repeat->copy( source->repeat );

	this->generateMipmaps = source->generateMipmaps;
	this->premultiplyAlpha = source->premultiplyAlpha;
	this->flipY = source->flipY;
	this->unpackAlignment = source->unpackAlignment;
	this->encoding = source->encoding;

	return this;
}
/*
Texture::toJSON( meta ) {
	if ( meta.textures[ this->uuid ] != undefined ) {
		return meta.textures[ this->uuid ];
	}

	function getDataURL( image ) {
		var canvas;

		if ( image.toDataURL != undefined ) {
			canvas = image;
		} else {
			canvas = document.createElementNS( 'http://www.w3.org/1999/xhtml', 'canvas' );
			canvas.width = image.width;
			canvas.height = image.height;

			canvas.getContext( '2d' ).drawImage( image, 0, 0, image.width, image.height );
		}

		if ( canvas.width > 2048 || canvas.height > 2048 ) {
			return canvas.toDataURL( 'image/jpeg', 0.6 );
		} else {
			return canvas.toDataURL( 'image/png' );
		}
	}

	var output = {
		metadata: {
			version: 4.5,
			type: 'Texture',
			generator: 'Texture.toJSON'
		},

		uuid: this->uuid,
		name: this->name,

		mapping: this->mapping,

		repeat: [ this->repeat.x, this->repeat.y ],
		offset: [ this->offset.x, this->offset.y ],
		wrap: [ this->wrapS, this->wrapT ],

		minFilter: this->minFilter,
		magFilter: this->magFilter,
		anisotropy: this->anisotropy,

		flipY: this->flipY
	};

	if ( this->image != undefined ) {
		// TODO: Move to THREE.Image
		var image = this->image;

		if ( image.uuid == undefined ) {
			image.uuid = Math::generateUUID(); // UGH
		}

		if ( meta.images[ image.uuid ] == undefined ) {
			meta.images[ image.uuid ] = {
				uuid: image.uuid,
				url: getDataURL( image )
			};
		}

		output.image = image.uuid;
	}

	meta.textures[ this->uuid ] = output;

	return output;
}
*/
void Texture::dispose() {
		this->dispatchEvent( Event("dispose") );
}

void Texture::transformUv(Vector2* uv ) {
	if ( this->mapping != UVMapping ) return;

	uv->multiply( this->repeat );
	uv->add( this->offset );

	if ( uv->x < 0 || uv->x > 1 ) {
		switch ( this->wrapS ) {
			case RepeatWrapping:
				uv->x = uv->x - Math::Floor( uv->x );
				break;
			case ClampToEdgeWrapping:
				uv->x = uv->x < 0 ? 0 : 1;
				break;
			case MirroredRepeatWrapping:
				if ( Math::Abs( ((int)Math::Floor( uv->x )) % 2 ) == 1 ) {
					uv->x = Math::Ceil( uv->x ) - uv->x;
				} else {
					uv->x = uv->x - Math::Floor( uv->x );
				}
				break;
		}
	}

	if ( uv->y < 0 || uv->y > 1 ) {
		switch ( this->wrapT ) {
			case RepeatWrapping:
				uv->y = uv->y - Math::Floor( uv->y );
				break;
			case ClampToEdgeWrapping:
				uv->y = uv->y < 0 ? 0 : 1;
				break;
			case MirroredRepeatWrapping:
				if ( Math::Abs( ((int)Math::Floor( uv->y )) % 2 ) == 1 ) {
					uv->y = Math::Ceil( uv->y ) - uv->y;
				} else {
					uv->y = uv->y - Math::Floor( uv->y );
				}
				break;
		}
	}

	if ( this->flipY ) {
		uv->y = 1 - uv->y;
	}
}
