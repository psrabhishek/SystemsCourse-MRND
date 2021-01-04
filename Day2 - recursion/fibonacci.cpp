#include"fibonacci.h"


long fib_recursion(int n)
{
	if (n < 2) return 1;
	return fib_recursion(n - 1) + fib_recursion(n - 2);
}

long fib_dp(int n, long* memo)
{
	if (n < 2) return n;
	if (memo[n - 1]) return memo[n - 1];
	else
		memo[n - 1] = fib_dp(n - 1, memo) + fib_dp(n - 2, memo);
	return memo[n - 1];
}