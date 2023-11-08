#include "Image.h"

Image::Image(const std::string_view& path) {
    std::ifstream stream;
    stream.open(std::string(path), std::ios_base::binary);
    if (!stream.is_open()) {
        throw std::runtime_error("No such file or directory: " + std::string(path));
    }

    BMPFileHeader file_header;
    stream.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    BMPInfoHeader info_header;
    stream.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (info_header.size != sizeof(info_header)) {
        throw std::runtime_error("Error: Input file must be BMP! But this was given:" + std::string(path));
    }
    if (info_header.bit_count != BITSIZE) {
        throw std::runtime_error("Only 24-bit BMPs are supported");
    }
    if (info_header.width < 0) {
        throw std::runtime_error("BMP with negative width");
    }

    SetSize(info_header.width, std::abs(info_header.height));
    channels_.resize(3);
    for (auto& channel : channels_) {
        channel.resize(info_header.height, std::vector<double>(info_header.width));
    }

    const int padding = ((4 - (info_header.width * 3) % 4) % 4);

    for (size_t y = 0; y < std::abs(info_header.height); ++y) {
        for (size_t x = 0; x < info_header.width; ++x) {
            uint8_t pixel_color[3];
            static const double MAX_CHANNEL_VALUE = 255;
            stream.read(reinterpret_cast<char*>(&pixel_color), 3);
            size_t valid_y = info_header.height > 0 ? info_header.height - y - 1 : y;
            channels_[0][valid_y][x] = static_cast<double>(pixel_color[2]) / MAX_CHANNEL_VALUE;
            channels_[1][valid_y][x] = static_cast<double>(pixel_color[1]) / MAX_CHANNEL_VALUE;
            channels_[2][valid_y][x] = static_cast<double>(pixel_color[0]) / MAX_CHANNEL_VALUE;
        }
        stream.seekg(padding, std::ios_base::cur);
    }
    stream.close();
}

void Image::BMPWriteFile(const std::string_view& path) {
    if (path.substr(path.size() - 4, 4) != ".bmp") {
        throw std::runtime_error("Error: Output file must be BMP! But this was given:" + std::string(path));
    }
    std::ofstream stream;
    stream.open(std::string(path), std::ios_base::binary);
    if (!stream.is_open()) {
        throw std::runtime_error("Error: Unable to open the input file: " + std::string(path));
    }

    // Write the file header
    BMPFileHeader file_header;
    file_header.file_size =
        sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) +
        channels_[0].size() * (3 * channels_[0][0].size() + ((4 - (channels_[0][0].size() * 3) % 4) % 4));
    file_header.reserved = 0;
    file_header.reserved2 = 0;
    file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    stream.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));

    // Write the info header
    BMPInfoHeader info_header;
    info_header.size = sizeof(BMPInfoHeader);
    info_header.width = static_cast<int32_t>(channels_[0][0].size());
    info_header.height = static_cast<int32_t>(channels_[0].size());
    info_header.planes = 1;
    info_header.bit_count = BITSIZE;
    info_header.compression = 0;
    info_header.image_size = file_header.file_size - file_header.offset_data;
    info_header.x_pixels_per_meter = 0;
    info_header.y_pixels_per_meter = 0;
    info_header.colors_used = 0;
    info_header.colors_important = 0;
    stream.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    const int padding = ((4 - (info_header.width * 3) % 4) % 4);
    for (int y = info_header.height - 1; y >= 0; --y) {
        for (int x = 0; x < info_header.width; ++x) {
            uint8_t pixel_color[3];
            static const double MAX_CHANNEL_VALUE = 255;
            if (channels_.size() == 3) {
                pixel_color[2] = static_cast<uint8_t>(channels_[0][y][x] * MAX_CHANNEL_VALUE);  // blue channel
                pixel_color[1] = static_cast<uint8_t>(channels_[1][y][x] * MAX_CHANNEL_VALUE);  // green channel
                pixel_color[0] = static_cast<uint8_t>(channels_[2][y][x] * MAX_CHANNEL_VALUE);  // red channel
            } else if (channels_.size() == 1) {
                pixel_color[2] = static_cast<uint8_t>(channels_[0][y][x] * MAX_CHANNEL_VALUE);  // blue channel
                pixel_color[1] = static_cast<uint8_t>(channels_[0][y][x] * MAX_CHANNEL_VALUE);  // green channel
                pixel_color[0] = static_cast<uint8_t>(channels_[0][y][x] * MAX_CHANNEL_VALUE);  // red channel
            } else {
                throw std::runtime_error("Warning: something wrong with bmp format file");
            }
            stream.write(reinterpret_cast<char*>(&pixel_color), 3);
        }
        uint8_t padding_data[3];
        stream.write(reinterpret_cast<char*>(&padding_data), padding);
    }

    stream.close();
}

std::vector<Image::Channel>& Image::GetChannels() {
    return channels_;
}

void Image::SetSize(uint32_t width, uint32_t height) {
    width_ = width;
    height_ = height;
}

uint32_t Image::GetHeight() const {
    return height_;
}

uint32_t Image::GetWidth() const {
    return width_;
}