
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

namespace THREE {

const std::string REVISION = "85";
//const int MOUSE = { LEFT: 0, MIDDLE: 1, RIGHT: 2 };
const int CullFaceNone = 0;
const int CullFaceBack = 1;
const int CullFaceFront = 2;
const int CullFaceFrontBack = 3;
const int FrontFaceDirectionCW = 0;
const int FrontFaceDirectionCCW = 1;
const int BasicShadowMap = 0;
const int PCFShadowMap = 1;
const int PCFSoftShadowMap = 2;
const int FrontSide = 0;
const int BackSide = 1;
const int DoubleSide = 2;
const int FlatShading = 1;
const int SmoothShading = 2;
const int NoColors = 0;
const int FaceColors = 1;
const int VertexColors = 2;
const int NoBlending = 0;
const int NormalBlending = 1;
const int AdditiveBlending = 2;
const int SubtractiveBlending = 3;
const int MultiplyBlending = 4;
const int CustomBlending = 5;
const int AddEquation = 100;
const int SubtractEquation = 101;
const int ReverseSubtractEquation = 102;
const int MinEquation = 103;
const int MaxEquation = 104;
const int ZeroFactor = 200;
const int OneFactor = 201;
const int SrcColorFactor = 202;
const int OneMinusSrcColorFactor = 203;
const int SrcAlphaFactor = 204;
const int OneMinusSrcAlphaFactor = 205;
const int DstAlphaFactor = 206;
const int OneMinusDstAlphaFactor = 207;
const int DstColorFactor = 208;
const int OneMinusDstColorFactor = 209;
const int SrcAlphaSaturateFactor = 210;
const int NeverDepth = 0;
const int AlwaysDepth = 1;
const int LessDepth = 2;
const int LessEqualDepth = 3;
const int EqualDepth = 4;
const int GreaterEqualDepth = 5;
const int GreaterDepth = 6;
const int NotEqualDepth = 7;
const int MultiplyOperation = 0;
const int MixOperation = 1;
const int AddOperation = 2;
const int NoToneMapping = 0;
const int LinearToneMapping = 1;
const int ReinhardToneMapping = 2;
const int Uncharted2ToneMapping = 3;
const int CineonToneMapping = 4;
const int UVMapping = 300;
const int CubeReflectionMapping = 301;
const int CubeRefractionMapping = 302;
const int EquirectangularReflectionMapping = 303;
const int EquirectangularRefractionMapping = 304;
const int SphericalReflectionMapping = 305;
const int CubeUVReflectionMapping = 306;
const int CubeUVRefractionMapping = 307;
const int RepeatWrapping = 1000;
const int ClampToEdgeWrapping = 1001;
const int MirroredRepeatWrapping = 1002;
const int NearestFilter = 1003;
const int NearestMipMapNearestFilter = 1004;
const int NearestMipMapLinearFilter = 1005;
const int LinearFilter = 1006;
const int LinearMipMapNearestFilter = 1007;
const int LinearMipMapLinearFilter = 1008;
const int UnsignedByteType = 1009;
const int ByteType = 1010;
const int ShortType = 1011;
const int UnsignedShortType = 1012;
const int IntType = 1013;
const int UnsignedIntType = 1014;
const int FloatType = 1015;
const int HalfFloatType = 1016;
const int UnsignedShort4444Type = 1017;
const int UnsignedShort5551Type = 1018;
const int UnsignedShort565Type = 1019;
const int UnsignedInt248Type = 1020;
const int AlphaFormat = 1021;
const int RGBFormat = 1022;
const int RGBAFormat = 1023;
const int LuminanceFormat = 1024;
const int LuminanceAlphaFormat = 1025;
const int RGBEFormat = RGBAFormat;
const int DepthFormat = 1026;
const int DepthStencilFormat = 1027;
const int RGB_S3TC_DXT1_Format = 2001;
const int RGBA_S3TC_DXT1_Format = 2002;
const int RGBA_S3TC_DXT3_Format = 2003;
const int RGBA_S3TC_DXT5_Format = 2004;
const int RGB_PVRTC_4BPPV1_Format = 2100;
const int RGB_PVRTC_2BPPV1_Format = 2101;
const int RGBA_PVRTC_4BPPV1_Format = 2102;
const int RGBA_PVRTC_2BPPV1_Format = 2103;
const int RGB_ETC1_Format = 2151;
const int LoopOnce = 2200;
const int LoopRepeat = 2201;
const int LoopPingPong = 2202;
const int InterpolateDiscrete = 2300;
const int InterpolateLinear = 2301;
const int InterpolateSmooth = 2302;
const int ZeroCurvatureEnding = 2400;
const int ZeroSlopeEnding = 2401;
const int WrapAroundEnding = 2402;
const int TrianglesDrawMode = 0;
const int TriangleStripDrawMode = 1;
const int TriangleFanDrawMode = 2;
const int LinearEncoding = 3000;
const int sRGBEncoding = 3001;
const int GammaEncoding = 3007;
const int RGBEEncoding = 3002;
const int LogLuvEncoding = 3003;
const int RGBM7Encoding = 3004;
const int RGBM16Encoding = 3005;
const int RGBDEncoding = 3006;
const int BasicDepthPacking = 3200;
const int RGBADepthPacking = 3201;

};

#endif // _GLOBALS_H_
