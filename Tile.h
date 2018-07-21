#ifndef TILE_H
#define TILE_H

class Tile {
private:
    bool isBlank;
    int num;

public:
    Tile(int num = 0);

    Tile(const Tile &tile);

    Tile &operator=(const Tile &tile);

    bool isTileBlank();

    int getNum();

    void setNum(int num);
};

#endif
