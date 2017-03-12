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

class Foom
{
public:
    Foom(StringVector& args) : m_args(args) {}

    void testRun()
    {
        std::cout << "Foom::testRun(args[" << m_args.size() << "])" << std::endl;
    }

private:
    StringVector m_args;
};

typedef int(*foom)(Foom *);

int foomTest(Foom *pFoom)
{
    pFoom->testRun();
    return 0;
}

class Woot
{
public:
    Woot(foom fmm) { m_foom = fmm; }

    int doIt(Foom *pFoom) { return m_foom(pFoom); }

    foom m_foom;
};

#include <map>

class Commandable
{
public:
    typedef eCmdResult(*pfnCmd)(Commandable*, const StringVector&);

    Commandable() {}
    virtual ~Commandable() {}

    virtual void initCommands() = 0;

    void registerCommand(const std::string& cmd, pfnCmd fCmd)
    {
        m_cmds[toUpper(cmd)] = fCmd;
    }

    eCmdResult runCommand(const std::string& cmd, const StringVector& args)
    {
        if (m_cmds.empty())
            initCommands();

        std::map<std::string, pfnCmd>::const_iterator itr = m_cmds.find(toUpper(cmd));
        if (itr != m_cmds.end())
        {
            return itr->second(this, args);
        }
        else
        {
            return eCmdResult::E_UNKNOWN;
        }
    }

private:
    std::map<std::string, pfnCmd> m_cmds;
};

class Point
{
public:
    Point() : Point(0, 0) {}
    Point(int x, int y) : m_xPos(x), m_yPos(y) {}

    int& x() { return m_xPos; }
    const int& x() const { return m_xPos; }

    int& y() { return m_yPos; }
    const int& y() const { return m_yPos; }

private:
    int m_xPos, m_yPos;
};

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
        registerCommand("TEST", (pfnCmd)(&testCommand));
    }

private:
    eFacing m_facing;
};

int main(int argc, char *argv[])
{
    //*
    StringVector testArgs;
    testArgs.push_back("TEST");
    testArgs.push_back("42");
    testArgs.push_back("woooot?");

    Foom dummy(testArgs);

    foomTest(&dummy);

    Woot wt(foomTest);
    wt.doIt(&dummy);

    testArgs.push_back("naaaah");

    Turtle ttl;
    ttl.runCommand("test", testArgs);
    /*/
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
    //*/

    return 0;
}
