
#define DEFINE_MOD_FUN(N) \
int mod ## N (int x) \
{ \
  return x % N;
}
