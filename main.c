# include "libasm.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

int main() {
    char *s1 = "aba";
    char *s2 = "aba";
    printf("%d\n", ft_strcmp(s1, s2));
}
