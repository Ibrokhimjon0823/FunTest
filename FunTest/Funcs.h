#include "User.h";
#include "Teacher.h";
#include "Student.h"
#include <string>
using namespace std;

string str;
ifstream in;
void registerTeachers(User* &obj , string name, string password)
{
	obj = nullptr;
	/*User**/ obj = new Teacher(name);
	obj->reg(name, password, "Teacher");
	//return obj;
}

void registerStudents(User* &obj, string name, string password)
{
	obj = nullptr;
	obj = new Student(name);
	obj->reg(name, password, "Student");
}

void login(User* &obj, string name, string password,char type)
{
	obj = nullptr;
	bool islog;
	string tp;
	if (type == 't')
	{
		obj = new Teacher(name);
		islog = obj->login(name, password);
		tp = "Teacher";
	}
	else if (type=='s')
	{
		obj = new Student(name);
		islog = obj->login(name, password);
		tp = "Student";
	}
	else
	{
		cout << "\nWrong type!\n";
		_getch();
		exit(1);
	}

	if (islog)
	{
		in.open("users.txt");
		while (in >> str)
		{
			if (str == name)
			{
				in >> str;
				in >> str;
				in >> str;
				if (str != tp){ cout << "\nYour account didn't found\n"; _getch(); exit(1); }
				break;
			}
		}
		in.close();
		
		cout << "\n\tYou have succesfully signed in " << name << "! Account Type: " << str;
	}
	else{
		cerr << "\nYou have not registered yet\n";
	}
}
void addTest(User* &obj,string title)
{
	cout << "\nCopy and paste your test here and append to the end of your pasted  test word: #END \n\r";
	obj->addTest(title);
}
void displayStatistics(User* obj)
{
	cout << "\n\t\t---------------------------Results--------------------\n\r";
	cout << "DISCLAIMER:IF AFTER THIS STATEMENT WINDOW IS EMPTY YOU HAVEN'T ADDED ANY TEST \n\r";
	obj->showTestStats();
}
void startTest(User* obj, string teacherName, string title)
{
	bool exist = false;
	in.open(".//teachers//testlist.txt");
	while (in >> str)
	{
		if (str == teacherName)
		{
			in >> str;
			if (str == title){exist = true;break;}
		}
	}
	if (exist)
	{
		cout << "\n------------Test: " << title << " Teacher: " << teacherName<<" ------------\n";
		obj->start(teacherName, title);
		obj->check(teacherName, title);
	} 
	else
	{
		cerr << "\nTest Not Found\n";
	}
	in.close();
}

void showTestListForStudents(User* &obj)
{
	//	"<N> " << numOfTeachers << " Teacher: " << getName() << " Title: " << title << std::endl;
	cout << "\n\t\t\t---------------------------Tests--------------------\n\r";
	cout << "DISCLAIMER:IF AFTER THIS STATEMENT WINDOW IS EMPTY TEACHERS HAVEN'T PROVIDED ANY TEST \n\r";
	ifstream in;
	int userInput;
	string str,teacherName,testTitle;
	cout << "\n\nChoose one of the tests: \n\n\r";
	in.open(".//teachers//testlist.txt");
	while (in >> str)
	{
		if (str == "<N>")
		{
			in >> str;
			cout << str << ". ";
		}
		else if (str == "Teacher:")
		{
			cout << str << " ";
			in >> str;
			cout << str << " ";
		}
		else if (str == "Title:")
		{
			cout << str << " ";
			in >> str;
			cout << str << endl;
		}
		else{}
	}
		in.close();
		in.open(".//teachers//testlist.txt");
		cout << endl << in.tellg() << endl;
		cout << "\n\rEnter the order number of your chosen test: \n\r";
		cin >> userInput;
		while (in >> str)
		{
		//	1 Teacher: Sobirjon Title : LiteratureTest1
			if (str == "<N>")
			{
				in >> str;
				if (stoi(str) == userInput)
				{
					in >> str;
					in >> str;
					teacherName = str;
					in >> str;
					in >> str;
					testTitle = str;
					break;
				}
			}
		}
		cout << endl << teacherName << "  " << testTitle << endl;
		obj->start(teacherName,testTitle);
}

void TestResultsForStudents(User* &obj)
{
	ifstream in;
	char k;
	in.open(".\\students\\" + obj->getName() + ".txt");
	cout << "\n\t\t\t---------------------------Test Results--------------------\n\r";
	cout << "DISCLAIMER:IF AFTER THIS STATEMENT WINDOW IS EMPTY YOU DIDN'T PASS ANY TEST \n\n\r";
	while (in.get(k))
	{
		cout << k;
	}
}