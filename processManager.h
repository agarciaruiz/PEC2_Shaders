#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "resourceManager.h"
#include "particles.h"

class ProcessManager {
public:
	bool Keys[1024];
	unsigned int Width, Height;
	ProcessManager(unsigned int width, unsigned int height);
	~ProcessManager();
	void Init();
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Render();
};

#endif 