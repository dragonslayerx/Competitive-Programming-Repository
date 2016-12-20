/**
 * Heavy Light decomposition:  Perform point updates and aggregate queries over path between two nodes in a tree in case edges are weighted
 * Complexity: O(lg^2(N)) 
 * Source: https://github.com/dragonslayerx 
 */

#include<iostream>
#include<iostream>
#include<cmath>
#include<map>
#include<limits>
#include<vector>
#include<list>
#include<queue>
using namespace std;


const long long INF = 1000000000000000005LL;

long long mul(long long a, long long b) {
    pair<long long, long long> s, t, result;
    t.first = a / 1000000000;
    t.second = a % 1000000000;

    s.first = b / 1000000000;
    s.second = b % 1000000000;

    long long r1, r2, r3, r4;

    r1 = t.first * s.first;
    r2 = t.first * s.second;
    r3 = t.second * s.first;
    r4 = t.second * s.second;

    if (r1 && (r2 || r3 || r4)) return INF;
    else if ((r2 + r3) > 1000000000) return INF;
    else if ((r2 + r3)*1000000000 + r4 > INF) return INF;
    else return (r2 + r3)*1000000000 + r4;
}

class HLD
{
    public:
        typedef vector<list<int> > tree;
    private:
        tree &T;

        void doHLD(int cur=0)
        {
            chainNumber[cur]=chainSize.size()-1;
            chainPosition[cur]=chainSize.back();
            chainSize.back()++;

            int maxTreeSize=numeric_limits<int>::min();
            int maxTreeSizeNode=-1;

            for(list<int>::iterator i=T[cur].begin();i!=T[cur].end();i++)
                if(nodeLevel[*i]>nodeLevel[cur])
                    if(maxTreeSize<treeSize[*i])
                    {
                        maxTreeSize=treeSize[*i];
                        maxTreeSizeNode=*i;
                    }

            if(maxTreeSizeNode==-1)
                return;
            doHLD(maxTreeSizeNode);

            for(list<int>::iterator i=T[cur].begin();i!=T[cur].end();i++)
                if(nodeLevel[*i]>nodeLevel[cur])
                    if(*i!=maxTreeSizeNode)
                    {
                        chainSize.push_back(0);
                        chainHead.push_back(cur);
                        doHLD(*i);
                    }
        }

        void calculateTreeSize(int node)
        {
            treeSize[node]=1;
            for(list<int>::iterator i=T[node].begin();i!=T[node].end();i++)
            {
                if(nodeLevel[*i]>nodeLevel[node])
                {
                    calculateTreeSize(*i);
                    treeSize[node]+=treeSize[*i];
                }
            }
        }

    public:
        vector<int> chainHead;
        vector<int> chainNumber;
        vector<int> chainPosition;
        vector<int> chainSize;
        vector<int> nodeLevel;
        vector<int> treeSize;
        HLD(tree &t,int start=0):T(t)
        {
            chainHead.reserve(T.size());
            chainNumber.resize(T.size());
            chainPosition.resize(T.size());
            chainSize.reserve(T.size());
            nodeLevel.resize(T.size(),-1);
            treeSize.resize(T.size());


            chainSize.push_back(0);
            chainHead.push_back(-1);
            // bfs for finding the level of the node

            queue<int> Q;
            nodeLevel[start]=0;
            Q.push(start);
            while(!Q.empty())
            {
                int current=Q.front();
                Q.pop();
                for(list<int>::iterator i=T[current].begin();i!=T[current].end();i++)
                {
                    if(nodeLevel[*i]==-1)
                    {
                        nodeLevel[*i]=nodeLevel[current]+1;
                        Q.push(*i);
                    }
                }
            }

            // dfs
            calculateTreeSize(start);
            doHLD(start);
        }
        size_t chainCount() const
        {
            return chainSize.size();
        }
};

template<class T,class MF,class UN> class segmentTree
{
    public:
        typedef T value_type;

    private:
        vector<value_type> tree;
        MF mergeFunction;
        UN updateNode;
        size_t sz;

        bool inRange(size_t queryLeft,size_t queryRight,size_t nodeLeft,size_t nodeRight) const
        {
            if(nodeLeft > nodeRight || nodeLeft > queryRight || nodeRight < queryLeft)
                return false;
            return true;
        }

        size_t leftChild(size_t node)
        {
            return (node<<1)+1;
        }
        size_t rightChild(size_t node)
        {
            return (node<<1)+2;
        }

        void buildTree(const vector<value_type> &A,size_t low,size_t high, size_t node)
        {

            if(low==high)
                tree[node]=A[low];
            else if(low>high)
                return;
            else
            {
                buildTree(A,low,(low+high)/2,leftChild(node));
                buildTree(A,(low+high)/2+1,high,rightChild(node));
                tree[node]=mergeFunction(tree[leftChild(node)],tree[rightChild(node)]);
            }
        }

        value_type query(size_t queryLeft,size_t queryRight,size_t nodeLeft,size_t nodeRight,size_t node)
        {
            if(nodeLeft>=queryLeft&&nodeRight<=queryRight)
                return tree[node];
            else
            {
                bool leftInRange=inRange(queryLeft,queryRight,nodeLeft,(nodeLeft+nodeRight)/2);
                bool rightInRange=inRange(queryLeft,queryRight,(nodeLeft+nodeRight)/2+1,nodeRight);

                if(leftInRange&&!rightInRange)
                    return query(queryLeft,queryRight,nodeLeft,(nodeLeft+nodeRight)/2,leftChild(node));

                else if(!leftInRange&&rightInRange)
                    return query(queryLeft,queryRight,(nodeLeft+nodeRight)/2+1,nodeRight,rightChild(node));

                else
                    return mergeFunction(query(queryLeft,queryRight,nodeLeft,(nodeLeft+nodeRight)/2,leftChild(node)),query(queryLeft,queryRight,(nodeLeft+nodeRight)/2+1,nodeRight,rightChild(node)));
            }
        }

        void update(size_t queryLeft,size_t queryRight,size_t nodeLeft,size_t nodeRight,size_t node,value_type value)
        {
            if(!inRange(queryLeft,queryRight,nodeLeft,nodeRight))
                return;

            if(nodeLeft==nodeRight)
                tree[node]=updateNode(tree[node],value);
            else
            {
                update(queryLeft,queryRight,nodeLeft,(nodeLeft+nodeRight)/2,leftChild(node),value);
                update(queryLeft,queryRight,(nodeLeft+nodeRight)/2+1,nodeRight,rightChild(node),value);

                tree[node]=mergeFunction(tree[leftChild(node)],tree[rightChild(node)]);
            }
        }

    public:
        segmentTree()
        {
            sz=0;
        }

        segmentTree(size_t size,value_type initial=value_type())
        {
            assign(size,initial);
        }

        segmentTree(const vector<value_type> &A)
        {
            clear();
            assign(A);
        }

        void assign(size_t size,value_type initial=value_type())
        {
            clear();
            sz=size;
            tree.resize(4*size,initial);
        }

        void assign(const vector<value_type> &A) // assumes vector to be 0 indexed
        {
            assign(A.size());
            buildTree(A,0,A.size()-1,0);
        }

        void clear()
        {
            sz=0;
            tree.clear();
        }

        void update(size_t pos,const value_type &value)
        {
            update(pos,pos,0,sz-1,0,value);
        }

        value_type query(size_t low,size_t high)
        {
            return query(low,high,0,sz-1,0);
        }
        ~segmentTree()
        {
            clear();
        }
};
struct updateNode
{
    long long operator()(int node, long long newValue)
    {
        return newValue;
    }
};

struct mergeNode
{
    long long operator()(long long left, long long right)
    {
        return mul(left, right);
    }
};

struct edge
{
    int a,b;
    long long cost;
};

template<class T> class rmq
{
    private:
        vector<vector<T> > RMQ;
    public:
        rmq()
        {
        }
        rmq(vector<T> &arr)
        {
    //------------------------------------------------
            int n=arr.size();
            RMQ.resize(n);
            int len=5+ceil(log(arr.size()));
            for(int i=0;i<n;i++)
            {
                RMQ[i].resize(len);
            }


    //----------------------------------------------
            for(int i=0;i<n;i++)
            RMQ[i][0]=arr[i];

            for(int j=1,p=2;p<=n;j++,p*=2)
            {
                for(int i=0;i+p<=n;i++)
                RMQ[i][j]=min(RMQ[i][j-1],RMQ[i+p/2][j-1]);
            }
        }

        T query(int i,int j)
        {

            int gap=j-i+1;
            int p=-1;
            int po=1;

            while(gap) // calculates 2^(floor(logk)) and floor(logk)
            {
                gap=gap/2;
                p++;
                po<<=1;
            }
            po/=2;

            return min(RMQ[i][p],RMQ[j-po+1][p]);
        }
};

class LCA
{
    public:
        typedef vector<list<int> > tree; // change this according to your problem.
    private:
        tree &T;

        vector<bool> istraversed;
        vector<int> level;
        vector<int> position;
        vector<pair<int,int> > rmqArray;
        rmq<pair<int,int> >  RMQ;

        void dfs(int source)
        {
            if(!istraversed[source])
            {
                istraversed[source]=true;
                position[source]=rmqArray.size();
                rmqArray.push_back(make_pair(level[source],source));
                for(tree::value_type::iterator i=T[source].begin();i!=T[source].end();i++)
                {
                    if(!istraversed[*i])          // vertex point here
                    {
                        dfs(*i);
                        rmqArray.push_back(make_pair(level[source],source));
                    }
                }
            }
        }

        void bfs(int start)
        {
            queue<int> Q;
            level[start]=0;
            Q.push(start);

            while(!Q.empty())
            {
                int current=Q.front();
                Q.pop();
                for(tree::value_type::iterator i=T[current].begin();i!=T[current].end();i++)
                {
                    if(level[*i]==-1)
                    {
                        level[*i]=level[current]+1;
                        Q.push(*i);
                    }
                }
            }
        }


    public:
        LCA(tree &t,int start=0):T(t)
        {
            level.resize(t.size(),-1);
            bfs(start);

            position.resize(t.size());
            istraversed.resize(t.size());
            rmqArray.reserve(t.size());
            dfs(start);

            RMQ=rmq<pair<int,int> >(rmqArray);
        }

        int query(int nodeA,int nodeB)
        {
            return RMQ.query(min(position[nodeA],position[nodeB]),max(position[nodeA],position[nodeB])).second;
        }
};



int main(){
        //  freopen("testQTREE.txt","r",stdin);
        //  freopen("outQtree1.txt","w",stdout);

        ios_base::sync_with_stdio(false);

        int n, q;
        cin>>n >> q;

        vector<edge> E(n-1);
        HLD::tree T(n);

        for(int i=0;i<n-1;i++)
        {

            cin>>E[i].a>>E[i].b>>E[i].cost;
            E[i].a--;
            E[i].b--;
            T[E[i].a].push_back(E[i].b);
            T[E[i].b].push_back(E[i].a);
        }

        HLD hld(T);

        vector<segmentTree<long long,mergeNode,updateNode> > ST(hld.chainCount())   ;

        for(int i=0;i<hld.chainCount();i++)
            ST[i].assign(hld.chainSize[i]);

        for(int i=0;i<E.size();i++)
        {
            int target=(hld.nodeLevel[E[i].a]>hld.nodeLevel[E[i].b]?E[i].a:E[i].b);
            ST[hld.chainNumber[target]].update(hld.chainPosition[target],E[i].cost);
        }

        LCA lca(T,0);

        while(q--)
        {
            int choice;
            cin>>choice;
            if(choice==1)
            {
                int a,b;
                long long k;
                cin>>a>>b>>k;
                if(a==b)
                {
                    cout<<k<<endl;
                    continue;
                }
                a--;
                b--;

                int l=lca.query(a,b);

                long long ans=1;
                while(1)
                {
                    if(hld.chainNumber[l]==hld.chainNumber[a])
                    {
                        if(l==a)
                            break;
                        ans=mul(ans, ST[hld.chainNumber[a]].query(hld.chainPosition[l]+1,hld.chainPosition[a]));
                        break;
                    }
                    ans=mul(ans, ST[hld.chainNumber[a]].query(0,hld.chainPosition[a]));
                    a=hld.chainHead[hld.chainNumber[a]];
                }
                while(1)
                {
                    if(hld.chainNumber[l]==hld.chainNumber[b])
                    {
                        if(l==b)
                            break;
                        ans=mul(ans, ST[hld.chainNumber[b]].query(hld.chainPosition[l]+1,hld.chainPosition[b]));
                        break;
                    }
                    ans=mul(ans, ST[hld.chainNumber[b]].query(0,hld.chainPosition[b]));
                    b=hld.chainHead[hld.chainNumber[b]];
                }
                cout<<k/ans<<endl;
            }else if(choice==2){
                int i;
                long long value;
                cin>>i>>value;
                i--;
                int target=(hld.nodeLevel[E[i].a]>hld.nodeLevel[E[i].b]?E[i].a:E[i].b);
                ST[hld.chainNumber[target]].update(hld.chainPosition[target],value);
            }
        }
}