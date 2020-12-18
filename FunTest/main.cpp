#include "Funcs.h"
using namespace std;
//	out.open(".//teachers//testlist.txt", std::ios::app);


int main()
{
	char k,in;
	string lg,ps;
	User* u = new User();
	User* b = new Teacher();
	User* s = new Student();
	/*s->addTest
	b->addTest*/
	do
	{
		std::cout << "\nWelcome User!\nPick one of the options: \n";
		std::cout << "(1)__SIGN IN\n" <<
			"(2)__REGISTER\n(3)__TO EXIT\n\r";
		std::cin >> k;
		if (k == '1')
			{
			std::cout << "\nEnter your LoginName: "; std::cin >> lg;
			std::cout << "\nYour Password: "; std::cin >> ps;
			std::cout << "\nLogin as? (teacher(press 't') or student(press 's'))  "; std::cin >> in;
				login(u, lg, ps,in);
				if (!(u->islogged())){ std::cout << "\nTry again\n\n\r"; k = '1'; }
				else{ break; }
			}
		else if (k=='2')
		{
			std::cout << "\nEnter your LoginName:(One word only)  "; std::cin >> lg;
			std::cout << "\nYour Password: "; std::cin >> ps;
			std::cout << "\nRegister as? (teacher(press 't') or student(press 's'))  "; std::cin >> in;
			if (in == 't'){ u = nullptr; registerTeachers(u,lg, ps);  break; }
			else if (in == 's'){ registerStudents(u, lg, ps); break; }
			else
				{
				std::cout << "\nWrong Input!";
					k = '2';
				}
			if (!(u->islogged())){ std::cout << "\nTry again\n\r"; k = '2'; }
			else{ break; }
		}
		else
		{
			std::cout << "\nThank You!\n";
			_getch();
			exit(1);
		}
	} while (k == '1' || k == '2' || k == '3');
	//Teacher
	if (u->islogged() && in=='t')
	{
		std::cout << "\nPick one of the options: \n";
		std::cout << "(1)__Adding Tests\n" <<
			"(2)__Seeing results" << "\n(3)TO EXIT\n\r";
		std::cin >> k;
		while (k == '1' || k == '2' || k=='3')
		{
			if (k == '1')
			{
				std::cout << "\nEnter your test's title: "; cin >> lg;
					 addTest(u,lg);
					
			}
			else if (k=='2')
			{
				displayStatistics(u);
			}
			else
			{
				std::cout << "\nThank You!\n";
				_getch();
				exit(1);
			}
			std::cout << "\nYou are authenticated\n";
			std::cout << "\nPick one of the options: \n";
			std::cout << "(1)__Adding Tests\n" <<
				"(2)__Seeing results" << "\n(3)__TO EXIT\n\r";
			std::cin >> k;
		}
	}
	//Student
	else if (u->islogged()&& in == 's')
	{
		std::cout << "\nPick one of the options: \n";
		std::cout << "(1)__Starting new test\n" <<
			"(2)__Seeing results";
		std::cin >> k;
		while (k == '1' || k == '2'|| k=='3')
		{
			if (k == '1')
			{
				showTestListForStudents(u);
				
			}
			else if (k=='2')
			{
				TestResultsForStudents(u);
				//break;
			}
			else
			{
				std::cout << "\nThank You!\n";
				_getch();
				exit(1);
			}
			std::cout << "\nYou are authenticated\n";
			std::cout << "\nPick one of the options: \n";
			std::cout << "(1)__Starting new test\n" <<
				"(2)__Seeing results" << "\n(3)__TO exit\n\r";
			std::cin >> k;
		}
	}
	else
	{
		//std::cout << "\nYou are	NOT authenticated\n";
	}
	_getch();
	return 0;
}