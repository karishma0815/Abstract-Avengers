#ifndef COMMAND_H
#define COMMAND_H

class Command {
protected:
    bool fexecute;
    bool fundo;
    bool fisCommand;

public:
    Command();
    virtual ~Command();
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual bool isCommand() = 0;
};

#endif