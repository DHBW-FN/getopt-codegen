#ifndef CODEGENERATOR_STATEMACHINE_H
#define CODEGENERATOR_STATEMACHINE_H

/**
 * @brief States
 * States of the state machine.
 */
enum class State {
    START,
    GETOPTSETUP,
    AUTHOR,
    HEADERFILENAME,
    SOURCEFILENAME,
    NAMESPACE,
    CLASSNAME,
    OVERALLDESCRIPTION,
    BLOCK,
    SAMPLEUSAGE,
    SAMPLE,
    OPTIONS,
    OPTION,
    END
};

/**
 * @brief The Event enum
 * Events that can be triggered and will be handled by the state machine.
 */
enum class Event {
    GETOPTSETUPSTART,
    GETOPTSETUPEND,
    AUTHORSTART,
    AUTHOREND,
    HEADERFILENAMESTART,
    HEADERFILENAMEEND,
    SOURCEFILENAMESTART,
    SOURCEFILENAMEEND,
    NAMESPACESTART,
    NAMESPACEEND,
    CLASSNAMESTART,
    CLASSNAMEEND,
    OVERALLDESCRIPTIONSTART,
    OVERALLDESCRIPTIONEND,
    BLOCKSTART,
    BLOCKEND,
    SAMPLEUSAGESTART,
    SAMPLEUSAGEEND,
    SAMPLESTART,
    SAMPLEEND,
    OPTIONSSTART,
    OPTIONSEND,
    OPTIONSTART,
    OPTIONEND
};

/**
 * @brief The StateMachine class
 * State machine that handles the events and transitions.
 * @see Event
 * @see State
 * @see StateMachine::handleEvent
 */
class StateMachine {
public:
    // Constructor
    /**
     * @brief StateMachine
     * Constructor.
     */
    StateMachine();

    // Getters
    /**
     * @brief getCurrentState
     * Getter for the current state.
     * @return Current state.
     */
    State getState() const;

    // Setters
    /**
     * @brief setState
     * Setter for the current state.
     * @param state New state.
     */
    void setState(State state);

    // Methods
    /**
     * @brief handleEvent
     * Handles an event.
     * @param event Event to handle.
     */
    void handleEvent(Event event);

private:
    State currentState;
};


#endif //CODEGENERATOR_STATEMACHINE_H
