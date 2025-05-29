#include <iostream>
#include <vector>

using namespace std;

#define MAXBELT 100000
#define MAXGIFT 100000

typedef struct Gift {
    Gift* next = nullptr;
    Gift* prev = nullptr;
}; 

vector<Gift> gift, head, tail;
vector<int> beltSize;



void initBelt()
{
    int n, m;
    cin >> n >> m;

    gift.resize(m);
    head.resize(n);
    tail.resize(n);
    beltSize.resize(n,0);

    for(int i=0; i< n; i++)
    {
        head[i].next = &tail[i];
        tail[i].prev = &head[i];
    }

    for(int i=0; i<m; i++)
    {
        int B_NUM;
        cin >> B_NUM;
        tail[B_NUM].prev->next = &gift[i];
        gift[i].next = &tail[B_NUM];
        gift[i].prev = tail[B_NUM].prev;
        tail[B_NUM].prev = &gift[i];
        beltSize[B_NUM]++;
    }
}


void moveAll()
{
    int m_src, m_dst;
    cin >> m_src >> m_dst;

    head[m_src].next->prev = &head[m_dst]; // 2->dst head
    head[m_dst].next->prev = tail[m_src].prev; // 4<-dst 첫 gift
    head[m_dst].next = head[m_src].next; // dst head -> 2  

    tail[m_src].prev->next = head[m_dst].next; // 4 -> dst 첫 gift


    head[m_src].next = &tail[m_src];
    tail[m_src].prev = &head[m_src];

    // size 갱신
    beltSize[m_dst] += beltSize[m_src];
    beltSize[m_src] = 0;

    cout<< beltSize[m_dst] << "\n";
}

void changeFront()
{
    int m_src, m_dst;
    cin >> m_src >> m_dst;
    if(head[m_src].next == &tail[m_src])
    {
        head[m_src].next = head[m_dst].next;
        head[m_dst].next->prev = &head[m_src];
        
        head[m_dst].next->next->prev = &head[m_dst];
        head[m_dst].next = head[m_dst].next->next;

        head[m_src].next->next = &tail[m_src];
        tail[m_src].prev = head[m_src].next;

    }

}

int main()
{
    int q;
    cin >> q;

    while(q--)
    {
        int func;
        cin >> func;

        switch (func)
        {
            case 100:
                initBelt();
            break;

            case 200:
                moveAll();
            break;

            case 300:
                changeFront();
            break;
            case 400:

            break;

            case 500:

            break;

            case 600:

            break;
        }
    }

    return 0;
}