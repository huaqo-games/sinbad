#include "app.h"
#include <raylib.h>
#include <raymath.h>

Projectiles CreateProjectiles(void) {
  Projectiles projectiles = {.count = MAX_PROJECTILES};

  for (int i = 0; i < projectiles.count; i++) {
    projectiles.physics[i] =
        (Physics){(Vector2){0.0f, 0.0f}, (Vector2){0.0f, 0.0f},
                  (Vector2){0.0f, 0.0f}, 50.0f};
    projectiles.radius[i] = 1.0f;
    projectiles.active[i] = false;
    projectiles.color[i] = GRAY;
  }

  return projectiles;
}

void UpdateProjectiles(Projectiles *projectiles) {

  static float lastShotTime = 0.0f;
  const float reloadTime = 1.0f;
  float currentTime = GetTime();

  if (IsKeyDown(KEY_Q) && (currentTime - lastShotTime >= reloadTime)) {
    for (int i = 0; i < projectiles->count; i++) {
      if (!projectiles->active[i]) {
        projectiles->active[i] = true;
        Player *player = GetPlayer();
        projectiles->physics[i].position = player->physics.position;
        projectiles->physics[i].direction =
            Vector2Rotate(player->physics.direction, -90.0f * DEG2RAD);
        lastShotTime = currentTime;
        break;
      }
    }
  }

  if (IsKeyDown(KEY_E) && (currentTime - lastShotTime >= reloadTime)) {
    for (int i = 0; i < projectiles->count; i++) {
      if (!projectiles->active[i]) {
        projectiles->active[i] = true;
        Player *player = GetPlayer();
        projectiles->physics[i].position = player->physics.position;
        projectiles->physics[i].direction =
            Vector2Rotate(player->physics.direction, 90.0f * DEG2RAD);
        lastShotTime = currentTime;
        break;
      }
    }
  }

  for (int i = 0; i < projectiles->count; i++) {
    if (projectiles->active[i]) {
      UpdatePhysics(&projectiles->physics[i],
                    projectiles->physics[i].direction);
    }
  }
}

void RenderProjectiles(Projectiles *projectiles) {
  for (int i = 0; i < projectiles->count; i++) {
    printf("Projectile Active: %d", projectiles->active[i]);
    if (projectiles->active[i] == true) {
      DrawCircle(projectiles->physics[i].position.x,
                 projectiles->physics[i].position.y, projectiles->radius[i],
                 projectiles->color[i]);
    }
  }
}
