#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

void sinx_taylor(int terms, double x, double *result) {
    double value = x;              // 첫 항: x
    double numer = x * x * x;      // 분자: x^3
    double denom = 6.0;            // 분모: 3!
    int sign = -1;

    for (int j = 1; j < terms; j++) {
        value += sign * (numer / denom);
        numer *= x * x;
        denom *= (2.0 * j + 2.0) * (2.0 * j + 3.0);
        sign *= -1;
    }

    *result = value;
}

int main() {
    int num_elements = 5;
    double x[] = {0.0, M_PI/6, M_PI/4, M_PI/3, M_PI/2};
    int terms = 10;

    int pipes[5][2];
    pid_t pid;
    double result;

    for (int i = 0; i < num_elements; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe error");
            exit(1);
        }

	// fork() 사용으로 부모와 자식을 분리하여 작업 병렬처리   
        pid = fork();
        if (pid < 0) {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0) {  // 자식 프로세스
            close(pipes[i][0]);  // read 닫기

            double res;
            sinx_taylor(terms, x[i], &res);

            write(pipes[i][1], &res, sizeof(double));
            close(pipes[i][1]);
            exit(0);
        }
    }

    // 부모 프로세스
    for (int i = 0; i < num_elements; i++방지) {
	// wait() 사용으로 좀비 프로세스     
        wait(NULL);
        close(pipes[i][1]);  // write 닫기

        double child_result;
        read(pipes[i][0], &child_result, sizeof(double));
        close(pipes[i][0]);

        printf("x = %.3f, sin(x) ≈ %.6f (math.h: %.6f)\n",
               x[i], child_result, sin(x[i]));
    }

    return 0;
}

