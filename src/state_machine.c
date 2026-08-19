#include "state_machine.h"
#include <stddef.h>

static _Bool state_is_valid(State state){
    return state >= STATE_OFF && state < STATE_COUNT;
}

static _Bool event_is_valid(Event event){
    return event >= EVENT_NONE && event < EVENT_COUNT;
}

static _Bool transition_table_is_valid(const Transition* transition_table,
                                       uint32_t transition_table_size){
    uint32_t index;
    uint32_t previous_index;

    if(transition_table == NULL){
        return transition_table_size == 0;
    }

    for(index = 0; index < transition_table_size; ++index){
        const Transition* transition = &transition_table[index];

        if(!state_is_valid(transition->required_current_state) ||
           !event_is_valid(transition->required_event) ||
           !state_is_valid(transition->next_state)){
            return 0;
        }

        for(previous_index = 0; previous_index < index; ++previous_index){
            const Transition* previous = &transition_table[previous_index];

            if(previous->required_current_state == transition->required_current_state &&
               previous->required_event == transition->required_event){
                return 0;
            }
        }
    }

    return 1;
}

_Bool state_machine_initialize(StateMachine* state_machine, State initial_state,
                               const Transition* caller_transition_table,
                               uint32_t caller_transition_table_size){
    if(state_machine == NULL ||
       !state_is_valid(initial_state) ||
       !transition_table_is_valid(caller_transition_table,
                                  caller_transition_table_size)){
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

    if(state_machine == NULL ||
       !state_is_valid(state_machine->current_state) ||
       !event_is_valid(event) ||
       (state_machine->transition_table == NULL &&
        state_machine->transition_table_size > 0)){
        return 0;
    }

    for(index = 0; index < state_machine->transition_table_size; ++index){
        const Transition* transition = &state_machine->transition_table[index];

        if(transition->required_current_state == state_machine->current_state &&
           transition->required_event == event){
            if(!state_is_valid(transition->next_state)){
                return 0;
            }

            state_machine->current_state = transition->next_state;
            return 1;
        }
    }

    return 0;
}

State state_machine_get_current_state(const StateMachine* state_machine){
    if(state_machine == NULL || !state_is_valid(state_machine->current_state)){
        return STATE_INVALID;
    }
    return state_machine->current_state;
}

_Bool state_machine_reset(StateMachine* state_machine){
    if(state_machine == NULL || !state_is_valid(state_machine->initial_state)){
        return 0;
    }

    state_machine->current_state = state_machine->initial_state;
    return 1;
}
