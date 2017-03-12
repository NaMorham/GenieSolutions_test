#pragma once

#include "util.h"

#include <map>
#include <set>

// facing
enum eFacing
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

const char *toString(eFacing facing);
const eFacing fromString(const std::string& str);
const int toInt(eFacing facing);
const eFacing fromInt(const int faceInt);

// command results
enum eCmdResult
{
	S_OK,
	E_FAIL,
	E_INVALID,
    E_UNKNOWN
};

inline bool cmdOK(eCmdResult res) { return res == eCmdResult::S_OK; }

inline const char * string(eCmdResult res) { return (res == eCmdResult::S_OK ? "OK"
                : (res == eCmdResult::E_FAIL ? "FAIL" 
                : (res == eCmdResult::E_INVALID ? "INVALID" : "UNKNOWN"))); }

class Commandable
{
public:
    typedef eCmdResult(*pfnCmd)(Commandable*, const StringVector&);

    class CommandDetails
    {
    public:
        CommandDetails() : m_minArgs(0), m_pfnCmd(nullptr) {}
        CommandDetails(size_t minArgs, pfnCmd pfnCmd) : m_minArgs(minArgs), m_pfnCmd(pfnCmd) {}
        CommandDetails(const CommandDetails& orig) : m_minArgs(orig.m_minArgs), m_pfnCmd(orig.m_pfnCmd) {}
        size_t m_minArgs;
        pfnCmd m_pfnCmd;
    };
    typedef std::map<std::string, CommandDetails> CommandMap;

    Commandable() {}
    virtual ~Commandable() {}

    virtual void initCommands() = 0;

    void registerCommand(const std::string& cmd, const size_t minArgs, pfnCmd fCmd)
    {
        m_cmds[toUpper(cmd)] = CommandDetails(minArgs, fCmd);
    }

    virtual eCmdResult displayHelp();

    eCmdResult executeCommand(const std::string& cmd, const StringVector& args);

private:
    CommandMap m_cmds;
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

protected:
    int m_xPos, m_yPos;
};

// --- Robot ---
class Robot : public Point, Commandable
{
public:
    static inline const int getMaxX() { return ms_xSize; }
    static inline const int getMaxY() { return ms_ySize; }

    Robot();
    Robot(const int x, const int y, const eFacing facing);
    virtual ~Robot();

    eCmdResult runCommand(const std::string& cmd);
    bool isPlaced() const;

    // Commands
    static eCmdResult placeCommand(Robot *pRobot, const StringVector& args) { return pRobot->place(args); }
    static eCmdResult reportCommand(Robot *pRobot, const StringVector& args) { return pRobot->report(args); }
    static eCmdResult moveCommand(Robot *pRobot, const StringVector& args) { return pRobot->move(args); }
    static eCmdResult turnLeftCommand(Robot *pRobot, const StringVector& args) { return pRobot->turnLeft(args); }
    static eCmdResult turnRightCommand(Robot *pRobot, const StringVector& args) { return pRobot->turnRight(args); }

protected:
    virtual void initCommands();

private:
    eCmdResult place(const StringVector& args);
    eCmdResult report(const StringVector& args);
    eCmdResult move(const StringVector& args);
    eCmdResult turnLeft(const StringVector& args);
    eCmdResult turnRight(const StringVector& args);
    eCmdResult place(const int xPos, const int yPos, const eFacing facing);

    eFacing m_facing;

    // bounds
    static int ms_id;
    static int ms_xSize;
    static int ms_ySize;
};

