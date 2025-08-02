#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>

	EMSCRIPTEN_KEEPALIVE
	void onGPTResponse(const char* responsePtr) {
		// Print to console (for debugging)
		std::cout << "GPT response: " << responsePtr << std::endl;

		// Use raylib to draw or store the string as needed
		// For simplicity, let's just store it in a static variable
		static std::string gptResponse;
		gptResponse = responsePtr;

		// Optionally, trigger a redraw or update game state here
	}
#else
	extern "C" const char* my_secret() {
		return "I like salty potatoes!";
	}
#endif


const int WIDTH = 850;
const int HEIGHT = 450;

void UpdateDrawFrame();

int main(void)
{
	InitWindow(WIDTH, HEIGHT, "raylib [core] example - basic window");

	#if defined(PLATFORM_WEB)
    	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
	#else
		SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
		//--------------------------------------------------------------------------------------

		// Main game loop
		while (!WindowShouldClose())    // Detect window close button or ESC key
		{
			UpdateDrawFrame();
		}
	#endif

	CloseWindow();

	return 0;
}
std::string displayedText = "Waiting for GPT response...";
void UpdateDrawFrame()
{
	BeginDrawing();
	
	ClearBackground(RAYWHITE);

	DrawText(displayedText.c_str(), 20, 20, 20, BLACK);

	EndDrawing();
}