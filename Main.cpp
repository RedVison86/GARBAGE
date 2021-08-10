#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Map.h"

#include "Model.h"

#include "View.h"

#include "Controller.h"

int main()
{
    Model model("car.png", 100, 100, 34.0, 17.0);
    View view(&model);
    Controller controller(&model, &view);
    controller.Run();
    return 0;
}
