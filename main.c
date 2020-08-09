#include "MAIN.h"

int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        first_pass(argv[i]);
    }

    return 0;
}