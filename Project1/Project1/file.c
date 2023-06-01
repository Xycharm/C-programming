#include"macro_and_system.h"

void SaveMap() {
    char filename[2048] = { 0 };
    if (!SaveFileDialog("graphic file(*.data)\0*.data\0", filename))
        return;

    FILE* fp;
    if (!(fp = fopen(filename, "wb"))) {
        MessageBox(NULL, filename, "fail to open", MB_OK | MB_ICONWARNING);
        return;
    }
    fwrite(blockState, sizeof(int), X * X, fp);

    fclose(fp);
}

void LoadMap() {
    char filename[2048] = { 0 };
    if (!OpenFileDialog("????(*.data)\0*.data\0", filename))
        return;

    FILE* fp;
    if (!(fp = fopen(filename, "rb"))) {
        MessageBox(NULL, filename, "??????", MB_OK | MB_ICONWARNING);
        return;
    }
    fread(blockState, sizeof(int), X * X, fp);
    fclose(fp);
}