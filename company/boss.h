#ifndef BOSS_H_
#define BOSS_H_
#include "TecManager.h"
#include "SalManager.h"

class Boss:public TecManager,public SaleManager
{
public:

	void queryBoss(int id);
	void updateBossPwd(int id);
	//对经理的增删改查
	void addTecManager();
	void delTecManagerById();
	void modifyTecManager();
	void queryTecManagerInfo();
	void setTecManagerSalary(int id);
	void displayAllTecManagerInfo();
	void setNotice();
	void promoteTecPartTime();
	void demoteTecManager(Boss &boss);
	void promoteSalPartTime();
	void demoteSalManager(Boss &boss);
	//对销售经理的增删改查
	void addSalManager();
	void delSalManagerById();
	void modifySalManager();
	void querySalManagerInfo();
	void setSalManagerPercentage(int id);
	void getSalManagerSaledMoney(int id);
	void setSalManagerMonthPay(int id);
	void calSalManagerMonthSalary(int id);
	void displayAllSalManagerInfo();
	void tecSectionPromoteOrDemotion(Boss &boss);
	void SalSectionPromoteOrDemotion(Boss &boss);
	
};
#endif 
