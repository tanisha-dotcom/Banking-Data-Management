#include "CubicProbing.h"
CubicProbing::CubicProbing(){
        bankStorage1d.resize(100000);
        // for(int i=0;i<100000;i++){
        //     // bankStorage1d[i].balance=-1;
        // }
       
        }
int CubicProbing::Binary(vector<int> &x, int k)
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
     void CubicProbing::qp(vector<int> &x, int k)
    {
        int s = x.size() - 1;
        x.push_back(k);
        while ((x[s] > k) && (s >= 0))
        {
            swap(x[s], x[s + 1]);
            s--;
        }
    }
     void CubicProbing::qc(vector<int> &x, int a, int add)
    {
        int index = Binary(x, a);
        x[index] += add;
        if (add > 0)
        {
            while ((x[index] > x[index + 1]) && (index < x.size()-1))
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



void CubicProbing::createAccount(std::string id, int count)
{
    int y=hash(id);
    int x = hash(id);
    int i=1;
while (true)
{
    // {cout<<bankStorage1d[x].balance;
        if ((bankStorage1d[x].id == "") || (bankStorage1d[x].balance == -2))
        {
            bankStorage1d[x].id = id;
            bankStorage1d[x].balance = count;
            size++;
            qp(bals, count);
            return;
        }
        else{
        // {cout<<"else";
            x=y+(i*i*i);
            i++;
            x = x % bankStorage1d.size();
        }
    }

    // IMPLEMENT YOUR CODE HERE
    // cout<<"accc"<<endl;
}

std::vector<int> CubicProbing::getTopK(int k)
{
    vector<int> x;
    int s = bals.size() - 1;
    for (int i = 0; i < k; i++)
    {
        if(s<0){
            break;
        }
        x.push_back(bals[s]);
        s--;
    }
    return x;
}

int CubicProbing::getBalance(std::string id)
{
    int y=hash(id);
    int x = y;
    int i=1;
    while (!(bankStorage1d[x].id == ""))
    {
        if (bankStorage1d[x].id == id)
        {
            if(bankStorage1d[x].balance==-2){
                return -1;
            }
            return bankStorage1d[x].balance;
        }
        else
        {
            x=y+(i*i*i);
            i++;
            x = x % bankStorage1d.size();
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return -1; // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count)
{
    const int y=hash(id);
    int x = y;
    int i=1;
    while (!(bankStorage1d[x].id == ""))
    {
        if (bankStorage1d[x].id == id)
        {
            if(bankStorage1d[x].balance==-2){
                bankStorage1d[x].balance=count;
                qp(bals,count);
                size++;
                
                return;
            }
            qc(bals, bankStorage1d[x].balance, count);
            bankStorage1d[x].balance += count;
            return;
        }
        else
        {
            x=y+(i*i*i);
            i++;
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

bool CubicProbing::doesExist(std::string id)
{
    int y=hash(id);
    int x = hash(id);
    int i=1;
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
            x=y+(i*i*i);
            i++;
            x = x % bankStorage1d.size();
        }

    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id)
{
   int y=hash(id);
    int x = hash(id);
    int i=1;
    while (!(bankStorage1d[x].id == ""))
    {
        if (bankStorage1d[x].id == id)
        {
            // return bankStorage1d[x].balance;
            if(bankStorage1d[x].balance==-2){
                return false;
            }
            else{
                int index=Binary(bals,bankStorage1d[x].balance);
                bals.erase(bals.begin()+index);
                bankStorage1d[x].balance=-2;
                size--;
                return true;
            }
        }
        else
        {
            x=y+(i*i*i);
            i++;
            x = x % bankStorage1d.size();
        }
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int CubicProbing::databaseSize()
{
    return size;
    // IMPLEMENT YOUR CODE HERE
    return 0; // Placeholder return value
}

int CubicProbing::x(string& s,int &i){
        // cout<<"i:"<<i<<endl;
        int l=0;
        char c=s[i];
        i++;
        l+=(int(c)*256);
         c=s[i];
        i++;
        l+=(int(c));
        // cout<<"l:"<<l<<endl;
        return l*8;
    }
    
int CubicProbing::hash(string s){
    int arr[]={84983,91993,99227,99301,99373,99443,99503,99577,99647,99723,99911};
    int i=0;
    int a=0;
    for(int k=0;k<11;k++){
        a=a+x(s,i);
        a=a%arr[k];


    }
    return a;
}
// int main(){
//     CubicProbing raman=CubicProbing();
// raman.createAccount("CDAD7786825_7990768648", 648);
// for(int i:raman.bals){
//     cout<<i<<";";
// }
// raman.createAccount("DCDA7547234_9919615552" ,552);
// for(int i:raman.bals){
//     cout<<i<<";";
// }

// raman.createAccount("AACB1850545_7974534788", 788);
// for(int i:raman.bals){
//     cout<<i<<";";
// }
// cout<<raman.databaseSize()<<endl;//donr
// raman.createAccount("CDBD5250777_1124276711", 711);
// for(int i:raman.bals){
//     cout<<i<<";";
// }
// raman.createAccount("ABCB8377155_0656808575",575);
// for(int i:raman.bals){
//     cout<<i<<";";
// }
// vector<int> vec;
// vec=raman.getTopK( 1);
// for(int i:vec){
//     cout<<i<<":";
// }//dorn
// cout<<endl;
// raman.createAccount("CDDC3792028_3313680038" ,38);
// for(int i:raman.bals){
//     cout<<i<<";";
// }
// raman.createAccount("CBBA9574444_7470182321" ,321);
// raman.createAccount("DBCC4334636_8057544188" ,188);
// vec=raman.getTopK(3);//done
// for(int i:vec){
//     cout<<i<<":";
// } 
// cout<<endl;
// raman.createAccount("BABD5741078_5109455304" ,304);
// raman.createAccount("BCBA7529510_0817878868" ,868);
// cout<<raman.databaseSize()<<endl;
// vec=raman.getTopK(1); 
// for(int i:vec){
//     cout<<i<<";";
// }
// cout<<endl;
// raman.addTransaction( "BCBA7529510_0817878868" ,-860);
// cout<<raman.getBalance( "BCBA7529510_0817878868")<<endl;
// vec=raman.getTopK( 1);
// for(int i:vec){
//     cout<<i<<":";
// }
// vec=raman.getTopK(5);
// for(int i:vec){
//     // cout<<"yeah\n";
//     cout<<i<<";";
// } 
// cout<<endl;
// // cout<<"sizeofbals"<<raman.bals.size()<<endl;
// // for(int i:raman.bals){
// //     cout<<i<<";";
// // }
// // cout<<endl;
// raman.addTransaction("DCDA7547234_9919615552", 592);
// vec=raman.getTopK(5);
// for(int i:vec){
//     cout<<i<<":";
// } 
// cout<<endl;
// // for(int i:raman.bals){
// //     cout<<i<<";";
// // }
// // cout<<endl;
// cout<<raman.deleteAccount("DCDA7547234_9919615552")<<endl;
// vec=raman.getTopK(4); 
// for(int i:vec){
//     cout<<i<<";";
// }
// cout<<endl;

// cout<<raman.databaseSize()<<endl;
// raman.createAccount("qwer1234567_4567891234",50);
// for(int i:raman.bals){
//     cout<<i<<";";
// }


// }
