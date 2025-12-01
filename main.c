# include "libasm.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

/* test ft_strlen */
void test_strlen()
{
    printf("== ft_strlen ==\n");
    printf("empty: %zu | %zu\n", ft_strlen(""), strlen(""));
    printf("normal: %zu | %zu\n", ft_strlen("hello"), strlen("hello"));
    printf("long: %zu | %zu\n", ft_strlen("abcdefghijklmnopqrstuvwxyz"), strlen("abcdefghijklmnopqrstuvwxyz"));
}

/* test ft_strcpy */
void test_strcpy()
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

/* test ft_strcmp */
void test_strcmp()
{
    printf("== ft_strcmp ==\n");
    printf("equal: %d | %d\n", ft_strcmp("abc", "abc"), strcmp("abc", "abc"));
    printf("less: %d | %d\n", ft_strcmp("abc", "abd"), strcmp("abc", "abd"));
    printf("greater: %d | %d\n", ft_strcmp("abd", "abc"), strcmp("abd", "abc"));
    printf("empty: %d | %d\n", ft_strcmp("", ""), strcmp("", ""));
}

/* test ft_write */
void test_write()
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

/* test ft_read */
void test_read()
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

/* test ft_strdup */
void test_strdup()
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

int main()
{
    // test_strlen();
    // test_strcpy();
    // test_strcmp();
    // test_write();
    // test_read();
    // test_strdup();
    return 0;
}