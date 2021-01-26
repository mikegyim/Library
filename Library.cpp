#include <iostream>
#include "Book.h"
#include "Inventory.h"
#include <string>
#include "User.h"
#include <fstream>

using namespace std;

Inventory _inventory;
vector<User> _users;
User _loggedInUser;

Category GetCategoryFromIntVal(int categoryVal)
{
	Category outCategory;

	if (categoryVal == 0)
	{
		outCategory = Category::Admin;
	}
	else if (categoryVal == 1)
	{
		outCategory = Category::Employee;
	}
	else
	{
		outCategory = Category::Member;
	}

	return outCategory;
}

void LoadUsers()
{
	ifstream inFile("users.txt");

	string lineData[2];
	// lineData[0] = username
	// lineData[1] = role int val

	string userLine;
	while (getline(inFile, userLine))
	{
		size_t index = userLine.find('|');
		lineData[0] = userLine.substr(0, index);
		lineData[1] = userLine.substr(index + 1);

		User loadedUser;
		loadedUser.userName = lineData[0];
		loadedUser.Category = GetCategoryFromIntVal(stoi(lineData[1]));

		_users.push_back(loadedUser);
	}
}

int GetIntValFromCategory(Category category)
{
	int categoryVal = -1;
	if (category == Category::Admin)
	{
		categoryVal = 0;
	}
	else if (category == Category::Employee)
	{
		categoryVal = 1;
	}
	else if (category == Category::Member)
	{
		categoryVal = 2;
	}

	return categoryVal;
}

void CreateAccount()
{
	User newUser;

	/*cout << "First name:" << endl;
	string firstName;
	getline(cin, firstName);

	cout << "Last name:" << endl;
	string lastName;
	getline(cin, lastName);*/

	cout << "Username:" << endl;
	getline(cin, newUser.userName);

	cout << "Select your category:" << endl;
	cout << "1. Admin" << endl;
	cout << "2. Employee" << endl;
	cout << "3. Member" << endl;
	cout << "4. Guest" << endl;

	int categoryOption;
	cin >> categoryOption;
	cin.ignore();

	if (categoryOption == 1)
		newUser.Category = Category::Admin;
	else if (categoryOption == 2)
		newUser.Category = Category::Employee;
	else if (categoryOption == 3)
		newUser.Category = Category::Member;
	else 
		newUser.Category = Category::Guest;

	_users.push_back(newUser);

	ofstream oFile("users.txt", ios_base::app);
	oFile << newUser.userName << "|" << GetIntValFromCategory(newUser.Category) << endl;
	oFile.close();
}

void Login()
{
	cout << "Choose an option:" << endl;
	cout << "1. Log In" << endl;
	cout << "2. Create account" << endl;

	int option;
	cin >> option;
	cin.ignore();

	if (option == 2)
	{
		CreateAccount();
	}

	while (true)
	{
		cout << "Enter username: ";
		string username;
		getline(cin, username);

		User user;
		user.userName = username;

		vector<User>::iterator it = find(_users.begin(), _users.end(), user);

		if (it != _users.end())
		{
			_loggedInUser = _users[it - _users.begin()];
			break;
		}
	}
}

void DisplayMainMenu()
{
	cout << endl;
	cout << "Choose an option:" << endl;

	cout << "1. List all books" << endl;
	cout << "2. Check out book" << endl;
	cout << "3. Check in book" << endl;

	if (_loggedInUser.Category == Category::Employee
		|| _loggedInUser.Category == Category::Admin)
	{
		cout << "4. Add book" << endl;
		cout << "5. Remove book from library" << endl;
		cout << "6. List all checked out books" << endl;
	}

	cout << "9. Log out" << endl;
	cout << "0. Exit" << endl;
}

void AddNewBook()
{
	cout << "Book Title: ";
	string booktitle;
	getline(cin, booktitle);

	cout << "Author Name: ";
	string author_name;
	getline(cin, author_name);

	

	Book newBook(booktitle, author_name);

	_inventory.AddBook(newBook);
}

void ListAllBooks()
{
	_inventory.DisplayAllBooks();
}

void CheckInOrOutBook(bool checkOut)
{
	string inOrOut;
	if (checkOut)
	{
		inOrOut = "out";
	}
	else
	{
		inOrOut = "in";
	}

	cout << "Enter a book title to check " + inOrOut + ": ";
	string booktitle;
	getline(cin, booktitle);

	CheckInOrOutResult result = _inventory.CheckInOrOutBook(booktitle, checkOut);

	if (result == CheckInOrOutResult::BookNotFound)
	{
		cout << "Book not found";
	}
	else if (result == CheckInOrOutResult::Success)
	{
		cout << "Book checked " + inOrOut + "!" << endl;
	}
	else if (result == CheckInOrOutResult::AlreadyCheckedIn
		|| result == CheckInOrOutResult::AlreadyCheckedOut)
	{
		cout << "Book already checked " + inOrOut << endl;
	}
	else
	{
		cout << "Book failed checking " + inOrOut + "!" << endl;
	}
}

void RemoveBook()
{
	cout << "Book Title: ";
	string booktitle;
	getline(cin, booktitle);

	_inventory.RemoveBook(booktitle);
}

void DisplayCheckedOutBooks()
{
	_inventory.DisplayCheckedOutBooks();
}

int main()
{
	LoadUsers();

	while (true)
	{
		Login();

		_inventory.LoadBooks();
		bool isLoggedIn = true;
		while (isLoggedIn)
		{
			DisplayMainMenu();

			int input;
			cin >> input;
			cin.ignore();

			switch (input)
			{
			case 0:
				cout << "Thank you. Goodbye";
				return 0;
			case 1:
				ListAllBooks();
				break;
			case 2:
				CheckInOrOutBook(true);
				break;
			case 3:
				CheckInOrOutBook(false);
				break;
			case 4:
				AddNewBook();
				break;
			case 5:
				RemoveBook();
				break;
			case 6:
				DisplayCheckedOutBooks();
				break;
			case 9:
				isLoggedIn = false;
				break;
			default:
				cout << "Invalid selection. Try again." << endl;
				break;
			}
		}
	}
}

