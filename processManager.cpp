#include "processManager.h"
#include "spriteRenderer.h"
#include "resourceManager.h"
#include "particles.h"

// Initial size of the player paddle
const glm::vec2 EMITTER_SIZE(200.0f, 200.0f);
// Initial velocity of the player paddle
const glm::vec3 EMITTER_COLOR(1.0f, 1.0f, 1.0f);
const glm::vec2 INITIAL_VELOCITY(100.0f, -350.0f);

SpriteRenderer* Renderer;
GameObject* Emitter;
ParticleGenerator* Particles;

ProcessManager::ProcessManager(unsigned int width, unsigned int height)
	: Keys(), Width(width), Height(height)
{

}

ProcessManager::~ProcessManager()
{
	delete Renderer;
	delete Emitter;
	delete Particles;
}

void ProcessManager::Init()
{
	ResourceManager::LoadShader("3.3.fire_shader.vs", "3.3.fire_shader.fs", nullptr, "fireShader");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("fireShader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("fireShader").SetMatrix4("projection", projection);

	// Get the shader
	Shader shader;
	shader = ResourceManager::GetShader("fireShader");
	Renderer = new SpriteRenderer(shader);

	// Load and get the corresponding texture
	ResourceManager::LoadTexture("Particle.png", true, "fireTexture");
	Texture2D fireTexture;
	fireTexture = ResourceManager::GetTexture("fireTexture");

	Particles = new ParticleGenerator(shader, fireTexture, 50000);

	glm::vec2 emitterPos = glm::vec2(this->Width / 2.0f, this->Height / 2.0f);
	Emitter = new GameObject(emitterPos, EMITTER_SIZE, fireTexture, EMITTER_COLOR, INITIAL_VELOCITY);
}

void ProcessManager::Update(float dt)
{
	glm::vec2 offset = glm::vec2(EMITTER_SIZE/2.0f);
	Particles->Update(dt, *Emitter, 2, offset);
}

void ProcessManager::ProcessInput(float dt)
{

}

void ProcessManager::Render()
{
	// draw particles	
	Particles->Draw();
}