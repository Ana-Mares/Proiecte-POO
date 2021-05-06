#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm> ///Din aceasta librarie folosesc functia transform, pentru a modifica un string
///astfel incat toate literele sale sa fie minuscule (folosit la upcasting)

using namespace std;


class Proprietar
{
private:
    string nume;
    string prenume;
    string cnp;
public:
    Proprietar( string, string, string );
    Proprietar( const Proprietar& );
    ~Proprietar();

    void set_nume( string nume ) { this-> nume = nume; }
    string get_nume() const { return this-> nume; }

    void set_prenume( string prenume ) { this-> prenume = prenume; }
    string get_prenume( ) const { return this-> prenume; }

    void set_cnp( string cnp ) { this-> cnp = cnp; }
    string get_cnp( ) const { return this-> cnp; }

    Proprietar& operator = (const Proprietar&);

    void citire( istream& in );
    friend istream& operator >> ( istream&, Proprietar& );
    void afisare( ostream& out );
    friend ostream& operator << ( ostream&, Proprietar& );

};

Proprietar::Proprietar( string n = "", string p = "", string c = "" )
{
    //cout << "Constructor Proprietar" << endl;
    try
    {
        for ( int i = 0; i < c.length(); i++ )
            if ( c[i] < '0' || c[i]> '9' )
                throw 0;
    }
    catch ( int i )
    {
        cout << "CNP-ul persoanei trebuie sa contina numai cifre.\n";
        exit( EXIT_FAILURE );
    }

    this-> nume = n;
    this-> prenume = p;
    this-> cnp = c;
}

Proprietar::Proprietar( const Proprietar& p )
{
    this-> nume = p.nume;
    this-> prenume = p.prenume;
    this-> cnp = p.cnp;
}

Proprietar::~Proprietar()
{
    //cout << "Destructor Proprietar" << endl;
}

Proprietar& Proprietar::operator = ( const Proprietar& p )
{
    this-> nume = p.nume;
    this-> prenume = p.prenume;
    this-> cnp = p.cnp;
    return *this;
}

void Proprietar::citire( istream& in )
{
    cout << "Dati datele proprietarului: \n";

    cout << "Nume: ";
    in >> nume;

    cout << "Prenume: ";
    in >> prenume;

    cout << "CNP: ";
    string str;
    in >> str;
    int ok;
    int k = 0;

    while (k == 0)
    { ///Am comentat partea de verificare a lungimii CNP-ului pentru o mai usoara utilizare/ verificare e programului (pentru a evita introducerea repetata a unui CNP complet)
       // if ( str.length() != 13 ) { cout << "CNP-ul trebuie sa fie format din 13 cifre. Introduceti un CNP valid. -> \n"; cin >> str; }
       // else {
        ok = 1;
        for ( int i = 0; i < str.length(); i++ )
            if ( str[i] < '0' || str[i]> '9' )
                ok = 0;
        if ( ok == 0 )
        {
            cout << "CNP-ul persoanei trebuie sa contina numai cifre. Introduceti un CNP valid. -> \n";
            cin >> str;
        }
        else k = 1;
    } //}

    cnp = str;
}

istream& operator >> ( istream& in, Proprietar& p )
{
    p.citire( in );
    return in;
}

void Proprietar::afisare(ostream& out)
{
    out << "Datele proprietarului sunt: \n";
    out << "Nume si prenume: " << nume << " " << prenume << endl;
    out << "CNP: " << cnp << endl;
}

ostream& operator << ( ostream& out, Proprietar& p )
{
    p.afisare( out );
    return out;
}

/////////////////////////////////////////////////////////////////////

class Farmacie
{
protected:
    static Proprietar X;
public:
    Farmacie( ) { };
    virtual ~Farmacie( ) = 0;
    Farmacie( const Farmacie& );

    virtual void citire( istream& in ) = 0;
    friend istream& operator >>( istream&, Farmacie& );
    virtual void afisare( ostream& out ) = 0;
    friend ostream& operator <<( ostream&, Farmacie& );

    static void set_proprietar( );
    static Proprietar& get_proprietar ( );

    Farmacie& operator = ( Farmacie& f );
};

Proprietar Farmacie::X;

Farmacie::~Farmacie( )
{
    //cout << "Destructor Farmacie - virtual pur" << endl;
}

Farmacie::Farmacie( const Farmacie& F )
{
    //cout << "Constructor copiere Farmacie" << endl;
}

Farmacie& Farmacie::operator = ( Farmacie& F )
{
    //cout << "Operator = Farmacie" << endl;
    return *this;
}

istream& operator >> ( istream& in, Farmacie& F )
{
    F.citire( in );
    return in;
}

ostream& operator << ( ostream& out, Farmacie& F )
{
    F.afisare( out );
    return out;
}

void Farmacie::set_proprietar( )
{
    cin >> X;
}

Proprietar& Farmacie::get_proprietar ( )
{
     return X;
}

/////////////////////////////////////////////////////////////////////

class Farmacie_fizica : public Farmacie
{
private:
    string denumire;
    int nr_angajati;
    double* profituri;

public:
    Farmacie_fizica( );
    Farmacie_fizica( string, int, double* );
    Farmacie_fizica( const Farmacie_fizica& );
    ~Farmacie_fizica( );

    Farmacie_fizica& operator = ( const Farmacie_fizica& );

    void set_denumire( string denumire );
    string get_denumire ( ) const;
    void set_nr_angajati( int nrAngajati );
    int get_nr_angajati ( ) const;
    void set_profituri( double* p );
    double* get_profituri ( ) const;

    void citire( istream& in );
    friend istream& operator >> ( istream& in, Farmacie_fizica& FF );
    void afisare( ostream& out );
    friend ostream& operator << ( ostream& out, Farmacie_fizica& FF );
};


Farmacie_fizica::Farmacie_fizica( ) : Farmacie( )
{
    //cout << "Constructor Farmacie_fizica \n";
    this-> denumire = "";
    this-> nr_angajati = 0;
    profituri = new double[12];
    for ( int i = 0; i < 12; i++ )
        this-> profituri[i] = 0;
}

Farmacie_fizica::Farmacie_fizica( string denumire, int nr_angajati, double p[12] ) : Farmacie( )
{
    //cout << "Constructor parametrizat Farmacie_fizica \n";
    this-> denumire = denumire;
    this-> nr_angajati = nr_angajati;
    profituri = new double[12];
    for ( int i = 0; i < 12; i++ )
        this-> profituri[i] = p[i];
}

Farmacie_fizica::Farmacie_fizica( const Farmacie_fizica& FF )
{
    this-> denumire = FF.denumire;
    this-> nr_angajati = FF.nr_angajati;
    profituri = new double[12];
    for ( int i = 0; i < 12; i++ )
        this-> profituri[i] = FF.profituri[i];
}

Farmacie_fizica::~Farmacie_fizica( )
{
    //cout << "Destructor Farmacie_fizica\n";
    delete[] profituri;
}

Farmacie_fizica& Farmacie_fizica::operator = ( const Farmacie_fizica& FF )
{
    this-> denumire = FF.denumire;
    this-> nr_angajati = FF.nr_angajati;
    profituri = new double[12];
    for ( int i = 0; i < 12; i++ )
        this->profituri[i] = FF.profituri[i];
    return *this;
}

void Farmacie_fizica::set_denumire( string denumire )
{
    this-> denumire = denumire;
}

string Farmacie_fizica::get_denumire( ) const
{
    return this-> denumire;
}

void Farmacie_fizica::set_nr_angajati( int nr_angajati )
{
    this-> nr_angajati = nr_angajati;
}

int Farmacie_fizica::get_nr_angajati( ) const
{
    return this-> nr_angajati;
}

void Farmacie_fizica::set_profituri( double* p )
{
    for ( int i = 0; i < 12; i++ )
        this-> profituri[i] = p[i];
}

double* Farmacie_fizica::get_profituri( ) const
{
    return this-> profituri;
}

void Farmacie_fizica::citire( istream& in )
{
    cout << "Dati datele farmaciei fizice: \n";

    cout << "Denumirea: ";
    in >> this-> denumire;

    cout << "Numarul de angajati: ";
    in >> this-> nr_angajati;
    while ( nr_angajati < 0 )
    {
        cout << "Numarul angajatilor trebuie sa fie pozitiv. Dati o valoare valida. -> ";
        in >> this-> nr_angajati;
    }

    cout << "Profiturile lunare(pentru fiecare dintre cele 12 luni ale anului):" << endl;
    cout << "prima valoare - luna ianuarie, a douasprezecea valoare - luna decembrie: " << endl;
    for (int i = 0; i < 12; i++)
    {
        cout << "Luna " << i + 1 << ": ";
        in >> this-> profituri[i];
    }
}

istream& operator >> ( istream& in, Farmacie_fizica& FF )
{
    FF.citire( in );
    return in;
}

void Farmacie_fizica::afisare( ostream& out )
{
    out << endl << "Datele salvate pentru farmacia fizica sunt: ";
    out << endl << "Denumire: " << denumire;
    out << endl << "Numar de angajati: " << nr_angajati;
    out << endl << "Profiturile pe fiecare luna (ianuarie -> decembrie): ";
    for ( int i = 0; i < 12; i++ )
        out << this-> profituri[i] << " ";
}

ostream& operator << ( ostream& out, Farmacie_fizica& FF )
{
    FF.afisare( out );
    return out;
}


////////////////////////////////////////////////////////////////////////

class Farmacie_online : public Farmacie
{
private:
    string adresa_web;
    int nr_vizitatori;
    double discount;

public:
    Farmacie_online( string, int, double );
    Farmacie_online( const Farmacie_online& );
    ~Farmacie_online( );

    Farmacie_online& operator = ( const Farmacie_online& );

    void set_adresa_web( string );
    string get_adresa_web( ) const ;
    void set_nr_vizitatori( int );
    int get_nr_vizitatori( ) const;
    void set_discount( double );
    double get_discount( ) const;

    void citire( istream& in );
    friend istream& operator >> ( istream& in, Farmacie_online& FO );
    void afisare( ostream& out );
    friend ostream& operator << ( ostream& out, Farmacie_online& FO );


    operator Farmacie_fizica( )
    {
        double* p = new double[12];
        for ( int i = 0; i < 12; i++ )  p[i] = 0;
        Farmacie_fizica* FF = new Farmacie_fizica( this-> adresa_web + " ONLINE", 0, p );
        delete[] p;
        return *FF;
    }

};

Farmacie_online::Farmacie_online( string adresa_web = "", int nr_vizitatori = 0, double discount = 0 ) : Farmacie( )
{
    //cout << "Constructor Farmacie_online \n";
    this-> adresa_web = adresa_web;
    this-> nr_vizitatori = nr_vizitatori;
    this-> discount = discount;
}


Farmacie_online::Farmacie_online( const Farmacie_online& FO )
{
    this-> adresa_web = FO.adresa_web;
    this-> nr_vizitatori = FO.nr_vizitatori;
    this-> discount = FO.discount;
}

Farmacie_online::~Farmacie_online( )
{
    //cout << "Destructor Farmacie_online\n";
}

Farmacie_online& Farmacie_online::operator = ( const Farmacie_online& FO )
{
    this-> adresa_web = FO.adresa_web;
    this-> nr_vizitatori = FO.nr_vizitatori;
    this-> discount = FO.discount;
    return *this;
}

void Farmacie_online::set_adresa_web( string adresa_web )
{
    this-> adresa_web = adresa_web;
}

string Farmacie_online::get_adresa_web( ) const
{
    return this-> adresa_web;
}

void Farmacie_online::set_nr_vizitatori( int nr_vizitatori )
{
    this-> nr_vizitatori = nr_vizitatori;
}

int Farmacie_online::get_nr_vizitatori( ) const
{
    return this-> nr_vizitatori;
}

void Farmacie_online::set_discount( double discount )
{
    this-> discount = discount;
}

double Farmacie_online::get_discount( ) const
{
    return this-> discount;
}

void Farmacie_online::citire( istream& in )
{
    cout << "Dati datele farmaciei online: \n";

    cout << "Adresa web: ";
    in >> this-> adresa_web;

    cout << "Numarul de vizitatori: ";
    in >> this-> nr_vizitatori;
    while ( nr_vizitatori < 0 )
    {
        cout << "Numarul de vizitatori trebuie sa fie pozitiv. Dati o valoare valida. -> ";
        in >> this-> nr_vizitatori;
    }

    cout << "Discountul utilizat (0-100): ";
    in >> this-> discount;
    while ( discount < 0 || discount > 100 )
    {
        if ( discount < 0 )
        {
            cout << "Discountul trebuie sa fie pozitiv. Dati o valoare valida. -> ";
            in >> this-> discount;
        }
        if ( discount > 100 )
        {
            cout << "Discountul trebuie sa fie maxim 100. Dati o valoare valida. -> ";
            in >> this-> discount;
        }
    }
}

istream& operator >> ( istream& in, Farmacie_online& FO )
{
    FO.citire( in );
    return in;
}

void Farmacie_online::afisare( ostream& out )
{
    out << endl << "Datele salvate pentru farmacia online sunt: ";
    out << endl << "Adresa web: " << adresa_web;
    out << endl << "Numarul de vizitatori: " << nr_vizitatori;
    out << endl << "Discountul utilizat: " << discount << " " << endl;
}

ostream& operator << ( ostream& out, Farmacie_online& FO )
{
    FO.afisare( out );
    return out;
}


///////////////////////////////////////////////////////////////////////////

template <class t>
class GestionareFarmacii
{
private:
    vector<int> index_farmacie;
    const int id_lant = rand()%99 + 1;
    vector<t> Farmacii;
public:
    GestionareFarmacii( )
    {
        //cout << "Constructor template" << endl;
    }
    GestionareFarmacii( const GestionareFarmacii<t>& GF );
    ~GestionareFarmacii( )
    {
        //cout << "Destructor template" << endl;
    }

    int get_index( int i ) const { return index_farmacie[i]; }

    int get_id_lant( ) const { return id_lant; }

    void citire( istream& in );
    void afisare( ostream& out );
    friend istream& operator >> ( istream& in, GestionareFarmacii<t>& GF )
    {
        GF.citire( in );
        return in;
    };
    friend ostream& operator << ( ostream& out, GestionareFarmacii<t>& GF )
    {
        GF.afisare( out );
        return out;
    }

    GestionareFarmacii& operator = ( const GestionareFarmacii& GF );
    GestionareFarmacii<t> operator += ( Farmacie_online Farm )
    {
        if ( index_farmacie.empty() == 1 ) index_farmacie.push_back(1);
        else index_farmacie.push_back(index_farmacie.back()+1);
        Farmacii.push_back((Farmacie_fizica)Farm);
        return *this;
    }

    void adauga_farmacie( t& Farmacie )
    {
        if ( index_farmacie.empty() == 1 ) index_farmacie.push_back(1);
        else index_farmacie.push_back(index_farmacie.back()+1);
        Farmacii.push_back(Farmacie);
    }

};

template <class t>
GestionareFarmacii<t>::GestionareFarmacii( const GestionareFarmacii<t>& GF )
{
    index_farmacie.resize( GF.index_farmacie.size() );
    for ( int i = 0; i < GF.index_farmacie.size(); i++ )
        this-> index_farmacie[i] = GF.index_farmacie[i];
    //this-> id_lant = GF.id_lant;

    Farmacii.resize( GF.Farmacii.size() );
    for ( int i = 0; i < GF.Farmacii.size(); i++ )
        this-> Farmacii[i] = GF.Farmacii[i];
}

template <class t>
void GestionareFarmacii<t>::citire( istream& in )
{
    cout << "Introduceti numarul de farmacii din gestiune: ";
    int nr;
    cin >> nr;

    cout << endl << "Doriti sa cititi proprietarul farmaciei?" << endl << "1. Da" << endl << "0. Nu" << endl;
    int opt;
    cin >> opt;
    while ( opt != 0 && opt != 1 )
    {
        cout << "Introduceti o optiune valida (1 sau 0). -> ";
        cin >> opt;
    }
    if (opt == 1 )
    {
        cout << endl;
        Farmacie::set_proprietar();
    }
    cout << endl;


    for (int i = 0; i < nr; i++)
    {
        t aux;
        cout << endl;
        cin >> aux;
        adauga_farmacie( aux );
    }
}

template <class t>
void GestionareFarmacii<t>::afisare( ostream& out )
{
    out << endl << endl << "In gestiune exista urmatoarele  " << Farmacii.size( ) << " farmacii, cu id-ul lantului " << id_lant << ": " << endl << endl;

    for ( int i = 0; i < Farmacii.size(); i++ )
    {
        out << "Farmacia cu indexul " << index_farmacie[i] << ": ";
        out << Farmacii[i] << endl;
        out << endl;
    }

    Proprietar aux = Farmacie::get_proprietar();
    if ( aux.get_nume() == "" && aux.get_prenume() == "" && aux.get_cnp() == "" ) cout << "Nu au fost citite date pentru proprietar." << endl;
    else cout << aux;

}

template <class t>
GestionareFarmacii<t>& GestionareFarmacii<t>::operator = ( const GestionareFarmacii<t>& GF )
{
    for ( int i = 0; i < GF.index_farmacie.size (); i++ )
        this-> index_farmacie.push_back( GF.index_farmacie[i] );
    for ( int i = 0; i < GF.Farmacii.size(); i++ )
        this-> Farmacii.push_back( GF.Farmacii[i] );
}

/////////////////////////////////////////////////////////////////////////

template <> class GestionareFarmacii <Farmacie_online>
{
private:
    int vizitatori;
public:
    GestionareFarmacii( )
    {
        //cout << "Constructor specializare" << endl;
        vizitatori = 0;
    }
    GestionareFarmacii( const GestionareFarmacii<Farmacie_online>& GF );
    ~GestionareFarmacii( )
    {
        //cout << "Destructor specializare" << endl;
    }

    void set_vizitatori( int vizitatori ) { this-> vizitatori = vizitatori; }
    int get_vizitatori( ) const { return vizitatori; }

    void citire( istream& in );
    void afisare( ostream& out );
    friend istream& operator >> ( istream& in, GestionareFarmacii<Farmacie_online>& GF )
    {
        GF.citire( in );
        return in;
    };
    friend ostream& operator << ( ostream& out, GestionareFarmacii<Farmacie_online>& GF )
    {
        GF.afisare( out );
        return out;
    }

    GestionareFarmacii& operator = ( const GestionareFarmacii& GF );
    GestionareFarmacii<Farmacie_online> operator += ( Farmacie_online Farmacie )
    {
        vizitatori = vizitatori + Farmacie.get_nr_vizitatori();
        return *this;
    }

    void adauga_farmacie( Farmacie_online& Farmacie )
    {
        vizitatori += Farmacie.get_nr_vizitatori( );
    }

};

GestionareFarmacii<Farmacie_online>::GestionareFarmacii( const GestionareFarmacii<Farmacie_online>& GF )
{
    this-> vizitatori = GF.vizitatori;
}

void GestionareFarmacii<Farmacie_online>::citire( istream& in )
{
    cout << "Introduceti numarul de farmacii din gestiune: ";
    int nr;
    cin >> nr;

    cout << endl << "Doriti sa cititi proprietarul farmaciei?" << endl << "1. Da" << endl << "0. Nu" << endl;
    int opt;
    cin >> opt;
    while ( opt != 0 && opt != 1 )
    {
        cout << "Introduceti o optiune valida (1 sau 0). -> ";
        cin >> opt;
    }
    if (opt == 1 )
    {
        cout << endl;
        Farmacie::set_proprietar();
    }
    cout << endl;

    for ( int i = 0; i < nr; i++ )
    {

        Farmacie_online aux;
        cin >> aux;
        cout << endl;

        vizitatori += aux.get_nr_vizitatori();
    }
}

void GestionareFarmacii<Farmacie_online>::afisare( ostream& out )
{
    out << "Numarul total de vizitatori ai farmaciilor online legate de aceasta gestiune: " << endl;
    out << vizitatori << endl;

    Proprietar aux = Farmacie::get_proprietar();
    if ( aux.get_nume() == "" && aux.get_prenume() == "" && aux.get_cnp() == "" ) cout << endl << "Nu au fost citite date pentru proprietar." << endl;
    else cout << endl << aux;

}

GestionareFarmacii<Farmacie_online>& GestionareFarmacii<Farmacie_online>::operator = ( const GestionareFarmacii<Farmacie_online>& GF )
{

    this-> vizitatori = GF.vizitatori;
    return *this;
}

//////////////////////////////////////////////////////////////////////

void tip( Farmacie*& f, int& i )
{
    string s;
    cout << "\n";
    cout << "Introduceti tipul farmaciei " << i + 1 << " ('fizica' sau 'online'): ";
    cin >> s;
    transform( s.begin(), s.end(), s.begin(), ::tolower );
    try
    {
        if ( s == "fizica" )
        {
            f = new Farmacie_fizica;
            cin >> *f;
            i++;
        }
        else if ( s == "online" )
        {
            f = new Farmacie_online;
            cin >> *f;
            i++;
        }
        else
            throw 'a';
    }

    catch ( bad_alloc& ba )
    {
        cout << "Eroare la alocarea memoriei\n" << ba.what();
        exit( EXIT_FAILURE );
    }

    catch ( char& c )
    {
        cout << "Nu ati introdus un tip de farmacie valid. Farmacia trebuie sa fie 'fizica' sau 'online'.\n ";
    }
}

/////////////////////////////////////////////////////////////////////


void meniu( )
{
    cout << "Mares Ana-Maria Grupa 253 - Proiectul 3 - Tema 6: aplicatie care sa permita gestionarea " << endl << "activitatii unor farmacii apartinand proprietarului X \n\n\n";
    int optiune = 1;
    int n = 0;
    Farmacie** f;
    while ( optiune )
    {
        cout << "MENIU:\n\n";
        cout << "1. Citeste informatii despre farmacii fizice si online (upcast & late binding)\n";
        cout << "2. Contorizare farmacii - dynamic_cast (downcast)\n";
        cout << "3. Template GestionareFarmacii - clasa Farmacie_fizica\n";
        cout << "4. Template GestionareFarmacii - specializare pentru clasa Farmacie_online\n";
        cout << "0. Iesire.";
        cout << "\n";

        cout << "\nIntroduceti numarul actiunii: ";
        cin >> optiune;

        switch ( optiune )
        {
        case 1:  //1. informatii despre farmacii fizice si online (upcast & late binding)
        {
            try
            {

                cout << "Introduceti numarul de obiecte citite: ";
                cin >> n;
                while ( n < 1 )
                {
                    cout << "Numarul introdus trebuie sa fie strict pozitiv.Introduceti o valoare valida. -> ";
                    cin >> n;
                }

                cout << endl << "Doriti sa cititi proprietarul farmaciei?" << endl << "1. Da" << endl << "0. Nu" << endl;
                int opt;
                cin >> opt;
                while ( opt != 0 && opt != 1 )
                {
                    cout << "Introduceti o optiune valida (1 sau 0). -> ";
                    cin >> opt;
                }
                if (opt == 1 )
                {
                    cout << endl;
                    Farmacie::set_proprietar();
                }
                cout << endl;

                f = new Farmacie * [n];
                for ( int i = 0; i < n; )
                    tip( f[i], i );

                cout << "\n\nAfisarea farmaciilor citite anterior:\n";
                for ( int i = 0; i < n; i++ )
                {
                    cout << "\nFarmacia " << i + 1 << ": " << endl;
                    cout << "-------";
                    cout << *f[i] << endl;
                }
                cout << endl;
                Proprietar aux = Farmacie::get_proprietar();
                if ( aux.get_nume() == "" && aux.get_prenume() == "" && aux.get_cnp() == "" ) cout << "Nu au fost citite date pentru proprietar." << endl;
                else cout << aux;

            }
            catch ( bad_alloc  ba )
            {
                cout << "Eroare la alocarea memoriei\n" << ba.what( );
                exit( EXIT_FAILURE );
            }
            catch ( bad_cast bc )
            {
                cout << "Eroare la cast\n" << bc.what( );
                exit( EXIT_FAILURE );
            }
            break;
        }

        case 2: //2. Contorizare farmacii - dynamic_cast (downcast)
        {
            int nrFf, nrFo;
            nrFf = 0;
            nrFo = 0;
            if (n <= 0)
            {
                cout << "Nu s-a citit niciun tip de farmacie. Cititi cel putin o farmacie (optiunea 1).";
            }
            if (n > 0)
            {
                for (int i = 0; i < n; i++)
                {
                    Farmacie_fizica Ff;
                    //Farmacie_fizica *Ff = dynamic_cast <Farmacie_fizica*> ( f[i] );
                    Farmacie_online* Fo = dynamic_cast <Farmacie_online*> ( f[i] );
                    if ( typeid(Ff) == typeid(*f[i]) ) nrFf++; //RTTI
                    if ( Fo ) nrFo++;

                }
                cout << "Numarul de farmacii fizice: " << nrFf << "\n";
                cout << "Numarul de farmacii online: " << nrFo << "\n";
            }
            break;
        }

        case 3: //3. Template GestionareFarmacii - clasa Farmacie_fizica
        {
            GestionareFarmacii <Farmacie_fizica> Ff;
            cin >> Ff;
            cout << Ff;
            break;
        }

        case 4: //4. Template GestionareFarmacii - specializare pentru clasa Farmacie_online
        {
            GestionareFarmacii <Farmacie_online> Fo; //conform cerintei, acest obiect va contine si va
            cin >> Fo;                      //afisa doar numarul total de vizitatori ai farmaciilor online
            cout << Fo;
            break;
        }

        case 0: //0. Iesire
        {
            break;
        }

        default: //selectie incorecta
        {
            cout << "\nSelectia este incorecta. Introduceti un numar din lista data.\n";
            break;
        }
        }
        cout << "\n\n";
        system( "pause" );
        system( "cls" );
    }
}


int main()
{
    meniu();

    ///Testare functionare operator += pentru template-ul GestionareFarmacii
    /*GestionareFarmacii <Farmacie_fizica> g;
    cin >> g;
    Farmacie_online fo;
    cout << endl;
    cin >> fo;
    g += fo;
    cout << g;*/


    ///Testare functionare operatori copiere si atribuire pentru template-ul GestionareFarmacii
    /*GestionareFarmacii <Farmacie_fizica> x;
    cin >> x;
    cout << x;
    cout << endl;
    GestionareFarmacii <Farmacie_fizica> K(x);
    cout << endl << "Dupa copiere: \n" <<"-------" << K;
    GestionareFarmacii <Farmacie_fizica> L;
    L = x;
    cout << endl<< endl << "Dupa atribuire: \n" << "-------"  << L;
    return 0; */


    ///Testare functionare operatori copiere si atribuire pentru template-ul GestionareFarmacii - specializarea Farmacie_online
    /*GestionareFarmacii <Farmacie_online> x;
    cin >> x;
    cout << x;
    cout << endl;
    GestionareFarmacii <Farmacie_online> K(x);
    cout << endl << "Dupa copiere: \n" <<"-------\n" << K;
    GestionareFarmacii <Farmacie_online> L;
    L = x;
    cout << endl<< endl << "Dupa atribuire: \n" << "-------\n"  << L; */

    return 0;
}
