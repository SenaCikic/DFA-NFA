#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <iterator>
#include <algorithm>
using namespace std;

#define maks 32


class DFA
{
    vector<int> stanja, zavrsnaStanja;
    vector<char> alfabet;
    int brojStanja, brojSimbola, pocetnoStanje, brojZavrsnih;
    map<pair<int,char>,int> tranzicija;

    void unesiBrojStanja();
    void unesiStanja();
    void unesiBrojSimbola();
    void unesiSimbole();
    void unesiPocetno();
    void unesiBrojZavrsnih();
    void unesiZavrsna();
    void unesiTranziciju();
public:
    DFA()
    {
        unesiBrojStanja();
        unesiStanja();
        unesiBrojSimbola();
        unesiSimbole();
        unesiPocetno();
        unesiBrojZavrsnih();
        unesiZavrsna();
        unesiTranziciju();
    }

    map<pair<int,char>, int> vratiTranziciju()
    {
        return tranzicija;
    }

    DFA(vector<int> stanja,vector<int> zavrsnaStanja,vector<char> alfabet, int pocetnoStanje, map<pair<int,char>,int> tranzicija);
    int dajBrojStanja()
    {
        return brojStanja;
    }
    int dajBrojSimbola()
    {
        return brojSimbola;
    }
    int dajBrojZavrsnih()
    {
        return brojZavrsnih;
    }
    void ispisiTranziciju();

    void ispisiDFA();

    bool prihvata(string w);
};
void DFA :: unesiBrojStanja()
{
    int s;
    cout << "Unesite broj stanja od DFA: ";
    cin >> s;
    this->brojStanja=s;
}
DFA::DFA(vector<int> stanja,vector<int> zavrsnaStanja,vector<char> alfabet, int pocetnoStanje, map<pair<int,char>,int> tranzicija)
{
    this->stanja = stanja;
    this->zavrsnaStanja = zavrsnaStanja;
    this->alfabet = alfabet;
    this->pocetnoStanje = pocetnoStanje;
    this->brojSimbola = alfabet.size();
    this->brojStanja = stanja.size();
    this->brojZavrsnih = zavrsnaStanja.size();
    this->tranzicija = tranzicija;
}
void DFA :: unesiStanja()
{
    stanja.resize(dajBrojStanja());
    cout << "Unesite stanja od DFA: ";
    for(int i=0; i<stanja.size(); i++)
        cin >> stanja[i];
}
void DFA :: unesiBrojSimbola()
{
    int s;
    cout << "Unesite broj simbola alfabeta DFA: ";
    cin>>s;
    this->brojSimbola=s;
}
void DFA :: unesiSimbole()
{
    alfabet.resize(dajBrojSimbola());
    cout << "Unesite simbole alfabeta DFA: ";
    for(int i=0; i<alfabet.size(); i++)
        cin >> alfabet[i];
}
void DFA :: unesiPocetno()
{
    int p;
    cout << "Unesite pocetno stanje od DFA: ";
    cin >> p;
    this->pocetnoStanje=p;
}
void DFA :: unesiBrojZavrsnih()
{
    int z;
    cout << "Unesite broj zavrsnih stanja od DFA: ";
    cin>>z;
    this->brojZavrsnih=z;
}
void DFA :: unesiZavrsna()
{
    zavrsnaStanja.resize(dajBrojZavrsnih());
    cout<< "Unesite zavrsna stanja od DFA: ";
    for(int i=0; i<zavrsnaStanja.size(); i++)
        cin >> zavrsnaStanja[i];
}
void DFA :: unesiTranziciju()
{
    int ulaz, izlaz;
    char simbol;
    cout << "Unesite tranziciju za DFA: stanje - simbol - stanje: " << endl;
    for(int i=0; i<(stanja.size()*alfabet.size()); i++)
    {
        cin >> ulaz >> simbol >> izlaz;
        tranzicija[make_pair(ulaz,simbol)]=izlaz;
    }
}


void DFA :: ispisiTranziciju()
{
    cout << "Tranzicja od DFA je data sa:\n";
    for(auto x : tranzicija)
    {
        cout << x.first.first << " " << x.first.second << " " << x.second << "\n";
    }
    cout <<endl;
}

void DFA :: ispisiDFA()
{
    cout << "Skup stanja koja cine ovaj DFA su: " ;
    for(int i=0; i<stanja.size(); i++)
        cout << stanja[i] << " ";
        cout <<endl;
    cout << "Pocetno stanje DFA je "  << pocetnoStanje << endl;
    cout << "Alfabet je: ";
    for(int i=0; i<alfabet.size(); i++)
        cout << alfabet[i] << " ";
        cout <<endl;
    cout << "Zavrsna stanja su: ";
    for(int i=0; i<zavrsnaStanja.size(); i++)
       cout << zavrsnaStanja[i] << " ";
       cout<<endl;
    ispisiTranziciju();

}
bool DFA :: prihvata(string w)
{
    int pocetak = pocetnoStanje;
    if(w.length() == 0)
    {
        for(int i=0; i<zavrsnaStanja.size(); i++)
            if(pocetak==zavrsnaStanja[i])
                return true;
        return false;
    }
    if(zavrsnaStanja.size()==0)
        return false;
    for(int i=0; i<w.length(); i++)
        pocetak=tranzicija[make_pair(pocetak, w[i])];
    for(int i=0; i<zavrsnaStanja.size(); i++)
        if(pocetak==zavrsnaStanja[i])
            return true;
    return false;
}




class NFA
{
    vector<int> stanja, zavrsnaStanja;
    vector<char> alfabet;
    int brojStanja, brojSimbola, pocetnoStanje, brojZavrsnih;
    map<pair<int,char>,vector<int>> tranzicija;

    void unesiBrojStanja();
    void unesiStanja();
    void unesiBrojSimbola();
    void unesiSimbole();
    void unesiPocetno();
    void unesiBrojZavrsnih();
    void unesiZavrsna();
    void unesiTranziciju();

public:
    NFA()
    {
        unesiBrojStanja();
        unesiStanja();
        unesiBrojSimbola();
        unesiSimbole();
        unesiPocetno();
        unesiBrojZavrsnih();
        unesiZavrsna();
        unesiTranziciju();
    }
    NFA(vector<int> stanja,vector<int> zavrsnaStanja,vector<char> alfabet, int pocetak);
    DFA* KonvertujNFAuDFA();
    int dajBrojStanja()
    {
        return brojStanja;
    }
    int dajBrojSimbola()
    {
        return brojSimbola;
    };
    int dajBrojZavrsnih()
    {
        return brojZavrsnih;
    };
    void ispisiTranziciju();
    void ispisiNFA();
};
void NFA :: unesiBrojStanja()
{
    int s;
    cout << "Unesite broj stanja od NFA: ";
    cin >> s;
    this->brojStanja=s;
}
void NFA :: unesiStanja()
{
    stanja.resize(dajBrojStanja());
    cout << "Unesite stanja od NFA: ";
    for(int i=0; i<stanja.size(); i++)
        cin >> stanja[i];
}
void NFA :: unesiBrojSimbola()
{
    int s;
    cout << "Unesite broj simbola alfabeta: ";
    cin>>s;
    this->brojSimbola=s;
}
void NFA :: unesiSimbole()
{
    alfabet.resize(dajBrojSimbola());
    cout << "Unesite simbole alfabeta: ";
    for(int i=0; i<alfabet.size(); i++)
        cin >> alfabet[i];
}
void NFA :: unesiPocetno()
{
    int p;
    cout << "Unesite pocetno stanje: ";
    cin >> p;
    this->pocetnoStanje=p;
}
void NFA :: unesiBrojZavrsnih()
{
    int z;
    cout << "Unesite broj zavrsnih stanja: ";
    cin>>z;
    this->brojZavrsnih=z;
}
void NFA :: unesiZavrsna()
{
    zavrsnaStanja.resize(dajBrojZavrsnih());
    cout<< "Unesite zavrsna stanja: ";
    for(int i=0; i<zavrsnaStanja.size(); i++)
        cin >> zavrsnaStanja[i];
}

NFA::NFA(vector<int> stanja,vector<int> zavrsnaStanja,vector<char> alfabet, int pocetak)
{
    this->stanja = stanja;
    this->zavrsnaStanja = zavrsnaStanja;
    this->alfabet = alfabet;
    this->pocetnoStanje = pocetak;
    this->brojSimbola = alfabet.size();
    this->brojStanja = stanja.size();
    this->brojZavrsnih = zavrsnaStanja.size();
    unesiTranziciju();
}
void NFA :: unesiTranziciju()
{
    int ulaz, izlaz;
    char simbol;
    cout << "Unesite tranziciju od NFA: stanje - simbol - sva moguca stanja u koja se moze doci citajuci taj simbol(-1 za kraj):\n";
    while(1)
    {
        vector<int> sviIzlazi;
        cin >> ulaz;
        if(ulaz == -1)
            break;
        cin >> simbol;
        string text_line;
        getline(cin, text_line);

        for(int i = 0;  i < text_line.length(); i++)
        {
            if(text_line[i] == ' ')
                continue;
            else
                sviIzlazi.push_back(text_line[i]-'0');
        }
        tranzicija[make_pair(ulaz,simbol)] = sviIzlazi;
    }
}
void NFA :: ispisiTranziciju()
{
    cout << "Tranzicja od NFA je data sa:\n";
    for(auto x : tranzicija)
    {
        cout << x.first.first << " " << x.first.second << " ";
        for(int i=0; i<x.second.size(); i++)
            cout << x.second[i] << " ";
        cout << endl;
    }
}

void NFA :: ispisiNFA()
{
    cout << "Skup stanja koja cine ovaj NFA su: " ;
    for(int i=0; i<stanja.size(); i++)
        cout << stanja[i] << " ";
    cout << endl;
    cout << "Pocetno stanje NFA je "  << pocetnoStanje << endl;
    cout << "Alfabet od NFA je: " << endl;
    for(int i=0; i<alfabet.size(); i++)
        cout << alfabet[i] << " ";
    cout << endl;
    cout << "Zavrsna stanja od NFA su: ";
    for(int i=0; i<zavrsnaStanja.size(); i++)
            cout << zavrsnaStanja[i] << " ";
    cout <<endl;
    ispisiTranziciju();

}
string Binarni(int n)
{
    string s = "" ;
    while(n)
    {
        s+=to_string(n%2);
        n/=2;
    }
    reverse(s.begin(),s.end());
    return s;
}

vector<vector<int>> NapraviPartitivni(vector<int> v)
{
    int n = pow(2,v.size());
    vector<vector<int>> p(n);
    p[0] = {0};
    for(int i = 1; i < n; i++)
    {
        bitset<maks> bitovi(Binarni(i));
        vector<int> pomocni;
        for(int j = 0;  j < bitovi.size(); j++)
        {
            if(bitovi[j])
                pomocni.push_back(j+1);
        }
        p[i] = pomocni;
    }
    return p;
}

vector<int> PretvoriUVektor(vector<vector<int>> v)
{
    vector<int> t;
    for(int i = 0; i < v.size(); i++)
        for(int j = 0; j < v[i].size(); j++)
            t.push_back(v[i][j]);
//brise duplikate
    sort(t.begin(),t.end());
    t.erase( unique( t.begin(), t.end() ), t.end());
    return t;
}
DFA* NFA :: KonvertujNFAuDFA()
{

    vector<vector<int>> stanjaDFA = NapraviPartitivni(stanja);
    vector<int> pocetnoDFA;
    vector<vector<int>> zavrsnaDFA;

    pocetnoDFA.push_back(pocetnoStanje);

    vector<int> p;
    if(tranzicija.find(make_pair(pocetnoStanje, 'e')) != tranzicija.end())
        p=tranzicija[(make_pair(pocetnoStanje, 'e'))];

    for(int i = 0; i < p.size(); i++)
        pocetnoDFA.push_back(p[i]);


    for(int i=0; i < stanjaDFA.size(); i++)
        for(int k=0; k<stanjaDFA[i].size(); k++)
            for(int j=0; j<zavrsnaStanja.size(); j++)
                if(stanjaDFA[i][k]==zavrsnaStanja[j])
                {
                    zavrsnaDFA.push_back(stanjaDFA[i]);
                    break;
                }

    map<pair<vector<int>,char>,vector<int>> novat;
    cout << alfabet.size();
    for(int i = 0; i <stanjaDFA.size(); i++)
    {
        vector<int> temp = stanjaDFA[i];//pokupio jedno stanje

        for(int j = 0; j < alfabet.size(); j++)
        {
            vector<vector<int>> novoStaanje;//novo stanje
            for(int k = 0;  k < temp.size(); k++)
            {
                if(tranzicija.find(make_pair(temp[k],alfabet[j])) != tranzicija.end())
                    novoStaanje.push_back(tranzicija[make_pair(temp[k],alfabet[j])]);
            }

            vector<int> a = PretvoriUVektor(novoStaanje);

            for(int l = 0; l < a.size(); l++)
                if(tranzicija.find(make_pair(a[l],'e')) != tranzicija.end())
                    novoStaanje.push_back(tranzicija[make_pair(a[l],'e')]);

            novat[make_pair(stanjaDFA[i],alfabet[j])] = PretvoriUVektor(novoStaanje);
        }

    }

    vector<int> s(stanjaDFA.size());
    for(int i = 0; i < s.size(); i++)
        s[i] = i;
    vector<int> novazavrs;
    for(int i = 0; i < s.size(); i++)
    {
        for(int j = 0; j < zavrsnaDFA.size(); j++)
        {
            if (stanjaDFA[i] == zavrsnaDFA[j])
            {
                novazavrs.push_back(i);
                break;
            }
        }
    }
    int poc;
    for(int i = 0; i < s.size(); i++)
    {
        if(stanjaDFA[i] == pocetnoDFA)
        {
            poc = i;
            break;
        }

    }
    map<pair<int,char>,int> najnovijat;
    for(auto x : novat)
    {
        auto p = x.first.first;
        auto q = x.first.second;
        auto z = x.second;
        int k = 0;
        int j = 0;
        for(int i = 0; i < s.size(); i++)
        {
            if(p == stanjaDFA[i])
            {
                k = i;

            }
            if(z == stanjaDFA[i])
            {
                j = i;

            }
        }
        najnovijat[make_pair(k,q)] = j;

    }

    return new DFA(s,novazavrs,alfabet, poc,najnovijat);
    /*  for(auto x : novat)
    {
        auto p = x.first.first;
        auto q = x.first.second;
        auto z = x.second;

        for(auto y : p)
            cout << y << " ";
        cout << q <<" ";
        for(auto y :z)
            cout << y << " ";
        cout << "\n";1
    }
    */
    //1. odredi pocetno -> vector<int>
    //2. odredi ptihvatajuca vector<vector<int>>
    //3.odredi tranziciu map[pair(vector<int>,alphabet] = vector<int>

}

int main()
{
    vector<int> stanja = {1,2,3};
    vector<int> zavrsnaStanja= {1};
    vector<char> alfabet= {'a','b'};

    int pocetak = 1;

//    DFA k;
    //k.ispisiDFA();


    //NFA d(stanja,zavrsnaStanja,alfabet,pocetak);
    NFA d;
    d.ispisiNFA();
//   d.ispisiTranziciju();
    // NapraviPartitivni({1,2,3,4});
   /* DFA* dfa =  d.KonvertujNFAuDFA();
    dfa->ispisiTranziciju();
    if(dfa->prihvata("b"))

        cout << "DFA prihvata uneseni string";
    else
        cout <<"DFA ne prihvata uneseni string";
*/
    //  Binarni(6);
    return 0;
}
