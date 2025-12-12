#include "app.h"



const TextureAsset enemiesTextureAssets[ENEMIES_TEX_COUNT] = {
	{"assets/ship_start.png", 16.0f, 16.0f, 90.0f}
};

Enemies CreateEnemies(void){	
	Enemies enemies = {.count = MAX_ENEMIES};
	TextureAsset textureAsset = enemiesTextureAssets[BOAT];
	Texture2D texture = LoadTexture(textureAsset.path);
	float frameWidth = textureAsset.frameWidth;
	float rotation = textureAsset.rotation;

	for (int i = 0; i < enemies.count; i++)	
	{
		enemies.sprite[i] = (Sprite){
			.texture = texture,
			.frameSize = {frameWidth, frameWidth},
			.sourceRec = {0.0f, 0.0f, frameWidth, frameWidth},
			.destRec = {GetScreenWidth()/2, 0.0f, frameWidth, frameWidth},
			.origin = {frameWidth / 2, frameWidth / 2},
			.rotation = rotation,
			.color = WHITE
		};

		enemies.animation[i] = (Animation){
			.state = 1,
			.currentFrame = 0,
			.maxFrame = 2,
			.framesCounter = 0,
			.framesSpeed = 2.0f,
			.animTimer = 0.0f
		};

		Rectangle cameraRec = GetCameraRectangle();

		enemies.physics[i] = (Physics){
		.position = GetPositionOutsideRectangle(cameraRec, 100, 1000),
		.direction = (Vector2){0.0f, 0.0f},
		.speed = 5.0f
		};

		enemies.arrived[i] = true;
		enemies.destPos[i] = (Vector2){0.0f, 0.0f};	

	}

	return enemies;
}

void UpdateEnemies(Enemies *enemies){
	Camera2D *camera = GetCamera();
	Rectangle cameraRec = GetCameraRectangle();

	for (int i = 0; i < enemies->count; i++)
	{
		if(enemies->arrived[i])
		{
			enemies->destPos[i] = GetPositionOutsideRectangle(cameraRec, 100, 1000);
			enemies->arrived[i] = false;
		}
		if(CheckCollisionPointCircle(enemies->physics[i].position, enemies->destPos[i], 10.0F))
		{
			enemies->arrived[i] = true;
		}	
		if(GetDistanceBetweenTwoVectors(enemies->physics[i].position, camera->target) > 1000){
			enemies->physics[i].position = GetPositionOutsideRectangle(cameraRec, 100, 1000);
		}
		Vector2 dir = GetDirectionBetweenTwoVectors(enemies->physics[i].position, enemies->destPos[i]);
		UpdatePhysics(&enemies->physics[i], dir);
		UpdateSpriteDestRec(&enemies->sprite[i], &enemies->physics[i].position);
		float rotation = Vector2ToRotation(dir);
		UpdateSpriteRotation(&enemies->sprite[i], rotation + 90.0f);
		UpdateAnimation(&enemies->animation[i], GetFrameTime());
		UpdateSpriteSourceRec(&enemies->sprite[i], &(Vector2){enemies->sprite[i].frameSize.x * enemies->animation[i].currentFrame, enemies->sprite[i].frameSize.y});
	}
}

void RenderEnemies(Enemies *enemies){

	for (int i = 0; i < enemies->count; i++)
	{
		RenderSprite(&enemies->sprite[i]);
	}

}


