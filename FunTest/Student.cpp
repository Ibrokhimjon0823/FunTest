#include "Student.h"

Student::Student() :User{}
{
}
Student::Student(std::string nm) : User{ nm }
{
	std::ofstream out;
	out.open(".\\students\\" + nm+".txt", std::ios::app);
	out.close();
}
void Student::start(std::string teacher, std::string title)
{
	std::ifstream in;
	char ph[10] = "#Answers:";
	char k;
	in.open(".\\teachers\\" + teacher + "\\" + title + ".txt");
	InfileOpeningChecker(in);
	int x = 0;
	bool bl = false;
	while (in.get(k))
	{
		if (k != '~')
		{
			std::cout << k;
		}
		if (k == '\n')
		{
			while (in >> k)
				{
					if (k == ph[x])
						{
							if (x == 8){ bl = true; break; }
								x++;
						}
					else
						{
							std::cout << k;
							break;
						}
				}
			if (bl){ break; }
		}
	}
	Student::check(teacher,title);

}
void strtochar(char * charr, std::string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		charr[i] = str[i];
	}
}
void Student::check(std::string teacher, std::string title)
{
	std::ifstream in;
	std::string str;
	char k;
	in.open(".\\teachers\\" + teacher + "\\" + title + ".txt");
	InfileOpeningChecker(in);
	int num=0;
	while (in >> str)
	{
		if (str == "#Questions:")
		{
			in >> str;
			num = stoi(str);
		}
	}
	in.close();
	//std::cout << "\n" << num << "\n";
	in.open(".\\teachers\\" + teacher + "\\" + title + ".txt");
	InfileOpeningChecker(in);
	char *temp = new char[num + 1];
	char *stans = new char[num + 1];
	//std::cout << "\n" << sizeof(stans) << "\n";
	int x = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	while (in >> str) 
	{
		if (str == "#Answers:")
		{
			//in.get(k);
			while (in.get(k))
			{
				if (k == '\n'){ break; }
				if (k != ' '){ temp[x] = k; x++; }
			}
		}
	}
	in.close();
	std::cout << "\nType your answers(A,B,C,D or E)";
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//Student Input
	for (int i = 0; i < num; i++)
	{
		std::cout << "\n" << i+1 << "."; std::cin >> k;
		stans[i] = k;
	}
	x = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//Checking obtained Answers
	for (int i = 0; i < num; i++)
	{
		if (stans[i] == temp[i])
		{
			std::cout << "\n" << i + 1 << "."<<stans[i]<<" CORRECT))";
			x++;
		}
		else
		{
			std::cout << "\n" << i + 1 << "." << stans[i] <<
				" INCORRECT(( CORRECT ANSWER: "<<temp[i];
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	in.open(".\\students\\" + getName() + ".txt");
	InfileOpeningChecker(in);
	std::ofstream out;
	out.open("temp.txt", std::ios::trunc);
	bool bl = false,b=false;
	int tp = 0;
	while (in.get(k))
		{
			out << k;
		}
	in.close();
	out.close();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	in.open(".\\students\\" + getName() + ".txt");
	InfileOpeningChecker(in);
	while (in >> str)
	{
		if (str == title)
		{
			bl = true;
		}
		if (bl)
		{
			if (str == "Result:")
			{
				in >> str;
				if (stoi(str) < x)
				{
					b = true;
					break;
				}
			}
		}
	}
	in.close();
	if (b)
	{
		in.open("temp.txt");
		InfileOpeningChecker(in);
		std::string stitle = "Title:";
		std::string steach = "Teacher:";
		std::string sres = "Result:";
		bool bt = false;

		out.open(".\\students\\" + getName() + ".txt", std::ios::trunc);
		while (in>>str)
		{
			if (str == stitle)
			{
				in >> str;
				if (str == title)
				{
					bt = true;
				}
				out << stitle << " " << str<<" ";
			}
			else if (str == steach)
			{
				in >> str;
				out << steach << " " << str << " ";
			}
			else if (str == sres)
			{
				if (bt)
				{
					out << sres << " " << x << " / " << num << "\n";
					in >> str;
					in >> str;
					in >> str;
					bt = false;
				}
				else
				{
					in >> str;
					out << sres << " " << str;
					in >> str;
					out << " " << str;
					in >> str;
					out << " " << str << "\n";
				}
			}
		}
		in.close();
	}
	else if (!bl)
	{
		out.open(".\\students\\" + getName() + ".txt", std::ios::app);
		out << "Title: " << title << " Teacher: " << teacher
			<< " Result: " << x << " / " << num << "\n";
	}
	else{}
	out.close();
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Finding test and student credentilas
	in.open(".\\students\\" + getName() + ".txt");
	InfileOpeningChecker(in);
	bl = false;
	tp = 0;
	while (in >> str)
	{
		if (str == title)
		{
			bl = true;
		}
		if ( bl && (str=="Result:") )
			{
				in >> str;
				tp = stoi(str);
				std::cout << str;
				break;
			}
	}
	in.close();
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	bl = false;
	b = false;
	int isRelevant = 0;
	bool name = false;
	int oldscore = 0;
	//Searching teacher student-list 
	in.open(".\\teachers\\" + teacher + "\\results.txt");
	InfileOpeningChecker(in);
	while (in >> str)
	{
		if (str == "Test:"){ 
			in >> str;
			if ((str == title) || bl) { isRelevant++; bl = true; }    }
		if (str == getName() && isRelevant==1){ name = true; }
		if (name && str=="Result:" )
		{
			in >> str;
			if ( stoi(str) < tp )
			{
				oldscore = stoi(str);
				b = true;
			}
			break;
		}
	}
	in.close();
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (b)
	{
		//Copying Results.txt to temp.txt
		in.open(".\\teachers\\" + teacher + "\\results.txt");
		InfileOpeningChecker(in);
		out.open("temp.txt", std::ios::trunc);
		bool tt = false;
		double iavg = 0; int ipass = 0;
		std::string stest = "Test:";
		std::string savg = "Average:";
		std::string spass = "Passed:";
		std::string sst = "Student:";

		while (in>>(str))
		{
			if(str==stest)
			{
				in >> str;
				if (str == title){tt = true;}
				out << stest << " " << str << "\n";
			}
			else if ( str == spass )
			{
				in >> str;
				if (tt){
					ipass = stoi(str);
					out << spass << "\n";
				}
				else
				{
					out << spass << " " <<str<<"\n";
				}
			}
			else if (str == savg)
			{
				in >> str;
				if (tt){
					iavg = stod(str);
					out << savg << "\n";
				}
				else
				{
					out << savg << " " << str << "\n";
				}
			}
			else if ( str == sst )
			{
				in >> str;
				if (tt && (str == getName())){
					out << sst <<" "<<str<< " \n";
					in >> str;
					in >> str;
					in >> str;
					tt = false;
			}
				//Title: LiteratureTest1 Teacher : Sobirjon Result : 2 / 3
				else
				{
				//Student: SSD Result: 2 / 3
					out << sst << " " << str;
					in >> str;
					out <<" " << str<<" ";
					in >> str;
					out << str << " ";
					in >> str;
					out<< str<<" ";
					in >> str;
					out << str << "\n";
				}
			}
			else
			{
				//out << str;
			}
		}
		out.close();
		in.close();
//Wrting formatted data from temp.txt  to teacher/results //".\\teachers\\" + teacher + "\\results.txt"
		in.open("temp.txt");
		InfileOpeningChecker(in);
		out.open( ".\\teachers\\" + teacher + "\\results.txt", std::ios::trunc );
///////////////////////////////////////////////////////////////////////////////////////////////////////////
		tt = false;
		while (in >> (str))
		{
			if (str == stest)
			{
				in >> str;
				if (str == title){ tt = true; }
				out <<"\n"<< stest << " " << str << "\n";
			}
			else if (str == spass)
			{
				if (tt){
					//ipass;
					out << spass <<" "<<ipass<< "\n"; 
				}
				else
				{
					in >> str;
					out << spass << " " << str << "\n";
				}
			}
			else if (str == savg)
			{
				if (tt)
				{
		iavg = ( (ipass*iavg) + (double(x) / num) * 100 - ((double)oldscore / num) * 100) / ipass;
					out << savg <<" "<<iavg<< "\n";
				}
				else
				{
					in >> str;
					out << savg << " " << str << "\n";
				}
			}
			else if (str == sst)
			{
				in >> str;
				if (tt && (str==getName()))
				{
					out << sst << " " << str << " Result: " <<x << " / " <<num<< "\n";
					tt = false;
				}
				else
				{
					out << sst << " " << str;
					in >> str;
					out << " " << str << " ";
					in >> str;
					out << str << " ";
					in >> str;
					out << str << " ";
					in >> str;
					out << str << "\n";
				}
			}
			else
			{
				//out << str;
			}
		}
		in.close();
	}
	//If student is not in teacher result list////////////////////////////////////////////////////////////////
	else if ((!name))
	{
		in.open(".\\teachers\\" + teacher + "\\results.txt");
		InfileOpeningChecker(in);
		out.open("temp.txt", std::ios::trunc);
		bool tt = false;
		double iavg = 0; int ipass = 0;
		std::string stest = "Test:";
		std::string savg = "Average:";
		std::string spass = "Passed:";
		std::string sst = "Student:";
		while (in >> (str))
		{
			if (str == stest)
			{

				in >> str;
				if (str == title){ tt = true; }
				out << stest << " " << str << "\n";
			}
			else if (str == spass)
			{
				in >> str;
				if (tt){
					ipass = stoi(str);
					ipass++;
					out << spass<<" "<<ipass<< "\n";
				}
				else
				{
					out << spass << " " << str << "\n";
				}
			}
			else if (str == savg)
			{
				in >> str;
				if (tt){
					iavg = stod(str);
					iavg = ( (ipass-1)*iavg + (double(x) / num) * 100) / ipass;
					out << savg <<" "<<iavg<< "\n";
				out << "\n" << "Student: " << getName() << " Result: " << x <<" / "<<num << "\n";
					tt = false;
				}
				else
				{
					out << savg << " " << str << "\n";
				}
			}
			else if (str == sst)
			{
					in >> str;
					out << sst << " " << str;
					in >> str;
					out << " " << str << " ";
					in >> str;
					out << str << " ";
					in >> str;
					out << str << " ";
					in >> str;
					out << str << "\n";
			}
			else{
				//out << str;
			}
		}
		out.close();
		in.close();

		out.open(".\\teachers\\" + teacher + "\\results.txt", std::ios::trunc);
		in.open("temp.txt");
		InfileOpeningChecker(in);
		OutfileOpeningChecker(out);
		while (in.get(k))
		{
			out << k;
		}
	}
	else
	{

	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	out.close();
	in.close();
	std::cout << "\n\rResult:  " << (x)<<"  coreect "<<" from "<< num << " questions\n";
	std::cout << "\n name: "<<name<<"  b: "<<b<<"\n";
	delete[] temp;
	delete[] stans;
}

Student::~Student()
{
}