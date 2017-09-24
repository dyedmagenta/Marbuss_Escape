#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream ifile;
	ofstream ofile;
	string templine="";
	string en="";
	string pl="";
	bool flag=true;
	ifile.open("wesnoth-Marbuss_Escape.po");
	ofile.open("gendia.txt", ofstream::out | ofstream::trunc);
	while(!ifile.eof()){
		getline(ifile,templine);
		//cout<<templine.substr(0,5)<<"\n";
		if(templine.substr(0,5)=="msgid"){
			cout<<templine<<"\n";
			do{
				int ins=0,ine;
				while(flag){
					if(templine[ins]=='\"'){
						flag=false;
					}
					else ins++;
				}
				ine=ins+1;
				while(ine<templine.length()&&!flag){
					if(templine[ine]=='\"'){
						flag=true;
					}
					else ine++;
				}
				cout<<ine<<" "<<ins<<"\n";
				if(ine-ins>1) en=en+templine.substr(ins+1,ine-ins-1)+"\n";
				getline(ifile,templine);
				cout<<"current:"<<templine<<"\n";
			} while(templine[0]=='\"');
		}
		if(templine.substr(0,6)=="msgstr"){
			cout<<templine<<"\n";
			do{
				int ins=0,ine;
				while(flag){
					if(templine[ins]=='\"'){
						flag=false;
					}
					else ins++;
				}
				ine=ins+1;
				while(ine<templine.length()&&!flag){
					if(templine[ine]=='\"'){
						flag=true;
					}
					else ine++;
				}
				if(ine-ins>1) pl=pl+templine.substr(ins+1,ine-ins-1)+"\n";
				getline(ifile,templine);
			}while(templine[0]=='\"');
		}
		if(!(en=="")){
			cout<<"here\n";
			if(pl!=""){
				ofile<<"PL\n"<<pl<<"EN\n"<<en<<"\n";
			}
			else{
				//ofile<<"PL\n\n"<<"EN\n"<<en;
			}
			en="";
			pl="";
		}
		else{
			if(pl!=""){
				cout<<"something went wrong - no english text exist while polish text isn't empty\n";
				pl="";
			}
		}
	}
	cout<<"--END--";
	ifile.close();
	ofile.close();
}
