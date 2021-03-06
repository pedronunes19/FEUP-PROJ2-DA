#include "../include/Menu.h"
#include <chrono>

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
    utils::file::clearScreen();

    std::string prompt = "Generic Company that does company stuff\n\n"
                         "[1] Joint Planning\n"
                         "[2] Separate Planning\n"
                         "[3] Change Dataset\n"
                         "[0] Exit\n"
                         ">";

    unsigned long option = getUnsignedInput(prompt, 0, 3);

    switch(option) {
        case 1:
            MOpt = JOINT_PLAN;
            break;
        case 2:
            MOpt = SEPARATE_PLAN;
            break;
        case 3:
            MOpt = CHANGE_DATASET;
            break;
        case 0:
            MOpt = EXIT;
            break;
    }
}

void Menu::showJointPlanMenu() {
    utils::file::clearScreen();
    unsigned long start, end;
    int cap;
    std::list<Node> path, path2;

    std::string prompt = "[1] Maximize group\n"
                         "[2] Minimize transport switches\n"
                         "[0] Back\n"
                         ">";
    unsigned long option = getUnsignedInput(prompt, 0, 2);

    switch(option) {
        case 1: {
            start = getUnsignedInput("Start:", 1, company.getDatasetMax());
            end = getUnsignedInput("End:", 1, company.getDatasetMax());
            while (start == end){
                end = getUnsignedInput("End:", 1, company.getDatasetMax());
            }
            auto startTime = std::chrono::high_resolution_clock::now();
            path = company.maximizeJointAny(std::to_string(start), std::to_string(end), cap);
            auto stopTime = std::chrono::high_resolution_clock::now();
            auto algo_duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
            if (path.empty()) {
                std::cout << "No path found!" << std::endl;
                utils::file::waitForEnter();
                MOpt = MAIN_MENU;
                break;
            }

            std::cout << "Maximizing group dimensions (max: " << cap << "):" << std::endl;
            for (auto const &a: path) {
                if (a == path.back()) std::cout << a.id;
                else std::cout << a.id << " -> ";
            }

            std::cout << std::endl << std::flush;
            std::cout << "\nAlgorithm Duration: " << algo_duration.count() << " microseconds" << std::endl;
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        }
        case 2:
            start = getUnsignedInput("Start:", 1, company.getDatasetMax());
            end = getUnsignedInput("End:", 1, company.getDatasetMax());
            company.minimizeJointTrans(std::to_string(start), std::to_string(end), path, path2, cap);

            if (path.empty()) {
                std::cout << "No path found when maximizing group dimension!" << std::endl;
            } else {
                std::cout << "Maximizing group dimensions (max: "<< cap << "):" << std::endl;
                for (auto const &a: path){
                    if (a == path.back()) std::cout << a.id;
                    else std::cout << a.id << " -> ";
                }
            }

            std::cout << std::endl;

            if (path2.empty()) {
                std::cout << "No path found when minimizing vehicle changes!" << std::endl;
            } else {
                std::cout << "Minimizing vehicle changes:" << std::endl;
                for (auto const &a: path2){
                    if (a == path2.back()) std::cout << a.id;
                    else std::cout << a.id << " -> ";
                }
            }

            if ((path.size() == path2.size()) && !(path.empty() || path2.empty())) {
                std::cout << std::endl << "The paths found have the same amount of vehicle changes! We recommend the one maximizing the group dimensions!" << std::endl;
            }

            std::cout << std::endl << std::flush;
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        case 0:
            MOpt = MAIN_MENU;
            break;
    }
}

void Menu::showSeparatePlanMenu() {
    utils::file::clearScreen();

    unsigned long start, end, cap, add_cap;
    int init_flow, end_flow;
    std::list<Node> path, path2;

    std::string prompt = "[1] Find path by group size\n"
                         "[2] Find path by group size (incrementing)\n"
                         "[3] Find path for max group size\n"
                         "[4] Find minimum time/node for the whole group to be reunited at\n"
                         "[5] Find maximum wait time\n"
                         "[0] Back\n"
                         ">";
    unsigned long option = getUnsignedInput(prompt, 0, 5);

    switch (option) {
        case 1: {
            start = getUnsignedInput("Start:", 0, company.getDatasetMax());
            end = getUnsignedInput("End:", 0, company.getDatasetMax());
            cap = getUnsignedInput("Group Size:", 1, INT32_MAX);
            auto startTime = std::chrono::high_resolution_clock::now();
            company.ekLimit(std::to_string(start), std::to_string(end), cap);
            auto stopTime = std::chrono::high_resolution_clock::now();
            auto algo_duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

            std::cout << "\nAlgorithm Duration: " << algo_duration.count() << " microseconds" << std::endl;
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        }
        case 2:
            start = getUnsignedInput("Start:", 0, company.getDatasetMax());
            end = getUnsignedInput("End:", 0, company.getDatasetMax());
            cap = getUnsignedInput("Group Size:", 1, INT32_MAX);
            init_flow = company.ekLimit(std::to_string(start), std::to_string(end), cap);
            if (!init_flow) {
                utils::file::waitForEnter();
                MOpt = MAIN_MENU;
                break;
            }
            add_cap = getUnsignedInput("Try to increment group size by:", 1, INT32_MAX);
            end_flow = company.ekLimit(std::to_string(start), std::to_string(end), cap + add_cap);

            if (end_flow < cap + add_cap) {
                std::cout << "Group increase failed (from " << cap << " to " << cap + add_cap << "). Maximum capacity is: " << end_flow << ".\n";
            }

            else {
                std::cout << "Group increase successful (from " << cap << " to " << cap + add_cap << ")!\n";
            }
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        case 3:
            start = getUnsignedInput("Start:", 0, company.getDatasetMax());
            end = getUnsignedInput("End:", 0, company.getDatasetMax());
            company.ek(std::to_string(start), std::to_string(end));
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        case 4:
            start = getUnsignedInput("Start:", 0, company.getDatasetMax());
            end = getUnsignedInput("End:", 0, company.getDatasetMax());
            company.ekMaxPath(std::to_string(start), std::to_string(end), false);
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        case 5:
            start = getUnsignedInput("Start:", 0, company.getDatasetMax());
            end = getUnsignedInput("End:", 0, company.getDatasetMax());
            company.ekMaxPath(std::to_string(start), std::to_string(end), true);
            utils::file::waitForEnter();
            MOpt = MAIN_MENU;
            break;
        case 0:
            MOpt = MAIN_MENU;
            break;
    }
}

void Menu::showChangeDatasetMenu() {
    utils::file::clearScreen();
    std::string prompt = "Choose the dataset you want to load [1-10] (0 to go back): ";

    unsigned long option = getUnsignedInput(prompt, 0, 10);

    switch (option) {
        case 1:
            company.changeDataset(NORMAL_DATASET_1);
            break;
        case 2:
            company.changeDataset(NORMAL_DATASET_2);
            break;
        case 3:
            company.changeDataset(NORMAL_DATASET_3);
            break;
        case 4:
            company.changeDataset(NORMAL_DATASET_4);
            break;
        case 5:
            company.changeDataset(NORMAL_DATASET_5);
            break;
        case 6:
            company.changeDataset(NORMAL_DATASET_6);
            break;
        case 7:
            company.changeDataset(NORMAL_DATASET_7);
            break;
        case 8:
            company.changeDataset(NORMAL_DATASET_8);
            break;
        case 9:
            company.changeDataset(NORMAL_DATASET_9);
            break;
        case 10:
            company.changeDataset(NORMAL_DATASET_10);
            break;
        case 0:
            MOpt = MAIN_MENU;
            return;
    }
    MOpt = MAIN_MENU;
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
            showSeparatePlanMenu();
            break;
        case CHANGE_DATASET:
            showChangeDatasetMenu();
            break;
        case EXIT:
            throw Exit();
    }
}

void Menu::showExit() {
    utils::file::waitForEnter();
}
