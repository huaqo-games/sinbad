#include "app.h"
#include "raylib.h"
#include <limits.h>

void RenderOverlay(Mouse *mouse) {

  // Health
  Player *player = GetPlayer();
  const char *text = TextFormat("Health: %i\n"
                                "Gold: %i\n",
                                player->health, player->gold);
  DrawText(text, 0, 0, 25, WHITE);

  // Mouse
  Rectangle mouseRectangle = (Rectangle){0, 0, mouse->cursorTexture.width,
                                         mouse->cursorTexture.height};
  DrawTextureRec(mouse->cursorTexture, mouseRectangle, mouse->screenPosition,
                 WHITE);
}
