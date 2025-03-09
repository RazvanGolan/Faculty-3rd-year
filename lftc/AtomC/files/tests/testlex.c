// program de testare a analizorului lexical, v1.1

// identificator -> variable names, int, else double, etc
// eroare daca nu ai numar dupa virgula la double
// la &&, || verifica daca apar amadoi, else error

#include <stdlib.h>
#include "../utils.h"
#include "../lexer.h"

int main()
{
    const char *fileName = "/Users/razvybitea/Faculty-3rd-year/lftc/AtomC/files/tests/test.c";
    char *buf = loadFile(fileName);

    const Token *tokens = tokenize(buf);

    showTokens(tokens);

    free(buf);

    return 0;
}
