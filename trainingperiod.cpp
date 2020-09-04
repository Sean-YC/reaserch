#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <iomanip>
#include <chrono>
using namespace std;
#define sety 2010//2010
#define setm 1
#define setd 4//4
void* new2d(int h, int w, int size) {
    int i;
    void** p;
    p = (void**)new char[h * sizeof(void*) + h * w * size];
    for (int i = 0; i < h; i++)
        p[i] = ((char*)(p + h)) + i * w * size;
    return p;
}
#define NEW2D(H,W,TYPE) (TYPE **)new2d(H,W,sizeof(TYPE))
#define mnumber 133//85month number
#define endfile 2721
void cut(int** period, int& begindate) {
    ifstream input;
    input.open("C:/Users/GD/CLionProjects/2018catchYY/20190050.csv", ios::in);
    string s;
    int year, month, day, record = 0;
    int store[2] = { 0 }, mcount = 0, dcount = 0, over = endfile, count = 0;//1742
    store[0] = 2008;//initial year
    store[1] = 12;//initial month
    while (getline(input, s)) {
        string tmp, time;
        stringstream ss(s);
        for (int j = 0; j < 3; j++) {
            getline(ss, tmp, ',');
            if (j == 0) {
                stringstream date(tmp);
                getline(date, time, '/');
                stringstream a;
                a << time;
                a >> year;
                getline(date, time, '/');
                stringstream b;
                b << time;
                b >> month;
                getline(date, time, '/');
                stringstream c;
                c << time;
                c >> day;
            }
        }
        if (year == sety && month == setm && day == setd)
            record = count;
        count++;
        if (count == over) {
            period[0][mcount] = store[0];
            period[1][mcount] = store[1];
            period[2][mcount] = dcount + 1;
            break;
        }
        if (month != store[1]) {
            //cout<<store[0]<<" "<<store[1]<<endl;
            period[0][mcount] = store[0];
            period[1][mcount] = store[1];
            period[2][mcount] = dcount;
            store[0] = year;
            store[1] = month;
            dcount = 1;
            mcount++;
        }
        else
            dcount++;
    }
    input.close();
    begindate = record;
}
vector<int> slidingwindow(int** period, string choosetime) {
    int train = 0, test = 0, count = 1, day = 0, next = 0, begin = 0;//set begin is 2009
    vector<int> vec;
    int A, B, C;
    if (choosetime == "MM") {
        A = 1;
        B = 1;
        C = 0;
    }
    if (choosetime == "QQ") {
        A = 3;
        B = 3;
        C = 0;
    }
    if (choosetime == "HH") {
        A = 6;
        B = 6;
        C = 0;
    }
    if (choosetime == "YY") {
        A = 12;
        B = 12;
        C = 0;
    }
    if (choosetime == "QM") {
        A = 3;
        B = 1;
        C = 0;
    }
    if (choosetime == "HM") {
        A = 6;
        B = 1;
        C = 0;
    }
    if (choosetime == "YM") {
        A = 12;
        B = 1;
        C = 0;
    }
    if (choosetime == "HQ") {
        A = 6;
        B = 3;
        C = 0;
    }
    if (choosetime == "YQ") {
        A = 12;
        B = 3;
        C = 0;
    }
    if (choosetime == "YH") {
        A = 12;
        B = 6;
        C = 0;
    }
    if (choosetime == "M#") {
        A = 1;
        B = 13;
        C = 1;
        next = 1;
    }
    if (choosetime == "Q#") {
        A = 3;
        B = 15;
        C = 3;
        next = 1;
    }
    if (choosetime == "H#") {
        A = 6;
        B = 18;
        C = 6;
        next = 1;
    }
    while (true) {
        if ((count + A + B - C) <= 133) {
            //all+=period[2][count];
            for (int i = 0; i < A; i++)
                day += period[2][count + i];
            if (period[0][count] == sety && period[1][count] == setm) {//201012
                begin = 1;
                //cout << all << endl;
            }
            cout << period[0][count] << " " << period[1][count] << " " << day << endl;
            if (begin == 1)
                vec.push_back(day);
            day = 0;
        }
        else
            break;
        if (next == 1) {
            if (begin == 1) {
                int temp = 0;
                for (int i = 0; i < B % 12; i++)
                    temp += period[2][count + i];
                //cout << temp << endl;
                for (int i = 0; i < B % 12; i++)
                    day += period[2][count + A + 12 - C + i];
                vec.push_back(day);
                cout << day << endl;
            }
            day = 0;
            count += B % 12;
        }
        else {
            if (begin == 1) {
                int temp = 0;
                for (int i = 0; i < B; i++)
                    temp += period[2][count + i];
                vec.push_back(temp);
                cout << temp << endl;
            }
            for (int i = 0; i < B; i++)
                day += period[2][count + A + i];
            //cout << day << endl;
            day = 0;
            count += B;
        }
    }
    return vec;
}
void measure(double* beta, int size, int** strategy, int num, int** m) {
    double x;
    //int *m;
    int count = 0;
    //m=new int[size];
    for (int i = 0; i < 32; i++) {
        x = rand() / (double)(RAND_MAX + 1);
        if (x > beta[i])
            m[num][i] = 1;
        else
            m[num][i] = 0;
    }
    for (int i = 0; i < 32; i++) {
        //cout<<m[i]<<" ";
        count += pow(2, (7 - i % 8)) * m[num][i];
        if (i % 8 == 7) {
            //cout << m[i] <<" "<<count+1 <<endl;
            strategy[num][i / 8] = count + 1;
            //cout<<strategy[num][i/8]<<endl;
            count = 0;
        }
    }
}
void SMA(vector<double> v, int begin, int day, double** MA) {
    double total = 0.0;
    for (int i = 0; i < 256; i++) {
        double ma = 0.0;
        for (int j = 0; j < i + 1; j++) {
            ma += v[begin + day - j];
        }
        ma /= (i + 1);
        MA[i][day] = ma;
        //total+=ma;
    }
    //for(int i=0;i<day;i++)
    //cout<<MA[160][day]<<endl;
    //cout<<setprecision(10)<<total<<endl;
}
void WMA(vector<double> v, int begin, int day, double** MA) {
    int divisor = 0;
    for (int i = 0; i < 256; i++) {
        double ma = 0.0;
        for (int j = 0; j < i + 1; j++) {
            ma += (i + 1 - j) * v[begin + day - j];
        }
        divisor = ((i + 2) * (i + 1)) / 2;//i+2=1+(i+1)
        ma /= divisor;
        MA[i][day] = ma;
    }
}
void RWMA(vector<double> v, int begin, int day, double** MA) {
    int divisor = 0;
    for (int i = 0; i < 256; i++) {
        double ma = 0.0;
        for (int j = 0; j < i + 1; j++) {
            ma += (1 + j) * v[begin + day - j];
        }
        divisor = ((i + 2) * (i + 1)) / 2;//i+2=1+(i+1)
        ma /= divisor;
        MA[i][day] = ma;
    }
}
void EMA(vector<double> v, int begin, int day, double** MA, double store[256], int count, int stop) {
    if (count < 257) {
        for (int i = 0; i < count; i++) {
            double total = 0.0;
            if (i + 1 == count) {
                for (int j = 0; j < count; j++)
                    total += v[j];
                total /= count;
                store[i] = total;
            }
            else {
                store[i] += 2 * (v[count] - store[i]) / (i + 2);
            }
        }
    }
    else {
        for (int i = 0; i < 256; i++) {
            store[i] += 2 * (v[count] - store[i]) / (i + 2);
        }
    }
    if (begin != 0 && stop != 1) {
        for (int i = 0; i < 256; i++) {
            MA[i][day] = store[i];
        }
        //cout<<MA[0][day]<<endl;
    }
}
void file(vector<double> v, double** MA, double* p, int number, int start) {
    ifstream input;
    int begin = 0, count = 0, c = 0;
    int y, m, d;
    double store[256] = { 0.0 };
    double value;
    input.open("C:/Users/GD/CLionProjects/2018catchYY/20190050.csv", ios::in);
    string s;
    while (getline(input, s)) {
        string tmp, day;
        stringstream ss(s);
        int stop = 0;
        for (int j = 0; j < 2; j++) {
            getline(ss, tmp, ',');
            if (j == 0) {
                stringstream date(tmp);
                getline(date, day, '/');
                stringstream a;
                a << day;
                a >> y;
                getline(date, day, '/');
                stringstream b;
                b << day;
                b >> m;
                getline(date, day, '/');
                stringstream c;
                c << day;
                c >> d;
            }
            else {
                stringstream a;
                a << tmp;
                a >> value;
                v.push_back(value);
            }
        }
        if (start == count)//start==count
            begin = count;
        else if (begin != 0) {
            if (begin + number == count) {//+1
                stop += 1;
                cout << count << endl;
            }
        }
        //EMA(v, begin, c, MA, store, count, stop);
        if (begin != 0 && stop == 0) {
            //cout<<y<<" "<<m<<" "<<d<<endl;
            SMA(v, begin, c, MA);//MA
            p[c] = v[begin + c];
            c++;
        }
        else if (stop == 1) {
            //cout<<c<<endl;
            break;
        }
        count++;
    }
    //cout<<count<<endl;
    input.close();
}
void update(int& gbest, int& worst, int money, double* beta, int** m, int num, int gmatrix[32], int wmatrix[32], int& temp, int four[4]) {//one generation has 10000 strategy
    int count = 0;
    if (money > temp)
        temp = money;
    if (money > gbest) {
        gbest = money;
        for (int i = 0; i < 32; i++)
            gmatrix[i] = m[num][i];
    }
    else if (money <= worst) {
        worst = money;
        for (int i = 0; i < 32; i++)
            wmatrix[i] = m[num][i];
    }
    if (num == 299) {//9999
        //if(iter>1093)//add
        //cout<<temp<<" ";//add
        for (int i = 0; i < 32; i++) {
            if (gmatrix[i] != wmatrix[i] && gmatrix[i] == 0) {
                if (beta[i] + 0.001 <= 1)//1.0
                    beta[i] += 0.001;
            }
            else if (gmatrix[i] != wmatrix[i] && gmatrix[i] == 1) {
                if (beta[i] - 0.001 >= 0)//0.0
                    beta[i] -= 0.001;
            }
            for (int i = 0; i < 32; i++) {
                //cout<<m[i]<<" ";
                count += pow(2, (7 - i % 8)) * gmatrix[i];
                if (i % 8 == 7) {
                    four[i / 8] = count + 1;
                    //cout<<count+1<<" ";
                    count = 0;
                }
            }
        }
    }
}

int trade(int** strategy, double** MA, int num, int section, double* price, double* beta, int** m, int& gbest, int& worst) {
    int origin = 1000000, money = 1000000, stock = 0;
    int remainder;
    int buy = 0, day = 0;
    double rate;
    for (int i = 0; i < section; i++) {
        if (buy == 0) {
            if (MA[strategy[num][0] - 1][i] <= MA[strategy[num][1] - 1][i] &&
                MA[strategy[num][0] - 1][i + 1] > MA[strategy[num][1] - 1][i + 1]) {
                buy += 1;
                stock = int(money / price[1 + i]);
                remainder = int(money - price[1 + i] * stock);
                day = i + 1;
            }
        }
        else {
            if (MA[strategy[num][2] - 1][i] >= MA[strategy[num][3] - 1][i] &&
                MA[strategy[num][2] - 1][i + 1] < MA[strategy[num][3] - 1][i + 1]) {
                buy -= 1;
                day = i + 1;
                money = int(price[1 + i] * stock + remainder);
            }
        }
        if (buy == 1 && i == section - 1) {
            money = int(price[1 + i] * stock + remainder);
            //cout<<price[1+i]<<" "<<stock<<" "<<remainder<<endl;
        }
    }
    //cout<<price[23]<<endl;
    if (money != 1000000) {
        rate = (money - origin);
        //cout << rate/10000.0 << endl;
        //update(gbest,worst,money,beta,m,num);
        return money;
    }
    else
        //update(gbest,worst,origin,beta,m,num);
        return origin;
}
int test(double** MA, int four[4], int section, double* price, double* beta, int** m, int tri) {
    int origin = 1000000, money = 1000000, stock = 0;
    int remainder;
    int buy = 0, day = 0;
    stringstream c;
    stringstream d;
    stringstream e;
    string zzz;
    string phase;
    string ordd;
    if (tri == 1) {
        buy = 1;
        stock = origin / price[1];
        remainder = origin - (price[1] * stock);
    }
    for (int i = 0; i < section; i++) {
        //cout << i + 1 << "," << price[i + 1]<<endl;
        if (buy == 0) {
            if (MA[four[0]-1][i] <= MA[four[1]-1][i] &&
                MA[four[0]-1][i + 1] > MA[four[1]-1][i + 1]) {
                buy += 1;
                stock = money / price[1 + i];
                remainder = money - (price[1 + i] * stock);
                day = i + 1;
                //cout<<"buy: "<<buy<<"day: "<<day<<" "<<price[i]<<endl;
            }
        }
        else {
            if (MA[four[2]-1][i] >= MA[four[3]-1][i] &&
                MA[four[2]-1][i + 1] < MA[four[3]-1][i + 1]) {
                buy -= 1;
                day = i + 1;
                money = price[1 + i] * stock + remainder;
                //cout<<"buy: "<<buy<<"day: "<<day<<" "<<price[i]<<endl;
            }
        }
        if (buy == 1 && i == section - 1) {
            money = price[1 + i] * stock + remainder;
            //cout<<price[1+i]<<" "<<stock<<" "<<remainder<<endl;
        }
    }
    cout<<money<<endl;
    //cout<<price[23]<<endl;
    if (money != 1000000) {
        //rate = (money - origin);
        //cout << rate/10000.0 << endl;
        //update(gbest,worst,money,beta,m,num);
        return money;
    }
    else
        //update(gbest,worst,origin,beta,m,num);
        return origin;
}
int holdstock(int** strategy, double** MA, int num, int section, double* price, double* beta, int** m, int& gbest, int& worst) {
    int origin = 1000000, money = 0, stock = 0;
    int remainder;
    int buy = 1, day = 0;
    double rate;
    stock = int(origin / price[1]);
    remainder = int(origin - price[1] * stock);
    for (int i = 0; i < section; i++) {
        if (buy == 0) {
            if (MA[strategy[num][0] - 1][i] <= MA[strategy[num][1] - 1][i] &&
                MA[strategy[num][0] - 1][i + 1] > MA[strategy[num][1] - 1][i + 1]) {
                buy += 1;
                stock = int(money / price[1 + i]);
                remainder = int(money - price[1 + i] * stock);
                day = i + 1;
            }
        }
        else {
            if (MA[strategy[num][2] - 1][i] >= MA[strategy[num][3] - 1][i] &&
                MA[strategy[num][2] - 1][i + 1] < MA[strategy[num][3] - 1][i + 1]) {
                buy -= 1;
                day = i + 1;
                money = int(price[1 + i] * stock + remainder);
            }
        }
        if (buy == 1 && i == section - 1) {
            money = int(price[1 + i] * stock + remainder);
            //cout<<price[1+i]<<" "<<stock<<" "<<remainder<<endl;
        }
    }
    if (money != 0) {
        rate = (money - origin);
        return money;
    }
    else
        return origin;
}
void func(int begin, int number, vector<double> v, double** MA, double* p) {
    for (int i = 0; i < number + 1; i++) {
        SMA(v, begin, i, MA);//MA
        p[i] = v[begin + i];
        //cout<<i<<endl;
    }
}
void testtime(int &sstart,vector<int> date,string period){
    if(period=="M#"){
        for(int q=0;q<12;q++){
            sstart+=date[2*q];
        }
    }
    else if(period=="Q#"){
        for(int q=0;q<4;q++){
            sstart+=date[2*q];
        }
    }
    else if(period=="H#"){
        for(int q=0;q<2;q++){
            sstart+=date[2*q];
        }
    }
    else{
        sstart+=date[1];
    }
}
int main() {
    auto sta = chrono::steady_clock::now();
    //srand(10);//10
    int size = 32, gbest = 0, start;
    int gmatrix[32] = { 0 }, wmatrix[32] = { 0 };
    int money;
    int** period = NEW2D(3, mnumber, int);
    cut(period, start);
    int** strategy = NEW2D(300, 4, int);//10000
    int** m = NEW2D(300, 32, int);//10000
    vector<double> price;
    double* beta;
    int starty = sety - 1;
    //int regular[16]={5,20,5,60,10,20,10,60,60,120,20,120,20,240,60,240};
    beta = new double[size];
    for (int o = 0; o < 1; o++) {
        //string zone[13] = { "MM","QQ","HH","YY","QM","HM","HQ","YQ","YH","M#","H#","Q#","YM" };
        //string zone[7] = { "HQ","YQ","YH","M#","Q#","H#","YM"};
        string zone[1]={"YM"};
        int sstart = start - 1;
        int teststart=sstart;
        vector<int> date;
        date = slidingwindow(period, zone[o]);
        testtime(teststart,date,zone[o]);
        cout<<zone[o]+" testbegin: "<<teststart<<endl;
        //ofstream pha1("D:/20192105/0.0001/20192105RWMAphase130" + zone[o] + ".csv");
        //ofstream pha2("D:/20192105/0.0001/20192105RWMAphase230" + zone[o] + ".csv");
        ofstream pha3("D:/tradition/SMA/20190050SMAcompare30" + zone[o] + ".csv");
        ofstream pha4("D:/tradition/SMA/20190050SMAcomparetest30" + zone[o] + ".csv");
        int p1four[4] = { 0 };
        int p2four[4] = { 0 };
        int trabest[4];
        int flag=0;
        cout <<zone[o]+" begindate: "<<sstart<<endl;
        //cout << date.size() / 2 << endl;
        for(int l=0;l<date.size();l++)
            cout<<l<<" "<<date[l]<<endl;
        for (int l = 0; l < date.size() / 2; l++) {//date.size()/2
            cout<<" size "<<date.size()<<endl;
            double* p;
            p = new double[date[2 * l] + 1];
            double** MA = NEW2D(256, date[2 * l] + 1, double);
            file(price, MA, p, date[2 * l] + 1, sstart);
            for (int h = 0; h < 30; h++) {
                int g1, g2;
                int compare = 0, count = 0;
                gbest = 0;
                srand(h + 1);
                for (int i = 0; i < size; i++)//initial
                    beta[i] = 0.5;
                for (int j = 0; j < 10000; j++) {
                    for (int i = 0; i < 300; i++) {//10000
                        measure(beta, size, strategy, i, m);
                    }
                    int best_tmp = 0;
                    int worst = 2000000;
                    for (int i = 0; i < 300; i++) {//10000
                        money = trade(strategy, MA, i, date[2 * l], p, beta, m, gbest, worst);//hold money
                        //money = holdstock(strategy, MA, i, 23, p, beta, m, gbest, worst);
                        update(gbest, worst, money, beta, m, i, gmatrix, wmatrix, best_tmp, p1four);
                    }
                    if (compare != best_tmp) {//else if <= gbest
                        compare = best_tmp;//gbest
                        count = 0;
                    }
                    else {
                        count++;
                    }
                    if (count == 30) {//30
                        int num = 0;
                        for (int i = 0; i < 32; i++) {
                            //cout<<m[i]<<" ";
                            num += pow(2, (7 - i % 8)) * gmatrix[i];
                            if (i % 8 == 7) {
                                //cout << m[i] <<" "<<count+1 <<endl;
                                cout << num + 1 << " ";
                                p1four[i / 8] = num;
                                //cout<<strategy[num][i/8]<<endl;
                                num = 0;
                            }
                        }
                        cout << endl;
                        cout << j << endl;
                        break;
                    }
                }
                //pha1.close();
                //pha1 << p1four[0] + 1 << "," << four[1] + 1 << "," << four[2] + 1 << "," << four[3] + 1 << ",";
                // pha1 << gbest << endl;
                g1 = gbest;
                //---------------
                //datetest(four,MA,248,p,0,gbest);
                srand(h + 1);//10
                gbest = 0;//holdstock
                count = 0;
                compare = 0;
                for (int i = 0; i < size; i++)//initial
                    beta[i] = 0.5;
                for (int j = 0; j < 10000; j++) {
                    for (int i = 0; i < 300; i++) {//10000
                        measure(beta, size, strategy, i, m);
                    }
                    int best_tmp = 0;
                    int worst = 2000000;
                    for (int i = 0; i < 300; i++) {//10000
                        //money = trade(strategy, MA, i, 23, p, beta, m, gbest, worst);//hold money
                        money = holdstock(strategy, MA, i, date[2 * l], p, beta, m, gbest, worst);
                        update(gbest, worst, money, beta, m, i, gmatrix, wmatrix, best_tmp, p2four);
                    }
                    //cout << j << endl;
                    if (compare != best_tmp) {//else if <= gbest
                        compare = best_tmp;//gbest
                        count = 0;
                    }
                    else {
                        count++;
                    }
                    if (count == 30) {//30
                        int num = 0;
                        for (int i = 0; i < 32; i++) {
                            //cout<<m[i]<<" ";
                            num += pow(2, (7 - i % 8)) * gmatrix[i];
                            if (i % 8 == 7) {
                                //cout << m[i] <<" "<<count+1 <<endl;
                                cout << num + 1 << " ";
                                p2four[i / 8] = num;
                                //cout<<strategy[num][i/8]<<endl;
                                num = 0;
                            }
                        }
                        cout << endl;
                        cout << j << endl;
                        break;
                    }
                }
                //pha2 << four[0] + 1 << "," << four[1] + 1 << "," << four[2] + 1 << "," << four[3] + 1 << ",";
                // pha2 << gbest << endl;
                g2 = gbest;
                if (g1 >= g2){
                    pha3 << g1 << endl;
                    for(int i=0;i<4;i++)
                        trabest[i]=p1four[i]+1;
                    flag=0;
                }
                else {
                    pha3 << g2 << endl;
                    for (int i = 0; i < 4; i++)
                        trabest[i] = p2four[i] + 1;
                    flag=1;
                }
                //cout << gbest << endl;
                if(o<=9) {
                    //for (int h = 0; h < 2; h++)
                    //trabest[h] = regular[2 * flag + h];
                    if(l!=date.size()/2-1){
                        double *pp;
                        pp = new double[date[2 * l + 2] + 1];
                        double **testMA = NEW2D(256, date[2 * l + 2] + 1, double);
                        file(price, testMA, pp, date[2 * l + 2] + 1, teststart);
                        pha4 << test(MA, trabest, date[2 * l + 2], pp, beta, m, flag) << endl;
                    }
                    else {
                        cout << "now last L=" << l << endl;
                        int end= endfile-teststart;
                        double *pp;
                        pp = new double[end + 1];
                        double **testMA = NEW2D(256, end + 1, double);
                        file(price, testMA, pp, end + 1, teststart);
                        pha4 << test(MA, trabest, end, pp, beta, m, flag) << endl;
                    }
                }
                else{
                    //for(int h=0;h<2;h++)
                    //trabest[h]=regular[2*flag+h];
                    double* pp;
                    pp = new double[date[2 * l+1] + 1];
                    double** testMA = NEW2D(256, date[2 * l+1] + 1, double);
                    cout<<zone[o]+" testbegin: "<<teststart<<endl;
                    file(price, testMA, pp, date[2 * l+1] + 1, teststart);
                    pha4<<test(MA,trabest,date[2 * l+1], pp, beta, m,flag)<<endl;
                }
            }
            /*
            int trabest[2],flag;
            int profit=0;
            for(int i=0;i<8;i++){
                int ttemp[2]={regular[2*i],regular[2*i+1]};
                int tp=test(MA,ttemp,date[2 * l], p, beta, m,0);
                if(tp>profit){
                    profit=tp;
                    flag=i;
                }
            }*/
            //sstart += date[2 * l + 1];
            if(o<=9) {
                //for (int h = 0; h < 2; h++)
                //trabest[h] = regular[2 * flag + h];
                if(l!=date.size()/2-1){
                    sstart += date[2 * l + 1];
                    teststart += date[2 * l + 3];
                }
                /*else {
                    cout << "now last L=" << l << endl;
                    int end= endfile-teststart;
                    double *pp;
                    pp = new double[end + 1];
                    double **testMA = NEW2D(256, end + 1, double);
                    file(price, testMA, pp, end + 1, teststart);
                    pha4 << test(MA, trabest, end, pp, beta, m, 0) << endl;
                }*/
            }
            else{
                //for(int h=0;h<2;h++)
                //trabest[h]=regular[2*flag+h];
                sstart += date[2 * l];
                teststart+=date[2*l+1];
            }
            //pha1 << endl;
            //pha2 << endl;
            pha3 << endl;
            pha4 << endl;
        }
        //pha1.close();
        //pha2.close();
        pha3.close();
        pha4.close();
    }
    //datetest(four,MA,248,p,1,gbest);
    auto end = chrono::steady_clock::now();
    cout << "time: " << chrono::duration<double>(end - sta).count() << "s" << endl;
    system("pause");
    return 0;
}
