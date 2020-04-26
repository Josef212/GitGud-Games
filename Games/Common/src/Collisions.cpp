#include <ggpch.h>
#include "Collisions.h"

#include <GitGud.h>

namespace GitGud::Extensions
{
	struct Bounds
	{
		glm::vec2 BottomLeft;
		glm::vec2 Size;

		bool Collides(const Bounds& other)
		{
			glm::vec2 size = Size;
			glm::vec2 otherSize = other.Size;

			bool xCollision = BottomLeft.x < other.BottomLeft.x + otherSize.x && BottomLeft.x + size.x > other.BottomLeft.x;
			bool yCollision = BottomLeft.y < other.BottomLeft.y + otherSize.y && BottomLeft.y + size.y > other.BottomLeft.y;

			return xCollision && yCollision;
		}
	};

	// -----------------
		
	void Collider2D::OnCollision(Collider2D* collider) const
	{
		if (_callback)
		{
			_callback(collider);
		}
	}

	Collider2D::Collider2D(const glm::vec2& position, CollisionCallback callback, Collider2DType colliderType)
		: _position(position), _callback(callback), _colliderType(colliderType)
	{
	}

	// -----------------


	QuadCollider2D::QuadCollider2D(const glm::vec2& position, const glm::vec2& size, CollisionCallback callback)
		: Collider2D(position, callback, Collider2DType::Quad), _size(size)
	{
	}

	bool QuadCollider2D::CollidesWith(const Collider2D& other) const
	{
		GG_PROFILE_FUNCTION();
		GG_CORE_ASSERT(other.GetColliderType() != Collider2DType::None, "Collider of NONE type is not valid.");

		const QuadCollider2D& quadCollider = static_cast<const QuadCollider2D&>(other);
		
		// TODO: Can optimize this if each collider stores its bounds
		Bounds b1 = { { _position.x - _size.x * 0.5f, _position.y - _size.y * 0.5f }, _size };
		Bounds b2 = { { quadCollider._position.x - quadCollider._size.x * 0.5f, quadCollider._position.y - quadCollider._size.y * 0.5f }, quadCollider._size };
		
		return b1.Collides(b2);
	}

	// -----------------

	CollisionModule* CollisionModule::s_instance = nullptr;

	CollisionModule::CollisionModule()
	{
		GG_CORE_ASSERT(!s_instance, "Collision module already exists!");
		s_instance = this;
	}

	CollisionModule::~CollisionModule()
	{
		GG_PROFILE_FUNCTION();

		for (Collider2D* col : _colliders)
		{
			delete col;
		}
	}

	void CollisionModule::Update(float dt)
	{
		// Remove dirty colliders
		for (auto it = _colliders.begin(); it != _colliders.end();)
		{
			if (_dirtyColliders.find(*it) != _dirtyColliders.end())
			{
				it = _colliders.erase(it);
			}
			else
			{
				++it;
			}
		}

		_dirtyColliders.clear();

		// Check collisions
		for (auto it1 = _colliders.begin(); it1 != _colliders.end(); ++it1)
		{
			//for (auto it2 = _colliders.begin(); it2 != _colliders.end(); ++it2)
			for (auto it2 = std::next(it1); it2 != _colliders.end(); ++it2)
			{
				if ((*it1) == (*it2))
				{
					continue;
				}

				if ((*it1)->CollidesWith(*(*it2)))
				{
					// TODO: Set layers and check against them
					(*it1)->OnCollision(*(it2));
					(*it2)->OnCollision(*(it1));
				}
			}
		}
	}

	void CollisionModule::AddCollider(Collider2D* collider)
	{
		_colliders.push_back(collider);
	}

	void CollisionModule::RemoveCollider(Collider2D* collider)
	{
		GG_CORE_ASSERT(std::find(_colliders.begin(), _colliders.end(), collider) != _colliders.end(), 
			"Can't remove collider that's not added to collission module.");

		_dirtyColliders.insert(collider);
	}

	void CollisionModule::DrawDebug()
	{
		for (auto col : *this)
		{
			if (col->GetColliderType() == GitGud::Extensions::Collider2DType::Quad)
			{
				auto quadCollider = static_cast<GitGud::Extensions::QuadCollider2D*>(col);

				auto pos = quadCollider->GetPositon();
				auto size = quadCollider->GetSize();

				Renderer2D::DrawQuad({ pos.x, pos.y, 1.0f }, size, { 0.9f, 0.2f, 0.3f, 0.8f });
			}
		}
	}
}
