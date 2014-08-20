#ifndef _LUT_SUBR_H_
#define _LUT_SUBR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "common.h"
#include "espa_metadata.h"
#include "error_handler.h"

/* Prototypes */
int atmcorlamb2
(
    float xts,                       /* I: solar zenith angle (deg) */
    float xtv,                       /* I: observation zenith angle (deg) */
    float xfi,                       /* I: azimuthal difference between sun and
                                           observation (deg) */
    float raot550nm,                 /* I: nearest value of AOT */
    int iband,                       /* I: band index (0-based) */
    float pres,                      /* I: surface pressure */
    float tpres[7],                  /* I: surface pressure table */
    float aot550nm[22],              /* I: AOT look-up table */
    float ****rolutt,                /* I: intrinsic reflectance table
                                           [NSR_BANDS][7][22][8000] */
    float ****transt,                /* I: transmission table
                                           [NSR_BANDS][7][22][22] */
    float xtsstep,                   /* I: solar zenith step value */
    float xtsmin,                    /* I: minimum solar zenith value */
    float xtvstep,                   /* I: observation step value */
    float xtvmin,                    /* I: minimum observation value */
    float ***sphalbt,                /* I: spherical albedo table
                                           [NSR_BANDS][7][22] */
    float **tsmax,                   /* I: maximum scattering angle table
                                           [20][22] */
    float **tsmin,                   /* I: minimum scattering angle table
                                           [20][22] */
    float **nbfic,                   /* I: communitive number of azimuth angles
                                           [20][22] */
    float **nbfi,                    /* I: number of azimuth angles [20][22] */
    float tts[22],                   /* I: sun angle table */
    int32 indts[22],
    float **ttv,                     /* I: view angle table [20][22] */
    float uoz,                       /* I: total column ozone */
    float uwv,                       /* I: total column water vapor (precipital
                                           water vapor) */
    float tauray[NSR_BANDS],         /* I: molecular optical thickness coeff */
    double ogtransa1[NSR_BANDS],     /* I: other gases transmission coeff */
    double ogtransb0[NSR_BANDS],     /* I: other gases transmission coeff */
    double ogtransb1[NSR_BANDS],     /* I: other gases transmission coeff */
    double wvtransa[NSR_BANDS],      /* I: water vapor transmission coeff */
    double wvtransb[NSR_BANDS],      /* I: water vapor transmission coeff */
    double oztransa[NSR_BANDS],      /* I: ozone transmission coeff */
    float rotoa,                     /* I: top of atmosphere reflectance */
    float *roslamb,                  /* O: lambertian surface reflectance */
    float *tgo,                      /* O: other gaseous transmittance */
    float *roatm,                    /* O: atmospheric reflectance */
    float *ttatmg,
    float *satm,                     /* O: spherical albedo */
    float *xrorayp                   /* O: molecular reflectance */
);

void local_chand
(
    float xphi,    /* I: azimuthal difference between sun and observation
                         (deg) */
    float xmuv,    /* I: cosine of observation zenith angle */
    float xmus,    /* I: cosine of solar zenith angle */
    float xtau,    /* I: molecular optical depth */
    float *xrray   /* O: molecular reflectance, 0.0 to 1.0 */
);

void comptg
(
    int iband,                   /* I: band index (0-based) */
    float xts,                   /* I: solar zenith angle */
    float xtv,                   /* I: observation zenith angle */
    float uoz,                   /* I: total column ozone */
    float uwv,                   /* I: total column water vapor (precipital
                                       water vapor) */
    float pres,                  /* I: surface pressure */
    double ogtransa1[NSR_BANDS], /* I: other gases transmission coeff */
    double ogtransb0[NSR_BANDS], /* I: other gases transmission coeff */
    double ogtransb1[NSR_BANDS], /* I: other gases transmission coeff */
    double wvtransa[NSR_BANDS],  /* I: water vapor transmission coeff */
    double wvtransb[NSR_BANDS],  /* I: water vapor transmission coeff */
    double oztransa[NSR_BANDS],  /* I: ozone transmission coeff */
    float *tgoz,                 /* O: ozone transmission */
    float *tgwv,                 /* O: water vapor transmission */
    float *tgwvhalf,             /* O: water vapor transmission, half content */
    float *tgog                  /* O: other gases transmission */
);

void compsalb
(
    float raot550nm,                 /* I: nearest value of AOT */
    int iband,                       /* I: band index (0-based) */
    float pres,                      /* I: surface pressure */
    float tpres[7],                  /* I: surface pressure table */
    float aot550nm[22],              /* I: AOT look-up table */
    float ***sphalbt,                /* I: spherical albedo table
                                           [NSR_BANDS][7][22] */
    float *satm                      /* O: spherical albedo */
);

int comptrans
(
    float xts,                       /* I: solar zenith */
    float raot550nm,                 /* I: nearest value of AOT */
    int iband,                       /* I: band index (0-based) */
    float pres,                      /* I: surface pressure */
    float tpres[7],                  /* I: surface pressure table */
    float aot550nm[22],              /* I: AOT look-up table */
    float ****transt,                /* I: transmission table
                                           [NSR_BANDS][7][22][22] */
    float xtsstep,                   /* I: solar zenith step value */
    float xtsmin,                    /* I: minimum solar zenith value */
    float tts[22],
    float *xtts                      /* O: downward transmittance */
);

int comproatm
(
    float xts,                       /* I: solar zenith angle (deg) */
    float xtv,                       /* I: observation zenith angle (deg) */
    float xfi,                       /* I: azimuthal difference between sun and
                                           observation (deg) */
    float raot550nm,                 /* I: nearest value of AOT */
    int iband,                       /* I: band index (0-based) */
    float pres,                      /* I: surface pressure */
    float tpres[7],                  /* I: surface pressure table */
    float aot550nm[22],              /* I: AOT look-up table */
    float ****rolutt,                /* I: intrinsic reflectance table
                                           [NSR_BANDS][7][22][8000] */
    float **tsmax,                   /* I: maximum scattering angle table
                                           [20][22] */
    float **tsmin,                   /* I: minimum scattering angle table
                                           [20][22] */
    float **nbfic,                   /* I: communitive number of azimuth angles
                                           [20][22] */
    float **nbfi,                    /* I: number of azimuth angles [20][22] */
    float tts[22],                   /* I: sun angle table */
    int32 indts[22],
    float **ttv,                     /* I: view angle table [20][22] */
    float xtsstep,                   /* I: solar zenith step value */
    float xtsmin,                    /* I: minimum solar zenith value */
    float xtvstep,                   /* I: observation step value */
    float xtvmin,                    /* I: minimum observation value */
    float *roatm                     /* O: atmospheric reflectance */
);

int readluts
(
    float **tsmax,              /* O: maximum scattering angle table [20][22] */
    float **tsmin,              /* O: minimum scattering angle table [20][22] */
    float **ttv,                /* O: view angle table [20][22] */
    float tts[22],              /* O: sun angle table */
    float **nbfic,              /* O: communitive number of azimuth angles
                                      [20][22] */
    float **nbfi,               /* O: number of azimuth angles [20][22] */
    int32 indts[22],            /* O: */
    float ****rolutt,           /* O: intrinsic reflectance table
                                      [NSR_BANDS][7][22][8000] */
    float ****transt,           /* O: transmission table
                                      [NSR_BANDS][7][22][22] */
    float ***sphalbt,           /* O: spherical albedo table
                                      [NSR_BANDS][7][22] */
    float xtsstep,              /* I: solar zenith step value */
    float xtsmin,               /* I: minimum solar zenith value */
    char anglehdf[STR_SIZE],    /* I: angle HDF filename */
    char intrefnm[STR_SIZE],    /* I: intrinsic reflectance filename */
    char transmnm[STR_SIZE],    /* I: transmission filename */
    char spheranm[STR_SIZE]     /* I: spherical albedo filename */
);

int subaeroret
(
    int iband1,                      /* I: band 1 index (0-based) */
    int iband3,                      /* I: band 3 index (0-based) */
    float xts,                       /* I: solar zenith angle (deg) */
    float xtv,                       /* I: observation zenith angle (deg) */
    float xfi,                       /* I: azimuthal difference between sun and
                                           observation (deg) */
    float pres,                      /* I: surface pressure */
    float uoz,                       /* I: total column ozone */
    float uwv,                       /* I: total column water vapor (precipital
                                           water vapor) */
    float erelc[NSR_BANDS],          /* I: band ratio variable */
    float troatm[NSR_BANDS],         /* I: atmospheric reflectance table */
    float tpres[7],                  /* I: surface pressure table */
    float aot550nm[22],              /* I: AOT look-up table */
    float ****rolutt,                /* I: intrinsic reflectance table
                                           [NSR_BANDS][7][22][8000] */
    float ****transt,                /* I: transmission table
                                           [NSR_BANDS][7][22][22] */
    float xtsstep,                   /* I: solar zenith step value */
    float xtsmin,                    /* I: minimum solar zenith value */
    float xtvstep,                   /* I: observation step value */
    float xtvmin,                    /* I: minimum observation value */
    float ***sphalbt,                /* I: spherical albedo table
                                           [NSR_BANDS][7][22] */
    float **tsmax,                   /* I: maximum scattering angle table
                                           [20][22] */
    float **tsmin,                   /* I: minimum scattering angle table
                                           [20][22] */
    float **nbfic,                   /* I: communitive number of azimuth angles
                                           [20][22] */
    float **nbfi,                    /* I: number of azimuth anglesi [20][22] */
    float tts[22],                   /* I: sun angle table */
    int32 indts[22],
    float **ttv,                     /* I: [20][22] */
    float tauray[NSR_BANDS],         /* I: molecular optical thickness coeff */
    double ogtransa1[NSR_BANDS],     /* I: other gases transmission coeff */
    double ogtransb0[NSR_BANDS],     /* I: other gases transmission coeff */
    double ogtransb1[NSR_BANDS],     /* I: other gases transmission coeff */
    double wvtransa[NSR_BANDS],      /* I: water vapor transmission coeff */
    double wvtransb[NSR_BANDS],      /* I: water vapor transmission coeff */
    double oztransa[NSR_BANDS],      /* I: ozone transmission coeff */
    float *raot,                     /* O: AOT reflectance */
    float *residual                  /* O: model residual */
);

#endif