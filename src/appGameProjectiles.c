#include "app.h"
#include <raylib.h>
#include <raymath.h>

typedef enum {
  CANNONBALL_SHOOTING,
  CANNONBALL_IMPACT,
  SOUND_COUNT
} SoundID;

const SoundAsset   soundAssets[SOUND_COUNT] = {
  {"assets/cannonball_shooting.mp3"},
  {"assets/cannonball_impact.mp3"}
};

Projectiles CreateProjectiles(void) {
  Projectiles projectiles = {.count = MAX_PROJECTILES};

  for (int i = 0; i < projectiles.count; i++) {
    projectiles.physics[i] =
        (Physics){(Vector2){0.0f, 0.0f}, (Vector2){0.0f, 0.0f},
                  (Vector2){0.0f, 0.0f}, 50.0f};
    projectiles.radius[i] = 1.0f;
    projectiles.active[i] = false;
    projectiles.color[i] = GRAY;
    projectiles.soundShooting[i] = LoadSound(soundAssets[CANNONBALL_SHOOTING].path);
    projectiles.soundImpact[i] = LoadSound(soundAssets[CANNONBALL_IMPACT].path);
  }

  return projectiles;
}

void UpdateProjectiles(Projectiles *projectiles, Enemies *enemies) {

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
        PlaySound(projectiles->soundShooting[i]);
        lastShotTime = currentTime;
        break;
      }
    }
  }

  if (IsKeyDown(KEY_E) && (currentTime - lastShotTime >= reloadTime)) {
    for (int i = 0; i < projectiles->count; i++){
      if (!projectiles->active[i]) {
        projectiles->active[i] = true;
        Player *player = GetPlayer();
        projectiles->physics[i].position = player->physics.position;
        projectiles->physics[i].direction =
            Vector2Rotate(player->physics.direction, 90.0f * DEG2RAD);
        PlaySound(projectiles->soundShooting[i]);
        lastShotTime = currentTime;
        break;
      }
    }
  }

  for (int i = 0; i < projectiles->count; i++) {

    if (!projectiles->active[i]) continue;

    for (int j = 0; j < enemies->count; j++){
      if (CheckCollisionCircleRec(projectiles->physics[i].position, projectiles->radius[i], enemies->sprite[j].destRec)){
        PlaySound(projectiles->soundImpact[i]);
        Player *player = GetPlayer();
        player->gold += 1;
        SaveStorageValue(STORAGE_DATA_FILE, STORAGE_POSITION_GOLD, player->gold);
        projectiles->active[i] = false;
      }
    }

    UpdatePhysics(&projectiles->physics[i],
                  projectiles->physics[i].direction);
  }
}

void RenderProjectiles(Projectiles *projectiles) {
  for (int i = 0; i < projectiles->count; i++) {
    if (projectiles->active[i]) {
      DrawCircle(projectiles->physics[i].position.x,
                 projectiles->physics[i].position.y, projectiles->radius[i],
                 projectiles->color[i]);
    }
  }
}
