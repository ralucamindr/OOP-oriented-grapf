#include <iostream>
#include <fstream>
using namespace std;
ifstream f("date.in");
class nod
{
    int info;
    nod * next;
    int numar;
public:
    void setinf(int x);
    int getinf();
    void setnext(nod *a);
    nod * getnext();
};
void nod::setinf(int x)
{
    info=x;
}
int nod::getinf()
{
    return info;
}
void nod::setnext(nod *a)
{
    next = a;
}
nod * nod::getnext()
{
    return next;
}

class lista
{
    nod *prim,*ultim;
public:
    lista();
    void add(int x);
    nod * get_prim();
    void set_prim(nod *a);

};

lista::lista()
{
    cout<<"lista initializata"<<endl;
    prim=ultim=NULL;

}
void lista::set_prim(nod *a)
{
    prim=a;
}
nod * lista::get_prim()
{
        return prim;
}

void lista::add(int x)
{
    if(prim==NULL)
    {
        prim = new nod;
        prim->setnext(NULL);

        ultim=prim;
        prim->setinf(x);

    }

    else
    {
        nod*q;
        q=new nod;
        q->setinf(x);
        ultim->setnext(q);

        q->setnext(NULL);
        ultim = q;
    }
}

class Iterator
{
    nod *p;
public:
    Iterator(lista  l);
    void operator ++();
    int operator ()();
    bool operator !();
};
Iterator ::Iterator(lista l)
{

     p=l.get_prim();

}
void Iterator::operator++()
{
    p=p->getnext();
}
int Iterator::operator()()
{
    return p->getinf();
}
bool Iterator::operator!()
{

    return p!=NULL;
}


class stiva
{
    nod *top;
public:
    stiva();
    void push(int x);
    void pop();
    int peek();
    bool empty();
};

stiva::stiva()
{
    top=NULL;
    cout<<"stiva init"<<endl;
}
void stiva::push(int x)
{
    if(top==NULL)
    {
        top=new nod;
        top->setinf(x);
        top->setnext(NULL);
    }
    else
    {
        nod * p=new nod;
        p->setinf(x);
        p->setnext(top);
        top=p;
    }
}
void stiva::pop()
{
    nod *q;
    q=top;
    top=top->getnext();
    delete q;

}
bool stiva::empty()
{
    return(top==NULL);
}
int stiva::peek()
{
    return top->getinf();
}

class coada
{
    nod *prim,*ultim;
public:
    coada();
    void push(int x);
    void pop();
    int frontt();
    bool empty();

};
coada::coada()
{
    prim=NULL;
    ultim=prim;
    cout<<"coada init ";

}
void coada::push(int x)
{
    if(prim==NULL)
    {
        prim = new nod;
        prim->setnext(NULL);
        ultim=prim;
        prim->setinf(x);
    }

    else
    {
        nod*q;
        q=new nod;
        q->setinf(x);
        ultim->setnext(q);

        q->setnext(NULL);
        ultim = q;
    }
}

void coada::pop()
{

    nod *q;
    q=prim;
    prim=prim->getnext();
    delete q;
}

int coada::frontt()
{
    return prim->getinf();
}

bool coada::empty()
{
    return(prim==NULL);
}

class graf
{
    int n,m;
    lista *grf[100],*grft[100];
    int vizite[100];
    int viz[100];
    int vizite2[100];
    int postordine[100];
    int nr;
    int drum[100][100];
public:
    graf();//constructor
    graf(const graf & G );//constructor de copiere
    void citire();
    void set_viz();
   int get_vizite(int i);
    int get_vizite2(int i);
    void dfs(int vertex);
    void bfs(int vertex);
    int get_nr_noduri();
    void set_postordine(int i,int x);
    int get_postordine(int i);
    void dfst(int vertex);
    void determinare_comp_tare_conexe();
    void df_rec(int vertex);
    void dft(int vertex);
    void determinare_matrice_drumuri();
    void initilizari();
    ~graf();

};
graf::~graf()
{
    cout<<"GFDG";
    delete grf;
    delete grft;
}
graf::graf()
{
    f>>n;
    int i;
    for(i=0; i<n; i++)
        {grf[i]= new lista;
         grft[i]=new lista;
        }


    cout<<"graf initializat"<<endl;
}
void graf::citire()
{
    f>>m;
    int x,y;
    while(m)
    {
        f>>x>>y;
        m--;
        x--;
        y--;
        grf[x]->add(y);
        grft[y]->add(x);

     }
    cout<<"adaugare muchii cu succes"<<endl;
}
void graf::initilizari()
{
    nr=0;
    int i;
    for(i=0; i<n; i++)

    {
        vizite[i]= 0;
        vizite2[i]=0;
        viz[i]=0;
    }
}
graf::graf( const graf &G)
{
     cout<<"Constructor de copiere"<<endl;
    int i,j;
    n=G.n;
    for(i=0;i<n;i++)
    {
        grf[i]=new lista;
        grft[i]=new lista;
    }
    nr=0;
    for(i=0; i<n; i++)

    {
        vizite[i]=0;
        vizite2[i]=0;
        viz[i]=0;
        postordine[i]=0;

    }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        drum[i][j]=0;

    for(i=0;i<n;i++)
    {
        Iterator it(*G.grf[i]);
        while(!it)
        {
        grf[i]->add(it());
        ++it;
        }
        Iterator k(*G.grf[i]);
        while(!k)
        {
            grft[i]->add(k());
            ++k;
        }
    }

}
void graf::set_postordine(int i,int x)
{
    postordine[i]=x;
}
int graf::get_postordine(int i)
{
    return postordine[i];
}
int graf::get_nr_noduri()
{
    return n;
}
void graf::set_viz()
{
    for(int i=0;i<n;i++) viz[i]=0;
}
int graf::get_vizite(int i)
{
    return vizite[i];
}

int graf::get_vizite2(int i)
{
    return vizite2[i];
}

void graf::dfs(int vertex)
{
    stiva s;
    cout<<" Parcurgerea in adancime din varful "<<vertex+1 <<endl;
    cout<<vertex+1<<" ";
    bool found;
    int element;
    s.push(vertex);
    vizite[vertex]=1;

    while(!s.empty())
    {
        element=s.peek();
        found=false;
        Iterator i(*grf[element]);
        while(!i&&!found)
        {

            if(!vizite[i()])
               found=true;
               if(found==false) ++i;
        }

      if(found)
        {

            s.push(i());
            vizite[i()]=1;
            cout<<s.peek()+1<<" ";
        }
        else s.pop();
        }


    cout<<endl;


}
void graf::bfs(int vertex)
{


    int element;
    coada q;
    cout<<"Parcurgere bfs din varful "<<vertex+1 <<endl;
    cout<<vertex+1<<" ";
    q.push(vertex);
    vizite2[vertex]=1;
    while(!q.empty())
    {
        element=q.frontt();
        Iterator i(*grf[element]);


        while(!i)
        {
            if(!vizite2[i()])
            {
                q.push(i());
                vizite2[i()]=1;
                cout<<i()+1<<" ";
            }
            ++i;
        }
        q.pop();
    }cout<<endl;
}
void graf::df_rec(int vertex)
{
    Iterator i(*grf[vertex]);
    viz[vertex]=1;
    while(!i)
        {if(!viz[i()])
        df_rec(i());
        ++i;}
    postordine[nr++]=vertex;
}
void graf::dft(int vertex)
{
    Iterator i(*grft[vertex]);
    viz[vertex]=0;
    cout<<vertex+1<<" ";
    while(!i)
        {if(viz[i()])
        dft(i());
        ++i;
        }
}
void graf::determinare_comp_tare_conexe()
{
int i,nrc=0;
for(i=0;i<n;i++)
    if(!viz[i]) df_rec(i);
for(i=n-1;i>=0;i--)
    if(viz[postordine[i]])
{
    cout<<"Componenta tare-conexa "<<++nrc<<" :";
    dft(postordine[i]);
    cout<<endl;
}

}
void graf::determinare_matrice_drumuri()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        df_rec(i);
        for(j=0;j<n;j++)
            if(viz[j]==1)
            drum[i][j]=1;
        set_viz();

    }
    cout<<"Matricea drumurilor:"<<endl;
    for(i=0;i<n;i++)
    {for(j=0;j<n;j++)
    cout<<drum[i][j]<<" ";
    cout<<endl;
    }


}
int main()
{   graf *Graph;
    Graph=new graf;
    int i;
    int n;
    Graph->citire();
    Graph->initilizari();
    n=Graph->get_nr_noduri();
   for(i=0; i<n; i++)
        if(!Graph->get_vizite(i))
            Graph->dfs(i);
    for(i=0; i<n; i++)
        if(!Graph->get_vizite2(i))
            Graph->bfs(i);
    Graph->determinare_comp_tare_conexe();
    Graph->determinare_matrice_drumuri();
   // graf t(*Graph);// Apelare constructor copiere

}
