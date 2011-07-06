/** @file
 * 
 * Template matching observation model for particle filter
 * CvParticleState s must have s.x, s.y, s.width, s.height, s.angle
 *
 * The MIT License
 * 
 * Copyright (c) 2008, Naotoshi Seo <sonots(at)sonots.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef CV_PARTICLE_OBSERVE_TEMPLATE_H
#define CV_PARTICLE_OBSERVE_TEMPLATE_H

#include "opencvx/cvparticle.h"
#include "opencvx/cvrect32f.h"
#include "opencvx/cvcropimageroi.h"
using namespace std;

/********************* Globals **********************************/
int num_observes = 1;
CvSize feature_size;

/******************** Function Prototypes **********************/
#ifndef NO_DOXYGEN
void cvParticleObserveInitialize( CvSize featsize );
void cvParticleObserveFinalize( );
void cvParticleObserveMeasure( CvParticle* p, IplImage* cur_frame, IplImage *pre_frame );
#endif
/***************************************************************/

/**
 * Initialize
 */
void cvParticleObserveInitialize( CvSize featsize )
{
    feature_size = featsize;
}
/**
 * Finalize
 */
void cvParticleObserveFinalize( )
{
}

/**
 * Measure and weight particles. 
 *
 * The proposal function q is set p(xt|xt-1) in SIR/Condensation, and it results 
 * that "weights" are set to be proportional to the likelihood probability 
 * (Normalize later).
 * Rewrite here if you want to use a different proposal function q. 
 *
 * CvParticleState s must have s.x, s.y, s.width, s.height, s.angle
 *
 * @param particle
 * @param frame
 * @param reference
 */
void cvParticleObserveMeasure( CvParticle* p, IplImage* frame, IplImage *reference )
{
    int i;
    double likeli;
    IplImage *patch;
    IplImage *resize;
    resize = cvCreateImage( feature_size, frame->depth, frame->nChannels );
    for( i = 0; i < p->num_particles; i++ ) 
    {
        CvParticleState s = cvParticleStateGet( p, i );
        CvBox32f box32f = cvBox32f( s.x, s.y, s.width, s.height, s.angle );
        CvRect32f rect32f = cvRect32fFromBox32f( box32f );
        CvRect rect = cvRectFromRect32f( rect32f );
        
        patch = cvCreateImage( cvSize(rect.width,rect.height), frame->depth, frame->nChannels );
        cvCropImageROI( frame, patch, rect32f );
        cvResize( patch, resize );

        // log likeli. kinds of Gaussian model
        // exp( -d^2 / sigma^2 )
        // sigma can be omitted because common param does not affect ML estimate
        likeli = -cvNorm( resize, reference, CV_L2 ); 
        cvmSet( p->weights, 0, i, likeli );
        
        cvReleaseImage( &patch );
    }
    cvReleaseImage( &resize );
}

#endif
