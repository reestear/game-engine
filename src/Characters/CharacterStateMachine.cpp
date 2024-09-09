#include "CharacterStateMachine.h"
#include "iostream"

void CharacterStateMachine::handleInput(Input *input) {
    current_state->handleInput(this, input);
    current_state->enter();
}

void StandingState::handleInput(CharacterStateMachine *state_machine, Input *input) {
    
}

void StandingState::enter() {
    std::cout << "Entering Standing State" << std::endl;
}

void RunningState::handleInput(CharacterStateMachine *state_machine, Input *input) {
    
}

void RunningState::enter() {
    std::cout << "Entering Running State" << std::endl;
}

void JumpingState::handleInput(CharacterStateMachine *state_machine, Input *input) {
    
}

void JumpingState::enter() {
    std::cout << "Entering Jumping State" << std::endl;
}
