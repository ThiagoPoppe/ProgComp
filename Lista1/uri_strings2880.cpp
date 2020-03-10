#include <bits/stdc++.h>
#define MAX 10001

int main(int argc, char const *argv[]) {
	char s1[MAX], s2[MAX];
	int c = 0;
	
	scanf("%s %s", s1, s2);
	for (int i = 0; i < strlen(s1) - strlen(s2) + 1; i++) {
		int found = 0;
		for (int j = 0; j < strlen(s2); j++) {
			if (s1[i+j] == s2[j]) {
				found = 1;
				break;
			}
		}

		if (!found)
			c++;
	}

	printf("%d\n", c);

	return 0;
}
