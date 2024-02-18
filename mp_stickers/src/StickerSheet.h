/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

class StickerSheet {
    public:
    StickerSheet (const Image &picture, unsigned max);
    StickerSheet (const StickerSheet &other);

    void copy(const StickerSheet& other);
    void clear();
    ~StickerSheet();
    const StickerSheet & operator= (const StickerSheet &other);
    void changeMaxStickers (unsigned max);
    int addSticker (Image &sticker, int x, int y);
    int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
    bool translate (unsigned index, int x, int y);
    void removeSticker (unsigned index);
    Image * getSticker (unsigned index);
    int layers () const;
    Image render () const;
    

    struct Sticker {
        Image* image = nullptr;
        int x = 0;        
        int y = 0;  
        Sticker(): image(nullptr), x(0), y(0) {}
        Sticker(Image* img, int posX, int posY) : image(img), x(posX), y(posY) {}
    };

    Image* basePicture_;
    std::vector<Sticker> stickers_;


    unsigned max_;
};