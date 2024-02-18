#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma;
  alma.readFromFile("../data/alma.png");
  StickerSheet sheet(alma, 3);

  Image sticker1;
  sticker1.readFromFile("../data/i.png");

  Image sticker2;
  sticker2.readFromFile("../data/penguin.png");

  Image sticker3;
  sticker3.readFromFile("../data/penguin.png");


  sheet.addSticker(sticker1, 60, 60);

  sheet.addSticker(sticker2, -100, -500);

  sheet.addSticker(sticker3, 1000, 1000);

  Image result;
  result = sheet.render();
  std::cout << "Reached line " << __LINE__ << std::endl;
  result.writeToFile("myImage.png");

  return 0;
}
