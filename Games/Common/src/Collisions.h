#pragma once

#include <glm/glm.hpp>

#include <functional>
#include <unordered_set>

namespace GitGud::Extensions
{
	enum class Collider2DType
	{
		None = 0,
		Quad
	};

	class Collider2D
	{
	public:
		using CollisionCallback = std::function<void(Collider2D*)>;

		inline const glm::vec2& GetPositoon() const { return _position; }
		inline void SetPosition(float x, float y) { _position = { x, y }; }

		inline Collider2DType GetColliderType() const { return _colliderType; }
		void OnCollision(Collider2D* collider) const;

		virtual bool CollidesWith(const Collider2D& other) const = 0;

	protected:
		Collider2D(const glm::vec2& position, CollisionCallback callback, Collider2DType _colliderType);

	protected:
		glm::vec2 _position;

		CollisionCallback _callback;
		Collider2DType _colliderType;
	};

	class QuadCollider2D : public Collider2D
	{
	public:
		QuadCollider2D(const glm::vec2& position, const glm::vec2& size, CollisionCallback callback = nullptr);

		virtual bool CollidesWith(const Collider2D& other) const override;

		inline const glm::vec2& GetSize() const { return _size; }
		inline void SetSize(float x, float y) { _size = { x, y }; }

	private:
		glm::vec2 _size;
	};

	class CollisionModule
	{
	public:
		CollisionModule();
		~CollisionModule();

		void Update(float dt);

		void AddCollider(Collider2D* collider);
		void RemoveCollider(Collider2D* collider);

		std::vector<Collider2D*>::iterator begin() { return _colliders.begin(); }
		std::vector<Collider2D*>::iterator end() { return _colliders.end(); }

		const std::vector<Collider2D*>::const_iterator begin() const { return _colliders.begin(); }
		const std::vector<Collider2D*>::const_iterator end() const { return _colliders.end(); }

	private:
		std::vector<Collider2D*> _colliders;
		std::unordered_set<Collider2D*> _dirtyColliders;
	};
}