#pragma once
#include <string>
#include <map>
#include <chrono>
#include <functional>
#include <map>
#include <vector>
#include <Windows.h>
#include "FedorClock.h"
#include "Frame.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace FedorControl
{
	class DrivemagPlayer
	{
	public:

		using CallbackType = std::function<void(std::chrono::duration<float>, std::map<std::string, double>)>;

		/**
		������� ����� ������.
		/param[in] isInterpolation ���������������� �� ��������
		/param[in] frameDt ��� ������������
		/param[in] ����������� ����� ����� ����� �������, ��� ������� �����
		�������� ������������, ����� - ��� ������������
		*/
		DrivemagPlayer(bool isInterpolation = false, int frameDt = 5, int minInterpolationDt = 20, FedorClock& clock = FedorClock());
		~DrivemagPlayer();

		/**
		/brief ������ ��������� � ��������� �����
		/param[in] ������� ��������� �������� �����
		/param[in] ���������, � ������� ���� ��������� ������
		/param[in] time �����, �� ������� ���� ������� �� �������� � ��������� ����
		/param[in] callback �������, ���������������� ����
		*/
		void ToStart(const Pose& currentPose, const Pose& toPose, const double time, const CallbackType callback);

		/**
		/brief ������������� ��������� ���� Drivemag.

		��� ������� ����������� � ������ ����������, ������
		����� ���� ���� ����� �������������

		/param[in] frames ����� ���������
		/param[in] callback �������, ���������������� ����
		*/
		void PlayDrivemag(const vector<Frame>& frames, const CallbackType callback);

	private:
		int _frameDt;												// �������� ������������ ������ ��� ������������ (��)
		bool _isInterpolation;
		int _minInterpolationDt;

		FedorClock& _clock;
		HANDLE _hTimer;

		//������������� ���� ����
		void RunSingle(const Pose& pose, const int delay, const double origTime, const CallbackType callback);

		//��������� ������������
		void Interpolate(const Pose& fromPose, const Pose& toPose, const int delay, const CallbackType callback);


		// ������������� �������� ������� (��)
		void setTimer(int delay);
	};
}
