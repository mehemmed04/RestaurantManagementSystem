#pragma once
#include<fstream>
#include<iostream>
#include"Start.h"
#include"Database.h"
using namespace std;

Database ReadDatabaseFromFile() {
	Database database;
	ifstream fin("Database.txt", ios::in);
	Restaurant r; string name; string adress; string city; double budget;
	fin >> name >> adress >> city >> budget;
	int admin_count;
	fin >> admin_count;
	r.SetName(name); r.SetCity(city); r.SetAdress(adress); r.SetBudget(budget);
	for (size_t i = 0; i < admin_count; i++)
	{
		string username; string password;
		fin >> username >> password;
		r.AddAdmin(Admin(username, password));
	}
	int table_count;
	fin >> table_count;

	for (size_t i = 0; i < table_count; i++)
	{
		string Table_no; string isready;
		fin >> Table_no >> isready;
		bool IsReady; if (isready == "ready") IsReady = true; else IsReady = false;
		r.AddTable(Table(Table_no, IsReady));
	}

	Stock s;
	int ingredient_count = 0;
	fin >> ingredient_count;
	for (size_t i = 0; i < ingredient_count; i++)
	{
		string name;
		double fats;
		double protein;
		double carbohydrates;
		double kcal;
		double price;
		fin >> name >> kcal >> fats >> protein >> carbohydrates >> price;
		s.AddIngredient(Ingredient(name, fats, protein, carbohydrates, kcal, price));
	}

	Kitchen k;
	int meal_size;
	fin >> meal_size;
	for (size_t i = 0; i < meal_size; i++)
	{
		string name; double rating; double price; int item_count;
		fin >> name >> rating >> price >> item_count;
		Meal m(name, rating, price);
		for (size_t i = 0; i < item_count; i++)
		{
			string i_name; double amount;
			fin >> i_name >> amount;
			m.AddIngredient(RecipeItem(Ingredient(i_name), amount));
		}
		k.AddMeal(m);
	}
	int order_count = 0;
	fin >> order_count;
	for (size_t i = 0; i < order_count; i++)
	{
		string Table_no; string isready;
		fin >> Table_no >> isready;
		bool IsReady; if (isready == "ready") IsReady = true; else IsReady = false;

		int meal_count = 0;
		fin >> meal_count;
		vector<Meal> meals;
		for (size_t i = 0; i < meal_count; i++)
		{
			string name; double rating; double price; int item_count;
			fin >> name >> rating >> price >> item_count;
			Meal m(name, rating, price);
			for (size_t i = 0; i < item_count; i++)
			{
				string i_name; double amount;
				fin >> i_name >> amount;
				m.AddIngredient(RecipeItem(Ingredient(i_name), amount));
			}
			meals.push_back(m);
		}
		k.AddOrder(Order(Table_no, meals));

	}
	database.restaurant = r;
	database.kitchen = k;
	database.stock = s;
	return database;
}
void WriteDatabaseToFile(Database& database) {
	Restaurant r = database.restaurant;
	ofstream fout("Database.txt", ios::out);
	fout << r.GetName() << "   " << r.GetAdress() << "   " << r.GetCity() << "   " << r.GetBudget() << "\n";
	fout << r.GetAdmins().size() << "\n";
	for (auto admin : r.GetAdmins())
	{
		fout << admin.GetUsername() << "   " << admin.GetPassword() << "\n";
	}

	fout << r.GetTables().size() << "\n";
	for (auto table : r.GetTables()) {
		fout << table.GetTableNo() << "  ";
		if (table.IsReady) fout << "ready" << "   ";
		else fout << "not-ready" << "   ";
		fout << "\n";
	}

	//stock

	Stock s = database.stock;

	fout << s.GetIngredients().size() << "\n";
	for (auto i : s.GetIngredients()) {
		fout << i.GetName() << "  " << i.GetKcal() << "   " << i.GetFats() << "   " << i.GetProtein() << "   " << i.GetCarbohydrates() << "   " << i.GetPrice() << "\n";
	}


	//kitchen
	Kitchen k = database.kitchen;
	vector<Order> orders = k.GetOrders();
	vector<Meal> meals = k.GetMeals();

	fout << meals.size() << "\n";
	for (auto meal : meals) {
		fout << meal.GetName() << "   " << meal.GetRating() << "   " << meal.GetPrice() << "  " << meal.GetItems().size() << "\n";

		for (auto i : meal.GetItems()) {
			fout << i.GetIngredient().GetName() << "   " << i.GetAmount() << "\n";
		}
	}

	fout << orders.size() << "\n";
	for (auto order : orders) {
		fout << order.GetTableNo() << "  ";
		if (order.GetisReady()) fout << "ready";
		else fout << "not-ready";
		fout << "\n";
		auto mealsinorder = order.GetMeals();

		fout << meals.size() << "\n";
		for (auto meal : meals) {
			fout << meal.GetName() << "   " << meal.GetRating() << "   " << meal.GetPrice() << "  " << meal.GetItems().size() << "\n";

			for (auto i : meal.GetItems()) {
				fout << i.GetIngredient().GetName() << "   " << i.GetAmount() << "\n";
			}
		}
	}
}