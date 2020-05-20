#include <iostream>
#include<list>
#include<string>
#include<typeinfo>
#include<exception>
#include<fstream>

using namespace std;

class Exceptie: public exception
{
private:
    const char* exceptie;
public:
    Exceptie(const char* copie_exceptie) noexcept
    {
        this->exceptie=copie_exceptie;
    }
    Exceptie(const Exceptie&) noexcept=default;
    Exceptie& operator=(const Exceptie&) noexcept=default;
    virtual ~Exceptie() noexcept=default;
    virtual const char* what() const noexcept
    {
        return exceptie;
    }
};

class Animal
{
 protected:
    string denumire;
public:
    Animal(string denumire=""):denumire(denumire){};
    virtual void afisare() const =0;
    ~Animal() {denumire="";};
};

class Vertebrate : public Animal
{
public:
    Vertebrate(string denumire=""):Animal(denumire) {};
    void afisare () const
    {
       cout<<"Numele vertebratei este: "<<denumire<<endl;
    };
    friend istream &operator>>(istream &in, Vertebrate &v);
    friend ostream &operator<<(ostream &out, const Vertebrate &v);
    ~Vertebrate() {denumire="";};
};

istream &operator>>(istream &in, Vertebrate &v)
{
    cout<<"Introdu denumirea vertebratei: ";
    in>>v.denumire;
    return in;
}

ostream &operator<<(ostream &out,const Vertebrate &v)
{
   v.afisare();
   return out;
}

class Nevertebrate : public Animal
{
 public:
    Nevertebrate(string denumire=""):Animal(denumire) {};
    void afisare() const
    {
       cout<<"Numele nevertebratei este: "<<denumire<<endl;
    };
     ~Nevertebrate() {denumire="";};
     void operator= (Nevertebrate &n)
    {
        denumire=n.denumire;
    }
    friend istream &operator>>(istream &in,Nevertebrate &n);
    friend ostream &operator<<(ostream &out,const Nevertebrate &n);

};

istream &operator>>(istream &in,Nevertebrate &n)
{
    cout<<"Introdu denumirea nevertebratei: ";
    in>>n.denumire;
    return in;
}

ostream &operator<<(ostream &out,const Nevertebrate &n)
{
   n.afisare();
   return out;
}

class Pesti: public Vertebrate
{
    int rapitor; //0-nu e rapitor ; 1-e rapitor
    double lungime;
public:
    Pesti(string denumire="",int rapitor=0,double lungime=0):Vertebrate(denumire),
    rapitor(rapitor),lungime(lungime){};
    void operator= (Pesti &p)
    {
        denumire=p.denumire;
        rapitor=p.rapitor;
        lungime=p.lungime;
    }
    Pesti(const Pesti&p)
    {
        denumire=p.denumire;
        rapitor=p.rapitor;
        lungime=p.lungime;
    }

    void afisare() const
    {
       cout<<"Numele pestelui este: "<<denumire<<endl;
       if(rapitor==0)
            cout<<"Pestele nu este rapitor\n";
       else cout<<"Pestele este rapitor\n";
       cout<<"Lungimea pestelui este de "<<lungime<<" metri\n";
    };
     ~Pesti(){denumire="";rapitor=0;lungime=0;};
    int este_rapitor() const
     {
            if(rapitor==1 && lungime>1)
                return 1;
            return 0;
     }
    friend istream &operator>>(istream &in, Pesti &pes);
    friend ostream &operator<<(ostream &out, const Pesti &pes);
};

istream &operator>>(istream &in, Pesti &pes)
{
    cout<<"Introdu denumirea pestelui: ";
    in>>pes.denumire;
    cout<<"Pestele este rapitor ? 0-nu este, 1-este ";
    in>>pes.rapitor;
    cout<<"Introdu lungimea pestelui: ";
    in>>pes.lungime;
    if(pes.lungime <0)
        throw(Exceptie("Lungimea trebuie sa fie >0"));
    return in;
}

ostream &operator<<(ostream &out,const Pesti &pes)
{
   pes.afisare();
   return out;
}

class Pasari: public Vertebrate
{
public:
    Pasari(string denumire=""):Vertebrate(denumire){};
    void afisare() const
    {
       cout<<"Numele pasarei este: "<<denumire<<endl;
    };
    void operator= (Pasari &p)
    {
        denumire=p.denumire;
    }
     ~Pasari() {denumire="";};
    friend istream &operator>>(istream &in, Pasari &pas);
    friend ostream &operator<<(ostream &out, const Pasari &pas);

};

istream &operator>>(istream &in, Pasari &pas)
{
    cout<<"Introdu denumirea pasarii: ";
    in>>pas.denumire;
    return in;
}

ostream &operator<<(ostream &out,const Pasari &pas)
{
   pas.afisare();
   return out;
}

class Mamifere : public Vertebrate
{
public:
    Mamifere(string denumire=""):Vertebrate(denumire){};
    void afisare() const
    {
       cout<<"Numele mamiferului este: "<<denumire<<endl;
    };
    void operator= (Mamifere &m)
    {
        denumire=m.denumire;
    }
     ~Mamifere(){denumire="";};
    friend istream &operator>>(istream &in, Mamifere &m);
    friend ostream &operator<<(ostream &out, const Mamifere &m);
};

istream &operator>>(istream &in, Mamifere &m)
{
    cout<<"Introdu denumirea mamiferului: ";
    in>>m.denumire;
    return in;
}

ostream &operator<<(ostream &out,const Mamifere &m)
{
   m.afisare();
   return out;
}

class Reptile : public Vertebrate
{
public:
    Reptile(string denumire=""):Vertebrate(denumire){};
    void afisare() const
    {
       cout<<"Numele reptilei este: "<<denumire<<endl;
    };
    void operator= (Reptile &r)
    {
        denumire=r.denumire;
    }
     ~Reptile(){denumire="";};
    friend istream &operator>>(istream &in, Reptile &r);
    friend ostream &operator<<(ostream &out, const Reptile &r);
};

istream &operator>>(istream &in, Reptile &r)
{
    cout<<"Introdu denumirea reptilei: ";
    in>>r.denumire;
    return in;
}

ostream &operator<<(ostream &out,const Reptile &r)
{
   r.afisare();
   return out;
}

template<typename T>
class AtlasZoologic
{
    static int nrAnimale;
    list<Animal*> animale;
public:
    AtlasZoologic() {};
    ~AtlasZoologic() {};
    int get_nrAnimale() const {return nrAnimale;};
    void operator+= (T &t)
    {
            animale.push_back(&t);
            nrAnimale++;
    };
    //friend istream &operator>>(istream &in, T &t);
    //friend ostream &operator<<(ostream &out, const T &t);
    void afisare() const
    {
        cout<<"Atlasul de "<<get_nrAnimale()<<" "<<typeid(T).name()<<" contine urmatoarele animale:\n";
        for( auto i: animale)
          (*i).afisare();

    }
} ;

//template<typename T>
//AtlasZoologic<T> ostream &operator<<(ostream &out, const T &t)
//{
//    for( auto i: animale)
//        (*i).afisare();
//    return out;
//}

template<typename T>
int AtlasZoologic<T>::nrAnimale=0;

template<>
class AtlasZoologic<Pesti>
{
    static int nrAnimale;
    list<Pesti*> animale;
public:
    AtlasZoologic() {};
    ~AtlasZoologic() {};
    int get_nrAnimale() const {return nrAnimale;};
    void operator+= (Pesti &t)
    {
            animale.push_back(&t);
            nrAnimale++;
    };
    //friend istream &operator>>(istream &in, T &t);
    //friend ostream &operator<<(ostream &out, const T &t);
    int get_PredMari()
    {
        int nr=0;
        for(auto i : animale)
            if((*i).este_rapitor()==1)
                nr++;
        return nr;

    }
    void afisare() const
    {
        cout<<"Atlasul de "<<get_nrAnimale()<<" "<<typeid(Pesti).name()<<" contine urmatoarele animale:\n";
        for( auto i: animale )
          (*i).afisare();
    }

} ;

int AtlasZoologic<Pesti>::nrAnimale=0;

void menu()
{
    cout<<"1. Cititi un animal\n";
    cout<<"2. Afisati nr de animale\n";
    cout<<"3. Afisati animalele\n";
    cout<<"4. Afisati cati pesti rapitori cu lungimea de >1m sunt\n";
    cout<<"5. EXIT\n";
}

int main()
{
   /* Nevertebrate *n=new Nevertebrate;
    cin>>*n;
    cout<<*n;*/

    /*Mamifere *m=new Mamifere;
    cin>>*m;
    cout<<*m;
    m->afisare();

    Pesti *p=new Pesti;
    cin>>*p;
    cout<<*p;
    p->afisare();*/

//    AtlasZoologic<Mamifere> mamifere;
//    Mamifere *m=new Mamifere;
//    cin>>*m;
//     Mamifere *m1=new Mamifere;
//    cin>>*m1;
//    mamifere += *m;
//    mamifere += *m1;
//    mamifere.afisare();

    AtlasZoologic<Nevertebrate> nevertebrate;
    AtlasZoologic<Pesti> pesti;
    AtlasZoologic<Pasari> pasari;
    AtlasZoologic<Mamifere> mamifere ;
    AtlasZoologic<Reptile> reptile;

//    Pesti *p1=new Pesti;
//    cin>>*p1;
//    Pesti *p2=new Pesti;
//    p2=p1;
//    Pesti *p3(p2);
//    cout<<*p3;
//    pesti += *p1;
//    pesti += *p2;
//    pesti.afisare();

    ifstream f("animale.txt");

    do
    {
       loop:
        menu();
        cout<<"Optiunea ta este: ";
        int op;
        cin>>op;
        if(op==1)
        {
              cout<<"Introduceti tipul de animal pe care vreti sa il introduceti: : 0-peste, 1-pasare, 2-mamifer, 3-reptila, 4-nevertebrata\n";
              int tip;
              cin>>tip;
             // if(!(f>>tip))
              //{throw(Exceptie("Nu mai ai ce sa citesti")); cin>>op;}

              if(tip==0)
              {
                    Pesti *p=new Pesti;
                    eticheta:
                    try
                    {
                        cin>>*p;
                        //f>>*p;
                    }
                    catch(Exceptie &exception)
                            {
                                cout << "A aparut o exceptie : (" << exception.what() << ")\n"<<"Introduceti alt peste\n";
                                goto eticheta;
                            }
                    pesti += *p;
              }
              else if(tip==1)
              {
                    Pasari *pas=new Pasari;
                    cin>>*pas;
                    //f>>>*pas;
                    pasari += *pas;
              }
              else if(tip==2)
              {
                    Mamifere *m=new Mamifere;
                    cin>>*m;
                    //f>>*m;
                    mamifere += *m;
              }
              else if(tip==3)
              {
                    Reptile *r=new Reptile;
                    cin>>*r;
                    //f>>*r;
                    reptile += *r;
              }
              else if(tip==4)
              {
                    Nevertebrate *n=new Nevertebrate;
                    cin>>*n;
                    //f>>*n;
                    nevertebrate += *n;
              }
              else {cout<<"Ati introdus un tip incorent\nIncercati din nou\n\n"; cin>>tip; }
        }
        else if(op==2)
        {
            int nr=0;
                    nr+=nevertebrate.get_nrAnimale();
                    cout<<"Atlasul de "<<typeid(Nevertebrate).name()<<" contine "<<nevertebrate.get_nrAnimale()<<"nevertebrate\n";

                    nr+=pasari.get_nrAnimale();
                    cout<<"Atlasul de "<<typeid(Pasari).name()<<" contine "<<pasari.get_nrAnimale()<<"pasari\n";

                    nr+=pesti.get_nrAnimale();
                    cout<<"Atlasul de "<<typeid(pesti).name()<<" contine "<<pesti.get_nrAnimale()<<"pesti\n";

                    nr+=mamifere.get_nrAnimale();
                    cout<<"Atlasul de "<<typeid(Mamifere).name()<<" contine "<<mamifere.get_nrAnimale()<<"mamifere\n";

                    nr+=reptile.get_nrAnimale();
                    cout<<"Atlasul de "<<typeid(Reptile).name()<<" contine "<<reptile.get_nrAnimale()<<"reptile\n";

                    cout<<"Toate atlasele contin "<<nr<<" animale\n\n";
        }
        else if(op==3)
        {
            nevertebrate.afisare();
            pesti.afisare();
            pasari.afisare();
            mamifere.afisare();
            reptile.afisare();
        }
        else if(op==4)
        {
            cout<<"Sunt "<<pesti.get_PredMari()<<" pesti rapitori cu lungime >1m\n\n";
        }
        else {cout<<"Ati introdus o optiune invalida"; break;}

    }

    while(true);
    return 0;
}
