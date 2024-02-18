#include "sketching.h"
#include <algorithm>
#include <cmath>

// Helper function to find the k minimum values in a vector
std::vector<uint64_t> findKMinValues(const std::vector<uint64_t>& values, unsigned k) {
    std::vector<uint64_t> result;
    
    std::vector<uint64_t> sortedValues = values;
    std::sort(sortedValues.begin(), sortedValues.end());

    for (unsigned i = 0; i < k && i < sortedValues.size(); ++i) {
        result.push_back(sortedValues[i]);
    }

    while (result.size() < k) {
        result.push_back(GLOBAL_MAX_INT);
    }

    return result;
}

std::vector<uint64_t> kminhash(std::vector<int> inList, unsigned k, hashFunction h) {
    std::vector<uint64_t> minhashValues;
    std::set<uint64_t> uniqueHashValues;
    for (int value : inList) {
        uint64_t hashResult = h(value);
        if (uniqueHashValues.find(hashResult) == uniqueHashValues.end()) {
            minhashValues.push_back(hashResult);
            uniqueHashValues.insert(hashResult);
        }
    }
    return findKMinValues(minhashValues, k);
}

std::vector<uint64_t> khash_minhash(std::vector<int> inList, std::vector<hashFunction> hv) {
    std::vector<uint64_t> minhashValues;
    for (hashFunction h : hv) {
        std::vector<uint64_t> hashValues;
        for (int value : inList) {
            hashValues.push_back(h(value));
        }
        minhashValues.push_back(*std::min_element(hashValues.begin(), hashValues.end()));
    }
    return minhashValues;
}
std::vector<uint64_t> kpartition_minhash(std::vector<int> inList, int part_bits, hashFunction h) {
    std::vector<uint64_t> minhashValues(1ULL << part_bits, GLOBAL_MAX_INT);

    for (int value : inList) {
        uint64_t hashResult = h(value);
        uint64_t partition = hashResult >> (64 - part_bits);
        minhashValues[partition] = std::min(minhashValues[partition], hashResult);
    }

    return minhashValues;
}

float minhash_jaccard(std::vector<uint64_t> mh1, std::vector<uint64_t> mh2) {
    std::set<uint64_t> set1(mh1.begin(), mh1.end());
    std::set<uint64_t> set2(mh2.begin(), mh2.end());

    set1.erase(GLOBAL_MAX_INT);
    set2.erase(GLOBAL_MAX_INT);

    std::set<uint64_t> unionSet;
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(unionSet, unionSet.begin()));

    std::set<uint64_t> intersectionSet;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(intersectionSet, intersectionSet.begin()));

    float intersectionSize = static_cast<float>(intersectionSet.size());
    float unionSize = static_cast<float>(unionSet.size());

    if (unionSize == 0) {
        // empty union
        return 1.0;
    }

    return intersectionSize / unionSize;
}

int minhash_cardinality(std::vector<uint64_t> mh, unsigned k) {
    std::vector<uint64_t> mhCopy(mh);

    uint64_t k_min = mhCopy[k - 1];
    double k_min_double = static_cast<double>(k_min);
    double max = static_cast<double>(GLOBAL_MAX_INT);
    double k_min_normal = k_min_double/max;

    double estimated_cardinality = (static_cast<double>(k) / k_min_normal) - 1;
    int rounded_cardinality = static_cast<int>(std::ceil(estimated_cardinality));

    return rounded_cardinality;
}

float exact_jaccard(std::vector<int> raw1, std::vector<int> raw2) {
    std::set<int> set1(raw1.begin(), raw1.end());
    std::set<int> set2(raw2.begin(), raw2.end());

    size_t intersectCount = 0;
    for (int value : set1) {
        if (set2.find(value) != set2.end()) {
            ++intersectCount;
        }
    }

    size_t unionCount = set1.size() + set2.size() - intersectCount;

    return static_cast<float>(intersectCount) / static_cast<float>(unionCount);
}

int exact_cardinality(std::vector<int> raw) {
    std::set<int> uniqueSet(raw.begin(), raw.end());
    return static_cast<int>(uniqueSet.size());
}



MM::MM(const cs225::PNG& input, unsigned numTiles, unsigned k, hashFunction h) : numTiles_(numTiles), k_(k), hashFunction_(h) {
    
    width_length_ = static_cast<int>(std::ceil(static_cast<double>(input.width()) / static_cast<double>(numTiles)));
    height_length_ = static_cast<int>(std::ceil(static_cast<double>(input.height()) / static_cast<double>(numTiles)));
    // std::cout << "graph width: " << input.width() << " graph height: " << input.height() << std::endl;
    // std::cout << "numtiles: " << numTiles << " width_length " << width_length_ <<  " heightlength " << height_length_<< std::endl;

    for (unsigned j = 0; j < numTiles; ++j) {
        for (unsigned i = 0; i < numTiles; ++i) {
            minHashMatrix_.push_back(computeMinHash(input, i, j));
        }
    }
}

std::vector<uint64_t> MM::computeMinHash(const cs225::PNG &input, unsigned tileX, unsigned tileY) {
    std::vector<int> toHash;

    for (unsigned x = tileX * width_length_; x < (tileX + 1) * width_length_; ++x) {   
        if (x >= input.width()) {
            continue;
        }
        for (unsigned y = tileY * height_length_; y < (tileY + 1) * height_length_; ++y) {   
            if (y >= input.height()) {
                continue;
            }
            double luminance = input.getPixel(x, y).l; 
            toHash.push_back(static_cast<int>(luminance * 255.0));
        }
    }

    return kminhash(toHash, k_, hashFunction_);
}

std::vector<uint64_t> MM::getMinHash(unsigned width, unsigned height) const {

    return minHashMatrix_[height * numTiles_ + width];
}

int MM::countMatchTiles(const MM& other, float threshold) const {
    unsigned numTiles = numTiles_;

    int matchCount = 0;

    for (unsigned i = 0; i < numTiles; ++i) {
        for (unsigned j = 0; j < numTiles; ++j) {
            std::vector<uint64_t> currentTileSketch = getMinHash(i, j);
            std::vector<uint64_t> otherTileSketch = other.getMinHash(i, j);

            float similarity = minhash_jaccard(currentTileSketch, otherTileSketch);

            if (similarity >= threshold) {
                matchCount++;
            }
        }
    }

    return matchCount;
}


std::vector<std::tuple<int, int, int>> build_minhash_graph(std::vector<std::string> flist, unsigned numTiles, unsigned k, hashFunction h, float threshold) {
    std::vector<std::tuple<int, int, int>> edgeList;

    std::vector<MM> minhashObjects;
    for (const std::string& filename : flist) {
        cs225::PNG image;
        image.readFromFile(filename);
        MM minhashObject(image, numTiles, k, h);
        minhashObjects.push_back(minhashObject);
    }

    for (size_t i = 0; i < flist.size(); ++i) {
        for (size_t j = i + 1; j < flist.size(); ++j) {
            int matchingTiles = minhashObjects[i].countMatchTiles(minhashObjects[j], threshold);

            if (matchingTiles > 0) {
                edgeList.push_back(std::make_tuple(static_cast<int>(i), static_cast<int>(j), matchingTiles));
            }
        }
    }

    return edgeList;
}
