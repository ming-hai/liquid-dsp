/*
 * Copyright (c) 2007, 2008, 2009, 2010 Joseph Gaeddert
 * Copyright (c) 2007, 2008, 2009, 2010 Virginia Polytechnic
 *                                      Institute & State University
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIQUID_GROUPDELAY_AUTOTEST_H__
#define __LIQUID_GROUPDELAY_AUTOTEST_H__

#include "autotest/autotest.h"
#include "liquid.h"

void autotest_fir_groupdelay_n3()
{
    // create coefficients array
    float h[3] = {0.1, 0.2, 0.4};

    float tol = 1e-3f;
    unsigned int i;

    // create testing vectors
    float fc[4] = { 0.000,
                    0.125,
                    0.250,
                    0.375};
    
    float g0[4] = { 1.42857142857143,
                    1.54756605839643,
                    2.15384615384615,
                    2.56861651421767};


    // run tests
    float g;
    for (i=0; i<4; i++) {
        g = fir_group_delay(h, 3, fc[i]);
        CONTEND_DELTA( g, g0[i], tol );
    }

    // create filter
    firfilt_rrrf filter = firfilt_rrrf_create(h,3);

    // run tests again
    for (i=0; i<4; i++) {
        g = firfilt_rrrf_groupdelay(filter, fc[i]);
        CONTEND_DELTA( g, g0[i], tol );
    }

    // destroy filter
    firfilt_rrrf_destroy(filter);
}

#endif // __LIQUID_GROUPDELAY_AUTOTEST_H__
