#pragma once

#include "util.h"

// facing
typedef enum eFacing
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

class Robot
{
public:
    static inline const int getMaxX() { return ms_xSize; }
    static inline const int getMaxY() { return ms_ySize; }

    Robot();
    virtual ~Robot();

    eCmdResult runCommand(const std::string& cmd);
    bool isPlaced() const;

    // Commands
    eCmdResult place(const StringVector& args);
    eCmdResult report(const StringVector& args);
    eCmdResult move(const StringVector& args);
    eCmdResult turnLeft(const StringVector& args);
    eCmdResult turnRight(const StringVector& args);

private:
    eCmdResult place(const int xPos, const int yPos, const eFacing facing);

    int m_xPos;
    int m_yPos;
    eFacing m_facing;

    // bounds
    static int ms_id;
    static int ms_xSize;
    static int ms_ySize;
};

