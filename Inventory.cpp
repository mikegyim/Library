#include "Inventory.h"
#include <vector>
#include <fstream>
#include <string>

int Inventory::NumberOfBooks()
{
	return Inventory::Books.size();
}

Book Inventory::GetBookByIndex(int index)
{
	return Inventory::Books[index];
}

void Inventory::AddBook(Book book)
{
	int nextBookId = 0;
	if (Books.size() > 0)
		nextBookId = Books.back().Id + 1;

	book.Id = nextBookId;

	Inventory::Books.push_back(book);

	std::ofstream oFile("books.txt", std::ios_base::app);
	oFile << book.ObtainBookFileData() << std::endl;
	oFile.close();
}

void Inventory::LoadBooks()
{
	Books.clear();

	std::ifstream inFile("books.txt");

	std::string bookData[4];
	

	std::string bookLine;
	while (std::getline(inFile, bookLine))
	{
		size_t nextIndex = bookLine.find('|');
		bookData[0] = bookLine.substr(0, nextIndex);

		size_t prevIndex = nextIndex;
		nextIndex = bookLine.find('|', prevIndex + 1);

		bookData[1] = bookLine.substr(prevIndex+1, nextIndex - prevIndex - 1);
		prevIndex = nextIndex;
		nextIndex = bookLine.find('|', prevIndex + 1);

		bookData[2] = bookLine.substr(prevIndex + 1, nextIndex - prevIndex - 1);
		prevIndex = nextIndex;
		nextIndex = bookLine.find('|', prevIndex + 1);

		bookData[3] = bookLine.substr(prevIndex + 1, nextIndex - prevIndex - 1);

		Book loadedBook(bookData[1], bookData[2]);
		loadedBook.Id = stoi(bookData[0]);
		loadedBook.InOrOutCheck(stoi(bookData[3]));

		Books.push_back(loadedBook);
	}
}

void Inventory::RemoveBook(std::string booktitle)
{
	std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(booktitle, ""));
	if (it != Inventory::Books.end())
	{
		Inventory::Books.erase(it);
	}
}


int Inventory::FindBookByTitle(std::string booktitle)
{
	std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(booktitle, ""));
	if (it == Inventory::Books.end())
	{
		return -1;
	}

	int index = it - Inventory::Books.begin();

	return index;
}

CheckInOrOutResult Inventory::CheckInOrOutBook(std::string booktitle, bool checkOut)
{
	int foundBookIndex = FindBookByTitle(booktitle);

	if (foundBookIndex < 0)
	{
		return CheckInOrOutResult::Book_Not_Found;
	}
	else if (checkOut == Books[foundBookIndex].IsCheckedOut())
	{
		if (checkOut)
		{
			return CheckInOrOutResult::Already_Checked_Out;
		}
		else
		{
			return CheckInOrOutResult::Already_Checked_In;
		}
	}

	Books[foundBookIndex].InOrOutCheck(checkOut);

	std::ofstream oFile("books.txt");
	for (int i = 0; i < Books.size(); i++)
	{
		oFile << Books[i].ObtainBookFileData() << std::endl;
	}

	return CheckInOrOutResult::Successful;
}

void Inventory::ShowAllBooks()
{
	std::cout << "\nID\tTitle\tAuthor" << std::endl;
	for (int i = 0; i < NumberOfBooks(); i++)
	{
		Books[i].ShowBook();
	}
	std::cout << std::endl;
}

void Inventory::ShowCheckedOutBooks()
{
	std::cout << "\nID\tBook Title\tAuthor Name " << std::endl;
	for (int i = 0; i < NumberOfBooks(); i++)
	{
		if (GetBookByIndex(i).IsCheckedOut())
		{
			Books[i].ShowBook();
		}
	}
	std::cout << std::endl;
}
