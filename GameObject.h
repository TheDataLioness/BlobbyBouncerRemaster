#pragma once

#include "Component.h"
#include <vector>
#include <memory>
#include <type_traits>
#include <glm/glm.hpp>

class Component;


class GameObject {
    public:
        GameObject() {};

        template <typename T, typename... Args>
        void AddComponent(Args&&... args) {
            components.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        }

        void UpdateComponents(float deltaTime) {
            for (const auto& component : components) {
                component->Update(deltaTime);
            }
        }

        template <typename T>
        T* GetComponent() const {
            for (const auto& component : components) {
                if (dynamic_cast<T*>(component.get()) != nullptr) {
                    return static_cast<T*>(component.get());
                }
            }
            return nullptr; // Return nullptr if component of type T is not found
        }

        void SetPosition(glm::vec3 position_) {
			position = position_;
		}

        void SetScale(glm::vec3 scale_) {
			scale = scale_;
		}

        void SetRotation(float rotation_) {
			rotation = rotation_;
		}

        void SetFlipped(bool flipped_) {
			flipped = flipped_;
		}

        glm::vec3 GetPosition() const {
			return position;
		}

        glm::vec3 GetScale() const {
			return scale;
		}

        float GetRotation() const {
			return rotation;
		}

        bool GetFlipped() const {
			return flipped;
		}

		virtual void Update(float deltaTime) = 0;

private:
    std::vector<std::unique_ptr<Component>> components;

protected:
    glm::vec3 position{0.0f};
    glm::vec3 scale{1.0f};
    float rotation{0.0f};
    bool flipped = false;
};
