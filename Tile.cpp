#include "Tile.h"

Tile::Tile(int num/* = 0*/) {
    if (num <= 0) {
        this->isBlank = true;
        this->num = 0;
    } else {
        this->isBlank = false;
        this->num = num;
    }
}

Tile::Tile(const Tile &tile) {
    this->isBlank = tile.isBlank;
    this->num = tile.num;
}

Tile &Tile::operator=(const Tile &tile) {
    if (&tile != this) {
        this->isBlank = tile.isBlank;
        this->num = tile.num;
    }
    return *this;
}

bool Tile::isTileBlank() {
    return this->isBlank;
}

int Tile::getNum() {
    return this->num;
}

void Tile::setNum(int num) {
    if (num <= 0) {
        this->isBlank = true;
        this->num = 0;
    } else {
        this->isBlank = false;
        this->num = num;
    }
}