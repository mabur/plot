#include "plot.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_WRITE_PNG
#include <stb_image_write.h>
#include <carma/carma.h>

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
    auto WHITE = (Color){1};
    FILL(image, WHITE);
    rasterizeAxes(plot.axes, image);
    rasterizePoints(plot.points, image);
    rasterizeLines(plot.lines, image);
    return image;
}

void writePng() {
    // Define image properties
    int width = 256;
    int height = 256;
    int channels = 3; // RGB format
    unsigned char *image = (unsigned char *)malloc(width * height * channels);

    // Generate an example image (gradient pattern)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels;
            image[index + 0] = (unsigned char)(x % 256); // Red
            image[index + 1] = (unsigned char)(y % 256); // Green
            image[index + 2] = 128;                      // Blue
        }
    }

    // Write the image to a PNG file
    if (stbi_write_png("output.png", width, height, channels, image, width * channels)) {
        printf("Image successfully written to output.png\n");
    } else {
        printf("Failed to write image\n");
    }

    // Free the image buffer
    free(image);
}