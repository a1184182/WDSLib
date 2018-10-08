/*
**   EPANET2.H
**
** C/C++ header file for EPANET Programmers Toolkit
**
** Last updated on 3/1/01
*/

#ifndef EPANET2_H
#define EPANET2_H

/* These are codes used by the DLL functions */
#define EN_ELEVATION    0    /* Node parameters */
#define EN_BASEDEMAND   1
#define EN_PATTERN      2
#define EN_EMITTER      3
#define EN_INITQUAL     4
#define EN_SOURCEQUAL   5
#define EN_SOURCEPAT    6
#define EN_SOURCETYPE   7
#define EN_TANKLEVEL    8
#define EN_DEMAND       9
#define EN_HEAD         10
#define EN_PRESSURE     11
#define EN_QUALITY      12
#define EN_SOURCEMASS   13

#define EN_DIAMETER     0    /* Link parameters */
#define EN_LENGTH       1
#define EN_ROUGHNESS    2
#define EN_MINORLOSS    3
#define EN_INITSTATUS   4
#define EN_INITSETTING  5
#define EN_KBULK        6
#define EN_KWALL        7
#define EN_FLOW         8
#define EN_VELOCITY     9
#define EN_HEADLOSS     10
#define EN_STATUS       11
#define EN_SETTING      12
#define EN_ENERGY       13

#define EN_DURATION     0    /* Time parameters */
#define EN_HYDSTEP      1
#define EN_QUALSTEP     2
#define EN_PATTERNSTEP  3
#define EN_PATTERNSTART 4
#define EN_REPORTSTEP   5
#define EN_REPORTSTART  6
#define EN_RULESTEP     7
#define EN_STATISTIC    8
#define EN_PERIODS      9

#define EN_NODECOUNT    0    /* Component counts */
#define EN_TANKCOUNT    1
#define EN_LINKCOUNT    2
#define EN_PATCOUNT     3
#define EN_CURVECOUNT   4
#define EN_CONTROLCOUNT 5

#define EN_JUNCTION     0    /* Node types */
#define EN_RESERVOIR    1
#define EN_TANK         2

#define EN_CVPIPE       0    /* Link types */
#define EN_PIPE         1
#define EN_PUMP         2
#define EN_PRV          3
#define EN_PSV          4
#define EN_PBV          5
#define EN_FCV          6
#define EN_TCV          7
#define EN_GPV          8

#define EN_NONE         0    /* Quality analysis types */
#define EN_CHEM         1
#define EN_AGE          2
#define EN_TRACE        3

#define EN_CONCEN       0    /* Source quality types */
#define EN_MASS         1
#define EN_SETPOINT     2
#define EN_FLOWPACED    3

#define EN_CFS          0    /* Flow units types */
#define EN_GPM          1
#define EN_MGD          2
#define EN_IMGD         3
#define EN_AFD          4
#define EN_LPS          5
#define EN_LPM          6
#define EN_MLD          7
#define EN_CMH          8
#define EN_CMD          9

#define EN_TRIALS       0   /* Misc. options */
#define EN_ACCURACY     1
#define EN_TOLERANCE    2
#define EN_EMITEXPON    3
#define EN_DEMANDMULT   4

#define EN_LOWLEVEL     0   /* Control types */
#define EN_HILEVEL      1
#define EN_TIMER        2
#define EN_TIMEOFDAY    3

#define EN_AVERAGE      1   /* Time statistic types.    */
#define EN_MINIMUM      2 
#define EN_MAXIMUM      3
#define EN_RANGE        4

#define EN_NOSAVE       0   /* Save-results-to-file flag */
#define EN_SAVE         1
#define EN_INITFLOW     10  /* Re-initialize flow flag   */


/* These are the external functions that comprise the DLL */

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern 
#endif
#define  __stdcall

EXTERN int    ENepanet(char *, char *, char *, void (*) (char *));
EXTERN int    ENopen(char *, char *, char *);
EXTERN int    ENsaveinpfile(char *);
EXTERN int    ENclose(void);

EXTERN int    ENsolveH(void);
EXTERN int    ENsaveH(void);
EXTERN int    ENopenH(void);
EXTERN int    ENinitH(int);
EXTERN int    ENrunH(long *);
EXTERN int    ENnextH(long *);
EXTERN int    ENcloseH(void);
EXTERN int    ENsavehydfile(char *);
EXTERN int    ENusehydfile(char *);

EXTERN int    ENsolveQ(void);
EXTERN int    ENopenQ(void);
EXTERN int    ENinitQ(int);
EXTERN int    ENrunQ(long *);
EXTERN int    ENnextQ(long *);
EXTERN int    ENstepQ(long *);
EXTERN int    ENcloseQ(void);

EXTERN int    ENwriteline(char *);
EXTERN int    ENreport(void);
EXTERN int    ENresetreport(void);
EXTERN int    ENsetreport(char *);

EXTERN int    ENgetcontrol(int, int *, int *, float *,
                      int *, float *);
EXTERN int    ENgetcount(int, int *);
EXTERN int    ENgetoption(int, float *);
EXTERN int    ENgettimeparam(int, long *);
EXTERN int    ENgetflowunits(int *);
EXTERN int    ENgethdlss(int *);
EXTERN int    ENgetpatternindex(char *, int *);
EXTERN int    ENgetpatternid(int, char *);
EXTERN int    ENgetpatternlen(int, int *);
EXTERN int    ENgetpatternvalue(int, int, float *);
EXTERN int    ENgetqualtype(int *, int *);
EXTERN int    ENgeterror(int, char *, int);

EXTERN int    ENgetnodeindex(char *, int *);
EXTERN int    ENgetnodeid(int, char *);
EXTERN int    ENgetnodetype(int, int *);
EXTERN int    ENgetnodevalue(int, int, double *);

EXTERN int    ENgetlinkindex(char *, int *);
EXTERN int    ENgetlinkid(int, char *);
EXTERN int    ENgetlinktype(int, int *);
EXTERN int    ENgetlinknodes(int, int *, int *);
EXTERN int    ENgetlinkvalue(int, int, double *);

EXTERN int    ENgetversion(int *);

EXTERN int    ENsetcontrol(int, int, int, float, int, float);
EXTERN int    ENsetnodevalue(int, int, double);
EXTERN int    ENsetlinkvalue(int, int, double);
EXTERN int    ENsetpattern(int, float *, int);
EXTERN int    ENsetpatternvalue(int, int, float);
EXTERN int    ENsettimeparam(int, long);
EXTERN int    ENsetoption(int, double);
EXTERN int    ENsetstatusreport(int);
EXTERN int    ENsetqualtype(int, char *, char *, char *);

#endif
