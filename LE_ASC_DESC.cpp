// Hacer functores para ordenar una lista enlazada de forma ASC ó DESC

#include <iostream>

using namespace std;

template <class P>
struct ASC
{
    P operator()(P a, P b)
    {
        return a < b;
    }
};

template <class P>
struct DESC
{
    P operator()(P a, P b)
    {
        return a > b;
    }
};

template <class T>
struct nodo
{
    T valor;
    nodo<T>* next;
    nodo(T v, nodo<T>* n = NULL)
    {
        valor = v;
        next = n;
    }
};

template <class T, class O>
class LE
{
public:
    nodo<T>* head = NULL;
    bool find(T valor, nodo<T>*& pos);
    void add(T valor);
    void del(T valor);
    void print();
    ~LE();
};

template <class T, class O>
bool LE<T, O>::find(T valor, nodo<T>*& pos)
{
    O op;
    pos = NULL;
    nodo<T>* p = head;
    for (; p && op(p->valor, valor); pos = p, p = p->next);
    if (p && p->valor == valor)
        return true;
    else
        return false;
}

template <class T, class O>
void LE<T, O>::add(T valor)
{
    nodo<T>* pos;
    if (!find(valor, pos))
        if (!pos)
            head = new nodo<T>(valor, head);
        else
            pos->next = new nodo<T>(valor, pos->next);
}

template <class T, class O>
void LE<T, O>::del(T valor)
{
    nodo<T>* pos_ant, * pos_del;
    if (find(valor, pos_ant))
    {
        if (pos_ant)
        {
            pos_del = pos_ant->next;
            pos_ant->next = pos_del->next;
            delete pos_del;
        }
        else
        {
            pos_del = head;
            head = pos_del->next;
            delete pos_del;
        }
    }
}

template <class T, class O>
void LE<T, O>::print()
{
    cout << "head->";
    for (nodo<T>* p = head; p; p = p->next)
        cout << p->valor << "->";
    cout << "NULL\n";
}

template <class T, class O>
LE<T, O>::~LE()
{
    nodo<T>* tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main()
{
    LE<int, ASC<int>> Lista;

    cout << "Lista ASC\n";
    Lista.add(3);
    Lista.add(4);
    Lista.add(2);
    Lista.add(5);
    Lista.add(1);
    Lista.print();

    Lista.del(4);
    Lista.print();
}
