#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <stdint.h>

typedef enum{
    STATE_OFF,
    STATE_ON,
    STATE_BLINKING
} State;

typedef enum{
    EVENT_NONE,
    EVENT_BUTTON_PRESSED,
    EVENT_RESET
} Event;

typedef struct{
    State required_current_state;
    Event required_event;
    State next_state;
} Transition;

typedef struct{
    State current_state;
    State initial_state;
    const Transition* transition_table;
    uint32_t transition_table_size;
} StateMachine;

_Bool state_machine_initialize(StateMachine* state_machine, State initial_state, const Transition* caller_transition_table, uint32_t caller_transition_table_size);
_Bool state_machine_process(StateMachine* state_machine, Event event);   
State state_machine_get_current_state(const StateMachine* state_machine);
_Bool state_machine_reset(StateMachine* state_machine);

#endif