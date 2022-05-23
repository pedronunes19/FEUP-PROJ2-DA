#include "../include/Menu.h"

bool Menu::exitApplication = false;

void Menu::init() {

    // Company deliveryCompany{"GDC (Generic Delivery Company)"};

    atexit(Menu::endProgram);

    while (!Menu::exitApplication) {

        std::cout << std::string(100, '\n');

        int option = Menu::showInitialMenu("aaaaaaaaaaaaaaaaaaa");

        switch (option) {
            case CLIENT:
            case ADMIN:

                if (option == CLIENT) {

                    option = Menu::showClientMenu();

                    switch (option) {
                        case CLIENT_BACK:
                            break;
                        default:
                            std::cout << "Invalid option, returning to main menu\n\n";
                            break;
                    }

                } else {

                    option = Menu::showAdminMenu();

                    switch (option) {    
                        case ADMIN_BACK:
                            break;
                        default:
                            std::cout << "Invalid option, returning to main menu\n\n";
                            break;
                    }
                }
                break;
            case LEAVE:
                Menu::exitApplication = true;
                break;
            default:
                std::cout << "\tInvalid option chosen!\n\n";
                break;
        }
    }
}


unsigned long Menu::getUnsignedInput(std::string prompt, unsigned long min, unsigned long max) {
    std::string input;
    unsigned long number;
    bool done = false;

    do {
        input = getStringInput(prompt);

        try {
            number = stoul(input);
            done = true;
        } catch (std::invalid_argument) {
            done = false;
        }
    } while (!done || !inRange(number, min, max));

    return number;
}

std::string Menu::getStringInput(std::string prompt) {
    std::string input{};

    std::getline(std::cin, input);
    utils::file::normalizeInput(input);

    if (std::cin.eof())
        Menu::exitApplication = true;

    return input;
}

bool Menu::inRange(unsigned long n, unsigned long min,
                            unsigned long max) {
    return (n <= max) && (n >= min);
}

int Menu::showAdminMenu() {

    int option;

    std::cout << "\tHello, what would you like to do?\n\n"
                 "\t[1] Back\n\n"
                 "\t> ";

    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

int Menu::showClientMenu() {

    int option;

    std::cout << "\tHello, what would you like to do?\n\n"
                 "\t[1] Back\n\n"
                 "\t> ";

    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

int Menu::showInitialMenu(const std::string& busCompany) {

    int option;

    std::cout << "\t\tWelcome to " << busCompany << "\n\n";
    std::cout << "\t[1] Travel\n\t[2] Admin\n\t[3] Exit\n\n";
    std::cout << "\t> ";
    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

void Menu::endProgram() {
    utils::file::waitForEnter();
}