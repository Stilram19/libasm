# libasm

libasm is a 42 project where common libc functions are reimplemented in x86-64 assembly. it includes mandatory string and i/o functions, with optional bonus functions for linked lists and conversions.

## features

**mandatory functions:**
- ft_strlen (man 3 strlen)
- ft_strcpy (man 3 strcpy)
- ft_strcmp (man 3 strcmp)
- ft_write (man 2 write)
- ft_read (man 2 read)
- ft_strdup (man 3 strdup)

**bonus functions (optional):**
- ft_atoi_base
- ft_list_size
- ft_list_push_front
- ft_create_elem
- ft_list_sort
- ft_list_remove_if

## requirements

- Platform: linux x86-64
- Compiler (linker): gcc
- Assembler: nasm

## installation

build library and mandatory objects:

```bash
make all
```

build library including bonus:

```bash
make bonus
```

## tests

compile and run mandatory tests:

```bash
make test
./test.out
```

compile and run bonus tests:

```bash
make test_bonus
./test_bonus.out
```

## usage

link library in your c program:

```c
#include "libasm.h"

int len = ft_strlen("hello"); // 5
```

```c
#include "libasm_bonus.h"

int num = ft_atoi_base("7f", "0123456789abcdef"); // 127
```
