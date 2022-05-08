#include <iostream>
#include <vector>

#include "Book.h"
#include "std_lib_facilities.h"

int ex_08() {
    library::Patron patron{"John Doe", 123456};
    if (!patron.is_outstanding_fee()) {
        std::cout << patron.get_name() << " outstanding fees $" << patron.get_fees() << '\n';
    }

    patron.set_fees(0.01);
    std::cout << patron.get_name() << " outstanding fee of $" << patron.get_fees() << '\n';
}

int ex_07() {
    using library::Book;

    Book book1("0-321-99278-4", "Programming Principles and Practices Using C++ Second Edition",
               "Bjarne Stroustrup", 2014, Book::Genre::nonfiction);
    std::cout << book1 << "\n\n";
    Book book2;
    Book book3 = book1;

    if (book1 == book3) {
        std::cout << book3 << "\n\n";
    }

    if (book1 != book2) {
        std::cout << book2 << "\n\n";
    }

    // Book book4("0-321_99278-4", "Programming Principles and Practices Using C++ Second Edition",
    // "Bjarne Stroustrup", 2014, Book::Genre::nonfiction);
}

int ex_06() {
    library::Book book1("0-321-99278-4",
                        "Programming Principles and Practices Using C++ Second Edition",
                        "Bjarne Stroustrup", 2014);
    std::cout << book1 << "\n\n";
    library::Book book2;
    library::Book book3 = book1;

    if (book1 == book3) {
        std::cout << book3 << "\n\n";
    }

    if (book1 != book2) {
        std::cout << book2 << "\n\n";
    }

    // library::Book book4("0-321_99278-4", "Programming Principles and Practices Using C++ Second
    // Edition", "Bjarne Stroustrup", 2014);
}

int ex_05() {
    library::Book book("0-321-99278-4",
                       "Programming Principles and Practices Using C++ Second Edition",
                       "Bjarne Stroustrup", 2014);
    std::cout << "ISBN: " << book.get_isbn() << '\n'
              << "TITLE: " << book.get_title() << '\n'
              << "AUTHOR: " << book.get_author() << '\n'
              << "COPYRIGHT: " << book.get_copyright() << '\n'
              << "checked out: " << std::boolalpha << book.is_checked_out() << "\n\n";

    book.check_inout(true);
    std::cout << "ISBN: " << book.get_isbn() << '\n'
              << "TITLE: " << book.get_title() << '\n'
              << "AUTHOR: " << book.get_author() << '\n'
              << "COPYRIGHT: " << book.get_copyright() << '\n'
              << "checked out: " << std::boolalpha << book.is_checked_out() << "\n\n";

    // library::Book book2("0-321_99278-4", "Programming Principles and Practices Using C++ Second
    // Edition", "Bjarne Stroustrup", 2014);

    return 0;
}

int main() {
    ex_05();
    cout << "\n---------------------------------------\n";
    ex_06();
    cout << "\n---------------------------------------\n";
    ex_07();
    cout << "\n---------------------------------------\n";
    ex_08();
    cout << "\n---------------------------------------\n";
    return 0;
}