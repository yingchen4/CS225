/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"

BF::BF(uint64_t size, std::vector<hashFunction> hashList){
    bv.resize(size, false);
    hv = hashList;
}

BF::BF(const BF& other){
    bv = other.bv;
    hv = other.hv;
}

BF::~BF(){
    return;
}

void BF::add(const int & key){
    for (auto& hashFunc : hv) {
        int index = hashFunc(key) % bv.size();
        bv[index] = true;
    }
}

bool BF::contains(const int& key) const{
    for (const auto& hashFunc : hv) {
        int index = hashFunc(key) % bv.size();
        if (!bv[index]) {
            return false;
        }
    }
    return true;
}

void BF::bit_union(const BF& other){
    for (size_t i = 0; i < bv.size(); ++i) {
        bv[i] = bv[i] || other.bv[i];
    }
}

void BF::intersect(const BF& other){
    for (size_t i = 0; i < bv.size(); ++i) {
        bv[i] = bv[i] && other.bv[i];
    }
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    BF bloomFilter(size, hashList);

    for (const int& element : inList) {
        bloomFilter.add(element);
    }

    unsigned falsePositives = 0;
    unsigned trueNegatives = 0;
    for (unsigned i = 0; i < max; ++i) {
        if (std::find(inList.begin(), inList.end(), i) != inList.end()) {
        } else {
            if (bloomFilter.contains(i)) {
                falsePositives++;
            } else {
                trueNegatives++;
            }
        }
    }

    float FPR = static_cast<float>(falsePositives) / static_cast<float>(falsePositives + trueNegatives);
    return FPR;

}

bool getBitFromArray(std::vector<char> bv, int index) {
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    if (byteIndex >= static_cast<int>(bv.size())) {
        return false;
    }
    char byte = bv[byteIndex];

    char bitmask = 1 << (7-bitIndex);
    return (byte & bitmask) != 0;
}


bool getBitFromByte(char in, int index){
    return (in & (1 << (7-index))) != 0;
}

