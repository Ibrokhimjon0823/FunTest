#include "Teacher.h"
#include <cstring>
Teacher::Teacher() :User{}
{
}
void Teacher::reg(std::string nm, std::string password, std::string type)
{
	User::reg(nm,password,type);
}
bool Teacher::login(std::string nm, std::string password)
{
	return User::login(nm, password);
}
Teacher::Teacher(std::string nm):User{nm}
{
	std::string fname = "./teachers/" + nm;
	char *filename = new char[fname.length() + 1];
	for (unsigned int i = 0; i < strlen(filename); i++)
		{
			filename[i] = fname[i];
		}
	CreateDirectory(filename, NULL);
	delete[] filename;
}
void Teacher::parser(std::ofstream &out)
{
	char k;
	while (std::cin.get(k))
	{
		if (k == '#')
		{
			(std::cin >> k);
			if (k == 'E')
			{
				(std::cin >> k);
				if (k == 'N')
				{
					(std::cin >> k);
					if (k == 'D')
					{
						break;
					}
					else
					{
						out << k;
					}
				}
				else
				{
					out << k;
				}
			}
			else
			{
				out << k;
			}
		}
		else
		{
			out << k;
		}
	}
	
}
int  Teacher::quecounter(std::ifstream &in)
{
	int num = 0;
	char k;
	while (in >> k)
	{
		if (isdigit(k))
		{
			in >> k;
			if (k == '.')
			{
				in >> k;
				if (!(isdigit(k)))
				{
					++num;
				}
			}
		}
	}
	return num;
}

void Teacher::analayzer(std::ifstream &in, const int num, std::string str[])
{
	char k;
	int i = 0;
	while (in >> k)
	{
		if (k == '(')
		{
			in >> k;
			if (k == '~')
			{
				in >> k;
				if (isalpha(k))
				{
					if (i < num){ str[i] = k; i++; }
				}
			}
		}
	}
}

void Teacher::addTest(std::string title)
{
	int num;
	//Num of teachers
	std::string numstr;
	std::ifstream in;
	int numOfTeachers = 0;
	in.open(".//teachers//testlist.txt");
	InfileOpeningChecker(in);
	while (in >> numstr)
	{
		if (numstr == "<N>")
		{
			in >> numstr;
			numOfTeachers = stoi(numstr);
		}
	}
	in.close();
	std::ofstream out,out2;
	//For writing to the test list
	out.open(".//teachers//testlist.txt",std::ios::app);
	numOfTeachers++;
	 out <<"<N> "<<numOfTeachers<<" Teacher: "<< getName() << " Title: " << title << std::endl;
	out.close();
	//For writing student results
	out2.open(".//teachers//" + getName() + "//" + "results.txt",std::ios::app);
	out2 << "Test: " << title << "\nPassed: " << 0;
	out2  << "\nAverage: " << 0 << "\n";
	out2.close();
	//For creating test file
	out.open(".//teachers//"+getName() +"//"+ title+".txt",std::ios::trunc);
	parser(out);
	out.close();
	//Input Stream -- for fiding number of questions
	in.open(".//teachers//" + getName() + "//" + title + ".txt");
	User::InfileOpeningChecker(in);
	num = quecounter(in);
	in.close();
	//Input Stream -- for finding answers
	std::string str[100];
	in.open(".//teachers//" + getName() + "//" + title + ".txt");
	analayzer(in, num,str);
	in.close();
	//Output Stream -- for writing answers
	out2.open(".//teachers//" + getName() + "//" + title + ".txt", std::ios::app);
	User::OutfileOpeningChecker(out2);
	out2 << "\n#Answers: ";
	for (int i = 0; i < num; i++)
		{
			out2 << str[i];
		}
	out2 << "\n#Questions: "<<num;
	out2.close();
}

void Teacher::showTestStats()
{
	//std::string title
	std::ifstream in;
	std::string str;
	std::string stest = "Test:";
	std::string savg = "Average:";
	std::string spass = "Passed:";
	std::string sst = "Student:";
	int count=0;
	bool tt = false;
	in.open(".//teachers//" + getName() + "//" + "results.txt");
		while (in >> str)
		{
				if (str == stest)
				{
					in >> str;
					/*count++;
					if (tt && count != 0){ break; }
					if (str == title){
						count = 0; tt = true;*/
						std::cout << stest << " " << str << "\n";
					//}
				}
		/*	if (tt)
			{*/
				 if (str == spass)
				{
					in >> str;
					std::cout << spass << " " << str << "\n";
				}
				 if (str == savg)
				{
					in >> str;
					std::cout << savg << " " << str << "\n";
				}
				 if (str == sst)
				{
						in >> str;
						std::cout << sst << " " << str;
						in >> str;
						std::cout << " " << str << " ";
						in >> str;
						std::cout << str << " ";
						in >> str;
						std::cout << str << " ";
						in >> str;
						std::cout << str << "\n\r";
				}
			//}
		}
	in.close();
}

Teacher::~Teacher()
{
}