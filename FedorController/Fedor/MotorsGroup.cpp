#include "MotorsGroup.h"

FedorControl::MotorsGroup::MotorsGroup(SocketLib::TcpClient & socket, AbstractGroup * parent) : AbstractGroup(socket, parent)
{
}

std::string FedorControl::MotorsGroup::MyPrefix()
{
	return "motors";
}

//������������� ���� �������� �������
void FedorControl::MotorsGroup::Posset(std::map<std::string, double> motors)
{
	std::string cmd = Prefix();

	for (auto it = motors.begin(); it != motors.end(); ++it)
		cmd += it->first + ";";

	cmd += ":posset:";

	for (auto it = motors.begin(); it != motors.end(); ++it)
		cmd += std::to_string(it->second) + ";";

	SendCommand(cmd);
}


//�������� ������� ���� ��������� ��������
std::map<std::string, double> FedorControl::MotorsGroup::Posget(std::vector<std::string> motors)
{
	std::string cmd = Prefix();

	for (auto it = motors.begin(); it != motors.end(); ++it)
		cmd += *it + ";";

	cmd += ":posget";

	auto result = SendCommand(cmd);
	if (result.Code() != SUCCESS_WITH_RESULT)
	{
		//������: �� ��� ������� ������ ���� ����� SUCCESS_WITH_RESULT
		//TODO: ��������� ������
	}

	//�������� ������ � �������� ���������
	//result.Buffer()[result.Length() - 1] = 0;

	std::string str((char*)result.Data());
	std::map<std::string, double> angles;
	int pos = 0;
	int matchPos;
	size_t index = 0;

	while ((matchPos = str.find(';', pos)) != std::string::npos && index < motors.size())
	{
		std::string substr = str.substr(pos, matchPos - pos);
		pos = matchPos + 1;

		//��������� ���� �����-���� � ���
		try
		{
			angles.insert(std::make_pair(motors[index], std::stod(substr)));
			
		}
		catch (std::invalid_argument)
		{
			//������ - �� �����
			//TODO: ��������� ������
		}		

		index++;
	}


	if (index != motors.size() || pos < str.length())
	{
		//���������� ���������� � ����������� ���������� �� ���������
		//TODO: ��������� ������
	}

	return angles;
}


//�������� ������� ���� ���� ��������
std::map<std::string, double> FedorControl::MotorsGroup::Posget()
{
	//���� ��� ������ �������, �� �������� ���
	if (_motors.size() == 0)
		List();

	return Posget(_motors);
}


//�������� ������ �������
std::vector<std::string> FedorControl::MotorsGroup::List()
{
	std::string cmd = Prefix() + "list";
	auto result = SendCommand(cmd);
	if (result.Code() != SUCCESS_WITH_RESULT)
	{
		//������: �� ��� ������� ������ ���� ����� SUCCESS_WITH_RESULT
		//TODO: ��������� ������
	}

	_motors = Slice((const char*)result.Data(), ';');

	//���� � ����� ���� ������, ��� ������ ����� �������� �������? 
	return _motors;
}
