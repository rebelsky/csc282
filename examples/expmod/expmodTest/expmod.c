long
expmodBad(long x, long n, long m)
{
  long result = 1;
  for (int i = 0; i < n; i++)
    {
      result = (result * x) % m;
    } // for
  return result;
} // expmod

long
expmodRec(long x, long n, long m)
{
  if (n == 0)                           // x^0 = 1
    {
      return 1;
    }
  else if ((n % 2) == 0) { // even
    long tmp = expmodRec(x, n/2, m);       // x^(2k) = x^k * x^k
    return (tmp * tmp) % m;
  }
  else {
    long tmp = expmodRec(x, n-1, m);       // x^(k+1) = x^k * x
    return (x * tmp) % m;
  }
} // expmod