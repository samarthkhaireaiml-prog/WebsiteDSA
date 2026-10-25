// CampusCash — Student Expense Tracker (C++ data-structure implementation)
// Build: g++ -std=c++17 expense_tracker.cpp -o expense_tracker
// This standalone program demonstrates the same core operations as the website.
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <limits>
#include <algorithm>
using namespace std;

struct Expense {
    int id{};
    string title, category, date;
    double amount{};
};

// LINKED LIST: stores the transaction history.
class ExpenseList {
    struct Node { Expense data; unique_ptr<Node> next; explicit Node(Expense e):data(std::move(e)){} };
    unique_ptr<Node> head;
public:
    void add(Expense e) { auto n=make_unique<Node>(std::move(e)); n->next=std::move(head); head=std::move(n); }
    bool remove(int id, Expense &removed) {
        unique_ptr<Node>* cur=&head;
        while (*cur) {
            if ((*cur)->data.id==id) { removed=(*cur)->data; *cur=std::move((*cur)->next); return true; }
            cur=&((*cur)->next);
        }
        return false;
    }
    vector<Expense> all() const { vector<Expense> out; for(Node* p=head.get();p;p=p->next.get()) out.push_back(p->data); return out; }
    bool empty() const { return !head; }
};

// ARRAY: fixed categories and category-wise totals.
const string CATEGORIES[] = {"Food", "Travel", "Books", "Other"};
const int CATEGORY_COUNT=4;
int categoryIndex(const string& s) { for(int i=0;i<CATEGORY_COUNT;i++) if(CATEGORIES[i]==s)return i; return 3; }

// STACK: recently deleted expenses can be restored in last-in-first-out order.
int main() {
    ExpenseList history;
    stack<Expense> undoStack;
    int nextId=1;
    while(true) {
        cout << "\n========== CampusCash =========="
             << "\n1. Add expense\n2. View expenses\n3. Summary by category"
             << "\n4. Delete expense (undo stack)\n5. Undo last deletion\n0. Exit\nChoose: ";
        int choice; if(!(cin>>choice)) break;
        if(choice==0) break;
        if(choice==1) {
            Expense e; e.id=nextId++;
            cout<<"Expense name: "; cin.ignore(numeric_limits<streamsize>::max(),'\n'); getline(cin,e.title);
            cout<<"Amount (INR): "; while(!(cin>>e.amount)||e.amount<=0){cout<<"Enter a positive amount: ";cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');}
            cout<<"Category (1 Food, 2 Travel, 3 Books, 4 Other): "; int c; cin>>c; e.category=CATEGORIES[(c>=1&&c<=4)?c-1:3];
            cout<<"Date (YYYY-MM-DD): "; cin>>e.date;
            history.add(e); cout<<"Expense added.\n";
        } else if(choice==2) {
            auto items=history.all();
            if(items.empty()) cout<<"No expenses recorded yet.\n";
            for(const auto&e:items) cout<<"#"<<e.id<<" | "<<e.date<<" | "<<e.category<<" | "<<e.title<<" | Rs."<<fixed<<setprecision(2)<<e.amount<<"\n";
        } else if(choice==3) {
            double totals[CATEGORY_COUNT]={0},grand=0; int count=0;
            for(const auto&e:history.all()){totals[categoryIndex(e.category)]+=e.amount;grand+=e.amount;count++;}
            cout<<fixed<<setprecision(2)<<"\nTotal spent: Rs."<<grand<<" | Transactions: "<<count<<"\n";
            for(int i=0;i<CATEGORY_COUNT;i++) cout<<CATEGORIES[i]<<": Rs."<<totals[i]<<"\n";
        } else if(choice==4) {
            cout<<"Expense ID to delete: "; int id; cin>>id; Expense gone;
            if(history.remove(id,gone)){undoStack.push(gone);cout<<"Deleted. You can undo this action.\n";}else cout<<"ID not found.\n";
        } else if(choice==5) {
            if(undoStack.empty()) cout<<"Nothing to undo.\n";
            else {Expense e=undoStack.top();undoStack.pop();history.add(e);cout<<"Restored: "<<e.title<<"\n";}
        } else cout<<"Please choose a listed option.\n";
    }
    cout<<"Good luck with your studies!\n";
    return 0;
}
