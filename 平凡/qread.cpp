template<typename T>
inline void read(T &x){
  char ch;while((ch=getchar()),(ch>'9'||ch<'0'));
  x=ch-'0';while((ch=getchar()),(ch>='0'&&ch<='9')) x=x*10+ch-'0';
}
