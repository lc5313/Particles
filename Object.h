#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "VertexBufferLayout.h"

class Object
{
protected:
	VertexArray m_va;
	VertexBuffer m_vb;
	IndexBuffer m_ib;
	VertexBufferLayout m_layout;
	glm::mat4 m_modelTransform;
	Shader& shader;
	glm::vec4 m_color = glm::vec4(0.2f, 0.5, 0.7f, 1.0f);

public:
	Object(VertexBuffer& vb, IndexBuffer& ib, VertexBufferLayout& layout, Shader& shader, glm::mat4 modelMatrix);
	~Object();
	void bindShader();
	void setObjectUniforms();
	void setAllData();
	VertexArray& getVArray();
	IndexBuffer& getIBuffer();
	Shader& getShader();
	void transform(glm::mat4 transformation);
	void setObjectColor(glm::vec4 color);
};

