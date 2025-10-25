#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct ExtraBill {
    string billName;
    double amount;
};

struct Member {
    string name;
    double homeRent;
    double electricity;
    vector<ExtraBill> extraBills;
};

struct SharedBill {
    string billName;
    double amount;
};

void printBillHeader(const string& month) {
    cout << "\n" << string(60, '=') << endl;
    cout << setw(35) << "MEMBER BILL" << endl;
    cout << setw(35) << "Month: " << month << endl;
    cout << string(60, '=') << endl;
}

void printBill(const Member& member, const vector<SharedBill>& sharedBills, int numMembers, const string& month) {
    printBillHeader(month);
    
    cout << "\nMember Name: " << member.name << endl;
    cout << string(60, '-') << endl;
    
    cout << left << setw(30) << "Bill Item" << right << setw(15) << "Amount (BDT)" << endl;
    cout << string(60, '-') << endl;
    
    double total = 0.0;
    
    // Individual bills
    cout << left << setw(30) << "Home Rent" << right << setw(15) << fixed << setprecision(2) << member.homeRent << endl;
    total += member.homeRent;
    
    cout << left << setw(30) << "Electricity" << right << setw(15) << fixed << setprecision(2) << member.electricity << endl;
    total += member.electricity;
    
    // Extra bills for this member
    if (!member.extraBills.empty()) {
        cout << "\nExtra Bills:" << endl;
        cout << string(60, '-') << endl;
        
        for (const auto& extra : member.extraBills) {
            cout << left << setw(30) << extra.billName << right << setw(15) << fixed << setprecision(2) << extra.amount << endl;
            total += extra.amount;
        }
    }
    
    // Shared bills (divided equally)
    if (!sharedBills.empty()) {
        cout << "\nShared Bills (Split among " << numMembers << " members):" << endl;
        cout << string(60, '-') << endl;
        
        for (const auto& bill : sharedBills) {
            double perPersonShare = bill.amount / numMembers;
            cout << left << setw(30) << bill.billName << right << setw(15) << fixed << setprecision(2) << perPersonShare << endl;
            total += perPersonShare;
        }
    }
    
    cout << string(60, '=') << endl;
    cout << left << setw(30) << "TOTAL AMOUNT" << right << setw(15) << fixed << setprecision(2) << total << endl;
    cout << string(60, '=') << endl;
}

int main() {
    int numMembers;
    string month;
    vector<Member> members;
    vector<SharedBill> sharedBills;
    
    cout << "===== BILL MANAGEMENT SYSTEM =====" << endl;
    
    // Input month
    cout << "\nEnter month name (e.g., October 2025): ";
    getline(cin, month);
    
    cout << "\nEnter number of members: ";
    cin >> numMembers;
    cin.ignore(); // Clear newline from buffer
    
    // Input member details
    for (int i = 0; i < numMembers; i++) {
        Member member;
        cout << "\n--- Member " << (i + 1) << " ---" << endl;
        cout << "Enter name: ";
        getline(cin, member.name);
        cout << "Enter home rent: ";
        cin >> member.homeRent;
        cout << "Enter electricity bill: ";
        cin >> member.electricity;
        cin.ignore(); // Clear newline
        
        // Ask for extra bills for this member
        char hasExtra;
        cout << "Does " << member.name << " have any extra bills? (y/n): ";
        cin >> hasExtra;
        cin.ignore();
        
        if (hasExtra == 'y' || hasExtra == 'Y') {
            int numExtra;
            cout << "How many extra bills for " << member.name << "? ";
            cin >> numExtra;
            cin.ignore();
            
            for (int j = 0; j < numExtra; j++) {
                ExtraBill extra;
                cout << "  Extra bill " << (j + 1) << " name: ";
                getline(cin, extra.billName);
                cout << "  Amount: ";
                cin >> extra.amount;
                cin.ignore();
                
                member.extraBills.push_back(extra);
            }
        }
        
        members.push_back(member);
    }
    
    // Input shared bills
    cout << "\n===== SHARED BILLS =====" << endl;
    
    // WiFi
    SharedBill wifi;
    wifi.billName = "WiFi";
    cout << "\nEnter WiFi bill amount: ";
    cin >> wifi.amount;
    sharedBills.push_back(wifi);
    
    // Bua (Maid)
    SharedBill bua;
    bua.billName = "Bua (Maid)";
    cout << "Enter Bua (Maid) bill amount: ";
    cin >> bua.amount;
    sharedBills.push_back(bua);
    
    // Moyla (Cook)
    SharedBill moyla;
    moyla.billName = "Moyla (Cook)";
    cout << "Enter Moyla (Cook) bill amount: ";
    cin >> moyla.amount;
    sharedBills.push_back(moyla);
    
    // Option to add more shared bills
    char addMore;
    cout << "\nDo you want to add more shared bills? (y/n): ";
    cin >> addMore;
    cin.ignore();
    
    if (addMore == 'y' || addMore == 'Y') {
        int numAdditional;
        cout << "How many additional shared bills? ";
        cin >> numAdditional;
        cin.ignore();
        
        for (int i = 0; i < numAdditional; i++) {
            SharedBill bill;
            cout << "\n--- Additional Bill " << (i + 1) << " ---" << endl;
            cout << "Enter bill name (e.g., Gas, Water, Newspaper): ";
            getline(cin, bill.billName);
            cout << "Enter amount: ";
            cin >> bill.amount;
            cin.ignore();
            
            sharedBills.push_back(bill);
        }
    }
    
    // Print individual bills for all members
    cout << "\n\n";
    cout << string(60, '#') << endl;
    cout << setw(40) << "GENERATING INDIVIDUAL BILLS" << endl;
    cout << string(60, '#') << endl;
    
    for (const auto& member : members) {
        printBill(member, sharedBills, numMembers, month);
        cout << "\n";
    }
    
    return 0;
}
