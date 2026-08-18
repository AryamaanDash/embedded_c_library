#include "state_machine.h"
#include <stddef.h>

_Bool state_machine_initialize(StateMachine* state_machine, State initial_state,
                                const Transition* caller_transition_table,
                                uint32_t caller_transition_table_size){
    if(state_machine == NULL ||
       (caller_transition_table == NULL && caller_transition_table_size > 0)){
        return 0;
    }

    state_machine->current_state = initial_state;
    state_machine->initial_state = initial_state;
    state_machine->transition_table = caller_transition_table;
    state_machine->transition_table_size = caller_transition_table_size;

    return 1;
}

_Bool state_machine_process(StateMachine* state_machine, Event event){
    uint32_t index;

    if(state_machine == NULL){
        return 0;
    }

    for(index = 0; index < state_machine->transition_table_size; ++index){
        const Transition* transition = &state_machine->transition_table[index];

        if(transition->required_current_state == state_machine->current_state &&
           transition->required_event == event){
            state_machine->current_state = transition->next_state;
            return 1;
        }
    }

    return 0;
}

State state_machine_get_current_state(const StateMachine* state_machine){
    if(state_machine == NULL){
        return STATE_OFF;
    }
    return state_machine->current_state;
}

_Bool state_machine_reset(StateMachine* state_machine){
    if(state_machine == NULL){
        return 0;
    }

    state_machine->current_state = state_machine->initial_state;
    return 1;
}
