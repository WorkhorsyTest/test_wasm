
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "three.h"


class Texture : public EventDispatcher {
public:
	static long textureId;
	static Image* DEFAULT_IMAGE;
	static int DEFAULT_MAPPING;
	bool _value;
	long id;
	std::string uuid;
	std::string name;
	Image* image;
	std::vector<int> mipmaps;
	int mapping;
	int wrapS;
	int wrapT;
	int magFilter;
	int minFilter;
	int anisotropy;
	int format;
	int type;
	Vector2* offset;
	Vector2* repeat;
	bool generateMipmaps;
	bool premultiplyAlpha;
	bool flipY;
	int unpackAlignment;
	int encoding;
	int version;
	//function onUpdate;

	Texture();

	Texture(Image* image, int mapping, int wrapS, int wrapT, int magFilter, int minFilter, int format, int type, int anisotropy, int encoding);

	void needsUpdate(bool value);

	Texture* clone();

	Texture* copy(Texture* source );

	//toJSON( meta );

	void dispose();

	void transformUv(Vector2* uv );
};

#endif // _TEXTURE_H_
