#include "robot.h"

bool runCommand(Robot& theRobot, const std::string& cmd)
{
    std::string _cmd(toUpper(trim(cmd)));
    if (_cmd == "")
    {
        return true; // nothing to do
    }
    else if (_cmd == "QUIT")
    {
        std::cerr << "! Exiting..." << std::endl;
        return false;
    }
    else
    {
        eCmdResult res = theRobot.runCommand(_cmd);
        if (res == eCmdResult::E_INVALID)
        {
            std::cerr << "! Invalid command [" << _cmd << "]" << std::endl;
        }
        else if (res == eCmdResult::E_UNKNOWN)
        {
            std::cerr << "! Unknown command [" << _cmd << "]" << std::endl;
        }
        return true;
    }
}

void runInteractive(Robot& theRobot)
{
    while (true)
    {
        std::string cmd;
        std::cout << ": ";
        if (!std::getline(std::cin, cmd))
        {
            // nothing, ignore it and move on
            continue;
        }

        if (!runCommand(theRobot, cmd))
        {
            break;
        }
    }
}

void runScript(Robot& theRobot, int argc, char *argv[])
{
    StringVector cmds;
    int count = tokenise(argv[2], cmds, ';');
    std::cerr << "! Process [" << count << "] commands." << std::endl;

    for (auto itr = cmds.begin(); itr != cmds.end(); ++itr)
    {
        std::string cmd = *itr;
        std::cout << ": " << trim(cmd) << std::endl;
        if (!runCommand(theRobot, cmd))
        {
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    std::cerr << "! Generate test field for robot [" << Robot::getMaxX()
    	<< ", " << Robot::getMaxY() << "]" << std::endl;
    Robot theRobot;

    if (argc == 1)
    {
        // normal interactive operation
        std::cerr << "! Run in interactive mode" << std::endl;
        runInteractive(theRobot);
    }
    else if (argc == 3 && std::string(argv[1]) == "-c")
    {
        // run cmds as a script
        std::cerr << "! Run as a script: [" << argv[2] << "]" << std::endl;
        runScript(theRobot, argc, argv);
    }
    else
    {
        std::cerr << "! Invalid command line arg" << std::endl;
        return 1;
    }

    return 0;
}
