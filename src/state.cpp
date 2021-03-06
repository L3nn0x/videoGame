#include "state.h"
#include "statestack.h"

State::State(StateStack& stack, Context context) : mStack(&stack), mContext(*context.window,
		*context.textures, *context.fonts, *context.player)
{}

State::~State()
{}

State::Context	State::getContext() const
{
	return mContext;
}

void	State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void	State::requestStackPop()
{
	mStack->popState();
}

void	State::requestStackClear()
{
	mStack->clearStates();
}
