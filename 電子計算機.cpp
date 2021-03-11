#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <cmath>
#include <sstream>
using namespace std;
int main(){
	
	char op[]={'+','-','*','/'};
	set<char> s(op,op+4);  //set s放運算子 
	stack<char> sta;  //放運算子 
	bool negative=false;  //記運算元是不是負數 
	string infix; //中敘式 
	string num;  //記運算元
	vector<string> postfix;  //後敘式
	
	//輸入式子 
	cout<<"請輸入式子:";
	cin>>infix;
	
	//轉為後敘式 
	for(int i=0;i<infix.size();i++){
		if(infix[i]=='('){
			sta.push('('); 
		} 
		else if(infix[i]==')'){
			while(sta.top()!='('){
				postfix.push_back(string()+sta.top());
				sta.pop();
			}
			sta.pop();  //pop掉左括號 
		}
		else if(infix[i]=='+'){
			while(!sta.empty()){
				if(sta.top()=='(')
					break;
				postfix.push_back(string()+sta.top());
				sta.pop();
			}
			sta.push('+');
		}
		else if(infix[i]=='-'){
			if(i>0&&s.find(infix[i-1])==s.end()&&infix[i-1]!='('){  //前不為運算子和左括號 表示這個負號為運算子 
				while(!sta.empty()){
					if(sta.top()=='(')
						break;
					postfix.push_back(string()+sta.top());
					sta.pop();
				}
				sta.push('-');
			}
			else{  //為負數的負號 
				negative=true;
			}
				
		}
		else if(infix[i]=='*'||infix[i]=='/'){
			if(!sta.empty()){
				while(sta.top()=='*'||sta.top()=='/'){
					postfix.push_back(string()+sta.top());
					sta.pop();
					if(sta.empty())
						break;
				}
			}
			sta.push(infix[i]);
		}
		else{  //運算元 
			num="";
			if(negative){
				num+='-';
				negative=false;
			}
			while(i<infix.size()){
				num+=infix[i];
				i++;
				if(i==infix.size()||s.find(infix[i])!=s.end()||infix[i]==')'){   //遇到運算子或右括號 表示讀完的一個運算元 
					postfix.push_back(num);
					i--;
					break;
				}			
			}
			
		} 
	}
	//把剩下的運算子pop掉 
	while(!sta.empty()){
		postfix.push_back(string()+sta.top());
		sta.pop();
	}
	
	
	//輸出後敘式 
	cout<<"\n後敘式:"; 
	for(int i=0;i<postfix.size();i++)
		cout<<postfix[i];
		
		
	//運算 
	stack<int> ista;  //放運算元 
	int a,b;
	stringstream ss;
	for(int i=0;i<postfix.size();i++){
		//讀到運算子pop兩個運算元運算 
		if(postfix[i]=="+"){
			b=ista.top(); ista.pop();
			a=ista.top(); ista.pop();
			ista.push(a+b);
		}
		else if(postfix[i]=="-"){
			b=ista.top(); ista.pop();
			a=ista.top(); ista.pop();
			ista.push(a-b);
		}
		else if(postfix[i]=="*"){
			b=ista.top(); ista.pop();
			a=ista.top(); ista.pop();
			ista.push(a*b);
		}
		else if(postfix[i]=="/"){
			b=ista.top(); ista.pop();
			a=ista.top(); ista.pop();
			ista.push(a/b);
		}
		else{  //讀到運算元 
			int n;
			ss<<postfix[i];
			ss>>n;
			char c;  //讀 '^' 
			stack<int> sp;  //放指數 讓指數可以從後面開始算 
			sp.push(n);
			while(ss>>c){  //有 ^ 表示是指數 
				int power;  //指數的值 
				ss>>power;
				sp.push(power);
			}
			n=sp.top(); sp.pop();
			while(!sp.empty()){
				b=sp.top(); sp.pop();
				n=pow(b,n);
			}
			ista.push(n);
			ss.str("");
			ss.clear();			
		}	
	} 
	
	//輸出答案 
	cout<<endl<<"\n答案:"<<ista.top()<<endl<<endl;   
	
	system("pause");
	return 0;
} 


