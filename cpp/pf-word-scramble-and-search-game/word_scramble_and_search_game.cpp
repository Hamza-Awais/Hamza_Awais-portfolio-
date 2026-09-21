#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;
// All function prototypes.
void TakingGridfromFile(const int rows, const int clms, char grid[][20], ifstream& fin);
void displaygrid(const int rows, const int clms, char grid[][20]);
void wordScramble();
void WordSearchGame();
void MainMenuDisplay();
void Gridhint(int& hint);
void Gridevaluation(double timetakken, int sx, int sy, int ex, int ey, bool& word1, bool& word2, bool& word3, bool& word4, bool& word5, char grid[][20], int& score);
void scrambledwordmenu();
void scrambledhint( int& score, bool& hint1, bool& hint2, bool& hint3, bool& hint4);
// main function.
int main()
{
	int opt;
	cout << "--------WORD SCRAMBLE AND SEARCH GAME :---------";
	while (true)
	{

		MainMenuDisplay();   // funcion calling 
		if (cin >> opt)
		{
			switch (opt)
			{
			case 1:
				wordScramble();  // function calling 
				break;
			case 2:
				WordSearchGame(); // function calling 
				break;
			case 3:
				cout << "\nYOU CHOOSE TO EXIT YOUR GAME \n THANK YOU  :)\n";
				return 0;
				break;
			default:
				cin.ignore();
				cout << "INVALID CHOICE! ENTER INPUT AGAIN:";
			}
		}
		else
		{
			cout << "\n>>>YOUR GAME HAS ENDED BECAUSE YOU HAVE ENTERED WRONG INPUT<<<\n";
			break;
		}
	}
	return 0;
}


void TakingGridfromFile(const int rows, const int clms, char grid[][20], ifstream& fin)
{
	for (int i = 0; i < rows; i++)             // getting grid in 2d array from file.
	{
		for (int j = 0; j < clms; j++)
		{
			fin >> grid[i][j];
		}
	}
}
void displaygrid(const int rows, const int clms, char grid[][20])
{
	cout << "\t";                               // disply grid in proper form.  with coordinates .
	for (char i = 'A'; i <= 'T';i++)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << endl;
	for (int i = 0; i < rows; i++)
	{
		cout << i + 1 << "\t";
		for (int j = 0; j < clms; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}
void wordScramble()
{
	char word1[] = { "umbrella" };      // stored every word in different array to compare .
	char word2[] = { "jacket" };
	char word3[] = { "right" };
	char word4[] = { "mango" };

	int score = 0;
	char* wordname = new char[15];         // dynamic array for user .
	int word;                           
	int choice;
	bool hint1 = false, hint2 = false, hint3 = false, hint4 = false;   // tracks whether the one hint per word has been used
	while (true)
	{
		bool notsame = false;
		scrambledwordmenu();        //calling menu of this game 
		if (cin >> choice)                 // checking if the input value is an integer 
		{
			switch (choice)
			{
			case 1:
				// case for hint of any required word .
				cout << "\nFOR WHICH WORD.ENTER WORD NUMBER.\nDONOT ENTER ANY CHARACHTER.\nYOU HAVE ONLY ONE HINT FOR EACH WORD.\n";
				scrambledhint(score, hint1, hint2, hint3, hint4);
				break;
			case 2:

				cout << "\nWHICH WORD\n";           //user input for word number 
				cin >> word;
				switch (word)
				{
				case 1:
					cout << "Enter word:";              // checing if input word is same with the plotted word already .
					cin >> wordname;
					{
						int i = 0;
						for (; wordname[i] != '\0' && word1[i] != '\0'; i++)
						{
							if (word1[i] != wordname[i])
							{
								notsame = true;           // bool value will turns true .
								break;
							}
						}
						if (!notsame && wordname[i] != word1[i])   // catches leftover characters on either side
							notsame = true;
					}
					if (!notsame)                   //if notsam remains false .
					{
						cout << "\nYES,YOUR WORD IS CORRECT (umbrella)\n";
						score++;
					}
					else                    // if word not same it will turn into true.
					{
						cout << "\nNO!\nYOUR SCORE IS DEDUCTED\n";
						score--;                                              // score is also affected .
					}
					break;
				case 2:                                               // same case for every word .
					cout << "Enter word:";
					cin >> wordname;
					{
						int i = 0;
						for (; wordname[i] != '\0' && word2[i] != '\0'; i++)
						{
							if (word2[i] != wordname[i])
							{
								notsame = true;
								break;
							}

						}
						if (!notsame && wordname[i] != word2[i])
							notsame = true;
					}

					if (!notsame)
					{
						cout << "\nYES,YOUR WORD IS CORRECT (jacket)\n";
						score++;
					}
					else
					{
						cout << "\nNO!\nYOUR SCORE IS DEDUCTED\n";
						score--;
					}
					break;
				case 3:
					cout << "Enter word:";
					cin >> wordname;
					{
						int i = 0;
						for (; wordname[i] != '\0' && word3[i] != '\0'; i++)
						{
							if (word3[i] != wordname[i])
							{
								notsame = true;
								break;
							}

						}
						if (!notsame && wordname[i] != word3[i])
							notsame = true;
					}

					if (!notsame)
					{
						cout << "\nYES,YOUR WORD IS CORRECT (right)\n";
						score++;
					}
					else
					{
						cout << "\nNO!\nYOUR SCORE IS DEDUCTED\n";
						score--;
					}
					break;
				case 4:
					cout << "Enter word:";
					cin >> wordname;
					{
						int i = 0;
						for (; wordname[i] != '\0' && word4[i] != '\0'; i++)
						{
							if (word4[i] != wordname[i])
							{
								notsame = true;
								break;
							}

						}
						if (!notsame && wordname[i] != word4[i])
							notsame = true;
					}
					if (!notsame)
					{
						cout << "\nYES,YOUR WORD IS CORRECT (mango)\n";
						score++;
					}
					else
					{
						cout << "\nNO!\nYOUR SCORE IS DEDUCTED\n";
						score--;
					}
					break;

				}
				break;
			case 3:
			{                                            // saves and display the score  
				cout << "\nYOUR COMULATIVE SCORE ACCORDING TO INCREMENT AND DEDUCTION:\n";
				if (score < 0) score = 0;
				ofstream fout("scramblescore");            // storinf the dta into file 
				fout << score;
				cout << score;
				fout.close();
			}
			break;
			case 4:
			{
				cout << "YOUR PREVIOUS LAST SCORE IS :";
				int s_score = 0;                       // openning the fiel and dsiaplay the last saved data  
				ifstream fin("scramblescore");
				fin >> s_score;
				fin.close();
				cout << s_score;
			}
			break;
			case 5:                                       // return to main menu.
				cout << "YOU HAVE EXIT THIS GAME:";
				return;
			default:
				cout << "IVALID CHOICE ENTER AGAIN:";
				cin.ignore();
			}
		}
		else
		{
			cout << "WRONG INPUT GAME HAS ENDED:";
			break;
		}
	}
	delete[] wordname;
}
void MainMenuDisplay()
{
	cout << "\n\n\t\tPress 1 : PLAY SCRAMBLED WORDS   (easy)\n\t\tPress 2 : PLAY WORD SEARCH   (hard)\n";
	cout << "\t\tPress 3 : QUIT GAME\n\n";
	cout << "Enter your choice : ";
}
void WordSearchGame()
{
	int score = 0;
	int option;
	int hint = 5;
	int sx = 0;
	char sy;
	int ex = 0;
	char ey;
	double timetakken = 0;
	const int rows = 20;
	const int clms = 20;
	char grid[20][20] = {};
	bool word1 = false, word2 = false, word3 = false, word4 = false, word5 = false;

	ifstream fin("wordgrid.txt");
	TakingGridfromFile(rows, clms, grid, fin);
	fin.close();

	while (true)
	{
		cout << "\n FIVE WORDS TO FIND\n";
		cout << "\t\tpress 1. HINT\n";
		cout << "\t\tpress 2. START WITH GRID \n\t\tpress 3. SAVE AND DISPLAY SCORE\n\t\tpress 4. SHOW THE LAST HIGHEST SCORE\n\t\tpress 5. RETURN TO MAIN MENU\n";
		cout << "Enter choice:";
		if (cin >> option)
		{
			switch (option)
			{
			case 1:
				Gridhint(hint);
				break;
			case 2:
			{
				displaygrid(rows, clms, grid);   // firstly dispaly grid 
				cout << "\nYou Have only 30 seconds to find the location:\n";
				time_t starttime = time(0);
				cout << "ENTER START COORDINATE:\nIN (x,y) FORM\n";
				cin >> sx >> sy;
				cout << "ENTER END COORDINATE:\nIN (x,y) FORM\n";
				cin >> ex >> ey;
				time_t endtime = time(0);
				timetakken = difftime(endtime, starttime);
				Gridevaluation(timetakken, sx, sy, ex, ey, word1, word2, word3, word4, word5, grid, score);
			}
			break;
			case 3:
			{
				cout << "\nYOUR CURRENT SCORE IS\n";
				if (score < 0) score = 0;
				ofstream fout("savescore");
				cout << score;
				fout << score;
				fout.close();
			}
			break;
			case 4:
			{
				int s_score = 0;
				ifstream fin("savescore");
				fin >> s_score;
				fin.close();
				cout << "YOUR HIGHEST SCORE WAS:" << s_score;
			}
			break;
			case 5:
				cout << "YOU HAVE EXIT THIS GAME!";
				return;
				break;
			default:
				cin.ignore();
				cout << "WRONG INPUT !";
				break;
			}
		}
		else
		{
			break;
		}
	}
}
void Gridhint(int& hint)
{                                   // randomly show hints 
	if (hint == 5)           
	{
		cout << "\nS-ING\n";
		hint--;
	}
	else if (hint == 4)
	{
		cout << "\n-AR-NG\n";
		hint--;
	}
	else if (hint == 3)
	{
		cout << "\nR-LER\n";
		hint--;
	}
	else if (hint == 2)
	{
		cout << "\nB-TT-R\n";
		hint--;
	}
	else if (hint == 1)
	{
		cout << "\n-NA-KE\n";
		hint--;
	}
	else
		cout << "\nNO MORE HINTS\n";
}
void Gridevaluation(double timetakken, int sx, int sy, int ex, int ey, bool& word1, bool& word2, bool& word3, bool& word4, bool& word5, char grid[][20], int& score)
{
	if (timetakken <= 30)              // if you complete your task with in 30 seconds .
	{
		if (sx == 1 && (sy == 'a' || sy == 'A'))
		{
			if (ex == 1 && (ey == 'E' || ey == 'e'))
			{                                    //in every case .
				if (!word1)     //check that wod only one time. 
				{
					cout << "\nCONGRATULATIONS!\nYOU FOUND(snake)\n";
					cout << "YOU COMPLETE THIS TASK WITH IN " << timetakken << " SECONDS\n";
					for (int i = 0;i < 5;i++)  // loop to repace the found word into *,
					{
						grid[0][i] = '*';
					}
					word1 = true;      //bool word check turns into true whrn found one time 
					score++;
				}
				else
					cout << "\nALREADY FOUND!\n";
			}
			else// if column coordinates doesnt match
			{
				cout << "\nWRONG GUESS\n";
				cout << "SCORE DEDUCTED\n";
				score--;
			}
		}
		else if (sx == 2 && (sy == 'H' || sy == 'h'))
		{
			if (ex == 2 && (ey == 'd' || ey == 'D'))
			{
				if (!word2)
				{
					cout << "\nCONGRATULATIONS!\nYOU FOUND(ruler)\n";
					cout << "YOU COMPLETE THIS TASK WITH IN " << timetakken << " SECONDS\n";
					for (int i = 3;i < 8;i++)  // loop to repace the found word into *,
					{
						grid[1][i] = '*';
					}
					word2 = true;
					score++;
				}
				else
					cout << "\nALREADY FOUND!\n";
			}
			else// if column coordinates doesnt match
			{
				cout << "\nWRONG GUESS\n";
				cout << "SCORE DEDUCTED\n";
				score--;
			}
		}
		else if (sx == 4 && (sy == 'f' || sy == 'F'))
		{
			if (ex == 9 && (ey == 'k' || ey == 'K'))
			{
				if (!word3)
				{
					cout << "\nCONGRATULATIONS!\nYOU FOUND(better)\n";
					cout << "YOU COMPLETE THIS TASK WITH IN " << timetakken << " SECONDS\n";
					for (int i = 3;i < 9;i++)     // loop replace it into *,
					{
							grid[i][i+2] = '*';	
					}
					word3 = true;
					score++;
				}
				else
					cout << "\nALREADY FOUND!\n";
			}
			else// if column coordinates doesnt match
			{
				cout << "\nWRONG GUESS\n";
				cout << "SCORE DEDUCTED\n";
				score--;
			}
		}
		else if (sx == 9 && (sy == 'A' || sy == 'a'))
		{
			if (ex == 14 && (ey == 'A' || ey == 'a'))
			{
				if (!word4)
				{
					cout << "\nCONGRATULATIONS!\nYOU FOUND(caring)\n";
					cout << "YOU COMPLETE THIS TASK WITH IN " << timetakken << " SECONDS\n";
					for (int i = 8; i < 14;i++)    // loop replace it into *.
					{
						grid[i][0] = '*';
					}
					word4 = true;
					score++;
				}
				else
					cout << "\nALREADY FOUND!\n";
			}
			else// if column coordinates doesnt match
			{
				cout << "\nWRONG GUESS\n";
				cout << "SCORE DEDUCTED\n";
				score--;
			}
		}
		else if (sx == 7 && (sy == 'r' || sy == 'R'))
		{
			if (ex == 11 && (ey == 'r' || ey == 'R'))
			{
				if (!word5)
				{
					cout << "\nCONGRATULATIONS!\nYOU FOUND(swing)\n";
					cout << "YOU COMPLETE THIS TASK WITH IN " << timetakken << " SECONDS\n";
					for (int i = 6; i < 11;i++)    // loop replace it into *.
					{
						grid[i][17] = '*';
					}
					word5 = true;
					score++;
				}
				else
					cout << "\nALREADY FOUND!\n";
			}
			else   // if column coordinates doesnt match
			{
				cout << "\nWRONG GUESS\n";
				cout << "SCORE DEDUCTED\n";
				score--;
			}
		}
		else     // if row coordinates doesnot match 
		{
			cout << "\nWRONG GUESS\n";
			cout << "SCORE DEDUCTED\n";
			score--;
		}
	}
	else          // if you took more than 30 seconds .
	{
		cout << "\nYOU ARE OUT OF YOUR TIME\nYOU LOST!\n";
		cout << "YOU TOOK " << timetakken << "SECONDS\n";
		cout << "SCORE NOT INCRESED\n";
	}
}
void scrambledwordmenu()
{                                      // menu for word scrambled game .
	cout << "\n\n\t\tTHESE ARE YOUR SCRAMBLED WORDS.YOU NEED TO DECODE THEM: \n";
	cout << "\n\t\tword 1  >>>>> blermlua\n\t\tword 2  >>>>> tkcaej\n\t\tword 3  >>>>> gihtr\n\t\tword 4  >>>>> gnamo\n";
	cout << "\n\t\tpress 1 for HINT (Score will be Deducted-1):\n\t\tpress 2 to Enter Word\n\t\tpress 3 to show and save score\n\t\tpress 4 show last highest score\n\t\tpress 5 RETURN TO MAIN MENU \n\n";
	cout << "Enter:";
}
void scrambledhint(int& score, bool& hint1, bool& hint2, bool& hint3, bool& hint4)
{
	int hntword;
	if (cin >> hntword)      
	{
		switch (hntword)    // hint according to the word number   score will also decrease ,
		{
		case 1:
			if (hint1)
				cout << "\nYOU HAVE ALREADY USED YOUR HINT FOR THIS WORD\n";
			else
			{
				cout << "\n(hint)\n-----WATER PROTECTTOR----\n";
				score--;
				hint1 = true;
			}
			break;
		case 2:
			if (hint2)
				cout << "\nYOU HAVE ALREADY USED YOUR HINT FOR THIS WORD\n";
			else
			{
				cout << "\n(Hint)\n-----SEASONAL WEAR-----\n";
				score--;
				hint2 = true;
			}
			break;
		case 3:
			if (hint3)
				cout << "\nYOU HAVE ALREADY USED YOUR HINT FOR THIS WORD\n";
			else
			{
				cout << "\n(hint)\n------KIND OF A DIRECTION-----\n";
				score--;
				hint3 = true;
			}
			break;
		case 4:
			if (hint4)
				cout << "\nYOU HAVE ALREADY USED YOUR HINT FOR THIS WORD\n";
			else
			{
				cout << "(hint)\n----FRUIT---\n";
				score--;
				hint4 = true;
			}
			break;
		}
	}
	else
	{
		cout << "PLAY AGAIN:";
		return;
	}
}