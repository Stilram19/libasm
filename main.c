# include "libasm.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

int main() {
    char *str = "OMAR";
    ft_write(1, str, 4);
}
