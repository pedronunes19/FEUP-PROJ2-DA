#ifndef DA_PROJ_2_MENU_H
#define DA_PROJ_2_MENU_H

#include <iostream>
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

    /**
     * @brief Waits for user input (new line) to progress
     * @param prompt
     */
    static void waitForPrompt(const std::string& prompt);

public:
    /**
     * @brief Initialize the program
     */
    static void init();

    /**
     * @brief Shows the initial menu on screen
     * @param CompanyName Name of the company we are travelling with (displayed on screen)
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
    /**
     * @brief Set of functions that call the respective Company methods with the same name.
     * @param deliveryCompany The Company tasked with the deliveries.
     */



};

#endif //DA_PROJ_2_MENU_H