#include "../include/Menu.h"

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
    std::cout << prompt;
    std::string input{};

    std::getline(std::cin, input);
    utils::file::normalizeInput(input);

    if (std::cin.eof())
        throw Exit();

    return input;
}

bool Menu::inRange(unsigned long n, unsigned long min,
                            unsigned long max) {
    return (n <= max) && (n >= min);
}

void Menu::showMainMenu() {

    std::string prompt = "Generic Company that does company stuff\n\n"
                         "[1] Joint Planning\n"
                         "[2] Separate Planning\n"
                         "[0] Exit\n"
                         ">";

    unsigned long option = getUnsignedInput(prompt, 0, 2);

    switch(option) {
        case 1:
            MOpt = JOINT_PLAN;
            break;
        case 2:
            MOpt = SEPARATE_PLAN;
            break;
        case 0:
            MOpt = EXIT;
            break;
    }
}

void Menu::showJointPlanMenu() {
    unsigned long start, end;
    double max_flow;
    std::list<Node> path, path2;

    std::string prompt = "[1] Maximize group\n"
                         "[2] Minimize transport switches\n"
                         "[0] Exit\n"
                         ">";
    unsigned long option = getUnsignedInput(prompt, 0, 2);

    switch(option) {
        case 1:
            start = getUnsignedInput("Start:", 0, company.getDatasetMax());
            end = getUnsignedInput("End:", 0, company.getDatasetMax());
            path = company.maximizeJointAny(start, end);
            if (!path.size()) {
                std::cout << "No path found!" << std::endl;
                utils::file::waitForEnter();
                MOpt = MAIN_MENU;
                break;
            }

            for (auto const& i : path) {
                std::cout << i.id << "\n";
            }
            
            std::cout << std::flush;
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        case 2:
            start = getUnsignedInput("Start:", 1, company.getDatasetMax());
            end = getUnsignedInput("End:", 1, company.getDatasetMax());
            company.minimizeJointTrans(start, end, path, path2);

            if (!path.size()) {
                std::cout << "No path found when maximizing group dimension!" << std::endl;
            } else {
                std::cout << "Maximizing group dimensions:" << std::endl;
                for (auto const& i : path) {
                    std::cout << i.id << "\n";
                }
            }

            if (!path2.size()) {
                std::cout << "No path found when minizing vehicle changes!" << std::endl;
            } else {
                std::cout << "Minimizing vehicle changes:" << std::endl;
                for (auto const& j : path2) {
                    std::cout << j.id << "\n";
                }
            }

            if (path.size() == path2.size()) {
                std::cout << "The paths found have the same amount of vehicle changes! We recommend the one maximizing the group dimensions!" << std::endl;
            }

            std::cout << std::flush;
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        case 0:
            MOpt = MAIN_MENU;
            break;
    }
}

void Menu::show() {
    switch (MOpt) {
        case MAIN_MENU:
            showMainMenu();
            break;
        case JOINT_PLAN:
            showJointPlanMenu();
            break;
        case SEPARATE_PLAN:
            // separatePlan();
            break;
        case EXIT:
            throw Exit();
    }
}

void Menu::showExit() {
    utils::file::waitForEnter();
}
