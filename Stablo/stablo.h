#ifndef STABLO_H
#define STABLO_H

#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

template <typename Tip>
class Stablo;

//Nije funkcija clanica, a ima 2 opcionalna parametra, zato deklarisem prototip ovdje
template <typename Tip>
Stablo<Tip> Spajanje(Stablo<Tip> &s1, Stablo<Tip> &s2, const Tip &element=0,
                     const int &prioritet=0);
//Spajanje sa 4 parametra će se pozivati u funkciji UnijaRekurzivno

template <typename Tip>
class Stablo{

//privani atributi
    struct Cvor{
        Tip element;
        int prioritet;
        Cvor *rod, *ld, *dd;
        Cvor(const Tip &element, Cvor *rod=nullptr, Cvor *ld=nullptr, Cvor *dd=nullptr) :
             element(element), rod(rod), ld(ld), dd(dd) { prioritet=rand()+1; }
                                                  //raspon prioriteta je od 1 do RAND_MAX
    };

    Cvor *korijen;
    int velicina;

//privatne funkcije
    void SetujVelicinu(Cvor *korijen);
    Stablo(Cvor *korijen);

    void OcistiStabloRekurzivno(Cvor *korijen);
    Cvor* PomocniKopirac(Cvor *korijen, Cvor *korijen_roditelj, int &velicina);

    void Rotacija(Cvor *cvor);
    void DesnaRotacija(Cvor *lijevi, Cvor *gornji);
    void LijevaRotacija(Cvor *desni, Cvor *gornji);
    bool List(Cvor *cvor) const;
    Cvor* FindCvor(const Tip &element);
    Cvor* OdgovarajuceDijete(Cvor *cvor);
    void ObradiElementeRekurzivno(Cvor *korijen, void (f)(Tip)) const;

    Tip OdgovarajuciBroj(const Stablo<Tip> &s1, const Stablo<Tip> &s2) const;
    void PostupakSpajanja(Stablo<Tip> &s1, Stablo<Tip> &s2, const Tip &element,
                          const int &prioritet);
    Stablo<Tip> UnijaRekurzivno(Stablo<Tip> &s1, Stablo<Tip> &s2);

//konstruktori, destruktor i javne funkcije
public:

    Stablo();
    ~Stablo();
    Stablo(const Stablo<Tip> &s);
    Stablo(Stablo<Tip> &&s);
    Stablo<Tip>& operator=(const Stablo<Tip> &rhs);
    Stablo<Tip>& operator=(Stablo<Tip> &&rhs);

    int Size() const;
    bool Find(const Tip &element) const;
    void Insert(const Tip &element, const bool &jelKljuc=false);
    //jelKljuc je true kada insertujemo element za kojeg zelimo da bude korijen
    void Delete(const Tip &element);
    void ObradiElemente(void (f)(Tip)) const;

//prijateljske funkcije
    template <typename T>
    friend pair<Stablo<T>, Stablo<T>> Razdvajanje(Stablo<T> &s, const T &kljuc);

    template <typename T>
    friend Stablo<T> Spajanje(Stablo<T> &s1, Stablo<T> &s2, const T &element,
                              const int &prioritet);

    template <typename T>
    friend Stablo<T> Unija(Stablo<T> &s1, Stablo<T> &s2);

};

#include "stablo.cpp"

#endif // STABLO_H
