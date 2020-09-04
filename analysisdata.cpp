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
int main(){
    int begin = 0, c = 0;
    int y, m, d;
    double store[256] = { 0.0 };
    string zone[13] = { "MM","QQ","HH","YY","QM","HM","YM","HQ","YQ","YH","M#","H#","Q#" };
    //string mode[1] = { "RWMA"};
    string mode[3] = { "SMA","EMA","RWMA" };
    string stockfile("2409");
    for(int k=0;k<3;k++) {
        //ofstream pha("D:/2019"+stockfile+"/0.0001/20192330"+mode[k]+"compare30all.csv");
        ofstream pha("D:/tradition/"+mode[k]+"/20190050"+mode[k]+"comparetest30all.csv");
        for (int j = 0; j < 13; j++) {
            ifstream input;
            //string ffname = "D:/2019"+stockfile+"/0.0001/20192330"+mode[k]+"compare30" + zone[j] + ".csv";
            string ffname = "D:/tradition/"+mode[k]+"/20190050"+mode[k]+"comparetest30" + zone[j] + ".csv";
            double value;
            vector<int> v;
            double count = 0;
            input.open(ffname, ios::in);//read stock data
            string s;
            while (getline(input, s)) {
                string tmp, day;
                stringstream ss(s);
                int stop = 0;
                for (int j = 0; j < 1; j++) {
                    getline(ss, tmp, ',');
                    if (tmp != "") {
                        //cout<<tmp<<endl;
                        stringstream a;
                        a << tmp;
                        a >> value;
                        v.push_back(value);
                    }
                    /*
                    if (start == count)//the first day of output data
                    begin = count;
                    else if (begin != 0) {
                        if (begin + number == count) {//the last day of output data
                            stop += 1;
                            cout << count << endl;
                        }
                       }*/
                }
            }
            if (j <= 9) {
                string str1(zone[j], 1);
                //cout<<str1<<endl;
                string str2 = "M";
                string str3 = "Q";
                string str4 = "H";
                string str5 = "Y";
                if (str1 == str2) {
                    for (int i = (v.size() - year * 360); i < v.size(); i++)
                        count += v[i];
                    double avg = count / (year * 360) / 1000000;
                    if (j == 4) {
                        avg = pow(avg, 4);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    } else if (j == 5) {
                        avg = pow(avg, 2);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    } else if (j == 6) {
                        avg = pow(avg, 1);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    } else {
                        avg = pow(avg, 12);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    }
                } else if (str1 == str3) {
                    for (int i = (v.size() - year * 120); i < v.size(); i++)
                        count += v[i];
                    double avg = count / (year * 120) / 1000000;
                    if (j == 7) {
                        avg = pow(avg, 2);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    } else if (j == 8) {
                        avg = pow(avg, 1);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    } else {
                        avg = pow(avg, 4);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    }
                } else if (str1 == str4) {
                    for (int i = (v.size() - year * 60); i < v.size(); i++)
                        count += v[i];
                    double avg = count / (year * 60) / 1000000;
                    if (j == 9) {
                        avg = pow(avg, 1);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    } else {
                        avg = pow(avg, 2);
                        cout << setprecision(4) << avg - 1.0 << endl;
                        pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                    }
                } else if (str1 == str5) {
                    for (int i = (v.size() - year * 30); i < v.size(); i++)
                        count += v[i];
                    double avg = count / (year * 30) / 1000000;
                    avg = pow(avg, 1);
                    cout << setprecision(4) << avg - 1.0 << endl;
                    pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                }
            } else {
                for (int i = 0; i < v.size(); i++)
                    count += v[i];
                if (j == 10) {
                    double avg = count / (year * 360) / 1000000;
                    avg = pow(avg, 12);
                    cout << setprecision(4) << avg - 1.0 << endl;
                    pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                } else if (j == 11) {
                    double avg = count / (year * 60) / 1000000;
                    avg = pow(avg, 2);
                    cout << setprecision(4) << avg - 1.0 << endl;
                    pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                } else if (j == 12) {
                    double avg = count / (year * 120) / 1000000;
                    avg = pow(avg, 4);
                    cout << setprecision(4) << avg - 1.0 << endl;
                    pha << zone[j] << "," << setprecision(4) << avg - 1.0 << endl;
                }
            }
            //cout<<v.size()<<endl;
        }
    }
}