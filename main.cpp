#include <iostream>
#include <fstream>
using namespace std;

const int dimensiuneVector = 1001;

class Multime{
    int v[dimensiuneVector], n;
public:
    Multime(int v1[], int n1=0);
    Multime(const Multime &A);
    ~Multime();
    void transformare();
    friend Multime operator + (const Multime &A, const Multime &B);
    friend Multime operator * (const Multime &A, const Multime &B);
    friend Multime operator - (const Multime &A, const Multime &B);
    friend istream &operator >> (istream &input, Multime &A);
    friend ostream &operator << (ostream &output, Multime &A);
};

Multime::Multime(int v1[], int n1) {
    int i;
    n = n1;
    for(i=1; i<=n; ++i)
        v[i] = v1[i];
    this->transformare();
}

Multime::Multime(const Multime &A) {
    int i;
    n = A.n;
    for(i=1; i<=n; ++i)
        v[i] = A.v[i];
}

Multime::~Multime() {
    int i;
    for(i=1; i<=n; ++i)
        v[i] = 0;
    n = 0;
}

int caut(const int v[], int n, int poz, int x) { //returneaza pozitia primei aparitii a elementului x in vectorul v dupa pozitia poz
    int p = -1, i;
    for(i = poz+1; i <= n; ++i)
        if(v[i] == x) {
            p = i;
            break;
        }
    return p;
}

void eliminare(int v[], int &n, int p){ //elimina din vectorul v elementul de pe pozitia p
    int i;
    for(i=p+1; i<=n; ++i)
        v[i-1] = v[i];
    n--;
}

void Multime::transformare() {
    int i, poz;
    for(i=1; i<=n; ++i)
    {
        poz = caut(v, n, i, v[i]);
        while(poz != -1)
        {
            eliminare(v, n, poz);
            poz = caut(v, n, i, v[i]);
        }
    }
}

Multime operator + (const Multime &A, const Multime &B){
    int i, k = 0, c[1001];
    for(i=1; i<=A.n; ++i)
        c[++k] = A.v[i];
    for(i=1; i<=B.n; ++i)
        if(caut(c, k, 0, B.v[i]) == -1)
            c[++k] = B.v[i];
    return Multime(c, k);
}

Multime operator * (const Multime &A, const Multime &B){
    int i, k = 0, c[1001];
    for(i=1; i<=A.n; ++i)
        if(caut(B.v, B.n, 0, A.v[i]) != -1)
            c[++k] = A.v[i];
    return Multime(c, k);
}

Multime operator - (const Multime &A, const Multime &B){
    int c[1001], k = 0, i;
    for(i= 1; i<=A.n; ++i)
        if(caut(B.v, B.n, 0, A.v[i]) == -1)
            c[++k] = A.v[i];
    return Multime(c, k);
}

istream &operator >> (istream &input, Multime &A){
    input >> A.n;
    int i;
    for(i=1; i<=A.n; ++i)
        input >> A.v[i];
    A.transformare();
    return input;
}

ostream &operator << (ostream &output, Multime &A){
    int i;
    if(A.n == 0) output << "Multimea vida \n";
    else {
        output << "{";
        for (i = 1; i < A.n; ++i)
            output << A.v[i] << ", ";
        output << A.v[A.n] << "}" << "\n";
    }
    return output;
}

int main() {
    ifstream fin("exemple.txt");
    int v[dimensiuneVector], nrExemple, i, valori = dimensiuneVector;
    for(i=0; i<=dimensiuneVector; ++i)
        v[i] = valori--;
    Multime A(v), B(v);
    fin >> nrExemple;
    for(i=1; i<=nrExemple; ++i){
        fin >> A >> B;
        Multime C = A + B;
        cout << "Reuniune: " << C;
        Multime D = A * B;
        cout << "Intersectie: " << D;
        Multime E = A - B;
        cout << "Diferenta: " <<  E << "\n";
    }
    return 0;
}
