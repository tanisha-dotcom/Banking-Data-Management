#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include "BaseClass.h"
#include <iostream>

#include <vector>
using namespace std;


class QuadraticProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    QuadraticProbing();
        int Binary(vector<int>&s,int k);
    void qp(vector<int>&s,int k);
    void qc(vector<int>&s,int k,int l); 
    int x(string &s,int&i);

 vector<int> bals;
private:

int size=0;
    // Other data members and functions specific to Quadratic Probing
};

#endif // QUADRATICPROBING_H
