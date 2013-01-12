#include "GameState.h"

#include "Helicopter.h"

#include <iostream>
using namespace std;

typedef std::list<Object*>::iterator ObjectIterator;
typedef std::list<Object*>::const_iterator ObjectConstIterator;

GameState::GameState() {
    create(new Helicopter(30, 15));
}

void GameState::update(float delta) {
    for (ObjectIterator it = destroyedObjects.begin(); it != destroyedObjects.end(); ++it) {
        objects.remove(*it);
        delete *it;
    }
    destroyedObjects.clear();
    
    for (ObjectIterator it = objects.begin(); it != objects.end(); ++it)
        (*it)->update(delta);
}

void GameState::draw() const {
    XSetForeground(display, gc, BlackPixel(display, 0));
    XFillRectangle(display, win, gc, 0, 0, 600, 400);
    XSetForeground(display, gc, WhitePixel(display, 0));
    
    for (ObjectConstIterator it = objects.begin(); it != objects.end(); ++it) {
        Entity *entity = dynamic_cast<Entity*>(*it);
        if (entity)
            entity->draw();
    }
}

void GameState::create(Object *obj) {
    objects.push_back(obj);
    obj->setState(this);
}

void GameState::destroy(Object *obj) {
    destroyedObjects.push_back(obj);
}