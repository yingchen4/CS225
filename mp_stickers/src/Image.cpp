#include "Image.h"
Image::Image (unsigned int width, unsigned int height) {
    PNG(width,height);
}
void Image::darken() {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            if (this->getPixel(i,j).l >= 0.1) {
                this->getPixel(i,j).l -= 0.1;
            } else {
                this->getPixel(i,j).l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            if (this->getPixel(i,j).l >= amount) {
                this->getPixel(i,j).l -= amount;
            } else {
                this->getPixel(i,j).l = 0;
            }
        }
    }
}
void Image::desaturate() {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            if (this->getPixel(i,j).s >= 0.1) {
                this->getPixel(i,j).s -= 0.1;
            } else {
                this->getPixel(i,j).s = 0;
            }
        }
    }    
}
void Image::desaturate(double amount) {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            if (this->getPixel(i,j).s >= amount) {
                this->getPixel(i,j).s -= amount;
            } else {
                this->getPixel(i,j).s = 0;
            }
        }
    }     
}
void Image::grayscale() {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            this->getPixel(i,j).s = 0;
        }
    }   
}
void Image::illinify() {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            //“Illini Orange” has a hue of 11
            //“Illini Blue” has a hue of 216
            double curr_hue = this->getPixel(i,j).h;
            if (curr_hue >= 114 && curr_hue <= 293) {
                this->getPixel(i,j).h = 216;
            } else {
                this->getPixel(i,j).h = 11;
            }

        }
    }     
}
void Image::lighten() {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            if (this->getPixel(i,j).l <= 0.9) {
                this->getPixel(i,j).l += 0.1;
            } else {
                this->getPixel(i,j).l = 1.0;
            }
        }
    }  
}
void Image::lighten(double amount) {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            if (this->getPixel(i,j).l <= (1 - amount)) {
                this->getPixel(i,j).l += amount;
            } else {
                this->getPixel(i,j).l = 1.0;
            }
        }
    } 
}
void Image::rotateColor(double degrees) {
    int width = this->width();
    int height = this->height();
    
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            double curr_hue = this->getPixel(i,j).h;
            if (curr_hue + degrees >= 0  && curr_hue + degrees <= 360) {
                this->getPixel(i,j).h += degrees;
            } else if (curr_hue + degrees < 0) {
                this->getPixel(i,j).h = this->getPixel(i,j).h + degrees + 360;
            } else {
                this->getPixel(i,j).h = degrees - 360 + this->getPixel(i,j).h;
            }
        }
    } 
}
void Image::saturate() {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            if (this->getPixel(i,j).s <= 0.9) {
                this->getPixel(i,j).s += 0.1;
            } else {
                this->getPixel(i,j).s = 1.0;
            }
        }
    } 
}
void Image::saturate(double amount) {
    int width = this->width();
    int height = this->height();
    for(int i = 0; i < width; i++) {
        for(int j=0; j< height; j++) {
            if (this->getPixel(i,j).s <= (1 - amount)) {
                this->getPixel(i,j).s += amount;
            } else {
                this->getPixel(i,j).s = 1.0;
            }
        }
    } 
}
void Image::scale(double factor) {
    if (factor == 1.0) {
        return;
    }
    unsigned int new_width = this->width()*factor;
    unsigned int new_height = this->height()*factor;

    cs225::PNG copyImage(*this);//a copy of current image
    this->resize(new_width,new_height);//change current image to new size

    for (unsigned int x = 0; x < new_width; x++) {
        for (unsigned int y = 0; y < new_height; y++) {
            unsigned int originalX = static_cast<unsigned int>(x / factor);
            unsigned int originalY = static_cast<unsigned int>(y / factor);

            this->getPixel(x, y) = copyImage.getPixel(originalX,originalY);
        }
    }
}

void Image::scale(unsigned w,unsigned h) {
    double ratioW = static_cast<double>(w) / width();
    double ratioH = static_cast<double>(h) / height();
    
    double factor = 1.0;
    factor = (ratioW < ratioH) ? ratioW : ratioH;

    scale(factor);
}