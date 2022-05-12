#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "shader.h"
#include "texture.h"
#include "gameobject.h"

// Represents a single particle and its state
struct Particle {
    glm::vec2 Position, Direction, Velocity, Gravity;
    glm::vec4 Color;
    float     Life;
    float Scale;
    float Alpha;
    bool Active;

    Particle() : Position(0.0f), Direction(1.0f), Velocity(100.0f), Gravity(0.0f), Color(1.0f), Life(0.0f),
                Scale(100.0f), Alpha(1.0f), Active(true) {}

};

class ParticleGenerator
{
public:
    // constructor
    ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
    // update all particles
    void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    // render all particles
    void Draw();
private:
    // state
    std::vector<Particle> particles;
    unsigned int amount;
    // render state
    Shader shader;
    Texture2D texture;
    unsigned int VAO;
    // initializes buffer and vertex attributes
    void init();
    void updateParticle(Particle& p, float dt, GameObject& object, glm::vec2 offset);
    float generateRandomAlpha();
    float randomDirection();
};

#endif