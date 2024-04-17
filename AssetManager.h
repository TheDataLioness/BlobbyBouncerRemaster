#pragma once
#include <unordered_map>
#include "Sprite.h"

class AssetManager
{
public:
	AssetManager() = default;
	~AssetManager() = default;
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;
	AssetManager(const AssetManager&&) = delete;
	AssetManager& operator=(const AssetManager&&) = delete;


	static AssetManager& GetInstance() {
		static AssetManager instance;
		return instance;
	}
	Sprite* GetSprite(const char* filepath, FrameCountData frameCountData = { 1, 1 });

	void Garbage();

private:
	std::unordered_map<const char*, Sprite*> sprites;
};

