#pragma once

namespace graphs {
    enum Color{
        Blue, 
        Black, 
        Green,
        Red,
        Beige, 
        RedOutline,
        YellowOutline,
        PinkOutline,        
        BlueOutline, 
        BeigeOutline,
        Count
    };

    // Function to convert enum to int
    inline int colorToInt(Color color) {
        if (color < Count){
            return static_cast<int>(color);
        }
        return 0;
    }

    // Function to convert int to enum
    inline Color intToColor(int value) {
        if (value < Count){
            return static_cast<Color>(value);
        }
        return Color::Blue;
    }

}; // end namespace game
