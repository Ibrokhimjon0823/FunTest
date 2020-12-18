#include "User.h"


void User::InfileOpeningChecker(std::ifstream &file)
{
	if (!file)
	{
		std::cout << "\nInput File is not opened\n";
		_getch();
		exit(1);
	}
}

void User::OutfileOpeningChecker(std::ofstream &file)
{
	if (!file)
	{
		std::cout << "\nOutput File is not opened\n";
		_getch();
		exit(1);
	}
}

User::User() :name{""}
{
}

User::User(std::string nm) :name{nm}
{
	if (name == "")
	{
		std::cout << "\nError username cannot be empty\n";
		_getch();
		exit(1);
	}
}
void User::reg(std::string nm, std::string password, std::string type)
{
	if (nm=="" || password=="" || type=="")
	{
		std::cerr << "\nWrong input(UserName or password or account type)\n";
		_getch();
		exit(1);
	}
	int numOfAccs = 0;
	std::string str;
	bool alhasacc = true;
	std::ofstream out;
	std::ifstream in;
	in.open("users.txt");
	while (in >> str)
	{
		if (str == nm)
		{
			alhasacc = false;
		}
	}
	in.close();
	in.open("users.txt");
	while (in>>str)
	{
		if (str=="<N>")
		{
			in >> str;
			numOfAccs = stoi(str);
		}
	}
	in.close();
	if (alhasacc)
	{
		++numOfAccs;
		setLogTrue();
		out.open("users.txt", std::ios::app);
		User::OutfileOpeningChecker(out);
		out <<"<N> "<< numOfAccs << " .[ Name: " << nm << " "
		<< password <<" Type: "<<type<< " ]\n";
		out.close();
	}
	else
	{
		std::cerr << "\nYou have already registered\n";
	}
}
bool User::login(std::string nm, std::string password)
{
	bool sign = false;
	std::string wr;
	std::ifstream in;
	in.open("users.txt");
	User::InfileOpeningChecker(in);
	while (in >> wr)
	{
		if (wr == nm)
		{
			in >> wr;
			if (wr == password)
			{
				sign = true;
				setLogTrue();
				break;
			}
		}
	}
	in.close();
	return sign;
}
User::~User()
{
}