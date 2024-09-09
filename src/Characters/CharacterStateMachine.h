#pragma once
#ifndef CHARACTER_STATE_MACHINE_H
#define CHARACTER_STATE_MACHINE_H

class Input;
class Character;

class CharacterStateMachine;

// Base class for all Character States
class CharacterState {
    public:
        virtual void handleInput(CharacterStateMachine *state_machine, Input *input) = 0;
        virtual void enter() = 0;

        virtual ~CharacterState() = default;
        
};

class StandingState : public CharacterState {
    public:
        virtual void handleInput(CharacterStateMachine *state_machine, Input *input) override;
        virtual void enter() override;
    private:

};

class RunningState : public CharacterState {
    public:
        virtual void handleInput(CharacterStateMachine *state_machine, Input *input) override;
        virtual void enter() override;
    private:

};

class JumpingState : public CharacterState {
    public:
        virtual void handleInput(CharacterStateMachine *state_machine, Input *input) override;
        virtual void enter() override;
    private:

};

class FallingState : public CharacterState {
    public:
        virtual void handleInput(CharacterStateMachine *state_machine, Input *input) override;
        virtual void enter() override;
    private:

};

class AttackingState : public CharacterState {
    public:
        virtual void handleInput(CharacterStateMachine *state_machine, Input *input) override;
        virtual void enter() override;
    private:

};

class CrouchingState : public CharacterState {
    public:
        virtual void handleInput(CharacterStateMachine *state_machine, Input *input) override;
        virtual void enter() override;
    private:

};

// Base class for other State Machines
class CharacterStateMachine {
    public:
        // All Characters will have these states
        StandingState *standing;
        RunningState *running;
        JumpingState *jumping;
        FallingState *falling;
        AttackingState *attacking;
        CrouchingState *crouching;

        virtual void handleInput(Input *input);

    private:
        CharacterState *current_state;
        Character *character;
};


#endif // CHARACTER_STATE_MACHINE_H
