#include <iostream>
#include "Application.hh"

int main()
{
    TG::Application app;
    try {
        app.run();
    } catch (std::exception& e) {
        std::cout << e.what();
    }
}