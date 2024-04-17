#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class PhysicsComponent : public Component {
    public:
        // Constructors
        PhysicsComponent(GameObject& gameObject);
        PhysicsComponent(GameObject& gameObject, glm::vec3 position, glm::vec3 velocity, float mass);

        void SetPosition(glm::vec3 position);
        void SetVelocity(glm::vec3 velocity);
        void SetMass(float mass);
        
        glm::vec3 GetPosition() const;
        glm::vec3 GetVelocity() const;
        float GetMass() const;
        bool IsGrounded() const { return isGrounded; }

        void ApplyForce(glm::vec3 force, float deltaTime);
        void ApplyImpulse(glm::vec3 impulse);
        void Update(float deltaTime) override;

    private:
        glm::vec3 position;
        glm::vec3 velocity;
        float mass;

        // States
        bool isGrounded = false;
};


