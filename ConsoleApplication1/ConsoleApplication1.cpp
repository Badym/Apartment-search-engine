#include <iostream>
#include "klasy.h"
//#define _CRTDBG_MAP_ALLOC



int main()
{
    check CCC(2);

    Preferencje A;
    listaMieszkan ABC("aaa.txt", 100);
    
    std::unique_ptr <Interfejs> ptr;
    ptr = std::make_unique<Menu>();

    while (true)
    {
        ptr = ptr->strona(A,ABC);
        A.mias();
        if (ptr == nullptr) {
            break;
        }
    }
    

    return 0;

}



