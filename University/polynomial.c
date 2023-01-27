#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float coef;
	int expon;
} polynomial;	//구조체 선언

int compare(int, int);//비교 함수
polynomial* single_mul(polynomial, polynomial*);//항과 다항식의 곱셈 함수
polynomial* pmul(polynomial*, polynomial*);//덧셈함수
polynomial* padd(polynomial*, polynomial*);//곱셈함수
void attach(polynomial*, float, int);//지수와 계수를 삽입하는 함수

int size_a;
int size_b;
int avail;


int main() {
    polynomial* A = (polynomial*)malloc(sizeof(polynomial) * 10);
    polynomial* B = (polynomial*)malloc(sizeof(polynomial) * 10);

    int i = 0;

    while (1) {
        printf("A항을 입력하세요. (coef, expon)");
        scanf_s("%f %d", &A[i].coef, &A[i].expon);
        if (A[i].coef == -1 && A[i].expon == -1)break; //A의 지수와 계수가 -1일 때까지 입력
        i++;
        size_a++;
        if (size_a == 10) {
            A = (polynomial*)realloc(A, sizeof(polynomial) * 10);
        }//만약 항의 수가 10보다 커지면 배열 크기 증가
    }

    i = 0;
    while (1) {
        printf("B항을 입력하세요. (coef, expon)");
        scanf_s("%f %d", &B[i].coef, &B[i].expon);
        if (B[i].coef == -1 && B[i].expon == -1) break; //A의 지수와 계수가 -1일 때까지 입력
        i++;
        size_b++;
        if (size_b == 10) {
            B = (polynomial*)realloc(B, sizeof(polynomial) * 10);
        }//만약 항의 수가 10보다 커지면 배열 크기 증가
    }

    polynomial* D1 = padd(A, B); //D1 에 A와 B를 더함
    printf("         coef\texpon\n");
    for (int j = 0; j < avail; j++)
        printf("더하기 : %.2f\t%d\n", D1[j].coef, D1[j].expon);
    printf("\n");
    free(D1);

    polynomial* D2 = pmul(A, B); //D2에 A와 B를 곱함
    printf("         coef\texpon\n");
    for (int j = 0; j < avail; j++)
        printf("곱하기 : %.2f\t%d\n", D2[j].coef, D2[j].expon);
    printf("\n");
    free(D2);

    free(A);
    free(B);
    return 0;

}

int compare(int a, int b) {
    if (a < b)
        return -1;
    else if (a == b)
        return 0;
    else
        return 1;
}//비교함수

polynomial* padd(polynomial* A, polynomial* B) {
    avail = 0;
    float coefficient;
    polynomial* D = (polynomial*)malloc(sizeof(polynomial) * 50);
    int startA = 0, startB = 0;
    while (startA <= size_a - 1 || startB <= size_b - 1) {
        switch (compare(A[startA].expon, B[startB].expon)) {
        case -1: //B의 지수가 A의 지수보다 크면 D에 B의 지수를 넣음
            attach(D, B[startB].coef, B[startB].expon);
            startB++;
            break;
        case 0: //A의 지수와 B의 지수가 같으면  D에 A의 계수와 B의 계수를 더한 값을 넣음
            coefficient = A[startA].coef + B[startB].coef;
            if (coefficient)
                attach(D, coefficient, A[startA].expon);
            startA++;
            startB++;
            break;
        case 1://A의 지수가 B의 지수보다 크면 D에 A의 지수를 넣음 
            attach(D, A[startA].coef, A[startA].expon);
            startA++;
        }
    }
    for (; startA <= size_a - 1; startA++)//A의 나머지 항을 D에 추가
        attach(D, A[startA].coef, A[startA].expon);
    for (; startB <= size_b - 1; startB++)//B의 나머지 항을 D에 추가
        attach(D, A[startB].coef, A[startB].expon);
    return  D;
}

void attach(polynomial* D, float coefficient, int exponent) {
    D[avail].coef = coefficient;
    D[avail++].expon = exponent;
}//D에 지수와 계수를 삽입하는 함수

polynomial* single_mul(polynomial A, polynomial* B) {
    polynomial* X = (polynomial*)malloc(sizeof(polynomial) * 50);
    float coef = 0;
    int expon = 0;
    for (int i = 0; i < size_b; i++) { //B의 모든 항에 대해 A와 연산
        coef = A.coef * B[i].coef; //A의 계수와 B[i]의 계수를 곱함
        expon = A.expon + B[i].expon; //A의 지수와 B[i]의 계수를 더함
        X[i].coef = coef;
        X[i].expon = expon;
    }
    return X;

}


polynomial* pmul(polynomial* A, polynomial* B) {
    polynomial* D = (polynomial*)malloc(sizeof(polynomial) * 50);
    printf("               coef\texpon\n");
    for (int i = 0; i < size_a; i++) { // A의 모든 항에 대해 연산
        polynomial* X = single_mul(A[i], B); //A의 항과 B의 다항식끼리 곱셈
        for (int j = 0; j < size_b; j++)
            printf("%d차 single_mul:%.2f\t%d\n", i + 1, X[j].coef, X[j].expon); //single_mul 결과를 출력
        printf("\n");
        D = padd(D, X); //D에 기존의 D에 single_mul 한 X를 더함
        free(X);
    }
    return D;
}
