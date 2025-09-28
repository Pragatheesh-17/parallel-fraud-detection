#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;

struct Transaction {
    int id;
    double amount;
    string location;
    string time;
};

// Function to generate random time (HH:MM)
string randomTime(mt19937 &gen) {
    uniform_int_distribution<> hour(0, 23);
    uniform_int_distribution<> minute(0, 59);
    int h = hour(gen);
    int m = minute(gen);
    char buffer[6];
    sprintf(buffer, "%02d:%02d", h, m);
    return string(buffer);
}

// Function to generate random location
string randomLocation(mt19937 &gen) {
    string locations[] = {"NY", "LA", "TX", "CHI", "MUM", "LON", "PAR", "TOK"};
    uniform_int_distribution<> dist(0, 7);
    return locations[dist(gen)];
}

int main() {
    int n = 100000; // number of transactions
    ofstream file("../data/transactions.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }

    mt19937 gen(random_device{}());
    uniform_real_distribution<> amount(1, 10000);

    file << "id,amount,location,time\n"; // header

    for (int i = 1; i <= n; i++) {
        Transaction t;
        t.id = i;
        t.amount = amount(gen);
        t.location = randomLocation(gen);
        t.time = randomTime(gen);

        file << t.id << "," << t.amount << "," << t.location << "," << t.time << "\n";
    }

    cout << "Generated " << n << " transactions in data/transactions.csv\n";
    file.close();
    return 0;
}
