#include "vector"
#include "array"
#include "Hitbox.h"

class HitboxComponent
{
public:
	HitboxComponent();
	virtual ~HitboxComponent();
	void addHitbox(const Hitbox&& hitbox);
	void setPositionOfHitbox(const int numberOfHitbox, const sf::Vector2f& Position);
	sf::Vector2f getOffset(const int numberOfHitbox) const;
	void moveAllHitboxes(const sf::Vector2f& Offset);
	bool intersects(const sf::FloatRect& floatRect) const;
	bool intersects(const HitboxComponent& hitboxComponent) const;
	bool intersectsWithCircle(const sf::Vector2f& centerOfCircle, float radius) const;

	size_t size() const;
	const std::vector<Hitbox>& getHitboxes() const;
	const Hitbox& operator[](int i) const;

private:
	std::vector<Hitbox> hitboxes;
};
