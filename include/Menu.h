#ifndef DA_PROJ_2_MENU_H
#define DA_PROJ_2_MENU_H

#include <iostream>
#include "utils.h"
/**
 * @brief The application's menu.
 */
class Menu {
    /**
     * @brief Boolean that becomes true if the user chooses to leave the program.
     */
    static bool exitApplication;

    /**
     * @brief Series of enums that store the options in each menu (Main, Admin and Client).
     */
    enum MainMenuOption {
        CLIENT = 1,
        ADMIN,
        LEAVE
    };

    enum AdminMenuOption {
        ADMIN_BACK = 1
    };

    enum ClientMenuOption {
        CLIENT_BACK = 1
    };

public:
    /**
     * @brief Initialize the program
     */
    static void init();

    /**
     * @brief transforms string input into unsigned integer, creates an error message if it fails
     *
     * @param prompt shown to the user
     * @param min the left bound of the limit (inclusive)
     * @param max the right bound of the limit (inclusive)
     * @return the user input, as an unsigned integer
     */
    unsigned long getUnsignedInput(std::string prompt, unsigned long min = 0,
                                   unsigned long max = ULONG_MAX);

    /**
     * @brief gets a line from stdin and normalizes it
     *
     * @param prompt shown to the user
     * @return the user input
     */
    std::string getStringInput(std::string prompt);

    /**
     * @brief checks if an unsigned integer n is inside the limit [min, max]
     *
     * @param n the number to be checked
     * @param min the left bound of the limit
     * @param max the right bound of the limit
     * @return boolean of the logical result of: min <= n <= max
     */
    bool inRange(unsigned long n, unsigned long min, unsigned long max);

    /**
     * @brief Shows the initial menu on screen
     * @param CompanyName Name of the Company we are travelling with (displayed on screen)
     * @return User option (Client/Admin/EXit)
     */
    static int showInitialMenu(const std::string& CompanyName);
    /**
     * @brief Shows the administrator menu on screen
     * @return User option (from the admin functionalities available)
     */
    static int showAdminMenu();
    /**
     * @brief Shows the administrator menu on screen
     * @return User option (from the client functionalities available)
     */
    static int showClientMenu();
    /**
     * @brief Close the program
     */
    static void endProgram();
};

#endif //DA_PROJ_2_MENU_H