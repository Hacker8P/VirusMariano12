#include <windows.h>
#include <iostream>

int main() {
    // Codice per invertire i pulsanti del mouse
    if (SystemParametersInfo(SPI_SETMOUSE, 0, (PVOID)1, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE)) {
        NULL;
    } else {
        NULL;
    }
    
    return 0;
}