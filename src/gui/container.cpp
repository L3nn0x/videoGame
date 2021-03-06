#include "gui/container.h"

namespace	GUI
{
	Container::Container() : mChildren(), mSelectedChild(-1)
	{}

	void	Container::pack(Component::Ptr component)
	{
		mChildren.push_back(component);
		if (!hasSelection() && component->isSelectable())
			select_private(mChildren.size() - 1);
	}

	bool	Container::isSelectable() const
	{
		return false;
	}

	void	Container::handleEvent(const sf::Event& event)
	{
		if (hasSelection() && mChildren[mSelectedChild]->isActive())
			mChildren[mSelectedChild]->handleEvent(event);
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
				selectPrevious();
			else if (event.key.code == sf::Keyboard::Down)
				selectNext();
			else if (event.key.code == sf::Keyboard::Return)
				if (hasSelection())
					mChildren[mSelectedChild]->activate();
		}
	}

	bool	Container::hasSelection() const
	{
		return mSelectedChild != -1;
	}

	void	Container::select_private(std::size_t index)
	{
		if (mChildren[index]->isSelectable())
		{
			if (hasSelection())
				mChildren[mSelectedChild]->deselect();
			mChildren[index]->select();
			mSelectedChild = index;
		}
	}

	void	Container::selectNext()
	{
		if (!hasSelection())
			return;
		int	next = mSelectedChild;
		do
			next = (next + 1) % mChildren.size();
		while (!mChildren[next]->isSelectable());
		select_private(next);
	}

	void	Container::selectPrevious()
	{
		if (!hasSelection())
			return;
		int	previous = mSelectedChild;
		do
			previous = (previous + mChildren.size() - 1) % mChildren.size();
		while (!mChildren[previous]->isSelectable());
		select_private(previous);
	}

	void	Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		for (auto& child : mChildren)
			target.draw(*child, states);
	}
}
