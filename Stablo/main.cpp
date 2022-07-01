#include "stablo.h"

int main(){///Pisao sam šta se redom poziva kod svake linije koda osim kod operatora <<
    srand(time(NULL));

    Stablo<int> s, s1; ///Konstuktor bez parametara dva puta
    s1.Insert(1); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(3); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(5); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(7); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(6); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(4); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(2); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(0); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(7); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(7); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(0); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(0); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl;
    s1.Insert(7); ///Funkcija Insert sa jednim parametrom
    cout << s1 << endl << endl;

    s=Stablo<int>(s1); ///Konstruktor kopije i pomjerajuci operator dodjele
    cout << s << endl;
    cout << s.Find(3) << endl; ///Funkcija Find sa jednim parametrom
    cout << s.Find(8) << endl << endl; ///Funkcija Find sa jednim parametrom

    s1.Delete(1); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(3); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(5); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(7); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(0); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(2); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(4); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl;
    s1.Delete(6); ///Funkcija Delete sa jednim parametrom
    cout << s1 << endl << endl;


    Stablo<int> s3(s); ///Konstruktor kopije
    cout << s3 << endl;
    Stablo<int> s4; ///Konstruktor bez parametara
    s4=s3; ///Operator dodjele
    cout << s4 << endl << endl;

    s4.Delete(4); ///Funkcija Delete sa jednim parametrom
    cout << s4 << endl;
    pair<Stablo<int>, Stablo<int>> par(Razdvajanje(s4, 4)); ///Funkcija Razdvajanje sa dva parametra, pomjerajuci konstruktor kopije dva puta
    cout << s4 << endl;
    cout << par.first << endl;
    cout << par.second << endl << endl;

    Stablo<int> s2(Spajanje(par.first, par.second)); ///Funkcija Spajanje sa dva parametra, pomjerajuci konstruktor kopije
    cout << s2 << endl;
    cout << par.first << endl;
    cout << par.second << endl << endl;

    Stablo<double> s5, s6; ///Konstruktor bez parametara dva puta
    for(int i=0; i<20; i++){
        if(i%2==0) s5.Insert(i); ///Funkcija Insert sa jednim parametrom 10 puta
        else s6.Insert(i); ///Funkcija Insert sa jednim parametrom 10 puta
    }
    cout << s5 << endl;
    cout << s6 << endl << endl;

    Stablo<double> s7(Unija(s5,s6)); ///Funkcija Unija sa dva parametra, pomjerajuci konstruktor kopije
    cout << s5 << endl;
    cout << s5 << endl;
    cout << s7 << endl << endl;
    for(int i=1; i<25; i++){
        if(i%3==0){
            s7.Delete(i); ///Funkcija Delete sa jednim parametrom 6 puta
            cout << s7 << endl;
        }
    }

return 0;
}
