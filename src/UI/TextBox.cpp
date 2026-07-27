#include "TextBox.h"


TextBox::TextBox(Rectangle rect, const std::string& placeholder, bool isKeyBox)
    : rect(rect), text(placeholder), active(false), name(placeholder), isKeyBox(isKeyBox) {}

void TextBox::Update(bool isActive)
{
    active = isActive;
    if (!active) return;

    if (isKeyBox)
    {
        bool ctrl  = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
        bool alt   = IsKeyDown(KEY_LEFT_ALT)     || IsKeyDown(KEY_RIGHT_ALT);
        bool shift = IsKeyDown(KEY_LEFT_SHIFT)   || IsKeyDown(KEY_RIGHT_SHIFT);

        int fkeys[] = {
            KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5,KEY_F6,
            KEY_F7,KEY_F8,KEY_F9,KEY_F10,KEY_F11,KEY_F12
        };
        for (int i = 0; i < 12; i++) {
            if (IsKeyPressed(fkeys[i])) {
                std::string result = "";
                if (ctrl)  result += "Ctrl+";
                if (alt)   result += "Alt+";
                if (shift) result += "Shift+";
                result += "F" + std::to_string(i + 1);
                text = result;
                return;
            }
        }

        for (int key = KEY_A; key <= KEY_Z; key++) {
            if (IsKeyPressed(key)) {
                std::string result = "";
                if (ctrl)  result += "Ctrl+";
                if (alt)   result += "Alt+";
                if (shift) result += "Shift+";
                result += (char)('A' + (key - KEY_A));
                text = result;
                return;
            }
        }
        for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
            if (IsKeyPressed(key)) {
                std::string result = "";
                if (ctrl)  result += "Ctrl+";
                if (alt)   result += "Alt+";
                if (shift) result += "Shift+";
                result += (char)('0' + (key - KEY_ZERO));
                text = result;
                return;
            }
        }
        return; 
    }
}

void TextBox::Draw()
{
    DrawRectangleRec(rect, active ? colorActive : colorInactive);
    DrawRectangleLinesEx(rect, 1, active ? WHITE : colorBorder);
    DrawText(text.c_str(), (int)rect.x + 6, (int)rect.y + 9, fontSize, colorText);

    if (active && (int)(GetTime() * 2) % 2 == 0) {
        int textW = MeasureText(text.c_str(), fontSize);
        DrawText("|", (int)rect.x + 6 + textW, (int)rect.y + 9, fontSize, colorText);
    }
}

bool TextBox::IsClicked()
{
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect);
}