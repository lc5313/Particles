#include "ParticleSystem.h"
#include "Renderer.h"

ParticleSystem::ParticleSystem(int systemSize, Shader& shader, VertexBuffer& vb, IndexBuffer& ib, VertexBufferLayout& layout) 
	: particleShader(shader), particleVB(vb), particleIB(ib), particleVBL(layout)
{
	pool_size = systemSize;
	//particleShader = particleShader;
	//particleVB = vb;
	//particleIB = ib;
	//particleVBL = layout;
	
}
ParticleSystem::~ParticleSystem()
{

}

//update all particles
void ParticleSystem::onUpdate()
{
	//update system velocity
	for (auto& particle : m_particles)
	{
		//we can ignore inactive particles
		if (!particle.isActive())
		{
			continue;
		}
		particle.updateParticle();
		if (particle.isDying()) {
			particle.kill();
		}

	}
}

//render all active particles
//call the renderer on your active particles
void ParticleSystem::onRender()
{
	for (auto& particle : m_particles)
	{
		//we can ignore inactive particles
		if (!particle.isActive())
		{
			continue;
		}

		particle.transform(glm::translate(glm::mat4(1.0f), particle.getPosition()) * glm::scale(glm::mat4(1.0f), particle.getScale()));
		particle.setObjectColor(particle.getParticleColor());
		particle.setObjectUniforms();
		renderer.draw(particle.getVArray(), particle.getIBuffer(), particle.getShader());
	}
}

//activate new particles. don't confuse this with render
void ParticleSystem::spawnParticle()
{
	Particle& p = m_particles[particle_pool_index];
	p.setRespawnProperties(pp);
	p.setVelocity(systemVelocity);
	p.setPositionProperty(m_spawnPoint);
	p.activate();
	
	
	

	particle_pool_index = --particle_pool_index % pool_size;
}

void ParticleSystem::setSpawn(glm::vec3 newSpawn)
{
	systemVelocity = newSpawn - m_spawnPoint;
	m_spawnPoint = newSpawn;
}

void ParticleSystem::init(glm::vec3 initialSpawn, glm::vec4 color, float alphafade, float accel, glm::vec3 scal)
{
	m_spawnPoint = initialSpawn;
	pp.particle_color = color;
	pp.alphaFadeRate = alphafade;
	pp.acceleration = accel;
	pp.scale = scal;
	//m_particles.resize(pool_size);

	for (int i = 0; i < pool_size; i++)
	{
		m_particles.push_back(Particle(pp, particleVB, particleIB, particleVBL, particleShader, glm::mat4(1.0f)));
	}
}