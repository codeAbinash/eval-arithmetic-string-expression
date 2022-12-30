#include "iostream"
using namespace std;
#include "./define.hpp"
#include "unordered_map"
typedef bool (*scriptFunction)(int, char **);
using namespace std;

namespace command {
bool version(argCVDef) {
    std::cout << dye::light_green("Eval ") << dye::light_green(__VERSION);
    std::cout <<  dye::grey(" (C)codeAbinash ") << dye::light_yellow(__version_date) << std::endl;
    return true;
}

bool help(argCVDef) {
    cout << "Visit " << dye::light_blue("https://github.com/codeAbinash/eval") << " for more information." << endl;
    return true;
}

bool unknownCommand(argCVDef) {
    cout << "Unknown command "
         << "`" << dye::light_yellow(argv[1]) << "`" << endl;
    cout << dye::grey("Akta command o valo kore lekhte parche na :) !") << endl;
    cout << "Use " << dye::light_yellow("`eval --help`") <<  " for more information." << endl;
    return false;
}
}  // namespace command

/**
 * @param argc argument count
 * @param argv arguments
 * @returns true if the command is executed successfully else return false or
 * unknown command
 */
bool executeCommand(argCVDef) {
    char *s = argv[1];
    /**
     * create an unordered_map that contains all the commands and their function
     * pointers.
     */
    unordered_map<string, scriptFunction> allCommands;
    allCommands["--version"] = &command::version;
    allCommands["--v"] = &command::version;
    allCommands["--help"] = &command::help;

    bool (*commandCallbackFunc)(int, char **) = allCommands[s];

    return commandCallbackFunc ? commandCallbackFunc(argCV)
                               : command::unknownCommand(argCV);
}