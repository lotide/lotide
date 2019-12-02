////////////////////////////////////////////
// X-graph
// Copyright 2004, David Joiner and
//   The Shodor Education Foundation, Inc.
////////////////////////////////////////////

#include "X-graph.h"
#include "display.h"  /* getDisplay() */

void xgraphSetup(xgraph * thegraph, int width_in, int height_in) {
    thegraph->width = width_in;
    thegraph->height = height_in;

    thegraph->dpy = XOpenDisplay( getDisplay() );
    assert(thegraph->dpy);

    thegraph->blackColor =
        BlackPixel(thegraph->dpy, DefaultScreen(thegraph->dpy));
    thegraph->whiteColor =
        WhitePixel(thegraph->dpy, DefaultScreen(thegraph->dpy));

    thegraph->w =
        XCreateSimpleWindow(thegraph->dpy, DefaultRootWindow(thegraph->dpy),
        0, 0, thegraph->width, thegraph->height,
        0, thegraph->whiteColor, thegraph->whiteColor);

    thegraph->buffer =
        XCreatePixmap(thegraph->dpy,DefaultRootWindow(thegraph->dpy),
        thegraph->width,thegraph->height,DefaultDepth(thegraph->dpy,
        DefaultScreen(thegraph->dpy)));
          
    XSelectInput(thegraph->dpy, thegraph->w, StructureNotifyMask);

    XMapWindow(thegraph->dpy, thegraph->w);

    thegraph->gc = XCreateGC(thegraph->dpy, thegraph->w, 0, NIL);

    XSetForeground(thegraph->dpy, thegraph->gc, thegraph->blackColor);

    for(;;) {
        XEvent e;
        XNextEvent(thegraph->dpy, &e);
        if (e.type == MapNotify)
            break;
    }

}

void xgraphDraw(xgraph * thegraph, int npoints, double xmin, double ymin,
    double xmax, double ymax, double * x, double * y) {
    double xrange, yrange;
    int i;
    int xold, yold, xnew, ynew;

    xrange = xmax - xmin;
    yrange = ymax - ymin;

    XSetForeground(thegraph->dpy, thegraph->gc, thegraph->whiteColor);
    XFillRectangle(thegraph->dpy,thegraph->buffer,thegraph->gc,
        0,0,thegraph->width,thegraph->height);

    XSetForeground(thegraph->dpy,thegraph->gc,thegraph->blackColor);
    xold = (int) ( (x[0]-xmin)/xrange*(double)thegraph->width );
    yold = thegraph->height -
        (int) ( (y[0]-ymin)/yrange*(double)thegraph->height );
    for (i=1;i<npoints;i++) {
        xnew = (int) ( (x[i]-xmin)/xrange*(double)thegraph->width );
        ynew = thegraph->height -
            (int) ( (y[i]-ymin)/yrange*(double)thegraph->height );
        XDrawLine(thegraph->dpy,thegraph->buffer,thegraph->gc,
            xold,yold,xnew,ynew);
        xold = xnew;
        yold = ynew;       
    }
     
    XCopyArea(thegraph->dpy, thegraph->buffer, thegraph->w,
        thegraph->gc, 0, 0,
        thegraph->width, thegraph->height,  0, 0);
    XFlush(thegraph->dpy);
}
