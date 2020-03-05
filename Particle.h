#pragma once
#include "Object.h"

struct ParticleProperties
{
	//color properties
	glm::vec4 particle_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); //particles are white by default
	float alphaFadeRate = 0.05f;
	
	//position properties
	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 velocity = { 0, 0, 0 };
	float acceleration = 0.0f; //particles should slow, so this should be a float between 0 adn 1. smaller number = slower particle


	//
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	float shrinkRate = 0.0f;
	
	bool active = false;
	
};

class Particle : public Object
{
public:
	//color properties
	glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); //particles are white by default
	float m_alphaFadeRate = 0.05f;

	//position properties
	glm::vec3 m_position = { 0, 0, 0 };
	glm::vec3 m_velocity = { 0, 0, 0 };
	float m_acceleration = 0.0f; //particles should slow, so this should be a float between 0 adn 1. smaller number = slower particle


	//
	glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	float m_shrinkRate = 0.0f;

	bool m_active = false;
	

public:
	Particle();
	Particle(const ParticleProperties& properties, VertexBuffer& vb, IndexBuffer& ib, VertexBufferLayout& layout, Shader& s, glm::mat4 modelMatrix);
	~Particle();
	bool isDying();
	void kill();
	//we can call this if the particle is alive. make the draw call and fade the particle
	void updateParticle();
	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::vec4 getParticleColor();
	//void setRespawnProperties(glm::vec4 alpha, float fade, glm::vec3 pos, glm::vec3 veloc, float acceleration, glm::vec3 scale);
	void setRespawnProperties(const ParticleProperties& pp);
	void activate();
	void setPositionProperty(glm::vec3 pos);
	void setVelocity(glm::vec3 veloc);
	bool isActive();

};

