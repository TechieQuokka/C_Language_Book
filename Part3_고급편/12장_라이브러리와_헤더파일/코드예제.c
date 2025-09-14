/*
 * 12장 라이브러리와 헤더파일 - 핵심 개념 코드 예제
 * 개념 이해를 위한 최소한의 실용적 예제들
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

//=============================================================================
// 12.1 표준 라이브러리 활용 - 핵심 개념 예제
//=============================================================================

void demo_standard_library() {
    printf("=== 12.1 표준 라이브러리 활용 ===\n");

    // stdio.h - 스트림과 형식화된 입출력
    printf("스트림 개념: 표준 출력으로 데이터 흐름\n");

    char buffer[100];
    sprintf(buffer, "형식화된 문자열: %d + %d = %d", 5, 3, 8);
    printf("%s\n", buffer);

    // stdlib.h - 메모리 관리와 유틸리티
    int *numbers = malloc(5 * sizeof(int));
    if (numbers != NULL) {
        for (int i = 0; i < 5; i++) {
            numbers[i] = i * i;
        }
        printf("동적 배열: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        free(numbers);
    }

    // string.h - 문자열 조작
    char str1[50] = "Hello";
    char str2[] = " World";
    strcat(str1, str2);
    printf("문자열 연결: %s\n", str1);

    // math.h - 수학 함수
    double angle = 3.14159 / 4;  // 45도
    printf("sin(45°) = %.3f\n", sin(angle));
    printf("sqrt(16) = %.1f\n", sqrt(16));

    // ctype.h - 문자 분류
    char ch = 'A';
    printf("'%c'는 알파벳? %s\n", ch, isalpha(ch) ? "예" : "아니오");
    printf("'%c'를 소문자로: %c\n", ch, tolower(ch));

    // time.h - 시간 처리
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    printf("현재 시간: %d년 %d월 %d일 %d:%d:%d\n",
           local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
           local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

    printf("\n");
}

//=============================================================================
// 12.2 사용자 정의 헤더 파일 개념 시연
//=============================================================================

// 간단한 계산기 모듈 시뮬레이션
// (실제로는 calculator.h와 calculator.c로 분리됨)

// === calculator.h 에 해당하는 부분 (인터페이스) ===
typedef struct Calculator Calculator;

Calculator* calc_create(void);
double calc_add(Calculator* calc, double a, double b);
double calc_multiply(Calculator* calc, double a, double b);
double calc_get_last_result(Calculator* calc);
void calc_destroy(Calculator* calc);

// === calculator.c 에 해당하는 부분 (구현) ===
struct Calculator {
    double last_result;
    int operation_count;
};

Calculator* calc_create(void) {
    Calculator* calc = malloc(sizeof(Calculator));
    if (calc) {
        calc->last_result = 0.0;
        calc->operation_count = 0;
    }
    return calc;
}

double calc_add(Calculator* calc, double a, double b) {
    if (calc) {
        calc->last_result = a + b;
        calc->operation_count++;
    }
    return calc->last_result;
}

double calc_multiply(Calculator* calc, double a, double b) {
    if (calc) {
        calc->last_result = a * b;
        calc->operation_count++;
    }
    return calc->last_result;
}

double calc_get_last_result(Calculator* calc) {
    return calc ? calc->last_result : 0.0;
}

void calc_destroy(Calculator* calc) {
    if (calc) {
        printf("계산기 정리: %d번의 연산 수행됨\n", calc->operation_count);
        free(calc);
    }
}

void demo_custom_headers() {
    printf("=== 12.2 사용자 정의 헤더 파일 개념 ===\n");

    printf("인터페이스와 구현의 분리:\n");
    printf("- 사용자는 Calculator 구조체 내부를 모름\n");
    printf("- 불투명 포인터를 통해서만 조작\n");

    Calculator* calc = calc_create();

    printf("덧셈: %.1f\n", calc_add(calc, 10.5, 5.3));
    printf("곱셈: %.1f\n", calc_multiply(calc, 3.0, 4.0));
    printf("마지막 결과: %.1f\n", calc_get_last_result(calc));

    calc_destroy(calc);
    printf("\n");
}

//=============================================================================
// 12.3 모듈화 프로그래밍 - 핵심 개념 예제
//=============================================================================

// === 로거 모듈 시뮬레이션 ===
typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

typedef struct Logger Logger;

// 로거 인터페이스 (높은 응집도)
Logger* logger_create(const char* prefix);
void logger_log(Logger* logger, LogLevel level, const char* message);
void logger_destroy(Logger* logger);

// 로거 구현 (정보 은닉)
struct Logger {
    char prefix[32];
    int message_count;
};

Logger* logger_create(const char* prefix) {
    Logger* logger = malloc(sizeof(Logger));
    if (logger) {
        strncpy(logger->prefix, prefix ? prefix : "APP", 31);
        logger->prefix[31] = '\0';
        logger->message_count = 0;
    }
    return logger;
}

void logger_log(Logger* logger, LogLevel level, const char* message) {
    if (!logger || !message) return;

    const char* level_str[] = {"INFO", "WARN", "ERROR"};
    printf("[%s-%s] %s\n", logger->prefix, level_str[level], message);
    logger->message_count++;
}

void logger_destroy(Logger* logger) {
    if (logger) {
        printf("[%s] 총 %d개의 로그 메시지 출력됨\n",
               logger->prefix, logger->message_count);
        free(logger);
    }
}

// === 이벤트 시스템 모듈 (콜백 기반) ===
typedef void (*EventCallback)(const char* event, void* data);

typedef struct EventSystem {
    EventCallback callbacks[10];
    int callback_count;
} EventSystem;

static EventSystem g_event_system = {0};

void event_register(EventCallback callback) {
    if (g_event_system.callback_count < 10) {
        g_event_system.callbacks[g_event_system.callback_count++] = callback;
    }
}

void event_trigger(const char* event, void* data) {
    for (int i = 0; i < g_event_system.callback_count; i++) {
        g_event_system.callbacks[i](event, data);
    }
}

// 이벤트 핸들러 예시
void on_user_login(const char* event, void* data) {
    if (strcmp(event, "user_login") == 0) {
        char* username = (char*)data;
        printf("이벤트 처리: %s 사용자가 로그인했습니다\n", username);
    }
}

void on_system_error(const char* event, void* data) {
    if (strcmp(event, "system_error") == 0) {
        int error_code = *(int*)data;
        printf("이벤트 처리: 시스템 오류 발생 (코드: %d)\n", error_code);
    }
}

void demo_modular_programming() {
    printf("=== 12.3 모듈화 프로그래밍 개념 ===\n");

    // 로거 모듈 사용 (높은 응집도, 낮은 결합도)
    Logger* app_logger = logger_create("APP");
    Logger* db_logger = logger_create("DB");

    logger_log(app_logger, LOG_INFO, "애플리케이션 시작");
    logger_log(db_logger, LOG_INFO, "데이터베이스 연결");
    logger_log(app_logger, LOG_WARNING, "설정 파일 누락");
    logger_log(db_logger, LOG_ERROR, "연결 실패");

    // 이벤트 시스템 (콜백을 통한 느슨한 결합)
    printf("\n이벤트 시스템 (모듈 간 통신):\n");
    event_register(on_user_login);
    event_register(on_system_error);

    char username[] = "alice";
    event_trigger("user_login", username);

    int error_code = 404;
    event_trigger("system_error", &error_code);

    logger_destroy(app_logger);
    logger_destroy(db_logger);
    printf("\n");
}

//=============================================================================
// 12.4 컴파일과 링크 개념 시연
//=============================================================================

// 전처리기 개념 시연
#define MAX_ITEMS 5
#define SQUARE(x) ((x) * (x))
#define DEBUG_PRINT(msg) printf("DEBUG: %s\n", msg)

#ifdef DEBUG
    #define DBG(x) x
#else
    #define DBG(x)
#endif

// 조건부 컴파일 시연
void show_compilation_info() {
    printf("=== 컴파일 정보 ===\n");
    printf("컴파일 날짜: %s\n", __DATE__);
    printf("컴파일 시간: %s\n", __TIME__);
    printf("파일명: %s\n", __FILE__);

    #ifdef __GNUC__
        printf("컴파일러: GCC %d.%d.%d\n",
               __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #endif

    #ifdef _WIN32
        printf("플랫폼: Windows\n");
    #elif defined(__linux__)
        printf("플랫폼: Linux\n");
    #else
        printf("플랫폼: Unknown\n");
    #endif
}

// 심볼과 링크 개념
extern int external_symbol;  // 다른 파일에 정의된 심볼 (링크 시점에 해결)
static int internal_symbol = 100;  // 파일 내부에만 보이는 심볼

int global_symbol = 42;  // 외부에서 접근 가능한 심볼

void demo_compilation_and_linking() {
    printf("=== 12.4 컴파일과 링크 개념 ===\n");

    // 전처리기 개념
    printf("전처리기 매크로:\n");
    printf("MAX_ITEMS = %d\n", MAX_ITEMS);
    printf("SQUARE(4) = %d\n", SQUARE(4));
    DEBUG_PRINT("이것은 디버그 메시지입니다");

    // 조건부 컴파일 결과
    DBG(printf("디버그 모드가 활성화된 경우에만 출력\n"));

    // 심볼의 스코프
    printf("\n심볼의 가시성:\n");
    printf("전역 심볼: %d\n", global_symbol);
    printf("정적 심볼: %d\n", internal_symbol);
    // printf("외부 심볼: %d\n", external_symbol);  // 링크 오류 발생 가능

    // 빌드 정보
    show_compilation_info();

    printf("\n빌드 과정 단계:\n");
    printf("1. 전처리: 매크로 확장, include 처리\n");
    printf("2. 컴파일: C 코드 → 어셈블리\n");
    printf("3. 어셈블: 어셈블리 → 오브젝트 파일\n");
    printf("4. 링크: 오브젝트 파일들 → 실행 파일\n");

    printf("\n");
}

//=============================================================================
// 통합 시연: 라이브러리 설계 패턴
//=============================================================================

// 간단한 문자열 유틸리티 라이브러리 예제
typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} String;

String* string_create(const char* initial) {
    String* str = malloc(sizeof(String));
    if (!str) return NULL;

    size_t len = initial ? strlen(initial) : 0;
    str->capacity = len > 16 ? len * 2 : 16;
    str->data = malloc(str->capacity);
    str->length = len;

    if (initial && str->data) {
        strcpy(str->data, initial);
    } else if (str->data) {
        str->data[0] = '\0';
    }

    return str;
}

void string_append(String* str, const char* text) {
    if (!str || !text) return;

    size_t text_len = strlen(text);
    if (str->length + text_len >= str->capacity) {
        str->capacity = (str->length + text_len + 1) * 2;
        str->data = realloc(str->data, str->capacity);
    }

    if (str->data) {
        strcat(str->data, text);
        str->length += text_len;
    }
}

const char* string_get(const String* str) {
    return str ? str->data : "";
}

void string_destroy(String* str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

void demo_library_design() {
    printf("=== 라이브러리 설계 패턴 통합 예제 ===\n");

    String* message = string_create("Hello");
    string_append(message, " ");
    string_append(message, "Library");
    string_append(message, " Design!");

    printf("동적 문자열: %s\n", string_get(message));

    printf("\n라이브러리 설계 원칙:\n");
    printf("- 일관된 명명 규칙 (string_* prefix)\n");
    printf("- 불투명 포인터 사용 (구현 숨김)\n");
    printf("- 오류 처리 (NULL 체크)\n");
    printf("- 자원 관리 (create/destroy 패턴)\n");

    string_destroy(message);
    printf("\n");
}

//=============================================================================
// 메인 함수
//=============================================================================

int main() {
    printf("C언어 정석 - 12장 라이브러리와 헤더파일\n");
    printf("==========================================\n\n");

    demo_standard_library();
    demo_custom_headers();
    demo_modular_programming();
    demo_compilation_and_linking();
    demo_library_design();

    printf("모든 예제 완료!\n");
    return 0;
}