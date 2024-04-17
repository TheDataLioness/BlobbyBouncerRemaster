#pragma once

class GameObject;

class Component {
    public:
        Component(GameObject& gameObject) : gameObject(gameObject) {}
        virtual void Update(float deltaTime) = 0;
        virtual ~Component() {}
    protected:
        GameObject& gameObject;
};

