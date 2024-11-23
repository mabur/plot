#include "plot.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_WRITE_PNG
#include <stb_image_write.h>
#include <carma/carma.h>

const Color WHITE = makeColor(255, 255, 255, 255);
const Color GRAY = makeColor(160, 160, 160, 255);

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
    return height - (size_t)(border * height + (y_in_plot - ymin) / (ymax - ymin) * height * (1 - 2 * border));
}

static
void rasterizePoints(Points points, Axes axes, Image image) {
    FOR_EACH(point, points) {
        auto xi = xInImage(point->x, axes, image);
        auto yi = yInImage(point->y, axes, image);
        
        auto R = 4;
        for (int dy = -R; dy <= R; dy += 1) {
            for (int dx = -R; dx <= R; dx += 1) {
                if (dx * dx + dy * dy < R * R) {
                    image.data[(yi + dy) * image.width + xi + dx] = point->color;
                }
            }
        }
    }
}

static
void rasterizeLines(Lines lines, Image image) {

}

static
void rasterizeVerticalLine(size_t x, size_t ymin, size_t ymax, Color color, Image image) {
    for (size_t y = ymin; y <= ymax; ++y) {
        image.data[y * image.width + x] = color;
    }
}

static
void rasterizeHorizontalLine(size_t y, size_t xmin, size_t xmax, Color color, Image image) {
    for (size_t x = xmin; x <= xmax; ++x) {
        image.data[y * image.width + x] = color;
    }
}

static
void rasterizeAxes(Axes axes, Image image) {
    auto xi_min = xInImage(axes.xmin, axes, image);
    auto xi_max = xInImage(axes.xmax, axes, image);
    auto yi_min = yInImage(axes.ymax, axes, image);
    auto yi_max = yInImage(axes.ymin, axes, image);
    
    for (double xd = axes.xmin; xd - 0.5 * axes.xstep < axes.xmax; xd += axes.xstep) {
        auto xi = xInImage(xd, axes, image);
        xi = xi >= image.width ? image.width - 1 : xi;
        rasterizeVerticalLine(xi, yi_min, yi_max, GRAY, image);
    }
    for (double yd = axes.ymin; yd - 0.5 * axes.ystep < axes.ymax; yd += axes.ystep) {
        auto yi = yInImage(yd, axes, image);
        yi = yi >= image.height ? image.height - 1 : yi;
        rasterizeHorizontalLine(yi, xi_min, xi_max, GRAY, image);
    }
}

Image rasterizePlot(Plot plot) {
    auto image = (Image){};
    INIT_IMAGE(image, plot.width, plot.height);
    FILL(image, WHITE);
    rasterizeAxes(plot.axes, image);
    rasterizePoints(plot.points, plot.axes, image);
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
