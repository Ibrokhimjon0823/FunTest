#pragma once
#include "User.h"
class Student:public User
{
public:
	Student();
	virtual void start(std::string teacher, std::string title) override;
	virtual void check(std::string teacher, std::string title) override;
	Student(std::string nm);
	virtual ~Student();
private:
	void strtochar(char * charr, std::string str);
};

