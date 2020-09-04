#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <iomanip>
#define year 5
using namespace std;
int main(){
    int begin = 0, c = 0;
    int y, m, d;
    double store[256] = { 0.0 };
    string zone[13] = { "MM","QQ","HH","YY","QM","HM","YM","HQ","YQ","YH","M#","H#","Q#" };
    for(int j=1;j<2;j++){
    	ifstream input;
    	string ffname = "C:/Users/ASUS/Desktop/AAPL/short/2018AAPLshortEMAcompare30MM.csv";
    	double value;
    	vector<int> v;
    	double count = 0;
    	input.open("C:/Users/ASUS/Desktop/AAPL/short/2018AAPLshortEMAcompare30QQ.csv", ios::in);//read stock data
    	string s;
    	while(getline(input, s)){
       		string tmp, day;
        	stringstream ss(s);
        	int stop = 0;
        	for (int j = 0; j < 1; j++) {
        		getline(ss, tmp, ',');
        		if(tmp!=""){
        			cout<<tmp<<endl;
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
        if(j<=9){
        	string str1(zone[j],1);
        	cout<<str1<<endl;
        	string str2 = "M";
        	string str3 = "Q";
        	string str4 = "H";
        	string str5 = "Y";
        	if(str1==str2){
        		for(int i=(v.size()-year*360);i<v.size();i++)
    				count+=v[i];
    			cout<<count<<endl;
    			cout<<setprecision(10)<<double(count/(year*360))<<endl;
    		}
    		else if(str1==str3){
        		for(int i=(v.size()-year*180);i<v.size();i++)
    				count+=v[i];
    			cout<<count<<endl;
    			cout<<setprecision(10)<<double(count/(year*180))<<endl;
    		}
    		else if(str1==str4){
        		for(int i=(v.size()-year*60);i<v.size();i++)
    				count+=v[i];
    			cout<<setprecision(10)<<double(count/(year*60))<<endl;
    		}
    		else if(str1==str5){
        		for(int i=(v.size()-year*30);i<v.size();i++)
    				count+=v[i];
    			cout<<setprecision(10)<<double(count/(year*30))<<endl;
    		}
    	}
    	else{
    		for(int i=0;i<v.size();i++)
    			count+=v[i];
    		cout<<setprecision(10)<<double(count/v.size())<<endl;
		}
    	cout<<v.size()<<endl;
    }
}
