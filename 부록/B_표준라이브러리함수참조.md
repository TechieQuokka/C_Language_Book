# 부록 B. 표준 라이브러리 함수 참조

> **"표준 라이브러리는 프로그래머의 도구상자다. 올바른 도구를 선택하는 것이 효율적인 프로그래밍의 시작이다."**

## 개요

C 표준 라이브러리의 모든 헤더 파일과 주요 함수들을 체계적으로 정리한 참조표입니다. 각 함수의 프로토타입, 매개변수, 반환값, 사용 예시를 포함하여 실무에서 바로 활용할 수 있도록 구성했습니다.

## 표준 헤더 파일 목록

### C89/C90 표준 헤더 (15개)

| 헤더 파일 | 주요 기능 | 핵심 함수/매크로 |
|-----------|----------|------------------|
| **`<assert.h>`** | 디버그 어서션 | `assert()` |
| **`<ctype.h>`** | 문자 분류 및 변환 | `isalpha()`, `toupper()`, `tolower()` |
| **`<errno.h>`** | 오류 번호 정의 | `errno`, `EDOM`, `ERANGE` |
| **`<float.h>`** | 부동소수점 상수 | `FLT_MAX`, `DBL_DIG` |
| **`<limits.h>`** | 정수 타입 한계값 | `INT_MAX`, `CHAR_BIT` |
| **`<locale.h>`** | 지역화 함수 | `setlocale()` |
| **`<math.h>`** | 수학 함수 | `sin()`, `cos()`, `sqrt()`, `pow()` |
| **`<setjmp.h>`** | 비지역 점프 | `setjmp()`, `longjmp()` |
| **`<signal.h>`** | 신호 처리 | `signal()`, `raise()` |
| **`<stdarg.h>`** | 가변 인수 | `va_list`, `va_start()`, `va_end()` |
| **`<stddef.h>`** | 표준 정의 | `size_t`, `NULL`, `offsetof()` |
| **`<stdio.h>`** | 입출력 함수 | `printf()`, `scanf()`, `fopen()`, `fclose()` |
| **`<stdlib.h>`** | 유틸리티 함수 | `malloc()`, `free()`, `atoi()`, `rand()` |
| **`<string.h>`** | 문자열 처리 | `strlen()`, `strcpy()`, `strcmp()` |
| **`<time.h>`** | 시간 관련 함수 | `time()`, `clock()`, `strftime()` |

### C99 추가 헤더 (6개)

| 헤더 파일 | 주요 기능 | 핵심 함수/매크로 |
|-----------|----------|------------------|
| **`<complex.h>`** | 복소수 연산 | `creal()`, `cimag()`, `cabs()` |
| **`<fenv.h>`** | 부동소수점 환경 | `fegetround()`, `fesetround()` |
| **`<inttypes.h>`** | 정수 타입 포맷 | `PRId64`, `SCNx32` |
| **`<iso646.h>`** | 연산자 대체 매크로 | `and`, `or`, `not` |
| **`<stdbool.h>`** | 불린 타입 | `bool`, `true`, `false` |
| **`<stdint.h>`** | 정수 타입 정의 | `int32_t`, `uint64_t` |
| **`<tgmath.h>`** | 타입 제네릭 수학 | 타입에 따른 수학 함수 선택 |
| **`<wchar.h>`** | 와이드 문자 | `wprintf()`, `wcscpy()` |
| **`<wctype.h>`** | 와이드 문자 분류 | `iswalpha()`, `towupper()` |

### C11 추가 헤더 (5개)

| 헤더 파일 | 주요 기능 | 핵심 함수/매크로 |
|-----------|----------|------------------|
| **`<stdalign.h>`** | 정렬 지원 | `alignas`, `alignof` |
| **`<stdatomic.h>`** | 원자적 연산 | `atomic_int`, `atomic_store()` |
| **`<stdnoreturn.h>`** | 반환하지 않는 함수 | `noreturn` |
| **`<threads.h>`** | 스레드 지원 | `thrd_create()`, `mtx_lock()` |
| **`<uchar.h>`** | 유니코드 문자 | `char16_t`, `char32_t` |

## 주요 라이브러리 함수 상세

### 1. `<stdio.h>` - 입출력 함수

#### 파일 입출력

**파일 열기/닫기**
```
FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
```
- **매개변수**: filename (파일명), mode (열기 모드)
- **반환값**: 성공 시 파일 포인터, 실패 시 NULL
- **모드**: "r" (읽기), "w" (쓰기), "a" (추가), "rb" (바이너리 읽기) 등

**파일 읽기**
```
int fgetc(FILE *stream);                    // 문자 하나 읽기
char *fgets(char *str, int n, FILE *stream); // 문자열 읽기
size_t fread(void *ptr, size_t size, size_t count, FILE *stream); // 블록 읽기
```

**파일 쓰기**
```
int fputc(int c, FILE *stream);             // 문자 하나 쓰기
int fputs(const char *str, FILE *stream);   // 문자열 쓰기
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream); // 블록 쓰기
```

**파일 위치 제어**
```
int fseek(FILE *stream, long offset, int whence);  // 파일 포인터 이동
long ftell(FILE *stream);                          // 현재 위치 반환
void rewind(FILE *stream);                         // 파일 처음으로 이동
```

#### 포맷 입출력

**printf 계열**
```
int printf(const char *format, ...);                    // 표준 출력
int fprintf(FILE *stream, const char *format, ...);     // 파일 출력
int sprintf(char *str, const char *format, ...);        // 문자열 출력
int snprintf(char *str, size_t size, const char *format, ...); // 안전한 문자열 출력 (C99)
```

**scanf 계열**
```
int scanf(const char *format, ...);                     // 표준 입력
int fscanf(FILE *stream, const char *format, ...);      // 파일 입력
int sscanf(const char *str, const char *format, ...);   // 문자열 입력
```

**포맷 지정자**

| 지정자 | 타입 | 설명 | 예시 |
|--------|------|------|------|
| `%d`, `%i` | int | 10진 정수 | `printf("%d", 123)` |
| `%u` | unsigned int | 부호 없는 10진 정수 | `printf("%u", 123U)` |
| `%o` | unsigned int | 8진 정수 | `printf("%o", 64)` → "100" |
| `%x`, `%X` | unsigned int | 16진 정수 | `printf("%x", 255)` → "ff" |
| `%f` | double | 부동소수점 | `printf("%f", 3.14)` |
| `%e`, `%E` | double | 지수 표기법 | `printf("%e", 1234.0)` → "1.234e+03" |
| `%g`, `%G` | double | 자동 선택 | 짧은 형식 자동 선택 |
| `%c` | char | 단일 문자 | `printf("%c", 'A')` |
| `%s` | char* | 문자열 | `printf("%s", "Hello")` |
| `%p` | void* | 포인터 주소 | `printf("%p", ptr)` |
| `%%` | - | % 문자 | `printf("%%")` → "%" |

**포맷 수식어**

| 수식어 | 의미 | 예시 | 출력 |
|--------|------|------|------|
| `%5d` | 최소 5자리 | `printf("%5d", 123)` | "  123" |
| `%-5d` | 왼쪽 정렬 | `printf("%-5d", 123)` | "123  " |
| `%05d` | 0으로 패딩 | `printf("%05d", 123)` | "00123" |
| `%.2f` | 소수점 2자리 | `printf("%.2f", 3.14159)` | "3.14" |
| `%*d` | 동적 너비 | `printf("%*d", 5, 123)` | "  123" |

### 2. `<stdlib.h>` - 유틸리티 함수

#### 메모리 관리

**동적 메모리 할당**
```
void *malloc(size_t size);                    // 메모리 할당
void *calloc(size_t num, size_t size);        // 0으로 초기화된 메모리 할당
void *realloc(void *ptr, size_t size);        // 메모리 크기 변경
void free(void *ptr);                         // 메모리 해제
```

**사용 패턴**
- malloc → 사용 → free
- calloc → 0으로 초기화됨 → 사용 → free
- realloc → 기존 데이터 보존하며 크기 변경

#### 문자열 변환

**숫자 변환**
```
int atoi(const char *str);                    // 문자열을 int로
long atol(const char *str);                   // 문자열을 long으로
double atof(const char *str);                 // 문자열을 double로

long strtol(const char *str, char **endptr, int base);    // 진법 지원 long 변환
double strtod(const char *str, char **endptr);            // 오류 검출 가능한 double 변환
```

#### 정렬 및 검색

**정렬**
```
void qsort(void *base, size_t num, size_t size,
           int (*compare)(const void *, const void *));
```

**이진 검색**
```
void *bsearch(const void *key, const void *base, size_t num, size_t size,
              int (*compare)(const void *, const void *));
```

#### 난수 생성

**의사 난수**
```
int rand(void);                               // 0 ~ RAND_MAX 난수
void srand(unsigned int seed);                // 시드 설정
```

#### 프로그램 제어

**프로그램 종료**
```
void exit(int status);                        // 프로그램 종료
void abort(void);                             // 비정상 종료
int atexit(void (*func)(void));               // 종료 시 호출할 함수 등록
```

**환경변수**
```
char *getenv(const char *name);               // 환경변수 값 얻기
int system(const char *command);              // 시스템 명령 실행
```

### 3. `<string.h>` - 문자열 처리

#### 문자열 길이 및 복사

**길이 계산**
```
size_t strlen(const char *str);               // 문자열 길이
```

**복사**
```
char *strcpy(char *dest, const char *src);    // 문자열 복사
char *strncpy(char *dest, const char *src, size_t n);  // n개 문자 복사
```

**연결**
```
char *strcat(char *dest, const char *src);    // 문자열 연결
char *strncat(char *dest, const char *src, size_t n);  // n개 문자 연결
```

#### 문자열 비교

**비교**
```
int strcmp(const char *str1, const char *str2);        // 문자열 비교
int strncmp(const char *str1, const char *str2, size_t n);  // n개 문자 비교
int strcoll(const char *str1, const char *str2);       // 로케일 기반 비교
```

**반환값**:
- 0: 같음
- 양수: str1 > str2
- 음수: str1 < str2

#### 문자열 검색

**문자 검색**
```
char *strchr(const char *str, int c);         // 첫 번째 문자 위치
char *strrchr(const char *str, int c);        // 마지막 문자 위치
```

**문자열 검색**
```
char *strstr(const char *haystack, const char *needle);  // 부분 문자열 검색
size_t strspn(const char *str1, const char *str2);       // 일치하는 문자 개수
size_t strcspn(const char *str1, const char *str2);      // 일치하지 않는 문자 개수
char *strpbrk(const char *str1, const char *str2);       // 문자 집합 중 첫 일치
```

**토큰화**
```
char *strtok(char *str, const char *delim);   // 문자열 토큰화
```

#### 메모리 관련 함수

**메모리 설정**
```
void *memset(void *ptr, int value, size_t num);         // 메모리 값 설정
```

**메모리 복사**
```
void *memcpy(void *dest, const void *src, size_t n);    // 메모리 복사
void *memmove(void *dest, const void *src, size_t n);   // 겹치는 영역 복사
```

**메모리 비교**
```
int memcmp(const void *ptr1, const void *ptr2, size_t n);  // 메모리 비교
```

### 4. `<math.h>` - 수학 함수

#### 삼각함수

**기본 삼각함수**
```
double sin(double x);                         // 사인
double cos(double x);                         // 코사인
double tan(double x);                         // 탄젠트
```

**역삼각함수**
```
double asin(double x);                        // 아크사인
double acos(double x);                        // 아크코사인
double atan(double x);                        // 아크탄젠트
double atan2(double y, double x);             // 두 인수 아크탄젠트
```

**쌍곡함수**
```
double sinh(double x);                        // 쌍곡사인
double cosh(double x);                        // 쌍곡코사인
double tanh(double x);                        // 쌍곡탄젠트
```

#### 지수 및 로그

**지수 함수**
```
double exp(double x);                         // e^x
double exp2(double x);                        // 2^x (C99)
double expm1(double x);                       // e^x - 1 (C99)
```

**로그 함수**
```
double log(double x);                         // 자연로그 (ln)
double log10(double x);                       // 상용로그 (log₁₀)
double log2(double x);                        // 이진로그 (log₂) (C99)
double log1p(double x);                       // ln(1+x) (C99)
```

**거듭제곱**
```
double pow(double base, double exp);          // base^exp
double sqrt(double x);                        // 제곱근
double cbrt(double x);                        // 세제곱근 (C99)
double hypot(double x, double y);             // sqrt(x²+y²) (C99)
```

#### 반올림 및 나머지

**반올림**
```
double ceil(double x);                        // 천장 (올림)
double floor(double x);                       // 바닥 (내림)
double round(double x);                       // 반올림 (C99)
double trunc(double x);                       // 소수점 버림 (C99)
```

**나머지**
```
double fmod(double x, double y);              // 부동소수점 나머지
double remainder(double x, double y);         // IEEE 나머지 (C99)
```

#### 기타 함수

**절댓값**
```
double fabs(double x);                        // 부동소수점 절댓값
```

**부호 관련**
```
double copysign(double x, double y);          // x의 크기에 y의 부호 (C99)
```

**비교**
```
double fmax(double x, double y);              // 최댓값 (C99)
double fmin(double x, double y);              // 최솟값 (C99)
```

### 5. `<ctype.h>` - 문자 분류 및 변환

#### 문자 분류

**문자 타입 확인**
```
int isalpha(int c);                           // 알파벳인지
int isdigit(int c);                           // 숫자인지
int isalnum(int c);                           // 알파벳 또는 숫자인지
int isspace(int c);                           // 공백 문자인지
int ispunct(int c);                           // 구두점인지
int isupper(int c);                           // 대문자인지
int islower(int c);                           // 소문자인지
int isxdigit(int c);                          // 16진 숫자인지
int iscntrl(int c);                           // 제어 문자인지
int isprint(int c);                           // 출력 가능한지
int isgraph(int c);                           // 그래픽 문자인지
```

**반환값**: 0 (거짓) 또는 0이 아닌 값 (참)

#### 문자 변환

**대소문자 변환**
```
int toupper(int c);                           // 대문자로 변환
int tolower(int c);                           // 소문자로 변환
```

### 6. `<time.h>` - 시간 관련 함수

#### 시간 타입

**기본 타입**
```
time_t          // 시간 값 (보통 1970년 1월 1일부터의 초)
clock_t         // 프로세서 시간
struct tm       // 분해된 시간 구조체
```

**tm 구조체**
```
struct tm {
    int tm_sec;     // 초 (0-59)
    int tm_min;     // 분 (0-59)
    int tm_hour;    // 시 (0-23)
    int tm_mday;    // 일 (1-31)
    int tm_mon;     // 월 (0-11)
    int tm_year;    // 년 (1900년부터)
    int tm_wday;    // 요일 (0-6, 일요일=0)
    int tm_yday;    // 연중 일수 (0-365)
    int tm_isdst;   // 일광절약시간 플래그
};
```

#### 시간 함수

**현재 시간**
```
time_t time(time_t *timer);                   // 현재 시간
clock_t clock(void);                          // 프로세서 시간
```

**시간 변환**
```
struct tm *localtime(const time_t *timer);    // 지역 시간으로 변환
struct tm *gmtime(const time_t *timer);       // UTC 시간으로 변환
time_t mktime(struct tm *timeptr);            // tm을 time_t로 변환
```

**시간 포맷팅**
```
char *asctime(const struct tm *timeptr);      // 문자열로 변환
char *ctime(const time_t *timer);             // time_t를 문자열로
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr);
```

**strftime 포맷 지정자**

| 지정자 | 의미 | 예시 |
|--------|------|------|
| `%Y` | 4자리 년도 | 2024 |
| `%y` | 2자리 년도 | 24 |
| `%m` | 월 (01-12) | 03 |
| `%d` | 일 (01-31) | 15 |
| `%H` | 시 (00-23) | 14 |
| `%M` | 분 (00-59) | 30 |
| `%S` | 초 (00-59) | 45 |
| `%A` | 요일 (전체) | Monday |
| `%a` | 요일 (축약) | Mon |
| `%B` | 월명 (전체) | March |
| `%b` | 월명 (축약) | Mar |

### 7. `<stdarg.h>` - 가변 인수

#### 가변 인수 매크로

**타입 및 매크로**
```
va_list         // 가변 인수 리스트 타입

void va_start(va_list ap, last);    // 가변 인수 시작
type va_arg(va_list ap, type);      // 다음 인수 가져오기
void va_end(va_list ap);            // 가변 인수 정리
void va_copy(va_list dest, va_list src);  // va_list 복사 (C99)
```

### 8. `<errno.h>` - 오류 처리

#### 오류 번호

**전역 변수**
```
extern int errno;                             // 마지막 오류 번호
```

**주요 오류 상수**

| 상수 | 값 | 의미 |
|------|----|----- |
| `EDOM` | 33 | 수학 함수 정의역 오류 |
| `ERANGE` | 34 | 수학 함수 치역 오류 |
| `EILSEQ` | - | 잘못된 멀티바이트 문자 (C99) |

### 9. C99/C11 추가 함수들

#### `<stdint.h>` - 정수 타입

**고정 크기 정수 타입**
```
int8_t, int16_t, int32_t, int64_t           // 부호 있는 정수
uint8_t, uint16_t, uint32_t, uint64_t       // 부호 없는 정수

int_least8_t, int_least16_t, ...            // 최소 크기 정수
int_fast8_t, int_fast16_t, ...              // 빠른 정수

intmax_t, uintmax_t                         // 최대 크기 정수
intptr_t, uintptr_t                         // 포인터 크기 정수
```

#### `<stdbool.h>` - 불린 타입

**불린 관련**
```
bool            // 불린 타입 (typedef)
true            // 참 (1)
false           // 거짓 (0)
```

#### `<complex.h>` - 복소수

**복소수 타입**
```
float complex, double complex, long double complex
```

**복소수 함수**
```
double creal(double complex z);               // 실수부
double cimag(double complex z);               // 허수부
double cabs(double complex z);                // 절댓값
double carg(double complex z);                // 편각
```

## 함수 사용 시 주의사항

### 1. 메모리 관리

**malloc/free 쌍**
- malloc으로 할당한 메모리는 반드시 free로 해제
- free 후에는 포인터 사용 금지
- NULL 포인터에 대한 free는 안전함

### 2. 문자열 함수

**버퍼 오버플로우 방지**
- strcpy 대신 strncpy 사용 고려
- 목적지 버퍼 크기 확인
- 널 종료 문자 보장

### 3. 입출력 함수

**오류 검사**
- fopen 반환값이 NULL인지 확인
- fread/fwrite 반환값으로 실제 처리된 크기 확인
- 파일 작업 후 fclose로 정리

### 4. 수학 함수

**정의역 확인**
- sqrt는 음수에 대해 정의되지 않음
- log는 0 이하 값에 대해 정의되지 않음
- 오류 시 errno 설정됨

### 5. 타입 안전성

**적절한 타입 사용**
- size_t는 배열 인덱스와 크기에 사용
- time_t는 시간 값에 사용
- 타입 캐스팅 시 주의

## 마무리

표준 라이브러리는 C 프로그래밍의 핵심 도구입니다.

### 효율적 활용법

1. **적절한 함수 선택**: 요구사항에 맞는 함수 사용
2. **오류 처리**: 반환값과 errno 확인
3. **성능 고려**: 반복적 호출 시 최적화 고려
4. **이식성**: 표준 함수 우선 사용

정확한 라이브러리 함수 사용은 안전하고 효율적인 프로그램의 기초입니다.