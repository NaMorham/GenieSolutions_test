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

/*
class Turtle : public Commandable, Point
{
public:
    Turtle() : Commandable(), Point(0, 0), m_facing(NORTH) {}
    Turtle(const int x, const int y, const eFacing facing)
        : Commandable(), Point(x, y), m_facing(facing) {}

    static eCmdResult testCommand(Turtle &cttl, const StringVector& args) { return cttl.test(args); }
    eCmdResult test(const StringVector& args)
    {
        std::cout << "TEST: with [" << args.size() << "] args" << std::endl;
        return eCmdResult::S_OK;
    }

    static eCmdResult placeCommand(Turtle &cttl, const StringVector& args) { return cttl.place(args); }
    eCmdResult place(const StringVector& args)
    {
        std::cout << "PLACE: with [" << args.size() << "] args" << std::endl;
        return eCmdResult::S_OK;
    }

    virtual void initCommands()
    {
        registerCommand("TEST", 1, (pfnCmd)(&testCommand));
    }

private:
    eFacing m_facing;
};

void testOneArg(std::string test)
{
    std::cerr << "Test oneArg(" << test << ")" << std::endl;
    do
    {
        std::cerr << "OneArg: [" << oneArg(test, test) << "], remainder [" << test << "]" << std::endl;
    } while (!test.empty());
}

void testOneArg()
{
    std::string test1("This is a crazy long string.  With some      stupid\tspaces");
    std::string test2("");
    std::string test3("only_one_arg_here");
    std::string test4("     only_one_arg_here\t");
    testOneArg(test1);
    testOneArg(test2);
    testOneArg(test3);
    testOneArg(test4);
}
 */

int main(int argc, char *argv[])
{
    /*
    testOneArg();
     */

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
