#include <iostream>
using namespace std;
int main()
{
	const int size = 100;
	int emp_ID[size]{ 101,112,106,103,109,115,102,104,105,108,107,110,111,114,113 };
	float hour_w[size]{ 5,10,12,1,3,6,8,2,1,5,10,15,20,16,11 };
	float hour_r[size]{ 10,20,15,10,15,10,20,15,10,10,20,15,20,10,20 };
	float gross_s[size]{ 50,200,180,10,45,60,160,30,10,50,200,225,400,160,220 };
	float tax_d[size]{ 5,20,18,1,4.5,6,16,3,1,5,20,22.5,40,16,22 };
	float net_sal[size]{ 45,180,162,9,40.5,54,144,27,9,45,180,202.5,360,144,198 };
	char ch[10]{};
	int used_index = 15;
	int del_val, emp_id;
	float s_point;
	bool flag = true;
	char opt;

	cout << "\t\tPAYROLL MANAGEMENT SYSTEM\n\n\n";

	while (true)
	{
		flag = true;          // reset at the start of every menu round
		cout << "\n\n1. Sort and Display all Records by Employee ID(Ascending)\n";
		cout << "2. Sort and Display all Records by Employee ID(Descending)\n";
		cout << "3. Sort and Display all Records by Gross Salary(Ascending)\n";
		cout << "4. Sort and Display all Records by Gross Salary(Descending)\n";
		cout << "5. Add a New Employee Payroll Record\n";
		cout << "6. Delete an Employee Payroll Record Based on Employee ID\n";
		cout << "7. Display Employees with Net Salary Greater than or Equal to X(Descending)\n";
		cout << "8. Display Employees with Net Salary Greater than or Equal to X(Ascending)\n";
		cout << "9. Display Employees with Net Salary Less than X(Descending)\n";
		cout << "10. Display Employees with Net Salary Less than X(Ascending)\n";
		cout << "11. Update Hours Worked or Hourly Rate for an Employee Based on Employee ID\n";
		cout << "e. Exit\n";

		cout << "\nEnter your option : ";
		cin.width(10);        // read at most 9 characters, so the array can never overflow
		cin >> ch;
		if (!cin)
			break;            // input closed, stop the program
		cin.ignore(1000, '\n');   // throw away anything extra typed on the line

		if (ch[0] == '1' && ch[1] == '\0')
		{
			for (int i = 0; i < used_index; i++)
			{
				int pre_idx = 0;
				for (int j = 1; j < used_index - i; j++)
				{
					if (emp_ID[pre_idx] > emp_ID[j])
					{
						int temp_id = emp_ID[pre_idx];
						emp_ID[pre_idx] = emp_ID[j];
						emp_ID[j] = temp_id;

						float temp = hour_w[pre_idx];
						hour_w[pre_idx] = hour_w[j];
						hour_w[j] = temp;

						temp = hour_r[pre_idx];
						hour_r[pre_idx] = hour_r[j];
						hour_r[j] = temp;

						temp = gross_s[pre_idx];
						gross_s[pre_idx] = gross_s[j];
						gross_s[j] = temp;

						temp = tax_d[pre_idx];
						tax_d[pre_idx] = tax_d[j];
						tax_d[j] = temp;

						temp = net_sal[pre_idx];
						net_sal[pre_idx] = net_sal[j];
						net_sal[j] = temp;
					}
					pre_idx++;
				}
			}
			cout << endl << endl;
			cout << "  Employee records in ascending order by Employee ID\n";
			cout << endl;
			cout << "Employee ID\tHours worked\tHourly rate\tGross salary\tTax deduction\tNet salary";
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				cout << "   " << emp_ID[i] << "\t\t    " << hour_w[i] << "\t\t  " << hour_r[i] << "\t\t  " << gross_s[i] << "\t\t  " << tax_d[i] << "\t\t  " << net_sal[i] << "\n";
			}
			cout << endl << endl;
		}
		else if (ch[0] == '2' && ch[1] == '\0')
		{
			for (int i = 0; i < used_index; i++)
			{
				int pre_idx = 0;
				for (int j = 1; j < used_index - i; j++)
				{
					if (emp_ID[pre_idx] < emp_ID[j])
					{
						int temp_id = emp_ID[pre_idx];
						emp_ID[pre_idx] = emp_ID[j];
						emp_ID[j] = temp_id;

						float temp = hour_w[pre_idx];
						hour_w[pre_idx] = hour_w[j];
						hour_w[j] = temp;

						temp = hour_r[pre_idx];
						hour_r[pre_idx] = hour_r[j];
						hour_r[j] = temp;

						temp = gross_s[pre_idx];
						gross_s[pre_idx] = gross_s[j];
						gross_s[j] = temp;

						temp = tax_d[pre_idx];
						tax_d[pre_idx] = tax_d[j];
						tax_d[j] = temp;

						temp = net_sal[pre_idx];
						net_sal[pre_idx] = net_sal[j];
						net_sal[j] = temp;
					}
					pre_idx++;
				}
			}
			cout << endl << endl;
			cout << "  Employee records in descending order by Employee ID\n";
			cout << endl;
			cout << "Employee ID\tHours worked\tHourly rate\tGross salary\tTax deduction\tNet salary";
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				cout << "   " << emp_ID[i] << "\t\t    " << hour_w[i] << "\t\t  " << hour_r[i] << "\t\t  " << gross_s[i] << "\t\t  " << tax_d[i] << "\t\t  " << net_sal[i] << "\n";
			}
			cout << endl << endl;
		}
		else if (ch[0] == '3' && ch[1] == '\0')
		{
			for (int i = 0; i < used_index; i++)
			{
				int pre_idx = 0;
				for (int j = 1; j < used_index - i; j++)
				{
					if (gross_s[pre_idx] > gross_s[j])
					{
						int temp_id = emp_ID[pre_idx];
						emp_ID[pre_idx] = emp_ID[j];
						emp_ID[j] = temp_id;

						float temp = hour_w[pre_idx];
						hour_w[pre_idx] = hour_w[j];
						hour_w[j] = temp;

						temp = hour_r[pre_idx];
						hour_r[pre_idx] = hour_r[j];
						hour_r[j] = temp;

						temp = gross_s[pre_idx];
						gross_s[pre_idx] = gross_s[j];
						gross_s[j] = temp;

						temp = tax_d[pre_idx];
						tax_d[pre_idx] = tax_d[j];
						tax_d[j] = temp;

						temp = net_sal[pre_idx];
						net_sal[pre_idx] = net_sal[j];
						net_sal[j] = temp;
					}
					pre_idx++;
				}
			}
			cout << endl << endl;
			cout << "  Employee records in ascending order by Gross Salary\n";
			cout << endl;
			cout << "Employee ID\tHours worked\tHourly rate\tGross salary\tTax deduction\tNet salary";
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				cout << "   " << emp_ID[i] << "\t\t    " << hour_w[i] << "\t\t  " << hour_r[i] << "\t\t  " << gross_s[i] << "\t\t  " << tax_d[i] << "\t\t  " << net_sal[i] << "\n";
			}
			cout << endl << endl;
		}
		else if (ch[0] == '4' && ch[1] == '\0')
		{
			for (int i = 0; i < used_index; i++)
			{
				int pre_idx = 0;
				for (int j = 1; j < used_index - i; j++)
				{
					if (gross_s[pre_idx] < gross_s[j])
					{
						int temp_id = emp_ID[pre_idx];
						emp_ID[pre_idx] = emp_ID[j];
						emp_ID[j] = temp_id;

						float temp = hour_w[pre_idx];
						hour_w[pre_idx] = hour_w[j];
						hour_w[j] = temp;

						temp = hour_r[pre_idx];
						hour_r[pre_idx] = hour_r[j];
						hour_r[j] = temp;

						temp = gross_s[pre_idx];
						gross_s[pre_idx] = gross_s[j];
						gross_s[j] = temp;

						temp = tax_d[pre_idx];
						tax_d[pre_idx] = tax_d[j];
						tax_d[j] = temp;

						temp = net_sal[pre_idx];
						net_sal[pre_idx] = net_sal[j];
						net_sal[j] = temp;
					}
					pre_idx++;
				}
			}
			cout << endl << endl;
			cout << "  Employee records in descending order by Gross Salary\n";
			cout << endl;
			cout << "Employee ID\tHours worked\tHourly rate\tGross salary\tTax deduction\tNet salary";
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				cout << "   " << emp_ID[i] << "\t\t    " << hour_w[i] << "\t\t  " << hour_r[i] << "\t\t  " << gross_s[i] << "\t\t  " << tax_d[i] << "\t\t  " << net_sal[i] << "\n";
			}
			cout << endl << endl;
		}
		else if (ch[0] == '5' && ch[1] == '\0')
		{
			cout << "Add a new employee record \n\n";
			if (used_index >= size)
			{
				cout << "Record limit reached (" << size << " employees). Delete a record first.\n";
			}
			else
			{
				cout << "Enter Employee ID : ";
				cin >> emp_ID[used_index];
				if (cin.fail() || emp_ID[used_index] <= 0)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nInvalid ID! Please enter a positive whole number.\n";
					continue;
				}
				for (int i = 0; i < used_index; i++)
				{
					if (emp_ID[i] == emp_ID[used_index])
					{
						cout << "\nEnter a unique ID, This ID already exist \n";
						flag = false;
						break;
					}
				}
				if (flag)
				{
					cout << "Enter hours worked : ";
					cin >> hour_w[used_index];
					if (cin.fail() || hour_w[used_index] < 0)
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "\nInvalid input! Hours must be a number (0 or more).\n";
						continue;
					}
					cout << "Enter hourly rate  : ";
					cin >> hour_r[used_index];
					if (cin.fail() || hour_r[used_index] < 0)
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "\nInvalid input! Rate must be a number (0 or more).\n";
						continue;
					}
					gross_s[used_index] = hour_w[used_index] * hour_r[used_index];
					tax_d[used_index] = (10 * gross_s[used_index]) / 100;
					net_sal[used_index] = gross_s[used_index] - tax_d[used_index];
					cout << endl;
					cout << " gross salary is : " << gross_s[used_index] << endl;
					cout << " tax deduction is :" << tax_d[used_index] << endl;
					cout << " net salary is : " << net_sal[used_index] << endl;
					used_index++;
				}
			}
			cout << endl;
			cout << endl;
		}
		else if (ch[0] == '6' && ch[1] == '\0')
		{
			cout << endl << endl;
			cout << "Enter the Employee ID you want to delete : ";
			cin >> del_val;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Please enter a number.\n";
				continue;
			}
			for (int i = 0; i < used_index; i++)
			{
				if (emp_ID[i] == del_val)
				{
					for (int j = i; j < used_index - 1; j++)
					{
						emp_ID[j] = emp_ID[j + 1];
						hour_w[j] = hour_w[j + 1];
						hour_r[j] = hour_r[j + 1];
						gross_s[j] = gross_s[j + 1];
						tax_d[j] = tax_d[j + 1];
						net_sal[j] = net_sal[j + 1];
					}
					used_index--;
					flag = false;
					cout << "Employee record deleted.\n";
					break;
				}
			}
			if (flag)
				cout << "The employee does not exist with this employee ID " << del_val << endl << endl;
			cout << endl;
		}
		else if (ch[0] == '7' && ch[1] == '\0')
		{
			cout << "Enter the net salary (X) : ";
			cin >> s_point;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Please enter a number.\n";
				continue;
			}
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				int pre_idx = 0;
				for (int j = 1; j < used_index - i; j++)
				{
					if (net_sal[pre_idx] < net_sal[j])
					{
						int temp_id = emp_ID[pre_idx];
						emp_ID[pre_idx] = emp_ID[j];
						emp_ID[j] = temp_id;

						float temp = hour_w[pre_idx];
						hour_w[pre_idx] = hour_w[j];
						hour_w[j] = temp;

						temp = hour_r[pre_idx];
						hour_r[pre_idx] = hour_r[j];
						hour_r[j] = temp;

						temp = gross_s[pre_idx];
						gross_s[pre_idx] = gross_s[j];
						gross_s[j] = temp;

						temp = tax_d[pre_idx];
						tax_d[pre_idx] = tax_d[j];
						tax_d[j] = temp;

						temp = net_sal[pre_idx];
						net_sal[pre_idx] = net_sal[j];
						net_sal[j] = temp;
					}
					pre_idx++;
				}
			}
			cout << endl << endl;
			cout << "  Employee records with net salary greater than or equal to X (descending)\n";
			cout << endl;
			cout << "Employee ID\tHours worked\tHourly rate\tGross salary\tTax deduction\tNet salary";
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				if (net_sal[i] >= s_point)
				{
					cout << "   " << emp_ID[i] << "\t\t    " << hour_w[i] << "\t\t  " << hour_r[i] << "\t\t  " << gross_s[i] << "\t\t  " << tax_d[i] << "\t\t  " << net_sal[i] << "\n";
					flag = false;
				}
			}
			if (flag)
				cout << "  No employee found. \n";
			cout << endl << endl;
		}
		else if (ch[0] == '8' && ch[1] == '\0')
		{
			cout << "Enter the net salary (X) : ";
			cin >> s_point;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Please enter a number.\n";
				continue;
			}
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				int pre_idx = 0;
				for (int j = 1; j < used_index - i; j++)
				{
					if (net_sal[pre_idx] > net_sal[j])
					{
						int temp_id = emp_ID[pre_idx];
						emp_ID[pre_idx] = emp_ID[j];
						emp_ID[j] = temp_id;

						float temp = hour_w[pre_idx];
						hour_w[pre_idx] = hour_w[j];
						hour_w[j] = temp;

						temp = hour_r[pre_idx];
						hour_r[pre_idx] = hour_r[j];
						hour_r[j] = temp;

						temp = gross_s[pre_idx];
						gross_s[pre_idx] = gross_s[j];
						gross_s[j] = temp;

						temp = tax_d[pre_idx];
						tax_d[pre_idx] = tax_d[j];
						tax_d[j] = temp;

						temp = net_sal[pre_idx];
						net_sal[pre_idx] = net_sal[j];
						net_sal[j] = temp;
					}
					pre_idx++;
				}
			}
			cout << endl << endl;
			cout << "  Employee records with net salary greater than or equal to X (ascending)\n";
			cout << endl;
			cout << "Employee ID\tHours worked\tHourly rate\tGross salary\tTax deduction\tNet salary";
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				if (net_sal[i] >= s_point)
				{
					cout << "   " << emp_ID[i] << "\t\t    " << hour_w[i] << "\t\t  " << hour_r[i] << "\t\t  " << gross_s[i] << "\t\t  " << tax_d[i] << "\t\t  " << net_sal[i] << "\n";
					flag = false;
				}
			}
			if (flag)
				cout << "  No employee found. \n";
			cout << endl << endl;
		}
		else if (ch[0] == '9' && ch[1] == '\0')
		{
			cout << "Enter the net salary (X) : ";
			cin >> s_point;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Please enter a number.\n";
				continue;
			}
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				int pre_idx = 0;
				for (int j = 1; j < used_index - i; j++)
				{
					if (net_sal[pre_idx] < net_sal[j])
					{
						int temp_id = emp_ID[pre_idx];
						emp_ID[pre_idx] = emp_ID[j];
						emp_ID[j] = temp_id;

						float temp = hour_w[pre_idx];
						hour_w[pre_idx] = hour_w[j];
						hour_w[j] = temp;

						temp = hour_r[pre_idx];
						hour_r[pre_idx] = hour_r[j];
						hour_r[j] = temp;

						temp = gross_s[pre_idx];
						gross_s[pre_idx] = gross_s[j];
						gross_s[j] = temp;

						temp = tax_d[pre_idx];
						tax_d[pre_idx] = tax_d[j];
						tax_d[j] = temp;

						temp = net_sal[pre_idx];
						net_sal[pre_idx] = net_sal[j];
						net_sal[j] = temp;
					}
					pre_idx++;
				}
			}
			cout << endl << endl;
			cout << "  Employee records with net salary less than X (descending)\n";
			cout << endl;
			cout << "Employee ID\tHours worked\tHourly rate\tGross salary\tTax deduction\tNet salary";
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				if (net_sal[i] < s_point)
				{
					cout << "   " << emp_ID[i] << "\t\t    " << hour_w[i] << "\t\t  " << hour_r[i] << "\t\t  " << gross_s[i] << "\t\t  " << tax_d[i] << "\t\t  " << net_sal[i] << "\n";
					flag = false;
				}
			}
			if (flag)
				cout << "  No employee found. \n";
			cout << endl << endl;
		}
		else if (ch[0] == '1' && ch[1] == '0' && ch[2] == '\0')
		{
			cout << "Enter the net salary (X) : ";
			cin >> s_point;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Please enter a number.\n";
				continue;
			}
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				int pre_idx = 0;
				for (int j = 1; j < used_index - i; j++)
				{
					if (net_sal[pre_idx] > net_sal[j])
					{
						int temp_id = emp_ID[pre_idx];
						emp_ID[pre_idx] = emp_ID[j];
						emp_ID[j] = temp_id;

						float temp = hour_w[pre_idx];
						hour_w[pre_idx] = hour_w[j];
						hour_w[j] = temp;

						temp = hour_r[pre_idx];
						hour_r[pre_idx] = hour_r[j];
						hour_r[j] = temp;

						temp = gross_s[pre_idx];
						gross_s[pre_idx] = gross_s[j];
						gross_s[j] = temp;

						temp = tax_d[pre_idx];
						tax_d[pre_idx] = tax_d[j];
						tax_d[j] = temp;

						temp = net_sal[pre_idx];
						net_sal[pre_idx] = net_sal[j];
						net_sal[j] = temp;
					}
					pre_idx++;
				}
			}
			cout << endl << endl;
			cout << "  Employee records with net salary less than X (ascending)\n";
			cout << endl;
			cout << "Employee ID\tHours worked\tHourly rate\tGross salary\tTax deduction\tNet salary";
			cout << endl;
			for (int i = 0; i < used_index; i++)
			{
				if (net_sal[i] < s_point)
				{
					cout << "   " << emp_ID[i] << "\t\t    " << hour_w[i] << "\t\t  " << hour_r[i] << "\t\t  " << gross_s[i] << "\t\t  " << tax_d[i] << "\t\t  " << net_sal[i] << "\n";
					flag = false;
				}
			}
			if (flag)
				cout << "  No employee found. \n";
			cout << endl << endl;
		}
		else if (ch[0] == '1' && ch[1] == '1' && ch[2] == '\0')
		{
			cout << endl;
			cout << " Enter the employee ID of which you want to change Data : ";
			cin >> emp_id;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Please enter a number.\n";
				continue;
			}
			int pos = -1;
			for (int idx = 0; idx < used_index; idx++)
			{
				if (emp_ID[idx] == emp_id)
				{
					pos = idx;
					break;
				}
			}
			if (pos == -1)
			{
				cout << "\nEmployee with this ID does not exist \n\n";
			}
			else
			{
				float new_val;
				bool updated = false;
				cout << "your employee data  \n\n";
				cout << "employee ID : " << emp_ID[pos] << endl;
				cout << "hours worked : " << hour_w[pos] << endl;
				cout << "hourly rate : " << hour_r[pos] << endl;
				cout << "gross salary : " << gross_s[pos] << endl;
				cout << "tax deduction : " << tax_d[pos] << endl;
				cout << "net salary : " << net_sal[pos] << endl;
				cout << endl << endl;
				cout << "press (w) to change the hours worked\npress (r) to change the hourly rate\n";
				cin >> opt;
				cin.ignore(1000, '\n');
				if (opt == 'w' || opt == 'W')
				{
					cout << "Enter new hours worked : ";
					cin >> new_val;
					if (cin.fail() || new_val < 0)
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid input! Nothing was changed.\n";
					}
					else
					{
						hour_w[pos] = new_val;
						updated = true;
					}
				}
				else if (opt == 'r' || opt == 'R')
				{
					cout << "Enter new hourly rate : ";
					cin >> new_val;
					if (cin.fail() || new_val < 0)
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid input! Nothing was changed.\n";
					}
					else
					{
						hour_r[pos] = new_val;
						updated = true;
					}
				}
				else
					cout << "Invalid Input";
				if (updated)
				{
					gross_s[pos] = hour_w[pos] * hour_r[pos];
					tax_d[pos] = (10 * gross_s[pos]) / 100;
					net_sal[pos] = gross_s[pos] - tax_d[pos];
					cout << endl;
					cout << "Record updated. New values : " << endl;
					cout << " gross salary is : " << gross_s[pos] << endl;
					cout << " tax deduction is :" << tax_d[pos] << endl;
					cout << " net salary is : " << net_sal[pos] << endl;
				}
				cout << endl;
			}
		}
		else if ((ch[0] == 'e' || ch[0] == 'E') && ch[1] == '\0')
		{
			cout << "Exiting Program!..." << endl;
			break;
		}
		else
		{
			cout << "Invalid Input!....." << endl;
		}
	}
	return 0;
}
