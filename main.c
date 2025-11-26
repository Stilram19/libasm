# include "libasm.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

int main() {
    char s[10] = "OMAR\n";
    write(1, s, 5);
    return (0);
}