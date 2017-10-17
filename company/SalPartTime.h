#ifndef SALEPARTTIME_H_
#define SALEPARTTIME_H_

#include "employee.h"

class SalePartTime: virtual public Employee
{
public:
	void queryById_salPartTime(int id);
	void update_passwd_salPartTime(int id);
	bool judgeSalPartTimeEmpty();

private:
	float m_fPercentage;
	float m_fMonthSaledMoney;
	int m_salLeaderId;
	float m_fMonthSalary;
};

#endif 
