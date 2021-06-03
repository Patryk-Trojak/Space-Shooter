#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

void ParticleSystem::add(const sf::Vector2f& position, int numberOfNewParticles)
{
	for (int i = 0; i < numberOfNewParticles; i++)
	{
		particles.emplace_back(position, sf::Color(200,200,200));
		float angle = RandomEngine::randInt(0, 360) * 3.14f / 180.f;
		float velocity = static_cast<float>(RandomEngine::randInt(50, 200));
		velocitiesOfParticles.emplace_back(velocity * std::cos(angle), velocity * std::sin(angle));
		lifeTimesOfParticlesAsSeconds.emplace_back(static_cast<float>(RandomEngine::randInt(1, 3)));
	}
}

void ParticleSystem::update(float deltaTime)
{
	updateLifeTimesOfParticles(deltaTime);
	deleteParticlesIfLifeTimeIsOver();
	moveParticles(deltaTime);
}

void ParticleSystem::deleteParticlesIfLifeTimeIsOver()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (lifeTimesOfParticlesAsSeconds[i] <= 0.f)
		{
			particles.erase(particles.begin() + i);
			velocitiesOfParticles.erase(velocitiesOfParticles.begin() + i);
			lifeTimesOfParticlesAsSeconds.erase(lifeTimesOfParticlesAsSeconds.begin() + i);
		}
	}
}

void ParticleSystem::moveParticles(float deltaTime)
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i].position += velocitiesOfParticles[i] * deltaTime;
	}
}

void ParticleSystem::updateLifeTimesOfParticles(float deltaTime)
{
	for (auto& i : lifeTimesOfParticlesAsSeconds)
	{
		i -= deltaTime;
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!particles.empty())
		target.draw(&particles[0], particles.size(), sf::Points);
}
