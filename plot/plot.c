#include "plot.h"

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
