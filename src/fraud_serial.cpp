#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Transaction {
    int id;
    double amount;
    string location;
    string time;
};

// Simple fraud rules
bool isFraud(const Transaction &t) {
    if (t.amount > 9000) return true; // suspiciously large
    if (t.location == "MUM" && stoi(t.time.substr(0, 2)) < 6) return true; // odd hours in Mumbai
    return false;
}

int main() {
    ifstream file("../data/transactions.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open dataset.\n";
        return 1;
    }

    string line;
    getline(file, line); // skip header

    vector<Transaction> frauds;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Transaction t;

        getline(ss, token, ','); t.id = stoi(token);
        getline(ss, token, ','); t.amount = stod(token);
        getline(ss, token, ','); t.location = token;
        getline(ss, token, ','); t.time = token;

        if (isFraud(t)) frauds.push_back(t);
    }

    cout << "Fraudulent transactions detected: " << frauds.size() << "\n";
    for (size_t i = 0; i < min((size_t)10, frauds.size()); i++) {
        cout << "ID: " << frauds[i].id << " Amount: " << frauds[i].amount
             << " Location: " << frauds[i].location
             << " Time: " << frauds[i].time << "\n";
    }

    return 0;
}
