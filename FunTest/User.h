#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <windows.h>
class User
{
public:
	User();
	User(std::string nm); 
	virtual void reg(std::string nm, std::string password,std::string type) ;
	virtual bool login(std::string nm, std::string password) ;
	std::string getName()
	{
		return name;
	}
	virtual void setLogTrue()
	{
		log = true;
	}
	virtual bool islogged()
	{
		return log;
	}
	virtual void addTest(std::string title){}
	virtual void showTestStats(){};/*std::string title = ""*/
	//virtual void updateStatistics(std::string tName, std::string title){}
	//Student funcs
	virtual void start(std::string teacher, std::string title){}
	virtual void check(std::string teacher, std::string title){};
	virtual ~User();
private:
	std::string name;
protected:
	void InfileOpeningChecker(std::ifstream &file);
	void OutfileOpeningChecker(std::ofstream &file);
	bool log=false;
};

