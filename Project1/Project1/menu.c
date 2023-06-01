#include"macro_and_system.h"

void subtitle(char *title) {//draw the subtitle
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


void About() {//draw the about page
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

void Guide() {//draw the guide page
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
    char *str2 = "  clear the map and biuld your own: F1 / Edit the map->Regenerate";
    char *str3 = "  Regenerate a map: F2 / Edit the map->Clear and edit";
    char *str4 = "  Edit the map: F3 / Edit the map->Edit manually";
    char *str8 = "  (touch F3/Edit manually again to lock the map)";
    char *str5 = "  Start to play: Solve->Manually";
    char *str6 = "  (use up/down/left/right on the keyboard to advance)";
    char *str7 = "  Show the path: Solve->Automatically";

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
    DrawTextString(str8);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 8.5);
    DrawTextString(str5);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 10);
    DrawTextString(str6);

    MovePen(cx - len / 2 + 0.5, cy + len / 2 - fontAscent * 11.5);
    DrawTextString(str7);

}