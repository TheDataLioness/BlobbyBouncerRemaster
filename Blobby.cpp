#include "Blobby.h"
#include "Sprite.h"
#include "AssetManager.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

#include <iostream>

Blobby::Blobby()
{
	blobbyBody.body = AssetManager::GetInstance().GetSprite("assets/Blobby.png");
	blobbyBody.face = AssetManager::GetInstance().GetSprite("assets/BlobbyFace.png");	

	position = glm::vec3(0.0f, 0.0f, 0.0f);


	// Add components
	AddComponent<PhysicsComponent>(*this);
}

void Blobby::Update(float deltaTime)
{

	bool wasGrounded = false;

	PhysicsComponent* physicsComponent = GetComponent<PhysicsComponent>();
	if (physicsComponent) wasGrounded = physicsComponent->IsGrounded();

	UpdateComponents(deltaTime);
	bool grounded = physicsComponent->IsGrounded();

	if (physicsComponent)
	{
		// Jump logic
		if (luna::Input::isKeyDown(luna::Key::Space) && grounded)
		{
			wasHoldingJump = true;
			squishState.squishComplete = true;
			squishState.squishScale.y = glm::mix(squishState.squishScale.y, 0.5f, deltaTime);
			squishState.squishScale.x = 1.0f / squishState.squishScale.y;

			// Jump force from 0 to 1
			jumpForce = glm::clamp(0.5f / squishState.squishScale.y, 0.0f, 1.0f);
		}

		if (!luna::Input::isKeyDown(luna::Key::Space) && wasHoldingJump)
		{
			wasHoldingJump = false;

			// Apply jump force
			float xForce = 0.0f;
			if (luna::Input::isKeyDown(luna::Key::A)) xForce = -1.0f;
			if (luna::Input::isKeyDown(luna::Key::D)) xForce = 1.0f;

			physicsComponent->ApplyImpulse(glm::vec3(xForce * 10.0 * jumpForce, 7.5f * jumpForce, 0.0f));
			justJumped = true;
			squishState.squishComplete = true;

			squishState.squishComplete = false;
			squishState.squash = true;
			squishState.squish = 0.0f;
			squishState.amplitude = jumpForce;
		}

		//if (!grounded && justJumped) {
		//	// Squish based on velocity
		//	float squish = abs(physicsComponent->GetVelocity().y);
		//	squishState.squishScale.y = 1.0f + squish*squish*0.01f; //glm::mix(1.0f, 2.0f, squish);
		//	squishState.squishScale.x = 1.0f / squishState.squishScale.y;
		//}

		// Update Squish
		if (!wasGrounded && grounded)
		{
			if (justJumped) {
				squishState.amplitude = 0.5f;
			}
			else {
				squishState.amplitude = 0.1f;
			}

			squishState.squish = 0.0f;
			squishState.squash = false;
			justJumped = false;

		}

		UpdateSquish(deltaTime);
	}
	if(luna::Input::isKeyDown(luna::Key::A)) flipped = true;
	if(luna::Input::isKeyDown(luna::Key::D)) flipped = false;
}

void Blobby::Draw(luna::ForwardRenderer* renderer)
{
	glm::vec3 drawScale = blobbyBody.body->GetScale();
	glm::vec3 offset = glm::vec3(0.0f, drawScale.y * squishState.squishScale.y/2.0f, 0.0f);

	blobbyBody.face->Draw(position + offset + glm::vec3(0.0f,0.0f,0.1f), scale, 0.0f, renderer);
	blobbyBody.body->Draw(position + offset + glm::vec3((flipped ? 0.1f : 0.0f),0.0f,0.1f), squishState.squishScale, 0.0f, renderer);
}

void Blobby::UpdateSquish(float deltaTime) 
{
	if (squishState.squishComplete && squishState.squish == 0.0f) squishState.squishComplete = false;
	squishState.squish += deltaTime;
	
	if (!squishState.squishComplete) {
		if (!squishState.squash)
		{
			squishState.squishScale.x = 1.0f + exp(-squishState.fallOff * squishState.squish) * sin(squishState.frequency * luna::Tau * squishState.squish) * squishState.amplitude;
			squishState.squishScale.y = 1.0f / squishState.squishScale.x;
		}
		else {
			squishState.squishScale.y = 1.0f + exp(-squishState.fallOff * squishState.squish) * sin(squishState.frequency * luna::Tau * squishState.squish) * squishState.amplitude;
			squishState.squishScale.x = 1.0f / squishState.squishScale.y;
		}

		if (squishState.squish >= 5.0f) {
			squishState.squishComplete = true;
		}
	}
}