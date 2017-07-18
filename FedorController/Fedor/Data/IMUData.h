#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace FedorControl
{
	/**
		������ � ������� ������������
		���������
	*/
	class IMUData
	{
	public:
		//���� (�������)
		glm::vec3 Euler;

		//������ � ������������ (g)
		glm::vec3 Acc;

		//������ � ��������� (������/�)
		glm::vec3 Gyro;

		//������ � ������������ (Gauss)
		glm::vec3 Mag;

		//???
		glm::vec4 Quaternion;
	};
}