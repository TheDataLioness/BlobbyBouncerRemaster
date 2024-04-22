#include "PhysicsComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "imgui.h"

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
    prevVelocity = velocity;
}

void PhysicsComponent::Update(float deltaTime) 
{
    
    if (ImGui::BeginTabItem("Physics")) // Physics Editor
    {
        ImGui::DragFloat("Ground Drag", &groundDrag, 0.1f, 0.0f, 50.0f, "%.2f");
        ImGui::DragFloat("Gravity", &gravity, 0.1f, 0.0f, 50.0f, "%.2f");

        ImGui::Text("Max Y: %f", maxY);
        if(ImGui::Button("Reset Max Y")) maxY = -10000000000.0f;
        ImGui::EndTabItem();
    }

    // Apply gravity
    ApplyForce(glm::vec3(0.0f, -gravity * mass, 0.0f), deltaTime);


    // Apply drag
    if (isGrounded) {
        float blend = glm::pow(0.5f, deltaTime * groundDrag);
        velocity.x = glm::mix(0.0f, velocity.x, blend);
    }


    // Bounce off walls
    if (position.x > 5.0f) {
        position.x = 5.0f;
        velocity.x = -velocity.x;
        prevVelocity.x = -prevVelocity.x;
    }
    if (position.x < -5.0f) {
        position.x = -5.0f;
        velocity.x = -velocity.x;
        prevVelocity.x = -prevVelocity.x;
    }

    


    // Update position
    position += ((velocity + prevVelocity) / 2.0f) * deltaTime;

    if (position.y > maxY) {
        maxY = position.y;
    }

    if (position.y < -5.0f)
    {
        isGrounded = true;
		position.y = -5.0f;
		velocity.y = 0.0f;
    }
    else {
        isGrounded = false;
    }

    prevVelocity = velocity;
    gameObject.SetPosition(position);
}
