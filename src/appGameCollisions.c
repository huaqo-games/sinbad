#include "app.h"
#include <raylib.h>

void CheckPlayerEnemyCollisions(Player *player, Enemies *enemies) {
  for (int i = 0; i < enemies->count; i++) {

    Vector2 playerPos = player->physics.position;
    Vector2 enemiesPos = enemies->physics[i].position;

    float playerRadius = 8.0f;
    float enemiesRadius = 8.0f;
    float minDist = playerRadius + enemiesRadius;

    if (CheckCollisionCircles(playerPos, playerRadius, enemiesPos,
                              enemiesRadius)) {
      float dist = GetDistanceBetweenTwoVectors(playerPos, enemiesPos);
      float overlap = minDist - dist;

      if (dist > 0.0f) {
        Vector2 collisionVector = GetDirectionBetweenTwoVectors(
            enemies->physics[i].position, player->physics.position);
        player->physics.position.x += collisionVector.x * overlap;
        player->physics.position.y += collisionVector.y * overlap;
        Vector2 forward = RotationToVector2(player->rotation - 90.0f);
        float side = Cross2D(forward, collisionVector);
        player->rotation += side * 120.0f * GetFrameTime();
      }
    }
  }
}
void CheckEnemyEnemyCollisions(Enemies *enemies) {
  for (int a = 0; a < enemies->count; a++) {
    for (int b = a + 1; b < enemies->count; b++) {

      Vector2 posA = enemies->physics[a].position;
      Vector2 posB = enemies->physics[b].position;

      float enemiesRadius = 8.0f;
      float minDist = enemiesRadius * 2;

      if (CheckCollisionCircles(posA, enemiesRadius, posB, enemiesRadius)) {

        Vector2 collisionVectorA = GetDirectionBetweenTwoVectors(posB, posA);
        Vector2 collisionVectorB = GetDirectionBetweenTwoVectors(posA, posB);
        float dist = GetDistanceBetweenTwoVectors(posA, posB);
        float overlap = minDist - dist;

        if (dist > 0.0f) {
          enemies->physics[a].position.x += collisionVectorA.x * overlap * 0.5f;
          enemies->physics[a].position.y += collisionVectorA.y * overlap * 0.5f;

          enemies->physics[b].position.x += collisionVectorB.x * overlap * 0.5f;
          enemies->physics[b].position.y += collisionVectorB.y * overlap * 0.5f;

          Vector2 forwardA =
              RotationToVector2(enemies->sprite[a].rotation - 90.0f);
          Vector2 forwardB =
              RotationToVector2(enemies->sprite[b].rotation - 90.0f);
          float sideA = Cross2D(forwardA, collisionVectorA);
          float sideB = Cross2D(forwardB, collisionVectorB);
          enemies->sprite[a].rotation += sideA * 120.0f * GetFrameTime();
          enemies->sprite[b].rotation += sideB * 120.0f * GetFrameTime();
        }
      }
    }
  }
}

void CheckProjectileEnemyCollisions(Projectiles *projectiles,
                                    Enemies *enemies) {
  for (int i = 0; i < projectiles->count; i++) {
    for (int j = 0; j < enemies->count; j++) {
    }
  }
}
