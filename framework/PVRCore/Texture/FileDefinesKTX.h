/*!
\brief Defines used internally by the KTX reader.
\file PVRCore/Texture/FileDefinesKTX.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
#pragma once
#include "PVRCore/CoreIncludes.h"
//!\cond NO_DOXYGEN
namespace pvr {
namespace texture_ktx {
// Khronos texture file header
struct FileHeader
{
	uint8_t identifier[12];
	uint32_t endianness;
	uint32_t glType;
	uint32_t glTypeSize;
	uint32_t glFormat;
	uint32_t glInternalFormat;
	uint32_t glBaseInternalFormat;
	uint32_t pixelWidth;
	uint32_t pixelHeight;
	uint32_t pixelDepth;
	uint32_t numArrayElements;
	uint32_t numFaces;
	uint32_t numMipmapLevels;
	uint32_t bytesOfKeyValueData;
};

// Magic identifier
static const uint8_t c_identifier[] = { 0xAB, 0x4B, 0x54, 0x58, 0x20, 0x31, 0x31, 0xBB, 0x0D, 0x0A, 0x1A, 0x0A };

// Reference number to verify endianness of a file
static const uint32_t c_endianReference = 0x04030201;

// Expected size of a header in file
static const uint32_t c_expectedHeaderSize = 64;

// Identifier for the orientation meta data
static const char c_orientationMetaDataKey[] = "KTXOrientation";

namespace OpenGLFormats {
enum Enum
{
	/* glTypes */
	GL_BYTE = 0x1400,
	GL_UNSIGNED_BYTE = 0x1401,
	GL_SHORT = 0x1402,
	GL_UNSIGNED_SHORT = 0x1403,
	GL_INT = 0x1404,
	GL_UNSIGNED_INT = 0x1405,
	GL_FLOAT = 0x1406,
	GL_HALF_FLOAT = 0x140B,
	GL_FIXED = 0x140C,

	/* glSizedTypes */
	GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033,
	GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034,
	GL_UNSIGNED_SHORT_5_6_5 = 0x8363,
	GL_UNSIGNED_BYTE_3_3_2 = 0x8032,
	GL_UNSIGNED_INT_8_8_8_8 = 0x8035,
	GL_UNSIGNED_INT_10_10_10_2 = 0x8036,
	GL_UNSIGNED_BYTE_2_3_3_REV = 0x8362,
	GL_UNSIGNED_SHORT_5_6_5_REV = 0x8364,
	GL_UNSIGNED_SHORT_4_4_4_4_REV = 0x8365,
	GL_UNSIGNED_SHORT_1_5_5_5_REV = 0x8366,
	GL_UNSIGNED_INT_8_8_8_8_REV = 0x8367,
	GL_UNSIGNED_INT_2_10_10_10_REV = 0x8368,
	GL_UNSIGNED_SHORT_8_8_APPLE = 0x85BA,
	GL_UNSIGNED_SHORT_8_8_REV_APPLE = 0x85BB,
	GL_UNSIGNED_INT_10F_11F_11F_REV = 0x8C3B,
	GL_UNSIGNED_INT_5_9_9_9_REV = 0x8C3E,

	/* glFormats */
	GL_RED = 0x1903,
	GL_RG = 0x8227,
	GL_ALPHA = 0x1906,
	GL_RGB = 0x1907,
	GL_RGBA = 0x1908,
	GL_BGR = 0x80E0,
	GL_BGRA = 0x80E1,
	GL_LUMINANCE = 0x1909,
	GL_LUMINANCE_ALPHA = 0x190A,
	GL_RG_INTEGER = 0x8228,
	GL_RED_INTEGER = 0x8D94,
	GL_RGB_INTEGER = 0x8D98,
	GL_RGBA_INTEGER = 0x8D99,
	GL_RED_SNORM = 0x8F90,
	GL_RG_SNORM = 0x8F91,
	GL_RGB_SNORM = 0x8F92,
	GL_RGBA_SNORM = 0x8F93,
	GL_LUMINANCE_SNORM = 0x9011,
	GL_LUMINANCE_ALPHA_SNORM = 0x9012,
	GL_INTENSITY_SNORM = 0x9013,
	GL_ALPHA_SNORM = 0x9010,
	GL_SRGB = 0x8C40,
	GL_SRGB_ALPHA = 0x8C42,
	GL_SLUMINANCE_ALPHA = 0x8C44,
	GL_SLUMINANCE = 0x8C46,

	/* glSizedInternalFormats*/
	// Some weird format enum... not really used probably?
	GL_R3_G3_B2 = 0x2A10,

	// Tiny sized types.
	GL_ALPHA4 = 0x803B,
	GL_ALPHA8 = 0x803C,
	GL_ALPHA12 = 0x803D,
	GL_ALPHA16 = 0x803E,
	GL_LUMINANCE4 = 0x803F,
	GL_LUMINANCE8 = 0x8040,
	GL_LUMINANCE12 = 0x8041,
	GL_LUMINANCE16 = 0x8042,
	GL_LUMINANCE4_ALPHA4 = 0x8043,
	GL_LUMINANCE6_ALPHA2 = 0x8044,
	GL_LUMINANCE8_ALPHA8 = 0x8045,
	GL_LUMINANCE12_ALPHA4 = 0x8046,
	GL_LUMINANCE12_ALPHA12 = 0x8047,
	GL_LUMINANCE16_ALPHA16 = 0x8048,
	GL_INTENSITY = 0x8049,
	GL_INTENSITY4 = 0x804A,
	GL_INTENSITY8 = 0x804B,
	GL_INTENSITY12 = 0x804C,
	GL_INTENSITY16 = 0x804D,
	GL_RGB2 = 0x804E,
	GL_RGB4 = 0x804F,
	GL_RGB5 = 0x8050,
	GL_RGB8 = 0x8051,
	GL_RGB10 = 0x8052,
	GL_RGB12 = 0x8053,
	GL_RGB16 = 0x8054,
	GL_RGBA2 = 0x8055,
	GL_RGBA4 = 0x8056,
	GL_RGB5_A1 = 0x8057,
	GL_RGBA8 = 0x8058,
	GL_RGB10_A2 = 0x8059,
	GL_RGBA12 = 0x805A,
	GL_RGBA16 = 0x805B,

	// Regular sized r/rg/rgb/rgba
	GL_R8 = 0x8229,
	GL_R16 = 0x822A,
	GL_RG8 = 0x822B,
	GL_RG16 = 0x822C,
	GL_R16F = 0x822D,
	GL_R32F = 0x822E,
	GL_RG16F = 0x822F,
	GL_RG32F = 0x8230,
	GL_R8I = 0x8231,
	GL_R8UI = 0x8232,
	GL_R16I = 0x8233,
	GL_R16UI = 0x8234,
	GL_R32I = 0x8235,
	GL_R32UI = 0x8236,
	GL_RG8I = 0x8237,
	GL_RG8UI = 0x8238,
	GL_RG16I = 0x8239,
	GL_RG16UI = 0x823A,
	GL_RG32I = 0x823B,
	GL_RG32UI = 0x823C,
	GL_RGBA32F = 0x8814,
	GL_RGB32F = 0x8815,
	GL_RGBA16F = 0x881A,
	GL_RGB16F = 0x881B,
	GL_RGBA32UI = 0x8D70,
	GL_RGB32UI = 0x8D71,
	GL_RGBA16UI = 0x8D76,
	GL_RGB16UI = 0x8D77,
	GL_RGBA8UI = 0x8D7C,
	GL_RGB8UI = 0x8D7D,
	GL_RGBA32I = 0x8D82,
	GL_RGB32I = 0x8D83,
	GL_RGBA16I = 0x8D88,
	GL_RGB16I = 0x8D89,
	GL_RGBA8I = 0x8D8E,
	GL_RGB8I = 0x8D8F,

	// Slightly odd R/RG/RGB/RGBA formats
	GL_R11F_G11F_B10F = 0x8C3A,
	GL_RGB9_E5 = 0x8C3D,
	GL_RGB565 = 0x8D62,
	GL_RGB10_A2UI = 0x906F,

	// Floating point l/a/i types
	GL_ALPHA32F_ARB = 0x8816,
	GL_INTENSITY32F_ARB = 0x8817,
	GL_LUMINANCE32F_ARB = 0x8818,
	GL_LUMINANCE_ALPHA32F_ARB = 0x8819,
	GL_ALPHA16F_ARB = 0x881C,
	GL_INTENSITY16F_ARB = 0x881D,
	GL_LUMINANCE16F_ARB = 0x881E,
	GL_LUMINANCE_ALPHA16F_ARB = 0x881F,

	// An Apple extension
	GL_RGB_422_APPLE = 0x8A1F,

	// SRGB
	GL_SRGB8 = 0x8C41,
	GL_SRGB8_ALPHA8 = 0x8C43,
	GL_SLUMINANCE8_ALPHA8 = 0x8C45,
	GL_SLUMINANCE8 = 0x8C47,

	// Signed normalised types.
	GL_R8_SNORM = 0x8F94,
	GL_RG8_SNORM = 0x8F95,
	GL_RGB8_SNORM = 0x8F96,
	GL_RGBA8_SNORM = 0x8F97,
	GL_R16_SNORM = 0x8F98,
	GL_RG16_SNORM = 0x8F99,
	GL_RGB16_SNORM = 0x8F9A,
	GL_RGBA16_SNORM = 0x8F9B,
	GL_ALPHA8_SNORM = 0x9014,
	GL_LUMINANCE8_SNORM = 0x9015,
	GL_LUMINANCE8_ALPHA8_SNORM = 0x9016,
	GL_INTENSITY8_SNORM = 0x9017,
	GL_ALPHA16_SNORM = 0x9018,
	GL_LUMINANCE16_SNORM = 0x9019,
	GL_LUMINANCE16_ALPHA16_SNORM = 0x901A,
	GL_INTENSITY16_SNORM = 0x901B,

	/* glCompressedFormats*/

	// ETC1
	GL_ETC1_RGB8_OES = 0x8D64,

	// ETC2
	GL_COMPRESSED_R11_EAC = 0x9270,
	GL_COMPRESSED_SIGNED_R11_EAC = 0x9271,
	GL_COMPRESSED_RG11_EAC = 0x9272,
	GL_COMPRESSED_SIGNED_RG11_EAC = 0x9273,
	GL_COMPRESSED_RGB8_ETC2 = 0x9274,
	GL_COMPRESSED_SRGB8_ETC2 = 0x9275,
	GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 = 0x9276,
	GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 = 0x9277,
	GL_COMPRESSED_RGBA8_ETC2_EAC = 0x9278,
	GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC = 0x9279,

	// PVRTC1
	GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG = 0x8C00,
	GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG = 0x8C01,
	GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG = 0x8C02,
	GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG = 0x8C03,

	// PVRTC2
	GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG = 0x9137,
	GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG = 0x9138,

	// DXTC
	GL_COMPRESSED_RGB_S3TC_DXT1_EXT = 0x83F0,
	GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1,
	GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE = 0x83F2,
	GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE = 0x83F3,

	// AMD Formats
	GL_3DC_X_AMD = 0x87F9,
	GL_3DC_XY_AMD = 0x87FA,
	GL_ATC_RGB_AMD = 0x8C92,
	GL_ATC_RGBA_EXPLICIT_ALPHA_AMD = 0x8C93,
	GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD = 0x87EE,

	// Compressed "glFormat" variables... originally designed for glCompressedTexImage2D??
	GL_COMPRESSED_ALPHA = 0x84E9,
	GL_COMPRESSED_LUMINANCE = 0x84EA,
	GL_COMPRESSED_LUMINANCE_ALPHA = 0x84EB,
	GL_COMPRESSED_INTENSITY = 0x84EC,
	GL_COMPRESSED_RGB = 0x84ED,
	GL_COMPRESSED_RGBA = 0x84EE,
	GL_COMPRESSED_SRGB = 0x8C48,
	GL_COMPRESSED_SRGB_ALPHA = 0x8c49,
	GL_COMPRESSED_SLUMINANCE = 0x8C4A,
	GL_COMPRESSED_SLUMINANCE_ALPHA = 0x8C4B,

	// Palletted formats
	GL_PALETTE4_RGB8_OES = 0x8B90,
	GL_PALETTE4_RGBA8_OES = 0x8B91,
	GL_PALETTE4_R5_G6_B5_OES = 0x8B92,
	GL_PALETTE4_RGBA4_OES = 0x8B93,
	GL_PALETTE4_RGB5_A1_OES = 0x8B94,
	GL_PALETTE8_RGB8_OES = 0x8B95,
	GL_PALETTE8_RGBA8_OES = 0x8B96,
	GL_PALETTE8_R5_G6_B5_OES = 0x8B97,
	GL_PALETTE8_RGBA4_OES = 0x8B98,
	GL_PALETTE8_RGB5_A1_OES = 0x8B99
};
}
} // namespace texture_ktx
} // namespace pvr
//!\endcond