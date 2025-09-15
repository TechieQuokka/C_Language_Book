# 부록 C. ASCII 코드표 및 데이터 타입 크기

> **"컴퓨터는 숫자로 모든 것을 표현한다. 문자 인코딩과 데이터 타입의 이해는 시스템 프로그래밍의 기초다."**

## 개요

ASCII 코드표와 C언어 데이터 타입의 크기 및 범위를 체계적으로 정리한 참조표입니다. 문자 처리, 바이너리 데이터 조작, 플랫폼별 이식성 고려 시 필수적인 정보를 제공합니다.

## ASCII 코드표

### ASCII (American Standard Code for Information Interchange)

ASCII는 7비트로 구성되어 총 128개(0-127)의 문자를 표현합니다.

### 제어 문자 (0-31)

| 10진 | 16진 | 8진 | 문자 | 이름 | 설명 |
|------|------|-----|------|------|------|
| 0 | 00 | 000 | NUL | Null | 널 문자 (문자열 끝) |
| 1 | 01 | 001 | SOH | Start Of Heading | 헤딩 시작 |
| 2 | 02 | 002 | STX | Start Of Text | 텍스트 시작 |
| 3 | 03 | 003 | ETX | End Of Text | 텍스트 끝 |
| 4 | 04 | 004 | EOT | End Of Transmission | 전송 끝 |
| 5 | 05 | 005 | ENQ | Enquiry | 조회 |
| 6 | 06 | 006 | ACK | Acknowledgement | 승인 |
| 7 | 07 | 007 | BEL | Bell | 벨 소리 (`\a`) |
| 8 | 08 | 010 | BS | Backspace | 백스페이스 (`\b`) |
| 9 | 09 | 011 | HT | Horizontal Tab | 수평 탭 (`\t`) |
| 10 | 0A | 012 | LF | Line Feed | 줄 바꿈 (`\n`) |
| 11 | 0B | 013 | VT | Vertical Tab | 수직 탭 (`\v`) |
| 12 | 0C | 014 | FF | Form Feed | 폼 피드 (`\f`) |
| 13 | 0D | 015 | CR | Carriage Return | 캐리지 리턴 (`\r`) |
| 14 | 0E | 016 | SO | Shift Out | 시프트 아웃 |
| 15 | 0F | 017 | SI | Shift In | 시프트 인 |
| 16 | 10 | 020 | DLE | Data Link Escape | 데이터 링크 이스케이프 |
| 17 | 11 | 021 | DC1 | Device Control 1 | 장치 제어 1 (XON) |
| 18 | 12 | 022 | DC2 | Device Control 2 | 장치 제어 2 |
| 19 | 13 | 023 | DC3 | Device Control 3 | 장치 제어 3 (XOFF) |
| 20 | 14 | 024 | DC4 | Device Control 4 | 장치 제어 4 |
| 21 | 15 | 025 | NAK | Negative Acknowledgement | 부정 응답 |
| 22 | 16 | 026 | SYN | Synchronous Idle | 동기 아이들 |
| 23 | 17 | 027 | ETB | End Of Transmission Block | 전송 블록 끝 |
| 24 | 18 | 030 | CAN | Cancel | 취소 |
| 25 | 19 | 031 | EM | End Of Medium | 매체 끝 |
| 26 | 1A | 032 | SUB | Substitute | 대체 |
| 27 | 1B | 033 | ESC | Escape | 이스케이프 |
| 28 | 1C | 034 | FS | File Separator | 파일 구분자 |
| 29 | 1D | 035 | GS | Group Separator | 그룹 구분자 |
| 30 | 1E | 036 | RS | Record Separator | 레코드 구분자 |
| 31 | 1F | 037 | US | Unit Separator | 단위 구분자 |

### 출력 가능한 문자 (32-126)

#### 공백 및 특수 문자 (32-47)

| 10진 | 16진 | 8진 | 문자 | 이름 |
|------|------|-----|------|------|
| 32 | 20 | 040 | (공백) | Space |
| 33 | 21 | 041 | ! | Exclamation Mark |
| 34 | 22 | 042 | " | Quotation Mark |
| 35 | 23 | 043 | # | Number Sign |
| 36 | 24 | 044 | $ | Dollar Sign |
| 37 | 25 | 045 | % | Percent Sign |
| 38 | 26 | 046 | & | Ampersand |
| 39 | 27 | 047 | ' | Apostrophe |
| 40 | 28 | 050 | ( | Left Parenthesis |
| 41 | 29 | 051 | ) | Right Parenthesis |
| 42 | 2A | 052 | * | Asterisk |
| 43 | 2B | 053 | + | Plus Sign |
| 44 | 2C | 054 | , | Comma |
| 45 | 2D | 055 | - | Hyphen-Minus |
| 46 | 2E | 056 | . | Full Stop |
| 47 | 2F | 057 | / | Solidus |

#### 숫자 (48-57)

| 10진 | 16진 | 8진 | 문자 | 이름 |
|------|------|-----|------|------|
| 48 | 30 | 060 | 0 | Digit Zero |
| 49 | 31 | 061 | 1 | Digit One |
| 50 | 32 | 062 | 2 | Digit Two |
| 51 | 33 | 063 | 3 | Digit Three |
| 52 | 34 | 064 | 4 | Digit Four |
| 53 | 35 | 065 | 5 | Digit Five |
| 54 | 36 | 066 | 6 | Digit Six |
| 55 | 37 | 067 | 7 | Digit Seven |
| 56 | 38 | 070 | 8 | Digit Eight |
| 57 | 39 | 071 | 9 | Digit Nine |

#### 특수 문자 및 대문자 (58-90)

| 10진 | 16진 | 8진 | 문자 | 이름 |
|------|------|-----|------|------|
| 58 | 3A | 072 | : | Colon |
| 59 | 3B | 073 | ; | Semicolon |
| 60 | 3C | 074 | < | Less-Than Sign |
| 61 | 3D | 075 | = | Equals Sign |
| 62 | 3E | 076 | > | Greater-Than Sign |
| 63 | 3F | 077 | ? | Question Mark |
| 64 | 40 | 100 | @ | Commercial At |
| 65 | 41 | 101 | A | Latin Capital Letter A |
| 66 | 42 | 102 | B | Latin Capital Letter B |
| 67 | 43 | 103 | C | Latin Capital Letter C |
| 68 | 44 | 104 | D | Latin Capital Letter D |
| 69 | 45 | 105 | E | Latin Capital Letter E |
| 70 | 46 | 106 | F | Latin Capital Letter F |
| 71 | 47 | 107 | G | Latin Capital Letter G |
| 72 | 48 | 110 | H | Latin Capital Letter H |
| 73 | 49 | 111 | I | Latin Capital Letter I |
| 74 | 4A | 112 | J | Latin Capital Letter J |
| 75 | 4B | 113 | K | Latin Capital Letter K |
| 76 | 4C | 114 | L | Latin Capital Letter L |
| 77 | 4D | 115 | M | Latin Capital Letter M |
| 78 | 4E | 116 | N | Latin Capital Letter N |
| 79 | 4F | 117 | O | Latin Capital Letter O |
| 80 | 50 | 120 | P | Latin Capital Letter P |
| 81 | 51 | 121 | Q | Latin Capital Letter Q |
| 82 | 52 | 122 | R | Latin Capital Letter R |
| 83 | 53 | 123 | S | Latin Capital Letter S |
| 84 | 54 | 124 | T | Latin Capital Letter T |
| 85 | 55 | 125 | U | Latin Capital Letter U |
| 86 | 56 | 126 | V | Latin Capital Letter V |
| 87 | 57 | 127 | W | Latin Capital Letter W |
| 88 | 58 | 130 | X | Latin Capital Letter X |
| 89 | 59 | 131 | Y | Latin Capital Letter Y |
| 90 | 5A | 132 | Z | Latin Capital Letter Z |

#### 특수 문자 및 소문자 (91-122)

| 10진 | 16진 | 8진 | 문자 | 이름 |
|------|------|-----|------|------|
| 91 | 5B | 133 | [ | Left Square Bracket |
| 92 | 5C | 134 | \ | Reverse Solidus |
| 93 | 5D | 135 | ] | Right Square Bracket |
| 94 | 5E | 136 | ^ | Circumflex Accent |
| 95 | 5F | 137 | _ | Low Line |
| 96 | 60 | 140 | ` | Grave Accent |
| 97 | 61 | 141 | a | Latin Small Letter a |
| 98 | 62 | 142 | b | Latin Small Letter b |
| 99 | 63 | 143 | c | Latin Small Letter c |
| 100 | 64 | 144 | d | Latin Small Letter d |
| 101 | 65 | 145 | e | Latin Small Letter e |
| 102 | 66 | 146 | f | Latin Small Letter f |
| 103 | 67 | 147 | g | Latin Small Letter g |
| 104 | 68 | 150 | h | Latin Small Letter h |
| 105 | 69 | 151 | i | Latin Small Letter i |
| 106 | 6A | 152 | j | Latin Small Letter j |
| 107 | 6B | 153 | k | Latin Small Letter k |
| 108 | 6C | 154 | l | Latin Small Letter l |
| 109 | 6D | 155 | m | Latin Small Letter m |
| 110 | 6E | 156 | n | Latin Small Letter n |
| 111 | 6F | 157 | o | Latin Small Letter o |
| 112 | 70 | 160 | p | Latin Small Letter p |
| 113 | 71 | 161 | q | Latin Small Letter q |
| 114 | 72 | 162 | r | Latin Small Letter r |
| 115 | 73 | 163 | s | Latin Small Letter s |
| 116 | 74 | 164 | t | Latin Small Letter t |
| 117 | 75 | 165 | u | Latin Small Letter u |
| 118 | 76 | 166 | v | Latin Small Letter v |
| 119 | 77 | 167 | w | Latin Small Letter w |
| 120 | 78 | 170 | x | Latin Small Letter x |
| 121 | 79 | 171 | y | Latin Small Letter y |
| 122 | 7A | 172 | z | Latin Small Letter z |

#### 마지막 특수 문자 (123-127)

| 10진 | 16진 | 8진 | 문자 | 이름 |
|------|------|-----|------|------|
| 123 | 7B | 173 | { | Left Curly Bracket |
| 124 | 7C | 174 | \| | Vertical Line |
| 125 | 7D | 175 | } | Right Curly Bracket |
| 126 | 7E | 176 | ~ | Tilde |
| 127 | 7F | 177 | DEL | Delete |

### ASCII 코드 활용법

#### 문자-숫자 변환

**숫자 문자를 정수로**
```
'0' → 48, '1' → 49, ..., '9' → 57
정수값 = 문자 - '0'
예: '7' - '0' = 55 - 48 = 7
```

**대소문자 변환**
```
대문자 → 소문자: c + 32 또는 c + ('a' - 'A')
소문자 → 대문자: c - 32 또는 c - ('a' - 'A')
예: 'A' (65) + 32 = 'a' (97)
```

**문자 범위 확인**
```
숫자: '0' <= c <= '9' (48 <= c <= 57)
대문자: 'A' <= c <= 'Z' (65 <= c <= 90)
소문자: 'a' <= c <= 'z' (97 <= c <= 122)
```

## 확장 ASCII (128-255)

확장 ASCII는 표준이 아니며 시스템마다 다릅니다. 주요 확장:

- **Latin-1 (ISO 8859-1)**: 서유럽 문자
- **CP-1252**: Windows에서 주로 사용
- **UTF-8**: 유니코드 인코딩 (ASCII 호환)

## C언어 데이터 타입 크기 및 범위

### 정수 타입

#### 기본 정수 타입

| 타입 | 일반적 크기 | 최소 범위 | 일반적 범위 |
|------|-------------|-----------|-------------|
| **char** | 1바이트 | -127 ~ 127 또는 0 ~ 255 | -128 ~ 127 또는 0 ~ 255 |
| **signed char** | 1바이트 | -127 ~ 127 | -128 ~ 127 |
| **unsigned char** | 1바이트 | 0 ~ 255 | 0 ~ 255 |
| **short** | 2바이트 | -32,767 ~ 32,767 | -32,768 ~ 32,767 |
| **unsigned short** | 2바이트 | 0 ~ 65,535 | 0 ~ 65,535 |
| **int** | 4바이트 | -32,767 ~ 32,767 | -2,147,483,648 ~ 2,147,483,647 |
| **unsigned int** | 4바이트 | 0 ~ 65,535 | 0 ~ 4,294,967,295 |
| **long** | 4/8바이트 | -2,147,483,647 ~ 2,147,483,647 | 플랫폼 의존 |
| **unsigned long** | 4/8바이트 | 0 ~ 4,294,967,295 | 플랫폼 의존 |
| **long long** | 8바이트 | -9,223,372,036,854,775,807 ~ 9,223,372,036,854,775,807 | -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807 |
| **unsigned long long** | 8바이트 | 0 ~ 18,446,744,073,709,551,615 | 0 ~ 18,446,744,073,709,551,615 |

#### C99 고정 크기 정수 타입 (`<stdint.h>`)

| 타입 | 크기 | 범위 |
|------|------|------|
| **int8_t** | 1바이트 | -128 ~ 127 |
| **uint8_t** | 1바이트 | 0 ~ 255 |
| **int16_t** | 2바이트 | -32,768 ~ 32,767 |
| **uint16_t** | 2바이트 | 0 ~ 65,535 |
| **int32_t** | 4바이트 | -2,147,483,648 ~ 2,147,483,647 |
| **uint32_t** | 4바이트 | 0 ~ 4,294,967,295 |
| **int64_t** | 8바이트 | -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807 |
| **uint64_t** | 8바이트 | 0 ~ 18,446,744,073,709,551,615 |

#### 특수 정수 타입

| 타입 | 목적 | 일반적 크기 |
|------|------|-------------|
| **size_t** | 배열 크기, 메모리 크기 | 4/8바이트 (포인터 크기와 동일) |
| **ssize_t** | 부호 있는 size_t | 4/8바이트 |
| **ptrdiff_t** | 포인터 차이 | 4/8바이트 |
| **intptr_t** | 포인터를 저장할 수 있는 정수 | 4/8바이트 |
| **uintptr_t** | 부호 없는 intptr_t | 4/8바이트 |

### 부동소수점 타입

#### 부동소수점 타입

| 타입 | 크기 | 유효 자릿수 | 범위 (대략) |
|------|------|-------------|-------------|
| **float** | 4바이트 | 6-7자리 | ±1.2E-38 ~ ±3.4E+38 |
| **double** | 8바이트 | 15-16자리 | ±2.3E-308 ~ ±1.7E+308 |
| **long double** | 8/12/16바이트 | 18-19자리 이상 | 구현 의존 |

#### IEEE 754 부동소수점 구조

**float (32비트)**
```
| 부호 | 지수 (8비트) | 가수 (23비트) |
|  1   |      8       |      23       |
```

**double (64비트)**
```
| 부호 | 지수 (11비트) | 가수 (52비트) |
|  1   |      11       |      52       |
```

### 포인터 타입

| 플랫폼 | 포인터 크기 | 주소 공간 |
|--------|-------------|-----------|
| **32비트** | 4바이트 | 4GB |
| **64비트** | 8바이트 | 16EB (이론상) |

### 불린 타입 (C99)

| 타입 | 크기 | 값 |
|------|------|-----|
| **_Bool** | 1바이트 | 0 (거짓), 1 (참) |
| **bool** | 1바이트 | false, true (`<stdbool.h>`) |

## 플랫폼별 차이점

### 일반적인 플랫폼

#### 32비트 시스템

| 타입 | 크기 |
|------|------|
| char | 1바이트 |
| short | 2바이트 |
| int | 4바이트 |
| long | 4바이트 |
| long long | 8바이트 |
| float | 4바이트 |
| double | 8바이트 |
| 포인터 | 4바이트 |

#### 64비트 시스템

**Unix/Linux (LP64 모델)**
| 타입 | 크기 |
|------|------|
| char | 1바이트 |
| short | 2바이트 |
| int | 4바이트 |
| long | 8바이트 |
| long long | 8바이트 |
| 포인터 | 8바이트 |

**Windows (LLP64 모델)**
| 타입 | 크기 |
|------|------|
| char | 1바이트 |
| short | 2바이트 |
| int | 4바이트 |
| long | 4바이트 |
| long long | 8바이트 |
| 포인터 | 8바이트 |

### 데이터 모델

| 모델 | int | long | 포인터 | 플랫폼 |
|------|-----|------|--------|--------|
| **ILP32** | 32비트 | 32비트 | 32비트 | 32비트 시스템 |
| **LP64** | 32비트 | 64비트 | 64비트 | Unix/Linux 64비트 |
| **LLP64** | 32비트 | 32비트 | 64비트 | Windows 64비트 |

## 한계값 확인 헤더

### `<limits.h>` - 정수 한계값

| 매크로 | 의미 | 일반적 값 |
|--------|------|-----------|
| **CHAR_BIT** | char의 비트 수 | 8 |
| **CHAR_MAX** | char 최댓값 | 127 또는 255 |
| **CHAR_MIN** | char 최솟값 | -128 또는 0 |
| **SCHAR_MAX** | signed char 최댓값 | 127 |
| **SCHAR_MIN** | signed char 최솟값 | -128 |
| **UCHAR_MAX** | unsigned char 최댓값 | 255 |
| **SHRT_MAX** | short 최댓값 | 32767 |
| **SHRT_MIN** | short 최솟값 | -32768 |
| **USHRT_MAX** | unsigned short 최댓값 | 65535 |
| **INT_MAX** | int 최댓값 | 2147483647 |
| **INT_MIN** | int 최솟값 | -2147483648 |
| **UINT_MAX** | unsigned int 최댓값 | 4294967295U |
| **LONG_MAX** | long 최댓값 | 플랫폼 의존 |
| **LONG_MIN** | long 최솟값 | 플랫폼 의존 |
| **ULONG_MAX** | unsigned long 최댓값 | 플랫폼 의존 |
| **LLONG_MAX** | long long 최댓값 | 9223372036854775807LL |
| **LLONG_MIN** | long long 최솟값 | -9223372036854775808LL |
| **ULLONG_MAX** | unsigned long long 최댓값 | 18446744073709551615ULL |

### `<float.h>` - 부동소수점 한계값

| 매크로 | 의미 | float | double |
|--------|------|-------|--------|
| **FLT_DIG** / **DBL_DIG** | 정밀 자릿수 | 6 | 15 |
| **FLT_MAX** / **DBL_MAX** | 최댓값 | 3.4E+38 | 1.7E+308 |
| **FLT_MIN** / **DBL_MIN** | 최솟값 | 1.2E-38 | 2.3E-308 |
| **FLT_EPSILON** / **DBL_EPSILON** | 머신 엡실론 | 1.2E-07 | 2.2E-16 |

## 메모리 정렬 (Alignment)

### 정렬 규칙

**일반적인 정렬 요구사항**
- char: 1바이트 정렬
- short: 2바이트 정렬
- int: 4바이트 정렬
- long: 4/8바이트 정렬 (플랫폼 의존)
- float: 4바이트 정렬
- double: 8바이트 정렬
- 포인터: 포인터 크기 정렬

### 구조체 패딩

**패딩 예시**
```
struct Example {
    char c;     // 1바이트
    // 3바이트 패딩
    int i;      // 4바이트
    char c2;    // 1바이트
    // 3바이트 패딩 (구조체 끝)
};
// 총 크기: 12바이트 (8바이트 정렬)
```

**패킹된 구조체**
```
#pragma pack(1)
struct Packed {
    char c;     // 1바이트
    int i;      // 4바이트
    char c2;    // 1바이트
};
// 총 크기: 6바이트
```

## 바이트 순서 (Endianness)

### 리틀 엔디안 vs 빅 엔디안

**숫자 0x12345678 저장 방식**

**리틀 엔디안 (x86, x86-64)**
```
주소:   [0] [1] [2] [3]
값:     78  56  34  12
```

**빅 엔디안 (일부 ARM, MIPS)**
```
주소:   [0] [1] [2] [3]
값:     12  34  56  78
```

### 엔디안 확인 방법

```c
int check_endianness() {
    uint32_t test = 0x12345678;
    uint8_t *ptr = (uint8_t*)&test;

    if (ptr[0] == 0x78) {
        return 0; // 리틀 엔디안
    } else if (ptr[0] == 0x12) {
        return 1; // 빅 엔디안
    }
    return -1; // 알 수 없음
}
```

## 이식성 고려사항

### 타입 크기 가정 금지

**잘못된 가정**
- int가 항상 4바이트
- long이 int보다 크다
- 포인터가 int에 들어간다

**안전한 방법**
- sizeof() 연산자 사용
- `<stdint.h>` 고정 크기 타입 사용
- `<limits.h>` 한계값 확인

### 포인터와 정수 변환

**안전한 포인터-정수 변환**
```c
#include <stdint.h>

void* ptr = malloc(100);
uintptr_t addr = (uintptr_t)ptr;  // 포인터 → 정수
void* ptr2 = (void*)addr;         // 정수 → 포인터
```

### 구조체 크기 계산

**안전한 구조체 크기 계산**
```c
struct MyStruct {
    char c;
    int i;
    double d;
};

size_t size = sizeof(struct MyStruct);  // 패딩 포함 실제 크기
size_t offset_i = offsetof(struct MyStruct, i);  // 멤버 오프셋
```

## 마무리

ASCII 코드와 데이터 타입의 정확한 이해는 다음과 같은 영역에서 중요합니다:

### 실무 적용 영역

1. **문자 처리**: 문자 인코딩, 문자열 조작
2. **바이너리 데이터**: 파일 형식, 네트워크 프로토콜
3. **시스템 프로그래밍**: 메모리 관리, 하드웨어 인터페이스
4. **이식성**: 플랫폼 간 호환성

### 주의사항

- char의 부호 여부는 구현 의존적
- 정수 오버플로우는 undefined behavior
- 부동소수점 연산의 정밀도 한계
- 구조체 패딩으로 인한 크기 변화

정확한 데이터 타입 이해는 안전하고 이식 가능한 프로그램 작성의 기초입니다.