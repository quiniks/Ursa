#include "ursapch.h"
#include "Entity.h"

namespace Ursa {
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}
}