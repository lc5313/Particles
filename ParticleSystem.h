#pragma once
#include <vector>
#include "Particle.h"




class ParticleSystem
{
public:
	int pool_size = 10000;
	std::vector<Particle> m_particles;
	int particle_pool_index = pool_size - 1;
	glm::vec3 m_spawnPoint;
	glm::vec3 systemVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	Renderer renderer;

	//new particles are initililzed with these properties
	ParticleProperties pp;

	//needed for object rendering
	Shader& particleShader;
	VertexBuffer& particleVB;
	IndexBuffer& particleIB;
	VertexBufferLayout& particleVBL;


public:
	ParticleSystem(int systemSize, Shader& shader, VertexBuffer& vb, IndexBuffer& ib, VertexBufferLayout& layout);
	~ParticleSystem();
	void onUpdate();
	void onRender();
	void spawnParticle();
	void init(glm::vec3 initialSpawn, glm::vec4 color, float alphafade, float accel, glm::vec3 scal);
	void setSpawn(glm::vec3 newSpawn);
	void retrieveVelocity(glm::vec3 oldPos);
};