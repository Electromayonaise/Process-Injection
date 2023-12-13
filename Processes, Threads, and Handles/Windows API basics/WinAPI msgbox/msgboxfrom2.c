# include <windows.h>

int main(void){
    MessageBoxW(NULL, L"Message box", L"Hello, World!", MB_YESNOCANCEL| MB_ICONQUESTION);
    return EXIT_SUCCESS;
}