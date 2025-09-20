//
// Created by gaugamela on 9/13/25.
//

#include "KeyboardInputHandler.hpp"
#include "DrawUtils.hpp"
#include <iostream>
#include <linux/input-event-codes.h>

int main()
{
    InputCommon::KeyboardInputHandler kbd;
    Frame frame( 20, 20 );
    kbd.Start();

    Vec2I ballPos = { 10, 10 };

    while ( true )
    {
        std::optional< InputCommon::KeyInputCode > key;
        try
        {
            key = kbd.GetNextKeyPress();
        }
        catch (InputCommon::PeripheralInputException& pie)
        {
            std::cerr << pie.what();
            return 0;
        }

        if ( !key )
            continue;

        switch ( key.value() )
        {
        case KEY_UP:
            ballPos.y--;
            break;
        case KEY_DOWN:
            ballPos.y++;
            break;
        case KEY_LEFT:
            ballPos.x--;
            break;
        case KEY_RIGHT:
            ballPos.x++;
            break;
        default:;
        }

        DrawUtils::ClearScreen();
        DrawUtils::Clear( frame, '.' );
        DrawUtils::DrawPixel( ballPos, frame, 'x' );
        DrawUtils::Draw( frame );

    }
}