#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <iomanip>
#define year 8
using namespace std;
int file(){
	ifstream input;
    int count = 0;
    input.open("C:/Users/ASUS/Desktop/新增資料夾/2412/0.002/20192412EMAphase130YY.csv", ios::in);//read stock data
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
    int tradition[6]={5,10,20,60,120,240};
    size=file();
    ofstream pha("D:/20192412/0.001/20192412SMAcheckrule.csv");
    for(int j=1;j<2;j++){
    	int count=0,line=0;
    	ifstream input;
    	string ffname = "C:/Users/ASUS/Desktop/AAPL/short/2018AAPLshortEMAcompare30MM.csv";
    	int value;
    	vector<int> v;
    	input.open("C:/Users/ASUS/Desktop/新增資料夾/2412/0.002/20192412EMAphase130YY.csv", ios::in);//read stock data
    	string s;
    	if(j<=9){
        	string str1(zone[3],1);
        	cout<<str1<<endl;
        	string str2 = "M";
        	string str3 = "Q";
        	string str4 = "H";
        	string str5 = "Y";
        	if(str1==str2){
        		begin=size-year*360+1;
    			total=year*360*4;
    		}
    		else if(str1==str3){
    			begin=size-year*120+1;
    			total=year*120*4;
    		}
    		else if(str1==str4){
    			begin=size-year*60+1;
    			total=year*60*4;
    		}
    		else if(str1==str5){
    			begin=size-year*30+1;
    			total=year*30*4;
    		}
    	}
    	else{
    		if(j==10){
    			begin=size-year*360+1;
    			total=year*360*4;
			}
			else if(j==11){
				begin=size-year*60+1;
    			total=year*60*4;
			}
			else if(j==12){
				begin=size-year*120+1;
    			total=year*120*4;
			}
		}
    	while(getline(input, s)){
       		string tmp, day;
       		if(s!="")
        		line++;
        	stringstream ss(s);
        	int stop = 0;
        	for (int z = 0; z < 4;z++){
        		getline(ss, tmp, ',');
        		if(tmp!=""){
					stringstream a;
                	a << tmp;
                	a >> value;
                	//cout<<value<<endl;
        			for(int x=0;x<6;x++){
        				if(value==tradition[x]&&line>=begin){
        					count++;
        					cout<<"line:"<<line<<endl;
        					break;
						}
					}
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
        input.close();
        cout<<zone[3]<<" "<<count<<" "<<total<<endl;
    }
}
