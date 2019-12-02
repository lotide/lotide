////////////////////////////////////////////
// X-graph
// Copyright 2004, David Joiner and
//   The Shodor Education Foundation, Inc.
////////////////////////////////////////////
#ifndef XGRAPH
#define XGRAPH

#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>
#define NIL (0)

typedef struct xgraph_mem {
    Display *dpy;
    int blackColor;
    int whiteColor;
    int width,height;
    Window w;
    GC gc;
    Pixmap buffer;
} xgraph;

void xgraphSetup(xgraph * thegraph, int width_in, int height_in);

void xgraphDraw(xgraph * thegraph, int npoints, double xmin, double ymin,
    double xmax, double ymax, double * x, double * y);

#endif
