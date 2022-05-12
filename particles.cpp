#include "particles.h"

static GLfloat white[3] = { 1.0f,1.0f,1.0f };
static GLfloat blue[3] = { 0.0f,0.0f,1.0f };
static GLfloat yellow[3] = { 1.0f,1.0f,0.0f };
static GLfloat orange[3] = { 1.0f,0.5f,0.0f };
static GLfloat red[3] = { 1.0f,0.1f,0.0f };

float posX = 0.0f;
float posY = -5.0f;

float gravX = 0.0f;
float gravY = 0.0f;

float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount)
    : shader(shader), texture(texture), amount(amount)
{
    this->init();
}

void ParticleGenerator::Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset)
{
    // update all particles
    for (unsigned int i = 0; i < this->amount; ++i)
    {
        Particle& p = this->particles[i];
        this->updateParticle(p, dt, object, offset);
    }
}

// render all particles
void ParticleGenerator::Draw()
{
    // use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->shader.Use();
    for (Particle particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            this->shader.SetFloat("scale", particle.Scale);
            this->shader.SetVector2f("offset", particle.Position);
            this->shader.SetVector4f("color", particle.Color);
            this->texture.Bind();
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::updateParticle(Particle& p, float dt, GameObject& object, glm::vec2 offset)
{
    if (p.Active)
    {	// particle is alive, thus update
        p.Position.x += p.Direction.x / 10;// Move On The X Axis By X Speed
        p.Position.y += p.Direction.y / 10;// Move On The Y Axis By Y Speed
        //p.Position += p.Direction * dt;

        if ((p.Position.x > posX) && (p.Position.y > (0.1 + posY))) {
            p.Gravity.x = -0.3f;
        }
        else if ((p.Position.x < posX) && (p.Position.y > (0.1 + posY))) {
            p.Gravity.x = 0.3f;
        }
        else {
            p.Gravity.x = 0.0f;
        }

        p.Direction.x += (p.Gravity.x + gravX);			// Take Pull On X Axis Into Account
        p.Direction.y += (p.Gravity.y + gravY);			// Take Pull On Y Axis Into Account
        p.Life -= p.Color.a;

        if (p.Life <= 0.0f) {
            float random = ((rand() % 100) - 50) / 10.0f;
            p.Position = object.Position + glm::vec2(-50, -50);
            p.Direction.x = randomDirection();	// X Axis Speed And Direction
            p.Direction.y = randomDirection();	// Y Axis Speed And Direction
            p.Color.r = white[0];
            p.Color.g = white[1];
            p.Color.b = white[2];
            p.Color.a = generateRandomAlpha();
            p.Life = 1.0f;
            p.Velocity = object.Velocity * 0.1f;
        }
        else if (p.Life < 0.4f)
        {
            p.Color.r = red[0];
            p.Color.g = red[1];
            p.Color.b = red[2];
        }
        else if (p.Life < 0.6f)
        {
            p.Color.r = orange[0];
            p.Color.g = orange[1];
            p.Color.b = orange[2];
        }
        else if (p.Life < 0.75f)
        {
            p.Color.r = yellow[0];
            p.Color.g = yellow[1];
            p.Color.b = yellow[2];
        }
        else if (p.Life < 0.85f)
        {
            p.Color.r = blue[0];
            p.Color.g = blue[1];
            p.Color.b = blue[2];
        }
    }
}

void ParticleGenerator::init()
{
    // set up mesh and attribute properties
    unsigned int VBO;
    float particle_quad[] = {
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    // create this->amount default particle instances
    for (unsigned int i = 0; i < this->amount; ++i) {
        Particle p;
        float random = ((rand() % 100) - 50) / 10.0f;
        p.Position = glm::vec2(350.0f, 250);
        p.Direction.x = randomDirection();	// X Axis Speed And Direction
        p.Direction.y = randomDirection();	// Y Axis Speed And Direction
        p.Color.r = white[0];
        p.Color.g = white[1];
        p.Color.b = white[2];
        p.Color.a = generateRandomAlpha();
        p.Life = 1.0f;
        p.Velocity = glm::vec2(100.0f) * 0.1f;
        this->particles.push_back(p);
    }
}

float ParticleGenerator::generateRandomAlpha() {
    return (float)rand() / RAND_MAX;
}

float ParticleGenerator::randomDirection() {
    return float((rand() % 60) - 30.0f);;
}
