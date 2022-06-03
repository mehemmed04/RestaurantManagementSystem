#pragma once
#include<iostream>
#include<Windows.h>
#include"Entities.h"
#include"Database.h"
#include"Functions.h"
#include"FileHelper.h"
#include<string>
#include<conio.h>
using namespace std;


class Controller {
	Admin CurrentAdmin;
	Database database;
	int Set[6] = { 7,7,7,7,7,7 }; //DEFAULT COLORS
	int counter = 1;
	char key;

public:
	void INIT() {
		Table t1("T1");
		Table t2("T2");
		Table t3("T3");
		Table t4("T4");
		Table t5("T5");
		Table t6("T6");
		Table t7("T7");
		Table t8("T8");
		Table t9("T9");

		Restaurant r("Zeytin Bagi", "9-cu mkr", "Baku", vector<Admin>{Admin("admin", "admin"), Admin("admin", "12345")  });
		database.restaurant = r;
		database.restaurant.AddTable(t1);
		database.restaurant.AddTable(t2);
		database.restaurant.AddTable(t3);
		database.restaurant.AddTable(t4);
		database.restaurant.AddTable(t5);
		database.restaurant.AddTable(t6);
		database.restaurant.AddTable(t7);
		database.restaurant.AddTable(t8);
		database.restaurant.AddTable(t9);

		Ingredient i1("Cheese", 20.3, 25.2, 3.2, 200.25, 1.5);
		Ingredient i2("Rice", 1, 6, 80, 240.25, 1.5);
		Ingredient i3("Tomato", 5, 1.2, 3.4, 170.25, 0.5);
		Ingredient i4("Salt", 0.1, 0.6, 0, 1, 0.1);
		Ingredient i5("Beef", 23, 123, 12, 549, 15);
		Ingredient i6("Cucumber", 1, 3, 9, 20, 0.5);
		Ingredient i7("Pepper", 0.1, 0.2, 0.5, 0.9, 0.5);
		Ingredient i8("Milk", 10, 30, 90, 200, 3.5);
		Ingredient i9("Chicken", 20, 40, 15, 220, 5.5);

		RecipeItem r1(i1, 3);
		RecipeItem r2(i2, 200);
		RecipeItem r3(i3, 200);
		RecipeItem r4(i4, 2);
		RecipeItem r5(i5, 300);
		RecipeItem r6(i6, 300);
		RecipeItem r7(i7, 300);
		RecipeItem r8(i8, 300);
		RecipeItem r9(i9, 300);

		Meal m1("Dolma", 9.8);
		m1.AddIngredient(r5);
		m1.AddIngredient(r3);

		Meal m2("Plov", 9.6);
		m2.AddIngredient(r2);
		m2.AddIngredient(r4);
		m2.AddIngredient(r3);

		Meal m3("Salat", 4.5);
		m3.AddIngredient(r3);
		m3.AddIngredient(r6);

		Meal m4("Doner", 7.5);
		m4.AddIngredient(r2);
		m4.AddIngredient(r4);
		m4.AddIngredient(r7);

		Meal m5("Xengel", 5.5);
		m5.AddIngredient(r4);
		m5.AddIngredient(r9);
		m5.AddIngredient(r7);

		database.stock.AddIngredient(i1);
		database.stock.AddIngredient(i2);
		database.stock.AddIngredient(i3);
		database.stock.AddIngredient(i4);
		database.stock.AddIngredient(i5);
		database.stock.AddIngredient(i6);
		database.stock.AddIngredient(i7);
		database.stock.AddIngredient(i8);
		database.stock.AddIngredient(i9);
		database.kitchen.AddMeal(m1);
		database.kitchen.AddMeal(m2);
		database.kitchen.AddMeal(m3);
		database.kitchen.AddMeal(m4);
		database.kitchen.AddMeal(m5);
		WriteDatabaseToFile(database);
	}

	void StartProject() {
		INIT();
		Start();
	}
	bool IsReadyOrder = false;
	void Start() {
		counter = 1;
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;

#pragma region ConsoleFontSizeController
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;                   // Width of each character in the font
		cfi.dwFontSize.Y = 24;                  // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
#pragma endregion


		while (true)
		{
			system("cls");

			ShowHomeMenu();
			key = _getch();

			if (key == 72 && (counter == 2)) counter--; // 72 up arrow key
			else if (key == 80 && (counter == 1)) counter++; // 80 down arrow key

			if (key == '\r') {// carriage return  = Enter
				if (counter == 1) {
					system("cls");
					string username; string password;
					SetCordinates(50, 12);
					cout << "Enter Username : "; getline(cin, username);
					SetCordinates(50, 13);
					cout << "Enter Password : ";
#pragma region EnteringPassword

					char d;
					int i = 0;
					while (true)
					{
						d = _getch();
						if (d == '\r')
							break;
						if (d == 8)
						{
							cout << "\b \b";
							password[i] = '\0';
						}
						else
							cout << "*";
						password.push_back(d);
						i++;
					}
					password[i] = '\0';
#pragma endregion

					if (IsAdmin(username, password)) {
						CurrentAdmin = GetAdmin(username, password);
						AdminPanel(CurrentAdmin);
					}
					else {
						system("cls");
						SetCordinates(60, 12);
						color(12);
						cout << "ACCESS DENIED" << endl;
						color(7);
					}
					system("pause");
				}
				else if (counter == 2) {
					ClientPanel();
				}
			}
			Set[0] = 7;
			Set[1] = 7;
			if (counter == 1) {
				Set[0] = 12; // Color RED
			}
			else if (counter == 2) {
				Set[1] = 12;
			}

		}


	}


	void ShowHomeMenu() {
		// admin && client select
		SetCordinates(60, 12);
		color(Set[0]);
		cout << "ADMIN" << endl;
		SetCordinates(60, 13);
		color(Set[1]);
		cout << "CLIENT" << endl;

	}


	bool IsAdmin(const string& username, const string& password) {

		for (auto admin : database.restaurant.GetAdmins()) {
			if (admin.GetUsername() == username &&
				admin.GetPassword() == password) {
				return true;
			}
		}
		return false;
	}

	Admin GetAdmin(const string& username, const string& password) {
		for (auto admin : database.restaurant.GetAdmins()) {
			if (admin.GetUsername() == username &&
				admin.GetPassword() == password) {
				return admin;
			}
		}
		return Admin();
	}

	void AdminPanel(Admin& admin) {
		auto CurrentAdmin = admin;
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		color(Set[0]);
		counter = 2;
		while (true)
		{
			system("cls");
			SetCordinates(60, 12); color(Set[0]); cout << "KITCHEN" << endl;
			SetCordinates(60, 13); color(Set[1]); cout << " STOCK " << endl;
			SetCordinates(60, 14); color(Set[2]); cout << " BACK " << endl;
			key = _getch();

			if (key == 72 && (counter >= 2 && counter <= 3)) counter--; // 72 up arrow key
			if (key == 80 && (counter >= 1 && counter <= 2)) counter++; // 80 down arrow key

			if (key == '\r') {// carriage return  = Enter
				if (counter == 1) {
					KitchenPanel();
				}
				else if (counter == 2) {
					StockPanel();
				}
				else if (counter == 3) {
					Start();
				}
			}
			Set[0] = 7;
			Set[1] = 7;
			Set[2] = 7;
			if (counter == 1) {
				Set[0] = 12; // Color RED
			}
			else if (counter == 2) {
				Set[1] = 12;
			}
			else if (counter == 3) {
				Set[2] = 12;
			}


		}

	}

	void KitchenPanel() {
		counter = 3;
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		Set[4] = 7;
		Set[5] = 7;
		color(Set[0]);
		while (true)
		{
			system("cls");
			SetCordinates(55, 10);
			color(Set[0]);
			cout << "Show All Orders " << endl;
			SetCordinates(55, 11);
			color(Set[1]);
			cout << "Show All Meals  " << endl;
			SetCordinates(55, 12);
			color(Set[2]);
			cout << "   Add Meal     " << endl;
			SetCordinates(55, 13);
			color(Set[3]);
			cout << "  Update Meal    " << endl;
			SetCordinates(55, 14);
			color(Set[4]);
			cout << "  Show Stock   " << endl;
			SetCordinates(55, 15);
			color(Set[5]);
			cout << "     Back   " << endl;


			key = _getch();
			if (key == 80 && (counter >= 1 && counter <= 2)) counter++; // 80 down arrow key

			else if (key == 72 && (counter >= 2 && counter <= 3)) counter--; // 72 up arrow key
			else if (key == 80 && (counter >= 2 && counter <= 3)) counter++; // 80 down arrow key

			else if (key == 72 && (counter >= 3 && counter <= 4)) counter--; // 72 up arrow key
			else if (key == 80 && (counter >= 3 && counter <= 4)) counter++; // 80 down arrow key

			else if (key == 72 && (counter >= 4 && counter <= 5)) counter--; // 72 up arrow key
			else if (key == 80 && (counter >= 4 && counter <= 5)) counter++; // 80 down arrow key

			else if (key == 72 && (counter >= 5 && counter <= 6)) counter--; // 72 up arrow key



			if (key == '\r') {// carriage return  = Enter
				if (counter == 1) {
					system("cls");
					if (!IsReadyOrder) {
						database.kitchen.ShowAllOrders();
					}
					else cout << "There is not order." << endl;
					system("pause");
					int select = 0;
					//Table CurrentTable;
					//Table* CurrentTablePtr;
					cout << "Accept [1],  Reject [2] : "; cin >> select;
					if (select == 1) {
						cout << "Enter Table number : ";
						string Table_no;
						cin.ignore();
						cin.clear();
						getline(cin, Table_no);
						//Table* CurrentTablePtr = database.restaurant.GetTableByNoPtr(Table_no);
						Table CurrentTable = database.restaurant.GetTableByNo(Table_no);
						CurrentTable.SetMessageFromKitchen("Your request accepted");
						CurrentTable.IsReady = true;
						database.restaurant.SetTable(CurrentTable);
						IsReadyOrder = true;
					}
					else if (select == 2) {
						cout << "Enter Table number : ";
						string Table_no;
						cin.ignore();
						cin.clear();
						getline(cin, Table_no);
						Table CurrentTable = database.restaurant.GetTableByNo(Table_no);
						CurrentTable = database.restaurant.GetTableByNo(Table_no);
						CurrentTable.SetMessageFromKitchen("Your request rejected");
						CurrentTable.IsReady = true;
					}
					else {
						break;
					}


				}
				else if (counter == 2) {
					system("cls");
					database.kitchen.ShowAllMeals();
					system("pause");
				}
				else if (counter == 3) {
					Meal meal = database.kitchen.GetMeal();
					database.kitchen.AddMeal(meal);
					cout << "Meal added succesfully" << endl;
				}
				else if (counter == 4) {
					database.kitchen.UpdateMeal();
				}
				else if (counter == 5) {
					system("cls");
					database.kitchen.ShowStock(database.stock);
					system("pause");
				}
				else if (counter == 6) {
					AdminPanel(CurrentAdmin);
				}
			}
			Set[0] = 7;
			Set[1] = 7;
			Set[2] = 7;
			Set[3] = 7;
			Set[4] = 7;
			Set[5] = 7;
			if (counter == 1) {
				Set[0] = 12; // Color RED
			}
			else if (counter == 2) {
				Set[1] = 12;
			}
			else if (counter == 3) {
				Set[2] = 12;
			}
			else if (counter == 4) {
				Set[3] = 12;
			}
			else if (counter == 5) {
				Set[4] = 12;
			}
			else if (counter == 6) {
				Set[5] = 12;
			}


		}
	}

	void StockPanel() {
		counter = 3;
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		Set[4] = 7;
		Set[5] = 7;
		color(Set[0]);

		while (true)
		{

			system("cls");
			SetCordinates(50, 12);
			color(Set[0]);
			cout << "Show All Ingredients" << endl;
			SetCordinates(50, 13);
			color(Set[1]);
			cout << "   Add Igredient    " << endl;
			SetCordinates(50, 14);
			color(Set[2]);
			cout << "  Delete ingredient " << endl;
			SetCordinates(50, 15);
			color(Set[3]);
			cout << " Increase Ingredient" << endl;
			SetCordinates(50, 16);
			color(Set[4]);
			cout << " Decrease Ingredient" << endl;
			color(Set[5]);
			SetCordinates(50, 17);
			cout << "        Back        " << endl;
			key = _getch();

			if (key == 80 && (counter >= 1 && counter <= 2)) counter++; // 80 down arrow key

			else if (key == 72 && (counter >= 2 && counter <= 3)) counter--; // 72 up arrow key
			else if (key == 80 && (counter >= 2 && counter <= 3)) counter++; // 80 down arrow key

			else if (key == 72 && (counter >= 3 && counter <= 4)) counter--; // 72 up arrow key
			else if (key == 80 && (counter >= 3 && counter <= 4)) counter++; // 80 down arrow key

			else if (key == 72 && (counter >= 4 && counter <= 5)) counter--; // 72 up arrow key
			else if (key == 80 && (counter >= 4 && counter <= 5)) counter++; // 80 down arrow key

			else if (key == 72 && (counter >= 5 && counter <= 6)) counter--; // 72 up arrow key



			if (key == '\r') {// carriage return  = Enter
				if (counter == 1) {
					system("cls");
					database.stock.ShowAllIngredients();
					system("pause");
				}
				else if (counter == 2) {
					auto ingredient = database.stock.GetIngredient();
					database.stock.AddIngredient(ingredient);
					system("cls");
					SetCordinates(50, 13);
					cout << "Ingredient Added Succesfully" << endl;
					system("pause");
				}
				else if (counter == 3) {
					string ingredient_name;
					cout << "Enter Ingredient Name : "; getline(cin, ingredient_name);
					auto ingredient = database.stock.GetIngredientByName(ingredient_name);

					database.stock.DeleteIngredient(ingredient);
					system("cls");
					SetCordinates(50, 13);
					cout << "Ingredient Deleted Succesfully" << endl;
					system("pause");
				}
				else if (counter == 4) {
					cout << "Enter ingredient name : "; string name;
					getline(cin, name);
					database.stock.DecraseIngredientPrice(name);
				}
				else if (counter == 5) {
					cout << "Enter ingredient name : "; string name;
					getline(cin, name);
					database.stock.IncreaseIngredientPrice(name);
				}
				else if (counter == 6) {
					AdminPanel(CurrentAdmin);
				}
			}
			Set[0] = 7;
			Set[1] = 7;
			Set[2] = 7;
			Set[3] = 7;
			Set[4] = 7;
			Set[5] = 7;
			if (counter == 1) {
				Set[0] = 12; // Color RED
			}
			else if (counter == 2) {
				Set[1] = 12;
			}
			else if (counter == 3) {
				Set[2] = 12;
			}
			else if (counter == 4) {
				Set[3] = 12;
			}
			else if (counter == 5) {
				Set[4] = 12;
			}
			else if (counter == 6) {
				Set[5] = 12;
			}
		}

	}

	void ClientPanel() {
		system("cls");
		color(7);
		SetCordinates(55, 12);
		string table_no;
		cout << "Enter Table No : "; getline(cin, table_no);

		Table* CurrentTablePtr = database.restaurant.GetTableByNoPtr(table_no);

		if (CurrentTablePtr != nullptr) {
			Table CurrentTable = database.restaurant.GetTableByNo(table_no);
			system("cls");
			database.kitchen.ShowAllMeals();

			if (!IsReadyOrder) {
				vector<Meal>meals;
				int choose;
				do
				{
					do
					{

					cout << "If you want to see calories press 1 : "; cin >> choose; cin.ignore(); cin.clear();
					if (choose == 1) {
						string meal_name;
						cout << "Enter Meal Name : " << endl;
						getline(cin, meal_name);
						Meal CurrentMeal = database.kitchen.GetMealByName(meal_name);
						CurrentMeal.PrintRecipeWithMicro();
					}
					else break;
					} while (true);

					string meal_name;
					cout << "Enter Meal Name : " << endl;
					getline(cin, meal_name);
					Meal* CurrentMealPtr = database.kitchen.GetMealPtrByName(meal_name);
					if (CurrentMealPtr != nullptr) {
						Meal CurrentMeal = database.kitchen.GetMealByName(meal_name);
						cout << "Do yu want to continue to order Yes(1) : " << endl;
						cin >> choose;
						cin.ignore();
						cin.clear();
						meals.push_back(CurrentMeal);
						if (choose == 1) {
							continue;
						}
						else {
							break;
						}
					}
					else {
						cout << "There is not meal by this name. Try again." << endl;
					}
				} while (true);
				Order ord(CurrentTable.GetTableNo(), meals);
				database.restaurant.GetTableByNoPtr(table_no)->AddOrder(ord);
				database.kitchen.AddOrder(ord);
				WriteDatabaseToFile(database);
			}
			else {
				system("cls");
				cout << "Message : " << "Your meal is ready" << endl;
				system("pause");

				cout << "Enter Meal name : "; string meal_name; getline(cin, meal_name);
				cout << "Enter rating 1-10 for meal : ";
				int rating;
				cin >> rating;
				auto meal = database.kitchen.GetMealByName(meal_name);
				meal.AddRating(rating);
			}

			system("pause");


		}
		else {
			system("cls");
			SetCordinates(45, 12);
			color(12);
			cout << "There is not table by this name, Try agin." << endl;
			color(7);
			system("pause");
		}

	}


};