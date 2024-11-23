#include "plot.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_WRITE_PNG
#include <stb_image_write.h>
#include <carma/carma.h>

static
Color makeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (Color)r | ((Color)g << 8) | ((Color)b << 16) | ((Color)a << 24);
}

static
void rasterizePoints(Points points, Image image) {
    
}

static
void rasterizeLines(Lines lines, Image image) {

}

static
void rasterizeAxes(Axes axes, Image image) {

}

Image rasterizePlot(Plot plot) {
    auto image = (Image){};
    INIT_IMAGE(image, plot.width, plot.height);
    auto WHITE = makeColor(255, 255, 255, 255);
    FILL(image, WHITE);
    rasterizeAxes(plot.axes, image);
    rasterizePoints(plot.points, image);
    rasterizeLines(plot.lines, image);
    return image;
}

int writePng(Image image, const char* file_path) {
    auto width = (int)image.width;
    auto height = (int)image.height;
    auto data = (void*)image.data;
    auto channels = sizeof(*image.data);
    auto stride = width * channels;
    return stbi_write_png(file_path, width, height, channels, data, stride);
}