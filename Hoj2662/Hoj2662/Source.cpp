#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

//Code from: http://blog.csdn.net/wangjianbing1998/article/details/52168249
#define LL long long
LL dp[82][22][1<<6],mark[1<<6],zt,ans;
int n,m,k;
int num(LL x)//����һ��״̬��ֵ��Ӧ��1�ĸ������������X�������õ����ӵĸ���
{
    int sum=0;
    while(x)
    {
        if(x&1)sum++;
        x=x>>1;
    }
    return sum;
}
bool judge_row(int x)//������ж�ÿһ������Ƿ����㻥������
{
    return (!(x&(x<<1)));
}
int main()
{
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        zt=0;
        memset(dp,0,sizeof dp);
        memset(mark,0,sizeof mark);
        if(n<m)//�����Ǳ�֤n>=m��ʹ������������ʱ�䡣
        {
        n=n^m;
        m=n^m;
        n=n^m;
        }
//        cout<<"******************"<<endl<<n<<m<<endl;
        for(LL i=0;i<(1<<m);i++)//��ʼ����һ��
        {
            if(judge_row(i))
            {
                dp[1][num(i)][zt]=1;
                mark[zt++]=i;
            }
        }
        for(int i=2;i<=n;i++)//�ֱ�2~n�ж�׳ѹ
            for(int j=0;j<=k;j++)
            for(LL x=0;x<zt;x++)
            for(LL y=0;y<zt;y++)
            {
//                LL temp=num(mark[x]);
                if(((mark[x]&mark[y])==0)&&j>=num(mark[x]))//�������ж����������ǲ��ǺϷ���ʣ�µ����Ӷ������������ڵ�x�����
                {
                    dp[i][j][x]+=dp[i-1][j-num(mark[x])][y];//����һ���Ѿ��õ��Ľ������һ�еĽ��������������ǰi�е��ܷ�����
                }
            }
        ans=0;
        for(LL i=0;i<zt;i++)//����ͨ����ͬ״̬ɨ����ĩβ����Щ���������������������մ�
        ans+=dp[n][k][i];
            printf("%lld\n",ans);
    }
}

