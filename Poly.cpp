#include <iostream>

#include "Poly.h"

#include <fstream>
#include <cmath>

using namespace std;



Poly::Poly():grau(-1),a(nullptr)
{

}


Poly::Poly(int grau):grau(grau),a(nullptr)
{

    if(this->grau<0){
        this->a = nullptr;
    }

    else if (this->grau == 0){
        this->a = new double[1];
        this->a[0] = 0.0;
        }

    else{
        this->a = new double[this->grau+1];
        for (int i = 0; i<=this->grau ; i++){
            this->a[i] = 0;
        }
        this->a[this->grau] = 1.0;
    }


    }



Poly::Poly(const Poly& p):grau(p.grau),a(nullptr)
{

  if (this->grau>=0) a = new double[this->grau+1];
  for (int i=0; i<=this->grau; ++i) this->a[i] = p.a[i];


}


Poly::Poly(Poly&& p):grau(p.grau),a(p.a){
    p.grau = 0;
    p.a = nullptr;
}


Poly::~Poly(){
    clear();
}

void Poly::reduceGrau(){


}


void Poly::preencher(istream& Y,ostream& X){


    if(this->grau>0){
        for (int i = this->grau ; i>=0 ; --i){
            X<<"x^"<<i<<": "<<endl;
            Y>>this->a[i];
            while(i == this->grau && this->a[i]==0){
                X<<"digite um coeficiente válido"<<endl;
                Y>>this->a[i];
            }

        }


    }
    if(this->grau == 0){
        X<<"digite o valor do termo constante "<<endl;
        Y>>this->a[0];


    }

    if((*this).empty()){
        X<<"o polinomio é vazio"<<endl;

    }

}

void Poly::clear(){

    delete[] this->a;
    this->grau = -1;
    this->a = nullptr;

}

void Poly::imprimir(ostream& X) const{

    if((*this).empty()){
        X<<""<<endl;
    }
    else{

    for (int j = this->grau; j>=0 ; --j){

        if (this->a[j] == 0){
            if(j == 0 && this->grau == 0){
                X<<this->a[j];
            }
        //0.2x^3 + 3.2x^2 -1.4x +5.7
        //0.2x^3 + 0*x^2 +1.4x
        //x+0
        }
        else{
            if(a[j]<0){
                X<<"-";
            }
            else{
                if(j!=this->grau){
                    X<<"+";
                    }
                }

            if(fabs(a[j])!=1.0 || j==0){
                    X<<fabs(a[j]);
                }
            if(j!=0){
                if(fabs(a[j])!=1.0){
                    X<<"*";
                }
                X<<"x";
                if(j>1){
                    X<<"^";
                    X<<j<<"";
                    }

                }

            }

        }
    }
}


std::ostream& operator<<(std::ostream& X, const Poly& p){

    p.imprimir(X);
    return X;

}

std::istream& operator>>(std::istream& Y, Poly& p){

    if(p.getGrau()<0){
            cerr<<"Polinômio vazio"<<endl;
    }
    else{
        p.preencher(Y,cout);
    }
    return Y;
}

void Poly::recriar(int novo_grau){

    (*this) = Poly(novo_grau);
}

bool Poly::isZero()const{
    if(this->grau == 0 && this->a[0] == 0.0){
            return true;
    }
    return false;
}


void Poly::setCoef(int posicao, double valor){

    if(posicao<0 || posicao>this->grau){

        cerr<<"indice inválido"<<endl;

    }
    else if(posicao == this->grau && valor==0){
        cerr<<" o termo de grau "<< posicao <<" do polinomio não pode ser zero"<<endl;
    }
    else{
        this->a[posicao] = valor;
    }
}




Poly Poly::operator=(const Poly& p){

	if(this != &p){
            delete[] this->a;
            this->a = nullptr;
            this->grau = p.grau;
            if(this->grau >= 0){
                this->a = new double[this->grau+1];
                for (int j = 0; j<=this->grau ; j++){
                    this->a[j] = p.a[j];

                    }

            }
            else *this=Poly();


	}


    return *this;

}

Poly Poly::operator=(Poly&& P){

    clear();
    if(this!=&P){
        delete[] a;
        this->grau = P.grau;
        this->a = P.a;
        P.grau = 0;
        P.a = nullptr;
    }
    return *this;

}

double Poly::operator[](int posicao) const{

    return getCoef(posicao);

}

double Poly::operator()(double valor) const{
    Poly prov = *this;
    return prov.getValor(valor);
}


Poly Poly::operator+(const Poly& p2) const{

    if(((p2.empty() || p2.isZero()) && !((*this).empty())) || (isZero()&& p2.empty())){
        return *this;
    }

    else if((((*this).empty() || (*this).isZero()) && !(p2.empty())) || (empty() && (p2.isZero()))){
        return p2;
    }

    Poly prov(max(getGrau(),p2.getGrau()));
    for(int i = 0; i<=max(this->grau,p2.grau); i++){
        prov.a[i] = (*this)[i] + p2[i];

    }



    int n = prov.grau;
    while(prov.a[prov.grau] == 0 && prov.grau>0){
        prov.grau--;
    }

    if(prov.grau!=n){
        for(int i = 0; i<=prov.grau; i++){
            prov.a[i] = (*this)[i] + p2[i];
        }
    }

    return prov;
}


Poly Poly::operator-() const{

    Poly prov(this->grau);
    if((*this).empty() || (*this).isZero()){
        return *this;
    }

    for(int j = 0; j<=this->grau ; ++j){

        prov.a[j] = -1*this->a[j];
    }

    return prov;
}

Poly Poly::operator-(const Poly& p2) const{

    return (*this)+(-p2);
}

Poly Poly::operator*(const Poly& p2) const{

    if(p2.empty() || empty()){
        return Poly();
    }

    else if(p2.isZero() || isZero()){
        return Poly(0);
    }
    else if(p2.getGrau()== 0 && p2[0]==1){
        return *this;

    }
    else if(getGrau()==0 && (*this)[0]==1){
        return p2;
    }
    Poly prov(getGrau()+p2.getGrau());


    for(int k = 0; k<=prov.grau; k++){
        prov.a[k] = 0;
    }

        for(int j = 0; j<=p2.getGrau(); j++){

            for (int i = 0; i<=getGrau(); i++){

                prov.a[i+j] = prov.a[i+j]+(*this)[i]*p2[j];
            }

        }

    return prov;
}




bool Poly::operator==(const Poly& p2) const{
    if (this->grau != p2.grau){
        return false;
    }

    for(int j = 0; j<=this->grau ; ++j){
        if(this->a[j] != p2.a[j]) return false;

    }
    return true;
}

bool Poly::operator!=(const Poly& p2) const{

    if((*this)==p2){
        return false;
    }
    else{
        return true;
    }
}

//a função move é usada para apenas mover o conteúdo de p.a para this->a, desse modo não é criada variável cópia ou sem nome
double Poly::getGrau() const{
    return this->grau;
}


double Poly::getCoef(int posicao) const{
	if(posicao<0 || posicao>this->grau){
		return 0.0;
	}

    return this->a[posicao];

}
/*
*/





double Poly::getValor(double valor) const{
    if((*this).empty()){
        return 0;
    }
    if(valor == 0){

        return this->a[0];
    }
    double s = 0;
    for(int j = 0; j<=(*this).getGrau() ; j++){

        s = s + this->a[j]*pow(valor,j);


    }
    return s;


}

bool Poly::empty() const{
    if(this->grau<0){
        return true;

    }

    return false;

}

bool Poly::salvar(const string& nome) const{

    ofstream arquivo;
    arquivo.open(nome);
    if(arquivo.is_open()){
        arquivo <<"POLY "<<this->grau<<endl;
        if(this->grau<0){
        }
        else{
            for(int i = 0; i<=this->grau ; ++i){
                arquivo<<a[i]<<" ";
            }
            arquivo<<endl;
        }

    }
    if (arquivo.good()) return true;
    else{
        return false;
    }




}


bool Poly::ler(const string& nome){

    ifstream arquivo(nome);
    string cabecalho;
    int n;

    if(!(arquivo.is_open())){
        return false;
            }

    arquivo>>cabecalho;
    if(!(arquivo.good()) || cabecalho != "POLY"){
        return false;
    }



    if(!(arquivo.good())){
        arquivo.close();
        return false;
    }

    arquivo>>n;
    Poly prov(n);

    //recriar(n);
    if(n<0){
        return true;
    }

    for(int i = 0; i<=n; i++){
        arquivo>>prov.a[i];
        if(!(arquivo.good())){
            arquivo.close();
            return false;
        }
    }
    if(prov[n]==0 && n!=0) return false;

    *this = prov;
    return true;
}



