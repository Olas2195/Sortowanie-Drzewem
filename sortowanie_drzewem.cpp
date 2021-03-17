#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Wezel {
	string slowo;	
	Wezel *lewy;
	Wezel *prawy;
};

vector <string> lista;	
Wezel* korzen = NULL;

class Drzewo{
	ifstream plik1;
	ofstream plik2;
	
	public:		
		void wczytaj();
		void pracaStringiem();
		void tworzenieDrzewa();
		void wstawianie(Wezel *&korzen, string wyraz);		
		void rozczytywanie(Wezel *wezelek);
		void zapis();
		void usuwanieDrzewa(Wezel *wezelek);

};
void Drzewo::wczytaj() {
	string x;
	int y;
	
	plik1.open("we.txt");
	if(plik1.good()) {
		while(!plik1.eof()) {
			getline(plik1, x);
    		lista.push_back(x);
		}
	}
	plik1.close();
}

void Drzewo::pracaStringiem() {
	string cos;
	for (int i = 0; i < lista.size(); i++) {
		cos = lista[i];
		for(int j=0; j< cos.length(); j++) {
			if(cos[j]<95)
				cos[j]+=32;
		}
		lista[i] = cos;
	}	
}

void Drzewo::tworzenieDrzewa() {
	for (int i = 0; i < lista.size(); i++) {
    	this->wstawianie(korzen, lista[i]);
	}	
}

void Drzewo::wstawianie(Wezel *&korzen, string wyraz) {	
	Wezel *w;
	Wezel *miejsce;

	w = new Wezel;           
	w->lewy = NULL;
	w->prawy = NULL;
	w->slowo = wyraz;        
	miejsce = korzen;

	if(!miejsce) {
		korzen = w;
	}			                
  	else {	
   		while(true) {   			
   			bool ok=true;
   			bool przerwij=true;
   			int i=0;	
   			
   			do{	
	    		if(wyraz[i] < miejsce->slowo[i]) {     
    	    		if(!miejsce->lewy) {
        	  			miejsce->lewy = w;
        	  			przerwij = false;
          				break;
        			}
	        		else {
    	    			miejsce = miejsce->lewy;
					} 
      			}
	      		if(wyraz[i] > miejsce->slowo[i]) {
    	    		if(!miejsce->prawy) { 
        				miejsce->prawy = w;
						przerwij = false;
          				break;
	        		}
    	    		else{
        				miejsce = miejsce->prawy;	
					} 
	      		}
	      		if(wyraz[i] == miejsce->slowo[i]) {
    	  			ok = false;
    	  			i++;
				}
			}while(ok==false && i<wyraz.length());
			if(!przerwij) {
				break;
			}
		}	
	}
}

void Drzewo::zapis() {
	plik2.open("wy.txt");
	this->rozczytywanie(korzen);
	plik2.close();
}

void Drzewo::rozczytywanie(Wezel *wezelek) {
	if(wezelek) {
    	rozczytywanie(wezelek->lewy);
    	cout<<wezelek->slowo<<"\n";
    	plik2<<wezelek->slowo<<"\n";
    	rozczytywanie(wezelek->prawy);
	}
}

void Drzewo::usuwanieDrzewa(Wezel *wezelek) {
	if(wezelek) {
		usuwanieDrzewa(wezelek->lewy);
		usuwanieDrzewa(wezelek->prawy);
		delete wezelek;
	}
}


int main(int argc, char** argv) {
	Drzewo d1;
	
	d1.wczytaj();
	d1.pracaStringiem();
	d1.tworzenieDrzewa();
	d1.zapis();
	d1.usuwanieDrzewa(korzen); 
	
	return 0;
}
