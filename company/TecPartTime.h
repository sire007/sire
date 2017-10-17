#ifndef TECPARTTIME_H_
#define TECPARTTIME_H_

#include "employee.h"

class TecPartTime: virtual public Employee
{
public:
	void queryById_tecPartTime(int id);
	void update_passwd_tecPartTime(int id);
	bool judgeTecPartTimeEmpty();
private:
	int m_uiWorkHour;
	float m_fPerHourPay;
	int m_tecLeaderId;
	float m_fMonthSalary;
};

#endif 
