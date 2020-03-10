#include <bits/stdc++.h>

int check_s(int* v1, int* v2, int n2) {
	for (int i = 0; i < n2; i++)
		if (v1[i] != v2[n2 - i - 1])
			return 0;
	return 1;
}

int check_q(int* v1, int* v2, int n2) {
	for (int i = 0; i < n2; i++)
		if (v1[i] != v2[i])
			return 0;
	return 1;
}

int check_pq(int* v, int n) {
	for (int i = 0; i < n - 1; i++)
		if (v[i] < v[i+1])
			return 0;
	return 1;
}

int find(int* v, int n, int val) {
	for (int i = 0; i < n; i++)
		if (v[i] == val)
			return 1;
	return 0;
}

int sumArray(int* v, int n) {
	int s = 0;
	for (int i = 0; i < n; i++)
		s += v[i];
	return s;
}

void printArray(int* v, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}

#define MAX 1000
int main(int argc, char const *argv[]) {
	int n;
	while (scanf("%d", &n) != EOF) {
		int in[MAX] = {0}, out[MAX] = {0};
		int n1 = 0, n2 = 0;
		int j = 0, k = 0;
		int imp = 0;
		int est[3] = {1, 1, 1};

		for (int i = 0; i < n; i++) {
			int x, y;
			
			scanf("%d %d", &x, &y);
			if (x == 1)
				in[n1++] = y;
			else {
				if (!imp && find(in, n1, y))
					out[n2++] = y;
				else
					imp = 1;
			}
		}

		est[0] = check_s(in, out, n2);
		est[1] = check_q(in, out, n2);
		est[2] = check_pq(out, n2);

		if (imp || sumArray(est, 3) == 0)
			printf("impossible\n");
		else if (sumArray(est, 3) > 1)
			printf("not sure\n");
		else if (est[0])
			printf("stack\n");
		else if (est[1])
			printf("queue\n");
		else if (est[2])
			printf("priority queue\n");
	}

	return 0;
}