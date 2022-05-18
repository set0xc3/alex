#ifndef ALEX_SANDBOX_H
#define ALEX_SANDBOX_H

internal void sandbox_init();

// Callbacks
internal void sandbox_on_update();
internal void sandbox_on_event();
internal void sandbox_on_render();

internal void sandbox_draw_quad(const glm::vec3 &position, const glm::vec3 &size, const glm::vec4 &color);

#endif //ALEX_SANDBOX_H
