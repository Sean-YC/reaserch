#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <iomanip>
#define year 9
using namespace std;
int file(string filename){
    ifstream input;
    int count = 0;
    input.open(filename, ios::in);//read stock data
    string s;
    while (getline(input, s)) {
        if(s!="")
            count++;
    }
    input.close();
    return count;
}
int main(){
    int begin = 0, c = 0,size=0;
    int total;
    double store[256] = { 0.0 };
    string zone[13] = { "MM","QQ","HH","YY","QM","HM","YM","HQ","YQ","YH","M#","H#","Q#" };
    string mode[2]={"1","2"};
    int tradition[16]={5,20,5,60,10,20,10,60,60,120,20,120,20,240,60,240};
    ofstream pha("D:/20190050SMAcheckrule.csv");
    for(int j=0;j<13;j++){
        for(int k=0;k<2;k++) {
            int count = 0, line = 0;
            ifstream input;
            string ffname = "D:/20190050/0.002/20190050SMAphase" + mode[k] + "30" + zone[j] + ".csv";
            size = file(ffname);
            int value;
            vector<int> v;
            input.open(ffname, ios::in);//read stock data
            string s;
            if (j <= 9) {
                string str1(zone[j], 1);
                //cout << str1 << endl;
                string str2 = "M";
                string str3 = "Q";
                string str4 = "H";
                string str5 = "Y";
                if (str1 == str2) {
                    begin = size - year * 360 + 1;
                    total = year * 360 * 4;
                } else if (str1 == str3) {
                    begin = size - year * 120 + 1;
                    total = year * 120 * 4;
                } else if (str1 == str4) {
                    begin = size - year * 60 + 1;
                    total = year * 60 * 4;
                } else if (str1 == str5) {
                    begin = size - year * 30 + 1;
                    total = year * 30 * 4;
                }
            } else {
                if (j == 10) {
                    begin = size - year * 360 + 1;
                    total = year * 360 * 4;
                } else if (j == 11) {
                    begin = size - year * 60 + 1;
                    total = year * 60 * 4;
                } else if (j == 12) {
                    begin = size - year * 120 + 1;
                    total = year * 120 * 4;
                }
            }

            while (getline(input, s)) {
                int rule[4];
                string tmp, day;
                if (s != "")
                    line++;
                stringstream ss(s);
                int stop = 0;
                for (int z = 0; z < 4; z++) {
                    getline(ss, tmp, ',');
                    if (tmp != "") {
                        stringstream a;
                        a << tmp;
                        a >> value;
                        //cout<<value<<endl;
                        for (int x = 0; x < 6; x++) {
                            if (value == tradition[x] && line >= begin) {
                                count++;
                                //cout << "line:" << line << endl;
                                break;
                            }
                        }
                    }
                }/*
                    //=====
                    if (start == count)//the first day of output data
                    begin = count;
                    else if (begin != 0) {
                        if (begin + number == count) {//the last day of output data
                            stop += 1;
                            cout << count << endl;
                        }
                       }//=====
                }*/
                /*
                for (int z = 0; z < 4; z++) {
                    getline(ss, tmp, ',');
                    if (tmp != "") {
                        stringstream a;
                        a << tmp;
                        a >> rule[z];
                        //cout<<value<<endl;
                    }
                }
                for (int x = 0; x < 8; x++) {
                    if (rule[0] == tradition[2 * x] && rule[1] == tradition[2 * x + 1] && line >= begin) {
                        count++;
                        //cout << "line:" << line << endl;
                        break;
                    }
                }
                for (int x = 0; x < 8; x++) {
                    if (rule[3] == tradition[2 * x] && rule[2] == tradition[2 * x + 1] && line >= begin) {
                        count++;
                        //cout << "line:" << line << endl;
                        break;
                    }
                }
            }*/
            }
            input.close();
            //cout << zone[3] << " " << count << " " << total << endl;
            cout<<"SMAphase" + mode[k] + "30" + zone[j]<< " " << count << " " << total << endl;
            pha<<"SMAphase" + mode[k] + "30" + zone[j]<< "," << count << ","<< total << endl;
        }
    }
    pha.close();
    return 0;
}