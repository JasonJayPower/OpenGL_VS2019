#pragma once

#include <glm/glm.hpp>
#include "Types.h"

class OrthographicCamera {
public:
	OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top);

	void setProjection(f32 left, f32 right, f32 bottom, f32 top);

	void setPosition(const glm::vec3& position) { m_position = position; recalculateViewMatrix(); }

	void setRotation(float rotation) { m_rotation = rotation; recalculateViewMatrix(); }
	void setScale(const glm::vec2& scale) { m_scale = scale; recalculateViewMatrix(); }

	const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
	const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }
private:

private:
	void recalculateViewMatrix();

	f32 m_rotation;
	glm::vec2 m_scale;
	glm::vec3 m_position;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_viewProjectionMatrix;


};

