//
// Created by Alienson on 16.4.2024..
//

#ifndef INC_3DTEST_ASSETMANAGER_H
#define INC_3DTEST_ASSETMANAGER_H

#include <unordered_map>
#include <iostream>

template <typename T>
class AssetManager {
public:

    AssetManager() = default;
    ~AssetManager(){
        for (auto tex : assetsMap){
            delete tex.second;
        }
    }

    [[nodiscard]] T* getAsset(unsigned int id){
        if (assetsMap.find(id) == assetsMap.end()) {
            std::cout << "Asset " << id << "not loaded in memory!\n";
            exit(100);
        }
        return assetsMap[id];
    }

    template<typename... Args>
    [[maybe_unused]] T* createAsset(Args&&... args){
        T* asset = new T(args...);
        assetsMap[asset->ID] = asset;
        return asset;
    }

private:
    std::unordered_map<unsigned int, T*> assetsMap;
};

#endif //INC_3DTEST_ASSETMANAGER_H
