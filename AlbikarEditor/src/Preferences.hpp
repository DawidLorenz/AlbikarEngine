#include "imgui.h"
#include "imgui_impl_glfw.h"

constexpr ImVec2 CENTER_VEC = ImVec2(0.5f, 0.5F);

const char* const APP_NAME = "Albikar";

const char* const WINDOW_DOCKS = "DockWindow";
const char* const WINDOW_DOCKSPACE = "DockspaceWindow";
const char* const WINDOW_ASSETS_PREVIEW = "Assets Preview";
const char* const WINDOW_ENGINE_PROPERTIES = "Engine Properties";
const char* const WINDOW_ASSETS = "Assets";
const char* const WINDOW_GAME_VIEW = "Game View";
const char* const WINDOW_HIERARCHY = "Hierarchy";
const char* const WINDOW_INSPECTOR = "Inspector";
const char* const WINDOW_LOG = "Log";
const char* const WINDOW_PROFILER = "Profiler";
const char* const WINDOW_SCENE_VIEW = "Scene View";
const char* const WINDOW_MONITORS = "Monitors";

// Colors
static constexpr auto COLOR_RED = ImVec4(1.0F, 0.0F, 0.0F, 1.0F);
static constexpr auto COLOR_RED_DARK = ImVec4(0.9257F, 0.109375F, 0.140625F, 1.0F);
static constexpr auto COLOR_GREEN = ImVec4(0.0F, 1.0F, 0.0F, 1.0F);
static constexpr auto COLOR_GREEN_DARK = ImVec4(0.1328125F, 0.45703125F, 0.296875F, 1.0F);
static constexpr auto COLOR_BLUE = ImVec4(0.0F, 0.0F, 1.0F, 1.0F);
static constexpr auto COLOR_BLUE_DARK = ImVec4(0.0F, 0.35156270F, 0.5078123F, 1.0F);
static constexpr auto COLOR_BLACK = ImVec4(0.0F, 0.0F, 0.0F, 1.0F);
static constexpr auto COLOR_WHITE = ImVec4(1.0F, 1.0F, 1.0F, 1.0F);
static constexpr auto COLOR_YELLOW = ImVec4(1.0F, 1.0F, 0.0F, 1.0F);
static constexpr auto COLOR_ORANGE = ImVec4(0.9F, 0.8F, 0.3F, 1.0F);
static constexpr auto COLOR_ORANGE_DARK = ImVec4(0.996096F, 0.335932F, 0.01569F, 1.0F);