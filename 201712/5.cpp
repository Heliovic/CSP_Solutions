#include <iostream>
#include <vector>


using namespace std;

class Edge
{
public:
    Edge(int f,int v,int c){From=f;VerAdj=v;cost=c;link=NULL;}
    int From;
    int VerAdj;
    int cost;
    Edge* link;
};

class Vertex
{
public:
    Vertex(int vn){VerName=vn;adjacent=NULL;}
    int VerName;
    int v;
    int f;
    Edge* adjacent;

};

void reset(bool* visited,int n)
{
    for(int i=0;i<=n;i++)
    {
        visited[i]=false;
    }
}

void DFS(bool* visited,Vertex** Head,int v,int n,vector<Edge*> path,vector< vector<Edge*> >* paths)
{
    visited[v]=true;
    Edge* p=Head[v]->adjacent;

    if(p==NULL) //û���ӽ�㣬˵��������Ҷ�ӽ�㣬�򱣴�path
    {
        paths->push_back(path);
        return;
    }

    while(p!=NULL)
    {
        if(!visited[p->VerAdj])
        {
            vector<Edge*> newPath=vector<Edge*>(path);
            newPath.push_back(p);  //����·��
            DFS(visited,Head,p->VerAdj,n,newPath,paths);
        }
        p=p->link;
    }
}

int main(void)
{
    int T;
    cin>>T;

    vector<int> answer;

    for(int z=0; z<T; z++)
    {
        int n;
        cin>>n;

        Vertex* Head[n+1];

        for(int i=0; i<n+1; i++)
        {
            Head[i]=new Vertex(i);
        }

        for(int i=1; i<=n; i++)
        {
            int ui,si,vi,fi;
            cin>>ui>>si>>vi>>fi;
            Head[i]->v=vi;
            Head[i]->f=fi;
            Edge* e=new Edge(ui,i,si);
            e->link=Head[ui]->adjacent;
            Head[ui]->adjacent=e;
        }

        vector< vector<Edge*> > paths;

        bool visited[n+1];

        reset(visited,n);

        vector<Edge*> path;

        DFS(visited,Head,1,n,path,&paths);

        cout<<endl;

        vector< vector<Edge*> > subPath;  //����ֲ����

        /*for(vector< vector<Edge*> >::iterator it=paths.begin(); it!=paths.end(); it++)
        {
            vector<Edge*> e=*it;
            for(vector<Edge*>::iterator i=e.begin(); i!=e.end(); i++)
            {
                cout<<(*i)->From<<" ";
            }
            cout<<(*(e.end()-1))->VerAdj;
            cout<<endl;
        }*/

        int sum=0;

        for(int k=1; k<=n; k++)
        {
            subPath.clear();
            for(vector< vector<Edge*> >::iterator it=paths.begin(); it!=paths.end(); it++)
            {
                vector<Edge*> e=*it;
                for(vector<Edge*>::iterator i=e.begin(); i!=e.end(); i++)
                {
                    if((*i)->From==k)
                    {
                        subPath.push_back(vector<Edge*>(i,e.end()));
                    }
                }
            }

            int maxBenefit=0;

            /**��̬�滮�㷨����Ȼ��0�֣�������ʾ����Ȼ��ȷ��������ʱ�޽�*/

            for(vector< vector<Edge*> >::iterator it=subPath.begin(); it!=subPath.end(); it++)
            {


                vector<Edge*>::iterator s,p,e;
                s=(*it).begin();
                //cout<<(*s)->From<<" "<<Head[(*s)->From]->VerName<<endl;
                e=(*it).end();

                Vertex* vt=Head[(*s)->From];
                //cout<<(*s)->From;

                p=s;    //p����ǰһ�εõ��������ĵ�������ͨ��p���Ի��ǰһ���

                int lastBestBenefit=vt->v-(vt->f-(*s)->cost)*(vt->f-(*s)->cost);;  //�ֲ�������棬��ʼ��Ϊ��ʼ��
                //cout<<lastBestBenefit<<endl;

                int lastCost=(*s)->cost;

                int benefit=0;  //һ��·������֮�������������

                for(int i=1; i<e-s; i++)
                {
                    Vertex* vt=Head[(*(s+i))->From];
                    int x=vt->v-(vt->f-(*(s+i))->cost)*(vt->f-(*(s+i))->cost);  //ֻ���µı߻�õ��������
                    //cout<<"x: "<<x<<endl;
                    int newCost=lastCost+(*(s+i))->cost;    //��ԭ���Ļ���֮������
                    //cout<<"newCost"<<newCost<<endl;
                    vt=Head[(*p)->From];    //��ԭ���Ļ���֮������
                    int y=vt->v-(vt->f-newCost)*(vt->f-newCost);    //��ԭ���Ļ���֮������
                    //cout<<"y: "<<y<<endl;
                    if(y>x) //����֮������´ο��ܼ������죬���p���䡣
                    {
                        lastCost=newCost;
                        lastBestBenefit=y;
                    }
                    else    //����ֹͣ
                    {
                        lastCost=(*(s+i))->cost;
                        benefit+=lastBestBenefit;

                        if(x<0) //����ֹͣ������x,y��С��0�������ǵ��ﾡͷ������Ȼû�л�������˲��ټ���benefit
                            x=0;

                        lastBestBenefit=x;
                        p=s+i;
                    }
                }

                benefit+=lastBestBenefit;

                if(benefit>maxBenefit)
                    maxBenefit=benefit;
            }

            //cout<<">>>>>>>>>>>>"<<maxBenefit<<endl;
            sum+=maxBenefit;
        }

        answer.push_back(sum);
    }

   for(vector<int>::iterator it=answer.begin();it!=answer.end();it++)
   {
       cout<<(*it)%(long long)1e18<<endl;
   }


}
