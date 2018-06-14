#version 310 es
#extension GL_EXT_shader_pixel_local_storage2 : enable

#ifndef GL_EXT_shader_pixel_local_storage2
#extension GL_EXT_shader_pixel_local_storage : require
#endif

layout(std140, binding = 1) uniform StaticsPerPointLight
{
	highp float fLightIntensity;
	highp float fLightRadius;
	highp vec4 vLightColor;
	highp vec4 vLightSourceColor;
};

layout(rgba8)  __pixel_localEXT FragDataLocal {
	layout(rgba8) highp vec4 albedo;
	layout(rgb10_a2) highp vec4 normal; 
	layout(r32f) highp float depth;
	layout(rgba8) highp vec4 color;
} pls;

void main()
{
	pls.color = pls.color + vLightSourceColor;
}