#include "Chaining.h"
Chaining::Chaining(){
        bankStorage2d.resize(100000);
        
    }
 int Chaining:: Binary(vector<int> &x, int k)
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
     void Chaining::qp(vector<int> &x, int k)
    {
        int s = x.size() - 1;
        x.push_back(k);
        while ((x[s] > k) && (s >= 0))
        {
            swap(x[s], x[s + 1]);
            s--;
        }
    }
     void Chaining:: qc(vector<int> &x, int a, int add)
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


void Chaining::createAccount(std::string id, int count) {

    int x=hash(id);
    Account i;
    i.balance=count;
    i.id=id;
    bankStorage2d[x].push_back(i);
    size++;
    qp(bals,count);
    //cout<<"//Accc created:"<<id<<";"<<count<<"Chaining\n";
    //cout<<x<<endl;
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> Chaining::getTopK(int k) {
    vector<int> x;
    int s=bals.size()-1;
    for(int i=0;i<k;i++){
        if(s<0){
            break;
        }
        x.push_back(bals[s]);
        s--;
    }
    return x;
    // IMPLEMENT YOUR CODE HERE
    // Placeholder return value
}

int Chaining::getBalance(std::string id) {
    //cout<<id<<";"<<"getbal\n";
    int x=hash(id);
    //cout<<x<<endl;
    for(int i=0;i<bankStorage2d[x].size();i++){
        //cout<<"intheloop\n";
        if(bankStorage2d[x][i].id==id){
            //cout<<"balance given:chain\n";
            return bankStorage2d[x][i].balance;


        }
    }
                // cout<<"balance given:chain\n";

    return -1;
    // IMPLEMENT YOUR CODE HERE
     // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    //cout<<id<<";"<<count<<"tran\n";
    int x=hash(id);
    for(int i=0;i<bankStorage2d[x].size();i++){
        if(bankStorage2d[x][i].id==id){
            qc(bals,bankStorage2d[x][i].balance,count);
            bankStorage2d[x][i].balance+=count;
            //cout<<"trans made\n";
            return;
        }

    }
    Account i;
    i.id=id;
    i.balance=count;
    bankStorage2d[x].push_back(i);
    size++;
    qp(bals,count);
    // IMPLEMENT YOUR CODE HERE
}

bool Chaining::doesExist(std::string id) {
    int x=hash(id);
    for(int i=0;i<bankStorage2d[x].size();i++){
        if(bankStorage2d[x][i].id==id){
            return true;
        }

    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
      int x=hash(id);
    for(int i=0;i<bankStorage2d[x].size();i++){
        if(bankStorage2d[x][i].id==id){
            int index=Binary(bals,bankStorage2d[x][i].balance);
            bals.erase(bals.begin()+index);            
            auto it=bankStorage2d.begin()+x;
            auto it2=it->begin()+i;
            it->erase(it2);
            size--;
            //cout<<"delete:"<<id<<endl;
            return true;
        }

    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    return size;
    // IMPLEMENT YOUR CODE HERE
 // Placeholder return value
}

int Chaining::x(string& s,int &i){
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
    
// int Chaining::hash(std::string id)
int Chaining::hash(string s){
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
//     Chaining L;
//     L.createAccount("_abcd2476658_8573566351_", 5547);
// L.createAccount("_abcd5937260_2185380740_", 6598);
// L.createAccount("_abcd0860190_2385967542_", 19873);
// L.createAccount("_abcd6219026_1356987525_", 230);
// L.createAccount("_abcd8178386_7808831260_", 5583);
// L.createAccount("_abcd1336904_4501571090_", 4210);
// L.createAccount("_abcd1104679_2689825836_", 13586);
// L.createAccount("_abcd6393146_9817010599_", 18205);
// L.createAccount("_abcd7936311_8358446823_", 15418);
// L.createAccount("_abcd9021677_6308508304_", 9497);
// L.createAccount("_abcd2147861_1618688007_", 14688);
// L.createAccount("_abcd2944253_1544044152_", 286);
// L.createAccount("_abcd1016346_1192235669_", 11622);
// L.createAccount("_abcd5604499_5870791723_", 17472);
// L.createAccount("_abcd9099802_3731078508_", 1958);
// L.createAccount("_abcd8996214_7742884089_", 19637);
// L.createAccount("_abcd0442592_0992751937_", 9296);
// L.createAccount("_abcd0503240_6004350325_", 450);
// L.createAccount("_abcd5751034_6131711702_", 9271);
// L.createAccount("_abcd5967253_3785360236_", 7884);
// L.createAccount("_abcd4617577_3014617759_", 18109);
// L.createAccount("_abcd3804818_6135130873_", 2884);
// L.createAccount("_abcd9990820_3414272669_", 19420);
// L.createAccount("_abcd9504769_0015562941_", 1772);
// L.createAccount("_abcd0444769_8397320656_", 12195);
// L.createAccount("_abcd8743004_3818325028_", 11880);
// L.createAccount("_abcd1417611_7373977645_", 4225);
// L.createAccount("_abcd9218102_3452587606_", 542);
// L.createAccount("_abcd1846643_8027045112_", 16308);
// L.createAccount("_abcd5119825_5187881537_", 11985);
// L.createAccount("_abcd0248684_3661370482_", 1710);
// L.createAccount("_abcd2987099_6046095516_", 13974);
// L.createAccount("_abcd7195474_3467905225_", 2518);
// L.createAccount("_abcd5942588_6598993126_", 14384);
// L.createAccount("_abcd9069471_2018697087_", 10870);
// L.createAccount("_abcd2875111_2833579488_", 5710);
// L.createAccount("_abcd9587907_0219959664_", 17347);
// L.createAccount("_abcd0751047_1003266500_", 957);
// L.createAccount("_abcd5319151_3746698341_", 16874);
// L.createAccount("_abcd4703136_7687239275_", 11570);
// L.createAccount("_abcd5313091_0346561342_", 15846);
// L.createAccount("_abcd1106000_2911132661_", 18216);
// L.createAccount("_abcd8388279_7278508514_", 4168);
// L.createAccount("_abcd1944459_5498319401_", 13396);
// L.createAccount("_abcd9579629_2129568900_", 6151);
// L.createAccount("_abcd5217050_9511482740_", 16857);
// L.createAccount("_abcd8945972_5228216842_", 2473);
// L.createAccount("_abcd8197089_7782457151_", 8098);
// L.createAccount("_abcd4706423_0305585493_", 8650);
// L.createAccount("_abcd8737309_3862905220_", 17766);
// L.createAccount("_abcd6608137_1114537832_", 8690);
// L.createAccount("_abcd3967184_3199538721_", 18495);
// L.createAccount("_abcd2281437_6486836121_", 2253);
// L.createAccount("_abcd7040149_6700836015_", 13006);
// L.createAccount("_abcd0019402_8951970651_", 11944);
// L.createAccount("_abcd7761888_8899684369_", 9431);
// L.createAccount("_abcd1416353_4795033074_", 8049);
// L.createAccount("_abcd9603720_9619302592_", 5778);
// L.createAccount("_abcd1684176_2396882682_", 18892);
// L.createAccount("_abcd2844886_4225844312_", 6647);
// L.createAccount("_abcd6074337_5401132638_", 6188);
// L.createAccount("_abcd4329296_7963979895_", 16378);
// L.createAccount("_abcd2229314_8051601065_", 90);
// L.createAccount("_abcd2046188_5138227750_", 4846);
// L.createAccount("_abcd0579417_2643455617_", 142);
// L.createAccount("_abcd3562283_5810774698_", 4003);
// L.createAccount("_abcd5570863_3907967824_", 7354);
// L.createAccount("_abcd6988215_4755935232_", 9686);
// L.createAccount("_abcd6603094_1660867193_", 16407);
// L.createAccount("_abcd8722296_4332289257_", 16327);
// L.createAccount("_abcd0059303_3153341874_", 3522);
// L.createAccount("_abcd1286376_6403255006_", 7285);
// L.createAccount("_abcd1618490_0759795724_", 8885);
// L.createAccount("_abcd2239984_1990902086_", 18001);
// L.createAccount("_abcd4100356_5869970745_", 19784);
// L.createAccount("_abcd7615337_1182130256_", 8384);
// L.createAccount("_abcd2453371_9050218073_", 6013);
// L.createAccount("_abcd7919016_7986837885_", 2484);
// L.createAccount("_abcd6489693_2629522206_", 14253);
// L.createAccount("_abcd4235275_8547775297_", 3014);
// L.createAccount("_abcd9163481_2951219400_", 3371);
// L.createAccount("_abcd5303157_4816055871_", 11);
// L.createAccount("_abcd8772689_9967990035_", 19754);
// L.createAccount("_abcd7184034_7118649810_", 2554);
// L.createAccount("_abcd5629427_5718941038_", 14193);
// L.createAccount("_abcd3045519_0499183937_", 18484);
// L.createAccount("_abcd1107160_5129572371_", 4489);
// L.createAccount("_abcd2756885_3969312053_", 14911);
// L.createAccount("_abcd8321277_5062263894_", 232);
// L.createAccount("_abcd4816478_4808043952_", 9200);
// L.createAccount("_abcd8407108_4728717879_", 13423);
// L.createAccount("_abcd2466894_8740558382_", 5902);
// L.createAccount("_abcd3612101_1372138332_", 9817);
// L.createAccount("_abcd4343544_4199677787_", 4809);
// L.createAccount("_abcd7758152_4009490775_", 5651);
// L.createAccount("_abcd3416401_5558405550_", 12599);
// L.createAccount("_abcd3338456_3837278368_", 19034);
// L.createAccount("_abcd4571441_4732250330_", 577);
// L.createAccount("_abcd8479293_7347614155_", 4577);
// L.createAccount("_abcd6967940_9313896588_", 19094);
// vector<int> vec=L.getTopK(4);
// // for(int i:vec){
// //     cout<<i<<endl;
// // }
// cout<<vec.size()<<endl;
// }