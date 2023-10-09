#pragma once

#include "AGameObject.h"
#include <Windows.h>

class Quad : public AGameObject
{
public:
	/*struct vec3
	{
		float x, y, z;
	};

	struct vertex
	{
		vec3 position;
		vec3 position1;
		vec3 color;
		vec3 color1;
	};*/
	//__declspec(align(16))
	//	struct constant
	//{
	//	float m_angle;
	//};
	
	
	vertex list[4];


	virtual void onCreate(vertex v1, vertex v2, vertex v3, vertex v4) ;
	virtual void onRender(ConstantBuffer* m_cb);
	virtual void onDestroy();

	
	
};

