#include "Object.h"


Object::Object(VertexBuffer& vb, IndexBuffer& ib, VertexBufferLayout& layout, Shader& s, glm::mat4 modelMatrix) : shader(s)
{
	m_vb = vb;
	vb.bind();
	m_ib = ib;
	ib.bind();
	m_layout = layout;

	std::cout << "vertex array add bufer next" << std::endl;
	m_va.addBuffer(m_vb, m_layout);
	m_modelTransform = modelMatrix;

}


Object::~Object()
{

}

void Object::bindShader() 
{
	shader.bind();
}

void Object::setObjectUniforms()
{
	shader.setUniform4f("u_Color", m_color[0], m_color[1], m_color[2], m_color[3]);
	shader.setUniformMat4f("u_model", m_modelTransform);
}

void Object::setAllData() 
{
	setObjectUniforms();
}

VertexArray& Object::getVArray()
{
	return m_va;
}

IndexBuffer& Object::getIBuffer()
{
	return m_ib;
}

Shader& Object::getShader()
{
	return shader;
}

void Object::transform(glm::mat4 transformation)
{
	m_modelTransform = transformation;
}

void Object::setObjectColor(glm::vec4 color)
{
	m_color = color;
}