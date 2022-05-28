#include "include/Menu.h"

int main(){
    Company company;
    Menu menu = Menu(company);

    try {
        while (true) {
            menu.show();
        }
    } catch (Exit) {
        menu.showExit();
    }

    return 0;
}