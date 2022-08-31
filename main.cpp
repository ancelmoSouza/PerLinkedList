#include <iostream>
#include <vector>

using namespace std;

template <typename T>struct VersionTuple
{
    T v; //Valor associado á um campo na versão i
    int i;

    VersionTuple<T>(T value, int version)
    {
        this->v = value;
        this->i = version;
    }
    VersionTuple<T>() = default;
};

struct FatNode
{
    vector<VersionTuple<int>> data;
    vector<VersionTuple<FatNode *>> next;

};


class PerLinkedList
{
public:
    FatNode * head;
    int currentVersion;

    PerLinkedList(){
        this->currentVersion = -1;
    }

    void insertPer(int value);
    bool deletePer(int value);
    FatNode * findCurrentVer(int value);
    FatNode * findInVersion(int value, int v);

};

void PerLinkedList::insertPer(int value)
{
    VersionTuple<int> aux = VersionTuple(value, this->currentVersion + 1);
    FatNode * nodeAux = nullptr;

    if(this->currentVersion == -1)
    {
        FatNode * novo = new FatNode;
        novo->data.push_back(aux);
        novo->next.push_back(VersionTuple(nodeAux, this->currentVersion + 1));
        this->currentVersion += 1;
        this->head = novo;
    }else
    {
        FatNode * novo = new FatNode;
        nodeAux = head;
        novo->data.push_back(aux);
        novo->next.push_back(VersionTuple(nodeAux, this->currentVersion + 1));
        head = novo;
        this->currentVersion += 1;
    }

}

FatNode * PerLinkedList::findCurrentVer(int value){
    bool inList = false;
    FatNode * nodeAux = nullptr;

    if(this->currentVersion == -1)
        return nullptr;
    else if(this->currentVersion >= 0)
    {
        nodeAux = head;
        while(!inList){
            if(nodeAux->data[nodeAux->data.size() - 1].v == value)
            {
                inList = true;
            }
            else{
                nodeAux = nodeAux->next[nodeAux->next.size() -1].v;
            }
        }
    }

    return nodeAux;
}

FatNode * PerLinkedList::findInVersion(int value, int v){
    bool inList = false;
    FatNode * nodeAux = nullptr;

    if(this->currentVersion == -1)
        return nullptr;
    else if(this->currentVersion >= 0)
    {
        nodeAux = head;

        while(!inList){
            int version = -1;
            for(vector<VersionTuple<int>>::iterator it = nodeAux->data.begin();
                it < nodeAux->data.end(); it++){

                if((*it).i <= v){
                    version += 1;
                }else if (version == -1){
                    version++;
                    break;
                }else{
                    break;
                }
            }

            if(nodeAux->data[version].v == value && nodeAux->data[version].i <= v)
            {
                inList = true;
            }
            else{
                nodeAux = nodeAux->next[version].v;
            }
            //Último nó da lista na versão buscada
            if(nodeAux == nullptr)
            {
                inList = true; //Sair do laço, valor não existe na  lista
                               // Na versão buscada-
            }
        }
    }

    return nodeAux;
}

bool PerLinkedList::deletePer(int value){
    FatNode * aux = this->head;
    bool del = false;

    if(this->currentVersion == -1)
        return false;

    while(!del){
        if(aux->data[aux->data.size() -1].v == value){
            FatNode * next = aux->next[aux->next.size() -1].v;
            VersionTuple<int> dataFNode =  VersionTuple(next->data[next->data.size() -1].v, this->currentVersion + 1);
            VersionTuple<FatNode *> nextFNode = VersionTuple(next->next[next->data.size() -1].v, this->currentVersion + 1);
            aux->data.push_back(dataFNode);
            aux->next.push_back(nextFNode);
            this->currentVersion++;
            del = true;
            this->head = aux;
        }else
        {
            aux = aux->next[aux->next.size() -1].v;
        }
    }

    return del;


}

int main()
{

   PerLinkedList l;
   l.insertPer(1);
   l.insertPer(2);
   bool rem = l.deletePer(2);

   cout << l.head->data[l.head->data.size() -1].v << endl;
   cout << l.head->data[l.head->data.size() -1].i << endl;

}
























