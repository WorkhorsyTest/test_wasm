
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "three.h"

namespace THREE {

class Texture : public EventDispatcher {
public:
	static long textureId;
	static THREE::Image* DEFAULT_IMAGE;
	static int DEFAULT_MAPPING;
	bool _value;
	long id;
	std::string uuid;
	std::string name;
	THREE::Image* image;
	std::vector<int> mipmaps;
	int mapping;
	int wrapS;
	int wrapT;
	int magFilter;
	int minFilter;
	int anisotropy;
	int format;
	int type;
	THREE::Vector2* offset;
	THREE::Vector2* repeat;
	bool generateMipmaps;
	bool premultiplyAlpha;
	bool flipY;
	int unpackAlignment;
	int encoding;
	int version;
	//function onUpdate;

	Texture();

	Texture(THREE::Image* image, int mapping, int wrapS, int wrapT, int magFilter, int minFilter, int format, int type, int anisotropy, int encoding);

	void needsUpdate(bool value);

	THREE::Texture* clone();

	THREE::Texture* copy(THREE::Texture* source );

	//toJSON( meta );

	void dispose();

	void transformUv(THREE::Vector2* uv );
};

};

#endif // _TEXTURE_H_
