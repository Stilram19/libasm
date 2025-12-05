# include "libasm.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

/* test ft_strlen */
void test_strlen(void)
{
    printf("== ft_strlen ==\n");
    printf("empty: %zu | %zu\n", ft_strlen(""), strlen(""));
    printf("normal: %zu | %zu\n", ft_strlen("hello"), strlen("hello"));
    printf("long: %zu | %zu\n", ft_strlen("abcdefghijklmnopqrstuvwxyz"), strlen("abcdefghijklmnopqrstuvwxyz"));
}

void test_strlen_2(void)
{
    // 1. empty string
    const char *empty = "";
    printf("Test 1: Empty string\n");
    printf("Expected: 0, Got: %zu\n\n", ft_strlen(empty));

    // 2. very long string
    char long_str[10001];
    for (int i = 0; i < 10000; i++)
        long_str[i] = 'A';
    long_str[10000] = '\0';

    printf("Test 2: Very long string (10,000 chars)\n");
    printf("Expected: 10000, Got: %zu\n", ft_strlen(long_str));
}

/* test ft_strcpy */
void test_strcpy(void)
{
    printf("== ft_strcpy ==\n");
    char dst1[50];
    char dst2[50];

    ft_strcpy(dst1, "hello");
    strcpy(dst2, "hello");
    printf("%s | %s\n", dst1, dst2);

    ft_strcpy(dst1, "");
    strcpy(dst2, "");
    printf("\'%s\' | \'%s\'\n", dst1, dst2);
}

void test_strcpy_2(void)
{
    // try ft_strcpy with an empty string
    char dest1[10];
    const char *src1 = "";
    ft_strcpy(dest1, src1);
    printf("test 1: empty string\n");
    printf("expected: '', got: '%s'\n\n", dest1);

    // try ft_strcpy with a very long string
    char long_src[10001];
    char dest2[10001];
    for (int i = 0; i < 10000; i++)
        long_src[i] = 'A';
    long_src[10000] = '\0';
    ft_strcpy(dest2, long_src);
    printf("test 2: very long string (10000 chars)\n");
    printf("expected length: 10000, got length: %zu\n", ft_strlen(dest2));
}

/* test ft_strcmp */
void test_strcmp(void)
{
    printf("== ft_strcmp ==\n");
    printf("equal: %d | %d\n", ft_strcmp("abc", "abc"), strcmp("abc", "abc"));
    printf("less: %d | %d\n", ft_strcmp("abc", "abd"), strcmp("abc", "abd"));
    printf("greater: %d | %d\n", ft_strcmp("abd", "abc"), strcmp("abd", "abc"));
    printf("empty: %d | %d\n", ft_strcmp("", ""), strcmp("", ""));
}

void test_strcmp_2(void)
{
    // try ft_strcmp with 2 empty strings
    const char *s1 = "";
    const char *s2 = "";
    printf("test 1: 2 empty strings\n");
    printf("expected: 0, got: %d\n\n", ft_strcmp(s1, s2));

    // try ft_strcmp with 1 empty string as first argument
    const char *s3 = "";
    const char *s4 = "abc";
    printf("test 2: first string empty\n");
    printf("expected: negative, got: %d\n\n", ft_strcmp(s3, s4));

    // try ft_strcmp with 1 empty string as second argument
    const char *s5 = "abc";
    const char *s6 = "";
    printf("test 3: second string empty\n");
    printf("expected: positive, got: %d\n\n", ft_strcmp(s5, s6));

    // try ft_strcmp with multiple strings, equal or not, switching them
    const char *s7 = "hello";
    const char *s8 = "hello";
    const char *s9 = "world";
    printf("test 4a: equal strings\n");
    printf("expected: 0, got: %d\n", ft_strcmp(s7, s8));
    
    printf("test 4b: unequal strings (s7 < s9)\n");
    printf("expected: negative, got: %d\n", ft_strcmp(s7, s9));
    
    printf("test 4c: unequal strings (s9 > s7)\n");
    printf("expected: positive, got: %d\n", ft_strcmp(s9, s7));
}

/* test ft_write */
void test_write(void)
{
    printf("== ft_write ==\n");

    ssize_t r1 = ft_write(1, "hello\n", 6);
    printf("ft_write ret: %zd\n", r1);

    ssize_t r2 = write(1, "hello\n", 6);
    printf("write ret: %zd\n", r2);

    errno = 0;
    ft_write(-1, "err\n", 4);
    printf("ft_write errno: %d\n", errno);

    errno = 0;
    write(-1, "err\n", 4);
    printf("write errno: %d\n", errno);
}


void test_write_2(void)
{
    ssize_t ret;
    int saved_errno;

    // try ft_write with stdout
    const char *msg1 = "test 1: write to stdout\n";
    ret = ft_write(1, msg1, strlen(msg1));
    printf("test 1: return value: %zd\n", ret);


    // try ft_write with an open file descriptor
    int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    const char *msg2 = "test 2: write to file\n";
    ret = ft_write(fd, msg2, strlen(msg2));
    printf("test 2: return value: %zd\n\n", ret);
    close(fd);

    // try ft_write with a wrong file descriptor
    errno = 0; // reset errno
    ret = ft_write(-1, "hello", 5);
    saved_errno = errno;
    printf("test 3: write with wrong fd\n");
    printf("expected: -1, got: %zd\n", ret);
    printf("errno expected: set, got: %d (%s)\n\n", saved_errno, strerror(saved_errno));

    // check writing zero bytes (optional)
    errno = 0;
    ret = ft_write(1, msg1, 0);
    saved_errno = errno;
    printf("test 4: write zero bytes\n");
    printf("expected: 0, got: %zd\n", ret);
    printf("errno should not be set, got: %d (%s)\n", saved_errno, strerror(saved_errno));
}

/* test ft_read */
void test_read(void)
{
    printf("== ft_read ==\n");

    char buf1[20];
    char buf2[20];

    int fd = open("main.c", O_RDONLY);
    if (fd >= 0) {
        ssize_t r1 = ft_read(fd, buf1, 19);
        buf1[r1 > 0 ? r1 : 0] = 0;
        printf("ft_read: %zd | %s\n", r1, buf1);
        close(fd);
    }

    fd = open("main.c", O_RDONLY);
    if (fd >= 0) {
        ssize_t r2 = read(fd, buf2, 19);
        buf2[r2 > 0 ? r2 : 0] = 0;
        printf("read: %zd | %s\n", r2, buf2);
        close(fd);
    }

    errno = 0;
    ft_read(-1, buf1, 10);
    printf("ft_read errno: %d\n", errno);

    errno = 0;
    read(-1, buf2, 10);
    printf("read errno: %d\n", errno);
}

void test_read_2(void)
{
    ssize_t ret;
    int saved_errno;
    char buffer[1024];

    // try ft_read with stdin (user needs to type something)
    printf("test 1: read from stdin, type something and press enter:\n");
    ret = ft_read(0, buffer, sizeof(buffer) - 1);
    if (ret >= 0) buffer[ret] = '\0';
    printf("test 1: return value: %zd, read: '%s'\n\n", ret, buffer);

    // try ft_read with an open file descriptor
    int fd = open("./main.c", O_RDONLY);
    if (fd < 0)
    {
        perror("open main.c");
        return;
    }
    ret = ft_read(fd, buffer, sizeof(buffer) - 1);
    if (ret >= 0) buffer[ret] = '\0';
    printf("test 2: read from file\n");
    printf("return value: %zd, read: '%s'\n\n", ret, buffer);
    close(fd);

    // try ft_read with a wrong file descriptor
    errno = 0; // reset errno
    ret = ft_read(-1, buffer, 10);
    saved_errno = errno;
    printf("test 3: read with wrong fd\n");
    printf("expected: -1, got: %zd\n", ret);
    printf("errno expected: set, got: %d (%s)\n", saved_errno, strerror(saved_errno));
}

/* test ft_strdup */
void test_strdup(void)
{
    printf("== ft_strdup ==\n");

    char *s1 = ft_strdup("hello libasm");
    char *s2 = strdup("hello libasm");
    printf("\'%s\' | \'%s\'\n", s1, s2);
    free(s1);
    free(s2);

    s1 = ft_strdup("");
    s2 = strdup("");
    printf("\'%s\' | \'%s\'\n", s1, s2);
    free(s1);
    free(s2);
}

void test_strdup_2(void)
{
    char *dup;
    
    // try ft_strdup with an empty string
    const char *empty = "";
    dup = ft_strdup(empty);
    printf("test 1: empty string\n");
    printf("expected: '', got: '%s'\n", dup);
    free(dup);

    // try ft_strdup with a very long string
    char long_str[10001];
    for (int i = 0; i < 10000; i++)
        long_str[i] = 'A';
    long_str[10000] = '\0';

    dup = ft_strdup(long_str);
    if (dup)
    {
        printf("test 2: very long string (10000 chars)\n");
        printf("expected length: 10000, got length: %zu\n", strlen(dup));
        free(dup);
    }
    else
    {
        printf("test 2: very long string - ft_strdup returned NULL\n");
    }
}

int main()
{
    // test_strlen();
    // test_strlen_2();
    // test_strcpy();
    // test_strcpy_2();
    // test_strcmp();
    // test_strcmp_2();
    // test_write();
    // test_write_2();
    // test_read();
    // test_read_2();
    // test_strdup();
    // test_strdup_2();
    return 0;
}