# 🏦 Banking Management System (C++)

A console-based Banking Management System developed in C++ using Object-Oriented Programming (OOP) concepts and file handling.
This project simulates real-world banking operations such as account creation, deposits, withdrawals, balance inquiry, and secure money transfer.

# 🚀 Features

    ✅ Create bank accounts with unique auto-generated account numbers

    🔐 PIN-based security for sensitive operations

    💰 Deposit money

    💸 Withdraw money with balance checks

    🔁 Transfer money between two accounts

    📄 Persistent storage using file handling

    🛡 Strong input validation

    ⚙ Random account number generation

# 🧠 Concepts Used

    Object-Oriented Programming (Classes & Objects)

    Encapsulation & Const Correctness

    STL (vector)

    File Handling (ifstream, ofstream)

    Random Number Generation (<random>)

    Pointer Handling

    Input Validation & Error Handling

# 📁 Project Structure
    Banking_Management_System/
    │
    ├── banking.cpp        # Main source code
    ├── accounts.txt       # Account data file (auto-created)
    └── README.md          # Project documentation

# 🛠️ How to Compile & Run
    🔹 Using g++
        g++ banking.cpp -o banking
        ./banking

    🔹 Windows (PowerShell)
        g++ banking.cpp -o banking
        .\banking

# 🖥️ Menu Options
    1. Create Account
    2. Deposit
    3. Withdraw
    4. View Account
    5. Send Money
    6. Exit

# 🔐 Security Details

# Each account is protected with a 4-digit PIN

# PIN verification is required for:

    Withdrawals

    Money transfers

    Transfers to the same account are not allowed

# 💾 Data Persistence

    Account data is stored in accounts.txt

    Data loads automatically when the program starts

    No data loss between program executions

# 📌 Sample Data Format (accounts.txt)
    123456 John 5000 1234
    654321 Alice 3000 4321

# 🔮 Future Improvements

    🔄 Split project into .h and .cpp files

    🧾 Transaction history feature

    🔍 Search account by name

    🔐 Encrypt PIN storage

    🖥 GUI-based version

    🧪 Unit testing

# 👨‍💻 Author

Paras Mahajan
B.Tech Computer Science Student
Focused on C++ system-level and backend development

⭐ Support

If you like this project:

⭐ Star the repository

🍴 Fork it

🧑‍💻 Contribute enhancements

Happy Coding! 🚀