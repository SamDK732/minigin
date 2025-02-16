#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>

namespace dae
{
	template<typename T>
	concept ComponentConcept = std::is_base_of_v<Component, T>;

	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;

		const Transform& GetTransform() const { return m_Transform; }
		Transform& GetTransform() { return m_Transform; }

		//Components
		template<typename T>
		void AddComponent(T&& component) requires ComponentConcept<std::decay_t<decltype(*component)>>;

		template<typename ComponentT>
		[[nodiscard]] ComponentT* GetComponent() const requires ComponentConcept<ComponentT>;

		template<typename ComponentT>
		bool HasComponent() const requires ComponentConcept<ComponentT>
		{
			return GetComponent<ComponentT>() != nullptr;
		}

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::unordered_set<std::type_index> m_AddedComponentsRegistry;
		std::vector<std::unique_ptr<Component>> m_pComponents;
		Transform m_Transform{};
	};

	template<typename T>
	void GameObject::AddComponent(T&& component)
		requires ComponentConcept<std::decay_t<decltype(*component)>>
	{
		using ComponentType = std::decay_t<decltype(*component)>;
		if (m_AddedComponentsRegistry.insert(typeid(ComponentType)).second)
		{
			m_pComponents.emplace_back(std::forward<T>(component));
		}
		else
		{
			throw std::runtime_error("Component already added");
		}
	}

	template<typename ComponentT>
	ComponentT* GameObject::GetComponent() const requires ComponentConcept<ComponentT>
	{
		for (const auto& ptr : m_pComponents)
		{
			if (auto* component = dynamic_cast<ComponentT*>(ptr.get()))
				return component;
		}
		return nullptr;
	}
}
