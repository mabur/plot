#pragma once

#include <stdint.h>

#define auto __auto_type

typedef uint32_t Color;

typedef struct Point {
    double x;
    double y;
    double radius;
    Color color;
} Point;

typedef struct Line {
    double x0;
    double x1;
    double y0;
    double y1;
    double thickness;
    Color color;
} Line;

typedef struct VerticalLine {
    double x;
    double y0;
    double y1;
    double thickness;
    Color color;
} VerticalLine;

typedef struct HorizontalLine {
    double x0;
    double x1;
    double y;
    double thickness;
    Color color;
} HorizontalLine;

typedef struct Points {
    Point* data;
    size_t count;
    size_t capacity;
} Points;

typedef struct Lines {
    Line* data;
    size_t count;
    size_t capacity;
} Lines;

typedef struct VerticalLines {
    VerticalLine* data;
    size_t count;
    size_t capacity;
} VerticalLines;

typedef struct HorizontalLines {
    HorizontalLine* data;
    size_t count;
    size_t capacity;
} HorizontalLines;

typedef struct Axes {
    double xmin;
    double ymin;
    double xstep;
    double ystep;
    double xmax;
    double ymax;
    const char* x_label;
    const char* y_label;
    const char* x_format;
    const char* y_format;
} Axes;

typedef struct Plot {
    Points points;
    Lines lines;
    Axes axes;
    size_t width;
    size_t height;
} Plot;

typedef struct Image {
    Color* data;
    size_t count;
    size_t width;
    size_t height;
} Image;

Image rasterizePlot(Plot plot);
