#include "Gra.h"
#include <locale>
int main()
{
    std::setlocale( LC_ALL, "polish" );
    Gra gra;
    gra.uruchomGre();
    return EXIT_SUCCESS;
}
