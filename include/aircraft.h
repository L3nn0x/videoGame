
#ifndef _AIRCRAFT_H_
# define _AIRCRAFT_H_

#include "entity.h"
#include "texturesholder.h"

class	Aircraft : public Entity
{
	public:
		enum 	Type
		{
			Eagle,
			Raptor,
		};

		Aircraft(Type type, const TextureHolder& textures);

		virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual unsigned int	getCategory() const;

	private:
		Type		mType;
		sf::Sprite	mSprite;
};

Textures::ID	toTextureID(Aircraft::Type type);

struct	AircraftMover
{
	AircraftMover(float vx, float vy) : velocity(vx, vy)
	{}

	void	operator()(Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity);
	}
	sf::Vector2f	velocity;
};

#endif /* !_AIRCRAFT_H_ */
