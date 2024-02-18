/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{   
    int row = theSource.getRows();
    int column = theSource.getColumns();
    map<Point<3>, TileImage*> map;
    vector<Point<3>> vec;

    MosaicCanvas* canvas = new MosaicCanvas (row, column);
    for (auto& image : theTiles) {
        LUVAPixel avg = image.getAverageColor();
        Point<3> p = convertToXYZ(avg);
        vec.push_back(p);
        map[p] = &image;

    }
    KDTree<3> tree(vec);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            LUVAPixel color = theSource.getRegionColor(i, j);
            Point<3> initial = convertToXYZ(color);
            Point<3> neighbor = tree.findNearestNeighbor(initial);
            if(map.find(neighbor) == map.end()) {
                std::cout << " SHOULD NOT BE HERE" << std::endl;
            }
            TileImage * tile = map[neighbor];
            canvas->setTile(i, j, tile);
        }
    }

    return canvas;
}

