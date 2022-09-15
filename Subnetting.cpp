#include<iostream>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

class Subnet{
	public:
	string ip, cidr;
	int ncidr;
	int octet[4], network_id[4], netmask[4];
	int avl_host;
	int subnets;
		
	Subnet(){
		ip = "";
		cidr = "";
		ncidr = 0;
		avl_host = 0;
		subnets=0;
		for(int i =0 ; i < 4; i++){
			octet[i] = network_id[i] = netmask[i] = 0;
		}
		
	
	}
	
	Subnet(string ip, string cidr){
		this->ip = ip;
		this->cidr = cidr;
	}
	
	void input(){
		cout <<  "Enter input ip: "; cin >> ip;
		cout << "Enter cidr: " ;cin >> cidr;
		filloctet();
		
		for(int i =1; cidr[i] != '\0'; i++){
			ncidr*=10;
			ncidr+=(cidr[i] - '0');
		}
		
		fillNetMask();
		fillNetwordId();
		
		int p = 1;
		for(int i =0 ; i < 32 - ncidr; i++){
			p*=2;
		}
		avl_host = p;
		
	}
	
	void filloctet(){
		string n = "";
		int i = 0;
		int j = 0;
		while(ip[i] != '\0'){
			if(ip[i] == '.'){
				octet[j] = to_number(n);
				n = "";
				j++;
			}
			else{
				n +=ip[i];
			}
			i++;
		}
		
		octet[j] = to_number(n);
	}
	
	int to_number(string s){
		int n = 0;
		for(int i =0;s[i]!='\0';i++){
			n*=10;
			n+=(s[i] - '0');
		}
		return n;
	}
	
	void fillNetMask(){
		int tmpn = ncidr;
		int j = 0;
		while(tmpn > 0){
			if(tmpn >= 8){
				netmask[j] = 255;
				tmpn-=8;
				j++;
			}
			else{
				int ini = 128;
				for(int i = 7; i >= tmpn; i--){
					netmask[j]+= ini;
					ini/=2;
				}
				tmpn = 0;
			}
		}
	}
	
	void fillNetwordId(){
		for(int i =0; i < 4; i++){
			network_id[i] = (netmask[i] & octet[i]);
		}
	}
	
	void subnetting(){
		cout << "Enter number of subnets to from: ";cin>>subnets;
		if(subnets > avl_host){
			cout << "Low Available host number!!\n";
			return;
		}
		
		
		int bitstoborrow = ceil(log2(subnets*1.0));
		
		// int icanform = pow(2, bitstoborrow);
		
		// int extra = icanform - subnets;
		
		int subnetIds[subnets][4];
		for(int i =0 ; i < subnets; i++){
			for(int j =0 ; j< subnets; j++){
				subnetIds[i][j] = network_id[j];
			}
		}
		
		
		int lstbit = 32 - (ncidr + bitstoborrow);
		
		
		for(int i =1 ; i < subnets; i++){
			string binid = binary(i);
			int ini = pow(2, lstbit);
			int n = 0;
			for(int j =0 ; j < bitstoborrow; j++){
				if(binid[j] == '1'){
					n += ini;
				}
				ini*=2;
			}
			
			
			int presentOctet = (ncidr + bitstoborrow)/8;
			subnetIds[i][presentOctet] += n;
		}
		
		for(int i =0; i < subnets; i++){
			for(int j = 0; j < 4; j++){
				cout << subnetIds[i][j] << ".";
			}
			cout << "\n";
		}
		
	}
	
	string binary(int n){
		string res = "";
		while(n > 0){
			res += (n%2 + '0');
			n/=2;
		}
		
		// reverse(res.begin(), res.end());
		return res;
	}
	
	
	void display(){
		cout << "octet: ";
		for(int i = 0; i < 3; i++){
			cout << octet[i] << ".";
		}
		cout << octet[3] ;
		cout << "\n";
		
		cout << "netmask: " ;
		for(int i =0 ; i < 3; i++){
			cout << netmask[i] << ".";
		}
		cout << netmask[3] ;
		cout << "\n";
		
		cout << "network_id: ";
		for(int i =0 ; i < 3; i++){
			cout << network_id[i] << ".";
			
		}
		cout << network_id[3];
		cout << "\n";
		
		cout << "Available Hosts: " << avl_host << "\n";
	}
	
	
};

int main(){
	Subnet s;
	s.input();
	s.display();
	s.subnetting();
	return 0;
}
