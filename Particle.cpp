#include "Particle.h"

Particle::Particle(const ParticleProperties& properties, VertexBuffer& vb, IndexBuffer& ib, VertexBufferLayout& layout, Shader& s, glm::mat4 modelMatrix) 
	: Object(vb, ib, layout, s, modelMatrix)
{
	glm::vec4 m_color = properties.particle_color; //particles are white by default
	float m_alphaFadeRate = properties.alphaFadeRate;

	//position properties
	glm::vec3 m_position = properties.position;
	glm::vec3 m_velocity = properties.velocity;
	float m_acceleration = properties.acceleration; //particles should slow, so this should be a float between 0 adn 1. smaller number = slower particle


	//
	glm::vec3 m_scale = properties.scale;
	float m_shrinkRate = properties.shrinkRate;

	bool m_active = false;
}


Particle::~Particle()
{

}

/*
a function to determine if we should "kill" this particle (ie remove it from our data structure of particles)
*/
bool Particle::isDying() 
{
	return m_color[4] <= 0.0;
}

void Particle::updateParticle()
{
	m_color[3] -= m_alphaFadeRate;
	m_position += m_velocity;
	m_velocity *= m_acceleration;
}
void Particle::kill()
{
	m_active = false;
}

glm::vec3 Particle::getPosition()
{
	return m_position;
}
glm::vec3 Particle::getScale()
{
	return m_scale;
}

glm::vec4 Particle::getParticleColor()
{
	return m_color;
}

void Particle::setRespawnProperties(const ParticleProperties& properties)
{
	glm::vec4 m_color = properties.particle_color; //particles are white by default
	float m_alphaFadeRate = properties.alphaFadeRate;

	//position properties
	glm::vec3 m_position = properties.position;
	glm::vec3 m_velocity = properties.velocity;
	float m_acceleration = properties.acceleration; //particles should slow, so this should be a float between 0 adn 1. smaller number = slower particle


	//
	glm::vec3 m_scale = properties.scale;
	float m_shrinkRate = properties.shrinkRate;

	bool m_active = false;
}

void Particle::activate()
{
	m_active = true;
}

void Particle::setPositionProperty(glm::vec3 pos)
{
	m_position = pos;
}

void Particle::setVelocity(glm::vec3 veloc)
{
	m_velocity = veloc;
}

bool Particle::isActive()
{
	return m_active;
}