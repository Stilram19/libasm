# include "libasm.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

int main() {
    char *buf = malloc(sizeof(char) * 4);

    int ret = ft_read(0, buf, 2);
    printf("ret: %d\n", ret);
    perror(NULL);
    printf("%s\n", buf);
}
