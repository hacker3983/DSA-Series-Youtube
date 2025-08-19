#include <stdio.h>

/* Recursion - the process of a function / procedure calling itself.
 * this function is known as a recursive function.
 * Some problems that are done using recursion can be done iteratively but they both have
 * their advantages and disadvantages:
 * Advantages of recursion:
 * 1. Simpler Code for complex problems
 * 2. Code Readability
 * 3. Problem Decomposition - Breaking down problems into smaller subproblems
 * 4. Backtracking - Ideal for problems that involves exploring all possibilities such as puzzles, and mazes
 * Disadvantages:
 * 1. Memory Overhead
 * 2. Slower Execution
 * 3. Harder Debugging
 * 4. Risk of infinite recursion
*/

/* ITERATIVELY:
void count(int n) {
	for(int i=1;i<=n;i++) {
		printf("Counting %d\n", i);
	}
}*/

/* RECURSIVELY:*/
void count(int n) {
	if(n == 0) {
		return;
	}
	count(n-1);
	printf("Counting %d\n", n);
}

/* ITERATIVELY:
void print_digits_reversed(int n) {
	while(n != 0) {
		printf("%d\n", n % 10);
		n /= 10;
	}
}*/

/* RECURSIVELY:*/
void print_digits_reversed(int n) {
	if(n == 0) {
		return;
	}
	printf("%d\n", n % 10);
	print_digits_reversed(n / 10);
}

int main() {
	print_digits_reversed(347);
	return 0;
}
