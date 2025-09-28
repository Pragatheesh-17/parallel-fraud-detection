#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Transaction {
    int id;
    double amount;
    std::string location;
    std::string time;
};

int main() {
    std::ifstream inFile("../data/transactions.csv");
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open transactions.csv" << std::endl;
        return 1;
    }

    std::vector<Transaction> transactions;
    std::vector<Transaction> anomalies;

    std::string line;
    getline(inFile, line); // skip header row

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;
        Transaction t;

        // id
        if (!getline(ss, field, ',')) continue;
        try { t.id = stoi(field); } catch (...) { continue; }

        // amount
        if (!getline(ss, field, ',')) continue;
        try { t.amount = stod(field); } catch (...) { continue; }

        // location
        if (!getline(ss, field, ',')) continue;
        t.location = field;

        // time
        if (!getline(ss, field, ',')) continue;
        t.time = field;

        transactions.push_back(t);
    }
    inFile.close();

    // Fraud detection rule: amount > 5000
    for (auto &t : transactions) {
        if (t.amount > 5000.0) {
            anomalies.push_back(t);
        }
    }

    // Save anomalies to results file
    std::ofstream outFile("../results/serial_output.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open results file" << std::endl;
        return 1;
    }

    for (auto &t : anomalies) {
        outFile << "ID=" << t.id
                << " | Amount=" << t.amount
                << " | Location=" << t.location
                << " | Time=" << t.time
                << std::endl;
    }
    outFile.close();

    std::cout << "Processed " << transactions.size() << " transactions.\n";
    std::cout << "Detected " << anomalies.size()
              << " anomalies. Results written to results/serial_output.txt\n";

    return 0;
}
