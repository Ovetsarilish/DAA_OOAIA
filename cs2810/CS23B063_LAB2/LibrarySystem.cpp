#include <bits/stdc++.h>

using namespace std;

class Book{
    private : 
        string isbn;
        int copiesAvailable;
        int totalCopies;

    public :
        string title;
        string author;

        Book(){
            this->title = "UnknownTitle";
            this->author = "UnknownAuthor";
            this->isbn = "ISBN";
            this->copiesAvailable = 0;
            this->totalCopies = 5;
        }

        Book(string title, string author, string isbn, int copiesAvailable, int totalCopies){
            this->title = title;
            this->author = author;
            this->isbn = isbn;
            this->copiesAvailable = copiesAvailable;
            this->totalCopies = totalCopies;
        }

        Book(Book* book, string newISBN){
            this->title = book->title;
            this->author = book->author;
            this->isbn = newISBN;
            this->copiesAvailable = book->getCopiesAvailable();
            this->totalCopies = book->getTotalCopies();
        }

        string getISBN(){
            return this->isbn;
        }

        void setISBN(string isbn){
            this->isbn = isbn;
        }

        int getCopiesAvailable(){
            return this->copiesAvailable;
        }

        int getTotalCopies(){
            return this->totalCopies;
        }

        void updateCopies(int count){
            if(this->totalCopies + count < 0 || this->copiesAvailable + count < 0){
                cout << "Invalid request! Count becomes negative" << "\n";
            }else{
                this->totalCopies = this->totalCopies + count;
                this->copiesAvailable = this->copiesAvailable + count;
            }
        }

        bool borrowBook(){
            if(this->copiesAvailable > 0){
                assert(totalCopies > 0);
                this->copiesAvailable = this->copiesAvailable - 1;
                return true;
            }else{
                cout << "Invalid request! Copy of book not available" << "\n";
                return false;
            }
        }

        bool returnBook(){
            if(this->copiesAvailable >= this->totalCopies){
                cout << "Invalid request! Copy of book exceeds total copies" << "\n";
                return false;
            }else{
                this->copiesAvailable = this->copiesAvailable + 1;
                return true;
            }
        }

        void printDetails(){
            cout << this->title << " " << this->author << "\n";
        }
};

class Member{
    private  : 
        string memberID;
        map<string, int> borrowedBooks;
        int borrowLimit;
        int totalBorrowed;

    public :
        string name;

        Member(string memberID, string name){
            this->memberID = memberID;
            this->name = name;
            this->borrowLimit = 3;
            this->totalBorrowed = 0;
        }

        Member(string memberID, string name, int borrowLimit){
            this->memberID = memberID;
            this->name = name;
            this->borrowLimit = borrowLimit;
            this->totalBorrowed = 0;
        }

        string getMemberID(){
            return this->memberID;
        }

        bool borrowBook(string isbn){
            if(this->totalBorrowed < this->borrowLimit){
                this->borrowedBooks[isbn]++;
                this->totalBorrowed = this->totalBorrowed + 1;
                return true;
            }else{
                cout << "Invalid request! Borrow limit exceeded" << "\n";
                return false;
            }
        }

        bool returnBook(string isbn){
            if(this->borrowedBooks.find(isbn) != this->borrowedBooks.end() && this->borrowedBooks[isbn] > 0){
                this->borrowedBooks[isbn]--;
                this->totalBorrowed = this->totalBorrowed - 1;
                return true;
            }else{
                cout << "Invalid request! Book not borrowed" << "\n";
                return false;
            }
        }

        void printDetails(){
            for(auto iter : borrowedBooks){
                if(iter.second > 0){
                    cout << this->memberID << " " << this->name << " " << iter.first << " " << iter.second << "\n";
                }
            }
        }
};

class Library{
    private :
        vector<Book> books;
        vector<Member> members;

        set<string> assignedISBN;
        set<string> assignedMemberID;

    public :
        bool addBook(Book &book){
            if(assignedISBN.find(book.getISBN()) != assignedISBN.end()){
                cout << "Invalid request! Book with same isbn already exists" << "\n";
                return false;
            }else{
                books.push_back(book);
                assignedISBN.insert(book.getISBN());
                return true;
            }
        } 

        bool registerMember(Member &member){
            if(assignedMemberID.find(member.getMemberID()) != assignedMemberID.end()){
                cout << "Invalid request! Member with same id already exists" << "\n";
                return false;
            }else{
                members.push_back(member);
                assignedMemberID.insert(member.getMemberID());
                return true;
            }
        }

        bool borrowBook(string memberID, string isbn){
            int memberIndex = getMemberIndex(memberID);
            int bookIndex = getBookIndex(isbn);

            assert(memberIndex != -1 && bookIndex != -1);

            bool bookSuccess = books[bookIndex].borrowBook();
            if(bookSuccess){
                bool memberSuccess = members[memberIndex].borrowBook(books[bookIndex].getISBN());
                if(memberSuccess){
                    return true;
                }else{
                    books[bookIndex].returnBook();
                    return false;
                }
            }else{
                return false;
            }
        }

        bool returnBook(string memberID, string isbn){
            int memberIndex = getMemberIndex(memberID);
            int bookIndex = getBookIndex(isbn);

            assert(memberIndex != -1 && bookIndex != -1);

            bool bookSuccess = books[bookIndex].returnBook();
            if(bookSuccess){
                bool memberSuccess = members[memberIndex].returnBook(isbn);
                if(memberSuccess){
                    return true;
                }else{
                    books[bookIndex].borrowBook();
                    return false;
                }
            }else{
                return false;
            }
        }

        int getMemberIndex(string memberID){
            for(int i = 0; i < (int)members.size(); i++){
                if(members[i].getMemberID() == memberID){
                    return i;
                }
            }
            return -1;
        }

        int getBookIndex(string isbn){
            for(int i = 0; i < (int)books.size(); i++){
                if(books[i].getISBN() == isbn){
                    return i;
                }
            }
            return -1;
        }

        Book& getBookReference(string isbn){
            for(int i = 0; i < (int)books.size(); i++){
                if(books[i].getISBN() == isbn){
                    return books[i];
                }
            }
            return books[0];
        }

        Member& getMemberReference(string memberID){
            for(int i = 0; i < (int)members.size(); i++){
                if(members[i].getMemberID() == memberID){
                    return members[i];
                }
            }
            return members[0];
        }

        void printLibraryDetails(){
            for(int i = 0; i < (int)books.size(); i++){
                cout << books[i].title << " " << books[i].author << " " << books[i].getCopiesAvailable() << "\n";
            }

            for(int i = 0; i < (int)members.size(); i++){
                cout << members[i].getMemberID() << " " << members[i].name << "\n";
            }
        }
};

int main(){
    Library library;
    string s;
    do{
        cin >> s;
        if(s == "Book"){
            string format;
            cin >> format;

            if(format == "ExistingBook"){
                string oldISBN, newISBN;
                cin >> oldISBN >> newISBN;

                Book newBook(&library.getBookReference(oldISBN), newISBN);
                library.addBook(newBook);
            }else if(format == "None"){
                Book newBook;
                library.addBook(newBook);
            }else{
                string title, author, isbn; int copiesAvailable, totalCopies;
                title = format;
                cin >> author >> isbn >> copiesAvailable >> totalCopies;

                Book newBook(title, author, isbn, copiesAvailable, totalCopies);
                library.addBook(newBook);
            }
        }else if(s == "Member"){
            string format;
            cin >> format;
            if(format == "NoBorrowLimit"){
                string memberID, name;
                cin >> memberID >> name;

                Member newMember(memberID, name, 3);
                library.registerMember(newMember);
            }else{
                string memberID, name; int borrowLimit;
                memberID = format;
                cin >> name >> borrowLimit;

                Member newMember(memberID, name, borrowLimit);
                library.registerMember(newMember);
            }
        }else if(s == "Borrow"){
            string memberID, isbn;
            cin >> memberID >> isbn;

            library.borrowBook(memberID, isbn);
        }else if(s == "PrintBook"){
            string isbn;
            cin >> isbn;

            library.getBookReference(isbn).printDetails();
        }else if(s == "PrintLibrary"){
            library.printLibraryDetails();
        }else if(s == "PrintMember"){
            string memberID;
            cin >> memberID;

            library.getMemberReference(memberID).printDetails();
        }else if(s == "Return"){
            string memberID, isbn;
            cin >> memberID >> isbn;

            library.returnBook(memberID, isbn);
        }else if(s == "UpdateCopiesCount"){
            string isbn; int newCount;
            cin >> isbn >> newCount;

            library.getBookReference(isbn).updateCopies(newCount);
        }else if(s == "Done"){
            break;
        }
    }while(s != "Done");
}