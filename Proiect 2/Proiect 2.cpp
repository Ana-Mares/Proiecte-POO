#include <iostream>
#include <stdlib.h>
#include <iomanip> ///Din aceasta librarie folosesc manipulatorul setw(), pentru formatarea afisarii elementelor matricelor
using namespace std;

class Complex
{
private:
    float re;
    float im;

public:
    Complex();
    Complex( float, float );
    Complex( Complex& );
    ~Complex();

    void set_re( float r ) { this-> re = r; };
    float get_re() { return re; };
    void set_im( float i ) { this-> im = i; };
    float get_im() { return im; };

    void citire( istream &in );
    friend istream& operator >>( istream &in, Complex &c );
    void afisare( ostream &out );
    friend ostream& operator <<( ostream &out, Complex &c );

    Complex& operator =( Complex &c );
    friend Complex& operator * ( Complex& c1, Complex& c2 );
    friend Complex& operator / ( Complex& c1, Complex& c2 );
    friend Complex& operator + ( Complex& c1, Complex& c2 );

    friend class Matrice;
};

Complex::Complex()
{
    this-> re = 0;
    this-> im = 0;
}

Complex::Complex( float re, float im )
{
    this-> re = re;
    this-> im = im;
}

Complex::Complex( Complex &c )
{
    this-> re = c.re;
    this-> im = c.im;
}

Complex::~Complex()
{
    this-> re = 0;
    this-> im = 0;
}

void Complex::citire( istream &in )
{
    cout << "Partea reala: ";
    in >> re;
    cout << "Partea imaginara: ";
    in >> im;
}

istream& operator >>( istream& in, Complex& c )
{
    c.citire(in);
    return in;
}

void Complex::afisare( ostream &out )
{
    if ( im == 0 )
        out << re;
    else if ( re == 0 ) out << im << "*i";
    else if ( im < 0)
        out << re << im << "*i";
    else
        out << re << "+" << im << "*i";
}

ostream& operator <<( ostream& out, Complex& c )
{
    c.afisare(out);
    return out;
}

Complex& Complex::operator =( Complex &c )
{
    this-> re = c.re;
    this-> im = c.im;
}

Complex& operator *( Complex& c1, Complex& c2 )
{
    Complex *rez = new Complex;
    rez-> re = c1.re * c2.re  -  c1.im * c2.im;
    rez-> im = c1.re * c2.im  +  c2.re * c1.im;
    return *rez;
}

Complex& operator /( Complex& c1, Complex& c2 )
{
    Complex *rez = new Complex;
    rez-> re = ( c1.re*c2.re + c1.im*c2.im ) / ( c2.re*c2.re + c2.im*c2.im );
    rez-> im = ( c2.re*c1.im - c1.re*c2.im ) / ( c2.re*c2.re + c2.im*c2.im );
    return *rez;
}

Complex& operator +( Complex& c1, Complex& c2 )
{
    Complex *rez = new Complex;
    rez-> re = c1.re + c2.re;
    rez-> im = c1.im + c2.im;
    return *rez;
}

//////////////////////////////////////////////

class Matrice
{
protected:
    Complex **v;
    static int mat_existente;

public:
    Matrice();
    virtual ~Matrice();
    Matrice( const Matrice& );

    virtual void citire( istream &in );
    friend istream& operator >>( istream&, Matrice& );
    virtual void afisare( ostream &out );
    friend ostream& operator <<( ostream&, Matrice& );

    static int m_existente() { return mat_existente; };
    int set_m_existente( int m ) { mat_existente = m; };

    Matrice& operator = ( Matrice &m );

    virtual void Matrice_diagonala();
};
int Matrice::mat_existente;

Matrice::Matrice() ///Memoria se va aloca direct in functia clasei, intrucat pentru clasa Matrice nu se cunosc dimensiunile tablourilor.
{               ///Avand in vedere datele membre ale clasei, aceasta nu utilizeaza constructor parametrizat.
    //cout << "Constructor baza \n";
    mat_existente++;
}

Matrice::~Matrice()
{
    //cout << "Destructor baza \n";
    delete []v;
    mat_existente--;
}

Matrice::Matrice( const Matrice &m ) ///Prin prisma naturii clasei Matrice, aceasta metoda, precum si alte cateva, sunt "goale", toate
{                                 ///toate operatiile necesare fiind facute in cadrul metodelor cu acelasi nume din cadrul claselor Matrice_oarecare
}                                ///si Matrice_patratica. In situatiile necesare, metodele din clasele derivate apeleaza metodele din clasa de baza,
                                ///chiar daca acest lucru nu determina vreo diferenta efectiva in functionalitatea programului.
void Matrice::citire( istream &in )
{
    //cout<<"Citire baza\n";
}

istream& operator >>( istream &in, Matrice &m )
{
    m.citire(in);
    return in;
}

void Matrice::afisare( ostream &out )
{                         ///Aceasta afisare are rolul de a demonstra faptul ca metodele de afisare ale functiilor derivate apeleaza metoda din baza;
    out << "Matrice";   ///In plus, afisarea acestui cuvant este doveditoare si in ilustrarea conceptului de downcasting (a se vedea meniul si functia cu acest nume).
    //out<<"afisare baza \n";
}

ostream& operator <<( ostream &out, Matrice &m )
{
    m.afisare(out);
    return out;
}

Matrice& Matrice:: operator = ( Matrice &m )
{
}

void Matrice::Matrice_diagonala()
{
}

///////////////////////////////////////////////

class Matrice_oarecare: public Matrice
{
private:
    int lin, col;

public:
    Matrice_oarecare( int, int ); //constructor de intializare cu parametri impliciti
    ~Matrice_oarecare();
    Matrice_oarecare( const Matrice_oarecare& );

    void set_lin( int l ) { this-> lin = l; };
    int get_lin() { return lin; };
    void set_col( int c ) { this-> col = c; };
    int get_col() { return col; };

    void citire( istream &in );
    friend istream& operator >>( istream&, Matrice_oarecare& );
    void afisare( ostream &out );
    friend ostream& operator <<( ostream&, Matrice_oarecare& );

    Matrice_oarecare& operator = ( Matrice_oarecare &mo );

    void Matrice_diagonala ();
};

Matrice_oarecare::Matrice_oarecare( int lin = 0, int col = 0 ) : Matrice()
{
    //cout << "Constructor oarecare\n";

    this-> lin = lin;
    this-> col = col;
    v = new Complex*[lin];
    for ( int i = 0; i < lin; i++ )
        this-> v[i] = new Complex[col];
}

Matrice_oarecare::~Matrice_oarecare()
{
    //cout << "Destructor oarecare\n";

    for (int i = 0; i < lin; i++ )
        delete [] v[i];
    this-> lin = 0;
    this-> col = 0;
}

Matrice_oarecare::Matrice_oarecare( const Matrice_oarecare& mo )
{
    this-> lin = mo.lin;
    this-> col = mo.col;

    this-> v = new Complex*[lin];
    for ( int i = 0; i < lin; i++ )
        this-> v[i] = new Complex[col];

    for (int i = 0; i < mo.lin; i++)
    {
        for ( int j = 0; j < mo.col; i++)
            this-> v[i][j] = mo.v[i][j];
    }
}

void Matrice_oarecare::citire( istream &in )
{
    Matrice::citire(in);
    cout << "Dati elementele matricei oarecare cu " << lin << " linii si " << col << " coloane: " <<endl;
    for ( int i = 0; i < lin; i++ )
    {
        cout << endl << "Linia " << i+1 << ": " << endl;
        for ( int j = 0; j < col; j++ )
            in >> v[i][j];
    }

}

istream& operator >> ( istream& in, Matrice_oarecare& mo )
{
    mo.citire(in);
    return in;
}

void Matrice_oarecare::afisare( ostream &out )
{
    Matrice::afisare(out);
    out << " oarecare cu " << lin << " linii si " << col << " coloane: \n";
    for ( int i = 0; i < lin; i++ )
    {
        for ( int j = 0; j < col; j++ )
             out << setw(7) << v[i][j] << "  ";
        out << endl;
    }
}

ostream& operator << ( ostream& out, Matrice_oarecare& mo)
{
    mo.afisare(out);
    return out;
}

Matrice_oarecare& Matrice_oarecare:: operator = ( Matrice_oarecare &mo )
{
    this-> lin = mo.lin;
    this-> col = mo.col;

    v = new Complex*[lin];
    for ( int i = 0; i < col; i++ )
        this-> v[i] = new Complex[col];

    for (int i = 0; i < mo.lin; i++)
    {
        for ( int j = 0; j < mo.col; j++)
             this-> v[i][j] = mo.v[i][j];
    }
}

void Matrice_oarecare:: Matrice_diagonala ()
{
    cout << endl << "Matricea este una oarecare (numarul de linii este diferit de numarul de coloane). \nMatricea nu este triunghiulara.";
}

///////////////////////////////////////////////

class Matrice_patratica: public Matrice
{
private:
    int dim;

public:
    Matrice_patratica( int );
    ~Matrice_patratica();
    Matrice_patratica( const Matrice_patratica& );

    void set_dim( int d ) { this-> dim = d; };
    int get_dim() { return dim; };

    void citire( istream &in );
    friend istream& operator >>( istream&, Matrice_patratica& );
    void afisare( ostream &out );
    friend ostream& operator <<( ostream&, Matrice_patratica& );

    Matrice_patratica& operator = ( Matrice_patratica& );

    void Matrice_diagonala( );
    void determinant( );
};


Matrice_patratica::Matrice_patratica( int dim = 0 ) : Matrice()
{
    //cout << "Constructor patratica\n";

    this-> dim = dim;
    v = new Complex*[dim];
    for ( int i = 0; i < dim; i++ )
        this-> v[i] = new Complex[dim];
}

Matrice_patratica::~Matrice_patratica()
{
    //cout << "Destructor patratica\n";

    for (int i = 0; i < dim; i++ )
        delete [] v[i];
    this-> dim = 0;
}

Matrice_patratica::Matrice_patratica( const Matrice_patratica& mp )
{
    this-> dim = mp.dim;

    v = new Complex*[dim];
    for ( int i = 0; i < dim; i++ )
        this-> v[i] = new Complex[dim];

    for (int i = 0; i < mp.dim; i++)
    {
        for ( int j = 0; j < mp.dim; i++)
            this-> v[i][j] = mp.v[i][j];
    }
}

void Matrice_patratica::citire( istream &in )
{
    Matrice::citire(in);
    cout << "Dati elementele matricei patratice cu " << dim << " linii si " << dim << " coloane: " << endl;
    for ( int i = 0; i < dim; i++ )
    {
        cout << endl << "Linia " << i+1 << ": " << endl;
        for ( int j = 0; j < dim; j++ )
            in >> v[i][j];
    }
}

istream& operator >> ( istream& in, Matrice_patratica& mp)
{
    mp.citire(in);
    return in;
}

void Matrice_patratica::determinant ( ) /// Calculul determinantului cu ajutorul Metodei lui Gauss (metoda eliminarii succesive/ partiale)
{                                                             ///Prin intermediul acestei metode, se reduce matricea la forma sa triunghiulara, astfel ca, in final,
    Matrice_patratica aux;                                    ///determinantul se poate calcula foarte usor, fiind produsul elementelor de pe diagonala principala.
    aux = *this;

    int sem = 0;
    float f = 1;

    Complex c_aux;
    Complex m;

    int i, j, k;
    Complex nul; ///folosit in cazul in care determinantul este nul

    Complex neg(-1, 0);

    for ( i = 0; i < dim-1; i++ )
    {
        if ( aux.v[i][i].get_re() == 0 && aux.v[i][i].get_im() == 0 )
        {
            for ( k = i+1; k < dim; k++ )
                {
                    if ( aux.v[k][i].get_re() != 0 && aux.v[k][i].get_im() != 0)
                    {
                        sem = 1;
                        f *= -1;
                        for ( j = 0; j < dim; j++)
                        {
                            c_aux = aux.v[i][j];
                            aux.v[i][j] = aux.v[k][j];
                            aux.v[k][j] = c_aux;
                        }
                        break;
                    }
                }
                if ( sem == 0 )
                    cout << nul;
        }

        for ( k = i+1; k < dim; k++)
            {
                m = neg * aux.v[k][i] / aux.v[i][i];
                for ( j = i; j < dim; j++)
                    aux.v[k][j] = m * aux.v[i][j] + aux.v[k][j];
            }
    }

    Complex det(f, 0);

    for ( i = 0; i < dim; i++)
        det = det * aux.v[i][i];

    cout << "Determinantul este: " << det << endl;
}

void Matrice_patratica::afisare( ostream &out )
{
    Matrice::afisare(out);
    out << " patratica cu " << dim << " linii si " << dim << " coloane: \n";
    for ( int i = 0; i < dim; i++ )
    {
        for ( int j = 0; j < dim; j++ )
             out << setw(7) << v[i][j] << "  ";
        out << endl;
    }
    out << endl;
    determinant();
}

ostream& operator << ( ostream& out, Matrice_patratica& mp)
{
    mp.afisare(out);
    return out;
}

Matrice_patratica& Matrice_patratica:: operator = ( Matrice_patratica &mp )
{
    this-> dim = mp.dim;

    v = new Complex*[dim];
    for ( int i = 0; i < dim; i++ )
        this-> v[i] = new Complex[dim];

    for (int i = 0; i < mp.dim; i++)
    {
        for ( int j = 0; j < mp.dim; j++)
             this-> v[i][j] = mp.v[i][j];
    }
}

void Matrice_patratica::Matrice_diagonala ()
{
    int sup = 1;
    int inf = 1;
    int diag = 1;
    for ( int i = 0; i < dim; i++ )
    {
        for ( int j = 0; j < dim; j++)
        {
            if ( i > j && ( v[i][j].get_re() != 0 || v[i][j].get_im() != 0 ) )
                inf = 0;
            if ( i < j && ( v[i][j].get_re() != 0 || v[i][j].get_im() != 0 ) )
                sup = 0;
        }
        if ( v[i][i].get_re() == 0 && v[i][i].get_im() == 0 )
            diag = 0;
    }

    if ( sup == 0 && inf == 1 )
        cout << "Matricea este superior triunghiulara.";
    else if ( sup == 1 && inf == 0 )
        cout << "Matricea este inferior triunghiulara.";
    else if ( sup == 1 && inf ==  1 && diag == 1 )
        cout << "Matricea este diagonala.";
    else if ( sup == 1 && inf == 1 && diag == 0 )
        cout << "Matricea are numai elemente nule.";
    else
        cout << "Matricea patratica nu este nici triunghiulara, nici diagonala.";
}

/////////////////////////////////////////

void tip_matrice(Matrice *&M, int i)
{
    int lin, col;
    cout<<"\n";
    cout<<"Introduceti dimensiunile matricei (linii si coloane): ";

    cin>>lin >> col;
    while (lin < 1)
    {
        cout << "Numarul de linii trebuie sa fie strict pozitiv. Dati o valoare corecta.";
        cin >> lin;
    }
    while (col < 1)
    {
        cout << "Numarul de coloane trebuie sa fie strict pozitiv. Dati o valoare corecta.";
        cin >> col;
    }
    ///upcast
    if( lin == col )
    {
        M = new Matrice_patratica( lin );
        cin >> *M;
    }
    else
    {
        M = new Matrice_oarecare( lin, col );
        cin >> *M;
    }
}

void downcast()
{
    Matrice_patratica *mp = (Matrice_patratica*)new Matrice;
    cin >> *mp;
    cout << *mp;
    cout << endl;
    mp->set_m_existente(Matrice::m_existente()-1);   ///Este nevoie de aceasta linie pentru corectitudinea programului.
                                                ///In lipsa ei, pentru fiecare apel al functiei downcast, valoarea variabilei
                                             ///mat_existente ar creste, ceea ce ar determina greseli in gestionarea numarului de matrice salvate
                                          ///efectiv in program (de exemplu, pentru o matrice citita si o apelare a functiei downcast, programul ar
                                       ///considera ca au fost salvate doua matrice, ceea ce ar produce erori pentru afisare si citire).
}
/////////////////////////////////////////

void output_meniu()
{
    cout << "MENIU:\n\n";
    cout << "1. Citeste una sau mai multe matrice\n";
    cout << "2. Afiseaza una sau mai multe matrice (pentru matricele patratice, se afiseaza inclusiv determinantul)\n";
    cout << "3. Verifica daca o matrice triunghiulara este diagonala\n";
    cout << "4. Demonstrarea functiilor statice\n";
    cout << "5. Exemplificare downcast\n";
    cout << "0. Iesire.\n";
}


void meniu ()
{
    cout << "Mares Ana-Maria Grupa 253 - Proiectul 2 - Tema 10: matrice de numere complexe reprezentate ca tablouri bidimensionale \n\n\n";
    Matrice **M;
    int n;
    cout << "Introduceti numarul total de matrice posibile: ";
    cin >> n;
    while ( n <= 0 )
    {
        cout << "Selectia este incorecta. Introduceti un numar strict mai mare decat 0.  -> ";
        cin >> n;
    }
    M = new Matrice*[n]; //aloc memorie pentru n obiecte de tip Matrice => downcasting

    int optiune = 1;
    while (optiune)
    {
        output_meniu();
        cout<<"\nIntroduceti numarul actiunii dorite: ";
        cin>> optiune;

        switch( optiune )
        {
        case 1:  //1. Citeste una sau mai multe matrice
            int opt;
            if ( n == Matrice::m_existente() )
            {
                cout << "S-a citit deja numarul maxim de matrice.";
                opt = 1;
            }
            else
            {
                cout << "Cate matrice doriti sa cititi (maxim " << n-Matrice::m_existente() <<  " matrice)? ";
                cin >> opt;

                while ( opt < 1 || opt > n-Matrice::m_existente() )
                {

                    if ( n > 1 )
                    {
                        cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << n-Matrice::m_existente() << ".  -> ";
                        cin >> opt;
                    }
                    else
                    {
                        cout << "Selectia este incorecta. A fost setata citirea a maxim o singura matrice. Se va trece automat la citirea acesteia." << endl;
                        opt = 1;
                    }
                }

                int aux = Matrice::m_existente();
                for (int i = Matrice::m_existente() ; i < aux+opt && Matrice::m_existente() < n; i++)
                {
                    cout << endl << "Matricea "<< i+1 << endl;
                    tip_matrice (M[i], i);
                }
            }
            break;

        case 2: //2. Afiseaza una sau mai multe matrice (pentru matricele patratice, se afiseaza inclusiv determinantul)
            if ( Matrice::m_existente() == 0 ) cout << "Nu a fost citita nicio matrice. Cititi cel putin o matrice.";
            else  if( Matrice::m_existente() == 1 )
                cout << "A fost citita o singura matrice. Matricea 1:   " << *M[0];
            else
            {
                int opt = 0;
                cout << "Cate matrice doriti sa afisati? (maxim " << Matrice::m_existente() << " matrice) -> ";
                cin >> opt;
                while ( opt < 1 || opt > Matrice::m_existente())
                {
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << Matrice::m_existente() << ". -> ";
                    cin >> opt;
                }
                if ( opt == 1 )
                {
                    cout << endl << "Ce matrice doriti sa afisati? (introduceti un numar intre 1 si " << Matrice::m_existente() <<") -> ";
                    int i;
                    cin >> i;
                    while ( i < 1 || i > Matrice::m_existente())
                    {
                        cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << Matrice::m_existente() << ". -> ";
                        cin >> i;
                    }
                    cout << endl <<"Matricea " << i << ":    ";
                    cout << *M[i-1];
                }
                else
                    {
                        if ( opt < Matrice::m_existente()) cout << endl << "Primele " << opt << " matrice sunt: \n";
                        for (int i = 0 ; i < opt; i++)
                        {
                            cout << endl << "Matricea "<< i+1 << ":    ";
                            cout << *M[i];
                        }
                    }
                if ( opt == Matrice::m_existente() ) cout << "\nS-au afisat toate matricele existente.";
            }
            break;

        case 3: //3. Verifica daca o matrice triunghiulara este diagonala
            if (Matrice::m_existente() > 1)
            {
                cout << "Doriti sa afisati toate matricele existente? Optiuni posibile:" << endl;
                cout << "1. Da" << endl << "0. Nu" << endl;
                int af = 0;
                cout << "Optiunea dumnavoastra: ";
                cin >> af;
                while (af != 0 && af != 1)
                {
                        cout << "Selectia este incorecta. Introduceti un numar din lista data. -> ";
                        cin >> af;
                }
                if ( af == 1 )
                    for (int i = 0 ; i < Matrice::m_existente(); i++)
                        cout << endl << "Matricea "<< i+1 << ":    " << *M[i];
            }

            if ( Matrice::m_existente() == 0 ) cout << "Nu a fost citita nicio matrice. Cititi cel putin o matrice.";
            else if ( Matrice::m_existente() == 1 )
            {
                cout << "\nA fost citita o singura matrice." << endl;
                cout << endl << "Matricea este: " << *M[0];
                M[0]->Matrice_diagonala();
            }
            else
            {
                int m1;
                cout << "\nAlegeti matricea dorita: intre 1 si " << Matrice::m_existente() << "). -> ";
                cin >> m1;
                while ( m1 < 1 || m1 > Matrice::m_existente())
                {
                    if( !(m1 < 1 || m1 > Matrice::m_existente()) )
                        break;
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << Matrice::m_existente() << ". -> ";
                    cin >> m1;
                }
                cout << endl << "Matricea aleasa este: " << endl << *M[m1-1];
                M[m1-1]->Matrice_diagonala();
            }
            break;

        case 4: //4. Demonstrare functie statica
            cout << endl << "Am definit o variabila si o functie statice." << endl;
            cout << endl << "Variabila mat_existente salveaza numarul de matrice care se afla in prezent in vectorul utilizat." << endl;
            cout << "Altfel spus, aceasta variabila retine numarul de matrice cu care se lucreaza efectiv in program => de fiecare data " << endl;
            cout << "cand o matrice auxiliara (temporara) este distrusa, valoarea din variabila mat_existente scade cu 1." << endl;
            cout << "Functia m_existente() afiseaza variabila mat_existente. ";
            cout << "\n\nIn prezent, exista " << Matrice::m_existente() << " matrice in program." << endl;
            break;

        case 5: //5. Exemplificare downcast
            cout << endl << endl;
            cout << "Pentru ilustrarea conceptului de downcast am scris, in functia 'downcast', urmatoarele linii: " << endl <<endl;
            cout << "Matrice_patratica *mp = (Matrice_patratica*)new Matrice;" << endl;
            cout << "cin >> *mp;" << endl;
            cout << "cout <<*mp;" << endl;
            cout << endl;

            cout << "Se apeleaza functia downcast:" << endl << endl;
            downcast();
            break;

        case 0: //0. Iesire
            break;

        default: //selectie incorecta
            cout<<"\nSelectia este incorecta. Introduceti un numar din lista data.\n";
            break;
        }
        cout<<"\n\n";
        system("pause");
        system("cls");
    }
}


/////////////////////////////////////////
int main()
{
    meniu();
    return 0;
}

