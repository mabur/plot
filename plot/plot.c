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
size_t xInImage(double x_in_plot, Axes axes, Image image) {
    auto border = 0.1;
    auto xmin = axes.xmin;
    auto xmax = axes.xmax;
    auto width = (double)image.width;
    return (size_t)(border * width + (x_in_plot - xmin) / (xmax - xmin) * width * (1 - 2 * border));
}

static
size_t yInImage(double y_in_plot, Axes axes, Image image) {
    auto border = 0.1;
    auto ymin = axes.ymin;
    auto ymax = axes.ymax;
    auto height = (double)image.height;
    return (size_t)(border * height + (y_in_plot - ymin) / (ymax - ymin) * height * (1 - 2 * border));
}

static
void rasterizeVerticalLine(size_t x, Color color, Image image) {
    FOR_Y(y, image) {
        image.data[y * image.width + x] = color;
    }
}

static
void rasterizeHorizontalLine(size_t y, Color color, Image image) {
    FOR_X(x, image) {
        image.data[y * image.width + x] = color;
    }
}

static
void rasterizeAxes(Axes axes, Image image) {
    auto GRAY = makeColor(160, 160, 160, 255);
    for (double xd = axes.xmin; xd - 0.5 * axes.xstep < axes.xmax; xd += axes.xstep) {
        auto xi = xInImage(xd, axes, image);
        xi = xi >= image.width ? image.width - 1 : xi;
        rasterizeVerticalLine(xi, GRAY, image);
    }
    for (double yd = axes.ymin; yd - 0.5 * axes.ystep < axes.ymax; yd += axes.ystep) {
        auto yi = yInImage(yd, axes, image);
        yi = yi >= image.height ? image.height - 1 : yi;
        rasterizeHorizontalLine(yi, GRAY, image);
    }
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
