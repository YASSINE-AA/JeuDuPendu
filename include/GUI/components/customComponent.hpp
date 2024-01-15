#ifndef CUSTOM_COMPONENT_HPP
#define CUSTOM_COMPONENT_HPP

#include "renderer.hpp"
#include "window.hpp"
#include "states.hpp"

class CustomComponent
{
public:
    CustomComponent(Renderer &renderer, States &states) : renderer(renderer), states(states) {}
    virtual void render() = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void handleEvents(SDL_Event e) = 0;

protected:
    Renderer renderer;
    States states;
};

#endif
