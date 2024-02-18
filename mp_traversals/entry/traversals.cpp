
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "ImageTraversal.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG png;      png.readFromFile("../data/pacman.png");
  
  FloodFilledImage image(png);
  Traversals::ImageTraversal bfs(png, Point(100, 50), 0.2, {
    Traversals::bfs_add, Traversals::bfs_pop, Traversals::bfs_peek
  });

  HSLAPixel color(193, 1, 0.5);
  HSLAPixel color2(300, 1, 0.5);
  MyColorPicker my(color,color2);
  image.addFloodFill( bfs, my);

  Animation animation = image.animate(1000);

  // REQUIRE( animation.frameCount() > 2 );
  // PNG secondFrame = animation.getFrame(1);

  // secondFrame.writeToFile("pacman-solid-bfs-2.png");



  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
