#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <cmath>
#include <sstream>
using namespace std;
int main(){
	
	char op[]={'+','-','*','/'};
	set<char> s(op,op+4);  //set s��B��l 
	stack<char> sta;  //��B��l 
	bool negative=false;  //�O�B�⤸�O���O�t�� 
	string infix; //���Ԧ� 
	string num;  //�O�B�⤸
	vector<string> postfix;  //��Ԧ�
	
	//��J���l 
	cout<<"�п�J���l:";
	cin>>infix;
	
	//�ର��Ԧ� 
	for(int i=0;i<infix.size();i++){
		if(infix[i]=='('){
			sta.push('('); 
		} 
		else if(infix[i]==')'){
			while(sta.top()!='('){
				postfix.push_back(string()+sta.top());
				sta.pop();
			}
			sta.pop();  //pop�����A�� 
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
			if(i>0&&s.find(infix[i-1])==s.end()&&infix[i-1]!='('){  //�e�����B��l�M���A�� ��ܳo�ӭt�����B��l 
				while(!sta.empty()){
					if(sta.top()=='(')
						break;
					postfix.push_back(string()+sta.top());
					sta.pop();
				}
				sta.push('-');
			}
			else{  //���t�ƪ��t�� 
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
		else{  //�B�⤸ 
			num="";
			if(negative){
				num+='-';
				negative=false;
			}
			while(i<infix.size()){
				num+=infix[i];
				i++;
				if(i==infix.size()||s.find(infix[i])!=s.end()||infix[i]==')'){   //�J��B��l�Υk�A�� ���Ū�����@�ӹB�⤸ 
					postfix.push_back(num);
					i--;
					break;
				}			
			}
			
		} 
	}
	//��ѤU���B��lpop�� 
	while(!sta.empty()){
		postfix.push_back(string()+sta.top());
		sta.pop();
	}
	
	
	//��X��Ԧ� 
	cout<<"\n��Ԧ�:"; 
	for(int i=0;i<postfix.size();i++)
		cout<<postfix[i];
		
		
	//�B�� 
	stack<int> ista;  //��B�⤸ 
	int a,b;
	stringstream ss;
	for(int i=0;i<postfix.size();i++){
		//Ū��B��lpop��ӹB�⤸�B�� 
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
		else{  //Ū��B�⤸ 
			int n;
			ss<<postfix[i];
			ss>>n;
			char c;  //Ū '^' 
			stack<int> sp;  //����� �����ƥi�H�q�᭱�}�l�� 
			sp.push(n);
			while(ss>>c){  //�� ^ ��ܬO���� 
				int power;  //���ƪ��� 
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
	
	//��X���� 
	cout<<endl<<"\n����:"<<ista.top()<<endl<<endl;   
	
	system("pause");
	return 0;
} 


