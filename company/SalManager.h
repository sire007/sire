#ifndef SALEMANAGER_H_
#define SALEMANAGER_H_

#include "SalPartTime.h"

class SaleManager: public SalePartTime
{
public:
	void setSalPercentage(int id);
	void calSalPartTimeMonthSalary(int id);
	void modifySalNote(int id);
	void setMonthSaledMoney(int id);
	void addSalPartTime(int id);
	void delSalPartTimeById();
	void modifySalPartTime();
	void querySalPartTimeInfo();
	void update_passwd_salManager(int id);
	void querySalManagerinfo(int id);
	void displayAllSalPartTimeInfo();
	bool judgeSalManagerEmpty();
private:
	float m_salManagerMonthSaledMoney;
	float m_salManagerMonthSalary;
	float m_salManagerMonthPay;
	float m_salManagerPercentage;
};

#endif 
