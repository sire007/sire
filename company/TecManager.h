#ifndef TECMANAGER_H_
#define TECMANAGER_H_

#include "TecPartTime.h"

class TecManager: public TecPartTime
{
public:

	//对下属员工的增删改查
	void addTecPartTime(int id);
	void delTecPartTimeById();
	void modifyTecPartTime();
	void queryTecPartTimeInfo();
	void update_passwd_tecManager(int id);
	void queryTecManagerinfo(int id);
	void setWorkHour(int id);
	void setPartTimePerHourPay(int id);
	void modifyTecNote(int id);
	void calTecPartTimeMonthSalary(int id);
	void displayAllTecPartTimeInfo();
	bool judgeTecManagerEmpty();
private:
	float m_fSalary;
};

#endif 
