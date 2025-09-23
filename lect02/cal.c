#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("사용법: %s num1 operator num2\n", argv[0]);
		printf("예시: %s 3 + 4\n", argv[0]);
		return 1;
	}

	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[3]);
	char op = argv[2][0];

	int result;

	switch(op) {
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '.':
			result = num1 * num2;
			break;
		case '/':
			if (num2 == 0) {
				printf("0으로 나눌 수 없습니다.\n");
				return 1;
			}
			result = num1 / num2;
			break;
	}
	
	printf("%d %c %d = %d\n", num1, op, num2, result);

	return 0;
}
