#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>

// Constants for BMP header size
const int BITSIZE = 24;
const int TYPE = 0x4D42;

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{TYPE};
    uint32_t file_size;
    uint16_t reserved;
    uint16_t reserved2;
    uint32_t offset_data;
};

struct BMPInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes{1};
    uint16_t bit_count;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
};
#pragma pack(pop)

class Image {
public:
    using Channel = std::vector<std::vector<double>>;

    explicit Image(const std::string_view& path);
    void BMPWriteFile(const std::string_view& path);

    void SetSize(uint32_t width, uint32_t height);
    uint32_t GetHeight() const;
    uint32_t GetWidth() const;

    std::vector<Channel>& GetChannels();

private:
    std::vector<Channel> channels_;
    uint32_t width_;
    uint32_t height_;
};