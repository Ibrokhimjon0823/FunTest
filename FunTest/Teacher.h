#pragma once
#include "User.h"

class Teacher:public User
{
public:
	Teacher();
	Teacher(std::string nm);
	virtual void reg(std::string nm, std::string password, std::string type) override;
	virtual bool login(std::string nm, std::string password)override;
	virtual void addTest(std::string title) override;
	virtual void showTestStats() override;/*std::string title*/ 
	virtual void setLogTrue() override
	{
		log = true;
	}
	virtual bool islogged() override
	{
		return log;
	}
	//virtual void updateStatistics(std::string tName, std::string title) override;
	virtual ~Teacher();
private:
	void parser(std::ofstream &out);
	int quecounter(std::ifstream &in);
	void analayzer(std::ifstream &in, int num,std::string str[]);
};