#ifndef APPTYPES_H
#define APPTYPES_H

// INCLUDES//
#include <engine.h>
#include <raylib.h>

// DEFINES//
#define TEXT_COLOR_DARK (Color){182, 137, 98, 255}
#define TEXT_COLOR_LIGHT (Color){243, 229, 194, 255}
#define STORAGE_DATA_FILE "save1.data"

// ENUMS//
typedef enum {
  MENU_CURSOR_TEX,
  MENU_BIG_BUTTONS_TEX,
  MENU_BOARD_TEX,
  MENU_CLOUD_BACKGROUND,
  MENU_CLOUD_MIDGROUND,
  MENU_CLOUD_FOREGROUND,
  MENU_TEX_COUNT
} MenuTextureID;

typedef enum { MENU_MUSIC, MENU_SOUNDTRACK_COUNT } MenuSoundtrackID;

typedef enum { HOVER_SOUND, CLICK_SOUND, MENU_SOUND_COUNT } MenuSoundID;

typedef enum MenuView { MAIN = 0, SETTINGS = 1 } MenuView;

typedef enum { START_SHIP, PLAYER_TEX_COUNT } playerTextureID;

typedef enum { ANCHOR, SLOW_AHEAD, FAST_AHEAD, SPEED_COUNT } playerSpeedID;

typedef enum { ISLAND, ISLANDS_TEX_COUNT } islandsTextureID;

typedef enum { POST_FX, SHADER_COUNT } ShaderID;

typedef enum { GAMEPLAY_THEME, AMBIENT, SOUNDTRACK_COUNT } SoundtrackID;

typedef enum View { LOGO = 0, MENU = 1, GAMEPLAY = 2 } View;

typedef enum {
  STORAGE_POSITION_GOLD = 0,
  STORAGE_POSITION_POSX = 1,
  STORAGE_POSITION_POSY = 2
} StorageData;

// STRUCTS//
typedef struct {
  int frameCounter;
  int positionX;
  int positionY;
  int lettersCount;
  int topSideRecWidth;
  int leftSideRecHeight;
  int bottomSideRecWidth;
  int rightSideRecHeight;
  int state;
  float alpha;
} LogoState;

typedef struct {
  Sprite sprite;
  float scrolling;
  float scale;
  float scrollSpeed;
  Vector2 pos;
} Background;

typedef struct {
  Assets assets;
  Mouse mouse;
  Texture2D textures[MENU_TEX_COUNT];
  Sound sounds[MENU_SOUND_COUNT];
  Soundtrack soundtracks[MENU_SOUNDTRACK_COUNT];
  ImageElement board;
  ImageButton playButton;
  ImageButton quitButton;
  ImageButton settingsButton;
  int menuScale;
  Background background;
  Background midground;
  Background foreground;
} MenuMain;

typedef struct {
  Button showFPS;
  Button limitFPS;
  Button soundtrackOn;
} MenuSettings;

typedef struct {
  MenuView menuView;
  MenuMain menuMain;
  MenuSettings menuSettings;
} MenuState;

typedef struct {
  Sprite sprite;
  Rectangle bounds;
  Shader shader;
  float time;
} Floor;

typedef struct {
  Sprite sprite;
  Animation animation;
  Physics physics;
  float rotation;
  Sound soundFlapping;
  int gold;
} Player;

typedef enum { BOAT, ENEMIES_TEX_COUNT } enemiesTextureID;

typedef enum { START, SHIP_COUNT } shipID;

typedef struct {
  int id;
  char *assetPath;
  int frameSize;
  int speed0;
  int speed1;
  int speed2;
  int rotationSpeed;
} Ship;

#define MAX_ENEMIES 100

typedef struct {
  Config config;
  int count;
  Sprite sprite[MAX_ENEMIES];
  Animation animation[MAX_ENEMIES];
  Physics physics[MAX_ENEMIES];
  bool arrived[MAX_ENEMIES];
  Vector2 destPos[MAX_ENEMIES];
  bool alive[MAX_ENEMIES];
} Enemies;

typedef enum { FLYING, BIRDS_TEX_COUNT } birdsTextureID;

#define MAX_BIRDS 100

typedef struct {
  int count;
  Sprite sprite[MAX_BIRDS];
  Animation animation[MAX_BIRDS];
  Physics physics[MAX_BIRDS];
  bool arrived[MAX_BIRDS];
  Vector2 destPos[MAX_BIRDS];
} Birds;

typedef struct {
  Sprite sprite;
  Animation animation;
  Physics physics;
} Islands;

#define MAX_PROJECTILES 100
typedef struct {
  int count;
  Physics physics[MAX_PROJECTILES];
  bool active[MAX_PROJECTILES];
  float radius[MAX_PROJECTILES];
  Color color[MAX_PROJECTILES];
  Sound soundShooting[MAX_PROJECTILES];
  Sound soundImpact[MAX_PROJECTILES];
} Projectiles;

typedef struct {
  Assets assets;
  PostProcessing postFX[SHADER_COUNT];
  Soundtrack soundtracks[SOUNDTRACK_COUNT];
  RenderTexture2D target;
  Floor floor;
  Birds birds;
  Enemies enemies;
  Islands islands;
  Mouse mouse;
  Image image;
  Projectiles projectiles;
} GameState;

typedef struct {
  View currentView;
  bool running;
  bool gameStarted;
} State;

typedef struct {
  bool showFPS;
  bool limitFPS;
  bool soundtrackOn;
} Flags;

typedef struct {
  Config config;
  State state;
  Flags flags;
  Window window;
  Font font;
  LogoState logo;
  MenuState menu;
  GameState game;
} App;

// FUNCTIONS//
void InitLogo(LogoState *l);
void UpdateLogo(LogoState *l, View *currentView, bool *running);
void RenderLogo(const LogoState *l, Flags *flags);

void InitBackground(float scrollSpeed, Background *bg, Texture2D *texture,
                    const TextureAsset *backgroundAsset);
void UpdateBackground(Background *bg);
void RenderBackground(Background *bg);

void InitMenuMain(MenuMain *m);
void UpdateMenuMain(MenuMain *m, State *state, Flags *flags,
                    MenuView *menuView);
void RenderMenuMain(MenuMain *m, Font *font, const char *title, Flags *flags);
void CleanupMenuMain(MenuMain *m);

void InitMenuSettings(MenuSettings *s);
void UpdateMenuSettings(MenuSettings *s, MenuView *menuView, State *state,
                        Flags *flags);
void RenderMenuSettings(MenuSettings *s, Flags *flags);
void CleanupMenuSettings(MenuSettings *s);

void InitMenu(MenuState *m);
void UpdateMenu(MenuState *m, State *state, Flags *flags);
void RenderMenu(MenuState *m, Font *font, const char *title, Flags *flags);
void CleanupMenu(MenuState *m);

Floor CreateFloor(void);
void UpdateFloor(Floor *floor);
void RenderFloor(Floor *floor);
void UnloadFloor(Floor *floor);

playerSpeedID GetPlayerSpeedID(float speed);
Player *GetPlayer(void);
void CreatePlayer(void);
void UpdatePlayer(void);
void RenderPlayer(void);

Enemies CreateEnemies(void);
void UpdateEnemies(Enemies *enemies, Projectiles *projectiles);
void RenderEnemies(Enemies *enemies);

Birds CreateBirds(void);
void UpdateBirds(Birds *birds);
void RenderBirds(Birds *birds);

Islands CreateIslands(void);
void UpdateIslands(Islands *islands);
void RenderIslands(Islands *islands);

Projectiles CreateProjectiles(void);
void UpdateProjectiles(Projectiles *projectiles, Enemies *enemies);
void RenderProjectiles(Projectiles *projectiles);

void InitGame(App *app);
void UpdateGame(App *app);
void RenderComponents(App *app);
void RenderGame(App *app);
void CleanupGame(App *app);

void OnEscapeChangeView(App *app, View view);
void OnWindowClosedStoppApp(App *app);

void ConfigApp(App *app);
void InitApp(App *app);
void UpdateApp(App *app);
void CleanupApp(App *app);

#endif // APPTYPES_H
