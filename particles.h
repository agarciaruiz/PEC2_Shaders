#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "shader.h"
#include "texture.h"

// Represents a single particle and its state
struct Particle {
    glm::vec2 Position, Direction;
    glm::vec4 Color;
    float     Life;
    float Scale;
    float Alpha;
    bool Active;
};

class ParticleGenerator
{
public:
    // constructor
    ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
    // update all particles
    void Update(float dt);
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
    void updateParticle(Particle& p, float dt);
    float generateRandomAlpha();
    float randomDirection();
};

#endif