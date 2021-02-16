#include "../inc/functions.h"

Texture2D* LoadTextures() {

    Texture2D *textures = malloc(sizeof(Texture2D) * 5);

    textures = (Texture2D[5]){
        LoadTexture("../assets/background/parallax-mountain-bg.png"),              
        LoadTexture("../assets/background/parallax-mountain-montain-far.png"),
        LoadTexture("../assets/background/parallax-mountain-mountains.png"),
        LoadTexture("../assets/background/parallax-mountain-trees.png"),
        LoadTexture("../assets/background/parallax-mountain-foreground-trees.png")
    };
    return textures;
}

void UnloadTextures(Texture2D *textures) {
    int length = 5;

    for (int i = 0; i < length; i++) {
        UnloadTexture(textures[i]);
    }
}