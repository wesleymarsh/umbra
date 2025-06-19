#pragma once

#include <functional>
#include <vector>

using std::function;
using std::pair;
using std::vector;

class Actor;

// TODO: Implement scene graph/scene hierarchy, similar to Maths for Games.

class ActorWorld
{
	friend class Level;

public:
	void Spawn(Actor* actor);
	void Destroy(Actor* actor);

private:
	vector<Actor*> m_actors;
	// A generic collection of pairs of functions matching the signature void (Actor*), and the actor associated.
	vector<pair<function<void(Actor*)>, Actor*>> m_listChanges;

private:
	ActorWorld();
	~ActorWorld();

private:
	void Tick(float dt);
	void Render();
};