#include "Command.h"

Command::Command() 
    : fexecute(false), fundo(false), fisCommand(true) {}

Command::~Command() {}