#include <bits/stdc++.h>
#define MAX 1000000

int main(int argc, char const *argv[]) {
	std::vector<std::string> joias;
	char str[MAX];
	int c = 0;

	while (scanf("%s", str) != EOF) {
		auto it = std::find(joias.begin(), joias.end(), str);
		if (it == joias.end()) {
			joias.push_back(str);
			c++;
		}
	}

	printf("%d\n", c);
	
	return 0;
}