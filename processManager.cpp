#include "processManager.h"

ParticleGenerator* Particles;

ProcessManager::ProcessManager(unsigned int width, unsigned int height)
	: Keys(), Width(width), Height(height)
{

}

ProcessManager::~ProcessManager()
{
	delete Particles;
}

void ProcessManager::Init()
{
	ResourceManager::LoadShader("3.3.fire_shader.vs", "3.3.fire_shader.fs", nullptr, "fireShader");
	// Get the shader
	Shader shader;
	shader = ResourceManager::GetShader("fireShader");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("fireShader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("fireShader").SetMatrix4("projection", projection);

	// Load and get the corresponding texture
	ResourceManager::LoadTexture("Particle.png", true, "fireTexture");
	Texture2D fireTexture;
	fireTexture = ResourceManager::GetTexture("fireTexture");

	Particles = new ParticleGenerator(shader, fireTexture, 50000);
}

void ProcessManager::Update(float dt)
{
	Particles->Update(dt);
}

void ProcessManager::ProcessInput(float dt)
{

}

void ProcessManager::Render()
{
	// draw particles	
	Particles->Draw();
}