#include "imguihandler.hpp"

//Used exampel from https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl3/main.cpp
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imguihandler.hpp"
#include "gamemanger.hpp"

//using namespace ImGui; usikker på omg jeg skal ha denne

imgui_handler::imgui_handler()
    : context_(nullptr), initialized_(false) {
}

imgui_handler::~imgui_handler() {
    if (initialized_) {
        shutdown();
    }
}

void imgui_handler::init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    context_ = ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls, don't know if I need this
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    //Had issus with opengl version, so hardcoded it to 330. Ai assisted me with this part.
    ImGui_ImplOpenGL3_Init("#version 330");
    initialized_ = true;
}

void imgui_handler::begin_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imgui_handler::game_over_menu(bool &restart_game, bool &quit_game) {
    ImGuiIO &io = ImGui::GetIO();
    //To center the window after game over or win
    ImVec2 center(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
    ImVec2 window_size(400, 200);
    ImGui::SetNextWindowPos(ImVec2(center.x - window_size.x * 0.5f, center.y - window_size.y * 0.5f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Game Over", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    //Center "Game Over" text
    ImGui::SetCursorPosY(30);
    float text_width = ImGui::CalcTextSize("Game Over").x;
    ImGui::SetCursorPosX((window_size.x - text_width) * 0.5f);
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Game Over");

    //Center buttons
    ImGui::SetCursorPosY(100);
    float button_width = 150.0f;
    float spacing = 20.0f;
    float total_width = button_width * 2 + spacing;
    float start_x = (window_size.x - total_width) * 0.5f;

    ImGui::SetCursorPosX(start_x);
    if (ImGui::Button("Restart Game", ImVec2(button_width, 40))) {
        restart_game = true;
    }

    ImGui::SameLine(0, spacing);
    if (ImGui::Button("Exit Game", ImVec2(button_width, 40))) {
        quit_game = true;
    }

    ImGui::End();
}


void imgui_handler::render_ui(game_manger &game) {
    ImGui::Begin("Tank Simulator", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Tank Simulator");
    ImGui::Spacing();

    ImGui::Text("Level: %d", game.get_current_level());


    int hp = game.get_player_hp();
    ImGui::Text("Player HP: %d", hp);

    //HP bar
    float hp_ratio = hp / 10.0f;
    ImGui::ProgressBar(hp_ratio, ImVec2(200.0f, 0.0f));

    ImGui::Separator();

    //Boost Bar
    float boost_time = game.get_boost_time_left();
    ImGui::Text("Boost Time: %.1fs", boost_time);
    float boost_ratio = boost_time / 30.0f; // Assuming max 30 seconds
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); // Yellow
    ImGui::ProgressBar(boost_ratio, ImVec2(200.0f, 0.0f));
    ImGui::PopStyleColor();

    ImGui::Separator();

    //Ammo display as stars
    int ammo = game.get_ammo_count();
    ImGui::Text("Ammo:", ammo);
    for (int i = 0; i < ammo; ++i) {
        if (i > 0) ImGui::SameLine();
        ImGui::TextColored((ImVec4(1.0f, 0.5f, 0.0f, 1.0f)), "*");
    }

    //For the FPS viewer
    ImGuiIO &io = ImGui::GetIO();
    ImGui::Text("FPS: %.0f", io.Framerate);

    if (game.is_game_over()) {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Game Over!");
    }
    ImGui::End();
}


//THe menu that shows up when player wins or looses
void imgui_handler::victory_menu(bool &next_level, bool &quit_game) {
    ImGuiIO &io = ImGui::GetIO();
    //To center the window after  win
    ImVec2 center(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
    ImVec2 window_size(400, 200);
    ImGui::SetNextWindowPos(ImVec2(center.x - window_size.x * 0.5f, center.y - window_size.y * 0.5f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Victory!", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    //Center "VICTORY!" text
    ImGui::SetCursorPosY(30);
    float victory_width = ImGui::CalcTextSize("VICTORY!").x;
    ImGui::SetCursorPosX((window_size.x - victory_width) * 0.5f);
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "VICTORY!");

    ImGui::SetCursorPosY(60);
    float text_width = ImGui::CalcTextSize("All enemies defeated!").x;
    ImGui::SetCursorPosX((window_size.x - text_width) * 0.5f);
    ImGui::Text("All enemies defeated!");

    //Center buttons
    ImGui::SetCursorPosY(120);
    float button_width = 180.0f;
    float spacing = 20.0f;
    float total_width = button_width * 2 + spacing;
    float start_x = (window_size.x - total_width) * 0.5f;

    ImGui::SetCursorPosX(start_x);
    if (ImGui::Button("Restart Game", ImVec2(button_width, 40))) {
        next_level = true;
    }

    ImGui::SameLine(0, spacing);
    if (ImGui::Button("Quit", ImVec2(button_width, 40))) {
        quit_game = true;
    }

    ImGui::End();
}

void imgui_handler::end_frame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_handler::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(context_);
    initialized_ = false;
}
