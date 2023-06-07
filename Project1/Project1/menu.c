#include"macro_and_system.h"

void subtitle(char *title)
{//draw the subtitle
    double ww = GetWindowWidth();
    double wh = GetWindowHeight();

    double cx = ww / 2;
    double cy = wh / 2;
    double len = ww / 1.6;
    MovePen(cx - len / 2, cy - len / 2);
    SetPenColor("White");
    StartFilledRegion(1);
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);
    EndFilledRegion();

    MovePen(cx - len / 2, cy - len / 2);
    SetPenColor("Black");
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);

    char *str = title;
    double fontAscent = GetFontAscent();
    double tw = TextStringWidth(str);
    MovePen(cx - tw / 2, cy - fontAscent / 2);
    SetPenColor("Black");
    DrawTextString(str);

}


void About()
{//draw the about page
    double ww = GetWindowWidth();
    double wh = GetWindowHeight();

    double cx = ww / 2;
    double cy = wh / 2;
    double len = ww / 1.5;

    MovePen(cx - len / 2, cy - len / 2);
    SetPenColor("White");
    StartFilledRegion(1);
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);
    EndFilledRegion();

    MovePen(cx - len / 2, cy - len / 2);
    SetPenColor("Black");
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);

    char *str1 = "ABOUT";
    char *str2 = "  This is a maze game where players can both try to solve";
    char *str3 = "it by themselves or get some hints.And there're two ways ";
    char *str4 = "to get a new maze,including generating by the program or ";
    char *str5 = "by player.";
    char *str6 = "";
    char *str7 = "";
    char *str8 = "created by Xu Yang and Zheng Jiyun in 2023.";

    //ABOUT\n.\n generating by the program or by player.\ncreated by Xu Yang and Zheng Jiyun in 2023.\n";
    double fontAscent = GetFontAscent();

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent);
    SetPenColor("Black");
    DrawTextString(str1);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 2.5);
    DrawTextString(str2);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 4);
    DrawTextString(str3);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 5.5);
    DrawTextString(str4);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 7);
    DrawTextString(str5);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 8.5);
    DrawTextString(str6);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 10);
    DrawTextString(str7);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 11.5);
    DrawTextString(str8);

}

void Guide() 
{//draw the guide page
    double ww = GetWindowWidth();
    double wh = GetWindowHeight();

    double cx = ww / 2;
    double cy = wh / 2;
    double len = ww / 1.2;

    MovePen(cx - len / 2, cy - len / 2);
    SetPenColor("White");
    StartFilledRegion(1);
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);
    EndFilledRegion();

    MovePen(cx - len / 2, cy - len / 2);
    SetPenColor("Black");
    DrawLine(0, len);
    DrawLine(len, 0);
    DrawLine(0, -len);
    DrawLine(-len, 0);

    char *str1 = "HOW TO PLAY";
    char *str2 = "  Edit the map:   F3 / Edit the map->Edit manually";
    char *str3 = "  Regenerate a map:   F2 / Edit the map->Clear and edit";
    char *str4 = "  clear the map and build your own:   F1 / Edit the map->Regenerate";
    char *str5 = "  (touch  F3/Edit manually/Clear and edit  again to lock the map)";
    char *str6 = "  Start to play: M / Solve->Manually";
    char *str7 = "  (Control by keyboard: Plater 1 : up/down/left/right)";
    char* str8 = "                        Player 2 : W/S/A/D )";
    char *str9 = "  Show paths: F7 / Solve->Automatically";
    char* str10 = "  The Optimal path: F8 / Solve->Optimal";
    char* str11 = "  Show paths by steps/Get a hint: F9 / Solve->Single Step/Hint";
    char* str12 = "  The exploration process: E / Solve->Explore paths";
    char* str13 = "  Multiplayer mode: B / Solve->Multiplayer";
    char* str14 = "  Reinforcement Learning: R / Solve->Reinforcement Learning";

    double fontAscent = GetFontAscent();

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent);
    SetPenColor("Blue");
    DrawTextString(str1);

    SetPenColor("Dark Gray");
    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 2.5);
    DrawTextString(str2);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 4);
    DrawTextString(str3);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 5.5);
    DrawTextString(str4);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 9.5);
    DrawTextString(str6);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 14);
    DrawTextString(str9);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 15.5);
    DrawTextString(str10);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 17);
    DrawTextString(str11);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 18.5);
    DrawTextString(str12);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 20);
    DrawTextString(str13);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 21.5);
    DrawTextString(str14);

    SetPenColor("Violet");
    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 7);
    DrawTextString(str5);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 11);
    DrawTextString(str7);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 12.5);
    DrawTextString(str8);


}