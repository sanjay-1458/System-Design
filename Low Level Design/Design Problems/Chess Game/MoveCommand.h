#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

class MoveCommand {

public:

    virtual void execute() = 0;

    virtual void undo() = 0;

    virtual ~MoveCommand() = default;
};

#endif