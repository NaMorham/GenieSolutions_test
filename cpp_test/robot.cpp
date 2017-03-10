#include "robot.h"

//----------------------------------------------------------------------------
const char *toString(eFacing facing)
{
    switch (facing)
    {
    case eFacing::EAST:
        return "EAST";
    case eFacing::SOUTH:
        return "SOUTH";
    case eFacing::WEST:
        return "WEST";
    case eFacing::NORTH:
    default:
        return "NORTH";
    };
}

const eFacing fromString(const std::string& str)
{
    std::string uStr = toUpper(str);
    if (uStr == "N" || uStr == "NORTH")
        return eFacing::NORTH;
    else if (uStr == "E" || uStr == "EAST")
        return eFacing::EAST;
    else if (uStr == "S" || uStr == "SOUTH")
        return eFacing::SOUTH;
    else if (uStr == "W" || uStr == "WEST")
        return eFacing::WEST;
    else
        throw std::invalid_argument(std::string("Invalid facing [").append(str).append("]").c_str());
}

const int toInt(eFacing facing)
{
    return facing - eFacing::NORTH;
}

const eFacing fromInt(const int faceInt)
{
    if (faceInt >= 0 && faceInt <= 3)
    {
        return (eFacing)faceInt;
    }
    else
    {
        std::stringstream ss;
        ss << "Invalid facing [" << faceInt << "]";
        throw std::invalid_argument(ss.str().c_str());
    }
}

//----------------------------------------------------------------------------
int Robot::ms_id = 0;
int Robot::ms_xSize = 5;
int Robot::ms_ySize = 5;

Robot::Robot()
{
	m_xPos = -1;
	m_yPos = -1;
	m_facing = eFacing::NORTH;
}

Robot::~Robot()
{
}

eCmdResult Robot::runCommand(const std::string& rawCmd)
{
    StringVector cmdTokens;
    int count = tokenise(rawCmd, cmdTokens);

    if (count < 1)
    {
        return eCmdResult::S_OK; // do nothing
    }

    std::string cmd = cmdTokens[0];
    StringVector args(cmdTokens.begin()+1, cmdTokens.end());
	if (cmd == "PLACE")
	{
		return place(args);
	}

    if (!isPlaced())
	{
		// not placed yet, report it and fail
		std::cerr << "! Robot has not been placed yet." << std::endl;
		return eCmdResult::E_FAIL;
	}

    if (cmd == "REPORT")
        return report(args);
    else if (cmd == "MOVE")
        return move(args);
    else if (cmd == "LEFT")
        return turnLeft(args);
    else if (cmd == "RIGHT")
        return turnRight(args);
    else
		return eCmdResult::E_UNKNOWN;
}

bool Robot::isPlaced() const
{
	return (m_xPos >= 0 && m_xPos <= ms_xSize && m_yPos >= 0 && m_yPos <= ms_ySize);
}

// Commands
eCmdResult Robot::place(const StringVector& args)
{
    int count(args.size());
	if (count < 3)
	{
		std::cerr << "! Not enough tokens to place robot [" << count << "/3]." << std::endl;
		return eCmdResult::E_INVALID;
	}
	else if (count > 3)
	{
		std::cerr << "! Too many tokens to place robot [" << count << "/3]." << std::endl;
		return eCmdResult::E_INVALID;
	}
	try
	{
		int xPos = std::stoi(args[0]);
		int yPos = std::stoi(args[1]);
		eFacing facing = fromString(args[2]);

		return place(xPos, yPos, facing);
	}
	catch (std::exception &e)
	{
		std::cerr << "! Could not interpret place command." << std::endl;
		return eCmdResult::E_FAIL;
	}
}
eCmdResult Robot::place(const int xPos, const int yPos, const eFacing facing)
{
	if (xPos < 0 || xPos > ms_xSize || yPos < 0 || yPos > ms_ySize)
	{
		std::cerr << "! Invalid position for robot [" << xPos << ", " << yPos << "]" << std::endl;
		return eCmdResult::E_FAIL;
	}
	m_xPos = xPos;
	m_yPos = yPos;
	m_facing = facing;
	return eCmdResult::S_OK;
}

eCmdResult Robot::report(const StringVector& args)
{
    if (args.size() != 0)
    {
        std::cerr << "! Report command does not take arguments." << std::endl;
        return eCmdResult::E_INVALID;
    }
	std::cout << m_xPos << "," << m_yPos << "," << toString(m_facing) << std::endl;
	return eCmdResult::S_OK;
}

eCmdResult Robot::move(const StringVector& args)
{
    if (args.size() != 0)
    {
        std::cerr << "! Move command does not take arguments." << std::endl;
        return eCmdResult::E_INVALID;
    }

    int xPos = m_xPos;
    int yPos = m_yPos;

    switch (m_facing)
    {
    case eFacing::NORTH:
        ++yPos; break;
    case eFacing::SOUTH:
        --yPos; break;
    case eFacing::EAST:
        ++xPos; break;
    case eFacing::WEST:
        --xPos; break;
    };

    if (xPos > ms_xSize || xPos < 0 || yPos > ms_ySize || yPos < 0)
    {
        std::cerr << "! Cannot move.  New position [" << xPos << ", " << yPos << "] is outside the board" << std::endl;
        return eCmdResult::E_FAIL;
    }

    m_xPos = xPos; m_yPos = yPos;

    return eCmdResult::S_OK;
}

eCmdResult Robot::turnLeft(const StringVector& args)
{
    if (args.size() != 0)
    {
        std::cerr << "! Left turn command does not take arguments." << std::endl;
        return eCmdResult::E_INVALID;
    }

    int faceInt((toInt(m_facing) - 1) % 4);
    if (faceInt < 0)    // -1 mod 4 == -1, so check it
        m_facing = eFacing::WEST;
    else
        m_facing = fromInt(faceInt);
    return eCmdResult::S_OK;
}

eCmdResult Robot::turnRight(const StringVector& args)
{
    if (args.size() != 0)
    {
        std::cerr << "! Right turn command does not take arguments." << std::endl;
        return eCmdResult::E_INVALID;
    }

    int faceInt((toInt(m_facing) + 1) % 4);
    m_facing = fromInt(faceInt);
    return eCmdResult::S_OK;
}
