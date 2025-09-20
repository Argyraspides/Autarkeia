//
// Created by gaugamela on 9/13/25.
//

#include "KeyboardInputHandler.hpp"
#include <iostream>

int main()
{
    InputCommon::KeyboardInputHandler kbd;
    kbd.Start();

    while ( true )
    {
        try
        {
            std::optional< InputCommon::KeyInputCode > key = kbd.GetNextKeyPress();
            if ( !key.has_value() )
                continue;

            std::cout << "Pressed key: " << key.value() << "\n";

        }
        catch (InputCommon::PeripheralInputException& pie)
        {
            std::cerr << pie.what();
            return 0;
        }
    }
}