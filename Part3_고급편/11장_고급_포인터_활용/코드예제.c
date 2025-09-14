/*
 * 11장 고급 포인터 활용 - 핵심 개념 코드 예제
 * 개념 이해를 위한 최소한의 실용적 예제들
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=============================================================================
// 11.1 이중 포인터 - 핵심 개념 예제
//=============================================================================

// 개념 1: 포인터 자체를 변경하는 함수
void allocate_memory(int **ptr, int value) {
    *ptr = malloc(sizeof(int));
    **ptr = value;
    printf("메모리 할당 완료: %d\n", **ptr);
}

// 개념 2: 문자열 배열의 동적 관리
void create_string_array(char ***strings, int count) {
    *strings = malloc(count * sizeof(char*));

    char sample[][10] = {"Hello", "World", "C"};
    for (int i = 0; i < count; i++) {
        (*strings)[i] = malloc(strlen(sample[i]) + 1);
        strcpy((*strings)[i], sample[i]);
    }
}

void demo_double_pointer() {
    printf("=== 11.1 이중 포인터 개념 ===\n");

    // 포인터 변경 예제
    int *ptr = NULL;
    allocate_memory(&ptr, 42);
    printf("할당된 값: %d\n", *ptr);
    free(ptr);

    // 문자열 배열 관리
    char **strings = NULL;
    int count = 3;
    create_string_array(&strings, count);

    printf("생성된 문자열들:\n");
    for (int i = 0; i < count; i++) {
        printf("  %s\n", strings[i]);
        free(strings[i]);
    }
    free(strings);

    printf("\n");
}

//=============================================================================
// 11.2 포인터 배열 - 핵심 개념 예제
//=============================================================================

// 개념 1: 함수 포인터 배열을 이용한 간단한 계산기
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

void demo_pointer_array() {
    printf("=== 11.2 포인터 배열 개념 ===\n");

    // 함수 포인터 배열
    int (*operations[])(int, int) = {add, subtract, multiply};
    char *op_names[] = {"덧셈", "뺄셈", "곱셈"};

    int a = 15, b = 5;
    printf("a = %d, b = %d\n", a, b);

    for (int i = 0; i < 3; i++) {
        printf("%s: %d\n", op_names[i], operations[i](a, b));
    }

    // 문자열 포인터 배열의 효율성 비교
    printf("\n문자열 관리 비교:\n");

    // 2차원 배열 (고정 크기)
    char fixed_names[3][20] = {"Alice", "Bob", "Charlie"};
    printf("고정 배열 크기: %lu bytes\n", sizeof(fixed_names));

    // 포인터 배열 (가변 크기)
    char *dynamic_names[] = {"Alice", "Bob", "Charlie"};
    printf("포인터 배열 크기: %lu bytes\n", sizeof(dynamic_names));

    printf("\n");
}

//=============================================================================
// 11.3 다차원 배열과 포인터 - 핵심 개념 예제
//=============================================================================

// 개념 1: 2차원 배열의 다양한 접근 방법
void demo_2d_array_access() {
    printf("=== 11.3 다차원 배열 접근 방법 ===\n");

    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

    printf("matrix[1][2] = %d 에 접근하는 다양한 방법:\n", matrix[1][2]);
    printf("  matrix[1][2]         = %d\n", matrix[1][2]);
    printf("  *(*(matrix + 1) + 2) = %d\n", *(*(matrix + 1) + 2));
    printf("  (*(matrix + 1))[2]   = %d\n", (*(matrix + 1))[2]);

    printf("\n");
}

// 개념 2: 동적 2차원 배열 (간단한 버전)
void demo_dynamic_2d_array() {
    printf("=== 동적 2차원 배열 ===\n");

    int rows = 2, cols = 3;

    // 포인터 배열 방식
    int **matrix = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    // 값 할당
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }

    // 출력
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    // 해제
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    printf("\n");
}

//=============================================================================
// 11.4 복잡한 선언 해석 - 핵심 개념 예제
//=============================================================================

// 개념 1: 선언 해석 연습
void demo_declaration_parsing() {
    printf("=== 11.4 선언 해석 연습 ===\n");

    // 기본 패턴들
    int *p;              // p는 int를 가리키는 포인터
    int arr[5];          // arr은 5개 int의 배열
    int *ptr_arr[3];     // ptr_arr은 int 포인터 3개의 배열
    int (*arr_ptr)[5];   // arr_ptr은 int 5개 배열을 가리키는 포인터

    printf("선언 패턴들:\n");
    printf("  int *p;           // 포인터\n");
    printf("  int arr[5];       // 배열\n");
    printf("  int *ptr_arr[3];  // 포인터 배열\n");
    printf("  int (*arr_ptr)[5];// 배열의 포인터\n");

    // 함수 포인터 예제
    int (*func_ptr)(int, int) = add;
    printf("\n함수 포인터 사용:\n");
    printf("  결과: %d\n", func_ptr(10, 5));

    printf("\n");
}

// 개념 2: typedef를 이용한 복잡성 관리
typedef int (*BinaryOp)(int, int);
typedef BinaryOp OpArray[3];

void demo_typedef_simplification() {
    printf("=== typedef를 이용한 단순화 ===\n");

    // 복잡한 원본: int (*operations[3])(int, int)
    // 단순화된 버전:
    OpArray operations = {add, subtract, multiply};

    printf("typedef 사용 전: int (*operations[3])(int, int)\n");
    printf("typedef 사용 후: OpArray operations\n");
    printf("결과는 동일: %d + %d = %d\n", 8, 3, operations[0](8, 3));

    printf("\n");
}

//=============================================================================
// 통합 시연 예제
//=============================================================================

// 실용적 예제: 간단한 명령어 처리 시스템
typedef struct {
    char *name;
    void (*handler)(void);
} Command;

void cmd_hello() { printf("Hello, World!\n"); }
void cmd_info() { printf("포인터 활용 예제 프로그램\n"); }

void demo_practical_example() {
    printf("=== 실용적 활용 예제: 명령어 시스템 ===\n");

    Command commands[] = {
        {"hello", cmd_hello},
        {"info", cmd_info}
    };

    int cmd_count = sizeof(commands) / sizeof(commands[0]);

    printf("사용 가능한 명령어:\n");
    for (int i = 0; i < cmd_count; i++) {
        printf("  %s: ", commands[i].name);
        commands[i].handler();
    }

    printf("\n");
}

//=============================================================================
// 메인 함수
//=============================================================================

int main() {
    printf("C언어 정석 - 11장 고급 포인터 활용\n");
    printf("====================================\n\n");

    demo_double_pointer();
    demo_pointer_array();
    demo_2d_array_access();
    demo_dynamic_2d_array();
    demo_declaration_parsing();
    demo_typedef_simplification();
    demo_practical_example();

    printf("모든 예제 완료!\n");
    return 0;
}