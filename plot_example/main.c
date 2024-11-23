#define SDL_MAIN_HANDLED

#include <carma/carma.h>
#include <plot/plot.h>

int main(int, char**) {

    auto plot = (Plot){};
    plot.axes.xmin = 0;
    plot.axes.xstep = 0.1;
    plot.axes.xmax = 1;
    plot.axes.ymin = 0;
    plot.axes.ystep = 0.1;
    plot.axes.ymax = 1;
    plot.axes.x_label = "x";
    plot.axes.y_label = "y";
    plot.width = 640;
    plot.height = 480;
    
    for (auto x = 0.0; x < 1.0; x += 0.1) {
        auto y = x * x;
        auto radius = 0.01;
        auto color = (Color){0};
        auto point = (Point){x, y, radius, color};
        APPEND(plot.points, point);
    }

    auto image = rasterizePlot(plot);
    writePng(image, "output.png");

    return 0;
}
