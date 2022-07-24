/*
 * Editors: Tobias Goetz
 */

#include "StateMachine.h"
#include "Logger.h"

inline std::string eventToString(Event event) {
    switch (event) {
        case Event::GETOPTSETUPSTART:
            return "GETOPTSETUPSTART";
        case Event::GETOPTSETUPEND:
            return "GETOPTSETUPEND";
        case Event::AUTHORSTART:
            return "AUTHORSTART";
        case Event::AUTHOREND:
            return "AUTHOREND";
        case Event::HEADERFILENAMESTART:
            return "HEADERFILENAMESTART";
        case Event::HEADERFILENAMEEND:
            return "HEADERFILENAMEEND";
        case Event::SOURCEFILENAMESTART:
            return "SOURCEFILENAMESTART";
        case Event::SOURCEFILENAMEEND:
            return "SOURCEFILENAMEEND";
        case Event::NAMESPACESTART:
            return "NAMESPACESTART";
        case Event::NAMESPACEEND:
            return "NAMESPACEEND";
        case Event::CLASSNAMESTART:
            return "CLASSNAMESTART";
        case Event::CLASSNAMEEND:
            return "CLASSNAMEEND";
        case Event::OVERALLDESCRIPTIONSTART:
            return "OVERALLDESCRIPTIONSTART";
        case Event::OVERALLDESCRIPTIONEND:
            return "OVERALLDESCRIPTIONEND";
        case Event::BLOCKSTART:
            return "BLOCKSTART";
        case Event::BLOCKEND:
            return "BLOCKEND";
        case Event::SAMPLEUSAGESTART:
            return "SAMPLEUSAGESTART";
        case Event::SAMPLEUSAGEEND:
            return "SAMPLEUSAGEEND";
        case Event::SAMPLESTART:
            return "SAMPLESTART";
        case Event::SAMPLEEND:
            return "SAMPLEEND";
        case Event::OPTIONSSTART:
            return "OPTIONSSTART";
        case Event::OPTIONSEND:
            return "OPTIONSEND";
        case Event::OPTIONSTART:
            return "OPTIONSTART";
        case Event::OPTIONEND:
            return "OPTIONEND";
        default:
            return "UNKNOWN";
    }
}

inline std::string stateToString(State state) {
    switch (state) {
        case State::GETOPTSETUP:
            return "GETOPTSETUP";
        case State::AUTHOR:
            return "AUTHOR";
        case State::HEADERFILENAME:
            return "HEADERFILENAME";
        case State::SOURCEFILENAME:
            return "SOURCEFILENAME";
        case State::NAMESPACE:
            return "NAMESPACE";
        case State::CLASSNAME:
            return "CLASSNAME";
        case State::OVERALLDESCRIPTION:
            return "OVERALLDESCRIPTION";
        case State::BLOCK:
            return "BLOCK";
        case State::SAMPLEUSAGE:
            return "SAMPLEUSAGE";
        case State::SAMPLE:
            return "SAMPLE";
        case State::OPTIONS:
            return "OPTIONS";
        case State::OPTION:
            return "OPTION";
        default:
            return "UNKNOWN";
    }
}

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
    LOG_TRACE("State: " + stateToString(currentState) + " Event: " + eventToString(event));
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
                    currentState = State::OVERALLDESCRIPTION;
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
                    currentState = State::SAMPLEUSAGE;
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
