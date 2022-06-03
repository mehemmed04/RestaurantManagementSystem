#pragma once
#include<iostream>
#include"Start.h"
#include<vector>
#include<string>
#include"Functions.h"
#include<iomanip>
using namespace std;

class Ingredient {
protected:
	string name;
	double fats;
	double protein;
	double carbohydrates;
	double kcal;
	double price;
public:
	Ingredient() {

	}
	Ingredient(const string& name) {
		SetName(name);
	}
	Ingredient(const string& name, const double& fats, const double& protein, const double& carbohydrates, const double& kcal, const double& price) {
		SetName(name);
		SetFats(fats);
		SetProtein(protein);
		SetCarbohydrates(carbohydrates);
		SetKcal(kcal);
		SetPrice(price);
	}
	void SetPrice(const double& price) {
		this->price = price;
	}

	void SetName(const string& name) {
		this->name = name;
	}
	void SetFats(const double& fats) {
		this->fats = fats;
	}
	void SetProtein(const double& protein) {
		this->protein = protein;
	}
	void SetCarbohydrates(const double& carbohydrates) {
		this->carbohydrates = carbohydrates;
	}
	void SetKcal(const double& kcal) {
		this->kcal = kcal;
	}

	string GetName()const { return name; }
	double GetFats()const { return fats; }
	double GetProtein()const { return protein; }
	double GetCarbohydrates()const { return carbohydrates; }
	double GetKcal()const { return kcal; }
	double GetPrice() const { return price; }

	void ShowIngredient()const {
		cout <<setw(16) << "Name : " << name << endl;
		cout <<setw(16) << "Kcal : " << kcal << endl;
		cout <<setw(16) << "Fats : " << fats << endl;
		cout <<setw(16) << "Protein : " << protein << endl;
		cout <<setw(16) << "Carbohydrates : " << carbohydrates << endl;
		cout <<setw(16) << "Price : " << price << endl;
	}

};



class RecipeItem {
	Ingredient ingredient;
	int amount = 0;// neche dene
public:
	Ingredient GetIngredient() {
		return ingredient;
	}

	RecipeItem(Ingredient ingredient, int amount) {
		this->ingredient = ingredient;
		this->amount = amount;
	}
	int GetAmount()const { return amount; }

	void ShowRecipeItemWithMicro()const {
		cout << setw(16) << left << ingredient.GetName() << setw(16) << left << amount << " gr" << endl;
		ingredient.ShowIngredient();
	}
	void ShowRecipeItem() {
		cout << setw(16) << left << ingredient.GetName() << amount << " gr" << endl;
	}

};

class Meal {
protected:
	vector<RecipeItem> items;
	string name;
	double fats = 0; double protein = 0; double ch = 0; double kcal = 0;
	double rating;
	double price;
public:

	Meal() {}
	Meal(const string& name, const double& rating) {
		SetName(name);
		SetRating(rating);
		SetPrice();
		SetCalories();
	}

	Meal(const string& name, const double& rating, const double& price) {
		SetName(name);
		SetRating(rating);
		this->price = price;
	}
	void SetCalories() {
		for (auto i : items) {
			fats += i.GetIngredient().GetFats();
			protein += i.GetIngredient().GetProtein();
			ch += i.GetIngredient().GetCarbohydrates();
			kcal += i.GetIngredient().GetKcal();
		}
	}
	vector<RecipeItem> GetItems()const {
		return items;
	}

	void AddRating(const double& rating) {
		double new_rating = (this->rating * items.size() + rating) / (items.size() + 1);
		SetRating(new_rating);
	}

	void SetPrice() {
		price = 0;
		for (auto i : items) {
			price += i.GetIngredient().GetPrice();
		}

	}

	Meal& operator=(const Meal& other) {
		this->SetName(other.name);
		this->SetRating(other.rating);
		this->items = other.items;
		return *this;
	}

	void SetName(const string& name) {
		this->name = name;
	}
	void SetRating(const double& rating) {
		this->rating = rating;
	}
	bool operator==(const Meal& other) {
		if (name == other.GetName() && rating == other.GetRating()) return true;
		return false;
	}

	double GetRating()const {
		return rating;
	}
	double GetPrice()const {
		return price;
	}

	virtual void AddIngredient(RecipeItem item) {
		items.push_back(item);
		SetPrice();
		SetCalories();
	}
	string GetName()const { return name; }

	virtual void Taste() {
		cout << "I do not know what is this ? " << endl;
	}

	virtual void PrintRecipeWithMicro() {
		cout << setw(18)<<left << "Meal name : " << GetName() << endl;
		cout << setw(18)<<left << "Meal Price : " << price << "$" << endl;
		cout << setw(18)<<left << "Meal Rating : " << rating << endl;
		cout << setw(18)<<left << "Meal Ingredients : " << endl;
		cout << setw(18)<<left << "Fats : " << fats << endl;
		cout << setw(18)<<left << "Protein : " << protein << endl;
		cout << setw(18)<<left << "Carbohydrates : " << ch << endl;
		cout << setw(18)<<left << "Kcal : " << kcal << endl;
		cout << "-----------------" << endl;
	}

	virtual void PrintRecipe() {
		cout << setw(18) << left << "Meal name : " << GetName() << endl;
		cout << setw(18) << left << "Meal Price : " << price << endl;
		cout << setw(18) << left << "Meal Rating : " << rating << endl;
		cout << setw(18) << left << "Meal Ingredients : " << endl;
		for (auto i : items) {
			i.ShowRecipeItem();
		}
		cout << "-----------------" << endl;
	}
};


class Admin {
	string username;
	string password;
public:
	Admin() {

	}
	Admin(const string& username, const string& password) {
		SetUsername(username);
		SetPassword(password);
	}

	void SetUsername(const string& username) {
		this->username = username;
	}
	void SetPassword(const string& password) {
		this->password = password;
	}

	string GetUsername() {
		return username;
	}
	string GetPassword() {
		return password;
	}

};

class Order {
public:
	string Table_no;
	vector<Meal> meals;
	bool IsReady = false;
	Order() = default;
	Order(string Table_no, vector<Meal> meals) {
		this->Table_no = Table_no;
		SetMeals(meals);
	}
	void SetMeals(vector<Meal> meals) {
		this->meals = meals;
	}

	string GetTableNo()const { return Table_no; }
	vector<Meal> GetMeals()const {
		return meals;
	}
	bool GetisReady()const {
		return IsReady;
	}

	string GetTableNoByOrder() { return Table_no; }
	void ShowOrder() {
		for (auto meal : meals) {
			meal.PrintRecipe();
		}
	}

	Order& operator=(const Order& other) {
		this->Table_no = other.Table_no;
		this->meals = other.meals;
		this->IsReady = other.IsReady;
		return *this;

	}
};

class Table {
public:
	string table_no;
	Order order;
	string MessageFromKitchen = "";
	bool IsReady = false;
	Table() = default;
	Table(const string& table_no) {
		SetTableNo(table_no);
	}

	Table(const string& table_no, const bool& isready) {
		SetTableNo(table_no);
		this->IsReady = isready;
	}

	Table(const Table& other) {
		this->SetTableNo(other.GetTableNo());
		this->SetMessageFromKitchen(other.MessageFromKitchen);
		this->IsReady = other.IsReady;
		this->order = other.order;
	}

	Table& operator=(const Table& other) {
		this->SetTableNo(other.GetTableNo());
		this->SetMessageFromKitchen(other.MessageFromKitchen);
		this->IsReady = other.IsReady;
		this->order = other.order;
		return *this;
	}

	string GetMessageFromKitchen() {
		return MessageFromKitchen;
	}
	void SetTableNo(const string& table_no) {
		this->table_no = table_no;
	}
	string GetTableNo()const {
		return table_no;
	}
	void AddOrder(const Order& order) {
		this->order = order;
	}

	void SetMessageFromKitchen(const string& message) {
		this->MessageFromKitchen = message;
	}

};

class Restaurant {
	string name;
	string adress;
	string city;
	double budget;
	vector<Admin> admins;
	vector<Table> tables;
public:
	Restaurant() = default;
	Restaurant(const string& name, const string& adress, const string& city) {
		SetName(name);
		SetAdress(adress);
		SetCity(city);
		budget = 0;
	}
	void SetBudget(const double& budget) {
		this->budget = budget;
	}
	string GetName()const { return name; }
	string GetAdress()const { return adress; }
	string GetCity()const { return city; }
	double GetBudget()const { return budget; }
	vector<Admin> GetAdmins()const { return admins; }
	vector<Table> GetTables()const { return tables; }


	Table* GetTableByNoPtr(const string& table_no) {
		for (auto table : tables) {
			if (table.GetTableNo() == table_no) return &table;
		}
		return nullptr;
	}

	void SetTable(const Table& new_table) {
		for (auto table : tables) {
			if (table.GetTableNo() == new_table.GetTableNo()) {
				table = new_table;
			}
		}
	}

	Table GetTableByNo(const string& table_no) {
		for (auto table : tables) {
			if (table.GetTableNo() == table_no) return table;
		}
	}

	Restaurant(const string& name, const string& adress, const string& city, vector<Admin> admins) :Restaurant(name, adress, city) {
		SetAdmins(admins);
	}

	void AddTable(const Table& table) {
		tables.push_back(table);
	}

	vector<Admin>GetAdmins() {
		return admins;
	}

	void SetName(const string& name) { this->name = name; }

	void SetAdress(const string& adress) {
		this->adress = adress;
	}
	void SetCity(const string& city) {
		this->city = city;
	}

	void SetAdmins(vector<Admin> admins) {
		this->admins = admins;
	}

	void AddAdmin(const Admin& admin) {
		admins.push_back(admin);
	}

	void IncreaseBudget(double b) {
		budget += b;
	}

};

class Stock {
	vector<Ingredient> ingredients;
public:
	Ingredient GetIngredient() {
		string name; double fats; double protein; double carbohydrates; double price;
		double kcal;
		system("cls");
		SetCordinates(50, 10);
		cout << "Enter Ingredient Name : "; getline(cin, name);
		SetCordinates(50, 11);
		cout << "Enter Ingredient Fats : "; cin >> fats;
		SetCordinates(50, 12);
		cout << "Enter Ingredient Protein : "; cin >> protein;
		SetCordinates(50, 13);
		cout << "Enter Ingredient Carbohydrates : "; cin >> carbohydrates;
		SetCordinates(50, 14);
		cout << "Enter Ingredient kcal : "; cin >> kcal;
		SetCordinates(50, 15);
		cout << "Enter Ingredient Price : "; cin >> price;

		return Ingredient(name, fats, protein, carbohydrates, kcal, price);

	}
	vector<Ingredient> GetIngredients()const {
		return ingredients;
	}

	void AddIngredient(const Ingredient& ingredient) {
		ingredients.push_back(ingredient);
	}
	int GetIngredientIndex(const Ingredient& ingredient) {
		int count = -1;
		for (auto i : ingredients) {
			count++;
			if (i.GetName() == ingredient.GetName()) return count;
		}

	}

	void DeleteIngredient(const Ingredient& ingredient) {
		int iterator = GetIngredientIndex(ingredient);
		ingredients.erase(ingredients.begin() + iterator);
	}
	void ShowAllIngredients() const {
		cout << "STOCK : " << endl;
		for (auto i : ingredients) {
			i.ShowIngredient();
			cout << endl;
		}

	}
	Ingredient GetIngredientByName(const string& name) {
		for (auto i : ingredients) {
			if (i.GetName() == name) {
				return i;
			}
		}
		return Ingredient();
	}

	void DecraseIngredientPrice(const string& name) {
		auto Ingredient = GetIngredientByName(name);
		cout << "Enter new price : "; double price; cin >> price;
		Ingredient.SetPrice(price);

	}
	void IncreaseIngredientPrice(const string& name) {
		auto Ingredient = GetIngredientByName(name);
		cout << "Enter new price : "; double price; cin >> price;
		Ingredient.SetPrice(price);
	}
};

class Kitchen {
	vector<Order> orders;
	vector<Meal> meals;
public:
	void ShowAllOrders() {
		system("cls");
		for (auto order : orders) {
			if (!order.IsReady) {
				cout << "Table : " << order.GetTableNoByOrder() << endl;
				order.ShowOrder();
				cout << "=====================" << endl;
			}
		}
	}

	vector<Order> GetOrders()const {
		return orders;
	}
	vector<Meal> GetMeals()const {
		return meals;
	}
	Meal GetMeal() {
		string name;
		double rating;
		cout << "Enter meal name : "; getline(cin, name);
		cout << "Enter rating : "; cin >> rating;

		Meal meal(name, rating);
		return meal;
	}

	void AddOrder(const Order& order) {
		orders.push_back(order);
	}
	void AddMeal(const Meal& meal) {
		meals.push_back(meal);
	}

	Meal* GetMealPtrByName(const string& meal_name) {
		for (auto meal : meals) {
			if (meal.GetName() == meal_name) return &meal;
		}
		return nullptr;
	}

	Meal GetMealByName(const string& meal_name) {
		for (auto meal : meals) {
			if (meal.GetName() == meal_name) return meal;
		}
	}

	void UpdateMeal() {
		auto newMeal = GetMeal();
		string meal_name;
		cout << "Enter Meal name : ";
		cin.ignore(); cin.clear();
		getline(cin, meal_name);
		auto Meal = GetMealByName(meal_name);

		for (auto meal : meals) {
			if (meal == Meal) {
				meal = newMeal;
				break;
			}
		}
	}

	void ShowStock(const Stock& stock) {
		stock.ShowAllIngredients();
	}

	void ShowAllMeals() {
		for (auto meal : meals) {
			meal.PrintRecipe();
		}
	}

};