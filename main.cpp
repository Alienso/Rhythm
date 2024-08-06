#include <iostream>

#include "source/Rhythm.h"

int main(int argc, char** argv) {
    Rhythm app;
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}