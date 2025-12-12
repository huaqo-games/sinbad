#include "app.h"

void ConfigApp(App* app){
    InitConfig(&app->config, "config/config.ini");
    app->state.currentView = GetConfigInt(&app->config, "startView");
    app->flags.showFPS =  GetConfigInt(&app->config, "showFPS");
	app->flags.limitFPS = GetConfigInt(&app->config, "limitFPS");
	app->flags.soundtrackOn = GetConfigInt(&app->config, "soundtrackOn");
    app->window.title = GetConfigString(&app->config, "windowTitle");
    app->window.width = GetConfigInt(&app->config, "windowWidth");
    app->window.height = GetConfigInt(&app->config, "windowHeight");
}

void InitApp(App *app){
    InitFont(&app->font, GetConfigString(&app->config, "fontPath"));
    InitLogo(&app->logo);
    InitMenu(&app->menu);
    InitGame(app);
}

void UpdateApp(App *app){

    app->state.running = true;
    app->state.gameStarted = false;

    while (app->state.running)
    {
        switch (app->state.currentView)
        {
            case LOGO:
            {
                UpdateLogo(&app->logo, &app->state.currentView, &app->state.running);
                RenderLogo(&app->logo, &app->flags);
            }break;
            case MENU:
            {
                UpdateMenu(&app->menu, &app->state, &app->flags);
                RenderMenu(&app->menu, &app->font, app->window.title, &app->flags);
            }break;
            case GAMEPLAY:
            {
                UpdateGame(app);
                RenderGame(app);
            }break;
            default: break;
        } 
    }
}

void CleanupApp(App *app){
    CleanupMenu(&app->menu);
    CleanupGame(app);
    CleanupFont(&app->font);
    CleanUpConfig(&app->config);
}

