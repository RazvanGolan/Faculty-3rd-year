#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <parser.h>
#include <unistd.h>
#include "utils.h"
#include "lexer.h"

char *getAbsolutePath(const char *relativePath)
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        chdir("..");

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            char *absPath = malloc(PATH_MAX);
            snprintf(absPath, PATH_MAX, "%s/%s", cwd, relativePath);
            return absPath;
        }
    }
    perror("getcwd() error");
    return NULL;
}

int main()
{
    const char *relativePath = "AtomC/files/tests/testad.c";
    char *fileName = getAbsolutePath(relativePath);
    if (fileName == NULL)
    {
        return 1;
    }

    char *buf = loadFile(fileName);
    const Token *tokens = tokenize(buf);

    showTokens(tokens);

    parse(tokens);

    free(buf);

    return 0;
}
