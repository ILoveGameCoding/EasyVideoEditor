#pragma once
class Command
{
private:
    // An enumeration of the type of command.
    enum CommandType {
        COLOR_EMPHASIS, CHANGE_BRIGHTNESS, CHANGE_CONTRAST, FILTER_EFFECT, CHROMAKY, ANIMATION
        , ADD_IMAGE, ADD_VIDEO, CUT_VIDEO, RESIZE_RESOLUTION, CHANGE_PLAY_SPEED, ADD_SUBTITLE
    };

    // Command type.
    CommandType commandType;
public:
    // Default constructor.
    Command();

    // Default destructor.
    ~Command();

    // A pure virtual function overloaded with an operator that must be implemented in relation to a command in a class that inherits Command class.
    virtual void operator()() = 0;

    // Command type setter.
    void setCommand(CommandType commandType);
    // Command type getter.
    CommandType getCommand();
};