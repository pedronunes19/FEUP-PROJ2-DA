#ifndef DA_PROJ_2_MENU_H
#define DA_PROJ_2_MENU_H

#include <iostream>
#include <climits>
#include "utils.h"
#include "Company.h"

class Menu;

/**
 * @brief Series of enums that store the options in each menu (Main, Admin and Client).
 */
enum MenuOptions {
    MAIN_MENU,
    JOINT_PLAN,
    SEPARATE_PLAN,
    EXIT
};

/**
 * @brief The application's menu.
 */
class Menu {
    MenuOptions MOpt = MAIN_MENU;

    Company company;
public:

    Menu(Company company) {
        this->company = company;
    }
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
     * @brief Shows the administrator menu on screen
     * @return User option (from the admin functionalities available)
     */
    void showMainMenu();

    /**
     * @brief Close the program
     */
    void endProgram();

    void show();

    void jointPlan();

    void separatePlan();

    void showJointPlanMenu();

    void showExit();
};

#endif //DA_PROJ_2_MENU_H