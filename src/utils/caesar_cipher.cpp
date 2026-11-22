#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <fstream>
#include <cstring>
#include <math.h>

//Jaroslaw_Janiak_2019_ochrona_danych
//szyfr cezara
//caesar cipher

using namespace std;

unsigned char T[65] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
					   '0','1','2','3','4','5','6','7','8','9',
					   '.',',',';',':','!','?','"','@','#','$','%','^','&','*','_','(',')','[',']','{','}','\\','|','/','<','>','+','-','='};

void strcopy(char destiny[], string source) {
	int i = 0;
	do {
		destiny[i] = source[i];
	} while (destiny[i++] != 0);
}

//funkcja modulo (liczy tak¿e modulo dla ujemnych w argumancie liczb zarówno 'q' jak i 'm')
//modulo function with full functionality - posytive/negative value of 'q' and 'm'
int mod(float q, float m) {
	int r = 0;
	int k = 0;

	
	if(m<0 && q>0){
		k = floor(float(fabs(q/m)));
		k = k*(-1);
	} 
	else if(m<0 && q<0){
		k = ceil(float(fabs(q/m)));
		k = k*(-1);
	}
	else if(m>0 && q<0){
		k = ceil(float(fabs(q/m)));
		k = k*(-1);
	}
	else if(m>0 && q>=0){
		k = floor(float(q/m));
	}
	
	r = q - k*m;
	return r;
 }

class T_text {
public:
	string text_str;
	string file_name;

	T_text();
	T_text(string file_name);
	void read();
	void encryption();
	void decryption();
	void inverted_text(string source, string inverted_txt);
	void inverted_text(string source);
	void inverted_text();
	void view_frq();
	void view_text();
	
	private:
	void toUpperCase();
	void eraseWhiteSpace();
	void eraseBeyond();
};

T_text::T_text() {
	text_str = "null";
	
}

T_text::T_text(string file_name) {
	text_str = "null";
	this->file_name = file_name;
	
}

void T_text::inverted_text() {
	int i = 0;
	int str_size = text_str.size();
	string inverted_text;
	inverted_text.resize(str_size);
	
	do {
		inverted_text[i] = text_str[str_size-i-1];
	} while (i++<=str_size);
	
	i=0;	
	do {
		text_str[i] = inverted_text[i];
	} while (i++<=str_size);

	
	cout<<"\n   inverted_text:\n";
	for (int s = 0; s < text_str.size(); s++) cout<<inverted_text[s];
	cout<<"\n   inverted_text set in the field 'text_str':\n";
	for (int s = 0; s < text_str.size(); s++) cout<<text_str[s];

}

void T_text::inverted_text(string source) {
	int i = 0;
	int str_size = source.size();
	string inverted_text;
	inverted_text.resize(str_size);
	
	do {
		inverted_text[i] = source[str_size-i-1];
	} while (i++<=str_size);

	//source = inverted_txt;
	
	cout<<"\n   inverted_text:\n";
	for (int s = 0; s < text_str.size(); s++) cout<<inverted_text[s];
	for (int s = 0; s < text_str.size(); s++) cout<<source[s];

}

void T_text::inverted_text(string source, string inverted_txt) {
	int i = 0;
	int str_size = source.size();
	do {
		inverted_txt[i] = source[str_size-i-1];
		
	} while (i++<=str_size);
	
	cout<<"\n   inverted_text:\n";
	for (int s = 0; s < text_str.size(); s++) cout<<inverted_txt[s];
}

void T_text::view_text() {
	cout<<"\n   text:\n";
	for (int s = 0; s < text_str.size(); s++) cout<<text_str[s];
}

void T_text::view_frq() {
	unsigned int frq[65];
	unsigned int count = 0;
	char q = 'n';
	
	//cout<<"\n\nliczba znakow: "<<text_str.size()-1<<endl;
	
	for(int i =0;i<65;i++) frq[i] = 0;
	
	for(int i=0; i<text_str.size();i++){
                for(int j = 0;j<65;j++){
                    if(text_str[i]==T[j]) {
                            frq[j]++; 
                            count++;
							break;
							}
                }
            }
            
    cout << "\n\n   show the frequency? (y/n): ";
    cin>>q;
    if(q == 'y' || q == 'Y'){        
	    cout<<"\n\nnumber of characters (characters counter): "<<count<<endl;
	    
		cout<<endl;
		for(int i =0;i<65;i++) {
			//if(frq[i]!=0) cout<<T[i] <<": "<< (double(frq[i])/(text_str.size()-1))*100.<<"%\n";
			if(frq[i]!=0) cout<<T[i] <<": "<< (double(frq[i])/(count))*100.<<"%\n";
		}
		
		double qF = 0.0;
		
		for(int i =0;i<65;i++) {
			//q = q + (double(frq[i])/(text_str.size()-1))*100.;
			qF = qF + (double(frq[i])/(count))*100.;
		}
		
		cout<<"\nsum of the frequencies: "<<qF<<"%"<<endl;
		
		qF=0.0;
		
		for(int i =0;i<65;i++) {
			qF = qF + (frq[i]*(frq[i]-1));
		}
		
		qF = qF/((text_str.size()-1)*(text_str.size()-2));
		
		cout<<"\nq: "<<qF<<endl;
	}
}

void T_text::toUpperCase(){
	for(int i=0; i<text_str.size();i++){
		if (islower(text_str[i])) text_str[i] = toupper(text_str[i]);
	}
}

void T_text::eraseWhiteSpace(){
	for(int i=0; i<text_str.size();i++){
		if (text_str[i]=='\n' || text_str[i]==' ') text_str.erase(i,1);
	}
}

void T_text::eraseBeyond(){
	bool flag1 = false;
	bool flag2 = false;
	vector <int> indeksy;
	
	for(int i=0; i<text_str.size();i++){
		for(int j =0;j<65;j++){ 
		 	
			if(text_str[i]==T[j]){
						flag1 = true;
			}
			else if(text_str[i]!=T[j]){
				flag2 = true;
			}	
		}
			 
		if(flag1 == false && flag2==true) indeksy.push_back(i);
		flag1=false;
		flag2=false;
	}

 	
	 cout<<"\ntext_str.size4: "<<text_str.size()<<endl;
	 for (int k = 0; k < indeksy.size(); k++){
		cout<<indeksy[k]<<" ";
	}
	
	int q = 0;
	
	for(int j =0;j<indeksy.size();j++){
		q = indeksy[j]-j;
		if(q<0) q=0;
			text_str.erase(q,1);
	}
}

void T_text::read() {
	//zamiana string: 'name_file' na c-string
	//change 'name_file' string to c-string
	char * cstr = new char[file_name.length() + 1];
	strcopy(cstr, file_name);

	//czytanie textu
	//read text from source file
	ifstream file_text(cstr, std::ios::in);
	text_str.clear();
	if (file_text) {
		while (!file_text.eof())  text_str.push_back(file_text.get());
	}
	file_text.close();
	
	//zamiana na wilkie litery
	//change to upper case
	toUpperCase();
	
	//usowanie znaku nowej linii i spacji
	//remove new line and white space
	eraseWhiteSpace();
	
	//---
	//usowanie znakow spoza alfabetu
	//remove letters
	eraseBeyond();
	//---
	
}

void T_text::encryption() {
	int k = 0;
	cout<<"\ngive the encryption key: "; cin>>k;

    char *a = new char[text_str.size()];

            for(int i=0; i<text_str.size();i++){
                for(int j = 0; j< 65;j++){
                    if(text_str[i]==T[j]) {
                    	if(k<0){
                    		k = -1*(int(fabs(k))%(65-1));
                    		j=mod(65+k+j,65);
						} 
						else{
                            j=mod(k+j,65);
                        }
                        a[i] = T[j]; break;
					}
					else{
						a[i] = text_str[i];
					}
							
                }
            }
            
    for(int i=0; i<text_str.size();i++)  text_str[i] = a[i];
	cout<<"\n   the text has been encrypted! (plik: encrypted_text.txt)\n";
	
	ofstream file_out("encrypted_text.txt");
	for (int s = 0; s < text_str.size(); s++) file_out << text_str[s];
	file_out.close();

}

void T_text::decryption(){
	int k = 0;
	cout<<"\n\ngive the decryption key (usual same as encryption key): "; cin>>k;

    char *a = new char[text_str.size()];

            for(int i=0; i<text_str.size();i++){
                for(int j = 0; j< 65;j++){
                    if(text_str[i]==T[j]) {
                    		
                    		if(k<0){
                    			k = -1*(int(fabs(k))%(65-1));
                    			j=mod(65-k+j,65);
							} 
							else{
								j=mod(65-k+j,65);
							}
                    	         
                            a[i] = T[j]; break;
							}
							else{
							a[i] = text_str[i];
							}
                }
            }
            
    for(int i=0; i<text_str.size();i++) text_str[i] = a[i]; 
	cout<<"\n   the text has been decrypted! (file: decrypted_text.txt)\n\n";
    
    ofstream file_out("decrypted_text.txt");
	for (int s = 0; s < text_str.size(); s++) file_out << text_str[s];
	file_out.close();
    
	
}

int main()
{
	char q = 'n';
	string file_name = "source_text.txt";
	
	//===
	cout << "\n\n   do you want use your txt file? (y/n): ";
    cin>>q;
    if(q == 'y' || q == 'Y'){
		cout << "your file name:";
		cin>>file_name;
	}
	q = 'n';
	//===
	
	T_text t;
	t.file_name = file_name;
	
	//T_text t("source_text.txt");
	t.read();
	//t.view_text();
	t.view_frq();	
	
	//t.inverted_text();
	//t.inverted_text(t.text_str);	
	t.view_frq();
			
	t.encryption(), q = 'n';
	//t.view_text();
	t.view_frq();	
		
	
	t.file_name = "encrypted_text.txt";
	t.read();
	
	t.decryption(), q = 'n';
	//t.view_text();
	t.view_frq();
	
	cout<<endl<<endl;
	system("PAUSE");
	return 0;
}


