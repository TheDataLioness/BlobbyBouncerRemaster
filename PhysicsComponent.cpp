#include "PhysicsComponent.h"
#include "Component.h"
#include "GameObject.h"

PhysicsComponent::PhysicsComponent(GameObject& gameObject) : 
    position(0.0f), 
    velocity(0.0f), 
    mass(1.0f),
    Component(gameObject)
{}

PhysicsComponent::PhysicsComponent(GameObject& gameObject, glm::vec3 position, glm::vec3 velocity, float mass) : 
    position(position), 
    velocity(velocity), 
    mass(mass),
    Component(gameObject)
{}

// Setters
void PhysicsComponent::SetPosition(glm::vec3 position_) 
{
    position = position_;
}

void PhysicsComponent::SetVelocity(glm::vec3 velocity_) 
{
    velocity = velocity_;
}

void PhysicsComponent::SetMass(float mass_) 
{
    mass = mass_;
}

// Getters
glm::vec3 PhysicsComponent::GetPosition() const 
{
    return position;
}

glm::vec3 PhysicsComponent::GetVelocity() const 
{
    return velocity;
}

float PhysicsComponent::GetMass() const 
{
    return mass;
}

void PhysicsComponent::ApplyForce(glm::vec3 force, float deltaTime) 
{
    
    glm::vec3 acceleration = force / mass;
    velocity += acceleration * deltaTime;
}

void PhysicsComponent::ApplyImpulse(glm::vec3 impulse)
{
	velocity += impulse / mass;
}

void PhysicsComponent::Update(float deltaTime) 
{
    // Apply gravity
    ApplyForce(glm::vec3(0.0f, -9.8f, 0.0f), deltaTime);
    
    // Apply drag to horizontal velocity
    velocity.x -= 10.0f * velocity.x * deltaTime;



    // Update position
    position += velocity * deltaTime;

    if (position.y < -5.0f)
    {
        isGrounded = true;
		position.y = -5.0f;
		velocity.y = 0.0f;
    }
    else {
        isGrounded = false;
    }

    gameObject.SetPosition(position);
}
