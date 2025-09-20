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

    constexpr size_t frameSize = 20;
    Frame frame( frameSize, frameSize );
    kbd.Start();

    Vec2I ballPos = { frameSize / 2, frameSize / 2 };

    while ( true )
    {
        std::optional< InputCommon::KeyInputCode > key;

        kbd.WaitForKeyPress();

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
            ballPos.y = (ballPos.y - 1 < 0) ? (frameSize - 1) : (ballPos.y - 1);
            break;
        case KEY_DOWN:
            ballPos.y = (ballPos.y + 1) % frameSize;
            break;
        case KEY_LEFT:
            ballPos.x = (ballPos.x - 1 < 0) ? (frameSize - 1) : (ballPos.x - 1);
            break;
        case KEY_RIGHT:
            ballPos.x = (ballPos.x + 1) % frameSize;
            break;
        default:;
        }

        DrawUtils::ClearScreen();
        DrawUtils::Clear( frame, '.' );
        DrawUtils::DrawPixel( ballPos, frame, 'x' );
        DrawUtils::Draw( frame );

    }
}