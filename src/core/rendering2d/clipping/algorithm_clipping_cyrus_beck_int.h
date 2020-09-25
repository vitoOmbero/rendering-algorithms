#ifndef ALGORITHM_CLIPPING_CYRUS_BECK_INT_H
#define ALGORITHM_CLIPPING_CYRUS_BECK_INT_H

#include <array>

#include "point2i.h"
#include "typedefs.h"

/*
 * 1) parametric equation of each line
 * 2) parametric equation of each window edge
 * 3) test each line and side
 * 4) solve undiscarded equations
 *
 * eq for line ('):
 *
 * x' = x1' + (x2' - x1') * t'  (1)
 * y' = y1' + (y2' - y1') * t'  (2)
 *
 * eq for edge ("):
 *
 * x" = x1" + (x2" - x1") * t"  (3)
 * y" = y1" + (y2" - y1") * t"  (4)
 *
 * to find intersections solve eq system:
 * { (1) = (3),
 * { (2) = (4);
 *
 * for t' and t".
 */

/*
 * eq for line:
 *
 * p(t) = P1 + (P2 - P1) * t;
 *
 * There is Intersection point and normal for each edge.
 *
 *  vector form:
 *
 *     N_l * [P_l - P2]
 * t = ----------------
 *     N_l * [P2 - P1]
 *
 * if (0 <= t <= 1): line is placed between P1 nd P2;
 * if ( t < 0 )    : line is placed before P1 (discard the line);
 * if ( t > 1 )    : line is placed after P2 (discard);
 *
 * define D = (P2 - P1) (D for line)
 * define W = (P_i - P2) (W_i for each edge)
 *
 * algebraic form:
 *
 *     - (W_i * n_i)
 * t = -------------
 *        D * n_i
 *
 * normal displacements 2d:
 *
 * ( -1, 0 ) for Right edge (vector: -i)
 * ( 1 , 0 ) for Left edge  (vector: i)
 * ( 0 , -1) for Top edge   (vector: -j)
 * ( 0 , 1 ) for Bottom edge(vector: j)
 *
 * line is Potential Leaving (P.L.) if D*n_i > 0;
 * line is Potential Entering (P.E.) if D*n_i < 0;
 *
 * t for edges:
 *
 *     - (x1 - x_left)
 * t = -------------
 *        x2 - x1
 *
 *      x1 - x_right
 * t = -------------
 *     - (x2 - x1)
 *
 *     - (y1 - y_bot)
 * t = -------------
 *        y2 - y1
 *
 *      y1 - y_top
 * t = -------------
 *     - (y2 - y1)
 *
 * constraints:
 *
 * if t is outside the interval [0;1]:
 *  additional check if (W_i * n_i < 0) & ( (W_i * n_i + n_i * D) < 0 ):
 *  == trivial invisability;
 *
 * if t is outside the interval [0;1]:
 *  additional check if (W_i * n_i > 0) & ( (W_i * n_i + n_i * D) > 0 ):
 *  == trivial visability;
 *
 * if t is inside the interval [0;1]:
 *  n_i * D > 0 == P.L., t is bottom limit
 *  n_i * D < 0 == P.E., t is top limit
 *
 * if bottom intersection point < top i.p. => is visible
 * if bot intersection point > top i.p. => is invisible
 *
 * if (D == 0)  => this is a point or line is || to edge
 */

namespace ra_core::rendering2d::clipping
{

std::array<ra_types::Point2i, 2> clipping_cyrus_beck_int(
    ra_types::Point2i first, ra_types::Point2i second,
    ra_types::Point2i rectwindow_maxX_maxY,
    ra_types::Point2i rectwindow_minX_minY);
}

#endif // ALGORITHM_CLIPPING_CYRUS_BECK_INT_H
