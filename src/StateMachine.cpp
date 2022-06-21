#include "StateMachine.h"

// Constructor
StateMachine::StateMachine() {
    currentState = State::START;
}


// Getters
State StateMachine::getState() const {
    return currentState;
}


// Setters
void StateMachine::setState(State state) {
    currentState = state;
}


// Methods
void StateMachine::handleEvent(Event event) {
    switch (currentState) {
        case State::START:
            switch (event) {
                case Event::GETOPTSETUPSTART:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        case State::GETOPTSETUP:
            switch (event) {
                case Event::GETOPTSETUPEND:
                    currentState = State::END;
                    break;
                case Event::AUTHORSTART:
                    currentState = State::AUTHOR;
                    break;
                case Event::HEADERFILENAMESTART:
                    currentState = State::HEADERFILENAME;
                    break;
                case Event::SOURCEFILENAMESTART:
                    currentState = State::SOURCEFILENAME;
                    break;
                case Event::NAMESPACESTART:
                    currentState = State::NAMESPACE;
                    break;
                case Event::CLASSNAMESTART:
                    currentState = State::CLASSNAME;
                    break;
                case Event::OVERALLDESCRIPTIONSTART:
                    currentState = State::OVERALLDESCRIPTION;
                    break;
                case Event::SAMPLEUSAGESTART:
                    currentState = State::SAMPLEUSAGE;
                    break;
                case Event::OPTIONSSTART:
                    currentState = State::OPTIONS;
                    break;
                default:
                    break;
            }
            break;
        case State::AUTHOR:
            switch (event) {
                case Event::AUTHOREND:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        case State::HEADERFILENAME:
            switch (event) {
                case Event::HEADERFILENAMEEND:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        case State::SOURCEFILENAME:
            switch (event) {
                case Event::SOURCEFILENAMEEND:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        case State::NAMESPACE:
            switch (event) {
                case Event::NAMESPACEEND:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        case State::CLASSNAME:
            switch (event) {
                case Event::CLASSNAMEEND:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        case State::OVERALLDESCRIPTION:
            switch (event) {
                case Event::OVERALLDESCRIPTIONEND:
                    currentState = State::GETOPTSETUP;
                    break;
                case Event::BLOCKSTART:
                    currentState = State::BLOCK;
                    break;
                default:
                    break;
            }
            break;
        case State::BLOCK:
            switch (event) {
                case Event::BLOCKEND:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        case State::SAMPLEUSAGE:
            switch (event) {
                case Event::SAMPLEUSAGEEND:
                    currentState = State::GETOPTSETUP;
                    break;
                case Event::SAMPLESTART:
                    currentState = State::SAMPLE;
                    break;
                default:
                    break;
            }
            break;
        case State::SAMPLE:
            switch (event) {
                case Event::SAMPLEEND:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        case State::OPTIONS:
            switch (event) {
                case Event::OPTIONSEND:
                    currentState = State::GETOPTSETUP;
                    break;
                case Event::OPTIONSTART:
                    currentState = State::OPTION;
                    break;
                default:
                    break;
            }
            break;
        case State::OPTION:
            switch (event) {
                case Event::OPTIONEND:
                    currentState = State::GETOPTSETUP;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
