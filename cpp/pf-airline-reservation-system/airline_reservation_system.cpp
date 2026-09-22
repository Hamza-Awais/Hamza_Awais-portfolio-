#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<windows.h>
#include<cstring>
#include<ctime>
#include<cctype>
#include<cstdlib>
using namespace std;

// ----- console / UI helpers -----
void Goto(int x, int y);
void txtcolor(int color);
void box(int w, int h);

// ----- main driver -----
void working();

// ----- menu features -----
void viewFlights(char flightno[][10], char origin[][100], char destination[][100], char time[][10], char date[][100], int seat[3]);
void displaySeatLayout(char PK501[6][6], char PK502[6][6], char PK503[6][6]);
void bookSeat(char**& namelist, int& size, char PK501[][6], char PK502[][6], char PK503[][6], int seat[3], char**& userflightlist, int& flightsize, char**& userseatlist, int& seatsize);
void cancelReservation(char**& namelist, int& size, char PK501[][6], char PK502[][6], char PK503[][6], int seat[3], char**& userflightlist, int& flightsize, char**& userseatlist, int& seatsize);
void viewPassengerList(int& size, char**& namelist, char**& userflightlist, char**& userseatlist, ifstream& fin, int& seatsize, int& flightsize);
void saveData(char**& namelist, int& size, ofstream& fout, char**& userflightlist, char**& userseatlist, int& seatsize, int& flightsize);
void viewLog();

// ----- dynamic array helpers -----
void getusernameList(char**& namelist, int& size);
char** regrow(int& size, char**& namelist);
char* getsinglename();
void copyarray(char** newarray, char** oldarray, int size);
char** flightregrow(int size, char** userflight, int& flightChoice);
void getuserflight(char**& userflightlist, int& flightsize, int flightChoice);
char** seatregrow(int size, char** userflight, int& row, int clm);
void getusreseat(char**& userseatlist, int& seatsize, int& row, int& clm);
void cleanup(char**& namelist, int& namesize, char**& userflightlist, int& flightsize, int& seatsize, char**& userseatlist);

// ----- file / seat helpers -----
void gettingdatafromfile(ifstream& fin, int& size, int& flightsize, int& seatsize, char**& namelist, char**& userflightlist, char**& userseatlist);
void restoreSeats(char PK501[][6], char PK502[][6], char PK503[][6], int seat[3], char** userflightlist, int flightsize, char** userseatlist, int seatsize);
void markSeat(char PK501[][6], char PK502[][6], char PK503[][6], int seat[3], const char flight[], const char seatLabel[], char mark, int delta);
void removeEntry(char** list, int& count, int index);
void writeLog(const char action[], const char name[], const char flight[], const char seat[]);


int main()
{
	working();

	return 0;
}
void Goto(int x, int y)
{
	COORD coord;
	coord.X = (SHORT)x;
	coord.Y = (SHORT)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void txtcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void box(int w, int h)
{
	txtcolor(15);
	Goto(4, 5);
	cout << char(201);
	for (int i = 0;i < w - 2;i++)
	{

		cout << char(205);
	}
	cout << char(187);


	for (int i = 0; i < h - 2;i++)
	{
		Goto(4, 6 + i);
		cout << char(186);
		for (int i = 0; i < w - 2;i++)cout << " ";
		cout << char(186);
	}
	cout << endl;
	Goto(4, 5 + h - 1);
	cout << char(200);
	for (int i = 0;i < w - 2;i++)
	{
		txtcolor(15);
		cout << char(205);
	}
	cout << char(188);

}
void working()
{
	ofstream fout;
	ifstream fin;
	int size = 0;
	int flightsize = 0;
	int seatsize = 0;
	char** namelist = new char* [1];
	char** userflightlist = new char* [1];
	char** userseatlist = new char* [1];


	gettingdatafromfile(fin, size, flightsize, seatsize, namelist, userflightlist, userseatlist);
	char PK501[6][6] = { {' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '} };
	char PK502[6][6] = { {' ',' ',' ',' ',' ',' '}, {' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '} };
	char PK503[6][6] = { {' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '} };
	char choice;
	char flightno[3][10] = { "PK501","PK502","PK503" };
	char destination[3][100] = { "islamabad","dubai","china" };
	char origin[3][100] = { "lahore","islamabad","karachi" };
	char date[3][100] = { "30 - 07 - 2025","30-07-2025","01 - 08 - 2025" };
	int seat[3] = { 0,0,0 };  // seats occupied .
	char time[3][10] = { "14:30", "09:00","22:15" };

	// rebuild the seat grids and booked counts from the data loaded above
	restoreSeats(PK501, PK502, PK503, seat, userflightlist, flightsize, userseatlist, seatsize);

	while (true)
	{
		Goto(0, 0);
		system("cls");    // clear screen before functioning .
		Goto(5, 2);
		txtcolor(8);
		for (int i = 0; i < 37;i++)cout << char(205);
		Goto(9, 3);
		txtcolor(3);
		cout << "AIR LINE RESERVATION MAIN MENU\n";
		Goto(5, 4);
		txtcolor(8);
		for (int i = 0; i < 37;i++)cout << char(205);

		box(40, 12);  //making box for menu options .

		txtcolor(11);
		Goto(8, 7);  cout << "1. View Available Flights";
		Goto(8, 8);  cout << "2. Display Seat Layout";
		Goto(8, 9);  cout << "3. Book a Seat";
		Goto(8, 10); cout << "4. Cancel a Reservation";
		Goto(8, 11); cout << "5. View Passenger List";
		Goto(8, 12); cout << "6. Save Data to File";
		Goto(8, 13); cout << "7. View Booking Log";
		Goto(8, 14); cout << "8. Exit";

		txtcolor(14);
		Goto(5, 18); cout << "Enter your choice (1-8): ";
		cin >> choice;
		if (choice >= '1' && choice <= '8')
		{
			int choiceint = choice - '0';
			switch (choiceint)
			{
			case 1: viewFlights(flightno, origin, destination, time, date, seat); break;
			case 2: displaySeatLayout(PK501, PK502, PK503); break;
			case 3: bookSeat(namelist, size, PK501, PK502, PK503, seat, userflightlist, flightsize, userseatlist, seatsize); break;
			case 4: cancelReservation(namelist, size, PK501, PK502, PK503, seat, userflightlist, flightsize, userseatlist, seatsize); break;
			case 5: viewPassengerList(size, namelist, userflightlist, userseatlist, fin, seatsize, flightsize); break;
			case 6: saveData(namelist, size, fout, userflightlist, userseatlist, seatsize, flightsize); break;
			case 7: viewLog(); break;
			case 8:
				txtcolor(12);
				Goto(8, 19);
				cout << "Exiting... Thank you for using the system!";
				Sleep(1500);
				txtcolor(7);
				Goto(0, 23);
				cleanup(namelist, size, userflightlist, flightsize, seatsize, userseatlist);
				return;
			default:
				txtcolor(12);
				Goto(8, 19);
				cout << "Invalid choice. Please try again.";
				Sleep(800);
				break;
			}
		}
	}
	txtcolor(7);
	Goto(0, 23);
	cleanup(namelist, size, userflightlist, flightsize, seatsize, userseatlist);
}
void viewFlights(char flightno[][10], char origin[][100], char destination[][100], char time[][10], char date[][100], int seat[3])
{
	Goto(0, 0);
	system("cls");
	txtcolor(2);
	cout << "Available Flights:\n\n";
	cout << "Flight No\tOrigin\t\tDestination\tDate\t\t\tTime\tSeats\n";
	cout << "------------------------------------------------------------------------------------------------\n";

	txtcolor(15);
	cout << flightno[0] << "\t\t" << origin[0] << "\t\t" << destination[0] << "\t" << date[0] << "\t\t" << time[0];
	if (36 - seat[0] <= 0)          // no seat left -> FULL
	{
		txtcolor(3);
		cout << "\tFULL\n";
	}
	else
	{
		txtcolor(15);
		cout << "\t" << 36 - seat[0] << "\n";
	}

	txtcolor(15);
	cout << flightno[1] << "\t\t" << origin[1] << "\t" << destination[1] << "\t\t" << date[1] << "\t\t" << time[1];
	if (36 - seat[1] <= 0)
	{
		txtcolor(3);
		cout << "\tFULL\n";
	}
	else
	{
		txtcolor(15);
		cout << "\t" << 36 - seat[1] << "\n";
	}

	txtcolor(15);
	cout << flightno[2] << "\t\t" << origin[2] << "\t\t" << destination[2] << "\t\t" << date[2] << "\t\t" << time[2];
	if (36 - seat[2] <= 0)
	{
		txtcolor(3);
		cout << "\tFULL\n";
	}
	else
	{
		txtcolor(15);
		cout << "\t" << 36 - seat[2] << "\n";
	}

	Goto(0, 9);
	txtcolor(8);
	cout << "press any key to return to the menu......";
	cin.ignore(1000, '\n');
	cin.get();
}
void displaySeatLayout(char PK501[6][6], char PK502[6][6], char PK503[6][6])
{
	char ch;
	Goto(0, 0);
	system("cls");
	txtcolor(3);
	cout << "\tWHICH FLIGHT\n\n";
	txtcolor(10);
	Goto(2, 2);
	cout << "1.PK501";
	Goto(2, 3);
	cout << "2.PK502";
	Goto(2, 4);
	cout << "3.PK503";
	Goto(1, 6);
	cout << "Enter : ";
	cin >> ch;
	system("cls");
	txtcolor(2);
	cout << "\n\t\tSEAT LAYOUT\n\n";
	if (ch >= '1' && ch <= '3')
	{
		int chint = ch - '0';
		switch (chint)
		{
		case 1:
			txtcolor(7);
			for (int j = 0; j < 6; j++)
			{
				Goto(9 + j * 4, 4);  // x = 9 + col*4, y = 4
				cout << " " << char('A' + j);
			}
			for (int i = 0;i < 6;i++)
			{
				Goto(4, 5 + i);

				cout << i + 1;
			}
			for (int i = 0; i < 6;i++)
			{
				for (int j = 0; j < 6;j++)
				{
					Goto(9 + j * 4, i + 5);
					txtcolor(13);
					if (PK501[i][j] == 'X')
					{
						txtcolor(13);
					}
					else
					{
						txtcolor(14);
					}
					cout << "[" << PK501[i][j] << "]";
				}
			}
			break;
		case 2:
			txtcolor(7);
			for (int j = 0; j < 6; j++)
			{
				Goto(9 + j * 4, 4);
				cout << " " << char('A' + j);
			}
			for (int i = 0;i < 6;i++)
			{
				Goto(4, 5 + i);

				cout << i + 1;
			}
			for (int i = 0; i < 6;i++)
			{
				for (int j = 0; j < 6;j++)
				{
					Goto(9 + j * 4, i + 5);
					txtcolor(13);
					if (PK502[i][j] == 'X')
					{
						txtcolor(13);
					}
					else
					{
						txtcolor(14);
					}
					cout << "[" << PK502[i][j] << "]";
				}
			}
			break;
		case 3:
			txtcolor(7);
			for (int j = 0; j < 6; j++)
			{
				Goto(9 + j * 4, 4);
				cout << " " << char('A' + j);
			}
			for (int i = 0;i < 6;i++)
			{
				Goto(4, 5 + i);

				cout << i + 1;
			}
			for (int i = 0; i < 6;i++)
			{
				for (int j = 0; j < 6;j++)
				{
					Goto(9 + j * 4, i + 5);
					txtcolor(13);
					if (PK503[i][j] == 'X')
					{
						txtcolor(13);
					}
					else
					{
						txtcolor(14);
					}
					cout << "[" << PK503[i][j] << "]";
				}
			}
			break;
		}
	}
	else {
		cout << "invalid...";
		Sleep(1000);
	}

	Goto(0, 12);
	txtcolor(8);
	cout << "\npress any key to return to the menu......";
	cin.ignore(1000, '\n');
	cin.get();

}
void bookSeat(char**& namelist, int& size, char PK501[][6], char PK502[][6], char PK503[][6], int seat[3], char**& userflightlist, int& flightsize, char**& userseatlist, int& seatsize)
{
	int clm, row, flightChoice;
	Goto(0, 0);
	system("cls");
	txtcolor(6);
	cout << "ENTER YOUR NAME : ";
	txtcolor(7);
	cin.ignore(1000, '\n');
	getusernameList(namelist, size);  // getting name .
	Goto(0, 0);
	system("cls");
	txtcolor(6);
	cout << "\nSelect Flight:\n";
	cout << "1. PK501\n2. PK502\n3. PK503\nEnter choice (1-3): ";
	txtcolor(7);
	while (true)
	{
		cin >> flightChoice;

		if (cin.fail() || flightChoice > 3 || flightChoice < 1)
		{
			txtcolor(4);
			cout << "\n\n\n\nEnter Again!";
			cin.clear();
			cin.ignore(1000, '\n');
			txtcolor(6);
			Goto(20, 5);
			continue;
		}
		else
		{
			switch (flightChoice)
			{
			case 1:
				txtcolor(6);
				cout << "row : ";
				while (true)
				{
					cin >> row;
					if (cin.fail() || row > 6 || row < 1)
					{
						txtcolor(4);
						cout << "\n\n\nEnter Again!";
						cin.clear();
						cin.ignore(1000, '\n');
						txtcolor(6);
						Goto(6, 6);
						continue;
					}
					else
					{
						cout << "column : ";
						while (true)
						{
							cin >> clm;
							if (cin.fail() || clm > 6 || clm < 1)
							{
								txtcolor(4);
								cout << "\n\nEnter Again!";
								cin.clear();
								cin.ignore(1000, '\n');
								txtcolor(6);
								Goto(9, 7);
								continue;
							}
							else
							{
								if (PK501[row - 1][clm - 1] == 'X')
								{
									txtcolor(12);
									cout << "\nAlready booked Enter Again!";
									cin.clear();
									cin.ignore(1000, '\n');
									txtcolor(6);
									Goto(9, 7);
									continue;
								}
								else
								{
									PK501[row - 1][clm - 1] = 'X';
									seat[0]++;
									getuserflight(userflightlist, flightsize, flightChoice);
									getusreseat(userseatlist, seatsize, row, clm);
									writeLog("BOOKED", namelist[size - 1], userflightlist[flightsize - 1], userseatlist[seatsize - 1]);
									txtcolor(10);
									cout << "\n\nSeat booked successfully!   \n";
									Sleep(1500);
									break;
								}

							}
						}
						break;
					}

				}

				break;
			case 2:
				txtcolor(6);
				cout << "row : ";
				while (true)
				{
					cin >> row;
					if (cin.fail() || row > 6 || row < 1)
					{
						txtcolor(4);
						cout << "\n\n\nEnter Again!";
						cin.clear();
						cin.ignore(1000, '\n');
						txtcolor(6);
						Goto(6, 6);
						continue;
					}
					else
					{
						cout << "column : ";
						while (true)
						{
							cin >> clm;
							if (cin.fail() || clm > 6 || clm < 1)
							{

								txtcolor(4);
								cout << "\n\nEnter Again!";
								cin.clear();
								cin.ignore(1000, '\n');
								txtcolor(6);
								Goto(9, 7);
								continue;
							}
							else
							{
								if (PK502[row - 1][clm - 1] == 'X')
								{
									txtcolor(12);
									cout << "\nAlready booked Enter Again!";
									cin.clear();
									cin.ignore(1000, '\n');
									txtcolor(6);
									Goto(9, 7);
									continue;
								}
								else
								{
									PK502[row - 1][clm - 1] = 'X';
									seat[1]++;
									getuserflight(userflightlist, flightsize, flightChoice);
									getusreseat(userseatlist, seatsize, row, clm);
									writeLog("BOOKED", namelist[size - 1], userflightlist[flightsize - 1], userseatlist[seatsize - 1]);
									txtcolor(10);
									cout << "\n\nSeat booked successfully!   \n";
									Sleep(1500);
									break;
								}

							}
						}
						break;
					}
				}
				break;
			case 3:
				txtcolor(6);
				cout << "row : ";
				while (true)
				{
					cin >> row;
					if (cin.fail() || row > 6 || row < 1)
					{
						txtcolor(4);
						cout << "\n\n\nEnter Again!";
						cin.clear();
						cin.ignore(1000, '\n');
						txtcolor(6);
						Goto(6, 6);
						continue;
					}
					else
					{
						cout << "column : ";
						while (true)
						{
							cin >> clm;
							if (cin.fail() || clm > 6 || clm < 1)
							{
								txtcolor(4);
								cout << "\n\nEnter Again!";
								cin.clear();
								cin.ignore(1000, '\n');
								txtcolor(6);
								Goto(9, 7);
								continue;
							}
							else
							{
								if (PK503[row - 1][clm - 1] == 'X')
								{
									txtcolor(12);
									cout << "\nAlready booked Enter Again!";
									cin.clear();
									cin.ignore(1000, '\n');
									txtcolor(6);
									Goto(9, 7);
									continue;
								}
								else
								{
									PK503[row - 1][clm - 1] = 'X';
									seat[2]++;
									getuserflight(userflightlist, flightsize, flightChoice);
									getusreseat(userseatlist, seatsize, row, clm);
									writeLog("BOOKED", namelist[size - 1], userflightlist[flightsize - 1], userseatlist[seatsize - 1]);
									txtcolor(10);
									cout << "\nSeat booked successfully!   \n";
									Sleep(1500);
									break;
								}
							}
						}
						break;
					}
				}
				break;
			}
			break;
		}
	}
	Goto(0, 9);
	txtcolor(8);
	cout << "press any key to return to the menu......";
	cin.ignore(1000, '\n');
	cin.get();
}
void cancelReservation(char**& namelist, int& size, char PK501[][6], char PK502[][6], char PK503[][6], int seat[3], char**& userflightlist, int& flightsize, char**& userseatlist, int& seatsize)
{
	Goto(0, 0);
	system("cls");
	if (size == 0)
	{
		txtcolor(12);
		cout << "No bookings to cancel!\n";
		txtcolor(8);
		cout << "\nPress any key to return to the menu...";
		cin.ignore(1000, '\n');
		cin.get();
		return;
	}
	txtcolor(2);
	cout << "Cancel a Reservation\n\n";
	txtcolor(11);
	cout << "No.   Name              Flight     Seat\n";
	txtcolor(8);
	for (int i = 0; i < 42; i++) cout << char(205);
	cout << "\n";
	txtcolor(7);
	for (int i = 0; i < size; i++)
	{
		cout << " " << i + 1 << ".    " << namelist[i] << "            " << userflightlist[i] << "      " << userseatlist[i] << "\n";
	}
	txtcolor(14);
	cout << "\nEnter booking number to cancel (0 to go back): ";
	int num;
	while (true)
	{
		cin >> num;
		if (cin.fail() || num < 0 || num > size)
		{
			txtcolor(12);
			cout << "\nInvalid number. Enter again: ";
			cin.clear();
			cin.ignore(1000, '\n');
			txtcolor(14);
			continue;
		}
		break;
	}
	if (num == 0)
	{
		txtcolor(7);
		return;
	}
	int idx = num - 1;

	// free the seat in the layout and reduce the booked count
	markSeat(PK501, PK502, PK503, seat, userflightlist[idx], userseatlist[idx], ' ', -1);
	// record the cancellation in the booking log
	writeLog("CANCELLED", namelist[idx], userflightlist[idx], userseatlist[idx]);

	txtcolor(10);
	cout << "\nReservation cancelled for " << namelist[idx]
		<< " (" << userflightlist[idx] << ", seat " << userseatlist[idx] << ").\n";

	// remove this booking from all three parallel lists
	removeEntry(namelist, size, idx);
	removeEntry(userflightlist, flightsize, idx);
	removeEntry(userseatlist, seatsize, idx);

	txtcolor(8);
	cout << "\nPress any key to return to the menu...";
	cin.ignore(1000, '\n');
	cin.get();
}
void viewPassengerList(int& size, char**& namelist, char**& userflightlist, char**& userseatlist, ifstream& fin, int& seatsize, int& flightsize)
{
	Goto(0, 0);
	system("cls");

	if (size == 0)
	{
		txtcolor(12);
		cout << "No passengers booked yet!\n";
		txtcolor(7);
		cout << "\nPress any key to return to the menu...";
		cin.ignore(1000, '\n');
		cin.get();
		return;
	}
	else
	{
		txtcolor(2);
		cout << "Passenger List:\n\n";
		txtcolor(11);
		cout << "Name" << "   " << "Flight" << "  " << "Seat" << endl;
		for (int i = 0; i < 20;i++)
		{
			cout << char(205);
		}
		cout << endl;
		txtcolor(7);
		for (int i = 0; i < size; i++) {
			cout << namelist[i] << "  " << userflightlist[i] << "  " << userseatlist[i] << endl;
			cout << "-----------------------------------\n";
		}

	}
	txtcolor(8);
	cout << "\nPress any key to return to the menu...";
	cin.ignore(1000, '\n');
	cin.get();
}

void saveData(char**& namelist, int& size, ofstream& fout, char**& userflightlist, char**& userseatlist, int& seatsize, int& flightsize)
{
	Goto(0, 0);
	system("cls");
	fout.open("namefile");  // creates/overwrites the file
	fout << size << "\n";
	for (int i = 0; i < size; i++)
	{
		fout << namelist[i] << "\n";   // write each name on a new line
	}
	fout.close();

	fout.open("flightnofile");
	fout << flightsize << "\n";
	for (int i = 0; i < flightsize;i++)
	{
		fout << userflightlist[i] << "\n";
	}
	fout.close();

	fout.open("seatfile");
	fout << seatsize << "\n";
	for (int i = 0; i < seatsize;i++)
	{
		fout << userseatlist[i] << "\n";
	}
	fout.close();

	txtcolor(10);
	cout << "\nAll Data saved successfully\n";
	txtcolor(8);
	cout << "\nPress any key to return to the menu...";
	cin.ignore(1000, '\n');
	cin.get();
}
void viewLog()
{
	Goto(0, 0);
	system("cls");
	ifstream log("bookinglog");
	txtcolor(3);
	cout << "Booking Log (every booking and cancellation)\n\n";
	if (!log)
	{
		txtcolor(12);
		cout << "No activity recorded yet.\n";
	}
	else
	{
		char line[200];
		txtcolor(7);
		bool any = false;
		while (log.getline(line, 200))
		{
			if (line[0] != '\0')
			{
				cout << line << "\n";
				any = true;
			}
		}
		if (!any)
		{
			txtcolor(12);
			cout << "No activity recorded yet.\n";
		}
		log.close();
	}
	txtcolor(8);
	cout << "\nPress any key to return to the menu...";
	cin.ignore(1000, '\n');
	cin.get();
}
void getusernameList(char**& namelist, int& size)
{
	namelist = regrow(size, namelist);
	size++;
}
char** regrow(int& size, char**& namelist)
{
	if (size == 0)
	{
		char** newarray = new char* [1];
		newarray[size] = getsinglename();
		return newarray;
	}
	else
	{
		char** newarray = new char* [size + 1];
		copyarray(newarray, namelist, size);
		newarray[size] = getsinglename();
		delete[] namelist;
		return newarray;
	}
}
char* getsinglename()
{
	char* arr = new char[20];
	cin.getline(arr, 20);
	return arr;
}
void copyarray(char** newarray, char** oldarray, int size)
{
	for (int i = 0;i < size;i++)
	{
		newarray[i] = oldarray[i];
	}
}
char** flightregrow(int size, char** userflight, int& flightChoice)
{
	char** newarray;
	if (size == 0)
	{
		newarray = new char* [1];
	}
	else
	{
		newarray = new char* [size + 1];
		for (int i = 0; i < size; i++)
		{
			newarray[i] = userflight[i];
		}
		delete[] userflight;
	}

	// Allocate new flight name
	newarray[size] = new char[10];
	switch (flightChoice)
	{
	case 1:
		strcpy(newarray[size], "PK501");
		break;
	case 2:
		strcpy(newarray[size], "PK502");
		break;
	case 3:
		strcpy(newarray[size], "PK503");
		break;
	}
	return newarray;

}
void getuserflight(char**& userflightlist, int& flightsize, int flightChoice)
{
	userflightlist = flightregrow(flightsize, userflightlist, flightChoice);
	flightsize++;
}
void cleanup(char**& namelist, int& namesize, char**& userflightlist, int& flightsize, int& seatsize, char**& userseatlist)
{
	for (int i = 0; i < namesize; i++)
	{
		delete[] namelist[i];  // delete each name
	}
	delete[] namelist;
	namelist = nullptr;
	namesize = 0;

	for (int i = 0; i < flightsize; i++)
	{
		delete[] userflightlist[i];  // delete each flight name
	}
	delete[] userflightlist;
	userflightlist = nullptr;
	flightsize = 0;

	for (int i = 0; i < seatsize; i++)
	{
		delete[] userseatlist[i];  // delete each seat label
	}
	delete[] userseatlist;
	userseatlist = nullptr;
	seatsize = 0;
}
void getusreseat(char**& userseatlist, int& seatsize, int& row, int& clm)
{
	userseatlist = seatregrow(seatsize, userseatlist, row, clm);
	seatsize++;
}
char** seatregrow(int size, char** userflight, int& row, int clm)
{
	char** newarray;
	if (size == 0)
	{
		newarray = new char* [1];
	}
	else
	{
		newarray = new char* [size + 1];
		for (int i = 0; i < size; i++)
		{
			newarray[i] = userflight[i];
		}
		delete[] userflight;
	}

	// Allocate new seat label and build it from row + column
	newarray[size] = new char[4];
	newarray[size][0] = char('0' + row);
	newarray[size][1] = char('A' + (clm - 1));
	newarray[size][2] = '\0';
	return newarray;
}
void gettingdatafromfile(ifstream& fin, int& size, int& flightsize, int& seatsize, char**& namelist, char**& userflightlist, char**& userseatlist)
{
	// ----- names -----
	fin.clear();
	fin.open("namefile");
	if (fin)
	{
		fin >> size;
		fin.ignore(1000, '\n');
		delete[] namelist;
		namelist = new char* [size > 0 ? size : 1];
		for (int i = 0; i < size; i++)
		{
			namelist[i] = new char[100];
			fin.getline(namelist[i], 100);
		}
		fin.close();
	}
	else
	{
		size = 0;
		delete[] namelist;
		namelist = new char* [1];
	}

	// ----- flight numbers -----
	fin.clear();
	fin.open("flightnofile");
	if (fin)
	{
		fin >> flightsize;
		delete[] userflightlist;
		userflightlist = new char* [flightsize > 0 ? flightsize : 1];
		for (int i = 0; i < flightsize; i++)
		{
			userflightlist[i] = new char[20];
			fin >> userflightlist[i];
		}
		fin.close();
	}
	else
	{
		flightsize = 0;
		delete[] userflightlist;
		userflightlist = new char* [1];
	}

	// ----- seat labels -----
	fin.clear();
	fin.open("seatfile");
	if (fin)
	{
		fin >> seatsize;
		delete[] userseatlist;
		userseatlist = new char* [seatsize > 0 ? seatsize : 1];
		for (int i = 0; i < seatsize; i++)
		{
			userseatlist[i] = new char[5];
			fin >> userseatlist[i];
		}
		fin.close();
	}
	else
	{
		seatsize = 0;
		delete[] userseatlist;
		userseatlist = new char* [1];
	}
}
void restoreSeats(char PK501[][6], char PK502[][6], char PK503[][6], int seat[3], char** userflightlist, int flightsize, char** userseatlist, int seatsize)
{
	int n = flightsize < seatsize ? flightsize : seatsize;   // use whichever list is shorter, to stay safe
	for (int i = 0; i < n; i++)
	{
		markSeat(PK501, PK502, PK503, seat, userflightlist[i], userseatlist[i], 'X', 1);
	}
}
void markSeat(char PK501[][6], char PK502[][6], char PK503[][6], int seat[3], const char flight[], const char seatLabel[], char mark, int delta)
{
	if (seatLabel[0] < '1' || seatLabel[0] > '6')   // row must be 1-6
		return;
	int row = seatLabel[0] - '0';
	int col = toupper(seatLabel[1]) - 'A';          // column letter A-F -> 0-5
	if (col < 0 || col > 5)
		return;

	if (strcmp(flight, "PK501") == 0)
	{
		PK501[row - 1][col] = mark;
		seat[0] += delta;
		if (seat[0] < 0) seat[0] = 0;
	}
	else if (strcmp(flight, "PK502") == 0)
	{
		PK502[row - 1][col] = mark;
		seat[1] += delta;
		if (seat[1] < 0) seat[1] = 0;
	}
	else if (strcmp(flight, "PK503") == 0)
	{
		PK503[row - 1][col] = mark;
		seat[2] += delta;
		if (seat[2] < 0) seat[2] = 0;
	}
}
void removeEntry(char** list, int& count, int index)
{
	delete[] list[index];
	for (int j = index; j < count - 1; j++)
	{
		list[j] = list[j + 1];
	}
	count--;
}
void writeLog(const char action[], const char name[], const char flight[], const char seat[])
{
	ofstream log("bookinglog", ios::app);   // append, so history is never lost
	if (!log)
		return;

	time_t now = time(0);
	char* ts = ctime(&now);
	char timebuf[64];
	int k = 0;
	for (int i = 0; ts[i] != '\0' && ts[i] != '\n' && k < 63; i++)   // copy time without the trailing newline
		timebuf[k++] = ts[i];
	timebuf[k] = '\0';

	log << action << " | " << name << " | " << flight << " | seat " << seat << " | " << timebuf << "\n";
	log.close();
}
