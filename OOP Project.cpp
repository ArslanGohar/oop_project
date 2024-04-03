#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;
class Person
{
	protected:
    	string name, address;
    	int id, salary;
	public:
    	Person(const string N, const string A, int i, int s)
        : name(N), address(A), id(i), salary(s)
    	{
    	}
    	virtual void menu() = 0;
};

class Admin : public Person
{
	protected:
		int g_id;
	public:
		Admin(int empId, const string empName, int empSalary, const string empAddress, int empGroupId)
    	: Person(empName, empAddress, empId, empSalary), g_id(empGroupId)
	{
	}
		void login();
		void menu() override;
		void insert();
		void display();
		void search();
		void modify();
		void del();
		void group();
		void g_record();
		void show_group();
		void check_attendence();
		void search_attendence();
};

class Employee : public Admin
{
	public:
    	Employee() : Admin(0, "", 0, "", 0) {}
    	void main_menu();
   	    void emp_menu();
    	void modify();
    	void attendence();
    	void menu() override
    	{
    	   emp_menu();
    	}
}; 
    	
int main()
{
	Employee ee;
	ee.main_menu();
    return 0;
}

void Employee :: attendence()
{
	system("cls");
	fstream file;
	int test_id,found=0,a_date,a_month,a_year,t_id,count=0;
	SYSTEMTIME x;
    cout << "\n\n -----------------------Mark Your Attendance------------------------";
	file.open("emp.txt",ios::in);
	if(!file)
	{
        cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
	}
	else
	{
		cout << "\n\n\t Enter Your ID to Mark Attendence : " ;
		cin >> test_id;
		file >> id >> name >> salary >> address >> g_id;
		while(!file.eof())
		{
			if(test_id == id)
			{
				found++;
			}
			file >> id >> name >> salary >> address >> g_id;
		}
		file.close();
		if(found > 0)
		{
			GetSystemTime(&x);
			file.open("attendence.txt",ios::in);
			if(!file)
			{
				file.open("attendence.txt",ios::app|ios::out);
				file << " " << test_id << " " << x.wDay << " " << x.wMonth << " " << x.wYear << "\n";
				file.close();
				cout<<"\n\n\t\t Your Attendence Added Successfully ...!!";
			}
			else
			{
				file >> t_id >> a_date >> a_month >> a_year;
				while(!file.eof())
				{
					if(test_id == t_id && a_date == x.wDay && a_month == x.wMonth && a_year == x.wYear)
					{
						cout<<"\n\n\t  Your Attendence Already Added ...!!";
						count++;
					}
					file >> t_id >> a_date >> a_month >> a_year;
				}
				file.close();
				if(count == 0)
				{
					file.open("attendence.txt",ios::app|ios::out);
					file <<" " << test_id << " " << x.wDay << " " << x.wMonth << " " << x.wYear << "\n";
					file.close();
					cout<<"\n\n\t Your Attendence Added Successfully...";
				}
			}
		}
		else
		{
			cout<<"\n\n\t Invalid Employee ID....";
		}
	}
}

void Employee :: modify()
{
	int test_id, found = 0;
    string name1, address1;
    system("cls");
    cout << "\n\n -----------------------Modify Your Bio------------------------";
    fstream file, file2;
    file.open("emp.txt", ios::in);
    if (!file)
    {
        cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
    }
    cout << "\n\n\tEnter ID to Modify Your Bio : ";
    cin >> test_id;

    file2.open("emp1.txt", ios::app | ios::out);
    file >> id >> name >> salary >> address >> g_id;
    while (!file.eof())
    {
        if (test_id == id)
        {
            system("cls");
            cout << "\n\n\t\t\t\t Enter New Data of Employee for Modification ... ";
            cout << "\n\n\tEmployee Name : ";
            cin >> name1;
            cout << "\tEmployee Address : ";
            cin >>  address1;

            file2 << " " << id << " " << name1 << " " << salary << " " << address1 << " " << g_id << "\n";
            found++;
        }
        else
        {
            file2 << " " << id << " " << name << " " << salary << " " << address << " " << g_id << "\n";
        }
        file >> id >> name >> salary >> address >> g_id;
    }
    file.close();
    file2.close();
    remove("emp.txt");
    rename("emp1.txt", "emp.txt");
    if (found == 0)
    {
        cout << "\n\n\t\tYour ID not found ...!! ";
    }
    else
    {
        cout << "\n\n\t\tBio Modify Successfully ...!! ";
    }
}

void Employee :: emp_menu()
{
	int n;
	g:
	cout << "\n\n -----------------------Employee Control Pannel------------------------" ;
	cout << "\n\n\t\t\t Press 1. To check Bio " ;
	cout << "\n\t\t\t Press 2. To Modify Bio " ;
	cout << "\n\t\t\t Press 3. To Mark Attendance " ;
	cout << "\n\t\t\t Press 4. To Return Main Pannel " ;
	cout << "\n\n\t\t\t Select Your Option " ;
	cin >> n;
	switch(n)
	{
		case 1:
			system("cls");
			search();
			cout << "\n\n\t\t\tPress Any key to return Back ... " ;
            getch();
        	system("cls");
        	emp_menu();
			break;
		case 2:
			system("cls");
			modify();
			cout << "\n\n\t\t\tPress Any key to return Back ... " ;
            getch();
        	system("cls");
        	emp_menu();
			break;
		case 3:
			system("cls");	
			attendence();
			cout << "\n\n\t\t\tPress Any key to return Back ... " ;
            getch();
        	system("cls");
	        emp_menu();
			break;
		case 4:
			system("cls");
			main_menu();
			break;
		default:
		cout << "\n\n\t\t\t Invalid Choice ...!! " ;
		cout << "\n\t\t\tPress Any Key to Continue ...!! ";
		getch();
		system("cls");
		cout << "\n\t\t\t Try Again " ;
		goto g;
	}
}

void Admin :: login()
{
	s:
    string username, password;
    cout << "\n\n -----------------------Login Page------------------------" ;
    cout << "\n\n\t\tEnter Username: ";
    cin >> username;
    cout << "\t\tEnter Password: ";
    cin >> password;

    const string correctUsername = "admin";
    const string correctPassword = "password";

    if (username == correctUsername && password == correctPassword)
	{
        cout << "\n\t\t\tLogin Successful!" << endl;
        cout << "\n\n\t\t\tPress Any key To Continue ...!! " ;
        getch();
        system("cls");
       
	    Person *person;
	    Admin a1(0, "", 0, "", 0);
	    
		person = &a1;
    	person->menu();
    }
	else
	{
        cout << "\n\t\t\tLogin Failed ! " ;
        cout << "Press Any key to Try Again ...!! " ;
        getch();
        system("cls");
        goto s;
    }
}

void Admin :: show_group()
{
	system("cls");
	int test_id, salary_count=0 , found=0 , emp_total = 0 ;
	fstream file , file1;
	cout << "\n\n -----------------------Show All Group of Employees------------------------";
	file.open("Group_id.txt" , ios::in);
	if(!file)
	{
		cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
	}
	file >> test_id ;
	while(!file.eof())
	{
		file1.open("Group.txt" , ios::in);
		file1 >> g_id >> id >> salary ;
		while(!file1.eof())
		{
			if(test_id == g_id)
			{
				salary_count = salary_count + salary ;
				found++ ;
				emp_total++ ;
			}
			file1 >> g_id >> id >> salary ;
		}
		file1.close();
		cout << "\n\n\t\t\tGroup ID : " << test_id ;
		cout << "\n\t\t\tTotal Employees : " << emp_total ;
		cout << "\n\t\t\tTotal Salary : " << salary_count ;
		emp_total=0;
		salary_count=0;
		file >> test_id;
	}
	file.close();
}

void Admin :: g_record()
{
    system("cls");
    int test_id, salary_count = 0, found = 0, count = 0;
    fstream file;
    cout << "\n\n -----------------------Search Group Record of Employees------------------------";
    file.open("Group.txt", ios::in);
    if (!file)
    {
        cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
    }
    cout << "\n\n\tEnter Group ID to search : ";
    cin >> test_id;
    file >> g_id >> id >> salary;
    while (!file.eof())
    {
        if (test_id == g_id)
        {
            cout << "\n\n\t\t\tGroup ID : " << g_id;
            cout << "\n\t\t\tEmployee ID : " << id;
            cout << "\n\t\t\tEmployee Salary : " << salary;
            found++;
            count++;
            salary_count += salary;
        }
        file >> g_id >> id >> salary;
    }

    if (found != 0)
    {
        cout << "\n\n\t\t\tTotal Employees : " << count;
        cout << "\n\t\t\tTotal Salary : " << salary_count;
    }
    else
    {
        cout << "\n\n\t\tGroup ID not found ...!! ";
    }

    file.close();
}

void Admin :: group()
{
 	system("cls");
    fstream file;
    cout << "\n\n -----------------------Display Group of Employees------------------------";
    file.open("Group.txt", ios::in);
    if (!file)
    {
        cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
    }

    if (file.peek() == ifstream::traits_type::eof())
    {
        cout << "\n\n\t\tNo records found. The file is empty...!! ";
    }
    else
    {
        while (file >> g_id >> id >> salary)
        {
            cout << "\n\n\tEmployee ID : " << id;
            cout << "\n\tEmployee Salary : " << salary;
            cout << "\n\tEmployee Group ID : " << g_id;
        }
    }

    file.close();
}

void Admin :: del()
{
    int test_id, found = 0;
    system("cls");
    cout << "\n\n -----------------------Delete Record of Employee------------------------";
    fstream file, file1, file2, file3;
    file.open("emp.txt", ios::in);
	file1.open("Group.txt", ios::in);
    if (!file || !file1)
    {
        cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
    }
    cout << "\n\n\tEnter Employee ID to search : ";
    cin >> test_id;
    file2.open("emp1.txt", ios::app | ios::out);
    file >> id >> name >> salary >> address >> g_id;
    while (!file.eof())
    {
        if (test_id == id)
        {
            cout << "\n\n\t\t\tRecord Deleted Successfully ...!! ";
            found++;
        }
        else
        {
            file2 << " " << id << " " << name << " " << salary << " " << address << " " << g_id << "\n";
        }
        file >> id >> name >> salary >> address >> g_id;
    }
    file.close();
    file2.close();
    remove("emp.txt");
    rename("emp1.txt", "emp.txt");
    file3.open("Group1.txt", ios::app | ios::out);
    file1 >> g_id >> id >> salary;
    while (!file1.eof())
    {
        if (test_id != id)
        {
            file3 << " " << g_id << " " << id << " " << salary << "\n";
        }
        file1 >> g_id >> id >> salary;
    }
    file1.close();
    file3.close();
    remove("Group.txt");
    rename("Group1.txt", "Group.txt");
    if (found == 0)
    {
        cout << "\n\n\t\tEmployee ID not found ...!! ";
    }
}

void Admin :: modify()
{
    int test_id, found = 0, salary1;
    string name1, address1;
    system("cls");
    cout << "\n\n -----------------------Modify Record of Employee------------------------";
    fstream file, file1, file2, file3;
    file.open("emp.txt", ios::in);
    file1.open("Group.txt", ios::in);
    if (!file || !file1)
    {
        cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
    }
    cout << "\n\n\tEnter Employee ID to Modify Data : ";
    cin >> test_id;

    file2.open("emp1.txt", ios::app | ios::out);
    file >> id >> name >> salary >> address >> g_id;
    while (!file.eof())
    {
        if (test_id == id)
        {
            system("cls");
            cout << "\n\n\t\t\t\t Enter New Data of Employee for Modification ... ";
            cout << "\n\n\tEmployee Name : ";
            cin >> name1;
            cout << "\tEmployee Salary : ";
            cin >> salary1;
            cout << "\tEmployee Address : ";
            cin.ignore();
            getline(cin, address1);

            file2 << " " << id << " " << name1 << " " << salary1 << " " << address1 << " " << g_id << "\n";
            found++;
        }
        else
        {
            file2 << " " << id << " " << name << " " << salary << " " << address << " " << g_id << "\n";
        }
        file >> id >> name >> salary >> address >> g_id;
    }
    file.close();
    file2.close();
    remove("emp.txt");
    rename("emp1.txt", "emp.txt");

    file3.open("Group1.txt", ios::app | ios::out);
    file1 >> g_id >> id >> salary;
    while (!file1.eof())
    {
        if (test_id != id)
        {
            file3 << " " << g_id << " " << id << " " << salary << "\n";
        }
        else
        {
            file3 << " " << g_id << " " << id << " " << salary1 << "\n";
        }
        file1 >> g_id >> id >> salary;
    }
    file1.close();
    file3.close();
    remove("Group.txt");
    rename("Group1.txt", "Group.txt");

    if (found == 0)
    {
        cout << "\n\n\t\tEmployee ID not found ...!! ";
    }
    else
    {
        cout << "\n\n\t\tRecord Modify Successfully ...!! ";
    }
}

void Admin :: search()
{
    int emp_id, found = 0;
    system("cls");
    cout << "\n\n -----------------------Display Record of Employee------------------------";
    fstream file;
    file.open("emp.txt", ios::in);
    if (!file)
    {
        cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
    }
    cout << "\n\n\tEnter Employee ID to search : " ;
	cin >> emp_id;
    file >> id >> name >> salary >> address >> g_id;
    while (!file.eof())
    {
        if (emp_id == id)
        {
            system("cls");
            cout << "\n\n\t\t\t\t Data of Employee you search ... ";
            cout << "\n\n\tEmployee ID : " << id;
            cout << "\n\tEmployee Name : " << name;
            cout << "\n\tEmployee Salary : " << salary;
            cout << "\n\tEmployee Address : " << address;
            cout << "\n\tEmployee Group ID : " << g_id;
            found++;
        }
        file >> id >> name >> salary >> address >> g_id;
    }
    file.close();

    if (found == 0)
    {
        cout << "\n\n\t\tEmployee ID not found ...!! ";
    }
}

void Admin :: check_attendence()
{
	system("cls");
	fstream file,file1;
	int d,m,y,a_date,a_month,a_year,t_id,count=0;
    cout << "\n\n -----------------------Check Attendence of Employee------------------------";
	file.open("emp.txt",ios::in);
	file1.open("attendence.txt",ios::in);
	if(!file || !file1)
	{
		cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
	}
	else
	{
		cout << "\n\n\t Date : ";
		cin >> d ;
		cout << "\n\t Month : ";
		cin >> m;
		cout << "\n\t Year : ";
		cin >> y;
		file1.close();
		system("cls");
	    cout << "\n\n -----------------------Check Attendence of Employee------------------------";
		cout << "\n\n\t Employee ID\tPresents\tAbsents" ;
		file >> id >> name >> salary >> address >> g_id;
		while(!file.eof())
		{
			file1.open("attendence.txt",ios::in);
			file1 >> t_id >> a_date>> a_month >> a_year;
			while(!file1.eof())
			{
				if(id == t_id && d <= a_date && m == a_month && y == a_year)
				{
					count++;
				}
				file1 >> t_id >> a_date >> a_month >> a_year;
			}
			file1.close();
			cout << "\n\t " << id << "\t\t" << count << "\t\t" << 30-count;
			count = 0;
			file >> id >> name >> salary >> address >> g_id;
		}
		file.close();
	}
}
void Admin :: search_attendence()
{
	system("cls");
	fstream file,file1;
	int d,m,y,a_date,a_month,a_year,t_id,count=0;
    cout << "\n\n -----------------------Check Attendence of Employee------------------------";
	file.open("emp.txt",ios::in);
	file1.open("attendence.txt",ios::in);
	if(!file || !file1)
	{
		cout << "\n\n\tFile Opening Error ...! ";
        cout << "\n\tPress Any Key to Return Main Menu !!! ";
        getch();
        system("cls");
        menu();
	}
	else
	{
		cout << "\n\n\t Employee ID : ";
		cin >> id;
		cout << "\n\t Date : ";
		cin >> d ;
		cout << "\n\t Month : ";
		cin >> m ;
		cout << "\n\t Year : ";
		cin >> y ;
		file.close();
		system("cls");
		cout << "\n\n\t\t\tCheck Employee Attendence" ;
		file1 >> t_id >> a_date >> a_month >> a_year;
		while(!file1.eof())
		{
			if(id == t_id && d <= a_date && m == a_month && y == a_year)
			{
				count++;
			}
			file1 >> t_id >> a_date >> a_month >> a_year;
		}
		file1.close();
		if(count > 0)
		{
			cout << "\n\n\t Employee ID\tPresents\tAbsents";
			cout << "\n\t " << id <<  "\t\t" << count << "\t\t" << 30-count ;	
		}
		else
		{
			cout << "\n\n\t Employee ID Not Found..." ;
		}
	}
}

void Admin :: display()
{
	system("cls");
	fstream file;
	cout << "\n\n -----------------------Display Record of Employee------------------------" ;
	file.open("emp.txt" , ios::in);
	if(!file)
	{
		cout << "\n\n\tFile Opening Error ...! " ;
		cout << "\n\tPress Any Key to Return Main Menu !!! " ;
		getch();
		system("cls");
		menu();
	}
	file >> id >> name >> salary >> address >> g_id ;
	
   /* if (file.peek() == ifstream::traits_type::eof())
    {
        cout << "\n\n\t\tNo records found. The file is empty...!! ";
    }*/
	while(!file.eof()) // end file
	{
		cout << "\n\n\tEmployee ID : " << id;
		cout << "\n\tEmployee Name : " << name;
		cout << "\n\tEmployee Salary : " << salary;
		cout << "\n\tEmployee Address : " << address;
		cout << "\n\tEmployee Group ID : " << g_id;
		
		file >> id >> name >> salary >> address >> g_id ;
	}
	file.close();
}

Admin getEmployeeData()
{
    int empId, empSalary, empGroupId;
    string empName, empAddress;

    cout << "\n\n -----------------------Insert Record of Employee------------------------";
    cout << "\n\n\tEmployee ID (In Digits): ";
    cin >> empId;
    cout << "\tEmployee Name: ";
    cin >> empName;
    cout << "\tEmployee Salary: ";
    cin >> empSalary;
    cout << "\tEmployee Address: ";
    cin >> empAddress;
    cout << "\tEmployee Group ID (In Digits): ";
    cin >> empGroupId;

    return Admin(empId, empName, empSalary, empAddress, empGroupId);
}

void Admin::insert()
{
    int test_id, found = 0;
    Admin newEmployee = getEmployeeData();

    fstream file, file1;
    file.open("emp.txt", ios::in);
    if (!file)
    {
        file.open("emp.txt", ios::out | ios::app);
        file << " " << newEmployee.id << " " << newEmployee.name << " " << newEmployee.salary << " " << newEmployee.address << " " << newEmployee.g_id << "\n";
        file.close();
    }
    else
    {
        fstream tempFile;
        tempFile.open("temp_emp.txt", ios::out);
        file >> id >> name >> salary >> address >> g_id;
        while (!file.eof())
        {
            if (newEmployee.id < id && found == 0)
            {
                tempFile << " " << newEmployee.id << " " << newEmployee.name << " " << newEmployee.salary << " " << newEmployee.address << " " << newEmployee.g_id << "\n";
                found = 1;
            }
            tempFile << " " << id << " " << name << " " << salary << " " << address << " " << g_id << "\n";
            file >> id >> name >> salary >> address >> g_id;
        }
        if (found == 0)
        {
            tempFile << " " << newEmployee.id << " " << newEmployee.name << " " << newEmployee.salary << " " << newEmployee.address << " " << newEmployee.g_id << "\n";
        }
        file.close();
        tempFile.close();
        remove("emp.txt");
        rename("temp_emp.txt", "emp.txt");
    }

    cout << "\n\tNew Record Inserted Successfully ...! \n";
}

void Employee :: main_menu()
{
	int choice;
	r:
	cout << "\n\n -----------------------Control Pannal------------------------ " ;
	cout << "\n\n\t\t\t Press 1 For Admin " ;
	cout << "\n\t\t\t Press 2 For Employee " ;
	cout << "\n\t\t\t Press 3 For Exit " ;
	cout << "\n\n\t\t\t Select Your Option " ;
	cin >> choice;
	if (choice == 1)
	{
		system("cls");
		login();
	}
	else if (choice == 2)
	{
		system("cls");
		Person *person;
    	Employee e1;
 
    	person = &e1;
    	person->menu();
	}
	else if (choice == 3)
	{
		exit(0);
	}
	else
	{
		cout << "\n\n\t\t\t Invalid Choice ...!! " ;
		cout << "\n\t\t\tPress any key to try Again ...." ;
		getch();
		goto r;
	}
}

void Admin :: menu()
{
	Employee e1;
	int choice;
	int opt , total = 1;
	p:
	cout << "\n\n -----------------------Admin Control Pannel------------------------" ;
	cout << "\n\n | 1.  To Insert Data " ;
	cout << "\n | 2.  To Display Data " ;
	cout << "\n | 3.  To Search Data " ;
	cout << "\n | 4.  To Modify Data " ;
	cout << "\n | 5.  To Delete Data " ;
	cout << "\n | 6.  To Gruop Record " ;
	cout << "\n | 7.  To Search Gruop " ;
	cout << "\n | 8.  To Show All Gruops " ;
	cout << "\n | 9.  To Check Attendence " ;
	cout << "\n | 10. To Search Attendence " ;
	cout << "\n | 11. To Return Main Pannel " ;
	cout << "\n\n Your Choice : " ;
	cin >> choice;
	switch(choice)
	{
		case 1:
			system("cls");
        	A:
            insert();
        	V:
            cout << "\n\n\t\t\tPress 1. To Enter More Employee" << endl;
            cout << "\n\t\t\tPress 2. To Return main menu" << endl;
            cout << "\n\t\t\tSelect option: ";
            cin >> opt;
            if (opt == 1)
			{
                system("cls");
                goto A;
            }
			else if (opt == 2)
			{
                system("cls");
                menu();
            }
			else
			{
                system("cls");
                cout << "\n\n\t\t\tInvalid" << endl;
                cout << "\n\t\t\tPlease select correct option...!!" << endl;
                goto V;
            }
            break;
		case 2:
            display();
            cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 3:
            search();
            cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 4:
			modify();
			cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 5:
			del();
			cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 6:
			group();
			cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 7:
			g_record();
			cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 8:
			show_group();
			cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 9:
			check_attendence();
			cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 10:
			search_attendence();
			cout << "\n\n\t\t\tPress Any key to return menu ... " ;
            getch();
        	system("cls");
            menu();
			break;
		case 11:
			system("Cls");
			e1.main_menu();
			break;
		default:
			system("cls");
			cout << "\n\n Invalid Input Please Select Valid One !!! " ;
			goto p;
	}
}
