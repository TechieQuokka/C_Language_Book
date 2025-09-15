# 부록 E. 디버깅 도구 사용법

> **"디버깅은 코드를 작성하는 것보다 두 배는 어렵다. 따라서 최대한 영리하게 코드를 작성했다면, 디버깅할 때는 충분히 영리하지 못할 것이다."** - Brian Kernighan

## 개요

효과적인 디버깅은 프로그램 개발에서 가장 중요한 기술 중 하나입니다. 이 부록에서는 C 프로그램 디버깅을 위한 다양한 도구들의 사용법을 체계적으로 설명하며, 실전에서 바로 적용할 수 있는 디버깅 전략과 기법들을 제공합니다.

## 디버깅 기본 개념

### 디버깅 프로세스

```
문제 발견 → 재현 → 분석 → 가설 수립 → 검증 → 수정 → 테스트
    ↑                                                        ↓
    ←←←←←←←←←← 회귀 테스트 및 재검증 ←←←←←←←←←←←←←←←←
```

### 버그의 분류

#### 1. 컴파일 시간 오류
- **구문 오류**: 문법 위반
- **타입 오류**: 타입 불일치
- **링크 오류**: 함수나 변수 미정의

#### 2. 런타임 오류
- **세그멘테이션 폴트**: 잘못된 메모리 접근
- **버퍼 오버플로우**: 배열 경계 초과
- **메모리 누수**: 할당된 메모리 미해제
- **무한 루프**: 종료되지 않는 반복

#### 3. 논리 오류
- **잘못된 알고리즘**: 로직 자체의 오류
- **경계 조건 오류**: 특수한 경우 처리 미흡
- **초기화 오류**: 변수 초기화 누락

## GDB (GNU Debugger) 완전 가이드

### GDB 기본 사용법

#### 프로그램 준비
```bash
# 디버그 정보를 포함하여 컴파일
gcc -g -O0 -Wall -o program program.c

# 최적화 없이 컴파일 (디버깅 용이)
gcc -g -O0 -DDEBUG program.c -o program
```

#### GDB 시작하기
```bash
# 프로그램과 함께 GDB 시작
gdb ./program

# 이미 실행 중인 프로세스에 연결
gdb -p <pid>

# 코어 덤프 분석
gdb ./program core

# 명령행 인수와 함께
gdb --args ./program arg1 arg2
```

### 기본 GDB 명령어

#### 프로그램 실행 제어

**실행 관련**
```gdb
(gdb) run [arguments]              # 프로그램 실행
(gdb) r                            # run의 축약형
(gdb) start                        # main에서 정지
(gdb) continue                     # 실행 계속
(gdb) c                            # continue의 축약형
(gdb) step                         # 한 줄 실행 (함수 내부 진입)
(gdb) s                            # step의 축약형
(gdb) next                         # 한 줄 실행 (함수 호출 건너뛰기)
(gdb) n                            # next의 축약형
(gdb) finish                       # 현재 함수 종료까지 실행
(gdb) until                        # 현재 줄을 벗어날 때까지 실행
(gdb) kill                         # 프로그램 종료
```

**중단점 관리**
```gdb
(gdb) break main                   # main 함수에 중단점
(gdb) b main                       # break의 축약형
(gdb) break 15                     # 15번 줄에 중단점
(gdb) break file.c:25              # 특정 파일의 25번 줄
(gdb) break function_name          # 함수 시작점에 중단점
(gdb) break *0x400123              # 특정 주소에 중단점

# 조건부 중단점
(gdb) break 20 if i == 5           # i가 5일 때만 정지
(gdb) break func if strcmp(name, "test") == 0

# 임시 중단점
(gdb) tbreak main                  # 한 번만 정지하는 중단점

# 중단점 관리
(gdb) info breakpoints             # 중단점 목록
(gdb) disable 1                    # 1번 중단점 비활성화
(gdb) enable 1                     # 1번 중단점 활성화
(gdb) delete 1                     # 1번 중단점 삭제
(gdb) clear                        # 현재 줄의 중단점 삭제
(gdb) delete                       # 모든 중단점 삭제
```

#### 변수 및 메모리 검사

**변수 값 출력**
```gdb
(gdb) print variable               # 변수 값 출력
(gdb) p variable                   # print의 축약형
(gdb) print *pointer               # 포인터가 가리키는 값
(gdb) print array[5]               # 배열 요소
(gdb) print struct.member          # 구조체 멤버

# 형식 지정자
(gdb) print/x variable             # 16진수로 출력
(gdb) print/d variable             # 10진수로 출력
(gdb) print/o variable             # 8진수로 출력
(gdb) print/t variable             # 2진수로 출력
(gdb) print/c variable             # 문자로 출력
(gdb) print/f variable             # 부동소수점으로 출력

# 배열 출력
(gdb) print array@10               # 배열의 처음 10개 요소
(gdb) print *array@10              # 포인터부터 10개 요소
```

**변수 값 변경**
```gdb
(gdb) set variable i = 10          # 변수 값 변경
(gdb) set variable ptr = 0         # 포인터 값 변경
(gdb) set {int}0x400000 = 5        # 특정 주소의 값 변경
```

**메모리 검사**
```gdb
(gdb) x/10x $rsp                   # 스택 포인터부터 10개 워드를 16진수로
(gdb) x/10i main                   # main 함수의 어셈블리 10줄
(gdb) x/s 0x400000                 # 특정 주소의 문자열
(gdb) x/10c array                  # 배열을 문자로 10개

# 메모리 검사 형식
# /<count><format><size>
# count: 출력할 단위 수
# format: x(hex), d(decimal), u(unsigned), o(octal), t(binary),
#         a(address), c(char), f(float), s(string), i(instruction)
# size: b(byte), h(halfword), w(word), g(giant, 8bytes)
```

#### 스택 추적 및 프레임

**호출 스택**
```gdb
(gdb) backtrace                    # 전체 호출 스택
(gdb) bt                           # backtrace의 축약형
(gdb) bt 5                         # 상위 5개 프레임만
(gdb) where                        # 현재 위치 정보

# 스택 프레임 이동
(gdb) frame 2                      # 2번 프레임으로 이동
(gdb) f 2                          # frame의 축약형
(gdb) up                           # 상위 프레임으로
(gdb) down                         # 하위 프레임으로

# 프레임 정보
(gdb) info frame                   # 현재 프레임 정보
(gdb) info locals                  # 지역 변수들
(gdb) info args                    # 함수 인수들
```

#### 소스 코드 보기

**코드 출력**
```gdb
(gdb) list                         # 현재 위치 주변 코드
(gdb) l                            # list의 축약형
(gdb) list 15                      # 15번 줄 주변
(gdb) list main                    # main 함수 주변
(gdb) list file.c:20               # 특정 파일의 20번 줄
(gdb) list 10,20                   # 10번부터 20번 줄까지

# 역어셈블리
(gdb) disassemble main             # main 함수 어셈블리
(gdb) disas main                   # disassemble의 축약형
(gdb) disas 0x400000,0x400010      # 주소 범위 역어셈블리
```

### 고급 GDB 기능

#### 감시점 (Watchpoints)

**변수 변경 감시**
```gdb
(gdb) watch variable               # 변수가 변경될 때 정지
(gdb) watch *0x400000              # 특정 주소 값 변경 감시
(gdb) watch expr                   # 표현식 값 변경 감시

# 읽기 감시점
(gdb) rwatch variable              # 변수를 읽을 때 정지
(gdb) awatch variable              # 읽기/쓰기 모두 감시

# 감시점 관리
(gdb) info watchpoints             # 감시점 목록
(gdb) delete watchpoint 1          # 감시점 삭제
```

#### 신호 처리

**신호 제어**
```gdb
(gdb) info signals                 # 신호 처리 상태
(gdb) handle SIGSEGV stop print    # SIGSEGV 시 정지하고 출력
(gdb) handle SIGINT nostop noprint # SIGINT 무시
(gdb) signal SIGUSR1               # 프로그램에 신호 전송
```

#### 스레드 디버깅

**멀티스레드 프로그램**
```gdb
(gdb) info threads                 # 스레드 목록
(gdb) thread 2                     # 2번 스레드로 전환
(gdb) thread apply all bt          # 모든 스레드의 백트레이스
(gdb) set scheduler-locking on     # 현재 스레드만 실행
(gdb) set non-stop on              # 논스톱 모드 활성화
```

#### 매크로 및 스크립팅

**GDB 매크로**
```gdb
# .gdbinit 파일에 정의
define printlist
    set $node = $arg0
    while $node
        print $node->data
        set $node = $node->next
    end
end

# 사용
(gdb) printlist head
```

**GDB 스크립트**
```bash
# script.gdb
break main
run
continue
quit

# 스크립트 실행
gdb -x script.gdb ./program
```

### GDB TUI (Text User Interface)

**TUI 모드**
```gdb
(gdb) tui enable                   # TUI 모드 활성화
(gdb) layout src                   # 소스 창 표시
(gdb) layout asm                   # 어셈블리 창 표시
(gdb) layout split                 # 소스와 어셈블리 분할
(gdb) layout regs                  # 레지스터 창 추가

# 창 전환
Ctrl+X, A                          # TUI 모드 토글
Ctrl+X, 1                          # 단일 창
Ctrl+X, 2                          # 분할 창
Ctrl+L                             # 화면 새로고침
```

## Valgrind 메모리 디버깅

### Valgrind 개요

Valgrind는 Linux와 macOS에서 메모리 오류를 검출하는 강력한 도구입니다.

#### 설치
```bash
# Ubuntu/Debian
sudo apt install valgrind

# CentOS/RHEL
sudo yum install valgrind

# macOS (Homebrew)
brew install valgrind
```

### Memcheck - 메모리 오류 검출

#### 기본 사용법
```bash
# 기본 메모리 검사
valgrind ./program

# 상세한 정보
valgrind --tool=memcheck --leak-check=full ./program

# 오류 발생 시 상세 정보
valgrind --tool=memcheck --track-origins=yes ./program

# 도달 가능한 메모리도 누수로 표시
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./program
```

#### 주요 옵션

**메모리 누수 검사**
```bash
--leak-check=no|summary|yes|full
    no: 누수 검사 안함
    summary: 요약만 표시
    yes: 각 누수 표시
    full: 누수 위치 상세 정보

--show-leak-kinds=kind1,kind2,...
    definite: 확실한 누수
    indirect: 간접적 누수
    possible: 가능한 누수
    reachable: 도달 가능한 누수
```

**오류 추적**
```bash
--track-origins=yes              # 초기화되지 않은 값 추적
--track-fds=yes                  # 파일 디스크립터 누수 추적
--malloc-fill=0xAB               # malloc된 메모리를 특정 값으로 채움
--free-fill=0xCD                 # free된 메모리를 특정 값으로 채움
```

### Valgrind 출력 해석

#### 메모리 누수 보고서

```
==12345== HEAP SUMMARY:
==12345==     in use at exit: 72,704 bytes in 1 blocks
==12345==   total heap usage: 1 allocs, 0 frees, 72,704 bytes allocated
==12345==
==12345== 72,704 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12345==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==12345==    by 0x400537: main (test.c:6)
```

**해석**:
- 72,704 바이트가 확실히 누수됨
- main 함수의 test.c:6에서 malloc 호출
- 해당 메모리가 free되지 않음

#### 잘못된 메모리 접근

```
==12345== Invalid write of size 4
==12345==    at 0x400544: main (test.c:8)
==12345==  Address 0x520004c is 0 bytes after a block of size 40 alloc'd
==12345==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==12345==    by 0x400537: main (test.c:6)
```

**해석**:
- 4바이트 크기의 잘못된 쓰기
- 할당된 블록(40바이트) 바로 뒤의 0바이트 위치
- 배열 경계 초과 접근

### Callgrind - 성능 프로파일링

#### 프로파일링 실행
```bash
valgrind --tool=callgrind ./program
```

#### 결과 분석
```bash
# 함수별 호출 횟수와 비용
callgrind_annotate callgrind.out.12345

# 시각화 도구 (KCachegrind)
kcachegrind callgrind.out.12345
```

### Cachegrind - 캐시 성능 분석

#### 캐시 분석
```bash
valgrind --tool=cachegrind ./program
```

#### 결과 해석
```
I   refs:      1,000,000   # 명령어 참조
I1  misses:        1,000   # L1 명령어 캐시 미스
LLi misses:          100   # 최종 레벨 명령어 캐시 미스
I1  miss rate:      0.10%  # L1 명령어 캐시 미스율

D   refs:        500,000   # 데이터 참조
D1  misses:        5,000   # L1 데이터 캐시 미스
LLd misses:          500   # 최종 레벨 데이터 캐시 미스
D1  miss rate:      1.00%  # L1 데이터 캐시 미스율
```

## AddressSanitizer (ASan)

### AddressSanitizer 개요

GCC와 Clang에 내장된 빠른 메모리 오류 검출기입니다.

#### 컴파일 옵션
```bash
# 기본 사용
gcc -fsanitize=address -g -o program program.c

# 최적화와 함께
gcc -fsanitize=address -O1 -g -fno-omit-frame-pointer -o program program.c

# 추가 검사
gcc -fsanitize=address -fsanitize=undefined -g -o program program.c
```

### ASan 환경 변수

#### 주요 옵션
```bash
# 오류 발생 시 즉시 중단
export ASAN_OPTIONS=halt_on_error=1

# 스택 정보 출력
export ASAN_OPTIONS=print_stacktrace=1

# 메모리 매핑 정보
export ASAN_OPTIONS=mmap_limit_mb=2048

# 여러 옵션 조합
export ASAN_OPTIONS=halt_on_error=1:check_initialization_order=1:strict_init_order=1
```

### ASan 출력 해석

#### 버퍼 오버플로우
```
=================================================================
==12345==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000000018 at pc 0x00000040084d bp 0x7fff8dbf6e60 sp 0x7fff8dbf6e58
WRITE of size 4 at 0x602000000018 thread T0
    #0 0x40084c in main /tmp/test.c:8:10
    #1 0x7f8b1ecb2f44 in __libc_start_main
    #2 0x400748 in _start

0x602000000018 is located 0 bytes to the right of 24-byte region [0x602000000000,0x602000000018)
allocated by thread T0 here:
    #0 0x4a1718 in __interceptor_malloc
    #1 0x4007d3 in main /tmp/test.c:6:12
    #2 0x7f8b1ecb2f44 in __libc_start_main
    #3 0x400748 in _start
```

**해석**:
- 힙 버퍼 오버플로우 발생
- 24바이트 할당된 메모리의 오른쪽 0바이트 위치에 4바이트 쓰기 시도
- 스택 추적으로 정확한 위치 파악 가능

## UndefinedBehaviorSanitizer (UBSan)

### UBSan 사용법

#### 컴파일 옵션
```bash
# 기본 미정의 동작 검사
gcc -fsanitize=undefined -g -o program program.c

# 특정 검사만
gcc -fsanitize=integer-divide-by-zero,null -g -o program program.c

# 모든 검사
gcc -fsanitize=undefined -fsanitize=float-divide-by-zero -g -o program program.c
```

#### 검사 항목

**수치 오버플로우**
```c
int overflow_example() {
    int max = INT_MAX;
    return max + 1;  // UBSan이 감지
}
```

**널 포인터 역참조**
```c
void null_deref_example() {
    int *p = NULL;
    *p = 42;  // UBSan이 감지
}
```

**배열 경계 초과**
```c
void bounds_example() {
    int arr[10];
    arr[15] = 42;  // UBSan이 감지
}
```

## 정적 분석 도구

### Clang Static Analyzer

#### 사용법
```bash
# 스캔 빌드 실행
scan-build gcc -o program program.c

# 결과를 HTML로 생성
scan-build --view gcc -o program program.c

# 특정 검사만
scan-build --use-analyzer /usr/bin/clang gcc -o program program.c
```

#### 주요 검사 항목
- 메모리 누수
- 널 포인터 역참조
- 버퍼 오버플로우
- 데드 코드
- 초기화되지 않은 변수 사용

### Cppcheck

#### 설치 및 사용
```bash
# 설치
sudo apt install cppcheck

# 기본 검사
cppcheck program.c

# 상세 검사
cppcheck --enable=all --std=c99 --platform=unix64 program.c

# XML 출력
cppcheck --xml --xml-version=2 program.c 2> report.xml
```

#### 검사 범주
```bash
--enable=error          # 오류만
--enable=warning        # 경고 포함
--enable=style          # 스타일 문제
--enable=performance    # 성능 문제
--enable=portability    # 이식성 문제
--enable=all            # 모든 검사
```

## 로그 기반 디버깅

### 디버그 매크로

#### 조건부 디버그 출력
```c
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d:%s(): " fmt "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif

// 사용 예
DEBUG_PRINT("Variable value: %d", variable);
```

#### 어서션 매크로
```c
#include <assert.h>

void function(int *ptr) {
    assert(ptr != NULL);  // 조건이 거짓이면 프로그램 중단
    *ptr = 42;
}

// 커스텀 어서션
#ifdef DEBUG
    #define ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                fprintf(stderr, "Assertion failed: %s\n", message); \
                fprintf(stderr, "File: %s, Line: %d\n", __FILE__, __LINE__); \
                abort(); \
            } \
        } while(0)
#else
    #define ASSERT(condition, message)
#endif
```

### 로깅 시스템

#### 간단한 로깅 구현
```c
typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

void log_message(LogLevel level, const char *format, ...) {
    const char *level_strings[] = {"ERROR", "WARNING", "INFO", "DEBUG"};

    va_list args;
    va_start(args, format);

    fprintf(stderr, "[%s] ", level_strings[level]);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
}

// 편의 매크로
#define LOG_ERROR(fmt, ...) log_message(LOG_ERROR, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) log_message(LOG_INFO, fmt, ##__VA_ARGS__)
```

## 플랫폼별 디버깅 도구

### Windows 디버깅

#### Visual Studio 디버거

**기본 사용법**
- F9: 중단점 설정/해제
- F5: 디버깅 시작
- F10: 한 줄씩 실행 (Step Over)
- F11: 한 줄씩 실행 (Step Into)
- Shift+F11: 함수에서 나가기 (Step Out)
- Ctrl+F5: 디버깅 없이 실행

**감시 창 활용**
- 로컬 변수 자동 표시
- 감시 식 추가 가능
- 메모리 창으로 원시 메모리 보기
- 호출 스택 창으로 함수 호출 추적

#### Dr. Memory (Windows용 Valgrind 대안)

**설치 및 사용**
```cmd
# Dr. Memory 다운로드 후 설치
drmemory.exe -batch -- program.exe

# 상세 보고서
drmemory.exe -check_uninitialized -batch -- program.exe
```

### macOS 디버깅

#### LLDB 사용법

**기본 명령어**
```lldb
# 프로그램 로드
(lldb) file program

# 중단점 설정
(lldb) breakpoint set --name main
(lldb) b main

# 실행
(lldb) run
(lldb) r

# 단계별 실행
(lldb) step
(lldb) s
(lldb) next
(lldb) n

# 변수 출력
(lldb) print variable
(lldb) p variable

# 메모리 검사
(lldb) memory read 0x100000000
(lldb) x 0x100000000
```

#### Instruments

**사용법**
1. Xcode에서 Product → Profile 선택
2. 템플릿 선택 (Leaks, Time Profiler 등)
3. 프로파일링 실행 및 분석

## 디버깅 전략 및 모범 사례

### 체계적 디버깅 접근법

#### 1. 문제 재현
```c
// 최소 재현 케이스 작성
int minimal_test_case() {
    // 문제를 재현하는 최소한의 코드
    int *ptr = malloc(sizeof(int));
    free(ptr);
    *ptr = 42;  // 댕글링 포인터 사용
    return 0;
}
```

#### 2. 이분 탐색 디버깅
```c
// 문제 발생 구간을 반으로 줄여가며 찾기
void binary_search_debug() {
    printf("Checkpoint 1\n");  // 여기까지는 정상
    // ... 코드 블록 1

    printf("Checkpoint 2\n");  // 여기서 문제 발생?
    // ... 코드 블록 2

    printf("Checkpoint 3\n");
    // ... 코드 블록 3
}
```

#### 3. 고무 오리 디버깅
코드를 다른 사람(또는 고무 오리)에게 설명하면서 논리적 오류를 찾는 방법

### 일반적인 버그 패턴과 검출

#### 메모리 관련 버그

**댕글링 포인터**
```c
// 잘못된 예
int *func() {
    int local = 42;
    return &local;  // 지역 변수 주소 반환
}

// 올바른 예
int *func() {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    return ptr;
}
```

**이중 해제**
```c
// 잘못된 예
void double_free_bug() {
    int *ptr = malloc(sizeof(int));
    free(ptr);
    free(ptr);  // 이중 해제
}

// 올바른 예
void safe_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}
```

#### 동시성 버그

**경쟁 조건**
```c
// 문제가 있는 코드
int counter = 0;

void increment() {
    counter++;  // 원자적이지 않음
}

// 안전한 코드
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void safe_increment() {
    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
}
```

### 성능 디버깅

#### 프로파일링 도구 비교

| 도구 | 플랫폼 | 특징 | 사용 용도 |
|------|--------|------|----------|
| **gprof** | Linux/Unix | 함수별 실행 시간 | 함수 단위 성능 분석 |
| **perf** | Linux | 하드웨어 이벤트 | 시스템 레벨 성능 분석 |
| **Valgrind/Callgrind** | Linux/macOS | 정확한 명령어 수 | 정밀한 성능 분석 |
| **Intel VTune** | x86 플랫폼 | 하드웨어 최적화 | 프로덕션 성능 분석 |
| **Instruments** | macOS | 통합 프로파일링 | macOS 앱 최적화 |

#### 병목 지점 식별

**CPU 바운드 vs I/O 바운드**
```bash
# CPU 사용률 모니터링
top -p <pid>

# I/O 대기 시간 측정
iostat -x 1

# 시스템 콜 추적
strace -c ./program
```

### 원격 디버깅

#### GDB 서버 사용

**타겟 시스템 (디버깅 대상)**
```bash
# gdbserver 실행
gdbserver :1234 ./program
```

**호스트 시스템 (개발 환경)**
```bash
# 원격 연결
gdb ./program
(gdb) target remote target_ip:1234
(gdb) continue
```

## 디버깅 도구 통합

### IDE 통합

#### Visual Studio Code 설정

**launch.json 설정**
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C Debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/program",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

### 자동화된 디버깅

#### 테스트 스위트와 연동

**CTest 설정**
```cmake
enable_testing()

add_test(NAME unit_tests COMMAND unit_test_runner)
add_test(NAME memory_test
         COMMAND valgrind --error-exitcode=1 --leak-check=full ./program)
add_test(NAME static_analysis
         COMMAND cppcheck --error-exitcode=1 ${CMAKE_SOURCE_DIR}/src)
```

#### 지속적 통합에서 디버깅

**GitHub Actions 예시**
```yaml
- name: Run tests with Valgrind
  run: |
    valgrind --error-exitcode=1 --leak-check=full ./tests

- name: Upload Valgrind results
  if: failure()
  uses: actions/upload-artifact@v2
  with:
    name: valgrind-report
    path: valgrind-report.txt
```

## 마무리

효과적인 디버깅을 위한 핵심 원칙:

### 예방이 최선
1. **코딩 표준** 준수
2. **정적 분석** 도구 활용
3. **단위 테스트** 작성
4. **코드 리뷰** 실시

### 체계적 접근
1. **문제 재현** 및 최소화
2. **가설 수립** 및 검증
3. **도구 활용** 극대화
4. **문서화** 및 학습

### 도구 선택 가이드

| 문제 유형 | 추천 도구 | 플랫폼 |
|-----------|-----------|--------|
| **메모리 오류** | Valgrind, ASan | Linux/macOS |
| **성능 문제** | gprof, perf, VTune | 플랫폼별 |
| **논리 오류** | GDB, LLDB | 모든 플랫폼 |
| **정적 분석** | Clang Analyzer, Cppcheck | 모든 플랫폼 |
| **동시성 문제** | ThreadSanitizer, Helgrind | Linux |

디버깅 기술은 경험을 통해 발전됩니다. 다양한 도구를 실제 프로젝트에 적용하면서 자신만의 디버깅 전략을 개발하시기 바랍니다.