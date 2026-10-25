CAMPUSCASH — STUDENT EXPENSE TRACKER
====================================

FILES
- index.html: responsive website demo. Open it in Chrome/Edge/Firefox.
- expense_tracker.cpp: standalone C++ program demonstrating the required data structures.

DATA STRUCTURES USED IN THE C++ PROGRAM
1. Singly linked list: stores expense records and supports adding, listing, and deleting expenses.
2. Stack: stores deleted expenses; Undo restores the most recently deleted expense (LIFO).
3. Array: holds the four fixed categories (Food, Travel, Books, Other) and category totals.

WEBSITE FEATURES
- Add food, travel, books, and other expenses
- Total spending, current-month spending, transaction count, average expense
- Last-seven-days chart and category breakdown
- Search and delete transactions, plus undo delete
- Browser localStorage persistence (data stays in that browser)

IMPORTANT PROJECT NOTE
The HTML website is a standalone front-end prototype and uses JavaScript data handling plus browser localStorage. The C++ file is a separate command-line implementation of the same core logic. They are not wired together as a live C++ web server. To make the browser UI call C++ directly, a backend API or a WebAssembly build would be needed.

RUN THE WEBSITE
Double-click index.html, or serve the folder locally, for example:
  python -m http.server 8000
Then open http://localhost:8000

RUN THE C++ PROGRAM
  g++ -std=c++17 expense_tracker.cpp -o expense_tracker
  ./expense_tracker
On Windows with MinGW:
  g++ -std=c++17 expense_tracker.cpp -o expense_tracker.exe
  .\expense_tracker.exe
