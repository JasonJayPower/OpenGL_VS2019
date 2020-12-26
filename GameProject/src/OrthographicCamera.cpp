
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top)
	: m_rotation { 0.0f }
	, m_scale { 1.f, 1.f }
	, m_position { 0.f, 0.f, 0.f}
	, m_projectionMatrix{ glm::ortho(left, right, bottom, top, -1.0f, 1.0f) }
	, m_viewMatrix{ 1.0f }
	, m_viewProjectionMatrix { m_projectionMatrix * m_viewMatrix }
{
}

void OrthographicCamera::setProjection(f32 left, f32 right, f32 bottom, f32 top)
{
	m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::recalculateViewMatrix()
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, m_position);
	transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0, 0, 1));
	transform = glm::scale(transform, glm::vec3(m_scale, 1));

	m_viewMatrix = glm::inverse(transform);
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

