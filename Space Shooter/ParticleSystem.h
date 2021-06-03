#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "RandomEngine.h"



class ParticleSystem
	: public sf::Drawable
{
public:
	ParticleSystem();
	void add(const sf::Vector2f& position, int numberOfNewParticles);
	void update(float deltaTime);
private:
	std::vector<sf::Vertex> particles;
	std::vector<sf::Vector2f> velocitiesOfParticles;
	std::vector<float> lifeTimesOfParticlesAsSeconds;
	void deleteParticlesIfLifeTimeIsOver();
	void moveParticles(float deltaTime);
	void updateLifeTimesOfParticles(float deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

