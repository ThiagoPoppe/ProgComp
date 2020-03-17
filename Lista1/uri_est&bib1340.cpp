#include <bits/stdc++.h>

int main(int argc, char const *argv[]) {
	int n, x, y;

	while (scanf("%d", &n) != EOF) {
		bool isStack = true, isQueue = true, isPrtQueue = true;

		// Declarando dentro do while para que seus valores sejam limpados
		std::stack<int> myStack;
		std::vector<int> myQueue, myPrtQueue;

		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);

			if (x == 1) {
				myStack.push(y);
				myQueue.push_back(y);
				myPrtQueue.push_back(y);

				// Criando um heap (max)
				std::push_heap(myPrtQueue.begin(), myPrtQueue.end());
			}
			else {
				// Verificando para a pilha
				if (isStack && y != myStack.top())
					isStack = false;
				else
					myStack.pop();

				// Verificando para a fila
				if (isQueue && y != myQueue.front())
					isQueue = false;
				else
					myQueue.erase(myQueue.begin());

				// Verificando para a fila de prioridades
				if (isPrtQueue && y != myPrtQueue.front())
					isPrtQueue = false;
				else {
					std::pop_heap(myPrtQueue.begin(), myPrtQueue.end());
					myPrtQueue.pop_back();	
				}
			}
		}

		// Imprimindo qual deve ser a estrutura de dados
		if (!isStack && !isQueue && !isPrtQueue)
			printf("impossible\n");
		else if (isStack && !isQueue && !isPrtQueue)
			printf("stack\n");
		else if (!isStack && isQueue && !isPrtQueue)
			printf("queue\n");
		else if (!isStack && !isQueue && isPrtQueue)
			printf("priority queue\n");
		else
			printf("not sure\n");
	}

	return 0;
}