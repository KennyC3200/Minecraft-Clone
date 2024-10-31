#pragma once

#include "../util/util.hpp"
#include "block.hpp"

class BlockData {
public:
    BlockData();
    ~BlockData();

    int metadata_get();
    void metadata_set(int metadata);
    int sunlight_intensity_get();
    void sunlight_intensity_set(int sunlight_intensity);
    int light_r_get();
    void light_r_set(int light_r);
    int light_g_get();
    void light_g_set(int light_g);
    int light_b_get();
    void light_b_set(int light_b);
    int light_intensity_get();
    void light_intensity_set(int light_intensity);
    int id_get();
    void id_set(int id);
private:
    /*
     * 28 bits metadata/extra
     * 4 bits sunlight intensity
     * 4 bits R light
     * 4 bits G light
     * 4 bits B light
     * 4 bits light intensity
     * 16 bits block id
     * */
    uint32_t data;
};
