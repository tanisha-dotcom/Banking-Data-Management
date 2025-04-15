#include "LinearProbing.h"
LinearProbing::LinearProbing(){
        bankStorage1d.resize(100000);
        
        
    }
int LinearProbing::Binary(vector<int> &x, int k)
{
    int i = 0;
    int j = x.size() - 1;
    int mid = (i + j) / 2;
    while (i <= j)
    {
        if (k == x[mid])
        {
            return mid;
        }
        else if (x[mid] < k)
        {
            i = mid + 1;
            mid = (i + j) / 2;
        }
        else
        {
            j = mid - 1;
            mid = (i + j) / 2;
        }
    }
    return x.size();
}
void LinearProbing::qp(vector<int> &x, int k)
{
    int s = x.size() - 1;
    x.push_back(k);
    while ((x[s] > k) && (s >= 0))
    {
        swap(x[s], x[s + 1]);
        s--;
    }
}
void LinearProbing::qc(vector<int> &x, int a, int add)
{
    int index = Binary(x, a);
    x[index] += add;
    if (add > 0)
    {
        while ((x[index] > x[index + 1]) && (index < x.size() - 1))
        {
            swap(x[index], x[index + 1]);
            index++;
        }
    }
    else
    {
        while ((x[index] < x[index - 1]) && (index > 0))
        {
            swap(x[index], x[index - 1]);
            index--;
        }
    }
}

void LinearProbing::createAccount(std::string id, int count)
{

    int x = hash(id);
    while (true)
    {
        if ((bankStorage1d[x].id == "") || (bankStorage1d[x].balance == -2))
        {
            bankStorage1d[x].id = id;
            bankStorage1d[x].balance = count;
            size++;
            qp(bals, count);
            // cout<<"acc created:"<<id<<";"<<count<<endl;
            return;
        }
        else
        {
            x++;
            x = x % bankStorage1d.size();
        }
    }

    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> LinearProbing::getTopK(int k)
{
    vector<int> x;
    int s = bals.size() - 1;
    for (int i = 0; i < k; i++)
    {
        if (s < 0)
        {
            break;
        }
        x.push_back(bals[s]);
        s--;
    }
    return x;
}

int LinearProbing::getBalance(std::string id)
{
    int x = hash(id);
    while (!(bankStorage1d[x].id == ""))
    {
        if (bankStorage1d[x].id == id)
        {
            if (bankStorage1d[x].balance == -2)
            {
                return -1;
            }
            return bankStorage1d[x].balance;
        }
        else
        {
            x++;
            x = x % bankStorage1d.size();
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return -1; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count)
{
    int x = hash(id);
    while (!(bankStorage1d[x].id == ""))
    {
        if (bankStorage1d[x].id == id)
        {
            if (bankStorage1d[x].balance == -2)
            {
                // cout<<bankStorage1d[x].balance/
                bankStorage1d[x].balance = count;
                qp(bals, count);
                size++;
                return;
            }
            qc(bals, bankStorage1d[x].balance, count);
            bankStorage1d[x].balance += count;
            // cout<<"transacion made:"<<id<<";"<<count<<endl;
            return;
        }
        else
        {
            x++;
            x = x % bankStorage1d.size();
        }
    }
    bankStorage1d[x].id = id;
    bankStorage1d[x].balance = count;
    size++;
    qp(bals, count);
    return;

    // IMPLEMENT YOUR CODE HERE
}

bool LinearProbing::doesExist(std::string id)
{
    int x = hash(id);
    while (!(bankStorage1d[x].id == ""))
    {
        if (bankStorage1d[x].id == id)
        {
            if (bankStorage1d[x].balance != -2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            x++;
            x = x % bankStorage1d.size();
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id)
{
    int x = hash(id);
    while (!(bankStorage1d[x].id == ""))
    {
        if (bankStorage1d[x].id == id)
        {
            // return bankStorage1d[x].balance;
            if (bankStorage1d[x].balance == -2)
            {

                return false;
            }
            else
            {
                int index = Binary(bals, bankStorage1d[x].balance);
                bals.erase(bals.begin() + index);
                bankStorage1d[x].balance = -2;
                size--;
                // cout<<id<<":deleted\n";
                return true;
            }
        }
        else
        {
            x++;
            x = x % bankStorage1d.size();
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int LinearProbing::databaseSize()
{
    return size;
    // IMPLEMENT YOUR CODE HERE
    // Placeholder return value
}

int LinearProbing::x(string &s, int &i)
{
    // cout<<"i:"<<i<<endl;
    int l = 0;
    char c = s[i];
    i++;
    l += (int(c) * 256);
    c = s[i];
    i++;
    l += (int(c));
    // cout<<"l:"<<l<<endl;
    return l * 8;
}

int LinearProbing::hash(string s)
{
    int arr[] = {84983, 91993, 99227, 99301, 99373, 99443, 99503, 99577, 99647, 99723, 99911};
    int i = 0;
    int a = 0;
    for (int k = 0; k < 11; k++)
    {
        a = a + x(s, i);
        a = a % arr[k];
    }
    return a;
}

// int main(){
//     LinearProbing r;
//     // r.createAccount("qwerrtyuhgfdcvghtrfdxs",1521);

//     r.addTransaction("qwerrtyuhgfdcvghtrfdxs",-100);
//     r.deleteAccount("qwerrtyuhgfdcvghtrfdxs");
//     r.addTransaction("qwerrtyuhgfdcvghtrfdxs",20);
//     cout<<r.getBalance("qwerrtyuhgfdcvghtrfdxs");
//     return 0;

// }