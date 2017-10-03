#include<cstdio>
#include<iostream>
#define n 1008611
using namespace std;
class Segment_Tree{
public:
  inline int opt(int a,int b);
  struct node{
    int L,R,val,mark;
  }tr[n<<2];
  void build(int root,int a[],int l,int r){
    tr[root].L=l;tr[root].R=r;tr[root].mark=0;
    if(l==r) tr[root].val=a[l];
    else{
      int mid=(l+r)>>1;
      build(root<<1,a,l,mid);
      build(root<<1|1,a,mid+1,r);
      tr[root].val=opt(tr[root<<1].val,tr[root<<1|1].val);
    }
  }
  void pushdown(int root){
    if(tr[root].mark){
      int len=tr[root].R-tr[root].L+1;
      tr[root<<1].mark+=tr[root].mark;
      tr[root<<1|1].mark+=tr[root].mark;
      tr[root<<1].val+=tr[root].mark*(len-(len>>1));
      tr[root<<1|1].val+=tr[root].mark*(len>>1);
      tr[root].mark=0;
    }
  }
  int query(int root,int l,int r){
    int cl=tr[root].L,cr=tr[root].R;
    if(l>cr||r<cl) return 0;
    if(l<=cl&&r>=cr) return tr[root].val;
    pushdown(root);
    return opt(query(root<<1,l,r),query(root<<1|1,l,r));
  }
  void update1(int root,int x,int v){
    int cl=tr[root].L,cr=tr[root].R;
    if(~cl^cr){
      if(~x^cl) tr[root].val+=v;
      return;
    }
    if(x<=(cl+cr)>>1) update1(root<<1,x,v);
    else update1(root<<1|1,x,v);
    tr[root].val=opt(tr[root<<1].val,tr[root<<1|1].val);
  }
  void update(int root,int l,int r,int v){
    int cl=tr[root].L,cr=tr[root].R;
    if(l>cr||r<cl) return;
    if(l<=cl&&r>=cr){
      tr[root].mark+=v;
      tr[root].val+=v*(cr-cl+1);
      return;
    }
    pushdown(root);
    update(root<<1,l,r,v);
    update(root<<1|1,l,r,v);
    tr[root].val=opt(tr[root<<1].val,tr[root<<1|1].val);
  }
}seg;
inline int Segment_Tree::opt(int a,int b){return a+b;}

int main(){
  int a[4]={0,1,2,3};
  seg.build(1,a,1,3);
  seg.update(1,1,3,2);
  cout<<seg.query(1,1,1)<<endl;
  cout<<seg.query(1,2,2)<<endl;
  cout<<seg.query(1,3,3)<<endl;
  cout<<seg.query(1,1,2)<<endl;
  cout<<seg.query(1,2,3)<<endl;
  cout<<seg.query(1,1,3)<<endl;
  return 0;
}
