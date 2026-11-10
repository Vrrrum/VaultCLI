#include <iostream>
#include <vector>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

int main() {
    // Przykładowe dane w menedżerze haseł
    std::vector<std::string> entries = {
        "gmail.com - user@gmail.com",
        "github.com - developer99",
        "netflix.com - filmweb_fan"
    };
    int selected = 0;

    // Komponent listy z obsługą strzałek
    auto menu = Menu(&entries, &selected);

    // Definicja wyglądu (Layout a'la Ranger: panel boczny i podgląd)
    auto component = Container::Vertical({
        menu,
    });

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer(component, [&] {
        return vbox({
            text("=== KONSOLOWY MENEDŻER HASEŁ ===") | bold | color(Color::Cyan) | center,
            separator(),
            hbox({
                // Lewy panel: Lista haseł
                window(text(" Wpisy "), menu->Render()) | size(WIDTH, EQUAL, 35),
                separator(),
                // Prawy panel: Szczegóły wybranego elementu
                window(text(" Szczegóły "), vbox({
                    text("Wybrano: " + entries[selected]),
                    separator(),
                    text("Login: [ukryty]"),
                    text("Hasło: ************"),
                    filler(),
                    text("Naciśnij 'q' aby wyjść, 'a' aby dodać.") | dim
                })) | flex,
            }) | flex,
            separator(),
            text(" [↑↓] Nawigacja | [Enter] Pokaż | [a] Dodaj | [d] Usuń | [q] Wyjście ") | center | dim
        }) | border;
    });

    // Obsługa wyjścia klawiszem 'q'
    renderer |= CatchEvent([&](Event event) {
        if (event == Event::Character('q')) {
            screen.Exit();
            return true;
        }
        return false;
    });

    screen.Loop(renderer);
    return 0;
}