#include "StickerSheet.h"
#include <iostream>

StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    max_ = max;
    basePicture_ = new Image(picture);
    for (unsigned i = 0 ; i < max ; ++i) {
        stickers_.push_back({nullptr, 0, 0});
    }
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    basePicture_ = new Image(*(other.basePicture_));
    max_ = other.max_;

    for (const Sticker& sticker : other.stickers_) {
        stickers_.push_back({sticker.image, sticker.x, sticker.y});
    }
}

void StickerSheet::clear() {
    delete basePicture_;
    stickers_.resize(0);

    // for (Sticker& sticker : stickers_) {
    //     delete sticker.image;
    // }

}

void StickerSheet::copy(const StickerSheet& other) {
    clear();

    basePicture_ = new Image(*(other.basePicture_));
    max_ = other.max_;
    for (const Sticker& sticker : other.stickers_) {
        stickers_.push_back({sticker.image, sticker.x, sticker.y});
    }
}

StickerSheet::~StickerSheet() {
    clear();
}


const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
    copy(other);
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max) {

    Sticker emptySticker({nullptr,0,0});
    max_ = max;
    stickers_.resize(max_, emptySticker);
}

int StickerSheet::addSticker (Image &sticker, int x, int y) {
    for (unsigned i = 0; i < max_; ++i) {
        if (stickers_[i].image == nullptr) {
            stickers_[i] = {&sticker,x,y};
            return i;
        }
    }
    
    stickers_.push_back(Sticker(&sticker, x, y));
    max_++;
    return stickers_.size() - 1;

}
int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if (layer < stickers_.size()) {
        // if (stickers_[layer].image != nullptr) {
        //     delete stickers_[layer].image;
        // }
        stickers_[layer] = Sticker(&sticker, x, y);
        return layer;
    } else {
        return -1;
    }
}
bool StickerSheet::translate (unsigned index, int x, int y) {
    if (index < stickers_.size() && stickers_[index].image != nullptr) {
        stickers_[index].x = x;
        stickers_[index].y = y;
        return true;
    } else {
        return false;
    }
}
void StickerSheet::removeSticker (unsigned index) {

    if (index < stickers_.size() && stickers_[index].image != nullptr) {
        //delete stickers_[index].image;
        
        stickers_[index].image = nullptr;
    }

}
Image * StickerSheet::getSticker (unsigned index) {
    if (index < stickers_.size() && stickers_[index].image != nullptr) {
        return stickers_[index].image;
    } else {
        return nullptr;
    }
}
int StickerSheet::layers () const {
    return max_;
}
Image StickerSheet::render () const {
    unsigned baseWidth = basePicture_->width();
    unsigned baseHeight = basePicture_->height();

    unsigned maxWidth = baseWidth;
    unsigned maxHeight = baseHeight;

    int negativeX = 0;
    int negativeY = 0;

    for (const Sticker& sticker : stickers_) {
        if (sticker.image != nullptr) {
            unsigned LargestX = sticker.image->width() + sticker.x;
            unsigned LargestY = sticker.image->height() + sticker.y;

            if (LargestX > maxWidth && static_cast<int>(sticker.image->width()) + sticker.x > 0) {
                maxWidth = LargestX;
            }
            if (LargestY > maxHeight && static_cast<int>(sticker.image->height()) + sticker.y > 0) {
                maxHeight = LargestY;
            }
            if (sticker.x < negativeX) {
                negativeX = sticker.x;
            }
            if (sticker.y < negativeY) {
                negativeY = sticker.y;
            }
        }
    }
    maxWidth -= negativeX;
    maxHeight -= negativeY;
    Image result(*basePicture_);
    result.resize(maxWidth, maxHeight); //create a new image with enough size
    

    if (negativeX < 0 || negativeY < 0) {
        cs225::HSLAPixel white;

        //make whole canva white
        for (unsigned x = 0; x < maxWidth; ++x) {
            for (unsigned y = 0; y < maxHeight; ++y) {
                cs225::HSLAPixel& p = result.getPixel(x, y);
                p = white;
            }
        }
        // //draw the base picture 
        for (unsigned x = 0; x < baseWidth; ++x) {
            for (unsigned y = 0; y < baseHeight; ++y) {
                cs225::HSLAPixel& pixel = result.getPixel(x - negativeX, y - negativeY);
                pixel = basePicture_->getPixel(x, y);
            }
        }
    }


    //std::cout << "Reached line " << __LINE__ << std::endl;

    //draw the stickers
    for (const Sticker& sticker : stickers_) {
        if (sticker.image != nullptr) {
            unsigned stickerWidth = sticker.image->width();
            unsigned stickerHeight = sticker.image->height();

            for (unsigned x = 0; x < stickerWidth; ++x) {
                for (unsigned y = 0; y < stickerHeight; ++y) {
                    unsigned resultX = x - negativeX + sticker.x;
                    unsigned resultY = y - negativeY + sticker.y;


                    
                    cs225::HSLAPixel& resultPixel = result.getPixel(resultX, resultY);

                    cs225::HSLAPixel stickerPixel = sticker.image->getPixel(x, y);


                    if (stickerPixel.a != 0) {
                        resultPixel = stickerPixel;
                    }
                
                }
            }
        }
    }

    return result;
}
