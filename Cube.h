#pragma once
#include "AGameObject.h"
class Cube : public AGameObject
{
public:
	Cube(std::string name, void* shader_byte_code, size_t size_shader);
	~Cube();
	 void onRender(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void onDestroy() override;
	void onUpdate(float deltaTime) override;
	void setAnimSpeed(float speed);
	void addMovement(bool direction, float deltaTime);
private:
	float ticks = 0.0f;
	float speedFactor = 0.0f;
	float deltaPos = 0.0f;
	float speed = 10.0f;

	
	

};

