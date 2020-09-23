#include "imtui/imtui.h"

#include "imtui/imtui-impl-ncurses.h"

#include "imtui-demo.h"

int main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto screen = ImTui_ImplNcurses_Init(true);
    ImTui_ImplText_Init();

    bool demo = true;
    bool pepe_selected = false;
    bool btn_clicked = false;
    int nframes = 0;
    int fval = 0x05;

    while (true) {
        ImTui_ImplNcurses_NewFrame();
        ImTui_ImplText_NewFrame();

        ImGui::NewFrame();

	if(demo)
	{
		ImGui::SetNextWindowPos(ImVec2(4, 2), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(50.0, 10.0), ImGuiCond_Once);
		ImGui::Begin("Hello, world!", &demo);
		ImGui::Text("NFrames = %d", nframes++);
		ImGui::Text("Mouse Pos : x = %g, y = %g", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		ImGui::Text("Time per frame %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Float:");
		ImGui::SameLine();
		ImGui::SliderInt("##int", &fval, 0x00, 0x10);
		ImGui::BeginMenu("Pepito", true);
			ImGui::MenuItem("pepe", "toto", &pepe_selected, true);
		ImGui::EndMenu();
		ImGui::End();

		if( pepe_selected )
		{
			ImGui::SetNextWindowPos(ImVec2(10, 2), ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(50.0, 10.0), ImGuiCond_Once);
			ImGui::Begin("Pepe WINDOW");
				if(!btn_clicked)
					btn_clicked = ImGui::Button("CLICK HERE");
				ImGui::SmallButton("NOT CLICK HERE");
			ImGui::End();
		}


	}

	if(btn_clicked)
	{
		btn_clicked = true;
		ImTui::ShowDemoWindow( &demo );
	}

        ImGui::Render();

        ImTui_ImplText_RenderDrawData(ImGui::GetDrawData(), screen);
        ImTui_ImplNcurses_DrawScreen();
    }

    ImTui_ImplText_Shutdown();
    ImTui_ImplNcurses_Shutdown();

    return 0;
}
