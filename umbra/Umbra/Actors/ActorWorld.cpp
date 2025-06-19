#include "ActorWorld.h"

#include "Actor.h"
#include "ActorTransform.h"

void ActorWorld::Spawn(Actor* actor)
{
	// Verify the spawning actor isn't already spawned
	if (std::ranges::find(m_actors, actor) != m_actors.end())
	{
		return;
	}

	m_listChanges.emplace_back([this](Actor* spawned)
		{
			spawned->BeginPlay();
			m_actors.emplace_back(spawned);
		}, actor);
}

void ActorWorld::Destroy(Actor* actor)
{
	// Verify the actor we want to destroy is spawned
	if (std::ranges::find(m_actors, actor) == m_actors.end())
	{
		return;
	}

	m_listChanges.emplace_back([this](Actor* spawned)
		{
			spawned->EndPlay();
			m_actors.erase(std::ranges::find(m_actors, spawned));
			delete spawned;
		}, actor);
}

ActorWorld::ActorWorld() = default;

ActorWorld::~ActorWorld()
{
	// apply any remaining changes (in case an actor is in the process of being spawned)
	for (auto& [func, actor] : m_listChanges)
	{
		func(actor);
	}

	m_listChanges.clear();

	// delete all actors
	for (Actor* actor : m_actors)
	{
		delete actor;
	}

	m_actors.clear();
}

void ActorWorld::Tick(float dt)
{
	// apply all changes to the actor list
	for (auto& [func, actor] : m_listChanges)
	{
		func(actor);
	}

	m_listChanges.clear();

	for (Actor* actor : m_actors)
	{
		actor->Tick(dt);
		actor->Transform()->Update();
	}
}

void ActorWorld::Render()
{
	for (Actor* actor : m_actors)
	{
		actor->Render();
	}
}
