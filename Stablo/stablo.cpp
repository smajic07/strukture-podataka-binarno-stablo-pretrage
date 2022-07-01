#ifndef STABLO_CPP
#define STABLO_CPP

#include "stablo.h"

template <typename Tip>
Stablo<Tip>::Stablo(Cvor *korijen) : korijen(korijen), velicina(0) {
    if(this->korijen!=nullptr){
        this->korijen->rod=nullptr;
        SetujVelicinu(this->korijen);
    }
}

template <typename Tip>
void Stablo<Tip>::SetujVelicinu(Cvor *korijen){
    if(korijen->ld!=nullptr) SetujVelicinu(korijen->ld);
    velicina++;
    if(korijen->dd!=nullptr) SetujVelicinu(korijen->dd);
}

template <typename Tip>
Stablo<Tip>::Stablo() : korijen(nullptr), velicina(0) {}

template <typename Tip>
void Stablo<Tip>::OcistiStabloRekurzivno(Cvor *korijen){
    if(korijen==nullptr) return;

    if(korijen->ld!=nullptr) OcistiStabloRekurzivno(korijen->ld);
    if(korijen->dd!=nullptr) OcistiStabloRekurzivno(korijen->dd);

    if(korijen->rod!=nullptr){
        if(korijen->rod->ld==korijen) korijen->rod->ld=nullptr;
        else korijen->rod->dd=nullptr;
    }
    else this->korijen=nullptr;

    delete korijen;
    velicina--;
}

template<typename Tip>
Stablo<Tip>::~Stablo(){
    OcistiStabloRekurzivno(korijen);
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::PomocniKopirac(Cvor *korijen, Cvor *korijen_roditelj,
                                                        int &velicina){
    if(korijen==nullptr) return nullptr;

    Cvor* novi=new Cvor(korijen->element);
    novi->rod=korijen_roditelj;
    novi->prioritet=korijen->prioritet;
    velicina++;

    novi->ld=PomocniKopirac(korijen->ld, novi, velicina);
    novi->dd=PomocniKopirac(korijen->dd, novi, velicina);

    return novi;
}

template <typename Tip>
Stablo<Tip>::Stablo(const Stablo<Tip> &s) : Stablo() {
    korijen=PomocniKopirac(s.korijen, nullptr, velicina);
}

template <typename Tip>
Stablo<Tip>::Stablo(Stablo<Tip> &&s) : korijen(s.korijen), velicina(s.velicina) {
    s.korijen=nullptr;
    s.velicina=0;
}

template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(const Stablo<Tip> &rhs){
    if(this==&rhs) return *this;

    OcistiStabloRekurzivno(korijen);
    korijen=PomocniKopirac(rhs.korijen, nullptr, velicina);

    return *this;
}

template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(Stablo<Tip> &&rhs){
    swap(korijen, rhs.korijen);
    swap(velicina, rhs.velicina);

    return *this;
}

template <typename Tip>
int Stablo<Tip>::Size() const {
    return velicina;
}

template <typename Tip>
bool Stablo<Tip>::Find(const Tip &element) const {
    Cvor *trenutni(korijen);
    while(trenutni!=nullptr){
        if(trenutni->element==element) return true;

        if(trenutni->element>element) trenutni=trenutni->ld;
        else trenutni=trenutni->dd;
    }

    return false;
}

template <typename Tip>
void Stablo<Tip>::Rotacija(Cvor *cvor){
    if(cvor->rod==nullptr) return;

    if(cvor->rod->ld==cvor) DesnaRotacija(cvor, cvor->rod);
    else if(cvor->rod->dd==cvor) LijevaRotacija(cvor, cvor->rod);
}

template <typename Tip>
void Stablo<Tip>::DesnaRotacija(Cvor *lijevi, Cvor *gornji){
    if(gornji==korijen) korijen=lijevi;
    else if(gornji->rod->ld==gornji) gornji->rod->ld=lijevi;
    else gornji->rod->dd=lijevi;

    lijevi->rod=gornji->rod;
    gornji->rod=lijevi;

    gornji->ld=lijevi->dd;
    lijevi->dd=gornji;

    if(gornji->ld!=nullptr) gornji->ld->rod=gornji;
}

template <typename Tip>
void Stablo<Tip>::LijevaRotacija(Cvor *desni, Cvor *gornji){
    if(gornji==korijen) korijen=desni;
    else if(gornji->rod->ld==gornji) gornji->rod->ld=desni;
    else gornji->rod->dd=desni;

    desni->rod=gornji->rod;
    gornji->rod=desni;

    gornji->dd=desni->ld;
    desni->ld=gornji;

    if(gornji->dd!=nullptr) gornji->dd->rod=gornji;
}

template <typename Tip>
void Stablo<Tip>::Insert(const Tip &element, const bool &jelKljuc){
    if(korijen==nullptr){
        korijen=new Cvor(element);//prioritet mu je sad svakako najveci ako je jelKljuc true
        velicina=1;

        return;
    }

    Cvor *trenutni(korijen);
    while(trenutni!=nullptr){
        if(trenutni->element==element) return;

        if(trenutni->element>element){
            if(trenutni->ld!=nullptr) trenutni=trenutni->ld;
            else{
                trenutni->ld=new Cvor(element, trenutni);
                velicina++;

                if(jelKljuc) trenutni->ld->prioritet=korijen->prioritet+1;

                Cvor *umetnuti(trenutni->ld);
                while(umetnuti!=korijen and umetnuti->prioritet>umetnuti->rod->prioritet){
                    Rotacija(umetnuti);
                }

                return;
            }
        }
        else{
            if(trenutni->dd!=nullptr) trenutni=trenutni->dd;
            else{
                trenutni->dd=new Cvor(element, trenutni);
                velicina++;

                if(jelKljuc) trenutni->dd->prioritet=korijen->prioritet+1;

                Cvor *umetnuti(trenutni->dd);
                while(umetnuti!=korijen and umetnuti->prioritet>umetnuti->rod->prioritet){
                    Rotacija(umetnuti);
                }

                return;
            }
        }
    }
}

template <typename Tip>
bool Stablo<Tip>::List(Cvor *cvor) const {
    return cvor->ld==nullptr and cvor->dd==nullptr;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::FindCvor(const Tip &element){
    Cvor *trenutni(korijen);
    while(trenutni!=nullptr){
        if(trenutni->element==element) return trenutni;

        if(trenutni->element>element) trenutni=trenutni->ld;
        else trenutni=trenutni->dd;
    }

    return nullptr;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::OdgovarajuceDijete(Cvor *cvor){
    if(cvor->ld==nullptr) return cvor->dd;
    if(cvor->dd==nullptr) return cvor->ld;
    if(cvor->ld->prioritet>cvor->dd->prioritet) return cvor->ld;
    return cvor->dd;
}

template <typename Tip>
void Stablo<Tip>::Delete(const Tip &element){
    Cvor *za_brisanje(FindCvor(element));
    if(za_brisanje==nullptr) return;

    if(List(za_brisanje)){//nema djece
        if(za_brisanje==korijen) korijen=nullptr;
        else{
            if(za_brisanje->rod->ld==za_brisanje) za_brisanje->rod->ld=nullptr;
            else za_brisanje->rod->dd=nullptr;
        }
    }
    else if(za_brisanje->ld!=nullptr and za_brisanje->dd==nullptr){//ima samo lijevo dijete
        if(za_brisanje==korijen){
            korijen=za_brisanje->ld;
            korijen->rod=nullptr;
        }
        else{
            za_brisanje->ld->rod=za_brisanje->rod;
            if(za_brisanje->rod->ld==za_brisanje) za_brisanje->rod->ld=za_brisanje->ld;
            else za_brisanje->rod->dd=za_brisanje->ld;
        }
    }
    else if(za_brisanje->ld==nullptr and za_brisanje->dd!=nullptr){//ima samo desno dijete
        if(za_brisanje==korijen){
            korijen=za_brisanje->dd;
            korijen->rod=nullptr;
        }
        else{
            za_brisanje->dd->rod=za_brisanje->rod;
            if(za_brisanje->rod->ld==za_brisanje) za_brisanje->rod->ld=za_brisanje->dd;
            else za_brisanje->rod->dd=za_brisanje->dd;
        }
    }
    else{//ima oba djeteta
        Cvor *sljedbenik(za_brisanje->dd);
        while(sljedbenik->ld!=nullptr){
            sljedbenik=sljedbenik->ld;
        }

        if(sljedbenik->rod==za_brisanje){
            sljedbenik->rod=za_brisanje->rod;
            sljedbenik->ld=za_brisanje->ld;

            if(za_brisanje->ld!=nullptr) za_brisanje->ld->rod=sljedbenik;

            if(za_brisanje==korijen) korijen=sljedbenik;
            else{
                if(za_brisanje->rod->ld==za_brisanje) za_brisanje->rod->ld=sljedbenik;
                else za_brisanje->rod->dd=sljedbenik;
            }

            while(!List(sljedbenik) and
                  OdgovarajuceDijete(sljedbenik)->prioritet>sljedbenik->prioritet){
                Rotacija(OdgovarajuceDijete(sljedbenik));
            }
        }
        else{
            sljedbenik->ld=za_brisanje->ld;
            za_brisanje->ld->rod=sljedbenik;

            sljedbenik->rod->ld=sljedbenik->dd;
            if(sljedbenik->dd!=nullptr) sljedbenik->dd->rod=sljedbenik->rod;

            sljedbenik->dd=za_brisanje->dd;
            za_brisanje->dd->rod=sljedbenik;

            sljedbenik->rod=za_brisanje->rod;

            if(za_brisanje==korijen) korijen=sljedbenik;
            else{
                if(za_brisanje->rod->ld==za_brisanje) za_brisanje->rod->ld=sljedbenik;
                else za_brisanje->rod->dd=sljedbenik;
            }

            while(!List(sljedbenik) and
                  OdgovarajuceDijete(sljedbenik)->prioritet>sljedbenik->prioritet){
                Rotacija(OdgovarajuceDijete(sljedbenik));
            }
        }
    }

    delete za_brisanje;
    velicina--;
}

template <typename Tip>
void Stablo<Tip>::ObradiElementeRekurzivno(Cvor *korijen, void (f)(Tip)) const {
    if(korijen->ld!=nullptr) ObradiElementeRekurzivno(korijen->ld, f);
    f(korijen->element);
    if(korijen->dd!=nullptr) ObradiElementeRekurzivno(korijen->dd, f);
}

template <typename Tip>
void Stablo<Tip>::ObradiElemente(void (f)(Tip)) const {
    if(korijen!=nullptr) ObradiElementeRekurzivno(korijen, f);
}

template <typename Tip>
pair<Stablo<Tip>, Stablo<Tip>> Razdvajanje(Stablo<Tip> &s, const Tip &kljuc){
    s.Insert(kljuc, true);
    pair<Stablo<Tip>, Stablo<Tip>> par;
    par={Stablo<Tip>(s.korijen->ld), Stablo<Tip>(s.korijen->dd)};

    delete s.korijen;
    s.korijen=nullptr;
    s.velicina=0;

    return par;
}

template <typename Tip>
Tip Stablo<Tip>::OdgovarajuciBroj(const Stablo<Tip> &s1, const Stablo<Tip> &s2) const {
    Cvor *trenutni1(s1.korijen);
    while(trenutni1->dd!=nullptr) trenutni1=trenutni1->dd;

    Cvor *trenutni2(s2.korijen);
    while(trenutni2->ld!=nullptr) trenutni2=trenutni2->ld;

    return (trenutni1->element+trenutni2->element)/2;
}

template <typename Tip>
void Stablo<Tip>::PostupakSpajanja(Stablo<Tip> &s1, Stablo<Tip> &s2, const Tip &element,
                                   const int &prioritet){
    if(prioritet==0){
        if(s1.velicina==0 and s2.velicina==0) return;

        if(s1.velicina==0){
            korijen=s2.korijen;
            velicina=s2.velicina;
            s2.korijen=nullptr;
            s2.velicina=0;
        }
        else if(s2.velicina==0){
            korijen=s1.korijen;
            velicina=s1.velicina;
            s1.korijen=nullptr;
            s1.velicina=0;
        }
        else{
            Insert(OdgovarajuciBroj(s1, s2));
            korijen->prioritet=-1;

            korijen->ld=s1.korijen;
            korijen->ld->rod=korijen;
            velicina+=s1.velicina;
            s1.korijen=nullptr;
            s1.velicina=0;

            korijen->dd=s2.korijen;
            korijen->dd->rod=korijen;
            velicina+=s2.velicina;
            s2.korijen=nullptr;
            s2.velicina=0;

            Cvor *za_obrisati(korijen);
            while(!List(za_obrisati)){
                Rotacija(OdgovarajuceDijete(za_obrisati));//jer za_obrisati ima -1 prioritet
            }

            if(za_obrisati->rod->ld==za_obrisati) za_obrisati->rod->ld=nullptr;
            else za_obrisati->rod->dd=nullptr;

            delete za_obrisati;
            velicina--;
        }
    }
    else{//prioritet<0 tj. Spajanje iz UnijeRekurzivno
        Insert(element);
        korijen->prioritet=-prioritet;//On ce imati najveci prioritet

        if(s1.velicina>0){
            korijen->ld=s1.korijen;
            korijen->ld->rod=korijen;
            velicina+=s1.velicina;
            s1.korijen=nullptr;
            s1.velicina=0;
        }
        if(s2.velicina>0){
            korijen->dd=s2.korijen;
            korijen->dd->rod=korijen;
            velicina+=s2.velicina;
            s2.korijen=nullptr;
            s2.velicina=0;
        }
    }
}

template <typename Tip>
Stablo<Tip> Spajanje(Stablo<Tip> &s1, Stablo<Tip> &s2, const Tip &element,
                     const int &prioritet){
    Stablo<Tip> za_vratiti;
    za_vratiti.PostupakSpajanja(s1, s2, element, prioritet);

    return za_vratiti;
}

template <typename Tip>
Stablo<Tip> Stablo<Tip>::UnijaRekurzivno(Stablo<Tip> &s1, Stablo<Tip> &s2){
    if(s1.korijen==nullptr) return s2;
    if(s2.korijen==nullptr) return s1;

    Stablo<Tip> za_vratiti;
    if(s1.korijen->prioritet>s2.korijen->prioritet){
        pair<Stablo<Tip>, Stablo<Tip>> pomocno(Razdvajanje(s2, s1.korijen->element));

        Stablo<Tip> a2, b2;
        a2.korijen=s1.korijen->ld;
        b2.korijen=s1.korijen->dd;

        if(a2.korijen!=nullptr) a2.korijen->rod=nullptr;
        if(b2.korijen!=nullptr) b2.korijen->rod=nullptr;

        Stablo<Tip> a(za_vratiti.UnijaRekurzivno(a2, pomocno.first));
        Stablo<Tip> b(za_vratiti.UnijaRekurzivno(b2, pomocno.second));

        za_vratiti=Spajanje(a, b, s1.korijen->element, -s1.korijen->prioritet);

        delete s1.korijen;
        s1.korijen=nullptr;
        s1.velicina=0;
    }
    else{
        pair<Stablo<Tip>, Stablo<Tip>> pomocno(Razdvajanje(s1, s2.korijen->element));

        Stablo<Tip> a2, b2;
        a2.korijen=s2.korijen->ld;
        b2.korijen=s2.korijen->dd;

        if(a2.korijen!=nullptr) a2.korijen->rod=nullptr;
        if(b2.korijen!=nullptr) b2.korijen->rod=nullptr;

        Stablo<Tip> a(za_vratiti.UnijaRekurzivno(pomocno.first, a2));
        Stablo<Tip> b(za_vratiti.UnijaRekurzivno(pomocno.second, b2));

        za_vratiti=Spajanje(a, b, s2.korijen->element, -s2.korijen->prioritet);

        delete s2.korijen;
        s2.korijen=nullptr;
        s2.velicina=0;
    }

    return za_vratiti;
}

template <typename Tip>
Stablo<Tip> Unija(Stablo<Tip> &s1, Stablo<Tip> &s2){
    Stablo<Tip> za_vratiti;
    za_vratiti=za_vratiti.UnijaRekurzivno(s1, s2);
    za_vratiti.korijen->dd=nullptr;
    return za_vratiti;
}

template<typename Tip>
void ispisi(Tip e){
    cout << e << " ";
}

template <typename Tip>
ostream& operator<<(ostream &ispis, const Stablo<Tip> &s){
    ispis << s.Size() << ": { ";
    s.ObradiElemente(ispisi);
    ispis << "}";

    return ispis;
}

#endif // STABLO_CPP
