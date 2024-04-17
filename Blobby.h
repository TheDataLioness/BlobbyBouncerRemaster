#pragma once
#include "Sprite.h"
#include "GameObject.h"

struct BlobbyBody
{
	Sprite* face;
	Sprite* body;
};

struct SquishState
{
	glm::vec3 squishScale = glm::vec3(0.0f);
	float squish = 0.0f;

	bool squash = false;
	float fallOff = 5.0f;
	float frequency = 5.0f;
	float amplitude = 0.5f;
	bool squishComplete = false;
};

enum JumpDirection
{
	Left,
	Right,
	Up
};

class Blobby : public GameObject
{
public:
	Blobby();
	~Blobby() {};
	void Update(float deltaTime) override;
	void UpdateSquish(float deltaTime);
	void Draw(luna::Renderer* renderer);
private:
	BlobbyBody blobbyBody;
	SquishState squishState;

	bool wasHoldingJump = false;
	bool justJumped = false;

	float jumpForce = 0.0f;

};

