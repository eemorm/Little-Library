// Herreson and Everett

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, int> checkedOut;
map<string, int> expirationDate;
map<string, int> renewed;

bool searchBooks();           // algorithm searches for books
void checkOutBook(string iD); // method of checking out books
void returnBook();            // returns books to the library
void renewBook();             // renews books to be kept for more time
void displayOverdueBooks();   // shows list of over due books
double calculateLateFees();   // calculates late fees
void clr();                   // clears screen

int day = 1;
double debt;

int main() {
  while (1) {
    clr(); // clears screen

    int choice;
    cout << "DAY " << day << "    DEBT: $" << debt << endl
         << endl; // displays time and debt if any
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "Welcome to the Library!"
         << endl; // directions to make the pogram eaiser to operate
    cout << "1. Search for a book" << endl;
    cout << "2. Return a book" << endl;
    cout << "3. Renew books" << endl;
    cout << "4. Display overdue books" << endl;
    cout << "5. Advance day" << endl;
    cout << "6. Exit" << endl << "-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-" << endl << ">>> ";
    cin >> choice;
    switch (choice) {
    case 1:
      searchBooks();
      break;
    case 2:
      returnBook();
      break;
    case 3:
      renewBook();
      break;
    case 4:
      displayOverdueBooks();
      break;
    case 5: {
      day++;
      for (auto &[id, days] : checkedOut) {
        days++;
      }
      clr();
    } break;
    case 6:
      return 0;
      break;
    default:
      continue;
    }
  }
}

bool searchBooks() {
  string search;
  clr();
  cout << "-+-+-+-+-+-+-+-" << endl;
  cout << "Enter the ID: "; // finds ID
  cin >> search;

  if (search.length() <= 4) {
    if (search.find("LB") == string::npos) {
      string paddedNum = string(4 - search.length(), '0') + search; // formats
                                                                    // ID
      search = "LB" + paddedNum;
    }
  }

  std::ifstream file("books.txt");
  if (!file.is_open()) {
    std::cerr << "Could not read catalogue" << std::endl;
    return false;
  }
  // this opens and reads the file
  string line;
  while (getline(file, line)) {
    if (line.find(search) != string::npos) {
      cout << "Found: " << line << endl;
      file.close();
      checkOutBook(search); // sends to other function to be checked out
      return true;
    }
  }

  file.close(); // closes file
  int d;
  cout << "Book not found (enter something to continue)" << endl;
  cin >> d;
  return false;
}

void checkOutBook(string iD) {
  int c;
  while (1) {
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "Would you like to check out this book?" << endl
         << "1. Yes" << endl // asks user if the book should be checked out
         << "2. No" << endl;
    cin >> c;
    if (c == 1) {
      checkedOut.insert({iD, 1});
      expirationDate.insert({iD, 7}); // adds to dictionaries
      renewed.insert({iD, 4});
      break;
    } else if (c == 2) {
      break;
    } else {
      continue;
    }
  }
}

void returnBook() {
  string returnBook;
  clr();

  if (checkedOut.empty()) {
    cout << "No books to return." << endl;
    cout << "(enter something to continue)"
         << endl; // checks if nothing to return
    cin >> returnBook;
    return;
  }

  cout << "Currently checked out books:" << endl;
  cout << "--------------------------" << endl;
  for (const auto &pair : checkedOut) {
    ifstream file("books.txt");
    string line; // lists checked out books
    while (getline(file, line)) {
      if (line.find(pair.first) != string::npos) {
        cout << line << endl;
        cout << "Days left: " << expirationDate[pair.first] - pair.second
             << endl;
        cout << "--------------------------" << endl;
      }
    }
    file.close(); // closes file
  }
  cout << endl;
  cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
  cout << "Enter book ID to return: "; // finds ID
  cin >> returnBook;

  if (returnBook.length() <= 4) {
    if (returnBook.find("LB") == string::npos) {
      string paddedNum =
          string(4 - returnBook.length(), '0') + returnBook; // formats ID
      returnBook = "LB" + paddedNum;
    }
  }

  if (checkedOut.find(returnBook) != checkedOut.end()) {
    checkedOut.erase(returnBook);
    expirationDate.erase(returnBook);
    renewed.erase(returnBook);
    cout << "Book (" << returnBook
         << ") returned. (enter something to continue)" << endl; // returns book
    cin >> returnBook;
  } else {
    cout << "Book not found in checked out list. (enter something to continue)"
         << endl;
    cin >> returnBook;
  }
}

void renewBook() {
  string iD;
  clr();

  if (checkedOut.empty()) {
    cout << "No books to renew." << endl;
    cout << "(enter something to continue)"
         << endl; // checks if nothing to renew
    cin >> iD;
    return;
  }

  cout << "Currently checked out books:" << endl;
  cout << "--------------------------" << endl;
  for (const auto &pair : checkedOut) {
    ifstream file("books.txt");
    string line;
    while (getline(file, line)) {
      if (line.find(pair.first) != string::npos) { // lists checked out books
        cout << line << endl;
        cout << "Days left: " << expirationDate[pair.first] - pair.second
             << endl;
        cout << "--------------------------" << endl;
      }
    }
    file.close();
  }
  cout << endl;

  cout << "Enter book ID to renew: ";
  cin >> iD; // gets ID

  if (iD.length() <= 4) {
    if (iD.find("LB") == string::npos) {
      string paddedNum = string(4 - iD.length(), '0') + iD; // formats ID
      iD = "LB" + paddedNum;
    }
  }

  if (checkedOut.find(iD) != checkedOut.end() &&
      checkedOut[iD] < expirationDate[iD] && renewed[iD] > 0) {
    renewed[iD] -= 1;
    expirationDate[iD] += 2;
    cout << "Book (" << iD
         << ") renewed. (enter something to continue)" // renews book
         << endl;
    cin >> iD;
  } else {
    cout << "Cannot renew. (enter something to continue)" << endl;
    cin >> iD;
  }
}

void displayOverdueBooks() {
  clr(); // clears screen

  int choice;
  bool hasOverdueBooks = false;
  for (const auto &pair : checkedOut) {
    if (pair.second > expirationDate[pair.first]) {
      cout << "\033[31m"
           << "Book ID: " << pair.first
           << "\nDays after Checking Out: " << pair.second << endl
           << "Days Left: "
           << expirationDate[pair.first] - pair.second // colors if overdue
           << "\033[0m" << endl
           << endl;
      hasOverdueBooks = true;
    } else {
      cout << "Book ID: " << pair.first
           << "\nDays after Checking Out: " << pair.second << endl
           << "Days Left: " << expirationDate[pair.first] - pair.second << endl
           << endl;
    }
  }

  if (!hasOverdueBooks) {
    cout << "No overdue books." << endl;
  }

  string up;
  cout << "Enter anything to continue: ";
  cin >> up;

  if (hasOverdueBooks) {
    while (true) {
      cout << "Would you like to calculate late fees?" << endl
           << "1. Yes" << endl // calculates late fees if a book is overdue
           << "2. No" << endl;
      cin >> choice;
      if (choice == 1) {
        int pay;
        double fees = calculateLateFees();
        if (fees != 0) {
          cout << "Late fees: $" << fees + debt << endl << "Enter 1 to pay: ";
          cin >> pay;
          if (pay == 1) { // pays off debt
            debt = 0;
            cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
            cout << "Thank you for paying your fees!" << endl;
            cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
            cout << "Enter anything to continue: ";
            cin >> up;
          } else { // displays debt but does not pay
            debt += fees;
          }
        } else {
          cout << "No late fees to pay." << endl;
        }
        break;
      } else if (choice == 2) {
        break;
      } else {
        continue;
      }
    }
  }
}

double calculateLateFees() {
  for (const auto &pair : checkedOut) {
    if (pair.second > expirationDate[pair.first]) {
      return (pair.second - expirationDate[pair.first]) *
             0.25; // algorithm finds the fees
    }
  }
  return 0;
}

void clr() { cout << "\033[2J\033[1;1H"; } // clears screen

/*First, the program shows a menu that gives many options. One is searching for
 * books, which finds a book from the catalog and asks if you would like to
 * check it out. Next is returning books, which means that you can give back a
 * book that you are done with. You can also renew books, so that they will not
 * inflict late fees, which can be found by displaying overdue books. You can
 * see your books and if you have one overdue, you can pay your fees. If you
 * don't, you go into debt. This program could be used in real life as it could
 * function in a real library as a system to check out books. It is great for
 * management and the catalog is easily expandable.*/