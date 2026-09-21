#include <iostream>
using namespace std;
int main()
{
	int  index = 50;                //  total used index 
	int del_num, pro_id;
	float start_p;
	const int size = 100;
	int ID[size]{ 109,107,101,102,103,106,105,108,104,110,111,115,113,112,118,116,117,119,114,120,125,122,121,123,124,130,129,126,128,127,137,133,131,132,134,136,135,139,138,140,150,141,145,142,143,146,144,147,148,149 };
	int Qty[size]{ 20,20,20,10,40,23,21,34,5,10,12,23,50,66,80,34,23,21,34,56,30,10,50,5,9,2,100,150,70,3,300,150,45,75,80,130,410,70,20,15,4,2,10,90,6,4,8,1,100,90 };
	float price[size]{ 10.5,500,350,100,100,230,560,900,1000,340,300,50,55,40,200,200,150,250,500,550,7,10,30,15,22,15,45,50,44,60,11,15.5,20,10,45,70,10,60,50,45.5,22,100,70,30,20,60,24,27.5,85,3 };
	float total[size]{ 210,10000,7000,1000,4000,5290,11760,30600,5000,3400,3600,1150,2750,2640,16000,6800,3450,5250,17000,30800,210,100,1500,75,198,30,4500,7500,3080,180,3300,2325,900,750,3600,9100,4100,4200,1000,682.5,88,200,700,2700,120,240,192,27.5,8500,270 };
	char ch[size]{ 'E','F','T','C','O','T','O','E','F','C','C','O','T','O','T','C','C','F','E','E','T','O','F','E','C','C','O','T','O','T','F','E','O','E','T','F','O','T','T','E','C','F','C','T','C','C','O','F','T','C' };

	int menu_choice;
	bool flag = true;

	cout << "\t\t\tINVENTORY MANAGEMENT SYSTEM\n\n\n";
	// this loop is to continue asking 
   //it will terminate when e E is pressed
	while (true)
	{
		flag = true;                 // reset at the start of every menu round
		cout << "Press 1. Sort and Display all Records by Product ID(Ascending)\n";
		cout << "Press 2. Sort and Display all Records by Product ID(Descending)\n";
		cout << "Press 3. Sort and Display all Records by Total Value(Ascending)\n";
		cout << "Press 4. Sort and Display all Records by Total Value(Descending)\n";
		cout << "Press 5. Add a New Product Record\n";
		cout << "Press 6. Delete a Product Record Based on Product ID\n";
		cout << "Press 7. Display Products with Quantity Greater than or Equal to X(Descending)\n";
		cout << "Press 8. Display Products with Quantity Greater than or Equal to X(Ascending)\n";
		cout << "Press 9. Display Products with Total Value Greater than or Equal to Y(Descending)\n";
		cout << "Press 10. Display Products with Total Value Greater than or Equal to Y(Ascending)\n";
		cout << "Press 11. Update Quantity or Unit Price for a Product Based on Product ID\n\n";
		cout << "          Press E to Exit Program\n\n ";
		cout << "What do you want please Enter \n";
		cout << ">>>";

		if (cin >> menu_choice)                               // if menu choice is an integer 
		{                                    //user selection

			switch (menu_choice)
			{
			case 1:                                    // a bubble sort to display the record in ascending order 
				for (int idx = 0;idx < index;idx++)
				{
					int temp_idx = 0;
					for (int j = 1;j <= index - idx - 1; j++)
					{
						if (ID[temp_idx] > ID[j])   //just ID is sorted in ascending order ,all the other info is sorted with respect to ID 
						{                                    // information is linked with product ID
							double temp = ID[temp_idx];
							ID[temp_idx] = ID[j];
							ID[j] = temp;

							temp = Qty[temp_idx];
							Qty[temp_idx] = Qty[j];
							Qty[j] = temp;

							temp = price[temp_idx];
							price[temp_idx] = price[j];
							price[j] = temp;

							temp = total[temp_idx];
							total[temp_idx] = total[j];
							total[j] = temp;

							temp = ch[temp_idx];
							ch[temp_idx] = ch[j];
							ch[j] = temp;
						}
						temp_idx++;
					}
				}
				cout << endl << endl;
				cout << " Your products record in ascending order By Product ID \n";
				cout << endl;
				cout << "product ID\tQuantity\tPrice\tTotal\tCategory";
				cout << endl;
				for (int i = 0; i < index; i++)    // loop to print the record in proper form
				{
					cout << "   " << ID[i] << "\t\t  " << Qty[i] << "\t\t" << price[i] << "\t" << total[i] << "\t  " << ch[i] << "\n";
				}
				cout << endl << endl;
				break;
			case 2:
				for (int idx = 0;idx < index;idx++)
				{
					int temp_idx = 0;                       //as above but sorting in descending order 
					for (int j = 1;j <= index - idx - 1; j++)
					{
						if (ID[temp_idx] < ID[j])
						{
							double temp = ID[temp_idx];
							ID[temp_idx] = ID[j];
							ID[j] = temp;

							temp = Qty[temp_idx];
							Qty[temp_idx] = Qty[j];
							Qty[j] = temp;

							temp = price[temp_idx];
							price[temp_idx] = price[j];
							price[j] = temp;

							temp = total[temp_idx];
							total[temp_idx] = total[j];
							total[j] = temp;

							temp = ch[temp_idx];
							ch[temp_idx] = ch[j];
							ch[j] = temp;
						}
						temp_idx++;
					}
				}
				cout << endl << endl;
				cout << " Your products record in descending order By Product ID\n";
				cout << endl;
				cout << "[Product ID]\tQuantity\tPrice\tTotal\tCategory";
				cout << endl;
				for (int i = 0; i < index; i++)     //loop to print info in a proper form
				{
					cout << "   " << ID[i] << "\t\t  " << Qty[i] << "\t\t" << price[i] << "\t" << total[i] << "\t  " << ch[i] << "\n";
				}
				cout << endl << endl;
				break;
			case 3:
				for (int idx = 0;idx < index;idx++)      //sorting with respect to  Total value in ascending order 
				{
					int temp_idx = 0;
					for (int j = 1;j <= index - idx - 1; j++)
					{
						if (total[temp_idx] > total[j])
						{
							double temp = total[temp_idx];
							total[temp_idx] = total[j];
							total[j] = temp;

							temp = ID[temp_idx];
							ID[temp_idx] = ID[j];
							ID[j] = temp;

							temp = Qty[temp_idx];
							Qty[temp_idx] = Qty[j];
							Qty[j] = temp;

							temp = price[temp_idx];
							price[temp_idx] = price[j];
							price[j] = temp;

							temp = ch[temp_idx];
							ch[temp_idx] = ch[j];
							ch[j] = temp;
						}
						temp_idx++;
					}
				}
				cout << endl << endl;
				cout << " Your products record in ascending order By Total Value \n";
				cout << endl;
				cout << "product ID\tQuantity\tPrice\t[Total]\tCategory";
				cout << endl;
				for (int i = 0; i < index; i++)
				{
					cout << "   " << ID[i] << "\t\t  " << Qty[i] << "\t\t" << price[i] << "\t " << total[i] << "\t  " << ch[i] << "\n";
				}
				cout << endl << endl;
				break;
			case 4:
				for (int idx = 0;idx < index;idx++)      // as above but in descending order .
				{
					int temp_idx = 0;
					for (int j = 1;j <= index - idx - 1; j++)
					{
						if (total[temp_idx] < total[j])
						{
							double temp = total[temp_idx];          // swapping that number according to the order .
							total[temp_idx] = total[j];
							total[j] = temp;

							temp = ID[temp_idx];
							ID[temp_idx] = ID[j];
							ID[j] = temp;

							temp = Qty[temp_idx];
							Qty[temp_idx] = Qty[j];
							Qty[j] = temp;

							temp = price[temp_idx];
							price[temp_idx] = price[j];
							price[j] = temp;

							temp = ch[temp_idx];
							ch[temp_idx] = ch[j];
							ch[j] = temp;
						}
						temp_idx++;
					}
				}
				cout << endl << endl;
				cout << " Your products record in descending order By Total Value \n";
				cout << endl;
				cout << "product ID\tQuantity\tPrice\t[Total]\tCategory";
				cout << endl;
				for (int i = 0; i < index; i++)
				{
					cout << "   " << ID[i] << "\t\t  " << Qty[i] << "\t\t" << price[i] << "\t " << total[i] << "\t  " << ch[i] << "\n";
				}
				cout << endl << endl;
				break;
			case 5:                                 // adding a new record
				cout << "Add a new product record \n\n";
				if (index >= size)                    // the arrays can hold only 100 records
				{
					cout << "The inventory is full (" << size << " products). Delete a record first.\n\n";
					break;
				}
				cout << "Enter product ID : ";                        // ID is added in ID array
				cin >> ID[index];
				if (ID[index] <= 0)                   // product ID must be a positive number
				{
					cout << "\nProduct ID must be a positive number \n\n";
					break;
				}
				for (int i = 0; i < index; i++)           // every product must have a unique ID 
				{
					if (ID[i] == ID[index])                 // check that the product does not already exist
					{
						cout << "\nEnter a unique ID, This ID already exist \n";
						flag = false;
						break;
					}
				}
				if (flag)                      // if no product has the same ID, add the new data with the unique ID 
				{
					cout << "Enter quantity in stock : ";
					cin >> Qty[index];                       // Quantity is added in Qty array 
					cout << "Enter its unit Price : ";
					cin >> price[index];                        // price is added in price array 
					if (Qty[index] < 0 || price[index] < 0)     // negative values are not allowed
					{
						cout << "\nQuantity and price cannot be negative. Record not added \n\n";
						break;
					}
					total[index] = Qty[index] * price[index];        // total value = Qty * price
					cout << "The total value is " << total[index] << endl;
					cout << "\nE for Electronics\nF for Food\nC for Clothing\nT for Toys\nO for Others\n";
					cout << "\nEnter your category choice : ";
					cin >> ch[index];
					if (ch[index] >= 'a' && ch[index] <= 'z')     // a small letter is also accepted
						ch[index] = ch[index] - 32;
					if (ch[index] != 'E' && ch[index] != 'F' && ch[index] != 'C' && ch[index] != 'T' && ch[index] != 'O')
					{
						cout << "\nInvalid category. Record not added \n\n";
						break;
					}
					index++;                       // increment in the total used index
				}
				cout << endl;
				cout << endl;
				break;
			case 6:
				cout << endl << endl;
				cout << "Enter the Product ID want to delete : ";
				cin >> del_num;                     // deleting all Data linked to that ID
				for (int i = 0;i < index;i++)      //loop check for the specific index in which that ID is placed 
				{
					if (ID[i] == del_num)
					{
						for (int j = i; j < index - 1;j++)     // loop to delete  by algorithm 
						{                                             // replacing that value of index with the next value 
							ID[j] = ID[j + 1];
							Qty[j] = Qty[j + 1];
							price[j] = price[j + 1];               // replacing all data from that specific index 
							total[j] = total[j + 1];
							ch[j] = ch[j + 1];
						}
						index--;        //decrement of the total index were used 
						flag = false;
						cout << "The product record has been deleted.\n";
						break;
					}
				}
				if (flag)    // if statement with flag if there is no existance of that number 
					cout << "The product does not exist with this product ID " << del_num << endl << endl;
				cout << endl;
				break;
			case 7:
				cout << endl;
				cout << "From which Quantity You want to see information : ";
				cin >> start_p;
				for (int idx = 0;idx < index;idx++)               // Display Products with Quantity Greater than or Equal to user input  Descending
				{                                                   // sorting array in descending order
					int temp_idx = 0;
					for (int j = 1;j <= index - idx - 1; j++)
					{
						if (Qty[temp_idx] < Qty[j])
						{
							double temp = Qty[temp_idx];
							Qty[temp_idx] = Qty[j];
							Qty[j] = temp;

							temp = ID[temp_idx];
							ID[temp_idx] = ID[j];
							ID[j] = temp;

							temp = price[temp_idx];
							price[temp_idx] = price[j];
							price[j] = temp;

							temp = total[temp_idx];
							total[temp_idx] = total[j];
							total[j] = temp;

							temp = ch[temp_idx];
							ch[temp_idx] = ch[j];
							ch[j] = temp;
						}
						temp_idx++;
					}
				}
				cout << endl << endl;
				cout << "Products with Quantity greater than or equal to " << start_p << " in descending order \n";
				cout << endl;
				cout << "Product ID\t[Quantity]\tPrice\tTotal\tCategory";
				cout << endl;
				for (int i = 0; i < index; i++)         // print every product with Quantity >= the user input
				{
					if (Qty[i] >= start_p)
					{
						flag = false;
						cout << "   " << ID[i] << "\t\t  " << Qty[i] << "\t\t" << price[i] << "\t" << total[i] << "\t  " << ch[i] << "\n";
					}
				}
				if (flag)                                    // if no product matches
					cout << "No product found with Quantity greater than or equal to " << start_p << "\n";
				cout << endl << endl;
				break;
			case 8:
				cout << endl;
				cout << "From which Quantity You want to see information : ";
				cin >> start_p;                                            // Display Products with Quantity Greater than or Equal to user input  
				for (int idx = 0;idx < index;idx++)                       // sorting array in ascending order 
				{
					int temp_idx = 0;
					for (int j = 1;j <= index - idx - 1; j++)
					{
						if (Qty[temp_idx] > Qty[j])
						{
							double temp = Qty[temp_idx];
							Qty[temp_idx] = Qty[j];
							Qty[j] = temp;

							temp = ID[temp_idx];
							ID[temp_idx] = ID[j];
							ID[j] = temp;

							temp = price[temp_idx];
							price[temp_idx] = price[j];
							price[j] = temp;

							temp = total[temp_idx];
							total[temp_idx] = total[j];
							total[j] = temp;

							temp = ch[temp_idx];
							ch[temp_idx] = ch[j];
							ch[j] = temp;
						}
						temp_idx++;
					}
				}
				cout << endl << endl;
				cout << "Products with Quantity greater than or equal to " << start_p << " in ascending order \n";
				cout << endl;
				cout << "Product ID\t[Quantity]\tPrice\tTotal\tCategory";
				cout << endl;
				for (int i = 0; i < index; i++)         // print every product with Quantity >= the user input
				{
					if (Qty[i] >= start_p)
					{
						flag = false;
						cout << "   " << ID[i] << "\t\t  " << Qty[i] << "\t\t" << price[i] << "\t" << total[i] << "\t  " << ch[i] << "\n";
					}
				}
				if (flag)                                    // if no product matches
					cout << "No product found with Quantity greater than or equal to " << start_p << "\n";
				cout << endl << endl;
				break;
			case 9:
				cout << endl;
				cout << "From which Total value You want to see information : ";
				cin >> start_p;
				for (int idx = 0;idx < index;idx++)            // displaying products with respect to  total values . descendig order 
				{                                                    // algorithm similar as above
					int temp_idx = 0;
					for (int j = 1;j <= index - idx - 1; j++)
					{
						if (total[temp_idx] < total[j])
						{
							double temp = Qty[temp_idx];
							Qty[temp_idx] = Qty[j];
							Qty[j] = temp;

							temp = ID[temp_idx];
							ID[temp_idx] = ID[j];
							ID[j] = temp;

							temp = price[temp_idx];
							price[temp_idx] = price[j];
							price[j] = temp;

							temp = total[temp_idx];
							total[temp_idx] = total[j];
							total[j] = temp;

							temp = ch[temp_idx];
							ch[temp_idx] = ch[j];
							ch[j] = temp;
						}
						temp_idx++;
					}
				}
				cout << endl << endl;
				cout << "Products with Total value greater than or equal to " << start_p << " in descending order \n";
				cout << endl;
				cout << "Product ID\tQuantity\tPrice\t[Total]\tCategory";
				cout << endl;
				for (int i = 0; i < index; i++)         // print every product with Total value >= the user input
				{
					if (total[i] >= start_p)
					{
						flag = false;
						cout << "   " << ID[i] << "\t\t  " << Qty[i] << "\t\t" << price[i] << "\t" << total[i] << "\t  " << ch[i] << "\n";
					}
				}
				if (flag)                                    // if no product matches
					cout << "No product found with Total value greater than or equal to " << start_p << "\n";
				cout << endl << endl;
				break;
			case 10:
				cout << endl;
				cout << "From which Total value You want to see information : ";
				cin >> start_p;                                   // displaying products with respect to  total values . ascending order
				for (int idx = 0;idx < index;idx++)                 // algorithm similar as above
				{
					int temp_idx = 0;
					for (int j = 1;j <= index - idx - 1; j++)
					{
						if (total[temp_idx] > total[j])
						{
							double temp = Qty[temp_idx];
							Qty[temp_idx] = Qty[j];
							Qty[j] = temp;

							temp = ID[temp_idx];
							ID[temp_idx] = ID[j];
							ID[j] = temp;

							temp = price[temp_idx];
							price[temp_idx] = price[j];
							price[j] = temp;

							temp = total[temp_idx];
							total[temp_idx] = total[j];
							total[j] = temp;

							temp = ch[temp_idx];
							ch[temp_idx] = ch[j];
							ch[j] = temp;
						}
						temp_idx++;
					}
				}
				cout << endl << endl;
				cout << "Products with Total value greater than or equal to " << start_p << " in ascending order \n";
				cout << endl;
				cout << "Product ID\tQuantity\tPrice\t[Total]\tCategory";
				cout << endl;
				for (int i = 0; i < index; i++)         // print every product with Total value >= the user input
				{
					if (total[i] >= start_p)
					{
						flag = false;
						cout << "   " << ID[i] << "\t\t  " << Qty[i] << "\t\t" << price[i] << "\t" << total[i] << "\t  " << ch[i] << "\n";
					}
				}
				if (flag)                                    // if no product matches
					cout << "No product found with Total value greater than or equal to " << start_p << "\n";
				cout << endl << endl;
				break;
			case 11:
				cout << endl;                           // changing value for the particular product ID
				cout << " Enter the Product ID of which you want to change Data : ";
				cin >> pro_id;
				for (int idx = 0; idx < index; idx++)                //loop checking for the existence of that product 
				{
					if (ID[idx] == pro_id)
					{                                 // if exist show all the previous value , at that particular index
						cout << "your previous data is \n\n";
						cout << "Product ID : " << ID[idx] << endl;
						cout << "Quantity : " << Qty[idx] << endl;
						cout << "Price : " << price[idx] << endl;
						cout << "Total : " << total[idx] << endl;
						cout << "category : " << ch[idx] << endl;
						cout << endl << endl;                                // asking for the new value to enter 
						cout << "You can just change the Price and Quantity of the Product the Total value will update Automatically\n\n";
						int old_qty = Qty[idx];
						float old_price = price[idx];
						cout << "Enter new Quantity : ";
						cin >> Qty[idx];                                // storing new values in that particular index 
						cout << "Enter new price : ";
						cin >> price[idx];
						if (Qty[idx] < 0 || price[idx] < 0)             // negative values are not allowed
						{
							Qty[idx] = old_qty;
							price[idx] = old_price;
							cout << "\nQuantity and price cannot be negative. Nothing was changed \n\n";
						}
						else
						{
							total[idx] = Qty[idx] * price[idx];
							cout << "The new total value is " << total[idx] << endl;
						}
						flag = false;
						break;                                               // updated with the new values ,
					}

				}
				if (flag)
					cout << "\nProduct with this ID does not exist \n\n";
				break;
			default:
				cout << "\n\nYou have entered wrong input ....\n\n";
				cout << endl;
				break;
			}
		}
		else                                   // this else statement is to detect that the menu choice is a character and it will terminate the loop  
		{
			cout << "\nYou have exited the program\n";
			break;
		}

	}
	return 0;
}