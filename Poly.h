#ifndef POLY_H
#define POLY_H


#include <iostream>
#include <string>
#include <fstream>
using namespace std;




class Poly{



private:
    int grau;
    double* a;


public:

    Poly();

    explicit Poly(int grau);

    Poly(const Poly& p);

	Poly(Poly&& p);

    ~Poly();

    void reduceGrau();

    void clear();

    void imprimir(ostream& X) const;

    void preencher(istream& Y, ostream& X);

    friend ostream& operator<<(ostream& X, const Poly& p);

    friend istream& operator>>(istream& Y, Poly& p);

    void recriar(int novo_grau);

    bool isZero() const;

    Poly operator=(const Poly& p);

    Poly operator=(Poly&& P);

    double operator[](int posicao) const;

    double operator()(double valor) const;

	Poly operator+(const Poly& p2) const;

	Poly operator-() const;

	Poly operator-(const Poly& p2) const;

	Poly operator*(const Poly& p2) const;

    bool operator ==(const Poly& p2) const;

    bool operator !=(const Poly& p2) const;

    double getGrau() const;

    double getValor(double valor) const;

    double getCoef(int posicao) const;

    void setCoef(int posicao, double valor);

    bool empty() const;

    bool salvar(const string& nome) const;

    bool ler(const string& nome);


};
#endif // POLY_H
