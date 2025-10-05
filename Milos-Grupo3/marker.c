#include "marker.h"

Marker newMarker(int x, int y) {
    Marker m;
    m.x = x;
    m.y = y;
    m.size = QUAD_SIZE;
    m.color = MARKER_COLOR;
    return m;
}

void MarkerDraw(Marker* m) {
    al_draw_filled_rectangle(m->x, m->y, m->x + m->size, m->y + m->size, m->color);
}
