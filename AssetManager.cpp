#include "AssetManager.h"
#include "Sprite.h"

Sprite* AssetManager::GetSprite(const char* filepath, FrameCountData frameCountData)
{
	auto sprite = sprites.find(filepath);
	if (sprite == sprites.end())
	{
		sprites[filepath] = new Sprite(filepath, frameCountData);
		return sprites[filepath];
	}
	return sprite->second;
}

void AssetManager::Garbage()
{
	for (auto sprite : sprites)
	{
		delete sprite.second;
	}
	sprites.clear();
}