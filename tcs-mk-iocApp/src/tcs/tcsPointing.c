/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsPointing.c
*
*   FUNCTION NAME(S)
*   tcsModelInit - Kernel initialization
*   tcsSecProcess - Secondary initialization process
*   tcsModel - Telescope model process
*   tcsSlowProcess - Slow pointing loop process
*   tcsEMediumLoop - Medium pointing EPICS process
*   tcsMediumLoop - Medium pointing loop
*   tcsEFastLoop - Fast pointing EPICS process
*   tcsFastLoop - Fast pointing loop
*   tcsUpdateAstCtx - Update astrometric library context
*   tcsESolsysLoop - Medium fast pointing EPICS process
*   tcsSolsysLoop - Medium fast pointing loop
*   tcsEMedFastLoop - Medium fast pointing EPICS process
*   tcsMedFastLoop - Medium fast pointing loop
*   tcsGetDiffTrack - Fetch and format differential tracking parameters
*   tcsGetTrack - Fast upstream transformation
*   tcsGetMountAzEl - Fetch demand az and el from global database
*   tcsGetTelescopeRADec - compute and return RA/Dec of rotator axis
*   tcsGetTemperature - Fetch temperature used in refraction calculations
*   tcsNewConfig - Set new configuration
*   tcsInitSource - Set source and kernel parameters on startup
*   tcsTelConfig - Set telescope configuration
*   tcsDriveMCS - Drive mount subsystem
*   tcsDriveCRS - Drive Cass rotator subsystem
*   tcsDriveECS - Drive enclosure subsystem
*   tcsDriveM2S - Drive M2 subsystem
*   tcsDriveAGS - Drive A & G subsystem
*   tcsDriveAOS - Drive AO subsystem
*   tcsDriveGG  - Drive one of the four generic guiders
*   tcsNullInit - Null EPICS record initialization routine
*   tcsGetAoprms - Fetch apparent to observed parameters
*   tcsGetTrackid - Fetch current track id
*   tcsSetTrackid - Sets a new track id
*   tcsGetTrack - Fetch current track id
*   tcsGetFrame - Get current tracking frame
*   tcsGetIaa - Get current instrument alignment angle
*   tcsGetPFilt - Fetch current pointing filters
*   tcsGetTFilt - Fetch current target filters
*   tcsGetTarget - Fetch current target
*   tcsGetImagePos - Fetch indvidual pointing origin
*   tcsGetPO   - Fetch total pointing origin
*   tcsGetChop - Fetch chop parameters
*   tcsGetGuide - Fetch guide parameters
*   tcsGetBaseOffset - Fetch offset from base
*   tcsGetRotConfig - Fetch rotator configuration
*   tcsGetPlanet - Fetch planet configuration
*   tcsGetOrbit - Fetch orbit configuration
*   tcsGetTelParams - Fetch telescope parameters
*   tcsGetCoord - Get current tracking coordinates
*   tcsGetObs - Get observatory parameters
*   tcsAbsorbOffsets - Absorb offsets into source positions
*   tcsGetGSAOIDistortion - return GSAOI distortion coeffs
*   tcsSetGSAOIDistortion - set optics distortion coefficients when AO in use
*   tcsSetOffsets - Set source position offsets
*   tcsAbsorbPoOffsets - Absorb offsets into pointing origins
*   tcsSetPoOffsets - Set pointing origin offsets
*   tcsSetSadParams - update SAD items when planet or orbit commands are given
*   tcsIncrOffsets - Increment offsets
*   tcsIncrPoOffsets - Increment offsets
*   tcsNod - Set nod state
*   tcsLimitTimes - Compute times to various limits
*   tcsTestOffLoad - checks if data is good of mount offload
*   tcsUpdCtx - Write AST context array
*   tcsWritePointLog - Write pointing observation log array
*   tcsKernelEnd - Completes fast loop processing
*   tcsKernelStatus - Output kernel data to EPICS
*   tcsKernelGGStatus - Output kernel data of gneric guiders to EPICS
*   tcsDump - Write global parameters to console
*
*/
/*
 * $Log: tcsPointing.c,v $
 * Revision 1.103  2015/06/10 10:28:03  cjm
 * Fix for probe glitches
 *
 * Revision 1.102  2014/10/01 16:30:59  cjm
 * Add extra messages for open and close of debug file
 *
 * Revision 1.101  2014/09/18 15:05:31  cjm
 * Changes to support time to limit for enclosure in basic mode
 *
 * Revision 1.100  2013/09/11 15:39:45  cjm
 * Modify debug output
 *
 * Revision 1.99  2013/05/20 12:21:30  cjm
 * Add tcsGetTelescopeRADec
 *
 * Revision 1.98  2012/06/01 16:10:59  cjm
 * Remove some redundant debug statemetns
 *
 * Revision 1.97  2012/05/08 09:46:17  cjm
 * Add set and get of P1LGSMode
 *
 * Revision 1.96  2011/09/20 14:05:20  cjm
 * Rework of ephemeris support
 *
 * Revision 1.95  2011/05/04 13:43:05  cjm
 * Merge AOM limit changes with new debug and ODGW changes
 *
 * Revision 1.93  2011/02/10 16:03:11  cjm
 * Move check for tick to end of fast loop
 *
 * Revision 1.92  2011/01/26 15:13:24  cjm
 * Set ODGW center from DriveGG routine
 *
 * Revision 1.91  2010/11/29 14:15:38  cjm
 * Fix WCS test routine
 *
 * Revision 1.90  2010/06/08 15:09:04  cjm
 * Add GSAOI port number in call to tcsProbeTcs2Odgw
 *
 * Revision 1.89  2010/06/03 15:40:48  cjm
 * Add support for GSAOI filter offsets
 *
 * Revision 1.88  2010/01/22 09:14:23  cjm
 * fix typo that was copying G4 global data to g3 local variables
 *
 * Revision 1.87  2009/12/01 13:41:23  cjm
 * Implement Odgw2Tcs transformations
 *
 * Revision 1.86  2009/11/02 16:36:23  cjm
 * Add guiding correction to rotator demands
 *
 * Revision 1.85  2009/10/30 17:20:55  cjm
 * Output target arrays for generic guiders
 *
 * Revision 1.84  2009/05/20 10:34:14  cjm
 * Use real rotator limits when determining wrap not the default +/-270
 *
 * Revision 1.83  2008/10/07 12:27:19  cjm
 * Improve validation of times to limits
 *
 * Revision 1.82  2008/05/01 15:20:13  cjm
 * Code to compute the limits for the A&G rotary tables
 *
 * Revision 1.81  2007/12/20 17:10:32  cjm
 * Fix incorrect comment
 *
 * Revision 1.80  2007/12/19 13:40:05  cjm
 * Add code to handle offsets for new generic guiders
 *
 * Revision 1.79  2007/12/18 16:41:22  cjm
 * Fix indices for NGS probes 3 & 4
 *
 * Revision 1.78  2007/12/18 10:16:03  cjm
 * Expand and modify to handle new guiders
 *
 * Revision 1.77  2007/01/09 14:06:05  cjm
 * Add SetSadParams and handle new orbit commands
 *
 * Revision 1.76  2006/11/24 10:26:00  cjm
 * Make probes go to demand position immediately even in presence of instrument offsets
 *
 * Revision 1.75  2006/04/21 10:53:24  cjm
 * Output pointing model data
 *
 * Revision 1.74  2005/12/23 14:40:15  cjm
 * Update track rates from ephemeris data
 *
 * Revision 1.73  2005/12/20 15:01:18  cjm
 * New call sequence for tcsOpticsProbeXYZ
 *
 * Revision 1.72  2005/12/15 09:35:51  cjm
 * New call sequence for tcsEphemerisTarget
 *
 * Revision 1.71  2005/10/21 15:40:42  cjm
 * Provide health feedback from SolsysLoop
 *
 *
 * Revision 1.68  2004/08/05 09:50:48  cjm
 * New routine tcsGetDiffTrack for displaying current differential track parameters
 *
 * Revision 1.67  2004/04/08 10:57:27  cjm
 * Add routine to output the nod/chop states
 *
 * Revision 1.66  2004/03/24 14:51:20  cjm
 * Dave's changes for tracking the demand rather than current rotator angle
 *
 * Revision 1.65  2003/05/16 13:24:25  dlt
 * Correct incrementing offsets across RA 0
 *
 * Revision 1.64  2003/04/10 10:21:09  dlt
 * Store chop mode in kernel
 *
 * Revision 1.63  2003/03/13 01:22:58  cjm
 * Send repeated move commands if ECS stops prematurely
 *
 * Revision 1.62  2003/01/13 16:03:19  dlt
 * Correct chop targets used for OTM calculation after a slew
 *
 * Revision 1.61  2002/11/23 12:37:01  cjm
 * Input x, y offsets for Altair
 *
 * Revision 1.60  2002/11/18 20:34:47  cjm
 * Add code to support the various focus shifts introduced by Altair
 *
 * Revision 1.59  2002/11/08 12:04:13  cjm
 * Handle Altair distortion when in the beam
 *
 * Revision 1.58  2002/10/22 20:37:45  dlt
 * Implement filter 1 for pointing origins and fix filter flag resetting
 *
 * Revision 1.57  2002/05/21 21:28:51  cjm
 * Add tcsTestOffLoad to check for good data from SCS
 *
 * Revision 1.56  2001/12/03 08:52:48  dlt
 * Implement rotator nod correction for all frames
 *
 * Revision 1.55  2001/11/26 22:24:12  dlt
 * Subtract absorbed guide star offsets from other chop state offsets
 *
 * Revision 1.54  2001/11/26 21:49:57  dlt
 * Correct rotator angle when nodding
 *
 * Revision 1.53  2001/11/25 07:07:56  dlt
 * Correct PWFS limit in position messages
 *
 * Revision 1.52  2001/10/24 22:53:39  dlt
 * Display reason for inPosition false
 *
 * Revision 1.51  2001/10/05 09:11:34  cjm
 * Clip demands afer transforming to oiwfs frame
 *
 * Revision 1.50  2001/09/27 09:41:40  cjm
 * In kernelEnd set a flag to show nodState has changed
 *
 * Revision 1.49  2001/05/24 10:30:08  cjm
 * Remove mosub record references and fix uninitialised variables in the handling of the wfs
 *
 * Revision 1.48  2001/03/12 15:19:08  cjm
 * Output predicted astigmatism for PWFS1
 *
 * Revision 1.47  2001/02/22 13:27:10  dlt
 * Correct problems with times to limits in South
 *
 * Revision 1.46  2001/02/05 01:35:17  cjm
 * Remove scaling of A&G demands, x/y demands are now in the focal plane
 *
 * Revision 1.45  2001/01/16 09:30:52  dlt
 * Make B/C relative to net A targets and remove B/C offset
 *
 * Revision 1.44  2001/01/15 13:38:59  dlt
 * Remove erronious fix to guide star target absorb
 *
 * Revision 1.43  2001/01/15 11:37:17  dlt
 * New handset interface
 *
 * Revision 1.42  2000/12/05 13:57:43  dlt
 * Revised pointing model code
 *
 * Revision 1.41  2000/11/23 16:24:55  cjm
 * Set inPosition flag for P2/AO depending on whether AO fold is deployed
 *
 * Revision 1.40  2000/10/11 05:34:40  cjm
 * Remove rotation of coma and astigmatism terms
 *
 * Revision 1.39  2000/10/08 20:16:28  dlt
 * Revised probe guiding algorithm
 *
 * Revision 1.38  2000/08/18 16:04:51  cjm
 * Remove dummy code from DriveAOS and replace with the real thing
 *
 * Revision 1.37  2000/08/07 07:58:15  cjm
 * Remove -90 rotation from demands to the A&G
 *
 * Revision 1.36  2000/07/20 03:00:53  dlt
 * Upgrade to latest tptlib
 *
 * Revision 1.35  2000/07/19 00:09:39  dlt
 * Implement new pointing model implementation
 *
 * Revision 1.34  2000/06/19 10:23:42  cjm
 * Fix sign of m2_scan_y before sending to SCS
 *
 * Revision 1.33  2000/06/19 08:34:36  dlt
 * Correction to target C handset code
 *
 * Revision 1.32  2000/05/09 08:11:46  cjm
 * Add routine tcsGetPO and output current nod state as a string in KernelEnd
 *
 * Revision 1.31  2000/04/20 09:49:28  dlt
 * Implement guiding of wfs probes
 *
 * Revision 1.30  2000/04/13 08:31:54  dlt
 * Add SAD records for WFS targets & offsets
 *
 * Revision 1.29  1999/12/16 17:24:12  cjm
 * Use xdemand, ydemand rather than g_x, g_y when computing Zernikes
 *
 * Revision 1.28  1999/11/28 12:47:52  cjm
 * Add fudge angles for P1 and P2 to overcome problems of adjusting the probe zero points by large amounts
 *
 * Revision 1.27  1999/11/21 00:43:07  cjm
 * Allow input from current position of rotator as well as from the array of time stamped positions
 *
 * Revision 1.26  1999/07/23 02:31:12  ajf
 * ajf: Took out azimuth scale factor. Now in MCS virtual encoder.
 *
 * Revision 1.25  1999/07/10 03:54:05  cjm
 * *** empty log message ***
 *
 * Revision 1.24  1999/05/31 11:29:28  dlt
 * Fix another bug in the azimuth wrap determination
 *
 * Revision 1.23  1999/05/29 08:12:27  dlt
 * Move tf to genertic parameters
 *
 * Revision 1.22  1999/05/24 04:06:25  cjm
 * Clip maximum elevation demand to 90 degs.
 *
 * Revision 1.21  1999/05/17 19:12:53  cjm
 * Output M2 data to TCS records in M2 units rather than user units
 *
 * Revision 1.20  1999/05/12 06:10:56  cjm
 * Ensure carousel az demands are always in range 0 to 360.0
 *
 * Revision 1.19  1999/05/11 00:45:00  cjm
 * Add temporary scaling factor of 16.8 arcsec/rev in azimuth plus new routine to read in generic pointing parameters
 *
 * Revision 1.18  1999/03/24 15:02:04  epics
 * Repair x/y demands to oiwfs after changes to support scaling of pwfs demands
 *
 * Revision 1.17  1999/03/22 22:03:34  dlt
 * Correct setting of telescope struture in InitSource and avoid divide by zero at zenith in upstream
 *
 * Revision 1.16  1999/03/18 03:24:41  dlt
 * Do tangent plane conversion properly for incremental offsets
 *
 * Revision 1.15  1999/03/16 02:32:45  dlt
 * Correction to comments in tcsModel
 *
 * Revision 1.14  1999/03/16 01:02:49  dlt
 * Remove all but CA & CE from local pointing model
 *
 * Revision 1.13  1999/02/27 05:35:15  cjm
 * As a temporary measure, scale the x,y demands for the probes. This should really go in the A&G
 *
 * Revision 1.12  1999/02/08 10:41:02  cjm
 * Updates to allow for a gensub rather than mosub to run tcsEfastLoop plus handle rotator positions in degs. rhater than rads
 *
 * Revision 1.11  1999/01/22 03:18:24  dlt
 * Do tangent plane conversion in tcsIncrOffset
 *
 * Revision 1.10  1999/01/21 20:56:38  cjm
 * Output demand x,y,z on separate links for display by engineering screens
 *
 * Revision 1.9  1999/01/21 01:00:04  dlt
 * remove unused simulate flags
 *
 * Revision 1.8  1999/01/15 19:43:02  cjm
 * Add tilt & focus scale to stream of demands in driveM2S
 *
 * Revision 1.7  1998/12/18 19:49:07  dlt
 * Complete implementation of otm calculation after slew
 *
 * Revision 1.6  1998/12/10 17:07:03  epics
 * temporary fix for incorrect OTMs after a slew
 *
 * Revision 1.5  1998/12/07 16:45:03  epics
 * Disable further 20Hz processing if fast loop does not run
 *
 * Revision 1.4  1998/12/07 11:27:01  epics
 * Send kernel target data to SAD
 *
 * Revision 1.3  1998/11/19 21:20:04  cjm
 * Input/output in degrees rather than rads to MCS
 *
 * Revision 1.2  1998/11/14 00:15:59  dlt
 * Add IA and IE to pointing model
 *
 * Revision 1.1.1.1  1998/11/08 00:21:06  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.74  1998/10/28 10:01:59  dlt
 * New routine for setting new trackid
 *
 * Revision 1.73  1998/10/26 13:18:27  tcs
 * Modify DriveAGS to allow a focus offset to be applied
 *
 * Revision 1.72  1998/10/20 07:56:34  dlt
 * reunite tcsGetAoprms with its header comments
 *
 * Revision 1.71  1998/07/28 08:46:56  tcs
 * Send only one set of demands to each probe rather than a set for each chop state
 *
 * Revision 1.70  1998/06/30 14:15:24  dlt
 * Print time with timePrint on startup
 *
 * Revision 1.69  1998/05/19 15:47:46  tcs
 * Invert time to limits validity mask
 *
 * Revision 1.68  1998/05/19 13:52:48  cjm
 * Prevent multiple moves to dome & shutters
 *
 * Revision 1.67  1998/05/18 13:24:34  tcs
 * Display airmass limit elevation in all frames & correct width of zenith region
 *
 * Revision 1.66  1998/04/17 13:01:27  tcs
 * Correct conversion of rotator limits to paralactic angle
 *
 * Revision 1.65  1998/04/01 15:34:08  cjm
 * Fix problem with large Z probe demands
 *
 * Revision 1.64  1998/03/24 14:59:49  cjm
 * Prevent blind spot limits propagating inapplicable severities
 *
 * Revision 1.63  1998/03/23 14:38:08  cjm
 * Add support for min scatter/vibration in tcsDrivesECS
 *
 * Revision 1.62  1998/02/16 16:58:02  tcs
 * implement internal in position flag
 *
 * Revision 1.61  1998/02/16 09:49:03  tcs
 * Revised applyC logic
 *
 * Revision 1.60  1998/01/20 12:17:03  cjm
 * Extra comments for tcsModel routine
 *
 * Revision 1.59  1997/12/15 11:42:05  tcs
 * Tide up comments
 *
 * Revision 1.58  1997/12/09 08:23:50  cjm
 * Read optics contributions to ca,ce into fast loop
 *
 * Revision 1.57  1997/12/08 10:02:52  cjm
 * Modify DriveAGS to output Zernike terms
 *
 * Revision 1.56  1997/12/01 09:09:58  cjm
 * Use new tcsOpticsScaleThrow routine
 *
 * Revision 1.55  1997/11/21 14:59:25  cjm
 * Add diagnostics to test software timing requirements
 *
 * Revision 1.54  1997/11/19 10:11:19  tcs
 * Change filter catchup to short circuit
 *
 * Revision 1.53  1997/11/18 08:25:52  cjm
 * Fix bug in scaling of M2 focus demand
 *
 * Revision 1.52  1997/11/17 13:32:09  tcs
 * Reverse rotator angle & set mount diff track to zero on initialization
 *
 * Revision 1.51  1997/11/14 15:59:41  tcs
 * Revised astRot arguments
 *
 * Revision 1.50  1997/11/14 10:42:43  tcs
 * Send chop A to A & G by default
 *
 * Revision 1.49  1997/11/13 13:23:37  tcs
 * Revised guide star scheme
 *
 * Revision 1.48  1997/11/05 16:46:24  cjm
 * Add calculation of dome vignetting to tcsDriveECS
 *
 * Revision 1.47  1997/11/05 11:36:37  tcs
 * Implement chop relative to IPA
 *
 * Revision 1.46  1997/10/31 14:46:29  tcs
 * Add instrument angle concept
 *
 * Revision 1.45  1997/10/31 12:35:09  pbt
 * Initial AO drive routine added : currently just outputs zero
 *
 * Revision 1.44  1997/10/31 09:32:38  tcs
 * Revise filter defaults
 *
 * Revision 1.43  1997/10/15 15:29:29  tcs
 * Add user offset to PA used for PA calculation
 *
 * Revision 1.42  1997/10/09 12:51:05  tcs
 * Drive SAD from kernel instead of CAD
 *
 * Revision 1.41  1997/10/09 09:52:38  tcs
 * Fix OTMs on/near horizon & add focal length to pointing log array
 *
 * Revision 1.40  1997/10/06 10:09:15  tcs
 * Correct argument order in ptrani
 *
 * Revision 1.39  1997/10/03 15:06:56  tcs
 * Fix rotator position for frame != mount
 *
 * Revision 1.38  1997/10/02 14:24:27  tcs
 * Changes to pointing obs array
 *
 * Revision 1.37  1997/09/30 13:58:35  tcs
 * Correction to blind-spot times
 *
 * Revision 1.36  1997/09/23 11:38:40  tcs
 * Use double version of slaRange
 *
 * Revision 1.35  1997/09/23 09:38:02  tcs
 * Add support for absorbing & zeroing offsets
 *
 * Revision 1.34  1997/09/16 11:07:57  cjm
 * Mods to tcsDriveECS to support basic mode
 *
 * Revision 1.33  1997/09/12 14:59:18  tcs
 * Pointing origin handset
 *
 * Revision 1.32  1997/09/12 13:06:49  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.31  1997/09/12 12:58:24  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.30  1997/09/10 14:52:41  tcs
 * Pointing log always logs FK5
 *
 * Revision 1.29  1997/09/08 14:01:28  tcs
 * Change name of point log routine to avoid clash with CAD routine
 *
 * Revision 1.28  1997/09/03 10:07:05  tcs
 * Change M2 units to tip/tilt
 *
 * Revision 1.27  1997/08/21 10:42:34  tcs
 * Change M2 units to arcsec on sky
 *
 * Revision 1.26  1997/08/13 10:24:38  tcs
 * Add guiding adjustments to ca/ce
 *
 * Revision 1.25  1997/08/08 12:45:59  tcs
 * Tidy up point parameter inputs
 *
 * Revision 1.24  1997/07/15 13:38:31  cjm
 * Add control of top & bottom shutter in ECSDrives
 *
 * Revision 1.23  1997/07/11 08:17:41  tcs
 * Fetch MCS and RCS limits from epics links
 *
 * Revision 1.22  1997/07/10 12:34:51  tcs
 * Implement times to limits
 *
 * Revision 1.21  1997/06/26 10:10:13  tcs
 * Update orbits at 0.1Hz
 *
 * Revision 1.20  1997/06/25 12:57:23  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.19  1997/06/19 12:12:30  tcs
 * Improve rotator prediction
 *
 * Revision 1.18  1997/06/11 15:14:21  tcs
 * Implement wavelength CADs
 *
 * Revision 1.17  1997/06/09 15:53:58  tcs
 * Move tcsLimits from tcsPointing
 *
 * Revision 1.16  1997/06/02 09:58:26  tcs
 * Add slew CAD
 *
 * Revision 1.15  1997/05/16 12:20:07  tcs
 * Change cosys to frame
 *
 * Revision 1.14  1997/05/15 14:15:09  tcs
 * Move differential tracking to separate CAD
 *
 * Revision 1.13  1997/05/08 15:18:21  tcs
 * Remove AZEL_MNT from kernel & initialize in FK5
 *
 * Revision 1.12  1997/05/07 12:47:45  tcs
 * Tidy up fiter code
 *
 * Revision 1.10  1997/05/02 13:22:30  tcs
 * More zenith improvements
 *
 * Revision 1.9  1997/04/30 10:37:53  tcs
 * Revised zenith avoidance
 *
 * Revision 1.8  1997/04/28 14:06:09  tcs
 * Add default values for MCS and RCS
 *
 * Revision 1.7  1997/04/24 13:26:11  tcs
 * Make no epoch or pm imply an epoch of now
 *
 * Revision 1.6  1997/04/22 15:18:58  tcs
 * Initialize kernel in topocentric Az/El
 *
 * Revision 1.5  1997/04/16 11:55:43  tcs
 * Move tube flexure to telescope-specific pointing model routines
 *
 * Revision 1.4  1997/04/09 13:28:39  tcs
 * Fix zenith bug and make mount az/el pre-tube flexure
 *
 * Revision 1.3  1997/04/03 14:34:14  cjm
 * Mods to driveM2 to agree with TCS/SCS ICD
 *
 * Revision 1.2  1997/03/24 15:17:22  cjm
 * Move chop routines to tcsOptics
 *
 * Revision 1.1  1997/02/10 17:10:51  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.99  1997/02/07 15:16:45  tcs
 * Allow nodding between any frames & make filters independent of
 * fast loop rate
 *
 * Revision 1.98  1997/02/06 13:29:03  tcs
 * Make catchup flag override grab & maxv
 *
 * Revision 1.97  1997/02/05 11:01:36  tcs
 * Set track ID and filter catchups in Nod command
 *
 * Revision 1.96  1997/02/03 16:40:56  tcs
 * Enable nodding while relative chopping
 *
 * Revision 1.95  1997/02/03 13:14:26  tcs
 * Correct sign of nod adjustments
 *
 * Revision 1.94  1997/01/31 14:18:55  tcs
 * Correct source C offset in handset
 *
 * Revision 1.93  1997/01/30 17:04:31  tcs
 * Chop throw from un-offset source A target
 *
 * Revision 1.92  1997/01/30 15:24:37  tcs
 * Correct chopping in Az/El frames
 *
 * Revision 1.91  1997/01/28 10:36:18  tcs
 * Corrections to differential tracking
 *
 * Revision 1.90  1997/01/24 14:25:19  tcs
 * Move tracking frame to separate CAD
 *
 * Revision 1.89  1997/01/23 10:46:47  tcs
 * Kernel support for relative chopping
 *
 * Revision 1.88  1997/01/21 10:31:23  tcs
 * Correct pointing origin filter
 *
 * Revision 1.87  1997/01/21 08:15:49  cjm
 * Remove some diagnostics
 *
 * Revision 1.86  1997/01/17 18:17:34  cjm
 * Open loop corrections to M2 and focus demands for probes
 *
 * Revision 1.85  1997/01/15 16:43:54  tcs
 * Put pointing origins back into ast array
 *
 * Revision 1.84  1997/01/14 17:37:01  pbt
 * Add tcsGetTrackid function
 *
 * Revision 1.82  1997/01/14 16:34:12  cjm
 * Add new functions to fetch az,el and temperature
 *
 * Revision 1.81  1997/01/10 15:22:12  tcs
 * Add nod support
 *
 * Revision 1.80  1997/01/09 21:41:07  cjm
 * Send default positions to probes when appropriate
 *
 * Revision 1.79  1997/01/08 09:37:05  cjm
 * Add debug statements
 *
 * Revision 1.78  1997/01/07 11:42:38  tcs
 * Correct use of INDENT
 *
 * Revision 1.77  1997/01/06 11:31:01  tcs
 * Restore reference refraction coefficients for each VT
 *
 * Revision 1.76  1997/01/03 11:21:44  tcs
 * Update fast loop and ptran
 *
 * Revision 1.75  1996/12/20 14:43:06  tcs
 * Remove guide probe flexure terms
 *
 * Revision 1.74  1996/12/18 11:17:35  tcs
 * Cleanup plus offset routines
 *
 * Revision 1.73  1996/12/13 15:07:47  tcs
 * Remove zerotime argument from tcsCtCoco
 *
 * Revision 1.72  1996/12/13 10:07:53  tcs
 * Rename tcs.h to tcsPointing.h
 *
 * Revision 1.71  1996/12/12 16:57:09  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.70  1996/12/09 08:15:12  cjm
 * Add tcsGetAoprms, tcsGetPfilt and tcsGetTelParams
 *
 * Revision 1.69  1996/12/06 14:09:56  tcs
 * Move all rotator calculations to fast loop
 *
 * Revision 1.68  1996/12/06 09:46:35  tcs
 * Correct copying of offsets from kernel to TCB
 *
 * Revision 1.67  1996/12/05 13:13:22  tcs
 * Implement filter catchup and initialize closed
 *
 * Revision 1.66  1996/12/03 16:55:41  tcs
 * Implement filters and reorganise fast loop
 *
 * Revision 1.65  1996/12/03 11:32:14  tcs
 * Interpolate rotator zero point
 *
 * Revision 1.64  1996/12/02 11:14:04  tcs
 * Implement rotator tracking frame
 *
 * Revision 1.63  1996/11/26 15:29:31  tcs
 * Fetch filter data from configuration
 *
 * Revision 1.62  1996/11/25 12:36:54  pbt
 * Changed demand output routines to use genSub record
 *
 * Revision 1.61  1996/11/25 08:45:29  tcs
 * Remove multiple evaluation of sqrt from fast loop
 *
 * Revision 1.60  1996/11/20 18:08:37  pbt
 * Changed kernel and simulation code to use genSub records
 *
 * Revision 1.59  1996/11/13 14:38:57  tcs
 * Add rotator CAD
 *
 * Revision 1.58  1996/11/11 13:10:05  tcs
 * Modify calling sequence of tcsCtCoco
 *
 * Revision 1.57  1996/11/08 13:37:38  tcs
 * Correct conversions to mount az/el
 *
 * Revision 1.56  1996/11/08 11:57:28  tcs
 * Add display of frame and equinox
 *
 * Revision 1.55  1996/11/07 16:22:13  tcs
 * Compute reference times relative to now in NewConfig
 *
 * Revision 1.54  1996/11/06 14:33:16  tcs
 * Rename NewOffset to NewConfig and remove NewSource
 *
 * Revision 1.53  1996/11/04 11:40:49  tcs
 * Calculate observed to apparent parameters in slow loop
 *
 * Revision 1.52  1996/11/04 08:15:32  cjm
 * Copy targets into kernel in tcsNewOffset
 *
 * Revision 1.51  1996/10/25 11:41:43  tcs
 * Correct fetching of pointing origin offsets
 *
 * Revision 1.50  1996/10/25 09:17:43  cjm
 * Move derotation of probes from A&G to TCS
 *
 * Revision 1.49  1996/10/24 16:11:11  tcs
 * Pointing origin offset commands
 *
 * Revision 1.48  1996/10/24 12:10:47  tcs
 * Add pointing origin commands
 *
 * Revision 1.47  1996/10/23 13:21:06  tcs
 * Implement tangent plane offsets
 *
 * Revision 1.46  1996/10/23 12:12:16  tcs
 * Move offset unit conversion to tcsPointing
 *
 * Revision 1.45  1996/10/21 13:47:11  cjm
 * Add tcsSet/GetChopLimits
 *
 * Revision 1.44  1996/10/08 14:01:37  tcs
 * Add CADs for all 13 VTs & remove guide1 and target
 *
 * Revision 1.43  1996/10/07 07:10:53  cjm
 * Support 13 VTs for both preset and current targets
 *
 * Revision 1.42  1996/10/04 08:08:10  cjm
 * Support tcbdefn command and new telescope types
 *
 * Revision 1.41  1996/09/25 07:38:04  tcs
 * Change chop states to ABC (comments only)
 *
 * Revision 1.40  1996/09/13 14:13:02  tcs
 * Avoid attempting to track through the inaccessible region near the zenith
 *
 * Revision 1.39  1996/09/11 13:40:50  tcs
 * Change azimuth wrap limits to -180/+360
 *
 * Revision 1.38  1996/09/10 15:11:37  tcs
 * Rewrite wrap algorithm
 *
 * Revision 1.37  1996/09/09 15:25:14  tcs
 * Honour wrap flags in mount az/el
 *
 * Revision 1.36  1996/09/09 10:39:45  tcs
 * Fix more topo az/el problems plus CR cable wrap bug
 *
 * Revision 1.35  1996/09/06 11:40:56  tcs
 * Improved wrap handling + Al/El coordinate handedness fixed
 *
 * Revision 1.34  1996/09/05 16:43:56  pbt
 * Using new data structures for target TCB data. Get wrap data from TCB.
 *
 * Revision 1.33  1996/08/23 13:07:45  cjm
 * Add initialization of kernel & fix polar motion
 *
 * Revision 1.32  1996/08/01 15:03:28  tcs
 * Delete commented out code
 *
 * Revision 1.31  1996/08/01 14:44:51  cjm
 * Fix error in tcsLimits
 *
 * Revision 1.30  1996/07/31 07:26:43  cjm
 * Addition of guide1 command
 *
 * Revision 1.29  1996/07/30 09:49:41  tcs
 * Correct guide probe positions for non-perp
 *
 * Revision 1.28  1996/07/29 13:39:09  tcs
 * Set guide probe target wavelength
 *
 * Revision 1.27  1996/07/25 12:51:12  cjm
 * Modifications to support data passing via TCBs
 *
 * Revision 1.26  1996/07/24 15:29:16  tcs
 * Clear up cosys confusion
 *
 * Revision 1.25  1996/07/24 13:58:59  tcs
 * Fix wrap bugs
 *
 * Revision 1.24  1996/07/23 15:52:47  tcs
 * Add header comments
 *
 */
/* *INDENT-ON* */


#include <string.h>
#include <epicsStdlib.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <iocsh.h> 
#include <math.h>
#include <epicsMutex.h>
#include <taskwd.h>
#include <epicsThread.h>

#include <dbDefs.h>
#include <alarm.h>
#include <subRecord.h>
#include <genSubRecord.h>
#include <cadRecord.h>

#include <slalib.h>
#include <slamac.h>
#include <timeLib.h>
#include <astLib.h>
#include "tcsConstants.h"
#include "tcsPointing.h"
#include "tcsGlobal.h"
#include "tcsConfig.h"
#include "tcsProbeLib.h"
#include "tcsCotran.h"
#include "tcsOptics.h"
#include "tcsLimits.h"
#include "tcsEcsLib.h"
#include "tcsInPosition.h"
#include "tptlib.h"
#include "tcsCadSupport.h"
#include "tcsEphemeris.h"
#include "tcsGuide.h"

/* Function prototypes for internal routines */
static void target(double, double, FRAMETYPE, double, double, double[2],
                   double[3][3],
                   double[3][3], double[3][3], double[3][3], double[3][3]);
static void probev(double[3], double, double[3], double[3], double[3]);
static void ptran(FRAMETYPE, double, double[3][3], double, double, double,
                  double, double[3], double[3][3], double[3], double[3], 
                  double[3]);
static void ptrani(double[3], FRAMETYPE, double, double, double, 
                   double[3][3], double*, double*);
static void otm(double[3], double[3], double[3], double[3], double[3],
                double[3], double[3][3], double[3][3], int *);
static void PartA(FRAMETYPE, double[2], double[3][3], double, double,
                  double[3][3],
                  double *, double *, double *,
                  double *, double *, double *,
                  double *, double *, double *,
                  double *, double *, double *);
static void PartAv(FRAMETYPE, double, double, double,
                   double[3][3], double, double, double[3][3],
                   double *, double *, double *,
                   double *, double *, double *,
                   double *, double *, double *);

/* These are needed only for formatting the diagnostics */
static void Dd2tf(int ndp, double days, char *sign, long ihmsf[4]);
static void Dr2af(int ndp, double angle, char *sign, long idmsf[4]);
static void Dr2tf(int ndp, double angle, char *sign, long ihmsf[4]);

/* Offset-from-base element used by nodding */
#define NODOB 2

/* Local static variables */
static int CrcsFollowStat = 0;       /* CRCS follow status */
static int P1LGSMode = 0;            /* P1 + LGS mode is disabled */

/* Debug related parameters */
static FILE *dbgfp = NULL;
static int pkdbgwriteflag = 0 ;     /* Print debug info if true */

static int cnt01 = 0;
static int cnt02 = 0;
static int cnt03 = 0;
static int cnt04 = 2;
static int cnt05 = 8;
static int cnt06 = 0;
static int cnt07 = 0;
static int cnt08 = 0;
static int cnt09 = 0;
static int cnt10 = 0;
static int cnt11 = 0;
static int cnt12 = 0;
static int cnt13 = 0;
static int cnt14 = 0;
static double tick0v = 0;
static double dtickv = 0;
static double DtimeSem1, DtimeSem2;
static double ADeltaT;
static double Flt_cnt;
static double FlTime;
static double DTraw;
static double DTick;
static double DtGetTelRD;
static double Traw;      /* Current TAI (clock) */
static double Dmd_cnt;    /* Demand Number */
static double Corr_cnt;   /* Tick Correction Number */
static double Corr_02;   /* Tick Correction Number */
static double Corr_08;   /* Tick Correction Number */

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsModelInit
 *
 *   Purpose:
 *   Intialises the telescope pointing model data structures.
 *
 *   Description:
 *   Calls tptMinit
 *
 *   Invocation:
 *   tcsModelInit()
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      None
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   tptMinit
 *
 *   External variables:
 *   (>)   TcsSemId    (int)    Global memory protection semaphore
 *   (>)   Various tpoint data arrays.
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


void tcsModelInit(void)
{
    int i, j;
    static int dbgLevel = DBG_NONE; /* debug level */

    /*02-14-2018 Ignacio is trying to initiliase this semaphore before iocInit*/
    TcsSemId = epicsMutexMustCreate();
    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsModelInit: Failed to create semaphore TcsSemId");
        return;
    }
  
    /* Rotation matrix, celestial [Az,EL] to nominal mount, and initial value
       for [Az,El] to mount. */
    for ( i = 0; i < 3; i++ ) {
        for ( j = 0; j < 3; j++ ) {
            Ae2nm[i][j] = (  i == j ? 1 : 0 );
            Ae2mt[i][j] = (  i == j ? 1 : 0 );
        }
    }

    /* Set up an empty pointing model */
    if ( tptMinit( MAXTRM, NTROOM, Model, &Nterml, &Ntermx, &Nterms, Coeffn) )
        printf( "tptMinit failed\n" );
    //tcsOpticsInit();
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSecProcess
 *
 *   Purpose:
 *   This routine gets invoked each time the secondary initialization record
 *   gets processed. This routine is expected to get called once the TCS
 *   database is loaded and initialized. It may also get called if a user
 *   wanted to modify any of the quasi-constants of the system whilst the
 *   system was running. In the language of EPICS it will be scanned passively
 *   i.e. it can be executed asynchronously compared with the rest of the TCS
 *   pointing processes.
 *
 *   Description:
 *   Reads the quasi-fixed parameters that affect pointing from EPICS into 
 *   global memory and initializes the time related variables that are updated
 *   by the fast loop so that the slow and medium loops can be run before
 *   the fast loop is started.
 *
 *   Invocation:
 *   tcsSecProcess(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    psub     (genSubRecord *) Pointer to genSub record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *   timeNow         timelib    Reads clock
 *   timeThenR       timelib    Converts time from raw form
 *
 *   External variables:
 *   (>)   TcsSemId  (int)      global memory protection semaphore
 *   (<)   Hm        (double)   site elevation
 *   (<)   Del       (double)   probe-vector spacing
 *   (<)   Sst       (double)   function of LAST
 *   (<)   Cst       (double)   function of LAST
 *   (<)   St        (double)   LAST at next tick
 *   (<)   Tt        (double)   TT at next tick
 *   (<)   Ae2nm     (double[3][3]) Az/El to nominal mount matrix (=identity)
 *
 *   Prior requirements:
 *   tcsApplInit must have been called at least once.
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


long tcsSecProcess( genSubRecord *psub )
{
    double traw;

/* Local copies of global variables. */
    double hm, del, sst, cst, st, tt;

/* fetch all input arguments into local variables */
    hm = *(double *)psub->a;
    del = *(double *)psub->b;

/* Time Service */
    (void) timeNow(&traw);
    (void) timeThenR(traw, LAST, &st);
    (void) timeThenR(traw, TT, &tt);

/* Functions of LAST */
    sst = sin(st);
    cst = cos(st);

    if (TcsSemId) {
       epicsMutexLock(TcsSemId);
       Hm = hm;
       Del = del;
       Sst = sst;
       Cst = cst;
       St = st;
       Tt = tt;
       epicsMutexUnlock(TcsSemId);
    }	
    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsModelAdjust
 *
 *   Purpose:
 *   Sets the adjustment to pointing model parameters.
 *
 *   Description:
 *   The pointing model adjustments are copied into global memory.
 *
 *   Invocation:
 *   tcsModelAdjust(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to gensub record
 *
 *   Epics inputs:
 *
 *   a => horizontal collimation (rads)
 *   b => vertical collimation (rads)
 *   c => Index error in azimuth (rads)
 * 
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (<)   Ca_delta  (double)    horizontal collimation
 *   (<)   Ce_delta  (double)    vertical collimation
 *   (<)   Ia_delta  (double)    index error in azimuth
 *
 *   Prior requirements:
 *   tcsApplInit must have been called at least once.
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


long tcsModelAdjust(struct genSubRecord *pgsub)
{
/* Local copies of global variables. */
    double ca_delta, ce_delta, ia_delta;

/* Fetch all input arguments into local variables. */
    ca_delta = *(double *)pgsub->a;          /* horizontal collimation */
    ce_delta = *(double *)pgsub->b;          /* vertical collimation */
    ia_delta = *(double *)pgsub->c;          /* index error in azimuth */

/* Copy into global memory. */
     
    if (TcsSemId) {
       epicsMutexLock(TcsSemId);
       Ca_delta = ca_delta;
       Ce_delta = ce_delta;
       Ia_delta = ia_delta;
       epicsMutexUnlock(TcsSemId);
    }
    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsModel
 *
 *   Purpose:
 *   Sets a telescope pointing model parameter.
 *
 *   Description:
 *   The model parameter is insterted into the tpoint model.
 *
 *   Invocation:
 *   tcsModel(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to gensub record
 *
 *   Epics inputs:
 * 
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *
 *   Prior requirements:
 *   tcsApplInit must have been called at least once.
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


long tcsModel(struct genSubRecord *pgsub)
{
    int i, j, status;
    double val;
    char name[9];

/* Local copies of global variables. */
    int model[MAXTRM], nterms;
    char coeffn[NTROOM][9];
    char coform[NTROOM][9];
    double coeffv[MAXTRM];

    if (!TcsSemId){
        printf("TcsSemId not created\n");
        return 0;
    }

/* Copy from global memory. */
    epicsMutexLock(TcsSemId);
    for ( i = 0; i < MAXTRM; i++ ) {
       model[i] = Model[i];
       coeffv[i] = Coeffv[i];
    }
    nterms = Nterms;
    for ( i = 0; i < NTROOM; i++ ) {
       for ( j = 0; j < 9; j++ ) {
          coeffn[i][j] = Coeffn[i][j];
          coform[i][j] = Coform[i][j];
       }
    }
    epicsMutexUnlock(TcsSemId);

/* Fetch all input arguments into local variables. */
    val = *(double *)pgsub->b;
    name[0] = '\0';
    strncat( name, pgsub->a, 9);
    //printf("name: %s - val = %f\n", name, val);

    if ( strlen( name ) ) {
       status = tcsAddtrm( MAXTRM, NTROOM, name, val, &nterms, coeffn, coform, 
            model, coeffv);
       if ( status <= 0  ) {
          printf("Failed to add %s to model; status %d\n", name, status);
       }
    }

/* Copy into global memory. */
    epicsMutexLock(TcsSemId);
    for ( i = 0; i < MAXTRM; i++ ) {
       Model[i] = model[i];
       Coeffv[i] = coeffv[i];
    }
    Nterms = nterms;
    for ( i = 0; i < NTROOM; i++ ) {
       for ( j = 0; j < 9; j++ ) {
          Coeffn[i][j] = coeffn[i][j];
          Coform[i][j] = coform[i][j];
       }
    }
    epicsMutexUnlock(TcsSemId);

    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSlowProcess
 *
 *   Purpose:
 *   The TCS slow loop.
 *
 *   Description:
 *   Implements the slow process of the Gemini TCS pointing model.
 *
 *   Invocation:
 *   tcsSlowProcess(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    psub     (genSubRecord *) Pointer to genSub record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *   timeNow         timelib    Reads clock
 *   timeThenR       timelib    Converts time from raw form
 *   slaPolmo        slalib     Computes polar motion
 *   slaAoppa        slalib     computes apparent to observed parameters
 *   slaMappa        slalib     computes mean to apparent parameters
 *
 *   External variables:
 *   (>)   TcsSemId  (int)      global memory protection semaphore
 *   (>)   Hm        (double)   site elevation
 *   (<)   Tick0     (double)   raw clock time at reference epoch
 *   (<)   St0       (double)   LAST at reference epoch
 *   (<)   Tt0       (double)   TT at reference epoch
 *   (<)   Tdbj      (double)   TDB Julian Epoch
 *   (<)   Amprms    (double)   target-independent MAP parameters
 *   (<)   Aoprms    (double)   target-independent AOP parameters
 *   (<)   Temp      (double)   ambient temperature
 *   (<)   Press     (double)   pressure
 *   (<)   Humid     (double)   relative humidity
 *   (<)   Wavelr    (double)   reference wavelength
 *   (<)   Refa      (double)   tan refraction constant
 *   (<)   Refb      (double)   tan^3 refraction constant
 *   (<)   Slat      (double)   function of telescope latitude
 *   (<)   Clat      (double)   function of telescope latitude
 *   (<)   Tlat      (double)   telescope true latitude
 *   (<)   Tlat      (double)   telescope true latitude
 *   (<)   Tlong     (double)   telescope true longitude
 *   (<)   Daz       (double)   azimuth correction for polar motion
 *   (<)   Ukm       (double)   distance from spin axis
 *   (<)   Vkm       (double)   distance from equator
 *   (<)   Diurab    (double)   diurnal aberration
 *
 *   Epics inputs:
 *   a => Temperature (deg (k)
 *   b => Air pressure (mbars)
 *   c => Humidity (0 -> 1)
 *   d => Wavelength for refraction calculations
 *
 *   Prior requirements:
 *   tcsApplInit must have been called at least once.
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


long tcsSlowProcess( genSubRecord *psub )
{
    int i;
    double ut1, tdb;

/* Local copies of global variables. */
    double tlongm, tlatm, xpmr, ypmr, uau, vau, temp, press, humid,
           wavelr, tlr, tick0, st0, tt0, deltdb, tdbj, amprms[21], tlat, ukm,
           vkm, tlong, hm, slat, clat, daz, diurab, aoprms[15];

/* Pull in all input parameters of the record */

    temp = *(double *)psub->a;             /* temperature (degrees K) */
    press = *(double *)psub->b;            /* pressure (mbars) */
    humid = *(double *)psub->c;            /* humidity (0 -> 1) */
    wavelr = *(double *)psub->d;           /* wavelength for refraction (microns) */
    tlr = *(double *)psub->e;              /* tropospheric lapse rate */
    tlongm = *(double *)psub->f;           /* telescope mean longitude */
    tlatm = *(double *)psub->g;            /* telescope mean latitude */
    xpmr = *(double *)psub->h;             /* polar motion */
    ypmr = *(double *)psub->i;             /* polar motion */

/* Grab consistent copies of global variables. Some of these are never
 * likely to change and could be got directly from global memory but just
 * to be on the safe side make local copies of everything. */

    if(! TcsSemId)return 0;
    epicsMutexLock(TcsSemId);
    hm = Hm;
    epicsMutexUnlock(TcsSemId);

/* Read the clock. */
    (void) timeNow(&tick0);

/* Go forward to middle of slow-update interval. */
    tick0 += TSLOW / 2.0;

/* LAST (radians) at that moment. */
    (void) timeThenR(tick0, LAST, &st0);

/* TT at that moment (MJD). */
    (void) timeThenD(tick0, TT, &tt0);

/* UT1 at that moment (MJD). */
    (void) timeThenD(tick0, UT1, &ut1);

/* Adjust the telescope latitude, longitude and azimuth for polar motion. */
    slaPolmo(tlongm, tlatm, xpmr, ypmr, &tlong, &tlat, &daz);
    slat = sin(tlat);
    clat = cos(tlat);

/* Distance of observatory from Earth spin axis and equator. */
    slaGeoc(tlat, hm, &uau, &vau);
    ukm = uau * AU2KM;
    vkm = vau * AU2KM;
    diurab = PI2 * uau * UTST / C;

/* TDB-TT and TDB Julian Epoch. */
    deltdb = slaRcc(tt0, dmod(ut1, 1.0), -tlong, ukm, vkm) / 86400.0;
    tdb = tt0 + deltdb;
    tdbj = slaEpj(tdb);

/* Target-independent apparent to observed place parameters. */
    slaAoppa(ut1, 0.0, tlongm, tlatm, hm, xpmr, ypmr, temp, press, humid,
             wavelr, tlr, aoprms);

/* Use more rigorous values of tlat etc from slaPolmo. */
    aoprms[0] = tlat;
    aoprms[1] = slat;
    aoprms[2] = clat;
    aoprms[14] = daz;

/* Target-independent J2000 mean to apparent place parameters. */
    slaMappa(2000.0, tdb, amprms);


    epicsMutexLock(TcsSemId);
    Tick0 = tick0;
    St0 = st0;
    Tt0 = tt0;
    Tdbj = tdbj;
    for (i = 0; i < 21; i++)
        Amprms[i] = amprms[i];
    for (i = 0; i < 15; i++)
        Aoprms[i] = aoprms[i];
    Temp = temp;
    Press = press;
    Humid = humid;
    Tlr = tlr;
    Wavelr = wavelr;
    Refa = aoprms[10];
    Refb = aoprms[11];
    Slat = slat;
    Clat = clat;
    Tlat = tlat;
    Tlong = tlong;
    Daz = daz;
    Ukm = ukm;
    Vkm = vkm;
    Diurab = diurab;
    epicsMutexUnlock(TcsSemId);

/* Debug output */
/*
   if (pkdbgwriteflag) {
     fprintf(dbgfp, "SlowProcess: start of output\n");
     fprintf(dbgfp, "tai (MJD)   %23.12f\n", timeRaw2tai(tick0));
     fprintf(dbgfp, "temp (deg K)  %f\n", temp);
     fprintf(dbgfp, "press (mbar)  %f\n", press);
     fprintf(dbgfp, "humid         %f\n", humid);
     fprintf(dbgfp, "wavelr (micron) %f\n", wavelr);
     fprintf(dbgfp, "tlong (degs)  %23.10f\n", tlong*180.0/PI);
     fprintf(dbgfp, "t0 (TAI MJD)  %23.10f\n", timeRaw2tai(tick0));
     fprintf(dbgfp, "st0 (hours)   %23.10f\n", st0*12.0/PI);
     fprintf(dbgfp, "tt0 (TT MJD)  %23.10f\n", tt0);
     fprintf(dbgfp, "ttj (TT )     %23.10f\n", tdbj);
     fprintf(dbgfp, "refa          %23.10f\n", Refa);
     fprintf(dbgfp, "refb          %23.10f\n", Refb);
     for (i = 0; i < 21; i++) {
       fprintf(dbgfp, "amprms[%d]   %23.10f\n", i, amprms[i]);
     }
     for (i = 0; i < 14; i++) {
       fprintf(dbgfp, "aoprms[%d]   %23.10f\n", i, aoprms[i]);
     }
     fprintf(dbgfp, "SlowProcess: end of output\n");
   }
*/
/* Write deltdb to output to make it available to the time routines. */
    *(double *)psub->vala = deltdb;

/* Write tlat and tlong to output to make them available to the time
   routines. */
    *(double *)psub->valb = tlat;
    *(double *)psub->valc = tlong;
    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsEMediumLoop
 *
 *   Purpose:
 *   The TCS medium loop.
 *
 *   Description:
 *   This code implements the Medium loop of the Gemini TCS.
 *   It is expected to be called at 0.2Hz as an EPICS subroutine record.
 *
 *   Invocation:
 *   tcsEMediumLoop(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    psub     (genSubRecord *) Pointer to genSub record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   tcsMediumLoop
 *
 *   External variables:
 *
 *   Prior requirements:
 *   tcsApplInit, tcsSecProcess and tcsSlowProcess must have been called at
 *   least once.
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


long tcsEMediumLoop( genSubRecord *psub )
{

/* do all the work in tcsMediumLoop */
    tcsMediumLoop();

    return 0;
}

/* *INDENT-OFF */
/*+
 *   Function name:
 *   tcsMediumLoop
 *
 *   Purpose:
 *   The TCS medium process.
 *
 *   Description:
 *   This code implements the Medium loop of the Gemini TCS.
 *
 *   Invocation:
 *   tcsMediumLoop()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *   none
 *
 *   Function value:
 *   none
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   (>)   Ae2mt     (double[3][3]) AzEl to mount rotation matrix
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (>)   M_tar_p   (double)    mount tracking coordinates
 *   (>)   M_frame   (FRAMETYPE) mount tracking frame
 *   (>)   M_eqx     (double)    mount equinox
 *   (>)   M_wavel   (double)    mount wavelength
 *   (>)   R_frame   (FRAMETYPE) rotator orientation frame
 *   (>)   R_eqx     (double)    rotator orientation equinox
 *   (>)   C_frame   (FRAMETYPE) chop orientation frame
 *   (>)   C_eqx     (double)    chop orientation equinox
 *   (>)   S_tar_pt  (double)    source tracking coordinates
 *   (>)   S_frame   (FRAMETYPE) source tracking frame
 *   (>)   S_eqx     (double)    source equinox
 *   (>)   S_wavel   (double)    source wavelength
 *   (>)   G1_tar_p  (double)    PWFS #1 tracking coordinates
 *   (>)   G1_frame  (FRAMETYPE) PWFS #1 tracking frame
 *   (>)   G1_eqx    (double)    PWFS #1 equinox
 *   (>)   G1_wavel  (double)    PWFS #1 wavelength
 *   (>)   G2_tar_p  (double)    PWFS #2 tracking coordinates
 *   (>)   G2_frame  (FRAMETYPE) PWFS #2 tracking frame
 *   (>)   G2_eqx    (double)    PWFS #2 equinox
 *   (>)   G2_wavel  (double)    PWFS #2 wavelength
 *   (>)   G3_tar_p  (double)    OIWFS tracking coordinates
 *   (>)   G3_frame  (FRAMETYPE) OIWFS tracking frame
 *   (>)   G3_eqx    (double)    OIWFS equinox
 *   (>)   G3_wavel  (double)    OIWFS wavelength
 *   (>)   Sst       (double)    function of LAST
 *   (>)   Cst       (double)    function of LAST
 *   (<)   M_otm1    (double)    mount OTM 1
 *   (<)   M_otm2    (double)    mount OTM 2
 *   (<)   M_otm1_i  (double)    mount inverse OTM 1
 *   (<)   M_otm2_i  (double)    mount inverse OTM 2
 *   (<)   R_otm1    (double)    rotator OTM 1
 *   (<)   R_otm2    (double)    rotator OTM 2
 *   (<)   R_otm1_i  (double)    rotator inverse OTM 1
 *   (<)   R_otm2_i  (double)    rotator inverse OTM 2
 *   (<)   C_otm1    (double)    chop OTM 1
 *   (<)   C_otm2    (double)    chop OTM 2
 *   (<)   C_otm1_i  (double)    chop inverse OTM 1
 *   (<)   C_otm2_i  (double)    chop inverse OTM 2
 *   (<)   S_otm1    (double)    source OTMs 1
 *   (<)   S_otm2    (double)    source OTMs 2
 *   (<)   S_otm1_i  (double)    source inverse OTMs 1
 *   (<)   S_otm2_i  (double)    source inverse OTMs 2
 *   (<)   G1_otm1   (double)    PWFS #1 OTMs 1
 *   (<)   G1_otm2   (double)    PWFS #1 OTMs 2
 *   (<)   G1_otm1_i (double)    PWFS #1 inverse OTMs 1
 *   (<)   G1_otm2_i (double)    PWFS #1 inverse OTMs 2
 *   (<)   G2_otm1   (double)    PWFS #2 OTMs 1
 *   (<)   G2_otm2   (double)    PWFS #2 OTMs 2
 *   (<)   G2_otm1_i (double)    PWFS #2 inverse OTMs 1
 *   (<)   G2_otm2_i (double)    PWFS #2 inverse OTMs 2
 *   (<)   G3_otm1   (double)    OIWFS OTMs 1
 *   (<)   G3_otm2   (double)    OIWFS OTMs 2
 *   (<)   G3_otm1_i (double)    OIWFS inverse OTMs 1
 *   (<)   G3_otm2_i (double)    OIWFS inverse OTMs 2
 *
 *   Prior requirements:
 *   tcsApplInit, tcsSecProcess, tcsSlowProcess and tcsInitSource must 
 *   have been called at least once.
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON */

void tcsMediumLoop(void)
{

/* Local copies of global variables */
    static double m_tar_p[2];
    static double s_tar_pt[3][2];
    static double g1_tar_p[3][2];
    static double g2_tar_p[3][2];
    static double g3_tar_p[3][2];
    static double gg1_tar_p[3][2];
    static double gg2_tar_p[3][2];
    static double gg3_tar_p[3][2];
    static double gg4_tar_p[3][2];

    static FRAMETYPE m_frame;
    static double m_eqx, m_wavel;
    static FRAMETYPE r_frame;
    static double r_eqx;
    static FRAMETYPE c_frame[2];
    static double c_eqx[2];
    static FRAMETYPE s_frame[3];
    static double s_eqx[3], s_wavel[3];
    static FRAMETYPE g1_frame;
    static double g1_eqx, g1_wavel;
    static FRAMETYPE g2_frame;
    static double g2_eqx, g2_wavel;
    static FRAMETYPE g3_frame;
    static double g3_eqx, g3_wavel;
    static FRAMETYPE gg1_frame;
    static double gg1_eqx, gg1_wavel;
    static FRAMETYPE gg2_frame;
    static double gg2_eqx, gg2_wavel;
    static FRAMETYPE gg3_frame;
    static double gg3_eqx, gg3_wavel;
    static FRAMETYPE gg4_frame;
    static double gg4_eqx, gg4_wavel;

    static double m_otm1[3][3], m_otm1_i[3][3], m_otm2[3][3], m_otm2_i[3][3];
    static double r_otm1[3][3], r_otm1_i[3][3], r_otm2[3][3], r_otm2_i[3][3];
    static double c_otm1[2][3][3], c_otm1_i[2][3][3],
                  c_otm2[2][3][3], c_otm2_i[2][3][3];
    static double s_otm1[3][3][3], s_otm1_i[3][3][3], s_otm2[3][3][3],
                  s_otm2_i[3][3][3];
    static double g1_otm1[3][3][3], g1_otm1_i[3][3][3], g1_otm2[3][3][3],
                  g1_otm2_i[3][3][3];
    static double g2_otm1[3][3][3], g2_otm1_i[3][3][3], g2_otm2[3][3][3],
                  g2_otm2_i[3][3][3];
    static double g3_otm1[3][3][3], g3_otm1_i[3][3][3], g3_otm2[3][3][3],
                  g3_otm2_i[3][3][3];
    static double gg1_otm1[3][3][3], gg1_otm1_i[3][3][3], gg1_otm2[3][3][3],
                  gg1_otm2_i[3][3][3];
    static double gg2_otm1[3][3][3], gg2_otm1_i[3][3][3], gg2_otm2[3][3][3],
                  gg2_otm2_i[3][3][3];
    static double gg3_otm1[3][3][3], gg3_otm1_i[3][3][3], gg3_otm2[3][3][3],
                  gg3_otm2_i[3][3][3];
    static double gg4_otm1[3][3][3], gg4_otm1_i[3][3][3], gg4_otm2[3][3][3],
                  gg4_otm2_i[3][3][3];
    static double dummy_otm1[2][3][3], dummy_otm1_i[2][3][3],
                  dummy_otm2[2][3][3], dummy_otm2_i[2][3][3];

    double sst, cst, ae2mt[3][3];
    double u[3], h[3], a[3], m[3];
    double r_tar_p[2];

    int i, j, k, ichop;

/* Get local copies of everything needed. */
    if (!TcsSemId) {
       printf("tcsMediumLoop: TcsSemId not available \n");
       return;
    }
    epicsMutexLock(TcsSemId);
    for ( i = 0; i < 3; i++ ) {
       for ( j = 0; j < 3; j++ ) {
          ae2mt[i][j] = Ae2mt[i][j];
       }
    }
    m_tar_p[0] = M_tar_p[0];
    m_tar_p[1] = M_tar_p[1];
    m_frame = M_frame;
    m_eqx = M_eqx;
    m_wavel = M_wavel;
    r_frame = R_frame;
    r_eqx = R_eqx;
    for (ichop = 1; ichop < 3; ichop++) {
       i = ichop - 1;
       c_frame[i] = C_frame[i];
       c_eqx[i] = C_eqx[i];
    }
    for (ichop = 0; ichop < 3; ichop++) {
        s_tar_pt[ichop][0] = S_tar_pt[ichop][0];
        s_tar_pt[ichop][1] = S_tar_pt[ichop][1];
        g1_tar_p[ichop][0] = G1_tar_p[ichop][0];
        g1_tar_p[ichop][1] = G1_tar_p[ichop][1];
        g2_tar_p[ichop][0] = G2_tar_p[ichop][0];
        g2_tar_p[ichop][1] = G2_tar_p[ichop][1];
        g3_tar_p[ichop][0] = G3_tar_p[ichop][0];
        g3_tar_p[ichop][1] = G3_tar_p[ichop][1];
        gg1_tar_p[ichop][0] = GG1_tar_p[ichop][0];
        gg1_tar_p[ichop][1] = GG1_tar_p[ichop][1];
        gg2_tar_p[ichop][0] = GG2_tar_p[ichop][0];
        gg2_tar_p[ichop][1] = GG2_tar_p[ichop][1];
        gg3_tar_p[ichop][0] = GG3_tar_p[ichop][0];
        gg3_tar_p[ichop][1] = GG3_tar_p[ichop][1];
        gg4_tar_p[ichop][0] = GG4_tar_p[ichop][0];
        gg4_tar_p[ichop][1] = GG4_tar_p[ichop][1];
        s_frame[ichop] = S_frame[ichop];
        s_eqx[ichop] = S_eqx[ichop];
        s_wavel[ichop] = S_wavel[ichop];
    }
    g1_frame = G1_frame;
    g1_eqx = G1_eqx;
    g1_wavel = G1_wavel;
    g2_frame = G2_frame;
    g2_eqx = G2_eqx;
    g2_wavel = G2_wavel;
    g3_frame = G3_frame;
    g3_eqx = G3_eqx;
    g3_wavel = G3_wavel;
    gg1_frame = GG1_frame;
    gg1_eqx = GG1_eqx;
    gg1_wavel = GG1_wavel;
    gg2_frame = GG2_frame;
    gg2_eqx = GG2_eqx;
    gg2_wavel = GG2_wavel;
    gg3_frame = GG3_frame;
    gg3_eqx = GG3_eqx;
    gg3_wavel = GG3_wavel;
    gg4_frame = GG4_frame;
    gg4_eqx = GG4_eqx;
    gg4_wavel = GG4_wavel;
    sst = Sst;
    cst = Cst;
    epicsMutexUnlock(TcsSemId);

/* Generate OTMs for mount. */
    target(sst, cst, m_frame, m_eqx, m_wavel, m_tar_p, ae2mt,
           m_otm1, m_otm1_i, m_otm2, m_otm2_i);

/* Get mount target in rotator tracking frame. */
    PartA(m_frame, m_tar_p, m_otm1, sst, cst, m_otm2, &u[0], &u[1], &u[2],
          &a[0], &a[1], &a[2], &h[0], &h[1], &h[2], &m[0], &m[1], &m[2]);
    ptrani( m, r_frame, r_eqx, sst, cst, ae2mt, &r_tar_p[0], &r_tar_p[1]);

/* Generate OTMs for rotator. */
    target(sst, cst, r_frame, r_eqx, m_wavel, r_tar_p, ae2mt,
           r_otm1, r_otm1_i, r_otm2, r_otm2_i);

/* Generate OTMs for chop. The inverse OTMs use are used for transforming
   source A az/el to chop frame and so use the source A wavelength. */
    for (ichop = 1; ichop < 3; ichop++) {
        i = ichop - 1;
        target(sst, cst, c_frame[i], c_eqx[i], s_wavel[ichop], m_tar_p, ae2mt,
               c_otm1[i], dummy_otm1_i[i], c_otm2[i], dummy_otm2_i[i]);
        target(sst, cst, c_frame[i], c_eqx[i], s_wavel[0], m_tar_p, ae2mt,
               dummy_otm1[i], c_otm1_i[i], dummy_otm2[i], c_otm2_i[i]);
    }

/* Generate OTMs for sources and guidestars. */
    for (ichop = 0; ichop < 3; ichop++) {
        target(sst, cst, s_frame[ichop], s_eqx[ichop],
               s_wavel[ichop], s_tar_pt[ichop], ae2mt,
               s_otm1[ichop], s_otm1_i[ichop],
               s_otm2[ichop], s_otm2_i[ichop]);
        target(sst, cst, g1_frame, g1_eqx,
               g1_wavel, g1_tar_p[ichop], ae2mt,
               g1_otm1[ichop], g1_otm1_i[ichop],
               g1_otm2[ichop], g1_otm2_i[ichop]);
        target(sst, cst, g2_frame, g2_eqx,
               g2_wavel, g2_tar_p[ichop], ae2mt,
               g2_otm1[ichop], g2_otm1_i[ichop],
               g2_otm2[ichop], g2_otm2_i[ichop]);
        target(sst, cst, g3_frame, g3_eqx,
               g3_wavel, g3_tar_p[ichop], ae2mt,
               g3_otm1[ichop], g3_otm1_i[ichop],
               g3_otm2[ichop], g3_otm2_i[ichop]);
        target(sst, cst, gg1_frame, gg1_eqx,
               gg1_wavel, gg1_tar_p[ichop], ae2mt,
               gg1_otm1[ichop], gg1_otm1_i[ichop],
               gg1_otm2[ichop], gg1_otm2_i[ichop]);
        target(sst, cst, gg2_frame, gg2_eqx,
               gg2_wavel, gg2_tar_p[ichop], ae2mt,
               gg2_otm1[ichop], gg2_otm1_i[ichop],
               gg2_otm2[ichop], gg2_otm2_i[ichop]);
        target(sst, cst, gg3_frame, gg3_eqx,
               gg3_wavel, gg3_tar_p[ichop], ae2mt,
               gg3_otm1[ichop], gg3_otm1_i[ichop],
               gg3_otm2[ichop], gg3_otm2_i[ichop]);
        target(sst, cst, gg4_frame, gg4_eqx,
               gg4_wavel, gg4_tar_p[ichop], ae2mt,
               gg4_otm1[ichop], gg4_otm1_i[ichop],
               gg4_otm2[ichop], gg4_otm2_i[ichop]);
    }

/* Copy the new values to the global areas. */
    epicsMutexLock(TcsSemId);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            M_otm1[i][j] = m_otm1[i][j];
            M_otm2[i][j] = m_otm2[i][j];
            M_otm1_i[i][j] = m_otm1_i[i][j];
            M_otm2_i[i][j] = m_otm2_i[i][j];
            R_otm1[i][j] = r_otm1[i][j];
            R_otm2[i][j] = r_otm2[i][j];
            R_otm1_i[i][j] = r_otm1_i[i][j];
            R_otm2_i[i][j] = r_otm2_i[i][j];
            for (ichop = 1; ichop < 3; ichop++) {
               k = ichop - 1;
               C_otm1[k][i][j] = c_otm1[k][i][j];
               C_otm2[k][i][j] = c_otm2[k][i][j];
               C_otm1_i[k][i][j] = c_otm1_i[k][i][j];
               C_otm2_i[k][i][j] = c_otm2_i[k][i][j];
            }
            for (ichop = 0; ichop < 3; ichop++) {
                S_otm1[ichop][i][j] = s_otm1[ichop][i][j];
                S_otm2[ichop][i][j] = s_otm2[ichop][i][j];
                S_otm1_i[ichop][i][j] = s_otm1_i[ichop][i][j];
                S_otm2_i[ichop][i][j] = s_otm2_i[ichop][i][j];
                G1_otm1[ichop][i][j] = g1_otm1[ichop][i][j];
                G1_otm2[ichop][i][j] = g1_otm2[ichop][i][j];
                G1_otm1_i[ichop][i][j] = g1_otm1_i[ichop][i][j];
                G1_otm2_i[ichop][i][j] = g1_otm2_i[ichop][i][j];
                G2_otm1[ichop][i][j] = g2_otm1[ichop][i][j];
                G2_otm2[ichop][i][j] = g2_otm2[ichop][i][j];
                G2_otm1_i[ichop][i][j] = g2_otm1_i[ichop][i][j];
                G2_otm2_i[ichop][i][j] = g2_otm2_i[ichop][i][j];
                G3_otm1[ichop][i][j] = g3_otm1[ichop][i][j];
                G3_otm2[ichop][i][j] = g3_otm2[ichop][i][j];
                G3_otm1_i[ichop][i][j] = g3_otm1_i[ichop][i][j];
                G3_otm2_i[ichop][i][j] = g3_otm2_i[ichop][i][j];
                GG1_otm1[ichop][i][j] = gg1_otm1[ichop][i][j];
                GG1_otm2[ichop][i][j] = gg1_otm2[ichop][i][j];
                GG1_otm1_i[ichop][i][j] = gg1_otm1_i[ichop][i][j];
                GG1_otm2_i[ichop][i][j] = gg1_otm2_i[ichop][i][j];
                GG2_otm1[ichop][i][j] = gg2_otm1[ichop][i][j];
                GG2_otm2[ichop][i][j] = gg2_otm2[ichop][i][j];
                GG2_otm1_i[ichop][i][j] = gg2_otm1_i[ichop][i][j];
                GG2_otm2_i[ichop][i][j] = gg2_otm2_i[ichop][i][j];
                GG3_otm1[ichop][i][j] = gg3_otm1[ichop][i][j];
                GG3_otm2[ichop][i][j] = gg3_otm2[ichop][i][j];
                GG3_otm1_i[ichop][i][j] = gg3_otm1_i[ichop][i][j];
                GG3_otm2_i[ichop][i][j] = gg3_otm2_i[ichop][i][j];
                GG4_otm1[ichop][i][j] = gg4_otm1[ichop][i][j];
                GG4_otm2[ichop][i][j] = gg4_otm2[ichop][i][j];
                GG4_otm1_i[ichop][i][j] = gg4_otm1_i[ichop][i][j];
                GG4_otm2_i[ichop][i][j] = gg4_otm2_i[ichop][i][j];
            }
        }
    }
    epicsMutexUnlock(TcsSemId);
/*
    if (pkdbgwriteflag) {
      printfromfast = 1 ;
      fprintf(dbgfp, "Medium loop inputs and outputs:\n");
      fprintf(dbgfp, "m_eqx             %23.10f (years)\n", m_eqx);
      fprintf(dbgfp, "m_wavel           %23.10f (years)\n", m_wavel);
      fprintf(dbgfp, "m_tar_p[0]        %23.10f (degs)\n", m_tar_p[0]/D2R);
      fprintf(dbgfp, "m_tar_p[1]        %23.10f (degs)\n", m_tar_p[1]/D2R);
      fprintf(dbgfp, "wavelr            %23.10f \n", Wavelr);
    }
*/
    return;
}

static void target(double sst, double cst, FRAMETYPE frame, double usreqx,
                   double wavel, double target[2], double ae2mt[3][3],
                   double otmua[3][3], double otmuai[3][3],
                   double otmhe[3][3], double otmhei[3][3])
/* *INDENT-OFF* */
/*
**  - - - - - - -
**   t a r g e t
**  - - - - - - -
**
**  Update target transformation
**
**  Given (arguments):
**     sst      double        sine of LAST
**     cst      double        cosine of LAST
**     frame    FRAMETYPE     tracking frame ID
**     usreqx   double        tracking frame equinox (mean RA/Dec only)
**     wavel    double        wavelength (micrometres)
**     target   double[2]     target spherical coordinates, tracking frame
**     ae2mt    double[3][3]  Az/El to mount rotation matrix
**
**  Returned (arguments):
**     otmua    double[3][3]  OTM #1
**     otmuai   double[3][3]  inverse of OTM #1
**     otmhe    double[3][3]  OTM #2
**     otmhei   double[3][3]  inverse of OTM #2
**
**  Given (global data):
**     Del      double        probe-vector spacing (radians)
**     Temp     double        ambient temperature (deg K)
**     Press    double        pressure (mB)
**     Humid    double        relative humidity (0-1)
**     Wavelr   double        reference wavelength (micrometres)
**     Refa     double        refraction constants A and...
**     Refb     double        ...B for reference wavelength (radians)
**
**  Called:  slaAtmdsp, slaDcs2c, ptran
**
**  Note:  the ptran function, called by this routine, itself uses
**         a number of items from global data.
*/
/* *INDENT-ON* */
{
    double prepre[3][3];        /* preliminary precession matrix */
    double refac, refbc;        /* refraction constants for source colour */
    double u[3];                /* current tracking coordinates */
    double u1[3], a1[3], h1[3], e1[3];  /* probe vector #1 */
    double u2[3], a2[3], h2[3], e2[3];  /* probe vector #2 */
    double u3[3], a3[3], h3[3], e3[3];  /* probe vector #3 */
    int j;

/* Local copies of global variables */
    double del, temp, press, humid, wavelr, refa, refb;
    static int dbgLevel = DBG_NONE; /* debug level */


    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "target: Semaphore not created");
        return;
    }
    epicsMutexLock(TcsSemId);
    del = Del;
    temp = Temp;
    press = Press;
    humid = Humid;
    wavelr = Wavelr;
    refa = Refa;
    refb = Refb;
    epicsMutexUnlock(TcsSemId);

/* Generate preliminary precession matrix if required. */
    if (frame == FK4) {

    /* Nominated FK4 equinox to B1950. */
        slaPrebn(usreqx, 1950.0, prepre);

    } else if (frame == FK5) {

    /* Nominated FK5 equinox to J2000. */
        slaPrec(usreqx, 2000.0, prepre);
    }

/* Adjust refraction constants for colour. */
    slaAtmdsp(temp, press, humid, wavelr, refa, refb, wavel,
              &refac, &refbc);

/* Get current tracking x,y,z (RH). */
    slaDcs2c(target[0], target[1], u);
    if (frame == AZEL_TOPO) u[0] = -u[0];

/* Generate three probe vectors. */
    probev(u, del, u1, u2, u3);

/* Put the probe vectors through the pointing transformation. */
    ptran(frame, usreqx, prepre, refac, refbc, sst, cst, u1, ae2mt, a1, h1, e1);
    ptran(frame, usreqx, prepre, refac, refbc, sst, cst, u2, ae2mt, a2, h2, e2);
    ptran(frame, usreqx, prepre, refac, refbc, sst, cst, u3, ae2mt, a3, h3, e3);

/* Generate the osculating transformation matrices. */
    otm(u1, u2, u3, a1, a2, a3, otmua, otmuai, &j);
    if (j != 0)
        printf("problem deriving OTM #1!\n");
    otm(h1, h2, h3, e1, e2, e3, otmhe, otmhei, &j);
    if (j != 0)
        printf("problem deriving OTM #2!\n");
}

/* A small number */
#define TINY 1e-10

static void ptran(FRAMETYPE frame, double usreqx, double prepre[3][3],
                  double refa, double refb, double sst, double cst,
                  double u[3], double ae2mt[3][3], double a[3], double h[3], 
                  double e[3])
/* *INDENT-OFF* */
/*
**  - - - - - -
**   p t r a n
**  - - - - - -
**
**  Pointing transformation
**
**  Given:
**     frame    FRAMETYPE     reference frame ID (see below)
**     usreqx   double        reference frame equinox (if a mean RA/Dec)
**     prepre   double[3][3]  user frame to B1950 or J2000 (if required)
**     refa     double        refraction constant A
**     refb     double        refraction constant B
**     u        double[3]     target x,y,z in tracking reference frame
**     ae2mt    double[3][3]  Az/El to mount rotation matrix
**
**  Returned:
**     a        double[3]  target x,y,z in pre-rotation frame
**     h        double[3]  target x,y,z in post-rotation frame
**     e        double[3]  target x,y,z in precollimation mount az/el frame
**
**  Given (global data):
**     Tdbj     double     TDB Julian Epoch
**     Sst      double     sine, cosine of LAST
**     Cst
**     Amprms   double[21] J2000 mean to apparent parameters
**     Slat     double     sine, cosine of true geodetic latitude
**     Clat
**     Daz      double     polar-motion correction to azimuth (radians)
**     Diurab   double     diurnal aberration (radians)
**
**  Pre-defined frame values:
**     AZEL_TOPO     topocentric Az/El
**     APPT          geocentric apparent RA/Dec
**     FK5           IAU 1976 RA/Dec, any equinox
**     FK4           pre IAU 1976 RA/Dec, any equinox
**
**  Called:  slaAddet, slaDcc2s, slaDcs2c, slaDmxv, slaFk45z,
**           slaMapqkz, slaSubet
**
**  Notes:
**
**  1  In the typical case, frame is FK4 or FK5, the vector u is
**     the nominated type of mean RA/Dec, a is geocentric apparent
**     RA/Dec and h is apparent -HA/Dec.
**
**  2  No check on frame validity is made.  The serendipitous
**     default is FK4.
*/
/* *INDENT-ON* */
{
    int i;
    double rm1, dm1, rm2, dm2, v2[3], v3[3], rm3, dm3,
           rm4, dm4, rm5, dm5, ra, da, rd[3],
           xrd, yrd, zrd, xhd, yhd, zhd, f,
           xhdt, yhdt, zhdt, xaet, yaet, zaet, z,
           zsq, rsq, r, wb, wt, dref, cosdel,
           aeo[3];
 
/* Local copies of global variables */
    double tdbj, diurab, daz, clat, slat, amprms[21];
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "ptran: Semaphore not created");
        return;
    }
    epicsMutexLock(TcsSemId);
    tdbj = Tdbj;
    diurab = Diurab;
    daz = Daz;
    clat = Clat;
    slat = Slat;
    for (i = 0; i < 21; i++) amprms[i] = Amprms[i];

    epicsMutexUnlock(TcsSemId);

/* Examine tracking frame ID. */
    if ( frame == AZEL_TOPO ) {

    /* Tracking frame is topocentric Az/El. */

    /* Copy the input vector to results. */
        xaet = h[0] = a[0] = u[0];
        yaet = h[1] = a[1] = u[1];
        zaet = h[2] = a[2] = u[2];

    } else {

        if (frame == APPT) {

        /* Tracking frame is geocentric apparent RA/Dec. */

        /* Copy the input vector to the local apparent RA/Dec. */
            for (i = 0; i < 3; i++) {
                rd[i] = u[i];
            }

        } else {

            if (frame == FK5) {

            /* Tracking frame is mean RA/Dec, FK5. */

            /* Precess to J2000. */
                slaDmxv(prepre, u, v3);

            /* Cartesian to spherical. */
                slaDcc2s(v3, &rm5, &dm5);

            } else {

            /* Tracking frame is mean RA/Dec, FK4. */

            /* Cartesian to spherical. */
                slaDcc2s(u, &rm1, &dm1);

            /* Remove E-terms. */
                slaSubet(rm1, dm1, usreqx, &rm2, &dm2);

            /* To Cartesian. */
                slaDcs2c(rm2, dm2, v2);

            /* Precess to B1950. */
                slaDmxv(prepre, v2, v3);

            /* To spherical. */
                slaDcc2s(v3, &rm3, &dm3);

            /* Add E-terms. */
                slaAddet(rm3, dm3, 1950.0, &rm4, &dm4);

            /* Transform to J2000 FK5. */
                slaFk45z(rm4, dm4, tdbj, &rm5, &dm5);
            }

        /* Tracking frame is some kind of mean RA/Dec. */

        /* J2000 mean to apparent. */
            slaMapqkz(rm5, dm5, amprms, &ra, &da);
 
        /* Apparent RA/Dec to Cartesian. */
            slaDcs2c(ra, da, rd);
        }

    /* Tracking frame is some kind of RA/Dec. */

    /* First result. */
        for (i = 0; i < 3; i++)
            a[i] = rd[i];

    /* Earth rotation. */
        xrd = rd[0];
        yrd = rd[1];
        zrd = rd[2];
        xhd =  cst * xrd + sst * yrd;
        yhd = -sst * xrd + cst * yrd;
        zhd = zrd;

    /* Second result. */
        h[0] = xhd;
        h[1] = yhd;
        h[2] = zhd;

    /* Diurnal aberration. */
        f = ( 1.0 - diurab * yhd );
        xhdt = f * xhd;
        yhdt = f * ( yhd + diurab );
        zhdt = f * zhd;

    /* -HA/Dec to Az/El. */
        xaet = slat * xhdt + daz * yhdt - clat * zhdt;
        yaet = - daz * slat * xhdt + yhdt + daz * clat * zhdt;
        zaet = clat * xhdt + slat * zhdt;
    }

/* Refraction (constant below 3 deg). */
    z = zaet > 0.05 ? zaet : 0.05;
    zsq = z * z;
    rsq = xaet * xaet + yaet * yaet;
    r = sqrt ( rsq );
    wb = refb * rsq / zsq;
    wt = ( refa + wb ) / ( 1.0 + ( refa + 3.0 * wb ) / zsq );
    dref = wt * r / z;
    cosdel = 1.0 - dref * dref / 2.0;
    f = cosdel * ( 1.0 - wt );
    aeo[0] = xaet * f;
    aeo[1] = yaet * f;
    aeo[2] = cosdel * ( zaet + dref * r );

/* Tilt of the azimuth axis (giving third result). */
    slaDmxv( ae2mt, aeo, e);
}

static void ptrani(double e[3], FRAMETYPE frame, double usreqx, 
                   double sst, double cst, double ae2mt[3][3], 
                   double* a1, double* a2)
/* *INDENT-OFF* */
/*
**  - - - - - - -
**   p t r a n i
**  - - - - - - -
**
**  Approximate inverse pointing transformation
**
**  Given:
**     e        double[3]   target x,y,z in precollimation mount az/el frame
**     frame    FRAMETYPE   reference frame ID (see below)
**     usreqx   double      reference frame equinox (if result a mean RA/Dec)
**     ae2mt    double[3][3] AzEl to mount rotation matrix
**
**  Returned:
**     a1       double      target RA or Az in specified frame
**     a2       double      target Dec or El in specified frame
**
**  Given (global data):
**     Amprms   double[21] J2000 mean to apparent parameters
**     Slat     double     sine, cosine of true geodetic latitude
**     Clat
**     Refa     double     refraction constant A
**
**  Pre-defined frame values:
**     AZEL_TOPO     topocentric Az/El
**     APPT          geocentric apparent RA/Dec
**     FK5           IAU 1976 RA/Dec, any equinox
**     FK4           pre IAU 1976 RA/Dec, any equinox
**
**  Called:  slaAmpqk, slaDcc2s, slaDimxv, slaPreces
**
**  Notes:
**
**  1  No check on frame validity is made.  The serendipitous
**     default is FK4.
**
**  2  The transformation is approximate, intended to be used
**     exclusively for locating the probe vectors needed for
**     generating the rotator OTMs.  The approximations are as
**     follows:
**
**     . single-term refraction model
**
**     . diurnal aberration ignored
**
**     . distinction between FK4 and FK5 ignored
**
*/
/* *INDENT-ON* */
{
    double aeo[3], x, y, z, xmhd, ymhd, zmhd, v[3], ra, da, rm, dm;
    int i;
 
/* Local copies of global variables */
    double clat, slat, refa, amprms[21];
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "ptrani: Semaphore not created");
        return;
    }
    epicsMutexLock(TcsSemId);
    clat = Clat;
    slat = Slat;
    refa = Refa;
    for (i = 0; i < 21; i++) amprms[i] = Amprms[i];
    epicsMutexUnlock(TcsSemId);

/* Precollimation mount az/el to observed. */
    slaDimxv( ae2mt, e, aeo);
    x = aeo[0];
    y = aeo[1];
    z = aeo[2];

/* Approximate refraction, giving topocentric az/el. */
    z -= refa / ( z > TINY ? z : TINY );

/* If Az/El requested, wrap up. */
    if ( frame == AZEL_TOPO ) {

        v[0] = -x;
        v[1] = y;
        v[2] = z;
        slaDcc2s ( v, a1, a2 );

    } else {

    /* Az/el to -HA/Dec. */
        xmhd = slat * x + clat * z;
        ymhd = y;
        zmhd = -clat * x + slat * z;

    /* n.b. diurnal aberration ignored. */

    /* Earth rotation, giving apparent RA/Dec. */
        x = cst * xmhd - sst * ymhd;
        y = sst * xmhd + cst * ymhd;
        z = zmhd;

        v[0] = x;
        v[1] = y;
        v[2] = z;

        slaDcc2s ( v, &ra, &da );

    /* If apparent RA/Dec requested, wrap up. */
        if ( frame == APPT ) {
            *a1 = ra;
            *a2 = da;

        } else {

        /* Apparent to J2000 mean. */
            slaAmpqk ( ra, da, amprms, &rm, &dm );

        /* Precess to specified equinox (ignoring FK4/5 distinction). */
            slaPreces ( "FK5", 2000.0, usreqx, &rm, &dm );

        /* Wrap up mean RA/Dec cases. */
            *a1 = rm;
            *a2 = dm;
        }
    }
}

static void probev(double v0[3], double del,
                   double v1[3], double v2[3], double v3[3])
/* *INDENT-OFF* */
/*
**  - - - - - - -
**   p r o b e v
**  - - - - - - -
**
**  Generate probe vectors for sampling of pointing transformation.
**
**  Given:
**     v0          d(3)       central position
**     del         d          radial distance of probe vectors
**
**  Returned:
**     v1,v2,v3    3*d(3)     probe vectors
**
**  This routine returns three vectors surrounding the given one.  The
**  pattern is essentially an equilateral triangle with one vertex in
**  the +z direction;  each probe vector is del radians from v0.  Except
**  for pathological cases, the method does not depend critically on
**  any particular pattern or spacing.
**
**  The probe vectors are intended to be transformed in the user's
**  program to explore the nature of the transformation in the region,
**  the end result being a 3x3 matrix called the "osculating
**  transformation matrix".  The matrix is generated with
**  the routine otm.
*/
/* *INDENT-ON* */
{
    double r, sa, ca, sasb, casb, x, y, z, f;

/* Separation resolved into vertical and horizontal components */
    double dup, ddn, drl;

/* X,Y,Z components of separations */
    double dxup, dyup, dzup, dxdn, dydn, dzdn, dxrl, dyrl;



/* Central vector. */
    x = v0[0];
    y = v0[1];
    z = v0[2];

/* Useful functions. */
    r = sqrt(x * x + y * y);
    if (r >= 1e-10) {
        sa = y / r;
        ca = x / r;
    } else {
        sa = 0.0;
        ca = 1.0;
    }
    sasb = sa * z;
    casb = ca * z;

/* X,Y,Z shifts for generating the three probe vectors. */
    dup = del;
    ddn = del * 0.5;
    drl = del * 0.866;

    dxup = -dup * casb;
    dyup = -dup * sasb;
    dzup = dup * r;

    dxdn = -ddn * casb;
    dydn = -ddn * sasb;
    dzdn = ddn * r;

    dxrl = -drl * sa;
    dyrl = drl * ca;

/* Normalization factor. */
    f = 1.0 - del * del / 2.0;

/* First probe vector: above the true vector. */
    v1[0] = f * (x + dxup);
    v1[1] = f * (y + dyup);
    v1[2] = f * (z + dzup);

/* Second probe vector: down and to the left. */
    v2[0] = f * (x - dxdn - dxrl);
    v2[1] = f * (y - dydn - dyrl);
    v2[2] = f * (z - dzdn);

/* Third probe vector: down and to the right. */
    v3[0] = f * (x - dxdn + dxrl);
    v3[1] = f * (y - dydn + dyrl);
    v3[2] = f * (z - dzdn);
}

static void otm(double v1[3], double v2[3], double v3[3],
                double v1r[3], double v2r[3], double v3r[3],
                double amd[3][3], double amdi[3][3], int *jstat)
/* *INDENT-OFF* */
/*
**  - - - -
**   o t m
**  - - - -
**
**  Solve probe vector samples for the osculating transformation matrix.
**
**  Given:
**     v1,v2,v3      3*d(3)    probe vectors before transformation
**     v1r,v2r,v3r   3*d(3)    probe vectors after transformation
**
**  Returned:
**     amd           d(3,3)    matrix representing transformation
**     amdi          d(3,3)    matrix representing inverse transformation
**     *jstat        i         singularity flag:  0  =  OK
**
**  On the basis of three probe vectors surrounding a small region of
**  interest which have been transformed in some locally smooth way,
**  this routine determines a matrix which describes the three probe
**  transformations exactly and which may therefore be expected to
**  describe other transformations in the same area to some useful
**  degree of approximation.
**
**  The probe vectors can be generated using the routine probev.
**
**  To show how a matrix can be devised that will produce all three
**  of the probe transformations, consider the vectors laid out as
**  three sets of simultaneous equations:
**
**  (Nomenclature:  X1 is v1[0], X1R is v1r[0] etc)
**
**     X1R  =  a*X1 + b*Y1 + c*Z1    }
**     X2R  =  a*X2 + b*Y2 + c*Z2    }-->  a,b,c
**     X3R  =  a*X3 + b*Y3 + c*Z3    }
**
**     Y1R  =  d*X1 + e*Y1 + f*Z1    }
**     Y2R  =  d*X2 + e*Y2 + f*Z2    }-->  d,e,f
**     Y3R  =  d*X3 + e*Y3 + f*Z3    }
**
**     Z1R  =  g*X1 + h*Y1 + i*Z1    }
**     Z2R  =  g*X2 + h*Y2 + i*Z2    }-->  g,h,i
**     Z3R  =  g*X3 + h*Y3 + i*Z3    }
**
**  Note that the matrix of coefficients in each case is the same,
**  and so only one inversion has to be carried out.
**
**  The solutions to these equations can be written out as:
**
**     XR        a  b  c         X
**     YR    =   d  e  f    x    Y
**     ZR        g  h  i         Z
**
**  Thus the relationship between the three probe vectors and their
**  transformations, and to some hopefully useful precision the
**  relationship between any other vector in the region and its
**  transformation, is encapsulated in the matrix, which is called
**  the osculating transformation matrix.
*/
/* *INDENT-ON* */
{
/* Matrix of coefficients */
    double am[3][3];

/* Workspace for matrix copying, inversion etc */
    double v[3], det, wm[3][3];
    int i, j, iw[3];



/* Form the matrix to be inverted. */
    for (i = 0; i < 3; i++) {
        am[0][i] = v1[i];
        am[1][i] = v2[i];
        am[2][i] = v3[i];
    }

/* Invert matrix and solve for x. */
    v[0] = v1r[0];
    v[1] = v2r[0];
    v[2] = v3r[0];
    slaDmat(3, &am[0][0], v, &det, jstat, iw);
    for (i = 0; i < 3; i++)
        amd[0][i] = wm[0][i] = v[i];

/* Solve for y. */
    v[0] = v1r[1];
    v[1] = v2r[1];
    v[2] = v3r[1];
    slaDmxv(am, v, v);
    for (i = 0; i < 3; i++)
        amd[1][i] = wm[1][i] = v[i];

/* Solve for z. */
    v[0] = v1r[2];
    v[1] = v2r[2];
    v[2] = v3r[2];
    slaDmxv(am, v, v);
    for (i = 0; i < 3; i++)
        amd[2][i] = wm[2][i] = v[i];

/* Obtain inverse transformation as well. */
    slaDmat(3, &wm[0][0], v, &det, &j, iw);
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++)
            amdi[i][j] = wm[i][j];
    }
}

static void PartA(FRAMETYPE frame, double target[2],
                  double otm1[3][3],
                  double sst, double cst,
                  double otm2[3][3],
                  double *xu, double *yu, double *zu,
                  double *xa, double *ya, double *za,
                  double *xh, double *yh, double *zh,
                  double *xm, double *ym, double *zm)
/* *INDENT-OFF* */
/*
**  - - - - - -
**   P a r t A
**  - - - - - -
**
**  First part of downstream pointing transformation: spherical version.
**
**  Given:
**     frame         FRAMETYPE     tracking frame ID
**     target        double[2]     target spherical coordinates
**     otm1          double[3][3]  1st osculating transformation matrix
**     sst           double        sine of LAST
**     cst           double        cosine of LAST
**     otm2          double[3][3]  2nd osculating transformation matrix
**
**  Returned:
**     xu,yu,zu      double        target x,y,z
**     xa,ya,za      double        target x,y,z following 1st transformation
**     xh,yh,zh      double        target x,y,z following rotation
**     xm,ym,zm      double        target x,y,z following 2nd transformation
**
**  Notes:
**
**  1  For the usual case of tracking a mean RA/Dec, the arguments
**     have the following meanings:
**
**       frame        FK4 or FK5
**       target       mean RA,Dec, arbitrary equinox, current epoch
**       OTM1         mean to apparent
**       sst,cst      sin, cos LAST
**       OTM2         equatorial to altazimuth
**       xu,yu,zu     current tracking coordinates vector
**       xa,ya,za     geocentric apparent RA,Dec vector
**       xh,yh,zh     geocentric apparent -HA,Dec vector
**       xm,ym,zm     precollimation mount Az,El vector (S thru E)
**
**     and between OTMs 1 and 2 there is a rotation about the z-axis
**     equal to the local apparent sidereal time.
**
**  2  When the tracking coordinates are apparent RA,Dec, the arguments
**     are as follows:
**
**       frame        APPT
**       target       apparent RA,Dec
**       OTM1         identity matrix
**       sst,cst      sin, cos LAST
**       OTM2         equatorial to altazimuth
**       xu,yu,zu     geocentric apparent RA,Dec
**       xa,ya,za     same
**       xh,yh,zh     geocentric apparent -HA,Dec
**       xm,ym,zm     precollimation mount Az,El (S thru E)
**
**     and between OTMs 1 and 2 there is a rotation about the z-axis
**     equal to the local apparent sidereal time.
**
**  3  When the tracking coordinates are topocentric Az,El, the
**     arguments are as follows:
**
**       frame        AZEL_TOPO
**       target       topocentric Az,El (N thru E)
**       OTM1         identity matrix
**       sst,cst      not used
**       OTM2         topocentric to precollimation
**       xu,yu,zu     topocentric Az,El (S thru E)
**       xa,ya,za     same
**       xh,yh,zh     same
**       xm,ym,zm     precollimation mount Az,El (S thru E)
**
**     and between OTMs 1 and 2 there is no rotation.
*/
/* *INDENT-ON* */
{
    double cosb;


/* Current tracking coordinates, spherical to Cartesian. */
    cosb = cos(target[1]);
    *xu = cos(target[0]) * cosb;
    *yu = sin(target[0]) * cosb;
    *zu = sin(target[1]);
    if (frame == AZEL_TOPO) *xu = -*xu;

/* Transformation. */
    PartAv(frame, *xu, *yu, *zu, otm1, sst, cst, otm2,
           xa, ya, za, xh, yh, zh, xm, ym, zm);
}

static void PartAv(FRAMETYPE frame, double x1, double y1, double z1,
                   double otm1[3][3],
                   double s, double c,
                   double otm2[3][3],
                   double *x2, double *y2, double *z2,
                   double *x3, double *y3, double *z3,
                   double *x4, double *y4, double *z4)
/* *INDENT-OFF* */
/*
**  - - - - - - -
**   P a r t A v
**  - - - - - - -
**
**  First part of pointing transformation: Cartesian version.
**
**  Capable of delivering either (i) the tracking frame to
**  precollimation az/el part of the downstream transformation
**  or (ii) the precollimation az/el to tracking frame part of
**  the upstream transformation, depending on which OTMs are
**  supplied in what order, and what direction of rotation is
**  specified.
**
**  Given:
**     frame         FRAMETYPE     tracking frame ID
**     x1,y1,z1      double        target x,y,z
**     otm1          double[3][3]  1st osculating transformation matrix
**     s             double        sine of rotation angle
**     c             double        cosine of rotation angle
**     otm2          double[3][3]  2nd osculating transformation matrix
**
**  Returned:
**     x2,y2,z2      double*       target x,y,z following 1st transformation
**     x3,y3,z3      double*       target x,y,z following rotation
**     x4,y4,z4      double*       target x,y,z following 2nd transformation
*/
/* *INDENT-ON* */
{
/* First transformation. */
    *x2 = otm1[0][0] * x1 + otm1[0][1] * y1 + otm1[0][2] * z1;
    *y2 = otm1[1][0] * x1 + otm1[1][1] * y1 + otm1[1][2] * z1;
    *z2 = otm1[2][0] * x1 + otm1[2][1] * y1 + otm1[2][2] * z1;

/* Rotation. */
    if (frame != AZEL_TOPO) {
       *x3 = c * *x2 + s * *y2;
       *y3 = -s * *x2 + c * *y2;
    } else {
       *x3 = *x2;
       *y3 = *y2;
    }
    *z3 = *z2;

/* Second transformation. */
    *x4 = otm2[0][0] * *x3 + otm2[0][1] * *y3 + otm2[0][2] * *z3;
    *y4 = otm2[1][0] * *x3 + otm2[1][1] * *y3 + otm2[1][2] * *z3;
    *z4 = otm2[2][0] * *x3 + otm2[2][1] * *y3 + otm2[2][2] * *z3;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsEFastLoop
 *
 *   Purpose:
 *   The TCS fast loop.
 *
 *   Description:
 *   This code implements the fast loop of the Gemini TCS.
 *   It is expected to be called at 20Hz as an EPICS subroutine record.
 *   For engineering /test purposes, a switch is provided to allow toggling
 *   between using the time stamped position and velocity of the rotator
 *   or simply the raw current position of the rotator. The default is
 *   to use the time stamped position and this should always be the operational
 *   configuration. If the raw position is used, proper tracking won't be 
 *   maintained.
 *
 *   Invocation:
 *   tcsEFastLoop(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub record
 *
 *   EPICS inputs:
 *
 *   a => Time stamped position and velocity of rotator 
 *   b => Current position of rotator (degs)
 *   c => Flag to toggle between using time stamped or current posn
 *   d => Guiding correction to ca (rads)
 *   e => Guiding correction to ce (rads)
 *   f => Optics correction to ca (rads)
 *   g => Optics correction to ce (rads)
 *   h => Probe guide error in "x"
 *   i => Probe guide error in "y"
 *   j => Probe to guide (1 -> 3)
 *   k => debug output flag 0 = no output, 1 = print debug
 *
 *   EPICS outputs:
 *   vala => disable flag for downstream processing
 *   valb => count of bad returns from fast loop
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   tcsFastLoop
 *
 *   Prior requirements:
 *   tcsApplInit, tcsSecProcess, tcsSlowProcess and tcsMediumLoop must have
 *   been called at least once.
 *
 *-
 */
/* *INDENT-ON* */


long tcsEFastLoop(struct genSubRecord *pgsub)
{
    double rma;                 /* rotator position */
    double rmat;                /* time of rotator position */
    double rmav;                /* rotator velocity (rad/s) */
    double ca_guide;            /* guiding correction to ca */
    double ce_guide;            /* guiding correction to ce */
    double caOptics;            /* optics correction to ca */
    double ceOptics;            /* optics correction to ce */
    long wfs;                   /* wave front sensor being guided */
    double wfserrx;             /* wave front sensor error in x */
    double wfserry;             /* wave front sensor error in y */
    double crArray[3] ;
    double rmCurr ;             /* Current rotator position */
    long   crSwitch ;           /* Switch to use timestamped/current posn */
    static int dbgLevel = DBG_NONE; /* debug level */
    
    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsEFastLooop: Semaphore not created");
        return 0;
    }

/* Pull in the current values of the inputs to the subroutine record. */
    memcpy (crArray, pgsub->a, 3 * sizeof (double)) ;
    rmat = crArray[0];
    rma  = crArray[1] * D2R;
    rmav = crArray[2] * D2R;
    rmCurr = *(double *)pgsub->b;
    crSwitch = *(long *)pgsub->c;

/* Possibly over ride time stamped position and velocity */
    if (crSwitch == 1) {
      rma = rmCurr * D2R ;
      rmav = 0.0 ;
    }
    ca_guide = *(double *)pgsub->d;
    ce_guide = *(double *)pgsub->e;
    caOptics = *(double *)pgsub->f;
    ceOptics = *(double *)pgsub->g;
    wfserrx = *(double *)pgsub->h;
    wfserry = *(double *)pgsub->i;
    wfs = *(long *)pgsub->j;

/*  Check for debug output */
    pkdbgwriteflag = atoi(pgsub->k);
    if (pkdbgwriteflag == 1) {
      if (!dbgfp) {
        dbgfp = fopen("tcs.dbg", "w");
        printf("Opening tcs.dbg for writing\n");
      }
    } else {
      if (dbgfp) {
        fclose(dbgfp);
        dbgfp = NULL;
        printf("Closing tcs.dbg\n");
      }
    }
 
/* Set up the appropriate image shift transformations*/
    if (tcsProbeGetGSAOIConfig()) {
      memcpy (T2ao, T2gsaoi, 6*sizeof(double)) ;
      memcpy (Ao2t, Gsaoi2t, 6*sizeof(double)) ;
    } else if (tcsProbeGetAOConfig() ) {
      memcpy (T2ao, T2altair, 6*sizeof(double)) ;
      memcpy (Ao2t, Altair2t, 6*sizeof(double)) ;
    } else {
      memcpy (Ao2t, Default2t, 6*sizeof(double)) ;
      memcpy (T2ao, T2default, 6*sizeof(double)) ;
    }

/* Do all the work in tcsFastLoop. Disable further 20Hz processing if the 
   fast loop returns an error. */
    if (tcsFastLoop(rma, rmat, rmav, ca_guide, ce_guide, caOptics, ceOptics,
       wfs, wfserrx, wfserry, 0 )) {
       *(double *)pgsub->vala = 1.0;
       *(double *)pgsub->valb += 1.0;
    } else {
       *(double *)pgsub->vala = 0.0;
    }
    return 0;
}

int tcsFastLoop ( double rma, double rmat, double rmav, 
                   double ca_guide, double ce_guide, 
                   double caOptics, double ceOptics,
                   long wfs, double wfserrx, double wfserry, long debug)
/* *INDENT-OFF* */
/*
** - - - - - - - - - - - -
**  t c s F a s t L o o p
** - - - - - - - - - - - -
**
** Gemini TCS 20 Hz main pointing routine.
**
** Given:
**    rma         double    achieved rotator orientation at time rmat
**    rmat        double    timestamp for rma and rmav
**    rmav        double    rotator velocity at time rmat
**    ca_guide    double    guiding adjustment to ca
**    ce_guide    double    guiding adjustment to ce
**    caOptics    double    optics adjustment to ca
**    ceOptics    double    optics adjustment to ce
**    wfs         long      Wave front sensor being guided.
**    wfserrx     double    wave front sensor adjustment in x
**    wfserry     double    wave front sensor adjustment in y
**    debug       long      Switch for debug info (use with extreme caution!)
**
** Externally defined:
**
**    STRPS       double    radians of sidereal time per SI second
**    AZEL_TOPO   int       frame ID: topocentric Az/El
**
**    ...plus a large number of items from the EPICS database
**
** D.L.Terrett & P.T.Wallace, RAL   30 January 1997
** with guest appearances by C. J. Mayer, OSL
*/
/* *INDENT-ON* */

/* Tick rate in Hz */
#define TICKHZ 20.0

{

/* Local variables */
/*   int jj ; */
   int i, j, k, ichop, iob, zaa;
   double traw, dtick, dt, dtm[2], xu, yu, zu, xc, yc, zc, 
          xa, ya, za, xh, yh, zh,
          xsm[3], ysm[3], zsm[3], x, y, z, px, py,
          xhi, yhi, zhi, xai, yai, zai, xui, yui, zui, w, pw,
          dx, dy, dz, pdx, pdy, d, pd, xm, ym, zm, rm2, zaf, f, 
          xr, yr, pacnp, maxcol, cpa, spa,
          pa, eta, canpxi, xi, xi2, eta2p1, sdf, r2, r,
          rsq0, r0, sq, cq, canpxi_r, rsq0_r, r0_r,
          xi_r0, eta_r0, xi_s, eta_s, xi_r, eta_r,
          spa_r, cpa_r, x0_r, y0_r, z0_r, xm_r, ym_r, zm_r,
          x_r[2], y_r[2], z_r[2], delta, s[2], n[2],
          xi_mm, eta_mm, xg, yg, zg, a[2], b[2], deltaa, deltab;
   FRAMETYPE frame;

/* Local copies of global variables */
   static double tickprev = 0;
   double tick, tick0, tickl, st, st0, sst, cst, tt, tt0, x0, y0, z0, rm,
          pnpae, vd, ca, ca_net, ce_net, ia_net, ae2mt[3][3],
//          fl, az, el, cvd, xf, yf, zf, paim, ipa, iaa, pa_r, cia, sia, ia, ie,
          fl, az, el, cvd, xf, yf, zf, paim, ipa, pa_r, cia, sia, ia, ie,
          ca_delta, ce_delta, ia_delta, rcorr;
   double applyDeltaT = 0;
   FRAMETYPE m_frame, r_frame, c_frame[2],
             s_frame[3], g1_frame, g2_frame, g3_frame,
             gg1_frame, gg2_frame, gg3_frame, gg4_frame;

   double m_tar_p0[2], m_tar_dt[2], m_tar_t0,
          m_tar_ob[2],
          m_tar_p[2],
          m_por_p0[2],
          m_por_ob[2],
          m_por_p[2];
   double s_tar_p0[3][2], s_tar_dt[3][2], s_tar_t0[3],
          s_tar_ob[3][3][2],
          s_tar_p[3][2], s_tar_pc[3][2],
          s_por_p0[3][2],
          s_por_ob[3][3][2],
          s_por_pc[3][2],
          s_por_p[3][2];
   int c_mode[2];
   double c_xieta[2][2], c_xieta_f[2];
   double g1_tar_p0[2], g1_tar_dt[2], g1_tar_t0,
          g1_tar_ob[3][2],
          g1_tar_p[3][2];
   double g2_tar_p0[2], g2_tar_dt[2], g2_tar_t0,
          g2_tar_ob[3][2],
          g2_tar_p[3][2];
   double g3_tar_p0[2], g3_tar_dt[2], g3_tar_t0,
          g3_tar_ob[3][2],
          g3_tar_p[3][2];
   double gg1_tar_p0[2], gg1_tar_dt[2], gg1_tar_t0,
          gg1_tar_ob[3][2],
          gg1_tar_p[3][2];
   double gg2_tar_p0[2], gg2_tar_dt[2], gg2_tar_t0,
          gg2_tar_ob[3][2],
          gg2_tar_p[3][2];
   double gg3_tar_p0[2], gg3_tar_dt[2], gg3_tar_t0,
          gg3_tar_ob[3][2],
          gg3_tar_p[3][2];
   double gg4_tar_p0[2], gg4_tar_dt[2], gg4_tar_t0,
          gg4_tar_ob[3][2],
          gg4_tar_p[3][2];

   static double g1_xi_mm[3], g1_eta_mm[3];
   static double g2_xi_mm[3], g2_eta_mm[3];
   static double g3_xi_mm[3], g3_eta_mm[3];
   static double gg1_xi_mm[3], gg1_eta_mm[3];
   static double gg2_xi_mm[3], gg2_eta_mm[3];
   static double gg3_xi_mm[3], gg3_eta_mm[3];
   static double gg4_xi_mm[3], gg4_eta_mm[3];
   static double otm1_if[3][3], otm2_if[3][3];
   static double m_otm1[3][3], m_otm2[3][3];
   static double m_otm1_i[3][3], m_otm2_i[3][3];
   static double r_otm1_i[3][3], r_otm2_i[3][3];
   static double c_otm1[2][3][3], c_otm2[2][3][3];
   static double c_otm1_i[2][3][3], c_otm2_i[2][3][3];
   static double s_otm1[3][3][3], s_otm2[3][3][3];
   static double s_otm1_i[3][3][3], s_otm2_i[3][3][3];
   static double g1_otm1_f[3][3][3], g1_otm2_f[3][3][3];
   static double g2_otm1_f[3][3][3], g2_otm2_f[3][3][3];
   static double g3_otm1_f[3][3][3], g3_otm2_f[3][3][3];
   static double gg1_otm1_f[3][3][3], gg1_otm2_f[3][3][3];
   static double gg2_otm1_f[3][3][3], gg2_otm2_f[3][3][3];
   static double gg3_otm1_f[3][3][3], gg3_otm2_f[3][3][3];
   static double gg4_otm1_f[3][3][3], gg4_otm2_f[3][3][3];
   static double g1_otm1_if[3][3][3], g1_otm2_if[3][3][3];
   static double g2_otm1_if[3][3][3], g2_otm2_if[3][3][3];
   static double g3_otm1_if[3][3][3], g3_otm2_if[3][3][3];
   static double gg1_otm1_if[3][3][3], gg1_otm2_if[3][3][3];
   static double gg2_otm1_if[3][3][3], gg2_otm2_if[3][3][3];
   static double gg3_otm1_if[3][3][3], gg3_otm2_if[3][3][3];
   static double gg4_otm1_if[3][3][3], gg4_otm2_if[3][3][3];

   double m2_scan_x[3], m2_scan_y[3];

   double g1_x[3], g1_y[3];
   double g2_x[3], g2_y[3];
   double g3_x[3], g3_y[3];
   double gg1_x[3], gg1_y[3];
   double gg2_x[3], gg2_y[3];
   double gg3_x[3], gg3_y[3];
   double gg4_x[3], gg4_y[3];

   double f1_bw, f1_grab, f1_maxv;
   double f2_w[4], f2_bw, f2_grab, f2_maxv;
   int f1_sc, f2_sc, nod, inPosition, inPosReason;

   double ao2t[6], t2ao[6] ;     /* Optical distortion coefficients */
   double xrpp, yrpp ;           /* Transformed coords */
   double xrob, yrob ;           /* Shift in pointing origin */
   double xcoord, ycoord ;       /* Temporary pointing origins */
   double xcoordpp, ycoordpp ;   /* Transformed pointing origins */
   double o_por[2] ;             /* Shift in PO due to optics */
   double d_r, w_r;
   static int dbgLevel = DBG_NONE; /* debug level */
   double trawold = 0;
   static double tick0old = 0;
   double timeBeforeSem1, timeAfterSem1;
   double timeBeforeSem2, timeAfterSem2;
   double timeAfterSem3;
   double dTimeSem1, dTimeSem2;
   double deltaTraw;
   double deltaTick = 0;
   int corrFlag = 0;


/*------------------------------------------------------------------------*/

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsFastLooop: Semaphore not created");
        return 0;
    }

    timeNow(&timeBeforeSem1);

    epicsMutexLock(TcsSemId);

    timeNow(&timeAfterSem1);
    dTimeSem1 = timeAfterSem1 - timeBeforeSem1;


/*
** Pull in local values of the global data generated elsewhere. This
** routine should run at the highest priority in the TCS application and
** so should not be able to be interrupted by lower priority tasks. Just
** to be on the safe side, however, all access to the global data is
** protected by semaphore, both reading and writing.
*/

    st0 = St0;
    tick0 = Tick0;
    tickl = Tick;
    tt0 = Tt0;
    pnpae = Pnpae;
    ca = Ca;
    vd = Vd;
    ia = Ia;
    ie = Ie;
    for ( i = 0; i < 3; i++ ) {
       for ( j = 0; j < 3; j++ ) {
          ae2mt[i][j] = Ae2mt[i][j];
       }
    }
    ca_delta = Ca_delta;
    ce_delta = Ce_delta;
    ia_delta = Ia_delta;
    paim = Paim;
    ipa = Ipa;
//    iaa = Iaa;
    sia = Sia;
    cia = Cia;
    az = Az;

    m_tar_t0 = M_tar_t0;
    for (i = 0; i < 2; i++) {
        m_tar_p0[i] = M_tar_p0[i];
        m_tar_dt[i] = M_tar_dt[i];
        m_tar_ob[i] = M_tar_ob[i];
        m_por_p0[i] = M_por_p0[i];
        m_por_ob[i] = M_por_ob[i];
    }
    m_frame = M_frame;
    r_frame = R_frame;
    for (ichop = 1; ichop < 3; ichop++) {
        i = ichop - 1;
        c_frame[i] = C_frame[i];
        c_mode[i] = C_mode[i];
        for (j = 0; j < 2; j++)
            c_xieta[i][j] = C_xieta[i][j];
        c_xieta_f[i] = C_xieta_f[i];
    }
    for (ichop = 0; ichop < 3; ichop++) {
        s_frame[ichop] = S_frame[ichop];
        s_tar_t0[ichop] = S_tar_t0[ichop];
        for (j = 0; j < 2; j++) {
            s_tar_p0[ichop][j] = S_tar_p0[ichop][j];
            s_tar_pc[ichop][j] = S_tar_pc[ichop][j];
            s_tar_dt[ichop][j] = S_tar_dt[ichop][j];
            s_por_p0[ichop][j] = S_por_p0[ichop][j];
            s_por_pc[ichop][j] = S_por_pc[ichop][j];
            g1_tar_ob[ichop][j] = G1_tar_ob[ichop][j];
            g2_tar_ob[ichop][j] = G2_tar_ob[ichop][j];
            g3_tar_ob[ichop][j] = G3_tar_ob[ichop][j];
            gg1_tar_ob[ichop][j] = GG1_tar_ob[ichop][j];
            gg2_tar_ob[ichop][j] = GG2_tar_ob[ichop][j];
            gg3_tar_ob[ichop][j] = GG3_tar_ob[ichop][j];
            gg4_tar_ob[ichop][j] = GG4_tar_ob[ichop][j];
        }
        for (j = 0; j < 3; j++) {
            s_tar_ob[ichop][j][0] = S_tar_ob[ichop][j][0];
            s_tar_ob[ichop][j][1] = S_tar_ob[ichop][j][1];
            s_por_ob[ichop][j][0] = S_por_ob[ichop][j][0];
            s_por_ob[ichop][j][1] = S_por_ob[ichop][j][1];
        }
    }
    g1_frame = G1_frame;
    g2_frame = G2_frame;
    g3_frame = G3_frame;
    gg1_frame = GG1_frame;
    gg2_frame = GG2_frame;
    gg3_frame = GG3_frame;
    gg4_frame = GG4_frame;
    g1_tar_t0 = G1_tar_t0;
    g2_tar_t0 = G2_tar_t0;
    g3_tar_t0 = G3_tar_t0;
    gg1_tar_t0 = GG1_tar_t0;
    gg2_tar_t0 = GG2_tar_t0;
    gg3_tar_t0 = GG3_tar_t0;
    gg4_tar_t0 = GG4_tar_t0;
    for (j = 0; j < 2; j++) {
        g1_tar_p0[j] = G1_tar_p0[j];
        g1_tar_dt[j] = G1_tar_dt[j];
        g2_tar_p0[j] = G2_tar_p0[j];
        g2_tar_dt[j] = G2_tar_dt[j];
        g3_tar_p0[j] = G3_tar_p0[j];
        g3_tar_dt[j] = G3_tar_dt[j];
        gg1_tar_p0[j] = GG1_tar_p0[j];
        gg1_tar_dt[j] = GG1_tar_dt[j];
        gg2_tar_p0[j] = GG2_tar_p0[j];
        gg2_tar_dt[j] = GG2_tar_dt[j];
        gg3_tar_p0[j] = GG3_tar_p0[j];
        gg3_tar_dt[j] = GG3_tar_dt[j];
        gg4_tar_p0[j] = GG4_tar_p0[j];
        gg4_tar_dt[j] = GG4_tar_dt[j];
    }

    for (ichop = 0; ichop < 4; ichop++) {
        f2_w[ichop] = F2_w[ichop];
    }
    f1_bw = F1_bw;
    f1_maxv = F1_maxv;
    f1_grab = F1_grab;
    f1_sc = F1_sc;
    f2_bw = F2_bw;
    f2_maxv = F2_maxv;
    f2_grab = F2_grab;
    f2_sc = F2_sc;
    nod = Nod;

    for (j = 0; j < 3; j++) {
        for (k = 0; k < 3; k++) {
            m_otm1[j][k] = M_otm1[j][k];
            m_otm2[j][k] = M_otm2[j][k];
            m_otm1_i[j][k] = M_otm1_i[j][k];
            m_otm2_i[j][k] = M_otm2_i[j][k];
            r_otm1_i[j][k] = R_otm1_i[j][k];
            r_otm2_i[j][k] = R_otm2_i[j][k];
        }
    }

    for (ichop = 1; ichop < 3; ichop++) {
        i = ichop - 1;
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                c_otm1[i][j][k] = C_otm1[i][j][k];
                c_otm2[i][j][k] = C_otm2[i][j][k];
                c_otm1_i[i][j][k] = C_otm1_i[i][j][k];
                c_otm2_i[i][j][k] = C_otm2_i[i][j][k];
            }
        }
    }

    for (ichop = 0; ichop < 3; ichop++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                s_otm1[ichop][j][k] = S_otm1[ichop][j][k];
                s_otm2[ichop][j][k] = S_otm2[ichop][j][k];
                s_otm1_i[ichop][j][k] = S_otm1_i[ichop][j][k];
                s_otm2_i[ichop][j][k] = S_otm2_i[ichop][j][k];
                g1_otm1_f[ichop][j][k] = G1_otm1[ichop][j][k];
                g1_otm2_f[ichop][j][k] = G1_otm2[ichop][j][k];
                g2_otm1_f[ichop][j][k] = G2_otm1[ichop][j][k];
                g2_otm2_f[ichop][j][k] = G2_otm2[ichop][j][k];
                g3_otm1_f[ichop][j][k] = G3_otm1[ichop][j][k];
                g3_otm2_f[ichop][j][k] = G3_otm2[ichop][j][k];
                g1_otm1_if[ichop][j][k] = G1_otm1_i[ichop][j][k];
                g1_otm2_if[ichop][j][k] = G1_otm2_i[ichop][j][k];
                g2_otm1_if[ichop][j][k] = G2_otm1_i[ichop][j][k];
                g2_otm2_if[ichop][j][k] = G2_otm2_i[ichop][j][k];
                g3_otm1_if[ichop][j][k] = G3_otm1_i[ichop][j][k];
                g3_otm2_if[ichop][j][k] = G3_otm2_i[ichop][j][k];
                gg1_otm1_f[ichop][j][k] = GG1_otm1[ichop][j][k];
                gg1_otm2_f[ichop][j][k] = GG1_otm2[ichop][j][k];
                gg2_otm1_f[ichop][j][k] = GG2_otm1[ichop][j][k];
                gg2_otm2_f[ichop][j][k] = GG2_otm2[ichop][j][k];
                gg3_otm1_f[ichop][j][k] = GG3_otm1[ichop][j][k];
                gg3_otm2_f[ichop][j][k] = GG3_otm2[ichop][j][k];
                gg4_otm1_f[ichop][j][k] = GG4_otm1[ichop][j][k];
                gg4_otm2_f[ichop][j][k] = GG4_otm2[ichop][j][k];
                gg1_otm1_if[ichop][j][k] = GG1_otm1_i[ichop][j][k];
                gg1_otm2_if[ichop][j][k] = GG1_otm2_i[ichop][j][k];
                gg2_otm1_if[ichop][j][k] = GG2_otm1_i[ichop][j][k];
                gg2_otm2_if[ichop][j][k] = GG2_otm2_i[ichop][j][k];
 
                gg3_otm1_if[ichop][j][k] = GG3_otm1_i[ichop][j][k];
                gg3_otm2_if[ichop][j][k] = GG3_otm2_i[ichop][j][k];
                gg4_otm1_if[ichop][j][k] = GG4_otm1_i[ichop][j][k];
                gg4_otm2_if[ichop][j][k] = GG4_otm2_i[ichop][j][k];
            }
        }
    }
    for (i = 0; i < 6; i++) {
      ao2t[i] = Ao2t[i] ;
      t2ao[i] = T2ao[i] ;
    }
    for (i = 0; i < 2; i++) {
      o_por[i] = O_por[i] ;
    }
    trawold = Traw;
    epicsMutexUnlock(TcsSemId);
    tcsOpticsGetFl(&fl);
/*===========================================================================*/

/*
**                    ------------------
**                     THE FAST PROCESS
**                    ------------------
**
**      This is the KERNEL of the Gemini TCS pointing system.
*/


/*
** TIME
** ----
*/

/*------------------------------------------------------------*
   Each time the present routine is scheduled, we perform the
   pointing calculations for the next tick.
 *------------------------------------------------------------*/

/* Get the raw TAI (seconds) at this moment. */
    /* (void) timeNow ( &traw ); */


    if ((i = timeNow(&traw)) != 0 ) {
    	printf("tcsFastLoop: timeNow failed with i=%d diff=%f \n",i, (traw - trawold));
    }
    deltaTraw = traw - trawold;
    /* Round up to time of next tick (still raw TAI in seconds). */
    /*tick = floor ( traw * TICKHZ + 1.0 ) / TICKHZ; */

    /* IA 20180605: The above line was commented because of issues with the "floor" function 
     * whereas a drift could be inserted in the generation of the ticks
     */
    tick = tickprev + 0.1;
    applyDeltaT = tick - traw;

    /* The following check corrects the tick in case of a drift between executions of the Fast Loop.
     * If the difference between now and the time the demand needs to be applied 
     * is less than 20 ms or more than 80 ms, then a correction of 50 ms is applied to the current time
     */
    if ( tickprev == 0 ) { 
        tick = traw + 0.05;
    } 
    else if (applyDeltaT < 0.02){ 
        tick = traw + 0.05;
        cnt03++; 
        cnt07++; 
    } 
    else if (applyDeltaT > 0.08){ 
        tick = traw + 0.05;
        cnt03++; 
        cnt08++; 
    }

    if (deltaTraw < 0.05){
        corrFlag = 1;
        cnt06++;
    }

    deltaTick = tick - tickprev;
    tickprev = tick;
    cnt02++;

/* Give up if the time is the same as the last time the fast loop processed. */
    /*if ( tick <= tickl ) cnt06++;   */

/*  The above line was commented out and moved to the very end of the routine 
 *  on 10/02/2011. In order to drive the ODGW the fast loop has to run before
 *  the odgwSetup routine. With the above line where it was the test would
 *  occassionally fail, the fast loop would exit and the new ODGW demands
 *  resulting from a handset offset etc. would not be calculated.
 *  By moving the check to the end of the routine. The code always runs
 *  but the return status still disables downstream record processing
 * so we don't get duplicated demands to the mount, rotator etc.
 */

/* Time of next tick relative to reference time (seconds). */
    dtick = tick - tick0;

/* IA: The following block is for debugging purposes. It helps observe the interaction with the Slow Process */
    if (tick0 != tick0old){
        tick0v = tick0;
        dtickv = dtick;
    }
    tick0old = tick0;
/* End of debug block */

/* Local Apparent Sidereal Time (radians), and functions. */
    st = st0 + dtick * STRPS;
    sst = sin ( st );
    cst = cos ( st );

/* Terrestrial Time (MJD). */
    tt = tt0 + dtick / 86400.0;

/* Adjust filter bandwidths and maximum velocities from Hz to "per
    interval since last tick" */
    f1_bw *= tick - tickl;
    f1_maxv *= tick - tickl;
    f2_bw *= tick - tickl;
    f2_maxv *= tick - tickl;

/* Assume we are "in position" */
    inPosition = 1;
    inPosReason = IPR_INPOSITION;

/*
** SOURCE TARGETS to PRECOLLIMATION Az/El
** --------------------------------------
*/

/* Chop state A differential tracking. */
    dt = tt - s_tar_t0[0];
    for (i = 0; i < 2; i++) {
        s_tar_p[0][i] = s_tar_p0[0][i] + dt * s_tar_dt[0][i];

/* Chop state A: offsets from base. */
        s_por_p[0][i] = s_por_p0[0][i];
        for (iob = 0; iob < 3; iob++) {
            s_tar_p[0][i] += s_tar_ob[0][iob][i];
            s_por_p[0][i] += s_por_ob[0][iob][i];
        }
        s_por_p[0][i] += o_por[i] ;
    }
    /*
    if (pkdbgwriteflag) {
      fprintf(dbgfp, "%18.9f %16.10f %16.10f\n", tt-66.184/86400.0+2400000.5,
              s_tar_p[0][0]*DR2H,
              s_tar_p[0][1]*DR2D ) ;
    }
    */

/* Chop state A tracking coordinates to pre-collimation Az/El. */
    PartA ( s_frame[0], s_tar_p[0],
            s_otm1[0], sst, cst, s_otm2[0],
            &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
            &xsm[0], &ysm[0], &zsm[0] );

/* Chop states B and C. */
    for (ichop = 1; ichop < 3; ichop++) {

    /* Is the B or C chop "absolute" or "relative"? */
        k = ichop - 1;
        if ( c_mode[k] ) {

        /* "Relative" chopping is enabled: we will use the    */
        /* specified chop throw to generate a new B/C target. */

        /* Source A pre-collimation Az/El to B/C chop frame. */
            PartAv ( c_frame[k], xsm[0], ysm[0], zsm[0],
                     c_otm2_i[k], -sst, cst, c_otm1_i[k],
                     &xh, &yh, &zh, &xa, &ya, &za,
                     &x, &y, &z );

        /* Apply the throw to give Source B/C in B/C chop frame. */
            xi = c_xieta[k][0];
            eta = c_xieta[k][1];
            f = c_xieta_f[k];
            r = sqrt ( x * x + y * y );
            if ( r == 0.0 ) {
                r = TINY;
                x = r;
            }
            xu = ( x - ( xi * y + eta * x * z ) / r ) / f;
            yu = ( y + ( xi * x - eta * y * z ) / r ) / f;
            zu = ( z + eta * r ) / f;

        /* To pre-collimation Az/El. */
            PartAv ( c_frame[k], xu, yu, zu,
                     c_otm1[k], sst, cst, c_otm2[k],
                     &xa, &ya, &za, &xh, &yh, &zh,
                     &xm, &ym, &zm );

        /* To Source B/C tracking coordinates. */
            PartAv ( s_frame[ichop], xm, ym, zm,
                     s_otm2_i[ichop], -sst, cst, s_otm1_i[ichop],
                     &xh, &yh, &zh, &xa, &ya, &za,
                     &xu, &yu, &zu );
            s_tar_p0[ichop][0] =
                atan2 ( yu,  s_frame[ichop] == AZEL_TOPO ? -xu : xu );
            s_tar_p0[ichop][1] =
                atan2 ( zu, sqrt ( xu * xu + yu * yu ) );

        /* Chop states B & C: no differential tracking or target offsets
           while relative chopping. */
            s_tar_p[ichop][0] = s_tar_p0[ichop][0];
            s_tar_p[ichop][1] = s_tar_p0[ichop][1];
        } else {

        /* Chop states B & C: differential tracking (absolute chopping only). */
            dt = tt - s_tar_t0[ichop];
            for (i = 0; i < 2; i++) {
                s_tar_p[ichop][i] = dt * s_tar_dt[ichop][i];

            /* Chop states B & C: target offsets from base. */
                for (iob = 0; iob < 3; iob++) {
                    s_tar_p[ichop][i] += s_tar_ob[ichop][iob][i];
                }
                s_tar_p[ichop][i] += s_tar_p0[ichop][i];
            }
        }

    /* Chop states B & C: pointing origin offsets from base. */
        for (i = 0; i < 2; i++) {
            s_por_p[ichop][i] = s_por_p0[ichop][i];
            for (iob = 0; iob < 3; iob++) {
                s_por_p[ichop][i] += s_por_ob[ichop][iob][i];
            }
            s_por_p[ichop][i] += o_por[i] ;
        }
    }

/* For all three chop states. */
    for (ichop = 0; ichop < 3; ichop++) {

    /*
    ** FILTER 1 target
    ** ---------------
    **
    ** Filter the target position into the current target position.
    */

    /* Target, Cartesian. */
        w = cos ( s_tar_p[ichop][1] );
        xu = cos ( s_tar_p[ichop][0] ) * w;
        yu = sin ( s_tar_p[ichop][0] ) * w;
        zu = sin ( s_tar_p[ichop][1] );
        if (s_frame[ichop] == AZEL_TOPO) xu = -xu;

    /* Current target, Cartesian. */
        w = cos ( s_tar_pc[ichop][1] );
        xc = cos ( s_tar_pc[ichop][0] ) * w;
        yc = sin ( s_tar_pc[ichop][0] ) * w;
        zc = sin ( s_tar_pc[ichop][1] );
        if (s_frame[ichop] == AZEL_TOPO) xc = -xc;

    /* Pull the current target towards the net source target. */

    /* Determine total distance left to go. */
        dx = xu - xc;
        dy = yu - yc;
        dz = zu - zc;
        w = sqrt ( dx * dx + dy * dy + dz * dz );

    /* Pull the current pointing origin towards the net source pointing
       origin. */

    /* Determine total distance left to go. */
        pdx = s_por_p[ichop][0] - s_por_pc[ichop][0];
        pdy = s_por_p[ichop][1] - s_por_pc[ichop][1];
        pw = sqrt ( pdx * pdx + pdy * pdy );

    /* Catchup forced? */
        if ( f1_sc > 0) {

        /* Yes!  Prepare to go all the way. */
            d = w;
            pd = pw;

        } else {

        /* Source almost there? */
            if ( w < f1_grab ) {

            /* Yes!  Prepare to go all the way. */
                d = w;

            } else {

            /* No.  Prepare to go a fraction of the way there. */
                d = w * f1_bw;

            /* Limit the increment to the maximum allowed. */
                d = d < f1_maxv ? d : f1_maxv;

            /* Not in position yet */
                inPosition = 0;
                inPosReason = IPR_TARFILT;
            }

        /* Pointing origin almost there? */
            if ( pw < f1_grab * fl ) {

            /* Yes! Prepare to go all the way. */
               pd = pw;

            } else {

            /* No. Prepare to go a fraction of the way there. */
               pd = pw * f1_bw;

            /* Limit the increment to the maximum allowed. */
               pd = pd < f1_maxv * fl ? pd : f1_maxv * fl;

            /* Not in position yet */
                inPosition = 0;
                inPosReason = IPR_TARFILT;
            }
        }

    /* Net fraction of the total distance to go. */
        w = w > 0.0 ? d / w : 1.0;
        w = w <= 1.0 ? w : 1.0;
        pw = pw > 0.0 ? pd / pw : 1.0;
        pw = pw <= 1.0 ? pw : 1.0;

    /* Add the increment. */
        xc += dx * w;
        yc += dy * w;
        zc += dz * w;

    /* To spherical, becoming the new base target. */
        s_tar_pc[ichop][0] = slaDranrm (
              xc <= TINY && xc >= -TINY && yc <= TINY && yc >= -TINY ?
              s_tar_pc[ichop][0] :
              atan2 ( yc, s_frame[ichop] == AZEL_TOPO ? -xc : xc ) );
        s_tar_pc[ichop][1] = atan2 ( zc, sqrt ( xc * xc + yc * yc ) );

    /* Tracking coordinates to pre-collimation Az/El. */
        PartA ( s_frame[ichop], s_tar_pc[ichop],
                s_otm1[ichop], sst, cst, s_otm2[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &xsm[ichop], &ysm[ichop], &zsm[ichop] );

/* Add the increment to the current pointing origin. */
        s_por_pc[ichop][0] += pdx * pw;
        s_por_pc[ichop][1] += pdy * pw;
    }

/* Reset the filter flag to indicate that the first pass has happened. */
    if ( f1_sc == 2 ) f1_sc = -2;
    else if ( f1_sc == 3 ) f1_sc = 0;

/*
** CALCULATE MOUNT DIFFERENTIAL TRACKING
** -------------------------------------
**
** The differential tracking adjustments are needed twice;
** once as the mount input to Filter 2 and once when the
** differential rates are applied.
*/
    dt = tt - m_tar_t0;
    for (i = 0; i < 2; i++)
       dtm[i] = dt * m_tar_dt[i];

/*
** FILTER 2
** --------
**
** Transform the three precollimation Az/Els to the mount
** tracking frame, and accumulate the weighted sum.  Then
** feed the resulting vector into into the mount target.
**
** Form a weighted average of the A, B, C pointing-origins and
** blend into the mount pointing origin.
**
** n.b.  This routine assumes that the weights are positive and
**       sum to unity.  No further validation is performed here.
*/

/* Initialize the Filter 2 input vector, the weighted */
/* combination of the three source targets.           */
    x = 0.0;
    y = 0.0;
    z = 0.0;

/* Initialize the Filter 2 input x/y, the weighted combination */
/* of the three source pointing origins.                       */
    px = 0.0;
    py = 0.0;

/* 3 chop states. */
    for (ichop = 0; ichop < 3; ichop++) {

    /* Source target to mount tracking frame. */
        PartAv ( m_frame, xsm[ichop], ysm[ichop], zsm[ichop],
                 m_otm2_i, -sst, cst, m_otm1_i,
                 &xhi, &yhi, &zhi, &xai, &yai, &zai, &xui, &yui, &zui );

    /* Accumulate the contribution from this source target. */
        w = f2_w[ichop];
        if ( ichop == nod ) w += f2_w[3];
        x += w * xui;
        y += w * yui;
        z += w * zui;

    /* Accumulate the contribution from this pointing origin. */
        px += w * s_por_pc[ichop][0];
        py += w * s_por_pc[ichop][1];
    }

/* Mount base target, Cartesian. */
    w = cos ( m_tar_p0[1] + dtm[1] );
    xu = cos ( m_tar_p0[0] + dtm[0] ) * w;
    yu = sin ( m_tar_p0[0] + dtm[0] ) * w;
    zu = sin ( m_tar_p0[1] + dtm[1] );
    if (m_frame == AZEL_TOPO) xu = -xu;

/* Form the normalized Filter 2 input vector. */
    w = x * x + y * y + z * z;
    if ( w != 0.0 ) {

    /* Normal case: normalize the accumulated vector. */
        w = sqrt ( w );
        x /= w;
        y /= w;
        z /= w;

    } else {

    /* Null result: use current mount coordinates. */
        x = xu;
        y = yu;
        z = zu;
    }

/* Pull the mount target towards the net source target. */

/* Determine total distance left to go. */
    dx = x - xu;
    dy = y - yu;
    dz = z - zu;
    w = sqrt ( dx * dx + dy * dy + dz * dz );

/* Pull the mount pointing origin towards the net */
/* source pointing origin.                        */

/* Determine total distance left to go. */
    pdx = px - m_por_p0[0];
    pdy = py - m_por_p0[1];
    pw = sqrt ( pdx * pdx + pdy * pdy );

/* Catchup forced? */
    if ( f2_sc > 0) {

    /* Yes!  Prepare to go all the way, and clear the flag. */
        d = w;
        pd = pw;
        if ( f2_sc == 2 ) f2_sc = -2;
        else if ( f2_sc == 3 ) f2_sc = 0;

    } else {

    /* Source almost there? */
        if ( w < f2_grab ) {

        /* Yes!  Prepare to go all the way. */
            d = w;

        } else {

        /* No.  Prepare to go a fraction of the way there. */
            d = w * f2_bw;

        /* Limit the increment to the maximum allowed. */
            d = d < f2_maxv ? d : f2_maxv;
        }

    /* Pointing origin almost there? */
        if ( pw < f2_grab * fl ) {

        /* Yes!  Prepare to go all the way. */
            pd = pw;

        } else {

        /* No.  Prepare to go a fraction of the way there. */
            pd = pw * f2_bw;

        /* Limit the increment to the maximum allowed. */
            pd = pd < f2_maxv * fl ? pd : f2_maxv * fl;
        }
    }

/* Net fraction of the total distance to go. */
    w = w > 0.0 ? d / w : 1.0;
    w = w <= 1.0 ? w : 1.0;
    pw = pw > 0.0 ? pd / pw : 1.0;
    pw = pw <= 1.0 ? pw : 1.0;

/* Add the increment. */
    xu += dx * w;
    yu += dy * w;
    zu += dz * w;

/* To spherical, becoming the new base target. */
    m_tar_p[0] = slaDranrm (
           xu <= TINY && xu >= -TINY && yu <= TINY && yu >= -TINY ?
           m_tar_p0[0] + dtm[0] :
           atan2 ( yu, m_frame == AZEL_TOPO ? -xu : xu ) );
    m_tar_p[1] = atan2 ( zu, sqrt ( xu * xu + yu * yu ) );

/* Add the increment to the base pointing origin. */
    m_por_p0[0] += pdx * pw;
    m_por_p0[1] += pdy * pw;

/*
** MOUNT TARGET to Az/El
** ---------------------
**
** The algorithm predicts three versions of the mount az/el:
**
**    x0, y0, z0     Cartesian, pre-tube-flexure
**    xf, yf, zf     Cartesian, post-tube-flexure
**    az, el         spherical (N=0, E=90), final
**
** In addition, the following rotator predictions are made:
**
**    pa             rotator angle, corrected for az/el nonperp
**    spa, cpa       sine and cosine of pa
*/

/* Update base target and add offset from base to net target and
    pointing origin. */
    for (i = 0; i < 2; i++) {
        m_tar_p0[i] = m_tar_p[i] - dtm[i];
        m_tar_p[i] += m_tar_ob[i];
        m_por_p[i] = m_por_p0[i] + m_por_ob[i] ;
        if (pw != 0) m_por_p[i] -= o_por[i];
    }

/* Current mount tracking coordinates to pre-collimation Az/El. */
    PartA ( m_frame, m_tar_p, m_otm1, sst, cst, m_otm2,
            &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh, &xm, &ym, &zm );

/* Cos(El). */
    rm2 = xm * xm + ym * ym;
    rm = sqrt ( rm2 );

/* Pointing origin position wrt rotator axis, natural units. */
    xr = m_por_p[0] / fl;
    yr = m_por_p[1] / fl;

/* Allow for distortion of focal plane due to AO  optics. Compute the 
*  position in the focal plane that will map to xr, yr when AO is
*  in the beam.
*/
    xrpp = ao2t[0] / fl + xr * ao2t[1] + yr * ao2t[2];
    yrpp = ao2t[3] / fl + xr * ao2t[4] + yr * ao2t[5];

/* Save the extra offset for later use. Note that to preserve the layout and
*  structure of the previous code. The offset is calculated here but not 
*  applied until the next cycle. This delays the application of the distortion
*  corrections for 0.05s but ensures consistent data is used to calculate M2
*  tip/tilt
*/
    xrob = xrpp - xr ;
    yrob = yrpp - yr ;

    m_por_p[0] += o_por[0] ;
    m_por_p[1] += o_por[1] ;
    xr += o_por[0]/fl ;
    yr += o_por[1]/fl ;

/* Apply guiding and optics corrections to ca and ce. */
    ca_net = ca + ca_delta + ca_guide + caOptics;
    ce_net = ce_delta + ce_guide + ceOptics;
    ia_net = ia + ia_delta;

/* Predicted rotator angle at next tick. */
    rma += ( tick - rmat ) * rmav;

/* Rotator angle, corrected for az/el nonperpendicularity. */
    pacnp = pnpae * rm;
    pa = rma + pacnp;
    spa = sin ( pa );
    cpa = cos ( pa );

/* Check for too close to the zenith. */
    maxcol = sqrt ( xr * xr + yr * yr ) +
        sqrt ( ca_net * ca_net + ( ce_net + pnpae ) * 
               ( ce_net + pnpae) ) + TINY;
    zaa = maxcol > rm;
    if ( zaa ) {
        zaf = rm / maxcol;
        inPosition = 0;
        inPosReason = IPR_ZENITH;
    } else {
        zaf = 1.0;
    }

/* Scale collimation to avoid awkward zenith region. */
    xr *= zaf;
    yr *= zaf;
    ca_net *= zaf;
    ce_net *= zaf;
    pnpae *= zaf;

/* Pointing origin position wrt ideal axis. */
    eta = xr * spa - yr * cpa + ce_net;
    canpxi = ca_net + pnpae * ( zm - eta * rm );
    xi = - xr * cpa - yr * spa + canpxi;

/* Apply complete collimation correction. */
    xi2 = xi * xi;
    eta2p1 = eta * eta + 1.0;
    sdf = zm * sqrt ( xi2 + eta2p1 );
    r2 = rm2 * eta2p1 - zm * zm * xi2;
    r2 = r2 < TINY * TINY ? TINY * TINY : r2;
    r = sqrt ( r2 );
    f = ( sdf * eta + r ) / ( eta2p1 * rm * sqrt ( r2 + xi2 ) );
    x0 = f * ( xm * r + ym * xi );
    y0 = f * ( ym * r - xm * xi );
    z0 = ( sdf - eta * r ) / eta2p1;

/* Vertical deflection (tube flexure etc). */

/* First rotate the mount coordinates into [Az,El]. */
   x = ae2mt[0][0] * x0 + ae2mt[1][0] * y0 + ae2mt[2][0] * z0;
   y = ae2mt[0][1] * x0 + ae2mt[1][1] * y0 + ae2mt[2][1] * z0;
   z = ae2mt[0][2] * x0 + ae2mt[1][2] * y0 + ae2mt[2][2] * z0;

/* Now apply the vertical deflection. */
   if ( ( r = sqrt ( x * x + y * y ) ) > 0.0 ) {
      cvd = 1.0 - vd * vd / 2.0;
      f = cvd - vd * z / r;
      x *= f;
      y *= f;
      z = z * cvd + vd * r;
   }

/* Finally rotate the [Az,El] back into mount coordinates. */
   xf = ae2mt[0][0] * x + ae2mt[0][1] * y + ae2mt[0][2] * z;
   yf = ae2mt[1][0] * x + ae2mt[1][1] * y + ae2mt[1][2] * z;
   zf = ae2mt[2][0] * x + ae2mt[2][1] * y + ae2mt[2][2] * z;

/* Mount azimuth (N thu E, 0-2pi) and elevation, including index errors. */
   az = ( xf == 0.0 && yf == 0.0 ) ? 0.0 : atan2 ( yf, -xf );
   az += ia_net;
   az = slaDranrm( az );
   el = atan2( zf, sqrt ( xf * xf + yf * yf ) );
   el -= ie;

/* Avoid the zenith. */
    rsq0 = x0 * x0 + y0 * y0;
    if ( rsq0 != 0.0 ) {
        r0 = sqrt ( rsq0 );
    } else {
        r0 = x0 = TINY;
    }

/* Needed for later: rotator axis position with respect to */
/* ideal axis, for neutral M2 tip/tilt.                    */
    xi_r0 = ca_net + pnpae * z0;
    eta_r0 = ce_net;

/*
** FIELD ORIENTATION
** -----------------
*/

/* Rotator angle: latest demand, corrected for az/el nonperp. */
    pacnp = pnpae * rm;
    pa_r = paim + pacnp;
    spa_r = sin ( pa_r );
    cpa_r = cos ( pa_r );

/* Pointing origin position wrt ideal axis. */
    eta_r = xr * spa_r - yr * cpa_r + ce_net;
    canpxi_r = ca_net + pnpae * ( zm - eta_r * rm );
    xi_r = - xr * cpa_r - yr * spa_r + canpxi_r;

/* Apply complete collimation correction. */
    xi2 = xi_r * xi_r;
    eta2p1 = eta_r * eta_r + 1.0;
    sdf = zm * sqrt ( xi2 + eta2p1 );
    r2 = rm2 * eta2p1 - zm * zm * xi2;
    r2 = r2 < TINY * TINY ? TINY * TINY : r2;
    r = sqrt ( r2 );
    f = ( sdf * eta_r + r ) / ( eta2p1 * rm * sqrt ( r2 + xi2 ) );
    x0_r = f * ( xm * r + ym * xi_r );
    y0_r = f * ( ym * r - xm * xi_r );
    z0_r = ( sdf - eta_r * r ) / eta2p1;

/* Cos(el), heading off zenith problems. */
    rsq0_r = x0_r * x0_r + y0_r * y0_r;
    if ( rsq0_r != 0.0 ) {
       r0_r = sqrt ( rsq0_r );
    } else {
       r0_r = x0_r = TINY;
    }

/* For two points displaced 1mm either side of the pointing origin
   along the Instrument Principal Direction (IPD), the orientation
   of which with respect to the +y direction is the Instrument
   Alignment Angle (IAA), sine and cosine of which are sia, cia. */
    for ( i = 0; i < 2; i++) {

        delta = 1.0 / fl;
        delta *= i ? -1.0 : 1.0;

    /* Displaced pointing-origin position wrt the "ideal axis". */
        xcoord = xr + delta * sia ;
        ycoord = yr + delta * cia ;
    
    /* In presence of distortion, calculate the coordinates that will map
    *  to this position
    */
        xcoordpp = ao2t[0] / fl + xcoord * ao2t[1] + ycoord * ao2t[2] ;
        ycoordpp = ao2t[3] / fl + xcoord * ao2t[4] + ycoord * ao2t[5] ;

        xi_r = - xcoordpp * cpa_r - ycoordpp * spa_r + ca_net + pnpae * zm;
        eta_r = xcoordpp  * spa_r - ycoordpp * cpa_r + ce_net;

    /* Remove complete collimation. */
        f = sqrt ( 1.0 + xi_r * xi_r + eta_r * eta_r );
        xm_r = ( x0_r - ( xi_r * y0_r + eta_r * x0_r * z0_r ) / r0_r ) / f;
        ym_r = ( y0_r + ( xi_r * x0_r - eta_r * y0_r * z0_r ) / r0_r ) / f;
        zm_r = ( z0_r + eta_r * r0_r ) / f;

    /* Pre-collimation position to rotator frame. */
        PartAv ( r_frame, xm_r, ym_r, zm_r,
                 r_otm2_i, -sst, cst, r_otm1_i,
                 &xhi, &yhi, &zhi, &xai, &yai, &zai,
                 &x_r[i], &y_r[i], &z_r[i] );
    }

/* Components of the IPD position-angle with respect to the rotator
   tracking frame. */
    sq = y_r[0] * x_r[1] - x_r[0] * y_r[1];
    cq = z_r[0] * ( x_r[1] * x_r[1] + y_r[1] * y_r[1] ) -
                   z_r[1] * ( x_r[0] * x_r[1] + y_r[0] * y_r[1] );

/* Subtract the requested Instrument Position Angle from the actual
   current IPD position-angle just calculated, and then apply this
   correction to the current rotator angle demand. */
    paim -= ( sq <= TINY && sq >= -TINY && cq <= TINY && cq >= -TINY ?
           0.0 : atan2 ( sq, cq ) ) - ipa;

/* Add correction to compensate for field rotation during a nod caused by
   the science target being in the Nod and not (necessarily) beam A. 
   This calculation has to be done with the chop A and Nod targets in
   the tracking frame of the rotator. */

/* Source A pre-collimation position to rotator frame. */
    PartAv ( r_frame, xsm[0], ysm[0], zsm[0],
             r_otm2_i, -sst, cst, r_otm1_i,
             &xh, &yh, &zh, &xa, &ya, &za,
             &x, &y, &z );

/* To spherical. */
    s[0] = slaDranrm (
           x <= TINY && x >= -TINY && y <= TINY && y >= -TINY ?
           s_tar_p[0][0] : atan2 ( y, x ) );
    s[1] = atan2 ( z, sqrt ( x * x + y * y ) );

/* And for the current nod state source. */
    PartAv ( r_frame, xsm[nod], ysm[nod], zsm[nod],
             r_otm2_i, -sst, cst, r_otm1_i,
             &xh, &yh, &zh, &xa, &ya, &za,
             &x, &y, &z );

/* To spherical. */
    n[0] = slaDranrm (
           x <= TINY && x >= -TINY && y <= TINY && y >= -TINY ?
           s_tar_p[nod][0] : atan2 ( y, x ) );
    n[1] = atan2 ( z, sqrt ( x * x + y * y ) );

    rcorr = 2.0 * atan2 ( sin ( ( s[0] - n[0] ) / 2.0 ) *
            sin ( ( n[1] + s[1] ) / 2.0 ) ,
            cos ( ( s[0] - n[0] ) / 2.0 ) *
            cos ( ( n[1] - s[1] ) / 2.0 ) );
/*
    printf ("Paim, paim, ipa %f %f %f %f %d\n", Paim/D2R, paim/D2R, ipa/D2R, ata
n2(sq,cq)/D2R, r_frame);
*/
    paim = slaDranrm( paim + rcorr );
/*
** SOURCE: PRECOLLIMATION AZ/EL to M2 TIP/TILT, for each of 3 chop states
** ----------------------------------------------------------------------
**
** The algorithm predicts the M2 scan tip/tilts:
**
**      m2_scan_x[ichop]
**      m2_scan_y[ichop]
**
*/

    for (ichop = 0; ichop < 3; ichop++) {

    /* Pick up the source pre-collimation coordinates. */
        x = xsm[ichop];
        y = ysm[ichop];
        z = zsm[ichop];

    /* From these and the mount post-collimation coordinates, */
    /* determine the xi,eta of the source image.              */
        w = x0 * x + y0 * y;
        d = r0 * ( w + z0 * z );
        xi_s = ( y * x0 - x * y0 ) / d;
        eta_s = ( z * rsq0 - z0 * w ) / d;

    /* Source pointing origin position wrt rotator axis, natural units. */
        xr = s_por_pc[ichop][0] / fl;
        yr = s_por_pc[ichop][1] / fl;

    /* Pointing origin position wrt ideal axis. */
        eta = xr * spa - yr * cpa + ce_net;
        xi = - xr * cpa - yr * spa + canpxi;

    /* Subtract the source xi,eta to give the required M2 tip/tilt. */
        m2_scan_x[ichop] = zaa ? 0.0 : xi - xi_s;
        m2_scan_y[ichop] = zaa ? 0.0 : eta - eta_s;
    }

/*
** TARGET to X/Y for the GUIDERS, for each of 3 chop states
** ----------------------------------------------------------
**
** The algorithm predicts the guidestar x/y coordinates,
** in millimetres and with respect to the rotator axis,
** but in the non-rotating focal plane:
**
**      g1_xi_mm[ichop], g1_eta_mm[ichop]
**      g2_xi_mm[ichop], g2_eta_mm[ichop]
**      g3_xi_mm[ichop], g3_eta_mm[ichop] etc.
*/

    for (ichop = 0; ichop < 3; ichop++) {

    /* Allow for the current M2 tip/tilt. */
        xi_r = xi_r0 - m2_scan_x[ichop];
        eta_r = eta_r0 - m2_scan_y[ichop];

    /*
    ** -------
    ** PWFS #1
    ** -------
    */


    /* Differential tracking and offsets from base. */
        dt = tt - g1_tar_t0;
        for (i = 0; i < 2; i++) {
            g1_tar_p[ichop][i] = g1_tar_p0[i] +
                                 ( dt * g1_tar_dt[i] +
                                        g1_tar_ob[ichop][i] );
        }

    /* Guidestar sky coordinates to pre-collimation Az/El. */
        PartA ( g1_frame, g1_tar_p[ichop],
                g1_otm1_f[ichop], sst, cst, g1_otm2_f[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &x, &y, &z );

    /* From the pre-tube-flexure mount coordinates and the  */
    /* guidestar pre-collimation coordinates, determine the */
    /* xi,eta of the guidestar image.                       */
        w = x * x0 + y * y0;
        d = w + z * z0;
        if ( d > 0.0 ) {
            if ( d < TINY ) d = TINY;
        } else {
            if ( d > TINY ) d = -TINY;
        }
        d *= r0;

/* Parallel calculations for demand rotator position */
        w_r = x * x0_r + y * y0_r;
        d_r = w_r + z * z0_r;
        if ( d_r > 0.0 ) {
            if ( d_r < TINY ) d_r = TINY;
        } else {
            if ( d_r > TINY ) d_r = -TINY;
        }
        d_r *= r0_r;


    /* Scale and rotate into instrument coordinates. How this is done
       depends on the CRCS follow status. If we're following we use
       the demand. If we're not then we use the current rotator
       position. The consequences of this are
       a) If following - when a rotator slew happens the probe will go
          directly to the new demand. The star will temporarily
          disappear from the wfs and then re-appear when the guide
          probe gets into position
       b) If not following - if we've been tracking a star and we
          stop the rotator the star will stay on the WFS with the
          probe x,y being driven approximately in a circle.
    */
        if (CrcsFollowStat) {
          g1_xi_mm[ichop] = ( ( y * x0_r - x * y0_r ) / d_r - xi_r ) * fl;
          g1_eta_mm[ichop] = ( ( z * rsq0_r - z0_r * w_r ) / d_r - eta_r ) * fl;
          g1_x[ichop] = - g1_xi_mm[ichop] * cpa_r + g1_eta_mm[ichop] * spa_r;
          g1_y[ichop] = - g1_xi_mm[ichop] * spa_r - g1_eta_mm[ichop] * cpa_r;
        } else {
          g1_xi_mm[ichop] = ( ( y * x0 - x * y0 ) / d - xi_r ) * fl;
          g1_eta_mm[ichop] = ( ( z * rsq0 - z0 * w ) / d - eta_r ) * fl;
          g1_x[ichop] = - g1_xi_mm[ichop] * cpa + g1_eta_mm[ichop] * spa;
          g1_y[ichop] = - g1_xi_mm[ichop] * spa - g1_eta_mm[ichop] * cpa;
        }

    /*
    ** -------
    ** PWFS #2
    ** -------
    */

    /* Differential tracking and offsets from base. */
        dt = tt - g2_tar_t0;
        for (i = 0; i < 2; i++)
            g2_tar_p[ichop][i] = g2_tar_p0[i] +
                                 ( dt * g2_tar_dt[i] +
                                        g2_tar_ob[ichop][i] );

    /* Guidestar sky coordinates to pre-collimation Az/El. */
        PartA ( g2_frame, g2_tar_p[ichop],
                g2_otm1_f[ichop], sst, cst, g2_otm2_f[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &x, &y, &z );

    /* From the pre-tube-flexure mount coordinates and the  */
    /* guidestar pre-collimation coordinates, determine the */
    /* xi,eta of the guidestar image.                       */
        w = x * x0 + y * y0;
        d = w + z * z0;
        if ( d > 0.0 ) {
            if ( d < TINY ) d = TINY;
        } else {
            if ( d > TINY ) d = -TINY;
        }
        d *= r0;

/* Parallel calculations for demand rotator position */
        w_r = x * x0_r + y * y0_r;
        d_r = w_r + z * z0_r;
        if ( d_r > 0.0 ) {
            if ( d_r < TINY ) d_r = TINY;
        } else {
            if ( d_r > TINY ) d_r = -TINY;
        }
        d_r *= r0_r;

    /* Scale and rotate into instrument coordinates (see comments for
       probe 1).
    */
        if (CrcsFollowStat) {
          g2_xi_mm[ichop] = ( ( y * x0_r - x * y0_r ) / d_r - xi_r ) * fl;
          g2_eta_mm[ichop] = ( ( z * rsq0_r - z0_r * w_r ) / d_r - eta_r ) * fl;
          g2_x[ichop] = - g2_xi_mm[ichop] * cpa_r + g2_eta_mm[ichop] * spa_r;
          g2_y[ichop] = - g2_xi_mm[ichop] * spa_r - g2_eta_mm[ichop] * cpa_r;
        } else {
          g2_xi_mm[ichop] = ( ( y * x0 - x * y0 ) / d - xi_r ) * fl;
          g2_eta_mm[ichop] = ( ( z * rsq0 - z0 * w ) / d - eta_r ) * fl;
          g2_x[ichop] = - g2_xi_mm[ichop] * cpa + g2_eta_mm[ichop] * spa;
          g2_y[ichop] = - g2_xi_mm[ichop] * spa - g2_eta_mm[ichop] * cpa;
        }


    /*
    ** -----
    ** OIWFS
    ** -----
    */

    /* Differential tracking and offsets from base. */
        dt = tt - g3_tar_t0;
        for (i = 0; i < 2; i++)
            g3_tar_p[ichop][i] = g3_tar_p0[i] +
                                 ( dt * g3_tar_dt[i] +
                                        g3_tar_ob[ichop][i] );

    /* Guidestar sky coordinates to pre-collimation Az/El. */
        PartA ( g3_frame, g3_tar_p[ichop],
                g3_otm1_f[ichop], sst, cst, g3_otm2_f[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &x, &y, &z );

    /* From the pre-tube-flexure mount coordinates and the  */
    /* guidestar pre-collimation coordinates, determine the */
    /* xi,eta of the guidestar image.                       */
        w = x * x0 + y * y0;
        d = w + z * z0;
        if ( d > 0.0 ) {
            if ( d < TINY ) d = TINY;
        } else {
            if ( d > TINY ) d = -TINY;
        }
        d *= r0;

/* Parallel calculations for demand rotator position */
        w_r = x * x0_r + y * y0_r;
        d_r = w_r + z * z0_r;
        if ( d_r > 0.0 ) {
            if ( d_r < TINY ) d_r = TINY;
        } else {
            if ( d_r > TINY ) d_r = -TINY;
        }
        d_r *= r0_r;

    /* Scale and rotate into instrument coordinates. Unlike the
       peripheral WFS the OIWFS is always driven to a position
       based on the demand rotator angle rather than its actual
       value. It is under consideration whether this is
       appropriate for all OIWFS. It is certainly needed for
       GMOS
    */
        g3_xi_mm[ichop] = ( ( y * x0_r - x * y0_r ) / d_r - xi_r ) * fl;
        g3_eta_mm[ichop] = ( ( z * rsq0_r - z0_r * w_r ) / d_r - eta_r ) * fl;
        g3_x[ichop] = - g3_xi_mm[ichop] * cpa_r + g3_eta_mm[ichop] * spa_r;
        g3_y[ichop] = - g3_xi_mm[ichop] * spa_r - g3_eta_mm[ichop] * cpa_r;

    /* The OIWFS is affected by the distortion due to Altair so compute
    *  corrected coords 
    */
        xr = t2ao[0]  + g3_x[ichop] * t2ao[1] + g3_y[ichop] * t2ao[2] ;
        yr = t2ao[3]  + g3_x[ichop] * t2ao[4] + g3_y[ichop] * t2ao[5] ;
        g3_x[ichop] = xr ;
        g3_y[ichop] = yr ;

    /*
    ** -------
    ** GG #1
    ** -------
    */


    /* Differential tracking and offsets from base. */
        dt = tt - gg1_tar_t0;
        for (i = 0; i < 2; i++) {
            gg1_tar_p[ichop][i] = gg1_tar_p0[i] +
                                 ( dt * gg1_tar_dt[i] +
                                        gg1_tar_ob[ichop][i] );
        }

    /* Guidestar sky coordinates to pre-collimation Az/El. */
        PartA ( gg1_frame, gg1_tar_p[ichop],
                gg1_otm1_f[ichop], sst, cst, gg1_otm2_f[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &x, &y, &z );

    /* From the pre-tube-flexure mount coordinates and the  */
    /* guidestar pre-collimation coordinates, determine the */
    /* xi,eta of the guidestar image.                       */
        w = x * x0 + y * y0;
        d = w + z * z0;
        if ( d > 0.0 ) {
            if ( d < TINY ) d = TINY;
        } else {
            if ( d > TINY ) d = -TINY;
        }
        d *= r0;

/* Parallel calculations for demand rotator position */
        w_r = x * x0_r + y * y0_r;
        d_r = w_r + z * z0_r;
        if ( d_r > 0.0 ) {
            if ( d_r < TINY ) d_r = TINY;
        } else {
            if ( d_r > TINY ) d_r = -TINY;
        }
        d_r *= r0_r;


    /* Scale and rotate into instrument coordinates. How this is done
       depends on the CRCS follow status. If we're following we use
       the demand. If we're not then we use the current rotator
       position. The consequences of this are
       a) If following - when a rotator slew happens the probe will go
          directly to the new demand. The star will temporarily
          disappear from the wfs and then re-appear when the guide
          probe gets into position
       b) If not following - if we've been trackig a star and we
          stop the rotator the star will stay on the WFS with the
          probe x,y being driven approximately in a circle.
    */
          gg1_xi_mm[ichop] = ( ( y * x0_r - x * y0_r ) / d_r - xi_r ) * fl;
          gg1_eta_mm[ichop] = ( ( z * rsq0_r - z0_r * w_r ) / d_r - eta_r ) * fl;
          gg1_x[ichop] = - gg1_xi_mm[ichop] * cpa_r + gg1_eta_mm[ichop] * spa_r;
          gg1_y[ichop] = - gg1_xi_mm[ichop] * spa_r - gg1_eta_mm[ichop] * cpa_r;

    /*
    ** -------
    ** GG #2
    ** -------
    */

    /* Differential tracking and offsets from base. */
        dt = tt - gg2_tar_t0;
        for (i = 0; i < 2; i++)
            gg2_tar_p[ichop][i] = gg2_tar_p0[i] +
                                 ( dt * gg2_tar_dt[i] +
                                        gg2_tar_ob[ichop][i] );

    /* Guidestar sky coordinates to pre-collimation Az/El. */
        PartA ( gg2_frame, gg2_tar_p[ichop],
                gg2_otm1_f[ichop], sst, cst, gg2_otm2_f[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &x, &y, &z );

    /* From the pre-tube-flexure mount coordinates and the  */
    /* guidestar pre-collimation coordinates, determine the */
    /* xi,eta of the guidestar image.                       */
        w = x * x0 + y * y0;
        d = w + z * z0;
        if ( d > 0.0 ) {
            if ( d < TINY ) d = TINY;
        } else {
            if ( d > TINY ) d = -TINY;
        }
        d *= r0;

/* Parallel calculations for demand rotator position */
        w_r = x * x0_r + y * y0_r;
        d_r = w_r + z * z0_r;
        if ( d_r > 0.0 ) {
            if ( d_r < TINY ) d_r = TINY;
        } else {
            if ( d_r > TINY ) d_r = -TINY;
        }
        d_r *= r0_r;

    /* Scale and rotate into instrument coordinates (see comments for
       probe 1).
    */
          gg2_xi_mm[ichop] = ( ( y * x0_r - x * y0_r ) / d_r - xi_r ) * fl;
          gg2_eta_mm[ichop] = ( ( z * rsq0_r - z0_r * w_r ) / d_r - eta_r ) * fl;
          gg2_x[ichop] = - gg2_xi_mm[ichop] * cpa_r + gg2_eta_mm[ichop] * spa_r;
          gg2_y[ichop] = - gg2_xi_mm[ichop] * spa_r - gg2_eta_mm[ichop] * cpa_r;

    /*
    ** -------
    ** GG #3
    ** -------
    */

    /* Differential tracking and offsets from base. */
        dt = tt - gg3_tar_t0;
        for (i = 0; i < 2; i++)
            gg3_tar_p[ichop][i] = gg3_tar_p0[i] +
                                 ( dt * gg3_tar_dt[i] +
                                        gg3_tar_ob[ichop][i] );

    /* Guidestar sky coordinates to pre-collimation Az/El. */
        PartA ( gg3_frame, gg3_tar_p[ichop],
                gg3_otm1_f[ichop], sst, cst, gg3_otm2_f[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &x, &y, &z );

    /* From the pre-tube-flexure mount coordinates and the  */
    /* guidestar pre-collimation coordinates, determine the */
    /* xi,eta of the guidestar image.                       */
        w = x * x0 + y * y0;
        d = w + z * z0;
        if ( d > 0.0 ) {
            if ( d < TINY ) d = TINY;
        } else {
            if ( d > TINY ) d = -TINY;
        }
        d *= r0;

/* Parallel calculations for demand rotator position */
        w_r = x * x0_r + y * y0_r;
        d_r = w_r + z * z0_r;
        if ( d_r > 0.0 ) {
            if ( d_r < TINY ) d_r = TINY;
        } else {
            if ( d_r > TINY ) d_r = -TINY;
        }
        d_r *= r0_r;

    /* Scale and rotate into instrument coordinates (see comments for
       probe 1).
    */
          gg3_xi_mm[ichop] = ( ( y * x0_r - x * y0_r ) / d_r - xi_r ) * fl;
          gg3_eta_mm[ichop] = ( ( z * rsq0_r - z0_r * w_r ) / d_r - eta_r ) * fl;
          gg3_x[ichop] = - gg3_xi_mm[ichop] * cpa_r + gg3_eta_mm[ichop] * spa_r;
          gg3_y[ichop] = - gg3_xi_mm[ichop] * spa_r - gg3_eta_mm[ichop] * cpa_r;

    /*
    ** -------
    ** GG #4
    ** -------
    */

    /* Differential tracking and offsets from base. */
        dt = tt - gg4_tar_t0;
        for (i = 0; i < 2; i++)
            gg4_tar_p[ichop][i] = gg4_tar_p0[i] +
                                 ( dt * gg4_tar_dt[i] +
                                        gg4_tar_ob[ichop][i] );

    /* Guidestar sky coordinates to pre-collimation Az/El. */
        PartA ( gg4_frame, gg4_tar_p[ichop],
                gg4_otm1_f[ichop], sst, cst, gg4_otm2_f[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &x, &y, &z );

    /* From the pre-tube-flexure mount coordinates and the  */
    /* guidestar pre-collimation coordinates, determine the */
    /* xi,eta of the guidestar image.                       */
        w = x * x0 + y * y0;
        d = w + z * z0;
        if ( d > 0.0 ) {
            if ( d < TINY ) d = TINY;
        } else {
            if ( d > TINY ) d = -TINY;
        }
        d *= r0;

/* Parallel calculations for demand rotator position */
        w_r = x * x0_r + y * y0_r;
        d_r = w_r + z * z0_r;
        if ( d_r > 0.0 ) {
            if ( d_r < TINY ) d_r = TINY;
        } else {
            if ( d_r > TINY ) d_r = -TINY;
        }
        d_r *= r0_r;

    /* Scale and rotate into instrument coordinates (see comments for
       probe 1).
    */
          gg4_xi_mm[ichop] = ( ( y * x0_r - x * y0_r ) / d_r - xi_r ) * fl;
          gg4_eta_mm[ichop] = ( ( z * rsq0_r - z0_r * w_r ) / d_r - eta_r ) * fl;
          gg4_x[ichop] = - gg4_xi_mm[ichop] * cpa_r + gg4_eta_mm[ichop] * spa_r;
          gg4_y[ichop] = - gg4_xi_mm[ichop] * spa_r - gg4_eta_mm[ichop] * cpa_r;

    }

/* Feedback from wave-front sensor to adjust guide probe target offsets and
   hence centre the guide star on the sensor. */
   xi_mm = 0.0;
   eta_mm = 0.0;
   frame = g1_frame ;
   if (wfs) {
    switch ( wfs ) {
       case 1:

      /* xi and eta of guide probe in chop state 0 */
          xi_mm = g1_xi_mm[0];
          eta_mm = g1_eta_mm[0];

      /* Inverse OTMs and frame. */
          for ( i = 0; i < 3; i++ ) {
             for ( j = 0; j < 3; j++ ) {
                otm1_if[i][j] = g1_otm1_if[0][i][j];
                otm2_if[i][j] = g1_otm2_if[0][i][j];
             }
          }
          frame = g1_frame;
          break;

       case 2:
          xi_mm = g2_xi_mm[0];
          eta_mm = g2_eta_mm[0];
          for ( i = 0; i < 3; i++ ) {
             for ( j = 0; j < 3; j++ ) {
                otm1_if[i][j] = g2_otm1_if[0][i][j];
                otm2_if[i][j] = g2_otm2_if[0][i][j];
              }
          }
          frame = g2_frame;
          break;

       case 3:
          xi_mm = g3_xi_mm[0];
          eta_mm = g3_eta_mm[0];
          for ( i = 0; i < 3; i++ ) {
             for ( j = 0; j < 3; j++ ) {
                otm1_if[i][j] = g3_otm1_if[0][i][j];
                otm2_if[i][j] = g3_otm2_if[0][i][j];
             }
          }
          frame = g3_frame;
          break;

       case 4:
          xi_mm = gg1_xi_mm[0];
          eta_mm = gg1_eta_mm[0];
          for ( i = 0; i < 3; i++ ) {
             for ( j = 0; j < 3; j++ ) {
                otm1_if[i][j] = gg1_otm1_if[0][i][j];
                otm2_if[i][j] = gg1_otm2_if[0][i][j];
              }
          }
          frame = gg1_frame;
          break;

       case 5:
          xi_mm = gg2_xi_mm[0];
          eta_mm = gg2_eta_mm[0];
          for ( i = 0; i < 3; i++ ) {
             for ( j = 0; j < 3; j++ ) {
                 otm1_if[i][j] = gg2_otm1_if[0][i][j];
                otm2_if[i][j] = gg2_otm2_if[0][i][j];
              }
          }
          frame = gg2_frame;
          break;

       case 6:
          xi_mm = gg3_xi_mm[0];
          eta_mm = gg3_eta_mm[0];
          for ( i = 0; i < 3; i++ ) {
             for ( j = 0; j < 3; j++ ) {
                 otm1_if[i][j] = gg3_otm1_if[0][i][j];
                otm2_if[i][j] = gg3_otm2_if[0][i][j];
              }
          }
          frame = gg3_frame;
          break;

       case 7:
          xi_mm = gg4_xi_mm[0];
          eta_mm = gg4_eta_mm[0];
          for ( i = 0; i < 3; i++ ) {
             for ( j = 0; j < 3; j++ ) {
                 otm1_if[i][j] = gg4_otm1_if[0][i][j];
                otm2_if[i][j] = gg4_otm2_if[0][i][j];
              }
          }
          frame = gg4_frame;
          break;

       default:
         printf("Switch on wfs - unknown value: %ld\n", wfs);
         break;
    }

/* Transform the probe X/Y back to RA/Dec once with the corrections from
   the WFS applied and once without. */
    for ( i = 0; i < 2; i++ ) {

   /* Displaced pointing-origin position wrt the "ideal axis". */
       xi = xi_mm / fl + ca_net - wfserry / fl + pnpae * zm;
       eta = eta_mm / fl + ce_net - wfserrx / fl ;
 
   /* Remove complete collimation. */
       f = sqrt ( 1.0 + xi * xi + eta * eta );
       xg = ( x0 - ( xi * y0 + eta * x0 * z0 ) / r0 ) / f;
       yg = ( y0 + ( xi * x0 - eta * y0 * z0 ) / r0 ) / f;
       zg = ( z0 + eta * r0 ) / f;

   /* Pre-collimation position to WFS frame. */
        PartAv ( frame, xg, yg, zg,
                otm2_if, -sst, cst, otm1_if,
                &xhi, &yhi, &zhi, &xai, &yai, &zai,
                &x, &y, &z );
 
   /* To spherical */
       a[i] = slaDranrm(atan2(y, frame == AZEL_MNT || 
                              frame == AZEL_TOPO ? -x : x));
       b[i] = atan2(z, sqrt(x * x + y * y));

       wfserrx = 0.0;
       wfserry = 0.0;
    }

/* Required adjustment to RA/Dec to center the star on the WFS. */
    deltaa = slaDrange( a[0] - a[1] );
    deltab = slaDrange( b[0] - b[1] );

    switch (wfs) {
       case 1:

      /* Adjust offsets from base for all 3 chop states */
          for ( ichop = 0; ichop < 3; ichop++ ) {
             g1_tar_ob[ichop][0] += deltaa;
             g1_tar_ob[ichop][1] += deltab;
          }
          break;

       case 2:
          for ( ichop = 0; ichop < 3; ichop++ ) {
             g2_tar_ob[ichop][0] += deltaa;
             g2_tar_ob[ichop][1] += deltab;
          }
          break;

       case 3:
          for ( ichop = 0; ichop < 3; ichop++ ) {
             g3_tar_ob[ichop][0] += deltaa;
             g3_tar_ob[ichop][1] += deltab;
          }
          break;

       case 4:
          for ( ichop = 0; ichop < 3; ichop++ ) {
             gg1_tar_ob[ichop][0] += deltaa;
             gg1_tar_ob[ichop][1] += deltab;
          }
          break;

       case 5:
          for ( ichop = 0; ichop < 3; ichop++ ) {
             gg2_tar_ob[ichop][0] += deltaa;
             gg2_tar_ob[ichop][1] += deltab;
          }
          break;

       case 6:
          for ( ichop = 0; ichop < 3; ichop++ ) {
             gg3_tar_ob[ichop][0] += deltaa;
             gg3_tar_ob[ichop][1] += deltab;
          }
          break;

       case 7:
          for ( ichop = 0; ichop < 3; ichop++ ) {
             gg4_tar_ob[ichop][0] += deltaa;
             gg4_tar_ob[ichop][1] += deltab;
          }
          break;

       default:
         printf("Switch on wfs - unknown value: %ld\n", wfs);
         break;
    }
   }
/*===========================================================================*/

    timeNow(&timeBeforeSem2);

    epicsMutexLock(TcsSemId);

    timeNow(&timeAfterSem2);
    dTimeSem2 = timeAfterSem2 - timeBeforeSem2;
    Tick = tick;
    Tt = tt;
    St = st;
    Cst = cst;
    Sst = sst;
    InPosition = inPosition;
    InPosReason = inPosReason;
    Ca_net = ca_net;
    Ce_net = ce_net;
    Ia_net = ia_net;
    X0 = x0;
    Y0 = y0;
    Z0 = z0;
    Az = az;
    El = el;
    DtimeSem1 = dTimeSem1;
    DtimeSem2 = dTimeSem2;
    Rm = rm;
    Paim = paim;
    Rma = rma;
    Fl = fl;
    Pa = pa;
    F1_sc = f1_sc;
    F2_sc = f2_sc;
    M_tar_p[0] = m_tar_p[0];
    M_tar_p[1] = m_tar_p[1];
    M_tar_p0[0] = m_tar_p0[0];
    M_tar_p0[1] = m_tar_p0[1];
    M_por_p[0] = m_por_p[0];
    M_por_p[1] = m_por_p[1];
    M_por_p0[0] = m_por_p0[0];
    M_por_p0[1] = m_por_p0[1];
    O_por[0] = xrob * fl ;
    O_por[1] = yrob * fl ;
    for (ichop = 0; ichop < 3; ichop++) {
        S_tar_pt[ichop][0] = s_tar_pc[ichop][0];
        S_tar_pt[ichop][1] = s_tar_pc[ichop][1];
        S_tar_p0[ichop][0] = s_tar_p0[ichop][0];
        S_tar_p0[ichop][1] = s_tar_p0[ichop][1];
        S_tar_pc[ichop][0] = s_tar_pc[ichop][0];
        S_tar_pc[ichop][1] = s_tar_pc[ichop][1];
        S_por_p[ichop][0] = s_por_p[ichop][0];
        S_por_p[ichop][1] = s_por_p[ichop][1];
        S_por_pc[ichop][0] = s_por_pc[ichop][0];
        S_por_pc[ichop][1] = s_por_pc[ichop][1];
        G1_tar_p[ichop][0] = g1_tar_p[ichop][0];
        G1_tar_p[ichop][1] = g1_tar_p[ichop][1];
        G2_tar_p[ichop][0] = g2_tar_p[ichop][0];
        G2_tar_p[ichop][1] = g2_tar_p[ichop][1];
        G3_tar_p[ichop][0] = g3_tar_p[ichop][0];
        G3_tar_p[ichop][1] = g3_tar_p[ichop][1];
        GG1_tar_p[ichop][0] = gg1_tar_p[ichop][0];
        GG1_tar_p[ichop][1] = gg1_tar_p[ichop][1];
        GG2_tar_p[ichop][0] = gg2_tar_p[ichop][0];
        GG2_tar_p[ichop][1] = gg2_tar_p[ichop][1];
        GG3_tar_p[ichop][0] = gg3_tar_p[ichop][0];
        GG3_tar_p[ichop][1] = gg3_tar_p[ichop][1];
        GG4_tar_p[ichop][0] = gg4_tar_p[ichop][0];
        GG4_tar_p[ichop][1] = gg4_tar_p[ichop][1];
        switch (wfs) {
           case 1:
              G1_tar_ob[ichop][0] = g1_tar_ob[ichop][0];
              G1_tar_ob[ichop][1] = g1_tar_ob[ichop][1];
              break;
           case 2:
              G2_tar_ob[ichop][0] = g2_tar_ob[ichop][0];
              G2_tar_ob[ichop][1] = g2_tar_ob[ichop][1];
              break;
           case 3:
              G3_tar_ob[ichop][0] = g3_tar_ob[ichop][0];
              G3_tar_ob[ichop][1] = g3_tar_ob[ichop][1];
           case 4:
              GG1_tar_ob[ichop][0] = gg1_tar_ob[ichop][0];
              GG1_tar_ob[ichop][1] = gg1_tar_ob[ichop][1];
           case 5:
              GG2_tar_ob[ichop][0] = gg2_tar_ob[ichop][0];
              GG2_tar_ob[ichop][1] = gg2_tar_ob[ichop][1];
           case 6:
              GG3_tar_ob[ichop][0] = gg3_tar_ob[ichop][0];
              GG3_tar_ob[ichop][1] = gg3_tar_ob[ichop][1];
           case 7:
              GG4_tar_ob[ichop][0] = gg4_tar_ob[ichop][0];
              GG4_tar_ob[ichop][1] = gg4_tar_ob[ichop][1];
        }
        M2_scan_x[ichop] = m2_scan_x[ichop];
        M2_scan_y[ichop] = m2_scan_y[ichop];
        G1_x[ichop] = g1_x[ichop];
        G1_y[ichop] = g1_y[ichop];
        G2_x[ichop] = g2_x[ichop];
        G2_y[ichop] = g2_y[ichop];
        G3_x[ichop] = g3_x[ichop];
        G3_y[ichop] = g3_y[ichop];
        GG1_x[ichop] = gg1_x[ichop];
        GG1_y[ichop] = gg1_y[ichop];
        GG2_x[ichop] = gg2_x[ichop];
        GG2_y[ichop] = gg2_y[ichop];
        GG3_x[ichop] = gg3_x[ichop];
        GG3_y[ichop] = gg3_y[ichop];
        GG4_x[ichop] = gg4_x[ichop];
        GG4_y[ichop] = gg4_y[ichop];
    }

    Traw = traw;
    Dmd_cnt = cnt02;
    Corr_cnt = cnt03;
    Corr_02 = cnt07;
    Corr_08 = cnt08;
    ADeltaT = applyDeltaT;
    Flt_cnt = cnt06;
    timeNow(&timeAfterSem3);
    FlTime = timeAfterSem3 - timeBeforeSem1;
    DTraw = deltaTraw;
    DTick = deltaTick;
    epicsMutexUnlock(TcsSemId);

/*
    if (pkdbgwriteflag && printfromfast) {
      printfromfast = 0;
      fprintf(dbgfp, "Fast loop: start of output\n");
      fprintf(dbgfp, "tai =              %23.12f \n", timeRaw2tai(tick));
      fprintf(dbgfp, "rotl =            1\n");
      fprintf(dbgfp, "st =               %23.10f \n", st*DR2H);
      fprintf(dbgfp, "m_tar_p0[0] = %23.10f (degs)\n", m_tar_p0[0]*DR2D);
      fprintf(dbgfp, "m_tar_p0[1] = %23.10f (degs)\n", m_tar_p0[1]*DR2D);
      fprintf(dbgfp, "m_tar_dt[0] = %23.10f (degs)\n", m_tar_dt[0]*DR2D);
      fprintf(dbgfp, "m_tar_dt[1] = %23.10f (degs)\n", m_tar_dt[1]*DR2D);
      fprintf(dbgfp, "fl          = %23.10f (mm)\n", fl);
      fprintf(dbgfp, "m_por_p[0]  = %23.10f (degs)\n", m_por_p[0]);
      fprintf(dbgfp, "m_por_p[1]  = %23.10f (degs)\n", m_por_p[1]);
      fprintf(dbgfp, "sia         = %23.10f \n", sia);
      fprintf(dbgfp, "cia         = %23.10f \n", cia);
      fprintf(dbgfp, "m_cosys     = %d\n", m_frame);
      fprintf(dbgfp, "r_cosys     = %d\n", r_frame);
      fprintf(dbgfp, "m_spm1\n");
      for (jj = 0; jj < 3; jj++) {
        fprintf(dbgfp, "%15.10f %15.10f %15.10f\n", m_otm1[0][jj], 
                m_otm1[1][jj], m_otm1[2][jj]);
      }
      fprintf(dbgfp, "m_spm2\n");
      for (jj = 0; jj < 3; jj++) {
        fprintf(dbgfp, "%15.10f %15.10f %15.10f\n", m_otm2[0][jj], 
                m_otm2[1][jj], m_otm2[2][jj]);
      }
      fprintf(dbgfp, "azimuth      = %23.10f\n", az*DR2D );
      fprintf(dbgfp, "elevation    = %23.10f\n", el*DR2D );
      fprintf(dbgfp, "Fast loop: end of output\n");
    }
*/
/*
    if(pkdbgwriteflag) {
      fprintf(dbgfp, "%23.12f %23.10f %23.10f %16.6f %16.6f\n", 
               timeRaw2tai(tick), az*DR2D, el*DR2D, G2_x[0], G2_y[0]);
    }
*/

/* This test was moved from beginning of routine so that if the tick had
 * not changed the return value of 1 will still disable down stream record
 * processing but if the target positions had changed the new demands 
 * would be availble for the ODGW.
 */
    if (( tick <= tickl ) || ( corrFlag==1 )) {
      return 1;  
    } else {
      return 0;
    }

}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsUpdateAstCtx
 *
 *   Purpose:
 *   Update the astrometic library context.
 *
 *   Description:
 *   Updates the astrometric library context in the TCS and copies
 *   the data to an output link to make it available to other IOCs.
 *   It is scanned at 20 Hz.
 *   A late addition was to pass the array of values needed by
 *   the sky simulator
 *
 *   Invocation:
 *   tcsUpdateAstCtx(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   astSetCtx            astlib         sets ast context
 *
 *   External variables:
 *
 *
 */
long tcsUpdateAstCtx(struct genSubRecord *pgsub)
{
    double *valap = pgsub->vala;  /* pointer to vala array of pgsub */
    double *valbp = pgsub->valb;  /* Pointer to valb array of pgsub */
    double fl;                    /* telescope effective focal length */
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsUpdateAstCtx: Semaphore not created");
        return 0;
    }

    tcsOpticsGetFl(&fl);

/* Lock the global data and copy the required items to the local array. */
    epicsMutexLock(TcsSemId);
    *valap++ = Tick;
    *valap++ = X0;
    *valap++ = Y0;
    *valap++ = Z0;
    *valap++ = fl;
    *valap++ = Rma;
    *valap++ = An;
    *valap++ = Aw;
    *valap++ = Pnpae;
    *valap++ = Ca_net;
    *valap++ = Ce_net;
    *valap++ = Tlat;
    *valap++ = Slat;
    *valap++ = Clat;
    *valap++ = Diurab;
    *valap++ = Hm;
    *valap++ = Temp;
    *valap++ = Press;
    *valap++ = Humid;
    *valap++ = Wavelr;
    *valap++ = Tlr;
    *valap++ = Refa;
    *valap++ = Refb;
    *valap++ = St;
    *valap++ = Daz;
    *valap++ = M2_scan_x[0];
    *valap++ = M2_scan_y[0];
    *valap++ = M2_scan_x[1];
    *valap++ = M2_scan_y[1];
    *valap++ = M2_scan_x[2];
    *valap++ = M2_scan_y[2];
    *valap++ = M_por_p[0];
    *valap++ = M_por_p[1];
    *valap++ = S_por_p[0][0];
    *valap++ = S_por_p[0][1];
    *valap++ = S_por_p[1][0];
    *valap++ = S_por_p[1][1];
    *valap++ = S_por_p[2][0];
    *valap++ = S_por_p[2][1];
    *valap++ = Ao2t[0] ;
    *valap++ = Ao2t[1] ;
    *valap++ = Ao2t[2] ;
    *valap++ = Ao2t[3] ;
    *valap++ = Ao2t[4] ;
    *valap++ = Ao2t[5] ;
    *valbp++ = Ae2mt[0][0];
    *valbp++ = Ae2mt[0][1];
    *valbp++ = Ae2mt[0][2];
    *valbp++ = Ae2mt[1][0];
    *valbp++ = Ae2mt[1][1];
    *valbp++ = Ae2mt[1][2];
    *valbp++ = Ae2mt[2][0];
    *valbp++ = Ae2mt[2][1];
    *valbp++ = Ae2mt[2][2];
    *valbp++ = Ia_net;
    *valbp++ = Ie;
    *valbp++ = Vd;
    epicsMutexUnlock(TcsSemId);

/* Set the local (TCS) ast context. */
    (void) astSetctx( pgsub->vala );

    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsWritePointLog
 *
 *   Purpose:
 *   Write pointing observation log array.
 *
 *   Description:
 *   Writes the data necessary for pointing analysis to an output link.
 *   This record is scanned at 20Hz but is normally disabled. When a pointing
 *   observation is logged the record is enabled for one scan and a the
 *   required data copied from global memory.
 *
 *   Invocation:
 *   tcsWritePointLog(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *
 *   External variables:
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 */
long tcsWritePointLog(struct genSubRecord *pgsub)
{
    double *valap = pgsub->vala;  /* pointer to vala array of pgsub */
    double tick, eqx, wavel, a1, b1, az, el, pa, pox, poy, fl;
    double temp, press, humid, tlr;
    double a2, b2, tt, tai, mjd, tod;
    double debug1, debug2;
    FRAMETYPE frame;
    struct EPOCH equinox, epochNow, eqx2000;
    struct PMPXRV pm;
    double aoprms[15];
    struct TELP telp;      /* never filled in */
    int i;
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsWritePointLog: Semaphore not created");
        return 0;
    }

/* Lock the global data and copy the required items to local variables. */
    epicsMutexLock(TcsSemId);
    tick = Tick;
    frame = S_frame[0];
    eqx = S_eqx[0];
    wavel = S_wavel[0];
    a1 = S_tar_p0[0][0];
    b1 = S_tar_p0[0][1];
    az = AzDef;
    el = ElDef;
    pox = S_por_p[0][0];
    poy = S_por_p[0][1];
    fl = Fl;
    pa = Pa;
    temp = Temp;
    press = Press;
    humid = Humid;
    tlr = Tlr;
    for ( i = 0; i < 15; i++ ) aoprms[i] = Aoprms[i];
    debug1 = Debug1;
    debug2 = Debug2;
    epicsMutexUnlock(TcsSemId);

/* Set up structures for Coco. */
    equinox.year = eqx;
    equinox.type = frame == FK4 ? 'B' : 'J';

/* Epoch now. */
    timeThenD( tick, TT, &tt);
    epochNow.year = slaEpj( tt );
    epochNow.type = 'J';

/* Equinox J2000. */
    eqx2000.year = 2000.0;
    eqx2000.type = 'J';

/* No proper motions. */
    pm.pm = 0;

/* Update observed to apparent array. */
    timeThenR(tick, LAST, &aoprms[13]);
    slaAtmdsp(aoprms[5], aoprms[6], aoprms[7], aoprms[8], aoprms[10],
              aoprms[11], wavel, aoprms + 10, aoprms + 11);

/* Transform position to FK5/2000 (approx ICRS). */
    astCoco( a1, b1, pm, frame, equinox, epochNow, FK5, eqx2000, tt,
             aoprms, telp, &a2, &b2);

/* Compute TAI now as MJD and seconds in day. */
    timeThenD( tick, TAI, &tai);
    mjd = floor( tai );
    tod = tick - timeTai2raw( mjd );
   
/* Copy data to output link. */
    *valap++ = mjd;
    *valap++ = tod;
    *valap++ = a2;
    *valap++ = b2;
    *valap++ = wavel;
    *valap++ = az;
    *valap++ = el;
    *valap++ = pa;
    *valap++ = pox;
    *valap++ = poy;
    *valap++ = fl;
    *valap++ = temp;
    *valap++ = press;
    *valap++ = humid;
    *valap++ = tlr;

    *(double *)pgsub->valb = debug1;
    *(double *)pgsub->valc = debug2;
    return 0;
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsESolsysLoop
 *
 *   Purpose:
 *   The TCS Solar-System Object loop.
 *
 *   Description:
 *   This code implements the solar system object loop of the Gemini TCS
 *   It is expected to be called at 0.1Hz as an EPICS subroutine record.
 *
 *   Invocation:
 *   tcsESolsysLoop(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    psub     (genSubRecord *) Pointer to genSub record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   tcsSolsysLoop
 *
 *-
 */
/* *INDENT-ON* */


long tcsESolsysLoop( genSubRecord *pgsub )
{
    char health[8] ;
    char mess[80] ;

/* Do all the work in tcsSolsysLoop. */
    tcsSolsysLoop(health, mess);

    strcpy(pgsub->vala, health);
    strcpy(pgsub->valb, mess)  ;

    return 0;
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSolsysLoop
 *
 *   Purpose:
 *   The TCS Solar-System Object loop.
 *
 *   Description:
 *   This code implements the solar system object loop of the Gemini TCS
 *   It is expected to be called at 0.1Hz. It updates the position
 *   and differential rates of source A if a solar system object is 
 *   being tracked.
 *   It will return an error status and message if any of the possible
 *   targets returns an error.
 *
 *   Invocation:
 *   tcsSolsysLoop(health, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *    (<)   health (char *)    Health string 
 *    (<)   mess   (char *)    Return message
 *
 *   Function value:
 *   none
 *
 *-
 */
/* *INDENT-ON* */

void tcsSolsysLoop(char *health, char *mess)
{

/* Local copies of global variables */
    PLANET code[11];
    int jform[11];
    double epochel[11], orbinc[11],  anode[11], perih[11], aorq[11];
    double e[11], aorl[11], dm[11];
    double tlong, tlat;
    FRAMETYPE frame[11];
    double eqx[11];
    double aoprms[15];
    int updateKernel[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Local variables */
    int istat, i;
    double traw, theta1[11], theta2[11], r, tt, dt, theta1dt, theta2dt,
           dtheta1[11], dtheta2[11], tdb, diam, utc;
    char errmess[80] ;
    char hstring[8];                   /* Health as string */
    double dra1, ddec1 ;               /* Track rates */
    static int dbgLevel = DBG_NONE; /* debug level */
    struct EPOCH equinox;
    struct EPOCH epoch;
    struct TELP telp;      /* never filled in */
    struct PMPXRV pmotion; /* never filled in */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsSolSysLoop: Semaphore not created");
        return;
    }
    epicsMutexLock(TcsSemId);
    for (i = 0; i< 11 ; i++) {
      code[i] = P_code[i];
      jform[i] = O_jform[i];
      epochel[i] = O_epoch[i];
      orbinc[i] = O_orbinc[i];
      anode[i] = O_anode[i];
      perih[i] = O_perih[i];
      aorq[i] = O_aorq[i];
      e[i] = O_e[i];
      aorl[i] = O_aorl[i];
      dm[i] = O_dm[i];
    }
    tlong = Tlong;
    tlat = Tlat;
    for ( i = 0; i < 15; i++) aoprms[i] = Aoprms[i];
    frame[MOUNT] = M_frame;
    for ( i = 0; i < 3; i++) {
      frame[i+1] = S_frame[i];
      eqx[i+1]   = S_eqx[i];
    }
    frame[PWFS1] = G1_frame;
    frame[PWFS2] = G2_frame;
    frame[OIWFS] = G3_frame;
    frame[G1]    = GG1_frame;
    frame[G2]    = GG2_frame;
    frame[G3]    = GG3_frame;
    frame[G4]    = GG4_frame;
    eqx[PWFS1]   = G1_eqx;
    eqx[PWFS2]   = G2_eqx;
    eqx[OIWFS]   = G3_eqx;
    eqx[G1]      = GG1_eqx;
    eqx[G2]      = GG2_eqx;
    eqx[G3]      = GG3_eqx;
    eqx[G4]      = GG4_eqx;
    epicsMutexUnlock(TcsSemId);

/* Get current time. */
    timeNow( &traw);
    timeThenD( traw, TT, &tt);

/* Initialize the returns */
    strcpy(health, "GOOD");
    strcpy(mess, " ");

/* Initialize the pmotion struct. Previously this wasn't done and there 
*  were no problems seen but using an uninitialized pmotion elsewhere
*  caused inexplicable and random crashes or sometimes big changes in
*  the output of astCoco. So, just to be safe...
*/
   pmotion.pm = 0 ;
   pmotion.pmRA = 0.0 ;
   pmotion.pmDec = 0.0;
   pmotion.px = 0.0 ;
   pmotion.rv = 0.0;

/* Loop through the virtual telescopes, checking whether the positions and
*  differential track rates need updating. Note, although each virtual
*  telescope is checked, many combinations are not implemented as the 
*  appropriate CAD records don't exist.
*  Mount - only NO_PLANET
*  SourceB, C - only NO_PLANET
*  SourceA - all options 
*  PWFS1, PWFS2, OIWFS, G1, G2, G3, G4 - potentially all options 
*/
    for ( i = 0; i < 11; i++) {
      if ( code[i] == NO_PLANET ) {
        continue;
      } else if ( code[i] == ORBIT ) {

    /* Get new position. */
        slaPlante( tt, tlong, tlat, jform[i], epochel[i], orbinc[i], anode[i],
                   perih[i], aorq[i], e[i], aorl[i], dm[i], &theta1[i], 
                   &theta2[i], &r, &istat);

    /* Get position 1 min in future. */
        dt = 1.0 / 24.0 / 60.0;
        slaPlante( tt + dt, tlong, tlat, jform[i], epochel[i], orbinc[i], 
                   anode[i], perih[i], aorq[i], e[i], aorl[i], dm[i], 
                   &theta1dt, &theta2dt, &r, &istat);
        if (istat) {
          strcpy(health, "BAD");
          if (istat == -1) {
            strcpy(mess, "slaPante: illegal element set");
          } else if (istat == -2) {
            strcpy(mess, "slaPlante: illegal eccentricity");
          } else if (istat == -3) {
            strcpy(mess, "slaPlante: illegal perihelion");
          } else if (istat == -4) {
            strcpy(mess, "slaPante: illegal daily motion");
          } else if (istat == -5) {
            strcpy(mess, "slaPlante: numerical error");
          } else {
            sprintf(mess, "slaPlante: unknown return %d", istat);
          }
          continue;
        }
        updateKernel[i] = 1;
        dtheta1[i] = (theta1dt - theta1[i]) / dt;
        dtheta2[i] = (theta2dt - theta2[i]) / dt;

      } else if ( code[i] == EPHEMERIS) {
        timeThenD( traw, UTC, &utc);
        dt = 1.0 / 24.0 / 60.0;
        istat = tcsEphemerisTarget(utc, i, APPT, &theta1[i], &theta2[i], 
                                   &dra1, &ddec1, hstring, errmess);
        if (istat) {
          strcpy(health, hstring);
          strcpy(mess, errmess);
          continue ;
        } else if (!strncmp(hstring, "WARNING", 7)) {
          strcpy(health, hstring);
          strcpy(mess, errmess);
        }
        updateKernel[i] = 1 ;
        dtheta1[i] = dra1;
        dtheta2[i] = ddec1;

      } else {
        timeThenD( traw, TDB, &tdb);

    /* Get new position. */
        slaRdplan( tdb, (int)code[i], tlong, tlat, &theta1[i], &theta2[i], 
                  &diam);

    /* Get position 1 min (or 10s if Moon) in future. */
        if ( code[i] == MOON ) dt = 1.0 / 24.0 / 60.0 / 6.0;
        else dt = 1.0 / 24.0 / 60.0;
        slaRdplan( tdb + dt, (int)code[i], tlong, tlat,
                   &theta1dt, &theta2dt, &diam);
        updateKernel[i] = 1;
        dtheta1[i] = (theta1dt - theta1[i]) / dt;
        dtheta2[i] = (theta2dt - theta2[i]) / dt;
      }

/* For consistency and because they are displayed on the TSD, update the
*  track rates in the TCB. We should probably also update the source
*  positions ? 
*/
      tcsConfigResetRates(i, tt, dtheta1[i], dtheta2[i]);

/* Convert new position and rates to the tracking frame. */
      equinox.year = eqx[i];
      equinox.type = frame[i] == FK4 ? 'B' : 'J';
      epoch.year = tt;
      epoch.type = 'J';
      astCocoR( theta1[i], theta2[i], pmotion, dtheta1[i]/86400.0, 
                dtheta2[i]/86400.0, APPT,
              equinox, epoch, frame[i], equinox, tt, aoprms, telp,
              &theta1[i], &theta2[i], &dtheta1[i], &dtheta2[i]);
      dtheta1[i] *= 86400.0;
      dtheta2[i] *= 86400.0;
    }

    epicsMutexLock(TcsSemId);
    if (updateKernel[MOUNT]) {
      M_tar_p0[0]    = theta1[MOUNT];
      M_tar_p0[1]    = theta2[MOUNT];
      if (P_override_rates[MOUNT]) {
        M_tar_dt[0] = dtheta1[MOUNT];
        M_tar_dt[1] = dtheta2[MOUNT];
        M_tar_t0    = tt;
      }
    }
    for ( i = 0; i < 3; i++) {
      if (updateKernel[i+1]) {
        S_tar_p0[i][0] = theta1[i+1];
        S_tar_p0[i][1] = theta2[i+1];
        if (P_override_rates[i+1]) {
          S_tar_dt[i][0] = dtheta1[i+1];
          S_tar_dt[i][1] = dtheta2[i+1];
          S_tar_t0[i]    = tt;
        } else {
/*
          printf("\n") ;
*/
        }
      }
    }
    if (updateKernel[PWFS1]) {
      G1_tar_p0[0]    = theta1[PWFS1];
      G1_tar_p0[1]    = theta2[PWFS1];
      if (P_override_rates[PWFS1]) {
        G1_tar_dt[0] = dtheta1[PWFS1];
        G1_tar_dt[1] = dtheta2[PWFS1];
        G1_tar_t0    = tt;
      }
    }
    if (updateKernel[PWFS2]) {
      G2_tar_p0[0]    = theta1[PWFS2];
      G2_tar_p0[1]    = theta2[PWFS2];
      if (P_override_rates[PWFS2]) {
        G2_tar_dt[0] = dtheta1[PWFS2];
        G2_tar_dt[1] = dtheta2[PWFS2];
        G2_tar_t0    = tt;
      }
    }
    if (updateKernel[OIWFS]) {
      G3_tar_p0[0]    = theta1[OIWFS];
      G3_tar_p0[1]    = theta2[OIWFS];
      if (P_override_rates[OIWFS]) {
        G3_tar_dt[0] = dtheta1[OIWFS];
        G3_tar_dt[1] = dtheta2[OIWFS];
        G3_tar_t0    = tt;
      }
    }
    if (updateKernel[G1]) {
      GG1_tar_p0[0]    = theta1[G1];
      GG1_tar_p0[1]    = theta2[G1];
      if (P_override_rates[G1]) {
        GG1_tar_dt[0] = dtheta1[G1];
        GG1_tar_dt[1] = dtheta2[G1];
        GG1_tar_t0    = tt;
      }
    }
    if (updateKernel[G2]) {
      GG2_tar_p0[0]    = theta1[G2];
      GG2_tar_p0[1]    = theta2[G2];
      if (P_override_rates[G2]) {
        GG2_tar_dt[0] = dtheta1[G2];
        GG2_tar_dt[1] = dtheta2[G2];
        GG2_tar_t0    = tt;
      }
    }
    if (updateKernel[G3]) {
      GG3_tar_p0[0]    = theta1[G3];
      GG3_tar_p0[1]    = theta2[G3];
      if (P_override_rates[G3]) {
        GG3_tar_dt[0] = dtheta1[G3];
        GG3_tar_dt[1] = dtheta2[G3];
        GG3_tar_t0    = tt;
      }
    }
    if (updateKernel[G4]) {
      GG4_tar_p0[0]    = theta1[G4];
      GG4_tar_p0[1]    = theta2[G4];
      if (P_override_rates[G4]) {
        GG4_tar_dt[0] = dtheta1[G4];
        GG4_tar_dt[1] = dtheta2[G4];
        GG4_tar_t0    = tt;
      }
    }
    epicsMutexUnlock(TcsSemId);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsEMedFastLoop
 *
 *   Purpose:
 *   The TCS medium fast loop.
 *
 *   Description:
 *   This code implements the medium fast loop of the Gemini TCS.
 *   It is expected to be called at 1Hz as an EPICS subroutine record.
 *
 *   Invocation:
 *   tcsEFastMedLoop(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    psub     (genSubRecord *) Pointer to genSub record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   tcsMedFastLoop
 *
 *   External variables:
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


long tcsEMedFastLoop( genSubRecord *psub )
{

/* Do all the work in tcsMedFastLoop. */
    tcsMedFastLoop();
    return 0;
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsMedFastLoop
 *
 *   Purpose:
 *   The TCS medium fast loop.
 *
 *   Description:
 *   This code implements the Medium fast loop of the Gemini TCS.
 *   It is expected to be called at 1Hz. It refreshes the basic pointing
 *   model and update AN & AW.
 *
 *   Invocation:
 *   tcsMediumLoop()
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *   none
 *
 *   Function value:
 *   none
 *
 *   External functions:
 *   tcsPup
 *
 *   External variables:
 *   (>)   Model;    (int[MAXTRM]) Pointing model
 *   (>)   Coeffv    (double[MAXTRM])
 *   (>)   Nterml, Ntermx, Nterms (int)
 *   (>)   Coeffn    (char[NTROOM][9])
 *   (>)   Coform    (char[NTROOM][9])
 *   (>)   Ae2nm     (double[3][3]) AzEl to nominal mount rotation matrix
 *   (>)   X0,Y0,Z0  (double)    precollination Az/El
 *   (>)   Aux       (double[3]) auxiliary readings
 *   (>)   Tlat      (double)    true latitude
 *   (<)   Ia        (double)    index error in azimuth
 *   (<)   Ie        (double)    index error in elevation
 *   (<)   Vd        (double)    vertical deflection
 *   (<)   Ca        (double)    collimation correction in azimuth
 *   (<)   Pnpae     (double)    non-perpendicularity
 *   (<)   Ae2mt     (double[3][3]) AzEl to mount rotation matrix
 *   (<)   An        (double)    azimuth tilt north
 *   (<)   Aw        (double)    azimuth tilt west
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


void tcsMedFastLoop(void)
{
/* Local copies of global variables */
    static double ia, ie, vd, pnpae, ca, ae2nm[3][3], ae2mt[3][3], aux[3];
    int model[MAXTRM], nterml, ntermx, nterms;
    double coeffv[MAXTRM];
    char coeffn[NTROOM][9];
    char coform[NTROOM][9];
    double tlat;
    double x0, y0, z0;
    double an, aw;

    double a0, b0;
    int i, j;
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsMedFastLoop: Semaphore not created");
        return;
    }

/* Get local copies of everything needed. */
    epicsMutexLock(TcsSemId);
    for ( i = 0; i < 3; i++ ) {
       for ( j = 0; j < 3; j++ ) {
          ae2nm[i][j] = Ae2nm[i][j];
       }
    }
    for ( i = 0; i < MAXTRM; i++ ) {
       model[i] = Model[i];
       coeffv[i] = Coeffv[i];
    }
    nterml = Nterml;
    ntermx = Ntermx;
    nterms = Nterms;
    for ( i = 0; i < NTROOM; i++ ) {
       for ( j = 0; j < 9; j++ ) {
          coeffn[i][j] = Coeffn[i][j];
          coform[i][j] = Coform[i][j];
       }
    }
    for ( i = 0; i < 3; i++ ) aux[i] = Aux[i];
    tlat = Tlat;
    x0 = X0;
    y0 = Y0;
    z0 = Z0;
    epicsMutexUnlock(TcsSemId);


/* Convert demand az/el from vector to spherical (Az is S thru E). */
    a0 = atan2( y0, x0 );
    b0 = atan2( z0, sqrt( x0 * x0 + y0 * y0 ) );

/* Translate the operational pointing model into the current basic one. */

#define AZEL 2
    (void) tcsPup( MAXTRM, model, coeffv, nterml, ntermx, nterms, coeffn, 
                   coform, AZEL, ae2nm, a0, b0, 0, aux, tlat, &ia, &ie, 
                   &vd, &ca, &pnpae, ae2mt );

/* Decompose ae2mt matrix into AN & AW for use with astlib. */
    an = atan2( ae2mt[0][2], 
                sqrt( ae2mt[1][2] * ae2mt[1][2] + ae2mt[2][2] * ae2mt[2][2]) );
    aw = atan2( -ae2mt[2][1], 
                sqrt( ae2mt[2][0] * ae2mt[2][0] + ae2mt[2][2] * ae2mt[2][2]) );

/* Copy the new values to the global areas. */
    epicsMutexLock(TcsSemId);
    Ia = ia;
    Ie = ie;
    Vd = vd;
    Ca = ca;
    Pnpae = pnpae;
    for ( i = 0; i < 3; i++ ) {
       for ( j = 0; j < 3; j++ ) {
          Ae2mt[i][j] = ae2mt[i][j];
       }
    }
    An = an;
    Aw = aw;
    epicsMutexUnlock(TcsSemId);
}


/*+
 *   Function name:
 *   tcsGetMountAzEl
 *
 *   Purpose:
 *   Fetch demand azimuth and elevation.
 *
 *   Description:
 *   This routine simply locks the global database and then copies the 
 *   current demand azimuth and elevation. 
 *
 *   Invocation:
 *   tcsGetMountAzEl (&azimuth, &elevation)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    azimuth  (double *) demand azimuth (rads)
 *      (<)    elevation (double *) demand elevation (rads)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsGetMountAzEl (double *azimuth, double *elevation)

{
  if( TcsSemId) {
    epicsMutexLock(TcsSemId);
    *azimuth = Az;
    *elevation = El;
    epicsMutexUnlock(TcsSemId);
  }
}

/*+
 *   Function name:
 *   tcsGetTelescopeRADec
 *
 *   Purpose:
 *   Compute and return the telescope RA & Dec. 
 *
 *   Description:
 *   The TCS continuously computes the current target RA & Dec by 
 *   performing an upstream calculation starting from the mount 
 *   azimuth and elevation. When tracking, this current RA/Dec should
 *   equal the demanded target RA/Dec. For the laser system it is important
 *   to also know the "telescope" RA/Dec which is the RA/dec of the 
 *   rotator center. The current RA/Dec and the telescope RA/Dec are the
 *   same unless a pointing origin has been set.  
 *
 *   Invocation:
 *   tcsGetTelescopeRaDec (&ra, &dec)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    ra  (double *) telescope RA (degs)
 *      (<)    dec (double *) telescope Dec (degs)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsGetTelescopeRADec (double *ra, double *dec)

{
    struct WCS_CTX wcsctx ;            /* Current WCS context */
    struct WCS wcs ;                   /* WCS transformation */
    int stat ;                         /* Status from astLib calls */
    double wavelr ;                    /* Reference wavelength */
    FRAMETYPE t_frame ;                /* Tracking frame */
    struct EPOCH t_equinox ;           /* Tracking equinox */
    double timestamp ;                 /* Raw time for which WCS is correct */

    char ctype1[9] ;                   /* FITS CTYPE axis 1 */
    char ctype2[9] ;                   /* FITS CTYPE axis 2 */
    char radecsys[9] ;                 /* value of FITS keyword RADECSYS */
    double crpix1val, crpix2val ;      /* "Pixel" coords of rotator center*/
    double crval1val, crval2val ;      /* RA/Dec of rotator center (degs) */
    double cd1_1, cd1_2, cd2_1, cd2_2; /* Transformation coeffs */
    double equinoxval ;                /* value for FITS keyword EQUINOX */
    double mjdobsval ;                 /* value of FITS keyword MJD-OBS */
    double tt ;                        /* Epoch of observation (MJD) */
    double ttinit ;                    /* Routine Init time stamp */
    double ttend ;                     /* Routine End time stamp */
    static double dtGetTelRD = 0;                /* Execution Time of Routine */

    *ra = 0.0;
    *dec = 0.0;

    timeNow(&ttinit);

    if(!TcsSemId)return;

    astGetctx (&wcsctx);  /*20180528 IA: changed because of jitter problem*/
    
    epicsMutexLock(TcsSemId);
    wavelr = Wavelr ;
    t_frame = S_frame[0] ;
    t_equinox.year = S_eqx[0] ;
    t_equinox.type = t_frame == FK4 ? 'B' : 'J' ;
    DtGetTelRD = dtGetTelRD;
    epicsMutexUnlock(TcsSemId);

/* Generate WCS transformation */
    
   if ((stat = astCtx2tr(wcsctx, t_frame, t_equinox, wavelr, 0, &wcs, 
                        &timestamp))) {
     /* At startup the default frame is AZEL_MNT until the kernel
      * initializes. We also don't want error messages if someone
      * legitimately sets an AZEL frame later on. Only output this
      * message for error codes -2 to -6 
      */
     if (stat != -1 ) {
       printf("tcsGetTelescopeRADec: failed to generate WCS, status = %d\n",
                        stat) ;
     }
     cnt12++;
     return ;
   }

   if ((stat = timeThenD (timestamp, TT, &tt))) {
     printf("tcsGetTelescopeRADec: failed to generate TT, status = %d\n",
             stat);
     return ;
   }

/* Generate FITS values. we are interested in crval1val and crval2val */
   if ((stat = astFITSv (wcs, t_frame, t_equinox, tt, ctype1, &crpix1val,
                         &crval1val, ctype2, &crpix2val, &crval2val,
                         &cd1_1, &cd1_2, &cd2_1,
                         &cd2_2, radecsys, &equinoxval, &mjdobsval))) {
      printf ("tcsGetTelescopeRADec: Failed to generate FITS values, status = %d\n", stat) ;

      return ;
   }

/* Copy return data */
   *ra  = crval1val ;
   *dec = crval2val ;

   timeNow(&ttend);
   dtGetTelRD = ttend - ttinit;
}

/*+
 *   Function name:
 *   tcsGetP1LGSMode
 *
 *   Purpose:
 *   Fetch the P1 + LGS mode from the global database.
 *
 *   Description:
 *   Simply copy the value from the private store.
 *
 *   Invocation:
 *   mode = tcsGetP1LGSMode ()
 *
 *   Function value:
 *   Curent mode either 1 or 0 
 * 
 *-
 */

int tcsGetP1LGSMode ()
{

   return P1LGSMode ;

}


/*+
 *   Function name:
 *   tcsGetTemperature
 *
 *   Purpose:
 *   Fetch temperature from global database.
 *
 *   Description:
 *   Simply copy the temperature value used in the refraction calculation.
 *
 *   Invocation:
 *   tcsgetTemperature (&temperature)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    temperature  (double *)  Atmospheric temperature (deg C)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsGetTemperature (double *temperature)
{

   *temperature = Temp - 273.16;

}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetTrack
 *
 *   Purpose:
 *   Returns the position of the mount in the tracking frame.
 *
 *   Description:
 *   This routine returns the current RA/Dec (or Az/El) of the mount
 *   given the input az, el, rotator angle and time. The algorithm is
 *   taken from PTW's fast upstream pointing code. At present this
 *   routine is expected to be called from the display task at about 1 Hz.
 *
 *   Invocation:
 *   tcsGetTrack( az, el, rma, tappl, &ra, &dec);
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>) az       (double)   azimuth
 *      (>) el       (double)   elevation
 *      (>) rma      (double)   rotator angle
 *      (>) tappl    (double)   time
 *      (<) taraui   (double)   RA or Az in tracking frame
 *      (<) tarbui   (double)   Dec or El in tracking frame
 *
 *   Function value:
 *   none
 *
 *   External functions:
 *   semTake         sem        takes VxWorks semaphore
 *   semGive         sem        releases VxWorks semaphore
 *   PartAv
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (<)   Pnpae     (double)    az/el nonperpendicularity
 *   (<)   Ca_net    (double)    horizontal collimation
 *   (<)   Ce_net    (double)    vertical collimation
 *   (<)   Ia_net    (double)    index error in azimuth
 *   (<)   Ie        (double)    index error in elevation
 *   (<)   Rm        (double)    cos of elevation
 *   (<)   Daz       (double)    azimuth correction for polar motion
 *   (>)   M_por_p   (double)    mount accumulated pointing origin
 *   (>)   M_frame   (FRAMETYPE) mount tracking frame
 *   (>)   M_otm1_i  (double)    mount inverse OTM 1
 *   (>)   M_otm2_i  (double)    mount inverse OTM 2
 *
 *   Prior requirements:
 *   The medium and fast loops must be running
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetTrack(double az, double el, double rma, double tappl,
                 double *taraui, double *tarbui)
{
    int i, j;

/* Local copies of global variables */
    FRAMETYPE m_frame;
//    double fl, pnpae, ca, ce, ia, ie, vd, spa, cpa, rm, r2;
    double fl, pnpae, ca, ce, vd, spa, cpa, rm, r2;
    double m_otm1_i[3][3], m_otm2_i[3][3];
    double m_por_p[2];
    double ae2mt[3][3];
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsGetTrack: Semaphore not created");
        return;
    }

    tcsOpticsGetFl(&fl);

    epicsMutexLock(TcsSemId);
    pnpae = Pnpae;
    ca = Ca_net;
    ce = Ce_net;
//    ia = Ia_net;
//    ie = Ie;
    vd = Vd;
    for ( i = 0; i < 3; i++ ) {
       for ( j = 0; j < 3; j++ ) {
          ae2mt[i][j] = Ae2mt[i][j];
       }
    }
    rm = Rm;
    m_por_p[0] = M_por_p[0];
    m_por_p[1] = M_por_p[1];
    m_frame = M_frame;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m_otm1_i[i][j] = M_otm1_i[i][j];
            m_otm2_i[i][j] = M_otm2_i[i][j];
        }
    }
    epicsMutexUnlock(TcsSemId);

/*
** FAST: UPSTREAM
** --------------
**
** This is merely a demonstration, hardwired for the mount
** virtual-telescope.  The final system may require continuous
** upstream transformations for several of the virtual-telescopes
** (for example the WFS ones, to generate measured guidestar
** RA/Decs), or there may be an "upstream transformation"
** function which is called when required.
*/

    {
        double s, c, st, r, x0, y0, z0, x, y, z, cvd, f, xci, yci, zci, 
               xmi, ymi, zmi, xhi, yhi, zhi, xai, yai, zai, xui, yui, zui,
               xr, yr, xi, eta, pacnp, pa;

    /* Sine and cosine of rotator angle corrected for */
    /* az/el non-perpendicularity */
        pacnp = pnpae * rm;
        pa = rma + pacnp;
        spa = sin(pa);
        cpa = cos(pa);

    /* Establish rotation. */
        (void) timeThenR(tappl, LAST, &st);
        s = sin(st);
        c = cos(st);

    /* Correct Az/El for index errors. */
       az -= Ia;
       el += Ie;
        
    /* To x,y,z */
        r = cos( el );
        x0 = - cos( az ) * r;
        y0 = sin( az ) * r;
        z0 = sin( el );

    /* Rotate the mount coordinates into [Az,El]. */
        x = ae2mt[0][0] * x0 + ae2mt[1][0] * y0 + ae2mt[2][0] * z0;
        y = ae2mt[0][1] * x0 + ae2mt[1][1] * y0 + ae2mt[2][1] * z0;
        z = ae2mt[0][2] * x0 + ae2mt[1][2] * y0 + ae2mt[2][2] * z0;

    /* Apply the vertical deflection. */
        if ( ( r = sqrt( x * x + y * y ) ) > 0.0 ) {
           cvd = 1.0 - vd * vd / 2.0;
           f = cvd + vd * z / r;
           x *= f;
           y *= f;
           z = z * cvd - vd * r;
        }

    /* Rotate the [Az,El] back into mount coordinates */
        xci = ae2mt[0][0] * x + ae2mt[0][1] * y + ae2mt[0][2] * z;
        yci = ae2mt[1][0] * x + ae2mt[1][1] * y + ae2mt[1][2] * z;
        zci = ae2mt[2][0] * x + ae2mt[2][1] * y + ae2mt[2][2] * z;

    /* Pointing origin position wrt rotator axis. */
        xr = m_por_p[0] / fl;
        yr = m_por_p[1] / fl;

    /* Pointing origin position wrt ideal axis. */
        xi = -xr * cpa - yr * spa + ca + pnpae * zci;
        eta = xr * spa - yr * cpa + ce;

    /* Remove combined collimation. */
        r2 = xci * xci + yci * yci;
        if ( r2 < 1e-20 ) r2 = 1e-20;
        r = sqrt( r2 );
        f = sqrt(1.0 + xi * xi + eta * eta);
        xmi = (xci - (xi * yci + eta * xci * zci) / r) / f;
        ymi = (yci + (xi * xci - eta * yci * zci) / r) / f;
        zmi = (zci + eta * r) / f;

    /* Transform to tracking frame. */
        PartAv(m_frame, xmi, ymi, zmi,
               m_otm2_i, -s, c, m_otm1_i,
               &xhi, &yhi, &zhi, &xai, &yai, &zai, &xui, &yui, &zui);

    /* To spherical (typically some sort of mean RA/Dec). */
        if (m_frame == AZEL_MNT) {
            *taraui = az;
            *tarbui = el;
        } else {
            *taraui = slaDranrm(atan2(yui, m_frame == AZEL_TOPO ? -xui : xui));
            *tarbui = atan2(zui, sqrt(xui * xui + yui * yui));
        }
    }
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetDiffTrack
 *
 *   Purpose:
 *   Fetch and format the current configurations differential track parameters
 *
 *   Description:
 *   The differential track parameters are fetched for the currently
 *   indexed virtual telescope and then reformatted suitable for display.
 *   The routine is called for each virtual telescope whenever a new
 *   configuration is entered. The reformatted parameters are sent to
 *   the SAD. The setting of the SAD parameters is done this way to ensure
 *   that any differential track parameters from a previous source are reset
 *   when a new target is entered. Previously this was done direct from
 *   the virtual telescope cad but this was made unreliable when the 
 *   differential track parameters were split into a separate CAD.
 *
 *   Invocation:
 *   tcsGetDiffTrack(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub  (struct genSubRecord *) Pointer to subroutine record
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 *
 *-
 */
/* *INDENT-ON* */


long tcsGetDiffTrack(struct genSubRecord *pgsub)
{
  TELESCOPE tel ;            /* Virtual telescope */
  long ntarget ;             /* Index to vitual telescope */
  FRAMETYPE dtframe ;        /* Differential tracking frame */
  struct EPOCH dteqx;        /* Equinox of differential track frame */
  double t0 ;                /* Zero time for differential tracking */
  double dtheta1 ;           /* Track rate for RA/Az */
  double dtheta2 ;           /* Track rate for Dec/El */


  ntarget = *(long *)pgsub->a ;

/* Do nothing except print a warning if the virtual telescope index is
*  out of range
*/
  if (ntarget < 0 || ntarget > 10) {
    printf("tcsGetDiffTrack: telescope index out of range\n");
  } else {
    switch (ntarget) {
      case 0:
        tel = MOUNT ;
        break ;
      case 1:
        tel = SOURCE_A ;
        break ;
      case 2:
        tel = SOURCE_B ;
        break ;
      case 3:
        tel = SOURCE_C ;
        break ;
      case 4:
        tel = PWFS1 ;
        break ;
      case 5:
        tel = PWFS2 ;
        break ;
      case 6:
        tel = OIWFS ;
        break ;
      case 7:
        tel = G1 ;
        break ;
      case 8:
        tel = G2 ;
        break ;
      case 9:
        tel = G3 ;
        break ;
      case 10:
        tel = G4 ;
        break ;
    }

    tcsConfigGetDiffTrack(CURRENT, tel, &dtframe, &dteqx, 
         &t0, &dtheta1, &dtheta2);

    strncpy (pgsub->vala, tcsCsFrame(dtframe), MAX_STRING_SIZE);
    sprintf (pgsub->valb, "%c%.14f", dteqx.type, dteqx.year);
    *(double *)pgsub->valc = t0;
    *(double *)pgsub->vald = dtheta1/S2R/86400.0;
    *(double *)pgsub->vale = dtheta2/AS2R/86400.0;
    
  }

  return 0;

}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsNewConfig
 *
 *   Purpose:
 *   Copy data into astrometric kernel.
 *
 *   Description:
 *
 *   Invocation:
 *   tcsNewConfig(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    psub     (struct subRecord *) Pointer to subroutine record
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 *
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
/* *INDENT-ON* */


long tcsNewConfig(struct subRecord *psub)
{
    int i;
    int ichop;
    double dt;                  /* UTC - T0 for differential tracking */
    double traw;                /* reference time */
    double ttref;               /* TT at reference time */
    int ioff;                   /* index for offset number */
    double theta1;              /* first offset */
    double theta2;              /* second offset */
    struct EPOCH eqx;           /* equinox of position */
    struct EPOCH eqx1;          /* equinox of position */
//    struct EPOCH epoch0;        /* epoch at t0 */
    struct EPOCH epochref;      /* epoch at reference time */
    double wavel;               /* effective wavelength */
    FRAMETYPE dtframe;          /* differential tracking frame */
    struct EPOCH dteqx;         /* equinox of differential tracking frame */
    double t0;                  /* zero time for differential tracking */
    double dtheta1;             /* differential tracking RA/Az */
    double dtheta2;             /* differential tracking Dec/El */
    FRAMETYPE tframe;           /* tracking frame */
    struct EPOCH teqx;          /* equinox of tracking frame */
    OFFCOORD coord;             /* offset coordinate type */
    struct PMPXRV pmotion;      /* proper motions */
    struct TELP tel;            /* telescope parameters */
    double aoprms[15];          /* apparent to observed parameters */
    double fl;                  /* telescope focal length */
    double throw;               /* chop throw */
    double pa;                  /* chop position angle */
    int pari;                   /* angle relaitive to ipa */
    double w;                   /* chop temporary */
    double az;                  /* current azimuth */
    double el;                  /* current elevation */
    static int dbgLevel = DBG_NONE; /* debug level */
    TELESCOPE source[3] = { SOURCE_A, SOURCE_B, SOURCE_C };

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsNewConfig: Semaphore not created");
        return 0;
    }

/* Target-independent configuration data. */
    tcsConfigGetSysconfig(CURRENT, &AzWrap, &RotWrap, &Ipa, &R_frame,
       &R_eqx, &Iaa, &ChopMode);

/* Set sine and cosine of instrument angle. */
    Sia = sin(Iaa);
    Cia = cos(Iaa);

/* Fetch effective focal length. */
    tcsOpticsGetFl(&fl);

    epicsMutexLock(TcsSemId);

/* Fill in tel structure. */
    tel.fl = fl;
    tel.rma = Rma;
    tel.an = An;
    tel.aw = Aw;
    tel.pnpae = Pnpae;
    tel.ca = Ca_net;
    tel.ce = Ce_net;

/* Apparent to observed place parameters (because they need to be updated). */
    for (i = 0; i < 15; i++)
        aoprms[i] = Aoprms[i];

/* Reference time as TT and epoch. */
    tcsConfigGetReftime(CURRENT, &traw);
    timeThenD(traw, TT, &ttref);
    epochref.year = slaEpj( ttref );
    epochref.type = 'J';

/* Update sidereal time in apparent to observed place parameters array. */
    timeThenR(traw, LAST, &aoprms[13]);

/*
** Pull all relevant data from the TCB
**
** The source positions have to be converted from the the input frame and
** equinox to the tracking frame and equinox.
**
** The offsets have to be converted to radians and, if necessary, transformed
** from tangent plane to RA/Dec.
*/

/* Mount */

/* Get source parameters from configuration block. */
    tcsConfigGetWavel(CURRENT, MOUNT, &wavel);
    tcsConfigGetTrack(CURRENT, MOUNT, &tframe, &teqx, &M_tar_p0[0],
       &M_tar_p0[1], &M_tar_dt[0], &M_tar_dt[1], &M_tar_t0);
    tcsConfigGetDiffTrack(CURRENT, MOUNT, &dtframe, &dteqx, 
       &t0, &dtheta1, &dtheta2);

/* Current epoch at zero time. */
//    epoch0.year = slaEpj( t0 );
//    epoch0.type = 'J';

/* Get pointing origin and offsets from configuration block. */
    tcsConfigGetPo(CURRENT, MOUNT, &M_por_p0[0], &M_por_p0[1]);
    tcsConfigGetPoOffset(CURRENT, MOUNT, 0, &M_por_ob[0], &M_por_ob[1]);
    M_por_p[0] = M_por_p0[0] + M_por_ob[0];
    M_por_p[1] = M_por_p0[1] + M_por_ob[1];

/* Copy frame and equinox to kernel. */
    M_frame = tframe;
    M_eqx = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type, teqx.year);
    M_wavel = wavel;
    M_tar_t0 = t0;

/* Get offset from configuration block. */
    tcsConfigGetOffset(CURRENT, MOUNT, 0, &coord, &theta1, &theta2);

/* Convert offset to tracking frame. */
    tcsCtOffToSph(tframe, M_tar_p0, coord, theta1, theta2, M_tar_ob);

/* Net target. */
    M_tar_p[0] = M_tar_p0[0] + M_tar_ob[0];
    M_tar_p[1] = M_tar_p0[1] + M_tar_ob[1];

/* Repeat for source targets. */

/*
 * N.B. ever since the filters were added, the code below tried to
 * adjust S_tar_pc to allow for any change in wavelength. A long
 * campaign in 2015 to track down glitches in probe demands to Altair showed
 * this was not the right approach. Imagine everything is tracking
 * the filter is open and just a new target wavelength is given. If we
 * modify S_tar_pc here then there is a difference between S_tar_pc
 * and S_tar_p that will change the probe demands. However over time
 * the fast loop will pull S_tar_pc back to S_tar_p. The affect is an 
 * artificial glitch in the current target S_tar_pc. Of course there is 
 * also a genuine step in the output probe demands generated by the
 * fast loop to allow for wavelength change. If we want to filter
 * thst step we must either have a separate filter
 * that slowly pulls the wavelengths together or we must filter the
 * probe demands directly and not filter the source or pointing origin.
 */
    for ( ichop = 0; ichop < 3; ichop++ ) {

    /* Current target to mount az/el. */
       tel.pox = 0.0;
       tel.poy = 0.0;
       pmotion.pm = 0.0;
       pmotion.pmRA = 0.0;
       pmotion.pmDec = 0.0;
       pmotion.px = 0.0;
       pmotion.rv = 0.0;
       eqx.year = S_eqx[ichop];
       eqx.type = S_frame[ichop] == FK4 ? 'B' : 'J';
       slaAtmdsp(aoprms[5], aoprms[6], aoprms[7], aoprms[8], aoprms[10],
          aoprms[11], S_wavel[ichop], aoprms + 10, aoprms + 11);
       astCoco( S_tar_pc[ichop][0], S_tar_pc[ichop][1], pmotion, 
          S_frame[ichop], eqx, epochref, AZEL_MNT, epochref, ttref, 
          aoprms, tel, &az, &el);

    /* Fetch new position and frame. */
       tcsConfigGetWavel(CURRENT, source[ichop], &wavel);
       tcsConfigGetTrack(CURRENT, source[ichop], &tframe, &teqx,
          &S_tar_p0[ichop][0], &S_tar_p0[ichop][1], 
          &S_tar_dt[ichop][0], &S_tar_dt[ichop][1],
          &S_tar_t0[ichop]);
       tcsConfigGetDiffTrack(CURRENT, source[ichop], &dtframe, &dteqx, 
          &t0, &dtheta1, &dtheta2);
       tcsConfigGetPo(CURRENT, source[ichop], &S_por_p0[ichop][0], 
          &S_por_p0[ichop][1]);
       S_por_p[ichop][0] = S_por_p0[ichop][0];
       S_por_p[ichop][1] = S_por_p0[ichop][1];
       for (i = 0; i < 3; i++) {
           tcsConfigGetPoOffset(CURRENT, source[ichop], i, 
              &S_por_ob[ichop][i][0], &S_por_ob[ichop][i][1]);
           S_por_p[ichop][0] += S_por_ob[ichop][i][0];
           S_por_p[ichop][1] += S_por_ob[ichop][i][1];
       }

    /* Convert current az/el back to new tracking frame. */
       aoprms[10] = Aoprms[10];
       aoprms[11] = Aoprms[11];
       slaAtmdsp(aoprms[5], aoprms[6], aoprms[7], aoprms[8], aoprms[10],
          aoprms[11], S_wavel[ichop], aoprms + 10, aoprms + 11);
       astCoco( az, el, pmotion, AZEL_MNT, eqx, epochref, tframe, teqx, 
          ttref, aoprms, tel, &S_tar_pc[ichop][0], &S_tar_pc[ichop][1]);

       S_frame[ichop] = tframe;
       S_eqx[ichop] = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type,
                                                          teqx.year);
       S_wavel[ichop] = wavel;
       S_tar_t0[ichop] = t0;
       S_tar_p[ichop][0] = S_tar_p0[ichop][0];
       S_tar_p[ichop][1] = S_tar_p0[ichop][1];

       for (ioff = 0; ioff < 3; ioff++) {
           tcsConfigGetOffset(CURRENT, source[ichop], ioff, &coord, &theta1, 
              &theta2);
           tcsCtOffToSph(tframe, S_tar_p0[ichop], coord, theta1, theta2,
              S_tar_ob[ichop][ioff]);
           S_tar_p[ichop][0] += S_tar_ob[ichop][ioff][0];
           S_tar_p[ichop][1] += S_tar_ob[ichop][ioff][1];
       }

/* Set the position used to generate the OTMs to the target as if the 
   filters were short circuit. This assumes that the filters are not used for 
   large slews. */
       S_tar_pt[ichop][0] = S_tar_p[ichop][0];
       S_tar_pt[ichop][1] = S_tar_p[ichop][1];

       aoprms[10] = Aoprms[10];
       aoprms[11] = Aoprms[11];
    }


/* PWFS1 */

    tcsConfigGetWavel(CURRENT, PWFS1, &wavel);
    tcsConfigGetTrack(CURRENT, PWFS1, &tframe, &teqx,
       &G1_tar_p0[0], &G1_tar_p0[1], &G1_tar_dt[0], &G1_tar_dt[1],
       &G1_tar_t0);
    tcsConfigGetDiffTrack(CURRENT, PWFS1, &dtframe, &dteqx, 
       &t0, &dtheta1, &dtheta2);
    G1_frame = tframe;
    G1_eqx = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type, teqx.year);
    G1_wavel = wavel;
    G1_tar_t0 = t0;
    for ( ichop = 0; ichop < 3; ichop++ ) {
       tcsConfigGetOffset(CURRENT, PWFS1, ichop, &coord, &theta1, &theta2);
       tcsCtOffToSph(tframe, G1_tar_p0, coord, theta1, theta2, 
          G1_tar_ob[ichop]);
       G1_tar_p[ichop][0] = G1_tar_p0[0] + G1_tar_ob[ichop][0];
       G1_tar_p[ichop][1] = G1_tar_p0[1] + G1_tar_ob[ichop][1];
    }

/* PWFS2 */

    tcsConfigGetWavel(CURRENT, PWFS2, &wavel);
    tcsConfigGetTrack(CURRENT, PWFS2, &tframe, &teqx,
       &G2_tar_p0[0], &G2_tar_p0[1], &G2_tar_dt[0], &G2_tar_dt[1],
       &G2_tar_t0);
    tcsConfigGetDiffTrack(CURRENT, PWFS2, &dtframe, &dteqx, 
       &t0, &dtheta1, &dtheta2);
    G2_frame = tframe;
    G2_eqx = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type, teqx.year);
    G2_wavel = wavel;
    G2_tar_t0 = t0;
    for ( ichop = 0; ichop < 3; ichop++ ) {
       tcsConfigGetOffset(CURRENT, PWFS2, ichop, &coord, &theta1, &theta2);
       tcsCtOffToSph(tframe, G2_tar_p0, coord, theta1, theta2, 
          G2_tar_ob[ichop]);
       G2_tar_p[ichop][0] = G2_tar_p0[0] + G2_tar_ob[ichop][0];
       G2_tar_p[ichop][1] = G2_tar_p0[1] + G2_tar_ob[ichop][1];
    }

/* OIWFS */

    tcsConfigGetWavel(CURRENT, OIWFS, &wavel);
    tcsConfigGetTrack(CURRENT, OIWFS, &tframe, &teqx,
       &G3_tar_p0[0], &G3_tar_p0[1], &G3_tar_dt[0], &G3_tar_dt[1],
       &G3_tar_t0);
    tcsConfigGetDiffTrack(CURRENT, OIWFS, &dtframe, &dteqx, 
       &t0, &dtheta1, &dtheta2);
    G3_frame = tframe;
    G3_eqx = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type, teqx.year);
    G3_wavel = wavel;
    G3_tar_t0 = t0;
    for ( ichop = 0; ichop < 3; ichop++ ) {
       tcsConfigGetOffset(CURRENT, OIWFS, ichop, &coord, &theta1, &theta2);
       tcsCtOffToSph(tframe, G3_tar_p0, coord, theta1, theta2, 
          G3_tar_ob[ichop]);
       G3_tar_p[ichop][0] = G3_tar_p0[0] + G3_tar_ob[ichop][0];
       G3_tar_p[ichop][1] = G3_tar_p0[1] + G3_tar_ob[ichop][1];
    }

/* Generic Guider 1 */

    tcsConfigGetWavel(CURRENT, G1, &wavel);
    tcsConfigGetTrack(CURRENT, G1, &tframe, &teqx,
       &GG1_tar_p0[0], &GG1_tar_p0[1], &GG1_tar_dt[0], &GG1_tar_dt[1],
       &GG1_tar_t0);
    tcsConfigGetDiffTrack(CURRENT, G1, &dtframe, &dteqx, 
       &t0, &dtheta1, &dtheta2);
    GG1_frame = tframe;
    GG1_eqx = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type, teqx.year);
    GG1_wavel = wavel;
    GG1_tar_t0 = t0;
    for ( ichop = 0; ichop < 3; ichop++ ) {
       tcsConfigGetOffset(CURRENT, G1, ichop, &coord, &theta1, &theta2);
       tcsCtOffToSph(tframe, GG1_tar_p0, coord, theta1, theta2, 
          GG1_tar_ob[ichop]);
       GG1_tar_p[ichop][0] = GG1_tar_p0[0] + GG1_tar_ob[ichop][0];
       GG1_tar_p[ichop][1] = GG1_tar_p0[1] + GG1_tar_ob[ichop][1];
    }

/* Generic Guider 2 */

    tcsConfigGetWavel(CURRENT, G2, &wavel);
    tcsConfigGetTrack(CURRENT, G2, &tframe, &teqx,
       &GG2_tar_p0[0], &GG2_tar_p0[1], &GG2_tar_dt[0], &GG2_tar_dt[1],
       &GG2_tar_t0);
    tcsConfigGetDiffTrack(CURRENT, G2, &dtframe, &dteqx, 
       &t0, &dtheta1, &dtheta2);
    GG2_frame = tframe;
    GG2_eqx = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type, teqx.year);
    GG2_wavel = wavel;
    GG2_tar_t0 = t0;
    for ( ichop = 0; ichop < 3; ichop++ ) {
       tcsConfigGetOffset(CURRENT, G2, ichop, &coord, &theta1, &theta2);
       tcsCtOffToSph(tframe, GG2_tar_p0, coord, theta1, theta2, 
          GG2_tar_ob[ichop]);
       GG2_tar_p[ichop][0] = GG2_tar_p0[0] + GG2_tar_ob[ichop][0];
       GG2_tar_p[ichop][1] = GG2_tar_p0[1] + GG2_tar_ob[ichop][1];
    }

/* Generic Guider 3 */

    tcsConfigGetWavel(CURRENT, G3, &wavel);
    tcsConfigGetTrack(CURRENT, G3, &tframe, &teqx,
       &GG3_tar_p0[0], &GG3_tar_p0[1], &GG3_tar_dt[0], &GG3_tar_dt[1],
       &GG3_tar_t0);
    tcsConfigGetDiffTrack(CURRENT, G3, &dtframe, &dteqx, 
       &t0, &dtheta1, &dtheta2);
    GG3_frame = tframe;
    GG3_eqx = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type, teqx.year);
    GG3_wavel = wavel;
    GG3_tar_t0 = t0;
    for ( ichop = 0; ichop < 3; ichop++ ) {
       tcsConfigGetOffset(CURRENT, G3, ichop, &coord, &theta1, &theta2);
       tcsCtOffToSph(tframe, GG3_tar_p0, coord, theta1, theta2, 
          GG3_tar_ob[ichop]);
       GG3_tar_p[ichop][0] = GG3_tar_p0[0] + GG3_tar_ob[ichop][0];
       GG3_tar_p[ichop][1] = GG3_tar_p0[1] + GG3_tar_ob[ichop][1];
    }

/* Generic Guider 4 */

    tcsConfigGetWavel(CURRENT, G4, &wavel);
    tcsConfigGetTrack(CURRENT, G4, &tframe, &teqx,
       &GG4_tar_p0[0], &GG4_tar_p0[1], &GG4_tar_dt[0], &GG4_tar_dt[1],
       &GG4_tar_t0);
    tcsConfigGetDiffTrack(CURRENT, G4, &dtframe, &dteqx, 
       &t0, &dtheta1, &dtheta2);
    GG4_frame = tframe;
    GG4_eqx = slaEpco( tframe == FK4 ? 'B' : 'J', teqx.type, teqx.year);
    GG4_wavel = wavel;
    GG4_tar_t0 = t0;
    for ( ichop = 0; ichop < 3; ichop++ ) {
       tcsConfigGetOffset(CURRENT, G4, ichop, &coord, &theta1, &theta2);
       tcsCtOffToSph(tframe, GG4_tar_p0, coord, theta1, theta2, 
          GG4_tar_ob[ichop]);
       GG4_tar_p[ichop][0] = GG4_tar_p0[0] + GG4_tar_ob[ichop][0];
       GG4_tar_p[ichop][1] = GG4_tar_p0[1] + GG4_tar_ob[ichop][1];
    }

/* Current mount tracking coordinates. */
    dt = ttref - M_tar_t0;
    for (i = 0; i < 2; i++)
        M_tar_p[i] = M_tar_p0[i] +
            M_tar_ob[i] +
            (M_tar_dt[i] * dt);

/* Guide configuration. */
    tcsConfigGetGuide( CURRENT, 0, G1_act);
    tcsConfigGetGuide( CURRENT, 1, G2_act);
    tcsConfigGetGuide( CURRENT, 2, G3_act);
    tcsConfigGetGuide( CURRENT, 3, GG1_act);
    tcsConfigGetGuide( CURRENT, 4, GG2_act);
    tcsConfigGetGuide( CURRENT, 5, GG3_act);
    tcsConfigGetGuide( CURRENT, 6, GG4_act);

/* Filters. */
    tcsConfigGetTFilt(CURRENT, &F1_bw, &F1_maxv, &F1_grab, &F1_sc);
    tcsConfigGetPFilt(CURRENT, &F2_w[0], &F2_w[1], &F2_w[2], &F2_w[3],
                      &F2_bw, &F2_maxv, &F2_grab, &F2_sc);

/* Chop parameters. */
    for ( i = 1; i < 3; i++ ) {
       tcsConfigGetChop(CURRENT, i, &C_mode[i-1], &C_frame[i-1], &C_eqx[i-1], 
                        &throw, &pa, &pari);

/* If the position angle is relative to the IAA, replace the frame and
   equinox with the rotator frame and adjust the position angle. */
       if (pari) {
          C_frame[i-1] = R_frame;
          C_eqx[i-1] = R_eqx;
          pa += Ipa;
       }
       w = sin ( throw ) / cos ( throw );
       C_xieta[i-1][0] = w * sin ( pa );
       C_xieta[i-1][1] = w * cos ( pa );
       C_xieta_f[i-1] = sqrt ( 1.0 + w * w );

/* If the chop mode is relative then replace the target position with the
   source A position as a best efforts estimate so the the resulting OTMs
   are nearly correct. */
       if ( C_mode[i-1] ) {
          eqx.year = S_eqx[0];
          eqx.type = S_frame[0] == FK4 ? 'B' : 'J';
          eqx1.year = S_eqx[i];
          eqx1.type = S_frame[i] == FK4 ? 'B' : 'J';
          astCoco( S_tar_p[0][0], S_tar_p[0][1], pmotion, 
             S_frame[0], eqx, epochref, S_frame[i], eqx1, ttref, 
             aoprms, tel, &S_tar_p[i][0], &S_tar_p[i][1]);
          S_tar_pt[i][0] = S_tar_p[i][0];
          S_tar_pt[i][1] = S_tar_p[i][1];
      }
    }

/* Copy planet, orbit and ephemeris data. */
    tcsConfigGetPlanet( CURRENT, P_code, P_override_rates);
    tcsConfigGetOrbit(CURRENT, O_jform, O_epoch, O_orbinc, O_anode, 
        O_perih, O_aorq, O_e, O_aorl, O_dm);

/* Set new tracking identifier and enable the MCS and RCS subsystems. */
    Trackid = traw;
    McsActive = TRUE;
    RcsActive = TRUE;

    epicsMutexUnlock(TcsSemId);

    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsInitSource
 *
 *   Purpose:
 *   Initialize the kernel on startup.
 *
 *   Description:
 *   This routine is attached to the $(top)ak:initsource subroutine record
 *   and is triggered on startup to initialize the kernel with target
 *   parameters. Many of these target parameters are simply defaulted to
 *   zero but the demand azimuth and elevation will have been fetched from
 *   the current azimuth and elevation as provided by the MCS. This is done
 *   to prevent any unwanted movement of the mount on startup. The mount
 *   should be interlocked out until a valid zeroset has been received but
 *   if due to some error condition the interlocks fail, at least the TCS
 *   demands will only be telling the mount to go to where it currently
 *   thinks it is.
 *
 *   Whilst this routine is executing, the fast loop is stopped so it is
 *   safe to read and write items in the global database without locking.
 *
 *   Invocation:
 *   tcsInitSource(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    psub     (struct subRecord *)  Pointer to subroutine structure
 *
 *   Function value:
 *   (<)  status  (long) Return status
 *
 *   External functions:
 *   timeNow        (timelib)          Returns time to use as track ID
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */


long tcsInitSource(struct subRecord *psub)
{
    double az, el, r, rma, wavel, tt;
    double time, xz, yz, xs, ys, perp, orient;
    int i, ichop;
    struct TELP telp;
    struct EPOCH epoch;
    struct EPOCH eqx;
    struct PMPXRV pmotion;
    struct WCS_CTX ctx;
    struct WCS wcs;
    double g1_x, g1_y, g1_z, g2_x, g2_y, g2_z, g3_x, g3_y, g3_z;
    double gg1_x, gg1_y, gg1_z;
    double gg2_x, gg2_y, gg2_z;
    double gg3_x, gg3_y, gg3_z;
    double gg4_x, gg4_y, gg4_z;
    static int dbgLevel = DBG_NONE; /* debug level */

/* Fetch MCS and RCS subsystem positions from EPICS links. */
    az = psub->a;
    el = psub->b;
    rma = psub->c;

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsInitSource: Semaphore not created");
        return 0;
    }

/* Fetch guide probe positions (set by tcsSeqInit). */
    tcsProbeGetDefaults( 0, &g1_x, &g1_y, &g1_z);
    tcsProbeGetDefaults( 1, &g2_x, &g2_y, &g2_z);
    tcsProbeGetDefaults( 2, &g3_x, &g3_y, &g3_z);
/*
 * TODO
 * decide what to do about MCAO guiders. The point is we don't know at this
 * stage which physical probes the generic guiders are attached to. They
 * might not be attached to any.
 * For present set values to 0.0
 */
    gg1_x = gg1_y = gg1_z = 0.0;
    gg2_x = gg2_y = gg2_z = 0.0;
    gg3_x = gg3_y = gg3_z = 0.0;
    gg4_x = gg4_y = gg4_z = 0.0;

    epicsMutexLock(TcsSemId);
/* Copy set default values to mechanical positions and make them active
   by setting the subsystem active flags to false. */
    AzDef = az;
    ElDef = el;
    McsActive = FALSE;
    RmaDef = rma;
    RcsActive = FALSE;

/* Set the kernel output values as the fast loop can leave them unchanged
   at some spots in the sky (i.e. the zenith and the pole). */
    Az = az;
    El = el;
    Paim = rma;

/* Set precollimation Az/El to safe values */
    r = cos( el );
    X0 = - cos( az ) * r;
    Y0 = sin( az ) * r;
    Z0 = sin( el );

/* Set azimuth and rotator wrap flags. */
    if ( az < 0.0 ) AzWrap = -1;
    else if ( az > PI ) AzWrap = 1;
    else AzWrap = 0;
    if ( rma < -D90 ) RotWrap = -1;
    else if ( rma > D90 ) RotWrap = 1;
    else RotWrap = 0;

/* Reference time (TT MJD). */
    timeThenD( Tick0, TT, &tt);

/* Epoch now. */
    epoch.year = slaEpj( tt );
    epoch.type = 'J';

/* Equinox J2000. */
    eqx.year = 2000.0;
    eqx.type = 'J';

/* Reference wavelength. */
    wavel = Aoprms[8];

/* Fill in telescope parameters structure. */
    tcsOpticsGetFl(&telp.fl);
    telp.rma = rma;
    telp.an = An;
    telp.aw = Aw;
    telp.pnpae = Pnpae;
    telp.ca = Ca;
    telp.ce = 0.0;
/*
    telp.pox = M_por_p[0];
    telp.poy = M_por_p[1];
*/
    telp.pox = 0.0;
    telp.poy = 0.0;

/* Mount Target context. */
    M_frame = FK5;
    M_eqx = eqx.year;
    M_wavel = wavel;

/* Transform to FK5 position and drift rate. */
    /*
     * No proper motion. The values are uninitialized up to here, and having
     * something != 0 here will affect the initial M_tar_p0 and M_tar_dt
     */
    pmotion.pm = 0;

    astCocoR( az, el, pmotion, 0.0, 0.0, AZEL_MNT, eqx, epoch, M_frame, 
        eqx, tt, Aoprms, telp, &M_tar_p0[0], &M_tar_p0[1],
        &M_tar_dt[0], &M_tar_dt[1]);

/* Convert track rates from radians per second to radians per day. */
    M_tar_dt[0] *= 86400.0;
    M_tar_dt[1] *= 86400.0;
    M_tar_t0 = tt;

/* Offsets from base all zero. */
    M_tar_ob[0] = 0.0;
    M_tar_ob[1] = 0.0;

/* Net target position. */
    M_tar_p[0] = M_tar_p0[0];
    M_tar_p[1] = M_tar_p0[1];

/* WCS context. */
    ctx.ab0[0] = az;
    ctx.ab0[1] = el;
    ctx.tel = telp;
    for ( i = 0; i < 15; i++ ) ctx.aoprms[i] = Aoprms[i];
    for ( i = 0; i < 3; i++ ) {
       ctx.m2xy[i][0] = 0.0;
       ctx.m2xy[i][1] = 0.0;
    }
    ctx.time = Tick0;

/* Rotator angle. */
    if ( astCtx2tr( ctx, M_frame, eqx, wavel, 0, &wcs, &time) == 0 ) {
       slaDcmpf( wcs.coeffs, &xz, &yz, &xs, &ys, &perp, &orient);
       Ipa = PI - orient;
    } else {
       Ipa =  0.0;
    }
    Iaa = 0.0;
    Sia = 0.0;
    Cia = 1.0;

/* Rotator context. */
    R_frame = M_frame;
    R_eqx = M_eqx;

/* Source targets to yield zero M2 tip/tilt. */
    for (ichop = 0; ichop < 3; ichop++) {
        astXy2sq( S_por_p[ichop][0], S_por_p[ichop][1], wcs, 
            &S_tar_p0[ichop][0], &S_tar_p0[ichop][1]);
        S_frame[ichop] = M_frame;
        S_eqx[ichop] = M_eqx;
        S_wavel[ichop] = M_wavel;
        S_tar_p[ichop][0] = S_tar_p0[ichop][0];
        S_tar_p[ichop][1] = S_tar_p0[ichop][1];
        S_tar_dt[ichop][0] = M_tar_dt[0];
        S_tar_dt[ichop][1] = M_tar_dt[1];
        S_tar_t0[ichop] = M_tar_t0;
        S_tar_ob[ichop][0][0] = M_tar_ob[0];
        S_tar_ob[ichop][0][1] = M_tar_ob[1];
        S_tar_ob[ichop][1][0] = 0.0;
        S_tar_ob[ichop][1][1] = 0.0;
        S_tar_ob[ichop][2][1] = 0.0;
        S_tar_ob[ichop][2][0] = 0.0;
        S_tar_pc[ichop][0] = S_tar_p[ichop][0];
        S_tar_pc[ichop][1] = S_tar_p[ichop][1];
        S_tar_pt[ichop][0] = S_tar_p[ichop][0];
        S_tar_pt[ichop][1] = S_tar_p[ichop][1];
        S_por_p[ichop][0] = 0.0;
        S_por_p[ichop][1] = 0.0;
        S_por_ob[ichop][0][0] = 0.0;
        S_por_ob[ichop][1][0] = 0.0;
        S_por_ob[ichop][2][0] = 0.0;
        S_por_ob[ichop][0][1] = 0.0;
        S_por_ob[ichop][1][1] = 0.0;
        S_por_ob[ichop][2][1] = 0.0;
        S_por_pc[ichop][0] = S_por_p[ichop][0];
        S_por_pc[ichop][1] = S_por_p[ichop][1];
    }

/* Relative chop parameters. */
    for (ichop = 1; ichop < 3; ichop++) {
        C_frame[ichop-1] = M_frame;
        C_eqx[ichop-1] = M_eqx;
    }
    for (ichop = 1; ichop < 3; ichop++) {
        C_mode[ichop-1] = 1;
        C_xieta[ichop-1][0] = 0.0;
        C_xieta[ichop-1][1] = 0.0;
        C_xieta_f[ichop-1] = 1.0;
    }

/* Guider VT contexts. */
    G1_frame = M_frame;
    G1_eqx = M_eqx;
    G1_wavel = M_wavel;
    G2_frame = M_frame;
    G2_eqx = M_eqx;
    G2_wavel = M_wavel;
    G3_frame = M_frame;
    G3_eqx = M_eqx;
    G3_wavel = M_wavel;
    GG1_frame = M_frame;
    GG1_eqx = M_eqx;
    GG1_wavel = M_wavel;
    GG2_frame = M_frame;
    GG2_eqx = M_eqx;
    GG2_wavel = M_wavel;
    GG3_frame = M_frame;
    GG3_eqx = M_eqx;
    GG3_wavel = M_wavel;
    GG4_frame = M_frame;
    GG4_eqx = M_eqx;
    GG4_wavel = M_wavel;

/* Guider VT targets. */
    astXy2sq( g1_x, g1_y, wcs, &G1_tar_p0[0], &G1_tar_p0[1]);
    G1_tar_dt[0] = M_tar_dt[0];
    G1_tar_dt[1] = M_tar_dt[1];
    G1_tar_t0 = M_tar_t0;
    for (ichop = 0; ichop < 3; ichop++) {
        G1_tar_ob[ichop][0] = 0.0;
        G1_tar_ob[ichop][1] = 0.0;
        G1_tar_p[ichop][0] = G1_tar_p0[0];
        G1_tar_p[ichop][1] = G1_tar_p0[1];
    }

    astXy2sq( g2_x, g2_y, wcs, &G2_tar_p0[0], &G2_tar_p0[1]);
    G2_tar_dt[0] = M_tar_dt[0];
    G2_tar_dt[1] = M_tar_dt[1];
    G2_tar_t0 = M_tar_t0;
    for (ichop = 0; ichop < 3; ichop++) {
        G2_tar_ob[ichop][0] = 0.0;
        G2_tar_ob[ichop][1] = 0.0;
        G2_tar_p[ichop][0] = G2_tar_p0[0];
        G2_tar_p[ichop][1] = G2_tar_p0[1];
    }

    astXy2sq( g3_x, g3_y, wcs, &G3_tar_p0[0], &G3_tar_p0[1]);
    G3_tar_dt[0] = M_tar_dt[0];
    G3_tar_dt[1] = M_tar_dt[1];
    G3_tar_t0 = M_tar_t0;
    for (ichop = 0; ichop < 3; ichop++) {
        G3_tar_ob[ichop][0] = 0.0;
        G3_tar_ob[ichop][1] = 0.0;
        G3_tar_p[ichop][0] = G3_tar_p0[0];
        G3_tar_p[ichop][1] = G3_tar_p0[1];
    }

    astXy2sq( gg1_x, gg1_y, wcs, &GG1_tar_p0[0], &GG1_tar_p0[1]);
    GG1_tar_dt[0] = M_tar_dt[0];
    GG1_tar_dt[1] = M_tar_dt[1];
    GG1_tar_t0 = M_tar_t0;
    for (ichop = 0; ichop < 3; ichop++) {
        GG1_tar_ob[ichop][0] = 0.0;
        GG1_tar_ob[ichop][1] = 0.0;
        GG1_tar_p[ichop][0] = GG1_tar_p0[0];
        GG1_tar_p[ichop][1] = GG1_tar_p0[1];
    }

    astXy2sq( gg2_x, gg2_y, wcs, &GG2_tar_p0[0], &GG2_tar_p0[1]);
    GG2_tar_dt[0] = M_tar_dt[0];
    GG2_tar_dt[1] = M_tar_dt[1];
    GG2_tar_t0 = M_tar_t0;
    for (ichop = 0; ichop < 3; ichop++) {
        GG2_tar_ob[ichop][0] = 0.0;
        GG2_tar_ob[ichop][1] = 0.0;
        GG2_tar_p[ichop][0] = GG2_tar_p0[0];
        GG2_tar_p[ichop][1] = GG2_tar_p0[1];
    }

    astXy2sq( gg3_x, gg3_y, wcs, &GG3_tar_p0[0], &GG3_tar_p0[1]);
    GG3_tar_dt[0] = M_tar_dt[0];
    GG3_tar_dt[1] = M_tar_dt[1];
    GG3_tar_t0 = M_tar_t0;
    for (ichop = 0; ichop < 3; ichop++) {
        GG3_tar_ob[ichop][0] = 0.0;
        GG3_tar_ob[ichop][1] = 0.0;
        GG3_tar_p[ichop][0] = GG3_tar_p0[0];
        GG3_tar_p[ichop][1] = GG3_tar_p0[1];
    }

    astXy2sq( gg4_x, gg4_y, wcs, &GG4_tar_p0[0], &GG4_tar_p0[1]);
    GG4_tar_dt[0] = M_tar_dt[0];
    GG4_tar_dt[1] = M_tar_dt[1];
    GG4_tar_t0 = M_tar_t0;
    for (ichop = 0; ichop < 3; ichop++) {
        GG4_tar_ob[ichop][0] = 0.0;
        GG4_tar_ob[ichop][1] = 0.0;
        GG4_tar_p[ichop][0] = GG4_tar_p0[0];
        GG4_tar_p[ichop][1] = GG4_tar_p0[1];
    }

/* Guide state states. */
    for (i= 0; i< 3; i++) {
        for (ichop = 0; ichop < 3; ichop++) {
            G1_act[i][ichop] = 0;
            G2_act[i][ichop] = 0;
            G3_act[i][ichop] = 0;
            GG1_act[i][ichop] = 0;
            GG2_act[i][ichop] = 0;
            GG3_act[i][ichop] = 0;
            GG4_act[i][ichop] = 0;
        }
    }

/* Filters: short-circuit at initialization. */
    F1_bw = 0.05;
    F1_maxv = 3.0e7;
    F1_grab = 1.0;
    F1_sc = 1;
    F2_w[0] = 1.0;
    F2_w[1] = 0.0;
    F2_w[2] = 0.0;
    F2_w[3] = 0.0;
    F2_bw = 0.05;
    F2_maxv = 3.0e7;
    F2_grab = 1.0;
    F2_sc = 1;

/* Mount differential track rates are applied after the filter,
   so set them to zero. */
    M_tar_dt[0] = 0.0;
    M_tar_dt[1] = 0.0;

/* Nod state (A). */
    Nod = 0;

/* Planet code. */
    for (i = 0; i < 11; i++) {
      P_code[i] = NO_PLANET;
      P_override_rates[i] = 0 ;
    }

/* Orbital elements. */
    for (i = 0; i < 11; i++) {
      O_jform[i] = 0;
      O_epoch[i] = 0.0;
      O_orbinc[i] = 0.0;
      O_anode[i] = 0.0;
      O_perih[i] = 0.0;
      O_aorq[i] = 0.0;
      O_e[i] = 0.0;
      O_aorl[i] = 0.0;
      O_dm[i] = 0.0;
    }

/* Chop mode. */
    ChopMode = NOCHOP;

/* Initial track ID. */
    Trackid = Tick0;

    epicsMutexUnlock(TcsSemId);
    return 0;


}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsTelConfig
 *
 *   Purpose:
 *   Initializes the pointing origins.
 *
 *   Description:
 *   Reads the pointing origin parameters from EPICS into global memory.
 *
 *   Invocation:
 *   tcsTelConfig(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    psub     (struct subRecord *) Pointer to subroutine record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)      global memory protection semaphore
 *   (<)   M_por_p   (double)   mount accumulated pointing origin
 *   (<)   M_por_p0  (double)   mount base pointing origin
 *   (<)   M_por_ob  (double)   mount pointing origin offset
 *   (<)   S_por_p   (double)   source accumulated pointing origin
 *   (<)   S_por_p0  (double)   source base pointing origin
 *   (<)   S_por_ob  (double)   source pointing origin offset
 *
 *   Prior requirements:
 *   tcsApplInit must have been called at least once.
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


long tcsTelConfig(struct subRecord *psub)
{
    double xim, yim;
    int ichop;

    xim = psub->a;
    yim = psub->b;

  if( TcsSemId) {

    epicsMutexLock(TcsSemId);
    M_por_p0[0] = xim;
    M_por_p0[1] = yim;
    M_por_ob[0] = 0.0;
    M_por_ob[1] = 0.0;
    M_por_p[0] = xim;
    M_por_p[1] = yim;
    for (ichop = 0; ichop < 3; ichop++) {
        S_por_p0[ichop][0] = xim;
        S_por_p0[ichop][1] = yim;
        S_por_ob[ichop][0][0] = 0.0;
        S_por_ob[ichop][0][1] = 0.0;
        S_por_ob[ichop][1][0] = 0.0;
        S_por_ob[ichop][1][1] = 0.0;
        S_por_ob[ichop][2][0] = 0.0;
        S_por_ob[ichop][2][1] = 0.0;
        S_por_p[ichop][0] = xim;
        S_por_p[ichop][1] = yim;
    }
    epicsMutexUnlock(TcsSemId);
  }
  return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDriveMCS
 *
 *   Purpose:
 *   Output demand positions to the Mount Control System.
 *
 *   Description:
 *   This routine outputs demand azimuth and elevation positions to the
 *   Mount Control System. It does this by fetching the latest values
 *   from the astrometric kernel and converting the azimuth to the nearest
 *   position allowed by the MCS. The algorithm used has the property that
 *   if the azimuth changes continuously in one direction the mount will
 *   reach its azimuth limit and stay there; it will never "spontaneously"
 *   unwrap.
 *
 *   If the current coordinate system is "mount" the values are sent to the
 *   mount unchanged.
 *
 *   Both the elevation and azimuth are clipped to the mount limits before
 *   being written to the output.
 *
 *   Invocation:
 *   tcsDriveMCS (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 *
 *   a => Elevation limit (rads)
 *   b => Azimuth lower limit (rads)
 *   c => Azimuth upper limit (rads)
 *
 *   Epics outputs :
 *
 *   vala => demand data array (see below)
 *   valb => demand azimuth (degs)
 *   valc => demand elevation (degs)
 *   vale => demand frame
 *   valf => demand equinox 
 *   valg => demand azimuth (rads)
 *   valh => demand elevation (rads)
 *
 *   Function value:
 *   Return status
 *
 *   External variables:
 *   Any external variables used in this function or procedure
 *
 *   Deficiencies:
 *   There is no mechanism for unwrapping the azimuth axis other than
 *   entering a demand in mount az/el coordinates.
 *-
 */
/* *INDENT-ON* */


long tcsDriveMCS(struct genSubRecord *pgsub)
{
    double MCSdemand[5];        /* output demand data array */
    double FLinfo[15] = {0};          /* output FastLoop debug info array */
    double tick;                /* copy of TAI of demand */
    double tnow;                /* TAI when data output */
    double az;                  /* azimuth demand */
    static double paz = 0.0;    /* previous azimuth demand */
    static int rot = 0;         /* number of rotations to add to demand */
    double el;                  /* elevation demand */
    double azdef;               /* default azimuth */
    double eldef;               /* default elevation */
    int active;                 /* subsystem active flag */
    FRAMETYPE frame;            /* coordinate system */
    double eqx;                 /* equinox */
    double ellimit;             /* elevation limit */
    double azhilimit;           /* high azimuth limit */
    double azlolimit;           /* low azimuth limit */
    double trackid;             /* track identifier */
    static double oldTrackid = 0.0;  /* previous trackid */
    static int dbgLevel = DBG_NONE; /* debug level */
    int inPosition;             /* in position flag */
    int inPosReason;            /* in position reason */
    int i;
    static double tnowold=0.0;

    double traw;                /* copy of TAI traw (Debug info) */
    double dmd_cnt;             /* copy of demand counter (Debug info) */
    double corr_cnt;            /* copy of tick correction number (Debug info) */
    double corr_02;             /* copy of tick correction number < 20[ms] (Debug info) */
    double corr_08;             /* copy of tick correction number > 80[ms] (Debug info) */
    double applyDeltaT;         /* Tick - Traw */
    double flt_cnt;             /* tcsEFastLoop fault counter */
//    double flTime;              /* tcsEFastLoop execution time */
    double deltaTraw;           /* Time between FastLoop executions */
    double deltaTick;           /* Time between Ticks */
    double dtGetTelRD;          /* Execution time of tcsGetTelescopeRADec */

/* Read limits from input. */
    ellimit = *(double *) pgsub->a;
    azhilimit = *(double *) pgsub->b;
    azlolimit = *(double *) pgsub->c;

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsDriveMCS: Semaphore not created");
        return 0;
    }

/* Pick up demands from global memory. */
    epicsMutexLock(TcsSemId);
    tick = Tick;
    az = Az;
    el = El;
    azdef = AzDef;
    eldef = ElDef;
    active = McsActive;
    frame = M_frame;
    eqx = M_eqx;
    trackid = Trackid;
    inPosition = InPosition;
    inPosReason = InPosReason;
    /* Debug Info*/
    traw = Traw;
    dmd_cnt = Dmd_cnt;
    corr_cnt = Corr_cnt;
    corr_02 = Corr_02;
    corr_08 = Corr_08;
    applyDeltaT = ADeltaT;
    flt_cnt = Flt_cnt;
//    flTime = FlTime;
    deltaTraw = DTraw;
    deltaTick = DTick;
    dtGetTelRD = DtGetTelRD;
    epicsMutexUnlock(TcsSemId);

    if (active) {

    /* The azimuth generated by the pointing code is in the range 0-360 and
       this must be mapped to the appropriate equivalent angle in the range
       -270/+360. In addition, when the telescope is tracking normally and it
       reaches one of the wrap limits we don't want it to jump back to 0 (or
       +180): we want it to stay at the limit. */

    /* Adjust the number of rotations if the demand has passed through zero. */
        if (paz - az > PI)
            rot++;
        else if (az - paz > PI)
            rot--;

    /* Normalize to range +/- wrap limit +360 by adjusting the the number
       of rotations. */
        if (az + 2.0 * PI * (double) rot > 4.0 * PI)
            rot--;
        else if (az + 2.0 * PI * (double) rot < -3.0 * PI)
            rot++;

    /* If the wrap flag is -1 this means that the desired azimuth is in the
       range -180/+180, so if the demand is > 180 we subtract one rotation. */
        if (AzWrap == -1)
            rot = az > 1.0 * PI ? -1 : 0;

    /* If the wrap flag is 1 this means that the desired azimuth is in the
       range 0/+360, so we subtract one rotation if the demand is > 360.
       Since this can't happen, rot is simply set to 0. */
        else if (AzWrap == 1)
            rot = 0;

    /* Wrap flag zero means leave the wrap state as it is. */
        else if (AzWrap == 0) {

        /* If the demand is < 180, the number of rotations must be zero. */
            if (az < 1.0 * PI)
                rot = 0;

        /* Otherwise select which ever of 0 and -1 is gives the point
           closest to the previous azimuth. */
            else {

            /* If the previous azimuth was also greater than 180, the wrap
               state remains the same. */
                if (paz > PI) {
                    if (rot > 0)
                        rot = 0;
                    else if (rot < 0)
                        rot = -1;

            /* Otherwise if the new azimuth is more than 180 greater than
               the previous go to negative wrap. */
                } else {
                    if (az - paz > PI)
                        rot = -1;
                    else
                        rot = 0;
                }
            }
        }

    /* Save the new demand azimuth. */
        paz = az;

    /* Cancel the wrap flag in order to resume normal tracking. */
        AzWrap = 2;

    /* Compute the demands to send to the mount. */
        azdef = az + 2.0 * PI * (double) rot;
        eldef = el;
    }

/* Clip demands. */
    if (eldef < ellimit) {
        eldef = ellimit;
        inPosition = 0;
        inPosReason = IPR_ELLOW;
    } else if (eldef > DPIBY2) {
        eldef = DPIBY2 ;
        inPosition = 0 ;
        inPosReason = IPR_ELHIGH;
    } 
    if (azdef > azhilimit) {
        azdef = azhilimit;
        inPosition = 0;
        inPosReason = IPR_AZHIGH;
    } else if (azdef < azlolimit) {
        azdef = azlolimit;
        inPosition = 0;
        inPosReason = IPR_AZLOW;
    }

/*
** Set output demand array for MCS:
** Element 0  = time now
** Element 1  = target time
** Element 2  = track identifier
** Element 3  = demanded Azimuth
** Element 4  = demanded Elevation
*/

    if ((i = timeNow(&tnow)) != 0 ) {
    	printf("tcsDriveMCS: timeNow failed with i=%d diff=%f \n",i, (tnow - tnowold));
    }
    tnowold = tnow; 
    MCSdemand[0] = tnow;
    MCSdemand[1] = tick;
    MCSdemand[2] = trackid;
    MCSdemand[3] = azdef * R2D;
    MCSdemand[4] = eldef * R2D;

/* Copy array contents to genSub record output field A. */
    memcpy(pgsub->vala, MCSdemand, 5 * sizeof(double));

/* For display, put az and el out on B and C and G & H. */
    *(double *) pgsub->valb = azdef * R2D;
    *(double *) pgsub->valc = eldef * R2D;
    *(double *) pgsub->valg = azdef ;
    *(double *) pgsub->valh = eldef ;

/* Frame and equinox output on E and F. */
    *(double *) pgsub->vale = (double) frame;
    *(double *) pgsub->valf = (double) eqx;

/* Generate Debug Info array*/
/*
** Set output debug array:
** Element 0  = Time at which commands is sent to MCS
** Element 1  = traw from Fast Loop
** Element 2  = Tick from Fast Loop
** Element 3  = Time to execute demand since calculation (tick - traw)
** Element 4  = Time between FastLoop executions
** Element 5  = Time it takes to take and release reading semaphore on tcsFastLoop
** Element 6  = Time it takes to take and release writing semaphore on tcsFastLoop
** Element 7  = Demand Number
** Element 8  = Tick Correction Number
** Element 9  = correction under 20[ms]
** Element 10  = correction over 80[ms]
** Element 11  = Fast Loop Fault counter
** Element 12  = Available
** Element 13  = demanded Azimuth
** Element 14  = demanded Elevation
*/

    FLinfo[0] = tnow;
    FLinfo[1] = traw;
    FLinfo[2] = tick;
    FLinfo[3] = applyDeltaT;
    FLinfo[4] = deltaTraw;
    FLinfo[5] = deltaTick;
    FLinfo[6] = dtGetTelRD;
    FLinfo[7] = dmd_cnt;
    FLinfo[8] = corr_cnt;
    FLinfo[9] = corr_02;
    FLinfo[10] = corr_08;
    FLinfo[11] = flt_cnt;
    FLinfo[12] = 0.0;
    FLinfo[13] = azdef * R2D;
    FLinfo[14] = eldef * R2D;


    memcpy(pgsub->vali, FLinfo, 15 * sizeof(double));


/* Save new default demands. */
    epicsMutexLock(TcsSemId);
    AzDef = azdef;
    ElDef = eldef;
    InPosition = inPosition;
    InPosReason = inPosReason;
    epicsMutexUnlock(TcsSemId);

/* Output diagnostics dependent on debug level;
   these diagnostics are used for ST02003 */
    if (trackid != oldTrackid) {
      DBGMSGREAL(DBG_FULL, "tcsDriveMCS: completed at ", tnow) ;
      oldTrackid = trackid ;
    }

    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDriveCRS
 *
 *   Purpose:
 *   Output demand rotator angle to the Cassegrain Rotator Control System.
 *
 *   Description:
 *   This routine outputs demand rotator mechanical angle to the Cassegrain
 *   Rotator Control System. It does this by fetching the latest values
 *   from the astrometric kernel and converting to the range -270/+270.
 *   The algorithm is the same as that used for the azimuth axis.
 *   Another function performed is to store the current state of the
 *   following status. This is needed by the fast loop but is stored
 *   here simply because of a lack of inputs on the fast loop gensub.
 *
 *   Epics inputs:
 *   a => Rotator high limit (rads)
 *   b => Rotator lower limit (rads)
 *   c => Rotator follow status (0 = not following)
 *
 *   Epics outputs:
 *   vala -> demand data array (see below)
 *   valb -> rotator demand (degs)
 *   valc -> rotator pa (degs)
 *   vald -> no. of 2pi rotations (for diagnostics)
 *
 *   Invocation:
 *   tcsDriveCRS (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub structure
 *
 *   Function value:
 *   Return status
 *
 *   Deficiencies:
 *   The first time this routine is called it needs to set up some
 *   initialization values. To do this properly it needs the current
 *   rotator mechanical angle. If this is not available it will get
 *   zero and may set up the initialization values incorrectly. Previous
 *   versions implicitly assumed a value of zero so hopefully the new
 *   initialization is no worse than the old.
 *-
 */
/* *INDENT-ON* */


long tcsDriveCRS(struct genSubRecord *pgsub)
{
    double CRSdemand[4];        /* output demand data array */
    double tick;                /* copy of TAI of demand */
    double tnow;                /* TAI when data sent to CRS */
    double pa;                  /* rotator angle demand */
    double rpadef;              /* default rotator angle */
    static double ppa = 0.0;    /* previous rotator angle demand */
    static int rot = 0;         /* number of rotations to add to demand */
    int active;                 /* subsystem active flag */
    double hilimit;             /* high rotator wrap limit */
    double lolimit;             /* low rotator wrap limit */
    double trackid;             /* track identifier */
    int inPosition;             /* in position flag */
    int inPosReason;            /* in position reason */
    long following ;            /* Follow flag */
    double rma ;                /* Current rotator angle (rads) */
    static int first = 1;       /* Flag for first call */
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsDriveCRS: Semaphore not created");
        return 0;
    }

/* Read limits from input. */
    hilimit = *(double *) pgsub->a;
    lolimit = *(double *) pgsub->b;
    following = *(long *) pgsub->c;
    if (following)
      CrcsFollowStat = 1 ;
    else
      CrcsFollowStat = 0;

/* Pick up demands from global memory. */
    epicsMutexLock(TcsSemId);
    tick = Tick;
    pa = Paim;
    rpadef = RmaDef;
    active = RcsActive;
    trackid = Trackid;
    inPosition = InPosition;
    inPosReason = InPosReason;
    rma = Rma ;
    epicsMutexUnlock(TcsSemId);

    if (active) {

    /* Add guiding demand */
        pa += tcsGetRotCorr();

    /* Try and set up the correct initialization */
       if (first) {
         if (rma < 0.0) {
           ppa = rma + 2.0 * PI;
           rot = -1;
         } else {
           ppa = rma ;
           rot = 0;
         }
         first = 0 ;
       }

    /*
    ** The PA generated by the pointing code is in the range 0-360 and
    ** this must be mapped to the appropriate equivalent angle in the range
    ** +/-270. In addition, when the telescope is tracking normally and it
    ** reaches one of the wrap limits we don't want it to jump back to -90
    ** (or +90) we want it to stay at the limit.
    */

    /* Adjust the number of rotations if the demand has passed through zero. */
        if (ppa - pa > PI)
            rot++;
        else if (pa - ppa > PI)
            rot--;

    /* Normalize to range +/- wrap limit +360 by adjusting the the number
       of rotations */
        if (pa + 2.0 * PI * (double) rot > (2.0 * PI + hilimit))
            rot--;
        else if (pa + 2.0 * PI * (double) rot < (-2.0 * PI + lolimit))
            rot++;

    /* If the wrap flag is -1 this means that the desired angle is in the
       range -270/+90, so if the demand is > 90 we subtract one rotation. */
        if (RotWrap == -1)
            rot = pa > 2.0 * PI + lolimit ? -1 : 0;

    /* If the wrap flag is 1 this means that the desired angle is in the
       range -90/+270 so we subtract one rotation if the demand is > 270.  */
        else if (RotWrap == 1)
            rot = pa > hilimit ? -1 : 0;

    /* Wrap flag zero means leave the wrap state as it is. */
        else if (RotWrap == 0) {

        /* If the demand is < 90, the number of rotations must be zero. */
            if (pa < 2.0 * PI + lolimit)
                rot = 0;

        /* If the demand is > 270, the number of rotations must be -1. */
            else if (pa > hilimit)
                rot = -1;

        /* Otherwise select which ever of 0 and -1 is closest to the
           current value. */
            else {
                if (rot > 0)
                    rot = 0;
                else if (rot < 0)
                    rot = -1;
            }
        }

/*
        printf("ppa, pa, RotWrap, rot %f %f %d %d\n", ppa/D2R, pa/D2R, RotWrap,
rot);
*/
    /* Save the new demand rotator angle. */
        ppa = pa;

    /* Cancel the wrap flag in order to resume normal tracking. */
        RotWrap = 2;

    /* Compute the angle to send to the instrument mount. */
        rpadef = pa + 2.0 * PI * (double) rot;
    }

/* Clip demand. */
    if (rpadef > hilimit) {
        rpadef = hilimit;
        inPosition = 0;
        inPosReason = IPR_ROTHIGH;
    } else if (rpadef < lolimit) {
        rpadef = lolimit;
        inPosition = 0;
        inPosReason = IPR_ROTLOW;
    }

/*
** Set output demand array for CRS:
** Element 0  = time now
** Element 1  = target time
** Element 2  = track identifier
** Element 3  = demanded rotator angle
*/

    (void) timeNow(&tnow);
    CRSdemand[0] = tnow;
    CRSdemand[1] = tick;
    CRSdemand[2] = trackid;
    CRSdemand[3] = rpadef/D2R;

/* Copy array contents to genSub record output field A. */
    memcpy(pgsub->vala, CRSdemand, 4 * sizeof(double));

/* For display, put rotator angle out on B etc. */
    *(double *) pgsub->valb = rpadef/D2R;
    *(double *) pgsub->valc = pa/D2R;
    *(long *)   pgsub->vald = (long)rot ;

/* Save new default demands. */
    epicsMutexLock(TcsSemId);
    RmaDef = rpadef;
    InPosition = inPosition;
    InPosReason = inPosReason;
    epicsMutexUnlock(TcsSemId);

    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDriveECS
 *
 *   Purpose:
 *   Output demand positions to the Enclosure Control System.
 *
 *   Description:
 *   This routine outputs demand azimuth and elevation positions to the
 *   Enclosure Control System. It does this by fetching the latest azimuth
 *   and elevation values from the astrometric kernel and then on the 
 *   basis of the current operating modes of the dome and shutters, computing
 *   the individual positions of the shutters and dome. All demands are
 *   clipped as neccesary to ensure that only valid data is sent to the ECS. 
 *   The routine also calculates the fraction of the primary mirror that
 *   is vignetted by the current positions of the mechanisms.
 *   The routines are complicated by the fact that the ECS & PLC do not
 *   like receiving move commands in rapid succession. The PLC will 
 *   actually discard any demands to the shutters received whilst it is moving
 *
 *   Epics inputs:
 *
 *   a => mount elevation lower limit (rads)
 *   b => azimuth tolerance for dome moves in basic mode (rads)
 *   c => current dome azimuth (degs)
 *   d => current top shutter position (degs)
 *   e => current bottom shutter position (degs)
 *   f => current mount azimuth (degs)
 *   g => current mount elevation (degs)
 *
 *   Epics outputs:
 *
 *   vala => demand data array (see below)
 *   valb => trigger for dome moves
 *   valc => dome azimuth demand (degs)
 *   vald => trigger for shutter moves
 *   vale => top shutter elevation demand (degs)
 *   valf => bottom shutter elevation demand (degs)
 *   valg => dome vignette alarm limit
 *   valh => dome vignette fraction
 *   vali => flag to indicate if there is a valid time to limit
 *   valj => time to limit (secs)
 *
 *   Invocation:
 *   tcsDriveECS (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub structure
 *
 *   Function value:
 *      (<)    status    (long)   Return status 0 = OK
 *
 *-
 */
/* *INDENT-ON* */

long tcsDriveECS(struct genSubRecord *pgsub)
{
    int i, j;
    double ECSdemand[6];        /* output demand data array */
    double tick;                /* copy of TAI of demand */
    double tnow;                /* TAI when data sent to ECS */
    double az;                  /* azimuth demand */
    double el;                  /* elevation demand */
    double ellimit;             /* elevation limit (rads) */
    double trackid;             /* track identifier */
    double posnTol;             /* position tolerance in Basic mode (rads)*/
    double domeTol;             /* tolerance for dome moves (rads) */
    double elTopShtr;           /* top shutter demand (rads) */
    double elBotShtr;           /* bottom shutter demand (rads) */
    static double elTopVShtr;   /* virtual shutter limit (rads) */
    static double elBotVShtr;   /* virtual shutter limit (rads) */
    static double domeAz ;      /* Dome azimuth demand (rads) */
    int    issueMoveDomeNow;    /* flag to generate a move_dome command */
    int    issueMoveShtrsNow;   /* flag to generate a move_shtrs command */
    int    issueMoves ;         /* flag to isuue move or follow commands */
    int    enabledDome;         /* true if dome is enabled in TCS */
    int    enabledShtrs;        /* true if shutters are enabled in TCS */
    ENCMODE encMode ;           /* enclosure operating mode */
    static ENCMODE oldEncMode ; /* Previous enclosure operating mode */
    double currAz ;             /* current azimuth of dome (rads) */
    double currTopShtr ;        /* current top shutter elevation (rads) */
    double currBotShtr ;        /* current bottom shutter elevation (rads) */
    double daz ;                /* position difference of dome */
    double dTopShtr;            /* position difference of top shutter */
    double dBotShtr;            /* position difference of bottom shutter */
    double coselev ;            /* cos of elevation */
    double vfrac ;              /* vignette fraction */
    double vfracHigh ;          /* vignette fraction alarm limit */
    double currAzMount;         /* current mount azimuth (rads) */
    double currElMount;         /* current mount elevation (rads) */
    double ae2mt[3][3];         /* AzEl to mount rotation matrix */
    double x0, y0, z0 ;         /* Cartesian components of pre-flexure mount */
    double x, y, z ;            /* Cartesian components of topo az/el */
    double clat, slat ;         /* Cosine and sine of site latitude */
    double startHA ;            /* Start HA (rads) */
    double endHA ;              /* End HA (rads) */
    double startDec ;           /* Start declination (rads) */
    double ssdec, csdec ;       /* Cos & Sin of starting declination */
    double timeToGo ;           /* Time to next enclosure limit (secs) */
    ENCLIMIT encLimit ;         /* Enclosure limit type */
    FRAMETYPE mframe ;          /* demand frame of mount */
    int issuedSlew;             /* TRUE if slew command is in configuration */
    static double tLimit ;      /* Estimated TAI when limit is reached */
    static double tUpdate ;     /* TAI at which new limit time is calculated */
    static int validTimes = FALSE; /* Flag to show validity of time limits */
    static double timeToNextMove = 86400.0 ; /* Default is 1 day */
    static double timeToNextUpdate = 10.0 ;  /* Default is 10 seconds */
    double dha ;                /* Time step (rads) */
    static int first = TRUE;    
    int encModeChanged ;        /* True if enclosure mode has changed */
    SHUTTERMODE shutMode ;      /* Current shutter mode */
    static SHUTTERMODE oldShutMode ;  /* Previous shutter mode */
    double slitHeight ;         /* Slit height (mm) */
    static double lastDomeRef ;     /* Last dome reference position */
    static double lastTopShtrRef ;  /* Last top shutter reference posn. */
    static double lastBotShtrRef ;  /* Last bottom shutter reference posn. */
    double dDomeDem ;               /* Increment between dome demands */
    double dTopShtrDem ;            /* Ditto for top shutter */
    double dBotShtrDem;             /* Ditto for bottom shutter */
    static double vignTol = 0.1 ;   /* Tolerance (degs) for vignette moves */
    int domeMoving ;                /* Flag to show if dome is moving */
    int topShtrMoving ;             /* Ditto for top shutter */
    int botShtrMoving ;             /* Ditto for bottom shutter */
    static double prevCurrAz ;      /* Dome azimuth during last routine call */
    static double prevCurrTopShtr;  /* Top shutter elevation in last call */
    static double prevCurrBotShtr;  /* Ditto for bottom shutter */
    static int domeMoveCounter = 0; /* Counter to delay move demands */
    static int shtrMoveCounter = 0; /* Ditto for shutters */
    double moveTolerance ;          /* checks if mechanisms are moving */
    double dMove ;                  /* Position error (rads) */
    double vTopShtr, vBotShtr ;     /* Effective shutter positions (rads) */
    static int dbgLevel = DBG_NONE; /* debug level */

/* Read elevation limit from input. */
    ellimit = *(double *) pgsub->a;

/* Read tolerance parameter from input. */
    posnTol = *(double *)pgsub->b;

/* Read current positions of dome and shutters. */
    currAz = *(double *) pgsub->c * D2R;
    currTopShtr = *(double *) pgsub->d * D2R;
    currBotShtr  = *(double *) pgsub->e * D2R;

/* Read current position of mount. */
    currAzMount = *(double *) pgsub->f * D2R;
    currElMount = *(double *) pgsub->g * D2R;

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsDriveECS: Semaphore not created");
        return 0;
    }

/* Pick up from global memory. */
    epicsMutexLock(TcsSemId);
    tick = Tick;
    az = Az;
    el = El;
    mframe = M_frame;
    trackid = Trackid;
    x0 = X0;
    y0 = Y0;
    z0 = Z0 ;
    for ( i = 0; i < 3; i++ ) {
       for ( j = 0; j < 3; j++ ) {
          ae2mt[i][j] = Ae2mt[i][j];
       }
    }
    clat = Clat ;
    slat = Slat ;
    epicsMutexUnlock(TcsSemId);

/* Fetch current time */
    (void)timeNow(&tnow);

/* Calculate default positions for slit edges. */
    tcsEcsCalcSlit (el, ellimit, CENTRED, &elTopShtr, &elBotShtr, &elTopVShtr,
      &elBotVShtr) ;

/* Now calculate whether a move command is needed for either the dome or
   shutters. */

    issueMoveDomeNow = 0; 
    issueMoveShtrsNow = 0;

/* Set time step to 4 minutes */
    dha = 240.0 * S2R ;

    tcsEcsGetIssueMoves (&issueMoves) ;
    tcsEcsGetEnableFlags (&enabledDome, &enabledShtrs) ;
    tcsEcsGetUserParams (&encMode, &shutMode, &slitHeight) ;

/* Calculate the current vignette fraction */
    tcsEcsVignette (currAzMount, currElMount, currAz, currTopShtr,
                    currBotShtr, &vfrac) ;

/* Check if a recalculation of the enclosure position is required due to 
*  a change of mode.
*/
    if (first) {
      oldEncMode      = encMode ;
      oldShutMode     = shutMode ;
      lastDomeRef     = currAz ;
      lastTopShtrRef  = currTopShtr ;
      lastBotShtrRef  = currBotShtr ;
      prevCurrAz      = currAz ;
      prevCurrTopShtr = currTopShtr ;
      prevCurrBotShtr = currBotShtr ;
      first = FALSE ;
    }
    if ((oldEncMode != encMode) || (oldShutMode != shutMode) ) {
      encModeChanged = TRUE ;
      oldEncMode = encMode ;
      oldShutMode = shutMode ;
    } else {
      encModeChanged = FALSE ;
    }

/* Check whether the dome and shutters are moving */
    domeMoving = 0 ;
    topShtrMoving = 0 ;
    botShtrMoving = 0 ;
    moveTolerance = 0.01 * D2R ;
    dMove = prevCurrAz - currAz ;
    if (dMove < 0.0) dMove = -dMove ;
    if (dMove > moveTolerance) 
      domeMoving = 1 ;
    dMove = prevCurrTopShtr = currTopShtr ;
    if (dMove < 0.0) dMove = -dMove ;
    if (dMove > moveTolerance)
      topShtrMoving = 1 ;
    dMove = prevCurrBotShtr = currBotShtr ;
    if (dMove < 0.0) dMove = -dMove ;
    if (dMove > moveTolerance)
      botShtrMoving = 1 ;

/* Reset positions ready for next pass */
    prevCurrAz      = currAz ;
    prevCurrTopShtr = currTopShtr ;
    prevCurrBotShtr = currBotShtr ;
    
    if (encMode == BASIC) {

/*  In basic mode we also now compute a time to limit. Normally when tracking
 *  the target will always be roughly centered in the enclosure aperture.
 *  If the enclosure stops for any reason however then after some time 
 *  we will start vignetting. Under normal conditions therefore the 
 *  time to limit will be calculated and then count down a bit until the
 *  next move occurs at which point it will increase again. 
 */
        if (vfrac > 0.0) {
          /*  If we are already vignetting then we are in a limit so
           *  time to limit is 0
           */
          validTimes = TRUE;
          timeToNextMove = 0.0;
        } else {
          if (mframe == AZEL_TOPO || mframe == AZEL_MNT) {
            /* If mount is fixed there is no limit. If dome/shutters
             * are enabled they will get to same as mount positions
             * eventually
             */
             timeToNextMove = 86400.0;
             validTimes = FALSE;
          } else {
             /*  For tracking frames we generate the start HA and Dec */

/* Convert pre-flexure mount coords to topocentric az and el */
             x = ae2mt[0][0] * x0 + ae2mt[1][0] * y0 + ae2mt[2][0] * z0;
             y = ae2mt[0][1] * x0 + ae2mt[1][1] * y0 + ae2mt[2][1] * z0;
             z = ae2mt[0][2] * x0 + ae2mt[1][2] * y0 + ae2mt[2][2] * z0;

/* Generate start HA/Dec for this target */
            tcsLimAzel2Hadec (x, y, z, clat, slat, &startHA, &startDec) ;

/* Generate ending HA/Dec for this target. If the target never sets then
*  set the end HA to the starting HA. Targets that never rise 
*  should never reach this code.
*/
            csdec = cos(startDec);
            ssdec = sin(startDec);
            endHA = 0.0;
            if (tcsLimEl (csdec, ssdec, ellimit, clat, slat, &endHA)) 
              endHA = startHA ;
            
            tcsEcsEffectiveSlitPosns(currTopShtr, currBotShtr, &vTopShtr, 
                                      &vBotShtr);
            tcsEcsLimitTime(startHA, startDec, currAz, vTopShtr, vBotShtr,
                            dha, clat, slat, &encLimit, &timeToGo);
            if (encLimit > NOLIMIT) {
              timeToNextMove = timeToGo;
              validTimes = TRUE;
            } else {
              timeToNextMove = 86400.0;
              validTimes = FALSE;
            }

          }   

        }

        if (issueMoves) {

        /*
        ** In BASIC mode we are only interested in whether the mechanisms
        ** differ by the tolerance parameter from the demands. If they do
        ** and they are enabled then set the relevant outputs.
        **
        ** Note that the tolerance in azimuth is divided by cos(el) for
        ** elevations below about 78.5 and is fixed at posnTol/0.2 for
        ** elevations above 78.5.
        */
            daz = az - currAz ;
            if (daz > PI) daz = daz - PI2 ;
            if (daz < -PI) daz = daz + PI2 ;
            if (daz < 0.0) daz = -daz ;
        
            dTopShtr = elTopShtr - currTopShtr;
            if (dTopShtr < 0.0) dTopShtr = -dTopShtr;

            dBotShtr = elBotShtr - currBotShtr;
            if (dBotShtr < 0.0) dBotShtr = -dBotShtr;

            coselev = cos(el) ;
            if (coselev < 0.2) {
                domeTol = posnTol / 0.2 ;
            } else {
                domeTol = posnTol / coselev ;
            }

/* Take care not to send too many move commands too quickly. The problem is
*  that when slewing to a new target the dome is out of position for 
*  what could be many hundred calls to this routine. We don't want to send
*  a move command on every call. 
*/

            if (!enabledDome) {
              lastDomeRef = currAz ;
            } else {
              if (daz > domeTol) {

/* Check whether the dome is moving. If it is outside the tolerance and stays
*  that way for about 10s then send another move
*/
                if (!domeMoving) {
                  domeMoveCounter++ ;
                  if (domeMoveCounter == 20)
                    lastDomeRef = currAz ;
                } 
                dDomeDem = az - lastDomeRef ;
                if (dDomeDem < 0.0) dDomeDem = -dDomeDem ;
                if (dDomeDem > domeTol) {
                  issueMoveDomeNow = 1;
                  lastDomeRef = az ;
                  domeMoveCounter = 0 ;
                }
               }
             }

             if (!enabledShtrs) {
               lastTopShtrRef = currTopShtr ;
               lastBotShtrRef = currBotShtr ;
             } else {
               if ((dTopShtr > posnTol) || (dBotShtr > posnTol)) {
                 if (!topShtrMoving || !botShtrMoving) {
                   shtrMoveCounter++ ;
                   if (shtrMoveCounter == 20) {
                     lastTopShtrRef = currTopShtr ;
                     lastBotShtrRef = currBotShtr ;
                   }
                 }
                 dTopShtrDem = elTopShtr - lastTopShtrRef ;
                 if (dTopShtrDem < 0.0) dTopShtrDem = -dTopShtrDem ;
                 dBotShtrDem = elBotShtr - lastBotShtrRef ;
                 if (dBotShtrDem < 0.0) dBotShtrDem = -dBotShtrDem ;
                 if ((dTopShtrDem > posnTol) || (dBotShtrDem > posnTol)) {
                   issueMoveShtrsNow = 1 ;
                   lastTopShtrRef = elTopShtr ;
                   lastBotShtrRef = elBotShtr ;
                   shtrMoveCounter = 0 ;
                 }
               }
             }

        } else {

        /* (Currently only support BASIC via moves. Follow will go here
            if/when it is implemented) */

        }

    } else {            /* Minimum scatter or minimum vibration */

/* Check if a slew command has been issued as part of the configuration. 
*  N.B. If this is the first time that minimum scatter or minimum vibration
*  mode has been entered and slew commands have previously been issued in
*  basic mode then we will find that issuedSlew is TRUE.
*/

       issuedSlew = tcsEcsClearSlewFlag();

/* Update time to limit and time to next update if these numbers are 
*  relevant.
*/
       if (validTimes) {
         timeToNextMove = tLimit - tnow ;
         timeToNextUpdate = tUpdate - tnow ;
       }

/* Now check if a new limit calculation is needed. There are four criteria
*  used. The first three are straightforward i.e. an explicit slew command
*  has been given, a previously calculated limit has been reached or
*  the enclosure operating mode has been changed. The
*  fourth is more complex. It will trigger a recalculation when both dome
*  and shutters are enabled and the beam is vignetted. The purpose of this
*  is to cause a repositioning in cases where the time to limit is wrong.
*  The time to limit calculation may be wrong because of an error in the
*  algorithm or more likely because the user has been offsetting between
*  re-estimates of the times to limits. A consequence of this criterion 
*  would be that repeated re-estimates would be made during a slew to a
*  new position. This would have the positive benefit that most of the slewing
*  time would be taken out of the time to limit estimate but on the down side
*  more CPU resources would be used and multiple move commands sent to
*  the ECS. To handle this a check is kept on why a move was issued. If
*  it is due to the mirror being vignetted then further moves aren't issued.
*/ 
       if (issuedSlew || timeToNextMove < 0.0 || encModeChanged ||
           ((vfrac > 0.0) && enabledDome && enabledShtrs) ) {

         if (mframe == AZEL_TOPO || mframe == AZEL_MNT) {

/* In the case that the mount frame is fixed, don't calculate any time
*  limits
*/
           validTimes = FALSE ;
           timeToNextMove = 86400.0;
           timeToNextUpdate = 10.0;

          if (enabledDome) issueMoveDomeNow = 1;
          if (enabledShtrs) issueMoveShtrsNow = 1;

        } else {

          if (enabledDome && enabledShtrs) {

/* Convert pre-flexure mount coords to topocentric az and el */
             x = ae2mt[0][0] * x0 + ae2mt[1][0] * y0 + ae2mt[2][0] * z0;
             y = ae2mt[0][1] * x0 + ae2mt[1][1] * y0 + ae2mt[2][1] * z0;
             z = ae2mt[0][2] * x0 + ae2mt[1][2] * y0 + ae2mt[2][2] * z0;

/* Generate start HA/Dec for this target */
            tcsLimAzel2Hadec (x, y, z, clat, slat, &startHA, &startDec) ;

/* Generate ending HA/Dec for this target. If the target never sets then
*  set the end HA to the starting HA. Targets that never rise 
*  should never reach this code.
*/
            csdec = cos(startDec);
            ssdec = sin(startDec);
            endHA = 0.0;
            if (tcsLimEl (csdec, ssdec, ellimit, clat, slat, &endHA)) 
              endHA = startHA ;

/* Now compute optimum position for dome and shutters plus time to limit */
            tcsEcsCalcPosns (startHA, startDec, endHA, ellimit,
                             clat, slat, &domeAz, &elTopShtr, &elBotShtr,
                             &elTopVShtr, &elBotVShtr);
            az = domeAz ;
            tcsEcsLimitTime (startHA, startDec, az, elTopVShtr, elBotVShtr,
                             dha, clat, slat, &encLimit, &timeToGo);

/* Set up time limits */
             if (encLimit > NOLIMIT) {
               tLimit  = tnow + timeToGo;
               tUpdate = tnow + 10.0;
               timeToNextUpdate = 10.0;
               validTimes = TRUE ;
             } else {
               validTimes = FALSE ;
             }
             issueMoveDomeNow = 1;
             issueMoveShtrsNow = 1;

           } else {              /* Mount tracking but not dome or shutters */
             validTimes = FALSE;
             timeToNextMove = 86400.0;
             timeToNextUpdate = 10.0;
             if (enabledDome) issueMoveDomeNow = 1;
             if (enabledShtrs) issueMoveShtrsNow = 1;
           }

        }                  /* End clause for non-azel frames */

/* Now check that we don't send too many moves when the mirror is vignetted */

        if (!enabledDome) {
          lastDomeRef = currAz ;
        } else {
          if (issuedSlew || timeToNextMove < 0.0 || encModeChanged) {
            lastDomeRef = az ;
          } else {
            dDomeDem = az - lastDomeRef ;
            if (dDomeDem < 0.0) dDomeDem = -dDomeDem ;
            if (dDomeDem < vignTol*D2R) {
              issueMoveDomeNow = 0 ;
            } else {
              issueMoveDomeNow = 1 ;
              lastDomeRef = az ;
            } 
          }
        }

        if (!enabledShtrs) {
          lastTopShtrRef = currTopShtr ;
          lastBotShtrRef = currBotShtr ;
        } else {
          if (issuedSlew || timeToNextMove < 0.0 || encModeChanged) {
            lastTopShtrRef = elTopShtr ;
            lastBotShtrRef = elBotShtr ;
          } else {
            dTopShtrDem = elTopShtr - lastTopShtrRef ;
            if (dTopShtrDem < 0.0) dTopShtrDem = - dTopShtrDem ;
            dBotShtrDem = elBotShtr - lastBotShtrRef ;
            if (dBotShtrDem < 0.0 ) dBotShtrDem = -dBotShtrDem ;
            if ((dTopShtrDem < vignTol*D2R) || (dBotShtrDem < vignTol*D2R)) {
               issueMoveShtrsNow = 0 ;
            } else {
               issueMoveShtrsNow = 1 ;
               lastTopShtrRef = elTopShtr ;
               lastBotShtrRef = elBotShtr ;
            }
          }
        }

       }                   /* End if (issuedSlew ...  */

       if (timeToNextUpdate < 0.0) {

/* Generate current topcentric position of telescope */
         x = ae2mt[0][0] * x0 + ae2mt[1][0] * y0 + ae2mt[2][0] * z0;
         y = ae2mt[0][1] * x0 + ae2mt[1][1] * y0 + ae2mt[2][1] * z0;
         z = ae2mt[0][2] * x0 + ae2mt[1][2] * y0 + ae2mt[2][2] * z0;
         tcsLimAzel2Hadec (x, y, z, clat, slat, &startHA, &startDec) ;

/* What is the time to the next limit based on the current positions of the
*  dome and shutters 
*/
         tcsEcsLimitTime (startHA, startDec, domeAz, elTopVShtr, elBotVShtr,
                          dha, clat, slat, &encLimit, &timeToGo);
         tUpdate = tnow + 10.0;
       }

    }                /* End of clause for min scatter & min vibration */

/* Compute the alarm limit for the vignette fraction. */

    if ((!enabledDome && !enabledShtrs) || mframe == AZEL_TOPO ||
         mframe == AZEL_MNT) 
        vfracHigh = 1.01;
    else
        vfracHigh = 0.000001;

/* Although not strictly necessary, as it will be done by the ECS, wrap the
*  demand into the range 0 to 360.0 This makes the displays look better as
*  the ECS always returns its current position in this range.
*/
    if (az < 0.0) az += PI2 ; 
/*
** Set output demand array for ECS:
** Element 0  = time now
** Element 1  = target time
** Element 2  = track identifier
** Element 3  = demanded Azimuth
** Element 4  = demanded Elevation (top shutter)
** Element 5  = demanded Elevation (bottom shutter)
*/
    ECSdemand[0] = tnow;
    ECSdemand[1] = tick;
    ECSdemand[2] = trackid;
    ECSdemand[3] = az;
    ECSdemand[4] = elTopShtr;
    ECSdemand[5] = elBotShtr;

/* Copy array contents to genSub record output field A. */
    memcpy(pgsub->vala, ECSdemand, 6 * sizeof(double));

    *(long *) pgsub->valb = (long)issueMoveDomeNow ;
    *(double *) pgsub->valc = az * R2D ;

    *(long *) pgsub->vald = (long)issueMoveShtrsNow ;
    *(double *) pgsub->vale = elTopShtr * R2D ;
    *(double *) pgsub->valf = elBotShtr * R2D ;
    *(double *) pgsub->valg = vfracHigh ;
    *(double *) pgsub->valh = vfrac ;
    *(long *) pgsub->vali = (long)validTimes ;
    *(double *) pgsub->valj = timeToNextMove ;

    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDriveM2S
 *
 *   Purpose:
 *   Output demand positions to the Secondary Mirror Control System.
 *
 *   Description:
 *   This routine outputs demand tip/tilt positions to the Secondary
 *   Mirror Control System. It does this by fetching the latest
 *   values from the astrometric kernel and using these values
 *   as the demands to M2. The values are clipped to the current limit.
 *   Note that the tip/tilt demands sent to M2 are converted from 
 *   sky units to M2 units before being sent. It also fetches the X,Y,Z
 *   translation demands from the optics model and transmits these in
 *   the same data stream.
 *
 *   Output :
 *   vala => demand data array (see below)
 *   valb => Chop A x scan demand (arcsec on sky)
 *   valc => Chop A y scan demand (arcsec on sky)
 *   vald => Chop B x scan demand (arcsec on sky)
 *   vale => Chop B y scan demand (arcsec on sky)
 *   valf => Chop C x scan demand (arcsec on sky)
 *   valg => Chop C y scan demand (arcsec on sky)
 *   valh => Open loop x scan demand (arcsec of M2)
 *   vali => Open loop y scan demand (arcsec of M2)
 *
 *   Invocation:
 *   tcsDriveM2S (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub structure
 *
 *   Function value:
 *   Return status
 *
 *
 *   External functions:
 *   tcsOpticsGetM2XY     (tcsOptics)    fetch X,Y translation demands
 *   tcsOpticsGetM2ZTilt  (tcsOptics)    fetch Z and tip/tilt demands
 *   tcsOpticsScaleThrow  (tcsOptics)    convert sky to M2 units 
 *
 *-
 */
/* *INDENT-ON* */

long tcsDriveM2S(struct genSubRecord *pgsub)
{
    double M2Sdemand[14];       /* demand data to pass to M2 subsystem */
    double tick;                /* copy of TAI of demand */
    double tnow;                /* TAI when data sent to M2S */
    double m2_scan_x[3];        /* chop A,B,C tip/tilt x */
    double m2_scan_y[3];        /* chop A,B,C tip/tilt y */
    double trackid;             /* track identifier */
    double maxTilt;             /* max M2 tilt on sky (arcsec) */
    double maxZ;                /* max M2 Z coordinate (mm) */
    double m2Scale;             /* scales sky to M2 tip/tilt units */
    int ichop;                  /* chop state index */
    double xposn, yposn;        /* x,y translation demands */
    double zposn;               /* z (focus) demand */
    double xtilt,ytilt;         /* tilt open loop demands */
    int inPosition;             /* in position flag */
    int inPosReason;            /* in position reason */
    double focusScale = -52.359; /* Conversion factor for Z3 */
    double tiltScale ;          /* Conversion factor for Z1, Z2 */
    double fLen ;               /* Current focal length (mm) */
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsDriveM2S: Semaphore not created");
        return 0;
    }

/* Fetch the open loop tip/tilt demands as well as the x,y,z
   translation demands. */
    tcsOpticsGetM2XY (&xposn, &yposn);
    tcsOpticsGetM2ZTilt (&zposn, &xtilt, &ytilt);

/* Derive M2 scale from a unit tilt on the sky. */
    m2Scale = tcsOpticsScaleThrow (1.0) ;

/* Pick up from global memory. */
    epicsMutexLock(TcsSemId);
    tick = Tick;
    inPosition = InPosition;
    inPosReason = InPosReason;

/*
** Get the tilt values for all 3 chop states, converted to arcsecs.
** Note that ytilt is added to M2_scan_x etc. M2_scan_x is the end point
** of the chop whereas xtilt is the rotation about the x axis. The user
** induced tilt is stored for use by the optics model.
*/
    for (ichop = 0; ichop < 3; ichop++) {
        m2_scan_x[ichop] = (M2_scan_x[ichop] + ytilt/m2Scale) / AS2R;
        m2_scan_y[ichop] = (-M2_scan_y[ichop] + xtilt/m2Scale) / AS2R;
        tcsOpticsSetM2XYRot (ichop, M2_scan_x[ichop]*m2Scale,
                             -M2_scan_y[ichop]*m2Scale );
    }
    trackid = Trackid;
    epicsMutexUnlock(TcsSemId);

/* Get current tilt limit. */
    tcsOpticsGetTiltLimits(&maxTilt, &maxZ);

/* Clip demands. */
    for (ichop = 0; ichop < 3; ichop++) {
        if (m2_scan_x[ichop] > maxTilt) {
            m2_scan_x[ichop] = maxTilt;
            inPosition = 0;
            inPosReason = IPR_M2XMAX;
        } else if (m2_scan_x[ichop] < -1.0 * maxTilt) {
            m2_scan_x[ichop] = -1.0 * maxTilt;
            inPosition = 0;
            inPosReason = IPR_M2XMAX;
        }
        if (m2_scan_y[ichop] > maxTilt) {
            m2_scan_y[ichop] = maxTilt;
            inPosition = 0;
            inPosReason = IPR_M2YMAX;
        } else if (m2_scan_y[ichop] < -1.0 * maxTilt) {
            m2_scan_y[ichop] = -1.0 * maxTilt;
            inPosition = 0;
            inPosReason = IPR_M2YMAX;
        }
    }

/* Compute tiltScale factor */
   tcsOpticsGetFl (&fLen) ;
   tiltScale = m2Scale / (1000.0 * AS2R * fLen) ;

/*
** Demand data array consisting of the 14 type double data
** items as follows :
**
**   Time sent
**   Time to be applied
**   Track ID
**   Chop A X tilt (arcsec) i.e. scan_y
**   Chop A Y Tilt (arcsec) i.e. scan_x
**   Chop B X tilt (arcsec)
**   Chop B Y Tilt (arcsec)
**   Chop C X tilt (arcsec)
**   Chop C Y Tilt (arcsec)
**   X position (microns)
**   Y position (microns)
**   Z focus    (microns)
**   tiltScale (converts microns in focal plane to M2 tilt in arcsec)
**   focusScale (converts Z3 to microns of displacement of M2)
*/

    (void) timeNow(&tnow);
    M2Sdemand[0] = tnow;
    M2Sdemand[1] = tick;
    M2Sdemand[2] = trackid;
    M2Sdemand[3] = m2_scan_y[0] * m2Scale;
    M2Sdemand[4] = m2_scan_x[0] * m2Scale;
    M2Sdemand[5] = m2_scan_y[1] * m2Scale;
    M2Sdemand[6] = m2_scan_x[1] * m2Scale;
    M2Sdemand[7] = m2_scan_y[2] * m2Scale;
    M2Sdemand[8] = m2_scan_x[2] * m2Scale;
    M2Sdemand[9] = xposn * 1000.0;
    M2Sdemand[10] = yposn * 1000.0;
    M2Sdemand[11] = zposn * 1000.0;
    M2Sdemand[12] = tiltScale ;
    M2Sdemand[13] = focusScale ;

/* Copy array contents to genSub record output field A. */
    memcpy(pgsub->vala, M2Sdemand, 14 * sizeof(double));
 
/* Copy individual elements (in M2 units) to EPICS output fields. */

    *(double *)pgsub->valb = m2_scan_y[0]*m2Scale;
    *(double *)pgsub->valc = m2_scan_x[0]*m2Scale;
    *(double *)pgsub->vald = m2_scan_y[1]*m2Scale;
    *(double *)pgsub->vale = m2_scan_x[1]*m2Scale;
    *(double *)pgsub->valf = m2_scan_y[2]*m2Scale;
    *(double *)pgsub->valg = m2_scan_x[2]*m2Scale;
    *(double *)pgsub->valh = xtilt/AS2R;
    *(double *)pgsub->vali = ytilt/AS2R;

    epicsMutexLock(TcsSemId);
    InPosition = inPosition;
    InPosReason = inPosReason;
    epicsMutexUnlock(TcsSemId);

    return 0;
}

/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsDriveAGS
 *
 *   Purpose:
 *   Output demand guide probe positions to the A & G Control System.
 *
 *   Description:
 *   This routine outputs demand guide probe positions to the A & G 
 *   Control System. Prior to and including V1-1 of the TCS, 
 *   three sets of data were sent to each guide probe
 *   one set for each chop state. The A&G was also sent the chop state
 *   that the probe should be following. To meet the latest TCS/A&G ICD
 *   only a single set of data is sent. The demand values are clipped
 *   to whatever the current probe limits are to prevent illegal values
 *   being sent. If the useDefault is set then the kernel generated
 *   numbers are not used but rather the current default positions.
 *
 *   Invocation:
 *   tcsDriveAGS (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub structure
 *
 *   EPICS inputs :
 *
 *   a => guide probe number (0, 1 or 2)
 *   b => Nominal X position
 *   c => Nominal Y position
 *   d => Nominal Z position
 *   e => probe focus model (0, 1 or 2)
 *
 *   EPICS outputs :
 *
 *   vala => demand data array 
 *   valb => chop state for probe (0, 1 or 2)
 *   valc => expected tip/tilt/focus array
 *   vald => expected high order Zernike terms
 *   vale => x demand (mm)
 *   valf => y demand (mm)
 *   valg => z demand (mm)
 *   valh => 0 astigmatism prediction (mm)
 *   vali => 45 astigmatism prediction (mm)
 *
 *   Function value:
 *   (<) status (long)  Return status, 0 = OK
 *
 *-
 */
/* *INDENT-ON*/



long tcsDriveAGS(struct genSubRecord *pgsub)
{
    double AGSdemand[6];        /* demand data to pass to AG subsystem */
    double AGSttf[8];           /* expected tip/tilt/focus */
    double AGSzerns[24];        /* expected Zernike terms */
    double tnow;                /* TAI when data sent to AGS */
    double tick;                /* copy of TAI of demand */
    double g_x[3];              /* x guider position for each chop state */
    double g_y[3];              /* y guider position for each chop state */
    double trackid;             /* track identifier */
    int guide;                  /* guider number */
    LIMITTYPE limitType;        /* probe limit type */
    double xmin, xmax;          /* probe X limits */
    double ymin, ymax;          /* probe Y limits */
    double zmin, zmax;          /* probe Z limits */
    double rmin, rmax;          /* probe radial limits */
    int ichop;                  /* chop state (0, 1 or 2)  */
    double radval;              /* apparent radial position */
    double cliprad;             /* clipping multiplier for radial value */
    double xdemand[3];          /* X probe demand for each chop state */
    double ydemand[3];          /* Y probe demand for each chop state */
    double zdemand[3];          /* Z probe demand for each chop state */
//    double xNominal;            /* X zero point */
//    double yNominal;            /* Y zero point */
//    double zNominal;            /* Z zero point */
    int chopState;              /* the chop state the probe is following */
    int nod;                    /* current nod state */
    int act[3];                 /* active flags for current nod state */
    double pa;                  /* local copy of rotator angle (rads) */
    double ttf[3] ;             /* tip/tilt/focus as Zernikes */
    double zerns[16];           /* Zernikes 4 to 19 */
    int i ;                     /* loop counter */
    int inPosition;             /* in position flag */
    int inPosReason;            /* in position reason */
    double zoffset ;            /* probe focus offset (mm) */
    double xlastDemand ;        /* Last x demand */
    double ylastDemand ;        /* Last y demand */
    double zlastDemand ;        /* Last z demand */
    double ox, oy ;             /* OIWFS probe demands in OIWFS frame */
    int focusModel ;            /* Index to focus model */
    static int dbgLevel = DBG_NONE; /* debug level */

    guide = floor(*(double *) pgsub->a);
//    xNominal = *(double *)pgsub->b;
//    yNominal = *(double *)pgsub->c;
//    zNominal = *(double *)pgsub->d;
    focusModel = *(long *)pgsub->e;

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsDriveAGS: Semaphore not created");
        return 0;
    }

/* Pick up from global memory. */
    epicsMutexLock(TcsSemId);
    tick = Tick;
    trackid = Trackid;
    inPosition = InPosition;
    inPosReason = InPosReason;
    nod = Nod;
    pa = Pa ;
    switch (guide) {
    case 0:
        for (ichop = 0; ichop < 3; ichop++) {
            g_x[ichop] = G1_x[ichop];
            g_y[ichop] = G1_y[ichop];
            act[ichop] = G1_act[nod][ichop];
        }
        break;
    case 1:
        for (ichop = 0; ichop < 3; ichop++) {
            g_x[ichop] = G2_x[ichop];
            g_y[ichop] = G2_y[ichop];
            act[ichop] = G2_act[nod][ichop];
        }
        break;
    case 2:
        for (ichop = 0; ichop < 3; ichop++) {
            g_x[ichop] = G3_x[ichop];
            g_y[ichop] = G3_y[ichop];
            act[ichop] = G3_act[nod][ichop];
        }
        break;
    }
    epicsMutexUnlock(TcsSemId);

/* Set demands to current defaults. */
    tcsProbeGetDefaults(guide, &xlastDemand, &ylastDemand,
                            &zlastDemand);
    tcsProbeGetZoff (guide, &zoffset) ;
    for (ichop = 0; ichop < 3; ichop++) {
        xdemand[ichop] = xlastDemand;
        ydemand[ichop] = ylastDemand;
        zdemand[ichop] = zlastDemand + zoffset;
    }

/* If the probe is active in the current nod state, overide the demands
   for the active chop states with the values calculated by the kernel. */

/* By default follow chop state 0 and set Zernike terms to zero */
    chopState = 0;
    for (i = 0; i < 3; i++ ) {
      ttf[i] = 0.0 ;
    }

/* Check each nod state (in reverse order so that if more than one chop
   state is active the lowest is used). */
    for (ichop = 2; ichop >= 0; ichop--) {
        if ( act[ichop] ) {
            xdemand[ichop] = g_x[ichop];
            ydemand[ichop] = g_y[ichop];
            zdemand[ichop] = 0.0;

        /* Make the A&G follow this chop state. */
            chopState = ichop;

        /* Get probe limits. */
            tcsProbeGetLimits(guide, &limitType, &xmin, &xmax, &ymin, 
                              &ymax, &zmin, &zmax, &rmin, &rmax);

        /* Clip values for XY type limits. */
            if (limitType == XY) {

/* Although it wasn't supposed to be like this (!) the OIWFS return limits
*  in their frame of reference not the TCS's. To check them we must
*  therefore transform the demand into the oiwfs frame
*/
                if (guide == 2) {
                  tcsProbeTcs2Oiwfs(xdemand[ichop], ydemand[ichop], &ox, &oy) ;
                } else {
                  ox = xdemand[ichop] ;
                  oy = ydemand[ichop] ;
                }
                if (ox > xmax) {
                    ox = xmax;
                    inPosition = 0;
                    inPosReason = IPR_WFSXMAX + guide * 8;
                } else if (ox < xmin) {
                    ox = xmin;
                    inPosition = 0;
                    inPosReason = IPR_WFSXMIN + guide * 8;
                }
                if (oy > ymax) {
                    oy = ymax;
                    inPosition = 0;
                    inPosReason = IPR_WFSYMAX + guide * 8;
                } else if (oy < ymin) {
                    oy = ymin;
                    inPosition = 0;
                    inPosReason = IPR_WFSYMIN + guide * 8;
                }
                if (guide == 2) {
                  tcsProbeOiwfs2Tcs(ox, oy, &xdemand[ichop], &ydemand[ichop]);
                } else {
                  xdemand[ichop] = ox ;
                  ydemand[ichop] = oy ;
                }
            }

        /* Clip values for RADIAL type limits. */
            else if (limitType == RADIAL) {
                radval = sqrt(xdemand[ichop] * xdemand[ichop] + 
                              ydemand[ichop] * ydemand[ichop]);
                if (radval > 1e-10) {
                    cliprad = 1.0;
                    if (radval > rmax) {
                        cliprad = rmax / radval;
                        inPosition = 0;
                        inPosReason = IPR_WFSRMAX + guide * 8;
                    } else if (radval < rmin) {
                        cliprad = rmin / radval;
                        inPosition = 0;
                        inPosReason = IPR_WFSRMIN + guide * 8;
                    }
                    xdemand[ichop] = xdemand[ichop] * cliprad;
                    ydemand[ichop] = ydemand[ichop] * cliprad;
                } else

            /* Probe demand is close to (0,0) - set to arbitrary point on
               minimum radius. */
                {
                    xdemand[ichop] = 0.0;
                    ydemand[ichop] = rmin;
                    inPosition = 0;
                    inPosReason = IPR_WFSRMIN + guide * 8;
                }
            }

        /* Adjust for optics model (PWFS1 & 2 only). */
            if ( guide == 0 || guide == 1 ) 
                tcsOpticsProbeXYZ (focusModel, &xdemand[ichop], &ydemand[ichop],
                                 &zdemand[ichop]);

        /* Adjust for any z offset */
            zlastDemand = zdemand[ichop] ;
            zdemand[ichop] += zoffset ; 

        /* clip the z demands */
            if (zdemand[ichop] > zmax) {
                zdemand[ichop] = zmax;
                inPosition = 0;
                inPosReason = IPR_WFSZMAX + guide * 8;
            } else if (zdemand[ichop] < zmin) {
                zdemand[ichop] = zmin;
                inPosition = 0;
                inPosReason = IPR_WFSZMIN + guide * 8;
            }

        /* Store the latest demand as the new default. */
            tcsProbeSetDefaults(guide, xdemand[ichop], 
                    ydemand[ichop], zlastDemand);
        }
    }     /* end for loop */

/* Compute the Zernike terms for the current probe and chop state. */
    tcsOpticsGetTTF (guide, chopState, xdemand[chopState], ydemand[chopState],
                     pa, ttf) ;
    tcsOpticsGetZernikes(guide, chopState, xdemand[chopState], 
                     ydemand[chopState], pa, zerns) ;

/*
** Set output demand array for A&G:
** Element 0  = time now
** Element 1  = target time
** Element 2  = track identifier
** Element 3  = demanded X position 
** Element 4  = demanded Y position 
** Element 5  = demanded Z position 
*/

    (void) timeNow(&tnow);
    AGSdemand[0] = AGSttf[0] = AGSzerns[0] = tnow;
    AGSdemand[1] = AGSttf[1] = AGSzerns[1] = tick;
    AGSdemand[2] = AGSttf[2] = AGSzerns[2] = trackid;

    AGSdemand[3] = xdemand[chopState] ;
    AGSdemand[4] = ydemand[chopState] ;
    AGSdemand[5] = zdemand[chopState];

    AGSttf[3] = AGSzerns[3] = pa / D2R ;
    AGSttf[4] = 3.0 ;
    AGSttf[5] = AGSzerns[5] = ttf[0] ;
    AGSttf[6] = AGSzerns[6] = ttf[1] ;
    AGSttf[7] = AGSzerns[7] = ttf[2] ;

    AGSzerns[4] = 19 ;
    memcpy(&AGSzerns[8], zerns, 16 * sizeof(double)) ;

/* Copy array contents to genSub record output field A. */
    memcpy(pgsub->vala, AGSdemand, 6 * sizeof(double));
    memcpy(pgsub->valc, AGSttf, 8 * sizeof(double)) ;
    memcpy(pgsub->vald, AGSzerns, 24 * sizeof(double)) ;

    *(double *) pgsub->valb = (double) chopState;
    *(double *) pgsub->vale = AGSdemand[3] ;
    *(double *) pgsub->valf = AGSdemand[4] ;
    *(double *) pgsub->valg = AGSdemand[5] ;

/* Put 0 and 45 predictions on output links for display */
    *(double *) pgsub->valh = AGSzerns[8] ;
    *(double *) pgsub->vali = AGSzerns[9] ;
  
/* Only set the in position flag for P2 if the AO system is not in use */
    if ( guide != 1 || !tcsProbeGetAOConfig()) {
      epicsMutexLock(TcsSemId);
      InPosition = inPosition;
      InPosReason = inPosReason;
    epicsMutexUnlock(TcsSemId);
    }

    return 0;
}

/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsDriveGG
 *
 *   Purpose:
 *   Output demand guide probe positions from the generic guiders.
 *
 *   Description:
 *   A copy of this routine is run for each physical guider attached
 *   to one of the generic guiders. It takes the demands from the kernel 
 *   and routes them to the physical guider if that guider is currently
 *   being controlled. The output values are clipped by the probe
 *   limits. The physical guiders currently using this routine are
 *   the three AOM TT Guode Probes and the 4 GSAOI ODGWs.
 *   If the useDefault is set then the kernel generated
 *   numbers are not used but rather the current default positions.
 *
 *   Invocation:
 *   tcsDriveGG(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub structure
 *
 *   EPICS inputs :
 *
 *   a => guide probe number (1..7)
 *
 *   EPICS outputs :
 *
 *   vala => demand data array 
 *   vale => x demand (mm or pixels)
 *   valf => y demand (mm or pixels)
 *
 *   Function value:
 *   (<) status (long)  Return status, 0 = OK
 *
 *-
 */
/* *INDENT-ON*/



long tcsDriveGG(struct genSubRecord *pgsub)
{
    double GGdemand[5];         /* demand data to pass to physical guider */
    double tnow;                /* TAI when data sent to guider */
    double tick;                /* copy of TAI of demand */
    double g_x[3];              /* x guider position for each chop state */
    double g_y[3];              /* y guider position for each chop state */
    double trackid;             /* track identifier */
    int guide;                  /* guider number */
    LIMITTYPE limitType;        /* probe limit type */
    double xmin, xmax;          /* probe X limits */
    double ymin, ymax;          /* probe Y limits */
    double zmin, zmax;          /* probe Z limits */
    double rmin, rmax;          /* probe radial limits */
    int ichop;                  /* chop state (0, 1 or 2)  */
    double radval;              /* apparent radial position */
    double cliprad;             /* clipping multiplier for radial value */
    double xdemand[3];          /* X probe demand for each chop state */
    double ydemand[3];          /* Y probe demand for each chop state */
    int chopState;              /* the chop state the probe is following */
    int nod;                    /* current nod state */
    int act[3];                 /* active flags for current nod state */
//    double pa;                  /* local copy of rotator angle (rads) */
    int inPosition;             /* in position flag */
    int inPosReason;            /* in position reason */
    double xlastDemand ;        /* Last x demand */
    double ylastDemand ;        /* Last y demand */
    double zlastDemand ;        /* Dummy last z demand */
    int gsaoiport;              /* GSAOI port number */
    double ox, oy ;             /* OIWFS probe demands in OIWFS frame */
    int pguide ;                /* Number of pysical guider */
    int ggindex;                /* Index of generic guider */
    int i ;                     /* Loop counter */
    static int dbgLevel = DBG_NONE; /* debug level */

    guide = floor(*(double *) pgsub->a);

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsDriveGG: Semaphore not created");
        return 0;
    }

/* Search to see if this physical guider is connected to a virtual guider */
    pguide = 0;
    ggindex = 0;
    for (i=0; i<4; i++) {
      tcsConfigGetGuideIndex(i, &pguide);
      if (guide == pguide) {
        ggindex = i+1 ;
        break ;
      }
    }

/* Pick up from global memory. */
    epicsMutexLock(TcsSemId);
    tick = Tick;
    trackid = Trackid;
    inPosition = InPosition;
    inPosReason = InPosReason;
    nod = Nod;
//    pa = Pa ;
    switch (ggindex) {
    case 1:
        for (ichop = 0; ichop < 3; ichop++) {
            g_x[ichop] = GG1_x[ichop];
            g_y[ichop] = GG1_y[ichop];
            act[ichop] = GG1_act[nod][ichop];
        }
        break;
    case 2:
        for (ichop = 0; ichop < 3; ichop++) {
            g_x[ichop] = GG2_x[ichop];
            g_y[ichop] = GG2_y[ichop];
            act[ichop] = GG2_act[nod][ichop];
        }
        break;
    case 3:
        for (ichop = 0; ichop < 3; ichop++) {
            g_x[ichop] = GG3_x[ichop];
            g_y[ichop] = GG3_y[ichop];
            act[ichop] = GG3_act[nod][ichop];
        }
        break;
    case 4:
        for (ichop = 0; ichop < 3; ichop++) {
            g_x[ichop] = GG4_x[ichop];
            g_y[ichop] = GG4_y[ichop];
            act[ichop] = GG4_act[nod][ichop];
        }
        break;
    default:
        for (ichop = 0; ichop < 3; ichop++) {
            g_x[ichop] = 0.0;
            g_y[ichop] = 0.0;
            act[ichop] = 0;
        }
        break;
    }
    epicsMutexUnlock(TcsSemId);

/* Set demands to current defaults. */
    tcsProbeGetDefaults(guide+3, &xlastDemand, &ylastDemand,
                            &zlastDemand);
    for (ichop = 0; ichop < 3; ichop++) {
        xdemand[ichop] = xlastDemand;
        ydemand[ichop] = ylastDemand;
    }

/* If the probe is active in the current nod state, overide the demands
   for the active chop states with the values calculated by the kernel. */

/* By default follow chop state 0 and set Zernike terms to zero */
    chopState = 0;

/* Check each nod state (in reverse order so that if more than one chop
   state is active the lowest is used). */
    for (ichop = 2; ichop >= 0; ichop--) {
        if ( act[ichop] ) {
            xdemand[ichop] = g_x[ichop];
            ydemand[ichop] = g_y[ichop];

        /* Make the probe follow this chop state. */
            chopState = ichop;

        /* Get probe limits. */
            tcsProbeGetLimits(guide+3, &limitType, &xmin, &xmax, &ymin, 
                              &ymax, &zmin, &zmax, &rmin, &rmax);

        /* Clip values for limits. */
            if (guide < 8 && guide > 3) {
                
                gsaoiport = tcsGetGsaoiPort();
                tcsProbeTcs2Odgw(gsaoiport, guide-4, xdemand[ichop], ydemand[ichop], 
                                 &ox, &oy) ;
                if (ox > xmax) {
                    ox = xmax;
                    inPosition = 0;
                    inPosReason = IPR_ODGW1XMAX + (guide - 4) * 4;
                } else if (ox < xmin) {
                    ox = xmin;
                    inPosition = 0;
                    inPosReason = IPR_ODGW1XMIN + (guide - 4) * 4;
                }
                if (oy > ymax) {
                    oy = ymax;
                    inPosition = 0;
                    inPosReason = IPR_ODGW1YMAX + (guide  - 4) * 4;
                } else if (oy < ymin) {
                    oy = ymin;
                    inPosition = 0;
                    inPosReason = IPR_ODGW1YMIN + (guide - 4) * 4;
                }
                xdemand[ichop] = ox ;
                ydemand[ichop] = oy ;
                /* Set demand positions ready to be sent with next
                 * dataODGW command to GSAOI
                 */
                tcsGuideSetODGWCenter(guide - 4, ox, oy);
            }

            else if (guide > 0 && guide < 4 ) {
                radval = sqrt(xdemand[ichop] * xdemand[ichop] + 
                              ydemand[ichop] * ydemand[ichop]);
                if (radval > 1e-10) {
                    cliprad = 1.0;
                    if (radval > rmax) {
                        cliprad = rmax / radval;
                        inPosition = 0;
                        inPosReason = IPR_NGS1RMAX + (guide - 1) * 4;
                    } else if (radval < rmin) {
                        cliprad = rmin / radval;
                        inPosition = 0;
                        inPosReason = IPR_NGS1RMIN + (guide - 1) * 4;
                    }
                    xdemand[ichop] = xdemand[ichop] * cliprad;
                    ydemand[ichop] = ydemand[ichop] * cliprad;
                } else

            /* Probe demand is close to (0,0) - set to arbitrary point on
               minimum radius. */
                {
                    xdemand[ichop] = 0.0;
                    ydemand[ichop] = rmin;
                    inPosition = 0;
                    inPosReason = IPR_NGS1RMIN + (guide - 1) * 4;
                }

               tcsProbeTcs2Aom (guide-1, xdemand[ichop], ydemand[ichop], 
                                &ox, &oy) ;
/* For AOM probes 1 & 2 we must also check the X limits */
               if (guide == 1 || guide ==2 ) {
                 if (ox > xmax) {
                    ox = xmax;
                    inPosition = 0;
                    inPosReason = IPR_NGS1XMAX + (guide - 1) * 4;
                 } else if (ox < xmin) {
                    ox = xmin;
                    inPosition = 0;
                    inPosReason = IPR_NGS1XMIN + (guide - 1) * 4;
                 }
                 /*
                 tcsProbeAom2Tcs(guide-1, ox, oy, &xdemand[ichop], 
                                 &ydemand[ichop]);
                 */
                 xdemand[ichop] = ox ;
                 ydemand[ichop] = oy ;
               }
            }



        /* Store the latest demand as the new default. */
            tcsProbeSetDefaults(guide+3, xdemand[ichop], 
                    ydemand[ichop], 0.0);
        }
    }     /* end for loop */

/*
** Set output demand array for guider:
** Element 0  = time now
** Element 1  = target time
** Element 2  = track identifier
** Element 3  = demanded X position 
** Element 4  = demanded Y position 
*/

    (void) timeNow(&tnow);
    GGdemand[0] = tnow;
    GGdemand[1] = tick;
    GGdemand[2] = trackid;

    GGdemand[3] = xdemand[chopState] ;
    GGdemand[4] = ydemand[chopState] ;

/* Copy array contents to genSub record output field A. */
    memcpy(pgsub->vala, GGdemand, 5 * sizeof(double));

    *(double *) pgsub->valb = (double) chopState;
    *(double *) pgsub->vale = GGdemand[3] ;
    *(double *) pgsub->valf = GGdemand[4] ;

/* Only set the in position flag for P2 if the AO system is not in use */
    if ( guide != 1 || !tcsProbeGetAOConfig()) {
      epicsMutexLock(TcsSemId);
      InPosition = inPosition;
      InPosReason = inPosReason;
      epicsMutexUnlock(TcsSemId);
    }

    return 0;
}


/*+
 *   Function name:
 *   tcsDriveAOS  
 *
 *   Purpose:
 *   Output demand positions to the Altair Control System.
 *
 *   Description:
 *   The demands for the Altair probe are the same as the ones generated
 *   for PWFS2. Only one probe can be active at a time and whether the
 *   PWFS2 or the AO WFS is following the demands is determined elsewhere.
 *   This routine also pulls in and stores the current distortion 
 *   coefficients for use when calculating WFS and telescope demands.
 *
 *   Invocation:
 *   tcsDriveAOS (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub structure
 *
 *   EPICS inputs:
 *   a => array of 6 affine connection coefficients
 *   b => Altair focal plane offset (mm)
 *   c => Probe x offset (mm)
 *   d => Probe y offset (mm)
 *
 *   EPICS outputs :
 *   vala => demand data array 
 *   valb => x demand (mm)
 *   valc => y demand (mm)
 *   vald => z demand (mm)
 *
 *   Function value:
 *   (<) status (long)  Return status, 0 = OK
 *
 *-
 */
/* *INDENT-ON*/

#define AOWFS 3

long tcsDriveAOS(struct genSubRecord *pgsub)
{
    double AOSdemand[6];        /* demand data to pass to AO subsystem */
    double tnow;                /* TAI when data sent to AOS */
    double tick;                /* copy of TAI of demand */
    double g_x[3];              /* x guider position for each chop state */
    double g_y[3];              /* y guider position for each chop state */
    double trackid;             /* track identifier */
    LIMITTYPE limitType ;       /* probe limit type */
    double xmin, xmax;          /* probe X limits */
    double ymin, ymax;          /* probe Y limits */
    double zmin, zmax;          /* probe Z limits */
    double rmin, rmax;          /* probe radial limits */
    int ichop;                  /* chop state (0, 1 or 2)  */
    double xdemand[3];          /* X probe demand for each chop state */
    double ydemand[3];          /* Y probe demand for each chop state */
    double zdemand[3];          /* Z probe demand for each chop state */
    int chopState;              /* the chop state the probe is following */
    int nod ;                   /* current nod state */
    int act[3];                 /* active flags for current nod state */
    double pa ;                 /* local copy of rotator angle (rads) */
    double ttf[3] ;             /* tip/tilt/focus as Zernikes */
    double zerns[16];           /* Zernikes 4 to 19 */
    int i ;                     /* loop counter */
    int inPosition ;            /* in position flag */
    int inPosReason ;           /* in position reason */
    double xoffset ;            /* probe x offset (mm) */
    double yoffset ;            /* probe y offset (mm) */
    double zoffset ;            /* probe focus offset (mm) */
    double fshift ;             /* Focal plane shift due to instrument */
    double xlastDemand ;        /* Last x demand */
    double ylastDemand ;        /* Last y demand */
    double zlastDemand ;        /* Last z demand */
    double coeffs[6] ;          /* Array of distortion coefficients */
    double icoeffs[6] ;         /* Inverse coefficients */
    int istat ;                 /* Status from slaInvf */
//    double az, el;              /* az, el for diagnostics */
//    double ra, dec ;            /* RA, Dec for diagnostics */
//    double dra, ddec ;          /* track rates for diagnostics */
//    double rmadem ;             /* demand rma for diagnostics */
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsDriveAOS: Semaphore not created");
        return 0;
    }

/* Pick up from global memory. */
    epicsMutexLock(TcsSemId);
    tick = Tick;
    trackid = Trackid;
    inPosition = InPosition ;
    inPosReason = InPosReason ;
    nod = Nod;
    pa = Pa ;
//    az = Az ;
//    el = El;
//    rmadem = RmaDef;
//    ra = S_tar_p[0][0] * DR2D;
//    dec = S_tar_p[0][1] * DR2D;
//    dra = S_tar_dt[0][0] * DR2AS / 24.0 ;  /* Arcsecs/hr */
//    ddec = S_tar_dt[0][1] * DR2AS / 24.0 ;
    for (ichop = 0; ichop < 3; ichop++) {
        g_x[ichop] = G2_x[ichop];
        g_y[ichop] = G2_y[ichop];
        act[ichop] = G2_act[nod][ichop];
    }

/*  If Altair is connected then store an appropriate set of distortion 
*   coefficients for later use.
*/
    if (pgsub->sevr == NO_ALARM) {
      memcpy (coeffs, pgsub->a, 6*sizeof(double)) ;
      slaInvf ( coeffs, icoeffs, &istat) ;
      memcpy (T2altair, coeffs, 6*sizeof(double)) ;
      memcpy (Altair2t, icoeffs, 6*sizeof(double)) ;

    }
    epicsMutexUnlock(TcsSemId);

/* Set demands to current defaults. */
    xoffset = *(double *)pgsub->c;
    yoffset = *(double *)pgsub->d;
    zoffset = *(double *)pgsub->b;
    tcsProbeGetDefaults(AOWFS, &xlastDemand, &ylastDemand, &zlastDemand) ;
    tcsProbeSetZoff (AOWFS, zoffset) ;
    tcsOpticsGetFshift (&fshift) ;
    for (ichop = 0; ichop < 3; ichop++) {
        xdemand[ichop] = xlastDemand;
        ydemand[ichop] = ylastDemand;
        zdemand[ichop] = zlastDemand - zoffset + fshift ;
    }

/* If the probe is active in the current nod state, overide the demands
   for the active chop states with the values calculated by the kernel. */
 
/* By default follow chop state 0 and set Zernike terms to zero */
    chopState = 0;
    for (i = 0; i < 3; i++ ) {
      ttf[i] = 0.0 ;
    }   
 
/* Check each nod state (in reverse order so that if more than one chop
   state is active the lowest is used). */
    for (ichop = 2; ichop >= 0; ichop--) {
        if ( act[ichop] ) {
            xdemand[ichop] = g_x[ichop];
            ydemand[ichop] = g_y[ichop];
            zdemand[ichop] = 0.0;
 
        /* Make the A&G follow this chop state. */
            chopState = ichop;
 
        /* Get probe limits. */
            tcsProbeGetLimits(AOWFS, &limitType, &xmin, &xmax, &ymin, &ymax,
                              &zmin, &zmax, &rmin, &rmax) ;
 
        /* Clip values */
            if (xdemand[ichop] > xmax) {
                xdemand[ichop] = xmax;
                inPosition = 0;
                inPosReason = IPR_AOXMAX;
            } else if (xdemand[ichop] < xmin) {
                xdemand[ichop] = xmin;
                inPosition = 0;
                inPosReason = IPR_AOXMIN;
            }
            if (ydemand[ichop] > ymax) {
                ydemand[ichop] = ymax;
                inPosition = 0;
                inPosReason = IPR_AOYMAX;
            } else if (ydemand[ichop] < ymin) {
                ydemand[ichop] = ymin;
                inPosition = 0;
                inPosReason = IPR_AOYMIN;
            }
 
        /* Adjust for any z offset */
            zlastDemand = zdemand[ichop] ;
            zdemand[ichop] -= zoffset ;
            zdemand[ichop] += fshift ;
 
        /* clip the z demands */
            if (zdemand[ichop] > zmax) {
                zdemand[ichop] = zmax;
                inPosition = 0;
                inPosReason = IPR_AOZMAX;
            } else if (zdemand[ichop] < zmin) {
                zdemand[ichop] = zmin;
                inPosition = 0;
                inPosReason = IPR_AOZMIN;
            }
 
        /* Store the latest demand as the new default. */
            tcsProbeSetDefaults(AOWFS, xdemand[ichop],
                    ydemand[ichop], zlastDemand);
        }
    }     /* end for loop */

/* Compute the Zernike terms for the current probe and chop state. */
    tcsOpticsGetTTF (1, chopState, xdemand[chopState], ydemand[chopState],
                     pa, ttf) ;
    tcsOpticsGetZernikes(1, chopState, xdemand[chopState],
                     ydemand[chopState], pa, zerns) ;
 
/*
** Set output demand array for AOS:
** Element 0  = Time now
** Element 1  = Target time
** Element 2  = Track identifier
** Element 3  = Demanded X position
** Element 4  = Demanded Y position
** Element 5  = Demanded Z position
*/

    (void) timeNow(&tnow);
    AOSdemand[0] = tnow;
    AOSdemand[1] = tick;
    AOSdemand[2] = trackid;

/* Initial checks indicate TCS x -> Altair Y etc. so simply swap x and y
*  here. This may need to be handled differently later e.g. a proper
*  model of the probes probably by an affine transformation.
*  Also subtract off the known pointing origin / zero point
*/
    AOSdemand[4] = xdemand[chopState] - xoffset;
    AOSdemand[3] = ydemand[chopState] - yoffset;
    AOSdemand[5] = zdemand[chopState];

/* Copy array contents to genSub record output field A. */
    memcpy(pgsub->vala, AOSdemand, 6 * sizeof(double));
    *(double *)pgsub->valb = AOSdemand[3] ;
    *(double *)pgsub->valc = AOSdemand[4] ;
    *(double *)pgsub->vald = AOSdemand[5] ;

/* Set the global in position flag if the AO system is in use */
    if (tcsProbeGetAOConfig()) {
      epicsMutexLock(TcsSemId);
      InPosition = inPosition;
      InPosReason = inPosReason;
      epicsMutexUnlock(TcsSemId);
    }

/*
    if(pkdbgwriteflag) {
      fprintf(dbgfp, "%20.12f %16.10f %16.10f %16.10f %12.6f %12.6f %16.10f %16.10f %12.6f %12.6f\n", 
               timeRaw2tai(tick), az*DR2D, el*DR2D, rmadem*DR2D, 
               AOSdemand[3], AOSdemand[4], ra, dec, dra, ddec);
    }
*/
    return 0;
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsNullInit
 *
 *   Purpose:
 *   Null routine for TCS subroutine records that have no specific
 *   initialization.
 *
 *   Description:
 *   Does nothing
 *
 *   Invocation:
 *   tcsNullInit()
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *   none
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *
 *   External variables:
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


long tcsNullInit(struct subRecord *psub)
{
    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetFrame
 *
 *   Purpose:
 *   Returns the current tracking frame of the mount.
 *
 *   Description:
 *
 *   Invocation:
 *   tcsGetFrame( tel, &frame, &eqx, &wavel);
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    tel      (TELESCOPE) Virtual telescope
 *      (<)    frame    (FRAMETYPE) Tracking frame
 *      (<)    eqx      (double)    Tracking equinox
 *      (<)    wavel    (double)    Tracking wavelength
 *
 *   Function value:
 *   none
 *
 *   External functions:
 *
 *   External variables:
 *   (>)   M_frame    (FRAMETYPE)   Mount tracking frame
 *   (>)   M_eqx      (double)      Mount tracking equinox
 *   (>)   M_wavel    (double)      Mount tracking wavelength
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetFrame(TELESCOPE tel, FRAMETYPE * frame, double * eqx, double * wavel)
{
    switch (tel) {
       case MOUNT:
          *frame = M_frame;
          *eqx = M_eqx;
          *wavel = M_wavel;
          break;
       case SOURCE_A:
          *frame = S_frame[0];
          *eqx = S_eqx[0];
          *wavel = S_wavel[0];
          break;
       case SOURCE_B:
          *frame = S_frame[1];
          *eqx = S_eqx[1];
          *wavel = S_wavel[1];
          break;
       case SOURCE_C:
          *frame = S_frame[2];
          *eqx = S_eqx[2];
          *wavel = S_wavel[2];
          break;
       case PWFS1:
          *frame = G1_frame;
          *eqx = G1_eqx;
          *wavel = G1_wavel;
          break;
       case PWFS2:
          *frame = G2_frame;
          *eqx = G2_eqx;
          *wavel = G2_wavel;
          break;
       case OIWFS:
          *frame = G3_frame;
          *eqx = G3_eqx;
          *wavel = G3_wavel;
          break;
       case G1:
          *frame = GG1_frame;
          *eqx = GG1_eqx;
          *wavel = GG1_wavel;
          break;
       case G2:
          *frame = GG2_frame;
          *eqx = GG2_eqx;
          *wavel = GG2_wavel;
          break;
       case G3:
          *frame = GG3_frame;
          *eqx = GG3_eqx;
          *wavel = GG3_wavel;
          break;
       case G4:
          *frame = GG4_frame;
          *eqx = GG4_eqx;
          *wavel = GG4_wavel;
          break;
    }
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetIaa
 *
 *   Purpose:
 *   Returns the current instrument alignment angle
 *
 *   Description:
 *
 *   Invocation:
 *   tcsGetIaa( &iaa);
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<)    iaa     (double) Instrument alignment angle
 *
 *   Function value:
 *   none
 *
 *   External functions:
 *
 *   External variables:
 *   (>)   Iaa      (double)   Instrument alignment angle
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetIaa(double * iaa)
{
    *iaa = Iaa;
}

/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsGetAoprms
 *
 *   Purpose:
 *   Fetches the latest apparent to observed parameters from the kernel.
 *
 *   Description:
 *   Simply copies the apparent to observed parameters into the return array.
 *
 *   Invocation:
 *   tcsGetAoprms (aoprms)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<)    aoprms (double *) Array of apparent to observed parameters
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake        (semLib)           Take a semaphore
 *   semGive        (semLib)           Give a semaphore
 *
 *-
 */
/* *INDENT-ON*/

void tcsGetAoprms(double *aoprms)
{
    int i;                      /* loop counter */
    
 if( TcsSemId) {

    epicsMutexLock(TcsSemId);

    for (i = 0; i < 15; i++)
        *aoprms++ = Aoprms[i];

    epicsMutexUnlock(TcsSemId);
  }
}


/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsGetTrackid
 *
 *   Purpose:
 *   Fetches the latest TCS tracking ID from the kernel.
 *
 *   Description:
 *   Simply copies the current TCS trackID value.
 *
 *   Invocation:
 *   tcsGetTrackid (trackid)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<)    trackid (double *) TCS Trackid
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake        (semLib)           Take a semaphore
 *   semGive        (semLib)           Give a semaphore
 *
 *-
 */
/* *INDENT-ON*/


void tcsGetTrackid(double *trackid)
{

  if( TcsSemId)  {
    epicsMutexLock(TcsSemId);

        *trackid = Trackid;

    epicsMutexUnlock(TcsSemId);
  }
}

/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsSetTrackid
 *
 *   Purpose:
 *   Sets a new track id.
 *
 *   Description:
 *   Sets the track id from the clock.
 *
 *   Invocation:
 *   tcsSetTrackid ()
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake        (semLib)           Take a semaphore
 *   semGive        (semLib)           Give a semaphore
 *
 *-
 */
/* *INDENT-ON*/


void tcsSetTrackid(void)
{
    double trackid;

    timeNow(&trackid);

  if( TcsSemId)  {

    epicsMutexLock(TcsSemId);

    Trackid = trackid;

    epicsMutexUnlock(TcsSemId);
  }
}

/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsSetP1LGSMode
 *
 *   Purpose:
 *   Sets a new P1 + LGS mode 
 *
 *   Description:
 *   This simply sets an internal variable to show if P1 + LGS mode
 *   is enabled (= 1) or disabled (= 0). If the mode is enabled
 *   then certain calculations are bypassed.
 *
 *   Invocation:
 *   tcsSetP1LGSMode (mode)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    mode  (int)     Mode to set either 0 or 1 
 *
 *   Function value:
 *   None
 *
 *-
 */
/* *INDENT-ON*/


void tcsSetP1LGSMode(int mode)
{
   P1LGSMode = mode ;
}

/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsGetTelParams
 *
 *   Purpose:
 *   Fetch telescope parameters from the kernel.
 *
 *   Description:
 *   This function simply extracts the telescope parameters from the kernel
 *   and returns them in a TELP structure. The relevant pointing origin
 *   is selected by the telescope parameter.
 *
 *   Invocation:
 *   tcsGetTelParams (telescope, &telParams)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    telescope  (TELESCOPE)      Enumerated type
 *      (<)    pTelParams (struct TELP *)  Pointer to TELP structure
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake        (semLib)           Take a semaphore
 *   semGive        (semLib)           Give a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   There is no check on the status from the semLib calls
 *
 *-
 */
/* *INDENT-ON*/


void tcsGetTelParams(TELESCOPE telescope, struct TELP *pTelParams)
{

    double fl ;      /* Telescope focal length */
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsGetTelParams: Semaphore not created");
        return;
    }

    tcsOpticsGetFl(&fl);

    epicsMutexLock(TcsSemId);

/* First set up all the non virtual telescope-specific data. */

    pTelParams->fl = fl;
    pTelParams->rma = Rma;
    pTelParams->an = An;
    pTelParams->aw = Aw;
    pTelParams->pnpae = Pnpae;
    pTelParams->ca = Ca_net;
    pTelParams->ce = Ce_net;

/* The pointing origin returned depends on the telescope that has been
   selected. */

    switch (telescope) {
    case MOUNT:

        pTelParams->pox = M_por_p[0];
        pTelParams->poy = M_por_p[1];
        break;

    case SOURCE_A:

        pTelParams->pox = S_por_p[0][0];
        pTelParams->poy = S_por_p[0][1];
        break;

    case SOURCE_B:

        pTelParams->pox = S_por_p[1][0];
        pTelParams->poy = S_por_p[1][1];
        break;

    case SOURCE_C:

        pTelParams->pox = S_por_p[2][0];
        pTelParams->poy = S_por_p[2][1];
        break;

/* There are no pointing origins for the guide VTs so set the pointing
   origins to zero. */

    case PWFS1:
    case PWFS2:
    case OIWFS:
    case G1:
    case G2:
    case G3:
    case G4:

        pTelParams->pox = 0.0;
        pTelParams->poy = 0.0;
        break;

    default:

        pTelParams->pox = 0.0;
        pTelParams->poy = 0.0;
        break;

    }

    epicsMutexUnlock(TcsSemId);

}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetCoord
 *
 *   Purpose:
 *   Fetch current total tracking coordinates from global database.
 *
 *   Description:
 *
 *   Invocation:
 *   tcsGetCoord( &ra, &dec)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (code) <name>   <C type>   <parameter description>
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *      (<) ra   (double *)   RA or Azimuth
 *      (<) dec  (double *)   Dec or Elevation
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetCoord(double *ra, double *dec)
{
    *ra = M_tar_p[0];
    *dec = M_tar_p[1];
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetObs
 *
 *   Purpose:
 *   Fetch observatory parameters from global database.
 *
 *   Description:
 *
 *   Invocation:
 *   tcsGetObs( &tlong, &tlat, &hm)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<) tlong   (double *)   Observatory true longitude
 *      (<) tlat    (double *)   Observatory true latitude
 *      (<) hm      (double *)   Observatory height (metres)
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetObs(double *tlong, double *tlat, double *hm)
{
    *tlong = Tlong;
    *tlat = Tlat;
    *hm = Hm;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDump
 *
 *   Purpose:
 *   Prints selected global memory items to the console.
 *
 *   Description:
 *
 *   Invocation:
 *   tcsDump()
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *   none
 *
 *   Function value:
 *   none
 *
 *   External functions:
 *
 *   External variables:
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


void tcsDump()
{
    double fl;
    
    tcsOpticsGetFl(&fl);

    printf("del %-+25.15g\n", Del);
    printf("hm %-+25.15g\n", Hm);
    printf("sst %-+25.15g\n", Sst);
    printf("cst %-+25.15g\n", Cst);
    printf("tlong %-+25.15g ", Tlong);
    {
        char sign;
        long ihmsf[4];
        Dr2tf(9, Tlong, &sign, ihmsf);
        printf(" >>> %c %02ld %02ld %02ld.%09ld ",
               sign, ihmsf[0], ihmsf[1], ihmsf[2], ihmsf[3]);
        Dr2af(8, Tlong, &sign, ihmsf);
        printf(" >>> %c %02ld %02ld %02ld.%08ld ",
               sign, ihmsf[0], ihmsf[1], ihmsf[2], ihmsf[3]);
        printf(" >>> %-+25.15g\n", Tlong / D2R);
    }
    printf("tlat %-+25.15g ", Tlat);
    {
        char sign;
        long ihmsf[4];
        Dr2af(8, Tlat, &sign, ihmsf);
        printf(" >>> %c %02ld %02ld %02ld.%08ld ",
               sign, ihmsf[0], ihmsf[1], ihmsf[2], ihmsf[3]);
        printf(" >>> %-+25.15g\n", Tlat / D2R);
    }
    printf("daz %-+25.15g ", Daz);
    {
        printf(" >>> %-+25.15g\n", Daz / AS2R);
    }
    printf("slat %-+25.15g\n", Slat);
    printf("clat %-+25.15g\n", Clat);
    printf("ukm %-+25.15g\n", Ukm);
    printf("vkm %-+25.15g\n", Vkm);
    printf("diurab %-+25.15g ", Diurab);
    {
        printf(" >>> %-+25.15g\n", Diurab / AS2R);
    }
    printf("sst %-+25.15g\n", Sst);
    printf("cst %-+25.15g\n", Cst);
    printf("tick0 %-+25.15g\n", Tick0);
    printf("st0 %-+25.15g ", St0);
    {
        char sign;
        long ihmsf[4];
        Dr2tf(9, slaDranrm(St0), &sign, ihmsf);
        printf(" >>> %02ld %02ld %02ld.%09ld\n",
               ihmsf[0], ihmsf[1], ihmsf[2], ihmsf[3]);
    }
    printf("tt0 %-+25.15g ", Tt0);
    {
        char sign;
        long ihmsf[4];
        Dd2tf(9, dmod(Tt0, 1.0), &sign, ihmsf);
        printf(" >>> %c %02ld %02ld %02ld.%09ld\n",
               sign, ihmsf[0], ihmsf[1], ihmsf[2], ihmsf[3]);
    }
    printf("tdbj %-+25.15g\n", Tdbj);
    printf("amprms[ 0] %-+25.15g\n", Amprms[0]);
    printf("amprms[ 1] %-+25.15g\n", Amprms[1]);
    printf("amprms[ 2] %-+25.15g\n", Amprms[2]);
    printf("amprms[ 3] %-+25.15g\n", Amprms[3]);
    printf("amprms[ 4] %-+25.15g\n", Amprms[4]);
    printf("amprms[ 5] %-+25.15g\n", Amprms[5]);
    printf("amprms[ 6] %-+25.15g\n", Amprms[6]);
    printf("amprms[ 7] %-+25.15g\n", Amprms[7]);
    printf("amprms[ 8] %-+25.15g\n", Amprms[8]);
    printf("amprms[ 9] %-+25.15g\n", Amprms[9]);
    printf("amprms[10] %-+25.15g\n", Amprms[10]);
    printf("amprms[11] %-+25.15g\n", Amprms[11]);
    printf("amprms[12] %-+25.15g\n", Amprms[12]);
    printf("amprms[13] %-+25.15g\n", Amprms[13]);
    printf("amprms[14] %-+25.15g\n", Amprms[14]);
    printf("amprms[15] %-+25.15g\n", Amprms[15]);
    printf("amprms[16] %-+25.15g\n", Amprms[16]);
    printf("amprms[17] %-+25.15g\n", Amprms[17]);
    printf("amprms[18] %-+25.15g\n", Amprms[18]);
    printf("amprms[19] %-+25.15g\n", Amprms[19]);
    printf("amprms[20] %-+25.15g\n", Amprms[20]);
    printf("refa %-+25.15g ", Refa);
    {
        printf(" >>> %-+25.15g\n", Refa / AS2R);
    }
    printf("refb %-+25.15g ", Refb);
    {
        printf(" >>> %-+25.15g\n", Refb / AS2R);
    }
    printf("fl %-+25.15g\n", fl);
    printf("pnpae %-+25.15g\n", Pnpae/AS2R);
    printf("ca(net) %-+25.15g\n", Ca_net/AS2R);
    printf("ce(net) %-+25.15g\n", Ce_net/AS2R);
    printf("ia(net) %-+20.10g = %-+20.10g + %-+20.10g\n", Ia_net/AS2R,
           Ia/AS2R, Ia_delta/AS2R);
    printf("tick %-+25.15g\n", Tick);
    printf("az   %-+25.15g ", Az);
    {
        printf(" >>> %-+25.15g\n", Az / D2R);
    }
    printf("el   %-+25.15g ", El);
    {
        printf(" >>> %-+25.15g\n", El / D2R);
    }
    printf("paim %-+25.15g ", Paim);
    {
        printf(" >>> %-+25.15g\n", Paim / D2R);
    }
    printf("rm %-+25.15g\n", Rm);
    printf("ipa  %-+25.15g ", Ipa);
    {
        printf(" >>> %-+25.15g\n", Ipa / D2R);
    }
    printf("iaa  %-+25.15g ", Iaa);
    {
        printf(" >>> %-+25.15g\n", Iaa / D2R);
    }
    printf("ao2t[0] gsaoi2t[0] %-+25.15g %-+25.15g\n", Ao2t[0], Gsaoi2t[0]);
    printf("ao2t[1] gsaoi2t[1] %-+25.15g %-+25.15g\n", Ao2t[1], Gsaoi2t[1]);
    printf("ao2t[2] gsaoi2t[2] %-+25.15g %-+25.15g\n", Ao2t[2], Gsaoi2t[2]);
    printf("ao2t[3] gsaoi2t[3] %-+25.15g %-+25.15g\n", Ao2t[3], Gsaoi2t[3]);
    printf("ao2t[4] gsaoi2t[4] %-+25.15g %-+25.15g\n", Ao2t[4], Gsaoi2t[4]);
    printf("ao2t[5] gsaoi2t[5] %-+25.15g %-+25.15g\n", Ao2t[5], Gsaoi2t[5]);
    printf("t2ao[0] t2gsaoi[0] %-+25.15g %-+25.15g\n", T2ao[0], T2gsaoi[0]);
    printf("t2ao[1] t2gsaoi[1] %-+25.15g %-+25.15g\n", T2ao[1], T2gsaoi[1]);
    printf("t2ao[2] t2gsaoi[2] %-+25.15g %-+25.15g\n", T2ao[2], T2gsaoi[2]);
    printf("t2ao[3] t2gsaoi[3] %-+25.15g %-+25.15g\n", T2ao[3], T2gsaoi[3]);
    printf("t2ao[4] t2gsaoi[4] %-+25.15g %-+25.15g\n", T2ao[4], T2gsaoi[4]);
    printf("t2ao[5] t2gsaoi[5] %-+25.15g %-+25.15g\n", T2ao[5], T2gsaoi[5]);

    printf("o_por          %-+25.15g %-+25.15g\n", O_por[0], O_por[1]);
    printf("M_tar_p0       %-+25.15g %-+25.15g\n", M_tar_p0[0]*R2D, 
            M_tar_p0[1]*R2D);
    printf("m_por_p0       %-+25.15g %-+25.15g\n", M_por_p0[0], M_por_p0[1]);
    printf("m_por_ob       %-+25.15g %-+25.15g\n", M_por_ob[0], M_por_ob[1]);
    printf("m_por_p        %-+25.15g %-+25.15g\n", M_por_p[0],  M_por_p[1]);
    printf("M_wavel        %-+25.15g \n", M_wavel);

    printf("S_tar_p[0]     %-+25.15g %-+25.15g\n", S_tar_p[0][0]*R2D, 
            S_tar_p[0][1]*R2D);
    printf("S_tar_p0[0]    %-+25.15g %-+25.15g\n", S_tar_p0[0][0]*R2D, 
            S_tar_p0[0][1]*R2D);
    printf("S_tar_p0[1]    %-+25.15g %-+25.15g\n", S_tar_p0[1][0]*R2D, 
            S_tar_p0[1][1]*R2D);
    printf("S_tar_p0[2]    %-+25.15g %-+25.15g\n", S_tar_p0[2][0]*R2D, 
            S_tar_p0[2][1]*R2D);
    printf("S_wavel        %-+25.15g %-+25.15g %-+25.15g\n", S_wavel[0], 
            S_wavel[1], S_wavel[2]);
    printf("s_por_p0[0]    %-+25.15g %-+25.15g\n", S_por_p0[0][0], S_por_p0[0][1]);
    printf("s_por_ob[0][0] %-+25.15g %-+25.15g\n", S_por_ob[0][0][0], S_por_ob[0][0][1]);
    printf("s_por_ob[0][1] %-+25.15g %-+25.15g\n", S_por_ob[0][1][0], S_por_ob[0][1][1]);
    printf("s_por_ob[0][2] %-+25.15g %-+25.15g\n", S_por_ob[0][2][0], S_por_ob[0][2][1]);
    printf("s_por_p[0]     %-+25.15g %-+25.15g\n", S_por_p[0][0], S_por_p[0][1]);
    printf("s_por_pc[0]    %-+25.15g %-+25.15g\n", S_por_pc[0][0], S_por_pc[0][1]);
    printf("s_por_p0[1]    %-+25.15g %-+25.15g\n", S_por_p0[1][0], S_por_p0[1][1]);
    printf("s_por_ob[1][0] %-+25.15g %-+25.15g\n", S_por_ob[1][0][0], S_por_ob[1][0][1]);
    printf("s_por_ob[1][1] %-+25.15g %-+25.15g\n", S_por_ob[1][1][0], S_por_ob[1][1][1]);
    printf("s_por_ob[1][2] %-+25.15g %-+25.15g\n", S_por_ob[1][2][0], S_por_ob[1][2][1]);
    printf("s_por_p[1]     %-+25.15g %-+25.15g\n", S_por_p[1][0], S_por_p[1][1]);
    printf("s_por_pc[1]    %-+25.15g %-+25.15g\n", S_por_pc[1][0], S_por_pc[1][1]);
    
/* Az/El to Mount transformation matrix */
   printf("ae2mt[][0] %-+25.15g %-+25.15g %-+25.15g\n", Ae2mt[0][0], Ae2mt[1][0], Ae2mt[2][0]);
   printf("ae2mt[][1] %-+25.15g %-+25.15g %-+25.15g\n", Ae2mt[0][1], Ae2mt[1][1], Ae2mt[2][1]);
   printf("ae2mt[][2] %-+25.15g %-+25.15g %-+25.15g\n", Ae2mt[0][2], Ae2mt[1][2], Ae2mt[2][2]);
/*
    for ( i = 0; i < MAXTRM; i++ ) {
       printf("Model[%d] %d\n", i, Model[i]);
       printf("Coeffv[%d] %f\n", i, Coeffv[i]);
    }
    for ( i = 0; i < NTROOM; i++ ) {
       for ( j = 0; j < 9; j++ ) {
          printf("Coeffn[%d][%d] %d\n", i, j, Coeffn[i][j]);
          printf("Coform[%d][%d] %d\n", i, j, Coform[i][j]);
       }
    } */
}

void tcsGuiderDump(void)
{

  printf("PWFS1\n");
  printf("G1_tar_p0[0]     %-+25.15g %-+25.15g\n", G1_tar_p0[0]*R2D, 
          G1_tar_p0[1]*R2D);
  printf("G1_tar_p[0]     %-+25.15g %-+25.15g\n", G1_tar_p[0][0]*R2D, 
          G1_tar_p[0][1]*R2D);
  printf("G1_tar_p[1]     %-+25.15g %-+25.15g\n", G1_tar_p[1][0]*R2D, 
          G1_tar_p[1][1]*R2D);
  printf("G1_tar_p[2]     %-+25.15g %-+25.15g\n", G1_tar_p[2][0]*R2D, 
          G1_tar_p[2][1]*R2D);
  printf("G1_tar_ob[0]    %-+25.15g %-+25.15g\n", G1_tar_ob[0][0]/AS2R, 
          G1_tar_ob[0][1]/AS2R);
  printf("G1_tar_ob[1]    %-+25.15g %-+25.15g\n", G1_tar_ob[1][0]/AS2R, 
          G1_tar_ob[1][1]/AS2R);
  printf("G1_tar_ob[2]    %-+25.15g %-+25.15g\n", G1_tar_ob[2][0]/AS2R, 
          G1_tar_ob[2][1]/AS2R);
  printf("G1_x, G1_y       %-+25.15g %-+25.15g\n", G1_x[0], G1_y[0]);

  printf("\n");
  printf("PWFS2\n");
  printf("G2_tar_p0[0]     %-+25.15g %-+25.15g\n", G2_tar_p0[0]*R2D, 
          G2_tar_p0[1]*R2D);
  printf("G2_tar_p[0]     %-+25.15g %-+25.15g\n", G2_tar_p[0][0]*R2D, 
          G2_tar_p[0][1]*R2D);
  printf("G2_tar_p[1]     %-+25.15g %-+25.15g\n", G2_tar_p[1][0]*R2D, 
          G2_tar_p[1][1]*R2D);
  printf("G2_tar_p[2]     %-+25.15g %-+25.15g\n", G2_tar_p[2][0]*R2D, 
          G2_tar_p[2][1]*R2D);
  printf("G2_tar_ob[0]    %-+25.15g %-+25.15g\n", G2_tar_ob[0][0]/AS2R, 
          G2_tar_ob[0][1]/AS2R);
  printf("G2_tar_ob[1]    %-+25.15g %-+25.15g\n", G2_tar_ob[1][0]/AS2R, 
          G2_tar_ob[1][1]/AS2R);
  printf("G2_tar_ob[2]    %-+25.15g %-+25.15g\n", G2_tar_ob[2][0]/AS2R, 
          G2_tar_ob[2][1]/AS2R);
  printf("G2_x, G2_y       %-+25.15g %-+25.15g\n", G2_x[0], G2_y[0]);
  
  printf("\n");
  printf("OIWFS\n");
  printf("G3_tar_p0[0]     %-+25.15g %-+25.15g\n", G3_tar_p0[0]*R2D, 
          G3_tar_p0[1]*R2D);
  printf("G3_tar_p[0]     %-+25.15g %-+25.15g\n", G3_tar_p[0][0]*R2D, 
          G3_tar_p[0][1]*R2D);
  printf("G3_tar_p[1]     %-+25.15g %-+25.15g\n", G3_tar_p[1][0]*R2D, 
          G3_tar_p[1][1]*R2D);
  printf("G3_tar_p[2]     %-+25.15g %-+25.15g\n", G3_tar_p[2][0]*R2D, 
          G3_tar_p[2][1]*R2D);
  printf("G3_tar_ob[0]    %-+25.15g %-+25.15g\n", G3_tar_ob[0][0]/AS2R, 
          G3_tar_ob[0][1]/AS2R);
  printf("G3_tar_ob[1]    %-+25.15g %-+25.15g\n", G3_tar_ob[1][0]/AS2R, 
          G3_tar_ob[1][1]/AS2R);
  printf("G3_tar_ob[2]    %-+25.15g %-+25.15g\n", G3_tar_ob[2][0]/AS2R, 
          G3_tar_ob[2][1]/AS2R);
  printf("G3_x, G3_y       %-+25.15g %-+25.15g\n", G3_x[0], G3_y[0]);

  printf("\n");
  printf("G1\n");
  printf("GG1_tar_p0[0]     %-+25.15g %-+25.15g\n", GG1_tar_p0[0]*R2D, 
          GG1_tar_p0[1]*R2D);
  printf("GG1_tar_p[0]     %-+25.15g %-+25.15g\n", GG1_tar_p[0][0]*R2D, 
          GG1_tar_p[0][1]*R2D);
  printf("GG1_tar_p[1]     %-+25.15g %-+25.15g\n", GG1_tar_p[1][0]*R2D, 
          GG1_tar_p[1][1]*R2D);
  printf("GG1_tar_p[2]     %-+25.15g %-+25.15g\n", GG1_tar_p[2][0]*R2D, 
          GG1_tar_p[2][1]*R2D);
  printf("GG1_tar_ob[0]    %-+25.15g %-+25.15g\n", GG1_tar_ob[0][0]/AS2R, 
          GG1_tar_ob[0][1]/AS2R);
  printf("GG1_tar_ob[1]    %-+25.15g %-+25.15g\n", GG1_tar_ob[1][0]/AS2R, 
          GG1_tar_ob[1][1]/AS2R);
  printf("GG1_tar_ob[2]    %-+25.15g %-+25.15g\n", GG1_tar_ob[2][0]/AS2R, 
          GG1_tar_ob[2][1]/AS2R);
  printf("GG1_x, GG1_y     %-+25.15g %-+25.15g\n", GG1_x[0], GG1_y[0]);

  printf("\n");
  printf("G2\n");
  printf("GG2_tar_p0[0]     %-+25.15g %-+25.15g\n", GG2_tar_p0[0]*R2D, 
          GG2_tar_p0[1]*R2D);
  printf("GG2_tar_p[0]     %-+25.15g %-+25.15g\n", GG2_tar_p[0][0]*R2D, 
          GG2_tar_p[0][1]*R2D);
  printf("GG2_tar_p[1]     %-+25.15g %-+25.15g\n", GG2_tar_p[1][0]*R2D, 
          GG2_tar_p[1][1]*R2D);
  printf("GG2_tar_p[2]     %-+25.15g %-+25.15g\n", GG2_tar_p[2][0]*R2D, 
          GG2_tar_p[2][1]*R2D);
  printf("GG2_tar_ob[0]    %-+25.15g %-+25.15g\n", GG2_tar_ob[0][0]/AS2R, 
          GG2_tar_ob[0][1]/AS2R);
  printf("GG2_tar_ob[1]    %-+25.15g %-+25.15g\n", GG2_tar_ob[1][0]/AS2R, 
          GG2_tar_ob[1][1]/AS2R);
  printf("GG2_tar_ob[2]    %-+25.15g %-+25.15g\n", GG2_tar_ob[2][0]/AS2R, 
          GG2_tar_ob[2][1]/AS2R);
  printf("GG2_x, GG2_y     %-+25.15g %-+25.15g\n", GG2_x[0], GG2_y[0]);

  printf("\n");
  printf("G3\n");
  printf("GG3_tar_p0[0]     %-+25.15g %-+25.15g\n", GG3_tar_p0[0]*R2D, 
          GG3_tar_p0[1]*R2D);
  printf("GG3_tar_p[0]     %-+25.15g %-+25.15g\n", GG3_tar_p[0][0]*R2D, 
          GG3_tar_p[0][1]*R2D);
  printf("GG3_tar_p[1]     %-+25.15g %-+25.15g\n", GG3_tar_p[1][0]*R2D, 
          GG3_tar_p[1][1]*R2D);
  printf("GG3_tar_p[2]     %-+25.15g %-+25.15g\n", GG3_tar_p[2][0]*R2D, 
          GG3_tar_p[2][1]*R2D);
  printf("GG3_tar_ob[0]    %-+25.15g %-+25.15g\n", GG3_tar_ob[0][0]/AS2R, 
          GG3_tar_ob[0][1]/AS2R);
  printf("GG3_tar_ob[1]    %-+25.15g %-+25.15g\n", GG3_tar_ob[1][0]/AS2R, 
          GG3_tar_ob[1][1]/AS2R);
  printf("GG3_tar_ob[2]    %-+25.15g %-+25.15g\n", GG3_tar_ob[2][0]/AS2R, 
          GG3_tar_ob[2][1]/AS2R);
  printf("GG3_x, GG3_y     %-+25.15g %-+25.15g\n", GG3_x[0], GG3_y[0]);

  printf("\n");
  printf("G4\n");
  printf("GG4_tar_p0[0]     %-+25.15g %-+25.15g\n", GG4_tar_p0[0]*R2D, 
          GG4_tar_p0[1]*R2D);
  printf("GG4_tar_p[0]     %-+25.15g %-+25.15g\n", GG4_tar_p[0][0]*R2D, 
          GG4_tar_p[0][1]*R2D);
  printf("GG4_tar_p[1]     %-+25.15g %-+25.15g\n", GG4_tar_p[1][0]*R2D, 
          GG4_tar_p[1][1]*R2D);
  printf("GG4_tar_p[2]     %-+25.15g %-+25.15g\n", GG4_tar_p[2][0]*R2D, 
          GG4_tar_p[2][1]*R2D);
  printf("GG4_tar_ob[0]    %-+25.15g %-+25.15g\n", GG4_tar_ob[0][0]/AS2R, 
          GG4_tar_ob[0][1]/AS2R);
  printf("GG4_tar_ob[1]    %-+25.15g %-+25.15g\n", GG4_tar_ob[1][0]/AS2R, 
          GG4_tar_ob[1][1]/AS2R);
  printf("GG4_tar_ob[2]    %-+25.15g %-+25.15g\n", GG4_tar_ob[2][0]/AS2R, 
          GG4_tar_ob[2][1]/AS2R);
  printf("GG4_x, GG4_y     %-+25.15g %-+25.15g\n", GG4_x[0], GG4_y[0]);

  printf("\n");
}


/*+
 *   Function name:
 *   tcsDumpWcs 
 *
 *   Purpose:
 *   Dump current WCS information for diagnostic purposes
 *
 *   Description:
 *   The current WCS context is fetched and then converted into WCS
 *   coordinate transform. The data are then printed out to check that
 *   values generated are consistent with what an instrument should
 *   be generating.
 *
 *   Invocation:
 *   tcsDumpWcs()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

void tcsDumpWcs (void) 
{

  struct WCS_CTX wcsctx ;       /* Current WCS structure */
  struct WCS wcs ;              /* WCS transformation */
  struct EPOCH tequinox ;       /* Tracking equinox */
  FRAMETYPE tframe ;            /* Track frame */
  int    stat ;                 /* Status from astCtx2tr */
  double timestamp ;            /* Raw time for which WCS is correct */
  double tt ;
  char   ctype1[81] ;           /* FITS header string */
  char   crpix1[81] ;           /* FITS header string */
  char   crval1[81] ;           /* FITS header string */
  char   ctype2[81] ;           /* FITS header string */
  char   crpix2[81] ;           /* FITS header string */
  char   crval2[81] ;           /* FITS header string */
  char   pc001001[81] ;         /* FITS header string */
  char   pc001002[81] ;         /* FITS header string */
  char   pc002001[81] ;         /* FITS header string */
  char   pc002002[81] ;         /* FITS header string */
  char   radecsys[81];          /* FITS header string */
  char   equinox[81] ;          /* FITS header string */
  char   mjdobs[81] ;           /* FITS header string */
  double crpix1val, crpix2val ; /* Values of crpix1 and crpix2 */
  double crval1val, crval2val ; /* Values of crval1 and crval2 */
  double cd1_1, cd1_2, cd2_1, cd2_2 ; /* Values of transformation coeffs */
  double equinoxval;
  double mjdobsval ;
  double posn1, posn2 ;  /* Positions at pixel 0.5, 0.5 */
  double xi, eta ;       /* Standard coords */


/* Fetch WCS context */
  astGetctx(&wcsctx) ;

/* Generate WCS transformation. Note that we use the data straight out
*  of global memory without bothering with semaphores. There is therefore
*  a possibility that the data might not be fully consistent when this 
*  routine runs.
*/ 
  tframe = FK5 ;
  tequinox.type = 'J' ;
  tequinox.year = 2000.0 ;
  if ((stat = astCtx2tr(wcsctx, tframe, tequinox, Wavelr, 0, &wcs,
                        &timestamp))) {
      printf ("Failed to generate WCS transform, status = %d\n", stat) ;
      return ;
  }

/* Form TT from timestamp */
  if ((stat = timeThenD (timestamp, TT, &tt))) {
    printf ("Failed to generate TT, status = %d\n", stat) ;
    return ;
  }

/* Generate the FITS headers */
  if ((stat = astFITSs (wcs, tframe, tequinox, tt, ctype1, crpix1,
                        crval1, ctype2, crpix2, crval2,
                        pc001001, pc001002, pc002001,
                        pc002002, radecsys, equinox, mjdobs))) {
       printf ("Failed to generate FITS headers, status = %d\n", stat) ;
       return ;
   }

/* Output the results */
   printf ("%s\n", ctype1) ;
   printf ("%s\n", crpix1) ;
   printf ("%s\n", crval1) ;
   printf ("%s\n", ctype2) ;
   printf ("%s\n", crpix2) ;
   printf ("%s\n", crval2) ;
   printf ("%s\n", pc001001) ;
   printf ("%s\n", pc001002) ;
   printf ("%s\n", pc002001) ;
   printf ("%s\n", pc002002) ;
   printf ("%s\n", radecsys) ;
   printf ("%s\n", equinox) ;
   printf ("%s\n", mjdobs) ;

/* Generate the FITS values and then compute the value of pixel 0.5, 0.5 */
  if ((stat = astFITSv (wcs, tframe, tequinox, tt, ctype1, &crpix1val,
                        &crval1val, ctype2, &crpix2val, &crval2val,
                        &cd1_1, &cd1_2, &cd2_1,
                        &cd2_2, radecsys, &equinoxval, &mjdobsval))) {
       printf ("Failed to generate FITS values, status = %d\n", stat) ;
       return ;
   }
   
   xi = (cd1_1 * (0.5 - crpix1val) + cd1_2 * (0.5 - crpix2val)) * D2R ;
   eta = (cd2_1 * (0.5 - crpix1val) + cd2_2 * (0.5 - crpix2val)) * D2R ;
   slaDtp2s (xi, eta, crval1val*D2R, crval2val*D2R, &posn1, &posn2);

   printf ("Positions at pixel 0.5, 0.5\n");
   printf ("RA = %.11f  Dec = %.11f\n", posn1/D2R, posn2/D2R);

}

/* These routines are only used for formatting debug output. */

static void Dd2tf(int ndp, double days, char *sign, long ihmsf[4])
#define D2S 86400.0             /* Days to seconds */
{
    double rs, rm, rh, a, ah, am, as, af;

/* Handle sign */
    *sign = (char) '-';
    *sign = (char) '+';
    *sign = (days < 0.0) ? (char) '-' : (char) '+';

/* Field units in terms of least significant figure. */
    rs = pow(10.0, (double) gmax(ndp, 0));
    rs = dint(rs);
    rm = rs * 60.0;
    rh = rm * 60.0;

/* Round interval and express in smallest units required. */
    a = rs * D2S * fabs(days);
    a = dnint(a);

/* Separate into fields. */
    ah = a / rh;
    ah = dint(ah);
    a = a - ah * rh;
    am = a / rm;
    am = dint(am);
    a = a - am * rm;
    as = a / rs;
    as = dint(as);
    af = a - as * rs;

/* Return results. */
    ihmsf[0] = (long) ah;
    ihmsf[1] = (long) am;
    ihmsf[2] = (long) as;
    ihmsf[3] = (long) af;
}
static void Dr2af(int ndp, double angle, char *sign, long idmsf[4])
{
/* Scale then use days to h,m,s routine. */
    Dd2tf(ndp, angle * D15B2P, sign, idmsf);
}
static void Dr2tf(int ndp, double angle, char *sign, long ihmsf[4])
{
/* Scale then use days to h,m,s routine. */
    Dd2tf(ndp, angle / D2PI, sign, ihmsf);
}
/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsGetPFilt
 *
 *   Purpose:
 *   Fetch the pointing filter parameters from the TCS kernel.
 *
 *   Description:
 *   This routine simply accesses the mount filter parameters from the
 *   TCS kernel and returns them in the relevant part of the Telescope
 *   Control Block (TCB).
 *
 *   Invocation:
 *   tcsGetPFilt (&pointFilter)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<)    pFilter  (struct POINTFILTER *) Pointer to structure
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semGive        (semLib)           Give a semaphore
 *   semTake        (semLib)           Take a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   There is no check on the return status of the semLib calls
 *
 *-
 */
/* *INDENT-ON*/



void tcsGetPFilt(struct POINTFILTER *pFilter)
{
 if( TcsSemId) {

    epicsMutexLock(TcsSemId);

    pFilter->weightA.val = F2_w[0];
    pFilter->weightB.val = F2_w[1];
    pFilter->weightC.val = F2_w[2];
    pFilter->weightNod.val = F2_w[3];
    pFilter->sc.val = abs ( F2_sc );
    pFilter->bw.val = F2_bw;
    pFilter->maxv.val = F2_maxv;
    pFilter->grab.val = F2_grab;

    epicsMutexUnlock(TcsSemId);
 } 
    return;
}

/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsGetTFilt
 *
 *   Purpose:
 *   Fetch the target filter parameters from the TCS kernel.
 *
 *   Description:
 *   This routine simply accesses the target filter parameters from the
 *   TCS kernel and returns them in the relevant part of the Telescope
 *   Control Block (TCB).
 *
 *   Invocation:
 *   tcsGetTFilt (&targetFilter)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<)    tFilter  (struct TARGETFILTER *) Pointer to structure
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semGive        (semLib)           Give a semaphore
 *   semTake        (semLib)           Take a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   There is no check on the return status of the semLib calls
 *
 *-
 */
/* *INDENT-ON*/



void tcsGetTFilt(struct TARGETFILTER *tFilter)
{
 if( TcsSemId) {
    epicsMutexLock(TcsSemId);

    tFilter->sc.val = abs ( F1_sc );
    tFilter->bw.val = F1_bw;
    tFilter->maxv.val = F1_maxv;
    tFilter->grab.val = F1_grab;

    epicsMutexUnlock(TcsSemId);
 }
    return;

}
/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsGetChop
 *
 *   Purpose:
 *   Fetch the specified chop parameters from the TCS kernel.
 *
 *   Description:
 *   This routine accesses the chop parameters from the TCS kernel,
 *   converts them to their input form and returns them in the relevant 
 *   part of the Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsGetChop (chopNo, &chop)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    chopNo   (int)    Number of chop to return
 *      (<)    pChop  (struct CHOP *) Pointer to structure
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semGive        (semLib)           Give a semaphore
 *   semTake        (semLib)           Take a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   There is no check on the return status of the semLib calls
 *
 *-
 */
/* *INDENT-ON*/



void tcsGetChop(int chopNo, struct CHOP *pChop)
{
 if( TcsSemId) {
    epicsMutexLock(TcsSemId);

    if (chopNo == 1) {
        pChop->mode.val = C_mode[0];
        pChop->frame.val = C_frame[0];
        pChop->eqx.val.year = C_eqx[0];
        if ( C_frame[0] == FK5 )
            pChop->eqx.val.type = 'J';
        else if ( C_frame[0] == FK4 )
            pChop->eqx.val.type = 'B';
        else
            pChop->eqx.val.type = ' ';
        pChop->throw.val = sqrt( C_xieta[0][0] * C_xieta[0][0] +
                                 C_xieta[0][1] * C_xieta[0][1]);
        if (C_xieta[0][0] == 0.0 && C_xieta[0][1] == 0.0)
           pChop->pa.val = 0.0;
        else 
           pChop->pa.val = atan2( C_xieta[0][0], C_xieta[0][1] );
    } else if (chopNo == 2) {
        pChop->mode.val = C_mode[1];
        pChop->frame.val = C_frame[1];
        pChop->eqx.val.year = C_eqx[1];
        if ( C_frame[1] == FK5 )
            pChop->eqx.val.type = 'J';
        else if ( C_frame[1] == FK4 )
            pChop->eqx.val.type = 'B';
        else
            pChop->eqx.val.type = ' ';
        pChop->throw.val = sqrt( C_xieta[1][0] * C_xieta[1][0] +
                                 C_xieta[1][1] * C_xieta[1][1]);
        if (C_xieta[1][0] == 0.0 && C_xieta[1][1] == 0.0)
           pChop->pa.val = 0.0;
        else 
           pChop->pa.val = atan2( C_xieta[1][0], C_xieta[1][1] );
    }
    epicsMutexUnlock(TcsSemId);
  }
    return;
}

/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsGetChopMode
 *
 *   Purpose:
 *   Fetch the chop mode from the TCS kernel.
 *
 *   Description:
 *   This routine accesses the chop mode from the TCS kernel,
 *   and returns it in the relevant part of the Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsGetChopMode (&pChopMode)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<)    pSysConfig  (struct SYSCONFIG *) Pointer to structure
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semGive        (semLib)           Give a semaphore
 *   semTake        (semLib)           Take a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   There is no check on the return status of the semLib calls
 *
 *-
 */
/* *INDENT-ON*/



void tcsGetChopMode(struct SYSCONFIG *pSysConfig)
{
 if( TcsSemId) {
    epicsMutexLock(TcsSemId);
    pSysConfig->chopmode.val = ChopMode;
    epicsMutexUnlock(TcsSemId);
  }
    return;

}
/* *INDENT-OFF*/
/*+
 *   Function name:
 *   tcsGetGuide
 *
 *   Purpose:
 *   Fetch the specified guide parameters from the TCS kernel.
 *
 *   Description:
 *   This routine accesses the guide parameters from the TCS kernel and
 *   returns them in the relevant part of the Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsGetGuide (guideNo, &guide)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    guideNo   (int)    Number of WFS to return
 *      (<)    guide  (struct GUIDE *) Pointer to structure
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semGive        (semLib)           Give a semaphore
 *   semTake        (semLib)           Take a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   There is no check on the return status of the semLib calls
 *
 *-
 */
/* *INDENT-ON*/



void tcsGetGuide(int guideNo, struct GUIDE *pGuide)
{
    int inod, ichop;

 if( TcsSemId) {

    epicsMutexLock(TcsSemId);

    switch (guideNo) {
    case 0:
        for ( inod = 0; inod < 3; inod ++) {
           for ( ichop = 0; ichop < 3; ichop ++) {
              pGuide->act[inod][ichop].val = G1_act[inod][ichop];
           }
        }
        break;
    case 1:
        for ( inod = 0; inod < 3; inod ++) {
           for ( ichop = 0; ichop < 3; ichop ++) {
              pGuide->act[inod][ichop].val = G2_act[inod][ichop];
           }
        }
        break;
    case 2:
        for ( inod = 0; inod < 3; inod ++) {
           for ( ichop = 0; ichop < 3; ichop ++) {
              pGuide->act[inod][ichop].val = G3_act[inod][ichop];
           }
        }
        break;
    case 3:
        for ( inod = 0; inod < 3; inod ++) {
           for ( ichop = 0; ichop < 3; ichop ++) {
              pGuide->act[inod][ichop].val = GG1_act[inod][ichop];
           }
        }
        break;
    case 4:
        for ( inod = 0; inod < 3; inod ++) {
           for ( ichop = 0; ichop < 3; ichop ++) {
              pGuide->act[inod][ichop].val = GG2_act[inod][ichop];
           }
        }
        break;
    case 5:
        for ( inod = 0; inod < 3; inod ++) {
           for ( ichop = 0; ichop < 3; ichop ++) {
              pGuide->act[inod][ichop].val = GG3_act[inod][ichop];
           }
        }
        break;
    case 6:
        for ( inod = 0; inod < 3; inod ++) {
           for ( ichop = 0; ichop < 3; ichop ++) {
              pGuide->act[inod][ichop].val = GG4_act[inod][ichop];
           }
        }
        break;
    }
    epicsMutexUnlock(TcsSemId);
 }
    return;

}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetTarget
 *
 *   Purpose:
 *   Extracts the information for a specifed telescope from global memory
 *   and fills out a structure within a Telescope Control Block.
 *
 *   Description:
 *   Locks the global memory database then simply copies the data
 *   for the specified telescope into the appropriate fields of a TCB.
 *
 *   Invocation:
 *   tcsGetTarget(tel, pTCB)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    tel       (TELESCOPE) Enumerated type specifying telescope
 *      (<)    pTCB      (struct TCB *) Pointer to TCB structure
 *
 *   Function value:
 *     None
 *
 *   External functions:
 *   semTake        (semLib)           Takes a semaphore
 *   semGive        (semLib)           Gives a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *-
 */
/* *INDENT-ON*/


void tcsGetTarget(TELESCOPE tel, struct TCB *pTCB) 
{
    char type;
    static int dbgLevel = DBG_NONE; /* debug level */

    strcpy(pTCB->target[tel].name.val, " "); /* currently no name in
                                                global memory */
    pTCB->target[tel].parallax.val = 0.0;    /* currently nothing in memory */
    pTCB->target[tel].pm = 1;                /* zero pm in reference frame */
    pTCB->target[tel].pmRA.val = 0.0;
    pTCB->target[tel].pmDec.val = 0.0;
    pTCB->target[tel].rv.val = 0.0;

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsGetTarget: Semaphore not created");
        return;
    }

    epicsMutexLock(TcsSemId);

    switch (tel) {
    case MOUNT:
        type = M_frame == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = M_tar_p0[0];
        pTCB->target[tel].theta2.val = M_tar_p0[1];
        pTCB->target[tel].frame.val = M_frame;
        pTCB->target[tel].eqx.val.year = M_eqx;
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = M_wavel;
        pTCB->difftrack[tel].t0.val = M_tar_t0;
        pTCB->difftrack[tel].dtheta1.val = M_tar_dt[0];
        pTCB->difftrack[tel].dtheta2.val = M_tar_dt[1];
        break;

    case SOURCE_A:
        type = S_frame[0] == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = S_tar_p0[0][0];
        pTCB->target[tel].theta2.val = S_tar_p0[0][1];
        pTCB->target[tel].frame.val = S_frame[0];
        pTCB->target[tel].eqx.val.year = S_eqx[0];
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = S_wavel[0];
        pTCB->difftrack[tel].t0.val = S_tar_t0[0];
        pTCB->difftrack[tel].dtheta1.val = S_tar_dt[0][0];
        pTCB->difftrack[tel].dtheta2.val = S_tar_dt[0][1];
        break;

    case SOURCE_B:
        type = S_frame[1] == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = S_tar_p0[1][0];
        pTCB->target[tel].theta2.val = S_tar_p0[1][1];
        pTCB->target[tel].frame.val = S_frame[1];
        pTCB->target[tel].eqx.val.year = S_eqx[1];
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = S_wavel[1];
        pTCB->difftrack[tel].t0.val = S_tar_t0[1];
        pTCB->difftrack[tel].dtheta1.val = S_tar_dt[1][0];
        pTCB->difftrack[tel].dtheta2.val = S_tar_dt[1][1];
        break;

    case SOURCE_C:
        type = S_frame[2] == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = S_tar_p0[2][0];
        pTCB->target[tel].theta2.val = S_tar_p0[2][1];
        pTCB->target[tel].frame.val = S_frame[2];
        pTCB->target[tel].eqx.val.year = S_eqx[2];
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = S_wavel[2];
        pTCB->difftrack[tel].t0.val = S_tar_t0[2];
        pTCB->difftrack[tel].dtheta1.val = S_tar_dt[2][0];
        pTCB->difftrack[tel].dtheta2.val = S_tar_dt[2][1];
        break;

    case PWFS1:
        type = G1_frame == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = G1_tar_p0[0];
        pTCB->target[tel].theta2.val = G1_tar_p0[1];
        pTCB->target[tel].frame.val = G1_frame;
        pTCB->target[tel].eqx.val.year = G1_eqx;
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = G1_wavel;
        pTCB->difftrack[tel].t0.val = G1_tar_t0;
        pTCB->difftrack[tel].dtheta1.val = G1_tar_dt[0];
        pTCB->difftrack[tel].dtheta2.val = G1_tar_dt[1];
        break;

    case PWFS2:
        type = G2_frame == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = G2_tar_p0[0];
        pTCB->target[tel].theta2.val = G2_tar_p0[1];
        pTCB->target[tel].frame.val = G2_frame;
        pTCB->target[tel].eqx.val.year = G2_eqx;
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = G2_wavel;
        pTCB->difftrack[tel].t0.val = G2_tar_t0;
        pTCB->difftrack[tel].dtheta1.val = G2_tar_dt[0];
        pTCB->difftrack[tel].dtheta2.val = G2_tar_dt[1];
        break;

    case OIWFS:
        type = G3_frame == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = G3_tar_p0[0];
        pTCB->target[tel].theta2.val = G3_tar_p0[1];
        pTCB->target[tel].frame.val = G3_frame;
        pTCB->target[tel].eqx.val.year = G3_eqx;
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = G3_wavel;
        pTCB->difftrack[tel].t0.val = G3_tar_t0;
        pTCB->difftrack[tel].dtheta1.val = G3_tar_dt[0];
        pTCB->difftrack[tel].dtheta2.val = G3_tar_dt[1];
        break;

    case G1:
        type = GG1_frame == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = GG1_tar_p0[0];
        pTCB->target[tel].theta2.val = GG1_tar_p0[1];
        pTCB->target[tel].frame.val = GG1_frame;
        pTCB->target[tel].eqx.val.year = GG1_eqx;
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = GG1_wavel;
        pTCB->difftrack[tel].t0.val = GG1_tar_t0;
        pTCB->difftrack[tel].dtheta1.val = GG1_tar_dt[0];
        pTCB->difftrack[tel].dtheta2.val = GG1_tar_dt[1];
        break;

    case G2:
        type = GG2_frame == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = GG2_tar_p0[0];
        pTCB->target[tel].theta2.val = GG2_tar_p0[1];
        pTCB->target[tel].frame.val = GG2_frame;
        pTCB->target[tel].eqx.val.year = GG2_eqx;
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = GG2_wavel;
        pTCB->difftrack[tel].t0.val = GG2_tar_t0;
        pTCB->difftrack[tel].dtheta1.val = GG2_tar_dt[0];
        pTCB->difftrack[tel].dtheta2.val = GG2_tar_dt[1];
        break;

    case G3:
        type = GG3_frame == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = GG3_tar_p0[0];
        pTCB->target[tel].theta2.val = GG3_tar_p0[1];
        pTCB->target[tel].frame.val = GG3_frame;
        pTCB->target[tel].eqx.val.year = GG3_eqx;
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = GG3_wavel;
        pTCB->difftrack[tel].t0.val = GG3_tar_t0;
        pTCB->difftrack[tel].dtheta1.val = GG3_tar_dt[0];
        pTCB->difftrack[tel].dtheta2.val = GG3_tar_dt[1];
        break;

    case G4:
        type = GG4_frame == FK4 ? 'B' : 'J';
        pTCB->target[tel].theta1.val = GG4_tar_p0[0];
        pTCB->target[tel].theta2.val = GG4_tar_p0[1];
        pTCB->target[tel].frame.val = GG4_frame;
        pTCB->target[tel].eqx.val.year = GG4_eqx;
        pTCB->target[tel].eqx.val.type = type;
        pTCB->wavel[tel].wavel.val = GG4_wavel;
        pTCB->difftrack[tel].t0.val = GG4_tar_t0;
        pTCB->difftrack[tel].dtheta1.val = GG4_tar_dt[0];
        pTCB->difftrack[tel].dtheta2.val = GG4_tar_dt[1];
        break;

    default:
        break;

    }
    epicsMutexUnlock(TcsSemId);

/* Set epoch to same as equinox */
    pTCB->target[tel].epoch.val.year = pTCB->target[tel].eqx.val.year;
    pTCB->target[tel].epoch.val.type = pTCB->target[tel].eqx.val.type;

/* Differential tracking frame is same as target frame */
    pTCB->difftrack[tel].frame.val = pTCB->target[tel].frame.val;
    pTCB->difftrack[tel].eqx.val.year = pTCB->target[tel].eqx.val.year;
    pTCB->difftrack[tel].eqx.val.type = pTCB->target[tel].eqx.val.type;

/* Fill tracking structure */
    pTCB->track[tel].frame = pTCB->target[tel].frame;
    pTCB->track[tel].eqx = pTCB->target[tel].eqx;
    pTCB->track[tel].theta1 = pTCB->target[tel].theta1.val;
    pTCB->track[tel].theta2 = pTCB->target[tel].theta2.val;
    pTCB->track[tel].dtheta1 = pTCB->difftrack[tel].dtheta1.val;
    pTCB->track[tel].dtheta2 = pTCB->difftrack[tel].dtheta2.val;
    pTCB->track[tel].t0 = pTCB->difftrack[tel].t0.val;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetImagePos
 *
 *   Purpose:
 *   Get image position from global memory.
 *
 *   Description:
 *   This routine locks the kernel database and then copies the relevant
 *   image position data into an image position structure which is
 *   normally part of a Telescope Control Block. The index is used to
 *   indicate which pointing origin is required. This index should be
 *   in the range 0 to 1 for the mount and 0 to 3 for the other telescopes.
 *
 *   Invocation:
 *   tcsGetImagePos(telescope, index, pimagePos, &status)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    telescope  (TELESCOPE)  Enumerated type for telescope
 *      (>)    index      (int)        Identifier for image position
 *      (<)    pimagePos  (struct IMAGEPOS *) Pointer to imagePos structure
 *      (!)    status     (int *)      Status return
 *
 *   Function value:
 *     None
 *
 *   External functions:
 *   semTake        (semLib)           Takes a semaphore
 *   semGive        (semLib)           Gives a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetImagePos(TELESCOPE telescope, int index,
                    struct IMAGEPOS *pimagePos, int *status)
{
    if (*status != 0)
        return;

 if( TcsSemId) {
    epicsMutexLock(TcsSemId);

    switch (telescope) {
    case MOUNT:
        if (index == 0) {
            pimagePos->x.val = M_por_p0[0];
            pimagePos->y.val = M_por_p0[1];
        } else if (index == 1) {
            pimagePos->x.val = M_por_ob[0];
            pimagePos->y.val = M_por_ob[1];
        } else
            *status = -1;
        break;

    case SOURCE_A:
        if (index == 0) {
            pimagePos->x.val = S_por_p0[0][0];
            pimagePos->y.val = S_por_p0[0][1];
        } else if (index > 0 && index < 4) {
            pimagePos->x.val = S_por_ob[0][index - 1][0];
            pimagePos->y.val = S_por_ob[0][index - 1][1];
        } else
            *status = -1;
        break;

    case SOURCE_B:
        if (index == 0) {
            pimagePos->x.val = S_por_p0[1][0];
            pimagePos->y.val = S_por_p0[1][1];
        } else if (index > 0 && index < 4) {
            pimagePos->x.val = S_por_ob[1][index - 1][0];
            pimagePos->y.val = S_por_ob[1][index - 1][1];
        } else
            *status = -1;
        break;

    case SOURCE_C:
        if (index == 0) {
            pimagePos->x.val = S_por_p0[2][0];
            pimagePos->y.val = S_por_p0[2][1];
        } else if (index > 0 && index < 4) {
            pimagePos->x.val = S_por_ob[2][index - 1][0];
            pimagePos->y.val = S_por_ob[2][index - 1][1];
        } else
            *status = -1;
        break;

    default:
        break;

    }

    epicsMutexUnlock(TcsSemId);
  }
}

/*+
 *   Function name:
 *   tcsGetPO
 *
 *   Purpose:
 *   Fetch total pointing origin for the specified telescope
 *
 *   Description:
 *   Simply copy the relevant data from the global memory area into the
 *   return variables. If a non-valid telescope is given then simply return
 *   zeroes. Non-valid in this context means a guidestar target.
 *
 *   Invocation:
 *   tcsGetPO (telescope, &x, &y)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  telescope (TELESCOPE)  Enumerated type specifying the telescope
 *      (<)  x         (double *)   X pointing origin (mm) 
 *      (<)  y         (double *)   Y pointing origin (mm) 
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsGetPO (TELESCOPE telescope, double *x, double *y)
{

/* Initialise the return data */
  *x = 0.0 ;
  *y = 0.0 ;

  if (TcsSemId) {
    epicsMutexLock(TcsSemId);

  switch (telescope) {
    case MOUNT:
       *x = M_por_p[0] ;
       *y = M_por_p[1] ;
       break;

    case SOURCE_A:
       *x = S_por_p[0][0] ;
       *y = S_por_p[0][1] ;
       break ;

    case SOURCE_B:
       *x = S_por_p[1][0] ;
       *y = S_por_p[1][1] ;
       break ;

    case SOURCE_C:
       *x = S_por_p[2][0] ;
       *y = S_por_p[2][1] ;
       break ;
   
    default:
       break ;

  }

    epicsMutexUnlock(TcsSemId);
 }
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetBaseOffset
 *
 *   Purpose:
 *   Get offset from base from global memory.
 *
 *   Description:
 *   This routine locks the kernel database and then copies the relevant
 *   base offset data into an offset from base structure which is
 *   normally part of a Telescope Control Block. The index is used to
 *   indicate which base offset is required. This index should be
 *   in 0 for the Mount and guide telescopes and 0 to 2 for the other
 *   telescopes.
 *
 *   Invocation:
 *   tcsGetBaseOffset(telescope, index, pob, status)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    telescope  (TELESCOPE)  Enumerated type for telescope
 *      (>)    index      (int)        Identifier for image position
 *      (<)    pob        (struct OFFBASE *) Pointer to base offset structure
 *      (!)    status     (int *)      Status return
 *
 *   Function value:
 *     None
 *
 *   External functions:
 *   semTake        (semLib)           Takes a semaphore
 *   semGive        (semLib)           Gives a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetBaseOffset(TELESCOPE telescope, int index, struct OFFBASE *pob,
                      int *status)
{

    if (*status != 0)
        return;

    if( ! TcsSemId) 
        return;
	
    epicsMutexLock(TcsSemId);

    switch (telescope) {
    case MOUNT:
        if (index == 0) {
            tcsCtSphToOff(M_frame, M_tar_p0, pob->coord.val, M_tar_ob,
                          &pob->dtheta1.val, &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case SOURCE_A:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(S_frame[0], S_tar_p0[0], pob->coord.val,
                          S_tar_ob[0][index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case SOURCE_B:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(S_frame[1], S_tar_p0[1], pob->coord.val,
                          S_tar_ob[1][index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case SOURCE_C:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(S_frame[2], S_tar_p0[2], pob->coord.val,
                          S_tar_ob[2][index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case PWFS1:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(G1_frame, G1_tar_p0, pob->coord.val,
                          G1_tar_ob[index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case PWFS2:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(G2_frame, G2_tar_p0, pob->coord.val,
                          G2_tar_ob[index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case OIWFS:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(G3_frame, G3_tar_p0, pob->coord.val,
                          G3_tar_ob[index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case G1:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(GG1_frame, GG1_tar_p0, pob->coord.val,
                          GG1_tar_ob[index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case G2:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(GG2_frame, GG2_tar_p0, pob->coord.val,
                          GG2_tar_ob[index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case G3:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(GG3_frame, GG3_tar_p0, pob->coord.val,
                          GG3_tar_ob[index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    case G4:
        if (index >= 0 || index < 3) {
            tcsCtSphToOff(GG4_frame, GG4_tar_p0, pob->coord.val,
                          GG4_tar_ob[index], &pob->dtheta1.val,
                          &pob->dtheta2.val);
        } else
            *status = -1;
        break;

    default:
        break;

    }

    epicsMutexUnlock(TcsSemId);

}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetRotConfig
 *
 *   Purpose:
 *   Get rotator configuration from global memory.
 *
 *   Description:
 *   This routine locks the kernel database and then copies the relevant
 *   rotator configuration data into an ROT structure which is
 *   normally part of a Telescope Control Block.
 *
 *   Invocation:
 *   tcsGetRotConfig( rot)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<)    rot     (struct ROT *) Pointer to ROT structure
 *
 *   Function value:
 *     None
 *
 *   External functions:
 *   semTake        (semLib)           Takes a semaphore
 *   semGive        (semLib)           Gives a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetRotConfig(struct ROT *rot)
{
 if( TcsSemId) {
    epicsMutexLock(TcsSemId);

    rot->ipa.val = Ipa;
    rot->frame.val = R_frame;
    rot->eqx.val.year = R_eqx;
    if (R_eqx == FK4) {
        rot->eqx.val.type = 'B';
    } else if (R_eqx == FK5) {
        rot->eqx.val.type = 'J';
    } else {
        rot->eqx.val.type = ' ';
    }
    rot->iaa.val = Iaa;

    epicsMutexUnlock(TcsSemId);
  }
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetPlanet
 *
 *   Purpose:
 *   Get planet configuration from global memory.
 *
 *   Description:
 *   This routine locks the kernel database and then copies the relevant
 *   planet configuration data into the planet structure of the  
 *   Telescope Control Block.
 *
 *   Invocation:
 *   tcsGetPlanet(tel, pTCB)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    tel      (TELESCOPE)  Virtual telescope
 *      (<)    pTCB     (struct TCB *) Pointer to TCB structure
 *
 *   Function value:
 *     None
 *
 *   External functions:
 *   semTake        (semLib)           Takes a semaphore
 *   semGive        (semLib)           Gives a semaphore
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetPlanet(TELESCOPE tel, struct TCB *pTCB)
{
 if( TcsSemId) {
    epicsMutexLock(TcsSemId);

    pTCB->planet[tel].code.val = P_code[tel];

    epicsMutexUnlock(TcsSemId);
 }
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetOrbit
 *
 *   Purpose:
 *   Get orbit configuration from global memory.
 *
 *   Description:
 *   This routine locks the kernel database and then copies the relevant
 *   orbit configuration data into an orbit structure which is normally
 *   part of a Telescope Control Block.
 *
 *   Invocation:
 *   tcsGetPlanet(tel, orbit)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    tel         (TELESCOPE)      Virtual telescope identifier
 *      (<)    orbit       (struct ORBIT *) Pointer to orbit structure
 *
 *   Function value:
 *     None
 *
 *   External functions:
 *   semTake        (semLib)           Takes a semaphore
 *   semGive        (semLib)           Gives a semaphore
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *-
 */
/* *INDENT-ON* */


void tcsGetOrbit(TELESCOPE tel, struct ORBIT *orbit)
{
 if( TcsSemId) {
    epicsMutexLock(TcsSemId);

    orbit->jform.val = O_jform[tel];
    orbit->epoch.val = O_epoch[tel];
    orbit->orbinc.val = O_orbinc[tel];
    orbit->anode.val = O_anode[tel];
    orbit->perih.val = O_perih[tel];
    orbit->aorq.val = O_aorq[tel];
    orbit->e.val = O_e[tel];
    orbit->aorl.val = O_aorl[tel];
    orbit->dm.val = O_dm[tel];

    epicsMutexUnlock(TcsSemId);
  }
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsAbsorbOffsets
 *
 *   Purpose:
 *   Absorbs offsets into source positions.
 *
 *   Description:
 *   Adds the selected offsets to the source positions for the nominated
 *   virtual telescopes and sets the offsets to zero. The net result of
 *   this operation is that the virtual telescope continues to track the
 *   same position.
 *
 *   Invocation:
 *   tcsAbsorbOffsets( telmask, ind )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    telmask  (TELESCOPE_M)  Virtual telescope mask
 *      (>)    ind      (int)          Offset index. Applies to source VTs
 *                                     only. (-1 => all offsets)
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (!)   M_tar_ob  (double)    Mount offsets
 *   (!)   S_tar_ob  (double)    Source offsets
 *   (!)   G1_tar_ob (double)    PWFS#1 offsets
 *   (!)   G2_tar_ob (double)    PWFS#2 offsets
 *   (!)   G3_tar_ob (double)    OIWFS offsets
 *   (!)   M_tar_p0  (double)    Mount source position
 *   (!)   S_tar_p0  (double)    Source source positions
 *   (!)   G1_tar_p0 (double)    PWFS#1 source positions
 *   (!)   G2_tar_p0 (double)    PWFS#2 source positions
 *   (!)   G3_tar_p0 (double)    OIWFS source positions
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

void tcsAbsorbOffsets( TELESCOPE_M telmask, int ind)
{
    int i;
    double delta[2];
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsAbsorbOffsets: Semaphore not created");
        return;
    }

/* Lock the global database */
    epicsMutexLock(TcsSemId);

/* For each virtual telesope in the mask, add the specified offsets to
   the source position and set the offsets to zero. */
    if ( telmask & MOUNT_M ) {
        M_tar_p0[0] += M_tar_ob[0];
        M_tar_p0[1] += M_tar_ob[1];
        M_tar_ob[0] = 0.0;
        M_tar_ob[1] = 0.0;
    }
    if ( telmask & SOURCE_A_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_tar_p0[0][0] += S_tar_ob[0][ind][0];
            S_tar_p0[0][1] += S_tar_ob[0][ind][1];
            S_tar_ob[0][ind][0] = 0.0;
            S_tar_ob[0][ind][1] = 0.0;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_tar_p0[0][0] += S_tar_ob[0][i][0];
                S_tar_p0[0][1] += S_tar_ob[0][i][1];
                S_tar_ob[0][i][0] = 0.0;
                S_tar_ob[0][i][1] = 0.0;
            }
        }
    }
    if ( telmask & SOURCE_B_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_tar_p0[1][0] += S_tar_ob[1][ind][0];
            S_tar_p0[1][1] += S_tar_ob[1][ind][1];
            S_tar_ob[1][ind][0] = 0.0;
            S_tar_ob[1][ind][1] = 0.0;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_tar_p0[1][0] += S_tar_ob[1][i][0];
                S_tar_p0[1][1] += S_tar_ob[1][i][1];
                S_tar_ob[1][i][0] = 0.0;
                S_tar_ob[1][i][1] = 0.0;
            }
        }
    }
    if ( telmask & SOURCE_C_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_tar_p0[2][0] += S_tar_ob[2][ind][0];
            S_tar_p0[2][1] += S_tar_ob[2][ind][1];
            S_tar_ob[2][ind][0] = 0.0;
            S_tar_ob[2][ind][1] = 0.0;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_tar_p0[2][0] += S_tar_ob[2][i][0];
                S_tar_p0[2][1] += S_tar_ob[2][i][1];
                S_tar_ob[2][i][0] = 0.0;
                S_tar_ob[2][i][1] = 0.0;
            }
        }
    }
    if ( telmask & PWFS1_M ) {
        if ( ind >= 0 && ind < 3 ) {
            delta[0] = G1_tar_ob[ind][0];
            delta[1] = G1_tar_ob[ind][1];
            G1_tar_p0[0] += delta[0];
            G1_tar_p0[1] += delta[1];
            for ( i = 0; i < 3; i++ ) {
               G1_tar_ob[i][0] -= delta[0];
               G1_tar_ob[i][1] -= delta[1];
            }
        } 
    }
    if ( telmask & PWFS2_M ) {
        if ( ind >= 0 && ind < 3 ) {
            delta[0] = G2_tar_ob[ind][0];
            delta[1] = G2_tar_ob[ind][1];
            G2_tar_p0[0] += delta[0];
            G2_tar_p0[1] += delta[1];
            for ( i = 0; i < 3; i++ ) {
               G2_tar_ob[i][0] -= delta[0];
               G2_tar_ob[i][1] -= delta[1];
            }
        } 
    }
    if ( telmask & OIWFS_M ) {
        if ( ind >= 0 && ind < 3 ) {
            delta[0] = G3_tar_ob[ind][0];
            delta[1] = G3_tar_ob[ind][1];
            G3_tar_p0[0] += delta[0];
            G3_tar_p0[1] += delta[1];
            for ( i = 0; i < 3; i++ ) {
               G3_tar_ob[i][0] -= delta[0];
               G3_tar_ob[i][1] -= delta[1];
            }
        } 
    }
    if ( telmask & G1_M ) {
        if ( ind >= 0 && ind < 3 ) {
            delta[0] = GG1_tar_ob[ind][0];
            delta[1] = GG1_tar_ob[ind][1];
            GG1_tar_p0[0] += delta[0];
            GG1_tar_p0[1] += delta[1];
            for ( i = 0; i < 3; i++ ) {
               GG1_tar_ob[i][0] -= delta[0];
               GG1_tar_ob[i][1] -= delta[1];
            }
        } 
    }
    if ( telmask & G2_M ) {
        if ( ind >= 0 && ind < 3 ) {
            delta[0] = GG2_tar_ob[ind][0];
            delta[1] = GG2_tar_ob[ind][1];
            GG2_tar_p0[0] += delta[0];
            GG2_tar_p0[1] += delta[1];
            for ( i = 0; i < 3; i++ ) {
               GG2_tar_ob[i][0] -= delta[0];
               GG2_tar_ob[i][1] -= delta[1];
            }
        } 
    }
    if ( telmask & G3_M ) {
        if ( ind >= 0 && ind < 3 ) {
            delta[0] = GG3_tar_ob[ind][0];
            delta[1] = GG3_tar_ob[ind][1];
            GG3_tar_p0[0] += delta[0];
            GG3_tar_p0[1] += delta[1];
            for ( i = 0; i < 3; i++ ) {
               GG3_tar_ob[i][0] -= delta[0];
               GG3_tar_ob[i][1] -= delta[1];
            }
        } 
    }
    if ( telmask & G4_M ) {
        if ( ind >= 0 && ind < 3 ) {
            delta[0] = GG4_tar_ob[ind][0];
            delta[1] = GG4_tar_ob[ind][1];
            GG4_tar_p0[0] += delta[0];
            GG4_tar_p0[1] += delta[1];
            for ( i = 0; i < 3; i++ ) {
               GG4_tar_ob[i][0] -= delta[0];
               GG4_tar_ob[i][1] -= delta[1];
            }
        } 
    }

/* Release the global database */
    epicsMutexUnlock(TcsSemId);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsAbsorbPoOffsets
 *
 *   Purpose:
 *   Absorbs offsets into pointing origins.
 *
 *   Description:
 *   Adds the selected offsets to the pointing origins for the nominated
 *   virtual telescopes and sets the offsets to zero. The net result of
 *   this operation is that the virtual telescope continues to track the
 *   same position.
 *
 *   Invocation:
 *   tcsAbsorbPoOffsets( telmask, ind )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    telmask  (TELESCOPE_M)  Virtual telescope mask
 *      (>)    ind      (int)          Offset index. Applies to source VTs
 *                                     only. (-1 => all offsets)
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (!)   M_por_ob  (double)    mount pointing origin offsets
 *   (!)   S_por_ob  (double)    source pointing origin offsets
 *   (!)   M_por_p0  (double)    mount pointing origin
 *   (!)   S_por_p0  (double)    source pointing origins
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

void tcsAbsorbPoOffsets( TELESCOPE_M telmask, int ind )
{
    int i;
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsAbsorbPoOffsets: Semaphore not created");
        return;
    }
	
/* Lock the global database. */
    epicsMutexLock(TcsSemId);

/* For each virtual telesope in the mask, add the specified offsets to
   the source position and set the offsets to zero. */
    if ( telmask & MOUNT_M ) {
        M_por_p0[0] += M_por_ob[0];
        M_por_p0[1] += M_por_ob[1];
        M_por_ob[0] = 0.0;
        M_por_ob[1] = 0.0;
    }
    if ( telmask & SOURCE_A_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_p0[0][0] += S_por_ob[0][ind][0];
            S_por_p0[0][1] += S_por_ob[0][ind][1];
            S_por_ob[0][ind][0] = 0.0;
            S_por_ob[0][ind][1] = 0.0;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_por_p0[0][0] += S_por_ob[0][i][0];
                S_por_p0[0][1] += S_por_ob[0][i][1];
                S_por_ob[0][i][0] = 0.0;
                S_por_ob[0][i][1] = 0.0;
            }
        }
    }
    if ( telmask & SOURCE_B_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_p0[1][0] += S_por_ob[1][ind][0];
            S_por_p0[1][1] += S_por_ob[1][ind][1];
            S_por_ob[1][ind][0] = 0.0;
            S_por_ob[1][ind][1] = 0.0;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_por_p0[1][0] += S_por_ob[1][i][0];
                S_por_p0[1][1] += S_por_ob[1][i][1];
                S_por_ob[1][i][0] = 0.0;
                S_por_ob[1][i][1] = 0.0;
            }
        }
    }
    if ( telmask & SOURCE_C_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_p0[2][0] += S_por_ob[2][ind][0];
            S_por_p0[2][1] += S_por_ob[2][ind][1];
            S_por_ob[2][ind][0] = 0.0;
            S_por_ob[2][ind][1] = 0.0;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_por_p0[2][0] += S_por_ob[2][i][0];
                S_por_p0[2][1] += S_por_ob[2][i][1];
                S_por_ob[2][i][0] = 0.0;
                S_por_ob[2][i][1] = 0.0;
            }
        }
    }

/* Release the global database. */
    epicsMutexUnlock(TcsSemId);
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsGetGSAOIDistortion
 *
 *   Purpose:
 *   Retrieves GSAOI Distortion coefficients.
 *
 *   Description:
 *   Simply return the asked for coefficients
 * 
 *   Invocation:
 *   tcsGetGSAOIDistortion( type, &coeffs )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    type      (int)           0 => TCS -> GSAOI
 *      (<)    coeffs    (double *)      Array of distortion coefficients 
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *-
 */
/* *INDENT-ON* */

void tcsGetGSAOIDistortion( int type, double* coeffs)
{

    int i ;

 if( TcsSemId) {
/* Lock the global database. */
    epicsMutexLock(TcsSemId);
      if (type > 0) {
        for (i = 0; i < 5; i ++) {
          coeffs[i] = Gsaoi2t[i];
        }
      } else {
        for (i = 0; i < 5; i ++) {
          coeffs[i] = T2gsaoi[i];
        }
      }
/* Release the global database */
    epicsMutexUnlock(TcsSemId);
  }
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSetGSAOIDistortion
 *
 *   Purpose:
 *   Sets GSAOI Distortion coefficients.
 *
 *   Description:
 *   Normally it is up to the instrument to compensate for any optical
 *   distortions that arise internally. AO is a bit different as it is
 *   typically part of the telescope. Altair introduced a set of 
 *   distortion coeffs but these have always (?) been left as an identity
 *   transformation. GSAOI although an instrument introduces image 
 *   shifts when a filter is changed that the TCS is required to 
 *   compensate for. This routine was introduced so that tcsProbeLib
 *   could set the coeffs when GSAOI was in use. tcsDriveAOS (which
 *   is used by Altair) doesn't need to call this routine as it has
 *   direct access to the Ao2t arrays.
 *
 *   Invocation:
 *   tcsSetGSAOIDistortion( coeffs )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    coeffs    (double *)      Array of distortion coefficients 
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *-
 */
/* *INDENT-ON* */

void tcsSetGSAOIDistortion( double* coeffs)
{

    int i ;
    double icoeffs[6] ;  /* Inverse coefficients */
    int istat ;

 if( TcsSemId) {
/* Lock the global database. */
    epicsMutexLock(TcsSemId);
      for (i = 0; i < 5; i ++) {
        Gsaoi2t[i] = coeffs[i];
      }
      slaInvf ( coeffs, icoeffs, &istat) ;
      for (i = 0; i < 5; i ++) {
        T2gsaoi[i] = icoeffs[i];
      }
/* Release the global database */
    epicsMutexUnlock(TcsSemId);
 }
}

/*+
 *   Function name:
 *   tcsSetOffsets
 *
 *   Purpose:
 *   Sets source position offsets.
 *
 *   Description:
 *   Sets the offsets for the nominated virtual telescopes.
 *
 *   Invocation:
 *   tcsSetOffsets( telmask, ind )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    telmask  (TELESCOPE_M)  Virtual telescope mask
 *      (>)    ind      (int)          Offset index. (-1 => all offsets)
 *      (>)    x        (double)       New value for x
 *      (>)    y        (double)       New value for y
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (!)   M_tar_ob  (double)    mount offsets
 *   (!)   S_tar_ob  (double)    source offsets
 *   (!)   G1_tar_ob (double)    PWFS#1 offsets
 *   (!)   G2_tar_ob (double)    PWFS#2 offsets
 *   (!)   G3_tar_ob (double)    OIWFS offsets
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

void tcsSetOffsets( TELESCOPE_M telmask, int ind, double x, double y)
{
    int i;
    double trackid;
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsSetOffsets: Semaphore not created");
        return;
    }
	
/* Generate a new track identifier. */
    timeNow(&trackid);

/* Lock the global database. */
    epicsMutexLock(TcsSemId);

/* For each virtual telesope in the mask, add the specified offsets to
   the source position and set the offsets to zero. */
    if ( telmask & MOUNT_M ) {
        M_tar_ob[0] = x;
        M_tar_ob[1] = y;
    }
    if ( telmask & SOURCE_A_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_tar_ob[0][ind][0] = x;
            S_tar_ob[0][ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_tar_ob[0][i][0] = x;
                S_tar_ob[0][i][1] = y;
            }
        }
    }
    if ( telmask & SOURCE_B_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_tar_ob[1][ind][0] = x;
            S_tar_ob[1][ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_tar_ob[1][i][0] = x;
                S_tar_ob[1][i][1] = y;
            }
        }
    }
    if ( telmask & SOURCE_C_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_tar_ob[2][ind][0] = x;
            S_tar_ob[2][ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_tar_ob[2][i][0] = x;
                S_tar_ob[2][i][1] = y;
            }
        }
    }
    if ( telmask & PWFS1_M ) {
        if ( ind >= 0 && ind < 3 ) {
            G1_tar_ob[ind][0] = x;
            G1_tar_ob[ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                G1_tar_ob[i][0] = x;
                G1_tar_ob[i][1] = y;
            }
        }
    }
    if ( telmask & PWFS2_M ) {
        if ( ind >= 0 && ind < 3 ) {
            G2_tar_ob[ind][0] = x;
            G2_tar_ob[ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                G2_tar_ob[i][0] = x;
                G2_tar_ob[i][1] = y;
            }
        }
    }
    if ( telmask & OIWFS_M ) {
        if ( ind >= 0 && ind < 3 ) {
            G3_tar_ob[ind][0] = x;
            G3_tar_ob[ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                G3_tar_ob[i][0] = x;
                G3_tar_ob[i][1] = y;
            }
        }
    }
    if ( telmask & G1_M ) {
        if ( ind >= 0 && ind < 3 ) {
            GG1_tar_ob[ind][0] = x;
            GG1_tar_ob[ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                GG1_tar_ob[i][0] = x;
                GG1_tar_ob[i][1] = y;
            }
        }
    }
    if ( telmask & G2_M ) {
        if ( ind >= 0 && ind < 3 ) {
            GG2_tar_ob[ind][0] = x;
            GG2_tar_ob[ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                GG2_tar_ob[i][0] = x;
                GG2_tar_ob[i][1] = y;
            }
        }
    }
    if ( telmask & G3_M ) {
        if ( ind >= 0 && ind < 3 ) {
            GG3_tar_ob[ind][0] = x;
            GG3_tar_ob[ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                GG3_tar_ob[i][0] = x;
                GG3_tar_ob[i][1] = y;
            }
        }
    }
    if ( telmask & G4_M ) {
        if ( ind >= 0 && ind < 3 ) {
            GG4_tar_ob[ind][0] = x;
            GG4_tar_ob[ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                GG4_tar_ob[i][0] = x;
                GG4_tar_ob[i][1] = y;
            }
        }
    }

    Trackid = trackid;

/* Release the global database */
    epicsMutexUnlock(TcsSemId);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSetPoOffsets
 *
 *   Purpose:
 *   Sets pointing origin offsets.
 *
 *   Description:
 *   Sets the selected the pointing origin offsets for the nominated
 *   virtual telescopes. 
 *
 *   Invocation:
 *   tcsSetPoOffsets( telmask, ind )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    telmask  (TELESCOPE_M)  Virtual telescope mask
 *      (>)    ind      (int)          Offset index. Applies to source VTs
 *                                     only. (-1 => all offsets)
 *      (>)    x        (double)       New value for x
 *      (>)    y        (double)       New value for y
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (!)   M_por_ob  (double)    mount pointing origin offsets
 *   (!)   S_por_ob  (double)    source pointing origin offsets
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

void tcsSetPoOffsets( TELESCOPE_M telmask, int ind, double x, double y)
{
    int i;
    double trackid;

    if( ! TcsSemId) 
	return;

/* Generate a new track identifier. */
    timeNow(&trackid);

/* Lock the global database. */
    epicsMutexLock(TcsSemId);

/* For each virtual telesope in the mask, add the specified offsets to
   the source position and set the offsets to zero. */
    if ( telmask & MOUNT_M ) {
        M_por_ob[0] = x;
        M_por_ob[1] = y;
    }
    if ( telmask & SOURCE_A_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_ob[0][ind][0] = x;
            S_por_ob[0][ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_por_ob[0][i][0] = x;
                S_por_ob[0][i][1] = y;
            }
        }
    }
    if ( telmask & SOURCE_B_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_ob[1][ind][0] = x;
            S_por_ob[1][ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_por_ob[1][i][0] = x;
                S_por_ob[1][i][1] = y;
            }
        }
    }
    if ( telmask & SOURCE_C_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_ob[2][ind][0] = x;
            S_por_ob[2][ind][1] = y;
        } else if ( ind == -1 ) {
            for ( i = 0; i < 3; i++ ) {
                S_por_ob[2][i][0] = x;
                S_por_ob[2][i][1] = y;
            }
        }
    }

    Trackid = trackid;

/* Release the global database. */
    epicsMutexUnlock(TcsSemId);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsIncrOffsets
 *
 *   Purpose:
 *   Increments one or more source offsets.
 *
 *   Description:
 *   Adds the specified amounts to the nominated offsets for the
 *   selected virtual telescopes.
 *
 *   Invocation:
 *   tcsIncrOffsets( delta1, delta2, telmask, ind )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    tanp     (int)          true if offset is tangent plane
 *      (>)    delta1   (double)       the first increment (radians)
 *      (>)    delta2   (double)       the second increment (radians)
 *      (>)    telmask  (TELESCOPE_M)  virtual telescope mask
 *      (>)    ind      (int)          offset index
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (!)   M_tar_ob  (double)    mount offsets
 *   (!)   S_tar_ob  (double)    source offsets
 *   (!)   G1_tar_ob (double)    PWFS#1 offsets
 *   (!)   G2_tar_ob (double)    PWFS#2 offsets
 *   (!)   G3_tar_ob (double)    OIWFS offsets
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

void tcsIncrOffsets( int tanp, double delta1, double delta2, 
                     TELESCOPE_M telmask, int ind)
{
    double trackid;
    double theta1, theta2;
    int i;
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsIncrOffsets: Semaphore not created");
        return;
    }
	
/* Generate a new track identifier. */
    timeNow(&trackid);

/* Lock the global database. */
    epicsMutexLock(TcsSemId);

/* For each virtual telesope in the mask, add the specified increments to
   the offsets. */
    if ( telmask & MOUNT_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, M_tar_p0[0], M_tar_p0[1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - M_tar_p0[0] );
            delta2 = slaDrange( theta2 - M_tar_p0[1] );
        }
        M_tar_ob[0] += delta1;
        M_tar_ob[1] += delta2;
    }
    if ( telmask & SOURCE_A_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, S_tar_p0[0][0], S_tar_p0[0][1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - S_tar_p0[0][0] );
            delta2 = slaDrange( theta2 - S_tar_p0[0][1] );
        }
        if ( ind >= 0 && ind < 3 ) {
             S_tar_ob[0][ind][0] += delta1;
             S_tar_ob[0][ind][1] += delta2;
        }
    }
    if ( telmask & SOURCE_B_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, S_tar_p0[1][0], S_tar_p0[1][1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - S_tar_p0[1][0] );
            delta2 = slaDrange( theta2 - S_tar_p0[1][1] );
        }
        if ( ind >= 0 && ind < 3 ) {
             S_tar_ob[1][ind][0] += delta1;
             S_tar_ob[1][ind][1] += delta2;
        }
    }
    if ( telmask & SOURCE_C_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, S_tar_p0[2][0], S_tar_p0[2][1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - S_tar_p0[2][0] );
            delta2 = slaDrange( theta2 - S_tar_p0[2][1] );
        }
        if ( ind >= 0 && ind < 3 ) {
            S_tar_ob[2][ind][0] += delta1;
            S_tar_ob[2][ind][1] += delta2;
        }
    }
    if ( telmask & PWFS1_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, G1_tar_p0[0], G1_tar_p0[1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - G1_tar_p0[0] );
            delta2 = slaDrange( theta2 - G1_tar_p0[1] );
        }
        for ( i = 0; i < 3; i++ ) {
            G1_tar_ob[i][0] += delta1;
            G1_tar_ob[i][1] += delta2;
        }
    }
    if ( telmask & PWFS2_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, G2_tar_p0[0], G2_tar_p0[1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - G2_tar_p0[0] );
            delta2 = slaDrange( theta2 - G2_tar_p0[1] );
        }
        for ( i = 0; i < 3; i++ ) {
            G2_tar_ob[i][0] += delta1;
            G2_tar_ob[i][1] += delta2;
        }
    }
    if ( telmask & OIWFS_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, G3_tar_p0[0], G3_tar_p0[1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - G3_tar_p0[0] );
            delta2 = slaDrange( theta2 - G3_tar_p0[1] );
        }
        for ( i = 0; i < 3; i++ ) {
            G3_tar_ob[i][0] += delta1;
            G3_tar_ob[i][1] += delta2;
        }
    }
    if ( telmask & G1_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, GG1_tar_p0[0], GG1_tar_p0[1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - GG1_tar_p0[0] );
            delta2 = slaDrange( theta2 - GG1_tar_p0[1] );
        }
        for ( i = 0; i < 3; i++ ) {
            GG1_tar_ob[i][0] += delta1;
            GG1_tar_ob[i][1] += delta2;
        }
    }
    if ( telmask & G2_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, GG2_tar_p0[0], GG2_tar_p0[1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - GG2_tar_p0[0] );
            delta2 = slaDrange( theta2 - GG2_tar_p0[1] );
        }
        for ( i = 0; i < 3; i++ ) {
            GG2_tar_ob[i][0] += delta1;
            GG2_tar_ob[i][1] += delta2;
        }
    }
    if ( telmask & G3_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, GG3_tar_p0[0], GG3_tar_p0[1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - GG3_tar_p0[0] );
            delta2 = slaDrange( theta2 - GG3_tar_p0[1] );
        }
        for ( i = 0; i < 3; i++ ) {
            GG3_tar_ob[i][0] += delta1;
            GG3_tar_ob[i][1] += delta2;
        }
    }
    if ( telmask & G4_M ) {
        if (tanp) {
            slaDtp2s( delta1, delta2, GG4_tar_p0[0], GG4_tar_p0[1], &theta1, 
                &theta2);
            delta1 = slaDrange( theta1 - GG4_tar_p0[0] );
            delta2 = slaDrange( theta2 - GG4_tar_p0[1] );
        }
        for ( i = 0; i < 3; i++ ) {
            GG4_tar_ob[i][0] += delta1;
            GG4_tar_ob[i][1] += delta2;
        }
    }

    Trackid = trackid;

/* Release the global database. */
    epicsMutexUnlock(TcsSemId);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsIncrPoOffsets
 *
 *   Purpose:
 *   Increments one or more pointing origin offsets.
 *
 *   Description:
 *   Adds the specified amnounts to the nominated pointing origin offsets 
 *   for the selected virtual telescopes.
 *
 *   Invocation:
 *   tcsIncrPoOffsets( delta1, delta2, telmask, ind )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    delta1   (double)       the first increment (mm)
 *      (>)    delta2   (double)       the second increment (mm)
 *      (>)    telmask  (TELESCOPE_M)  virtual telescope mask
 *      (>)    ind      (int)          offset index (source VTs only)
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (!)   M_por_ob  (double)    mount offsets
 *   (!)   S_por_ob  (double)    source offsets
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

void tcsIncrPoOffsets( double delta1, double delta2, TELESCOPE_M telmask,
                     int ind)
{
    double trackid;
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsIncrPoOffsets: Semaphore not created");
        return;
    }

/* Generate a new track identifier. */
    timeNow(&trackid);

/* Lock the global database. */
    epicsMutexLock(TcsSemId);

/* For each virtual telesope in the mask, add the specified increments to
   the offsets. */
    if ( telmask & MOUNT_M ) {
        M_por_ob[0] += delta1;
        M_por_ob[1] += delta2;
    }
    if ( telmask & SOURCE_A_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_ob[0][ind][0] += delta1;
            S_por_ob[0][ind][1] += delta2;
        }
    }
    if ( telmask & SOURCE_B_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_ob[1][ind][0] += delta1;
            S_por_ob[1][ind][1] += delta2;
        }
    }
    if ( telmask & SOURCE_C_M ) {
        if ( ind >= 0 && ind < 3 ) {
            S_por_ob[2][ind][0] += delta1;
            S_por_ob[2][ind][1] += delta2;
        }
    }

    Trackid = trackid;

/* Release the global database */
    epicsMutexUnlock(TcsSemId);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsNod
 *
 *   Purpose:
 *   Nod the telescope.
 *
 *   Description:
 *   This code has to be run whenever the nod state changes.  It
 *   manipulates element [2] of the offsets from base (both TCB->target
 *   and pointing-origin).
 *
 *   The nod state specifies which chop state has the star,
 *   based on the assumption that the star began in chop state A.
 *   The variable nod has the following values and meanings:
 *
 *      nod         meaning
 *
 *       0          star in chop state A
 *       1          star in chop state B
 *       2          star in chop state C
 *
 *   Invocation:
 *   tcsNod( nod )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    nod      (int)          Chop state to contain star
 *
 *   Function value:
 *   None
 *
 *   External functions:
 *   semTake         sem        Takes VxWorks semaphore
 *   semGive         sem        Releases VxWorks semaphore
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (>)   S_tar_p0  (double)    source targets
 *   (>)   S_por_p0  (double)    source pointing origins
 *   (>)   S_otm1    (double)    source OTM1s
 *   (>)   S_otm2    (double)    source OTM2s
 *   (>)   S_otm1_i  (double)    inverse source OTM1s
 *   (>)   S_otm2_i  (double)    inverse source OTM2s
 *   (>)   S_frame   (int)       source coordinate frames
 *   (>)   Cst       (double)    cosine of sidereal time
 *   (>)   Sst       (double)    sine of sidereal time
 *   (<)   S_tar_ob  (double)    source offset from base
 *   (<)   S_por_ob  (double)    source pointing origin offset
 *   (<)   Trackid   (double)    subsystem track identifier
 *   (!)   F2_sc     (int)       pointing filter catchup flag
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

void tcsNod( int nod )
{

    double a0, b0, xieta[3][2], xi, eta, a, b, w, tar_p[2];
    double xu, yu, zu, xa, ya, za, xh, yh, zh, xm, ym, zm;
    double sst, cst;
    int ixy, ichop, j, k;
    double s_tar_pc[3][2], s_por_p0[3][2];
    double s_tar_ob[3][2], s_por_ob[3][2];
    double s_otm1[3][3][3], s_otm2[3][3][3];
    double s_otm1_i[3][3][3], s_otm2_i[3][3][3];
    int s_frame[3];
    int f2_sc;
    double trackid;
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsNod: Semaphore not created");
        return;
    }

    epicsMutexLock(TcsSemId);
    for ( ichop = 0; ichop < 3; ichop++) {
        for ( ixy = 0; ixy < 2; ixy++) {
            s_tar_pc[ichop][ixy] = S_tar_pc[ichop][ixy];
            s_por_p0[ichop][ixy] = S_por_p0[ichop][ixy];
            s_tar_ob[ichop][ixy] = S_tar_ob[ichop][NODOB][ixy];
        }
        s_frame[ichop] = S_frame[ichop];
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                s_otm1[ichop][j][k] = S_otm1[ichop][j][k];
                s_otm2[ichop][j][k] = S_otm2[ichop][j][k];
                s_otm1_i[ichop][j][k] = S_otm1_i[ichop][j][k];
                s_otm2_i[ichop][j][k] = S_otm2_i[ichop][j][k];
            }
        }
    }
    sst = Sst;
    cst = Cst;
    f2_sc = F2_sc;
    epicsMutexUnlock(TcsSemId);

/* Use source A target as the centre of a tangent-plane projection. */
    a0 = s_tar_pc[0][0] - s_tar_ob[0][0];
    b0 = s_tar_pc[0][1] - s_tar_ob[0][1];

/* Generate the target xi/eta for the three chop states. */
    for (ixy = 0; ixy < 2; ixy++) {
        xieta[0][ixy] = 0.0;
    }
    for (ichop = 1; ichop < 3; ichop++) {

    /* Chop B/C to pre-collimation Az/El. */
        tar_p[0] = s_tar_pc[ichop][0] - s_tar_ob[ichop][0];
        tar_p[1] = s_tar_pc[ichop][1] - s_tar_ob[ichop][1];
        PartA ( s_frame[ichop], tar_p,
                s_otm1[ichop], sst, cst, s_otm2[ichop],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &xm, &ym, &zm );

    /* Chop B/C pre-collimation Az/El to chop A tracking frame. */
        PartAv ( s_frame[0], xm, ym, zm,
                 s_otm2_i[0], -sst, cst, s_otm1_i[0],
                 &xh, &yh, &zh, &xa, &ya, &za,
                 &xu, &yu, &zu );
        tar_p[0] = atan2 ( yu, s_frame[0] == AZEL_TOPO ? -xu : xu );
        tar_p[1] = atan2 ( zu, sqrt ( xu * xu + yu * yu ) );

        slaDs2tp(tar_p[0], tar_p[1], a0, b0,
                 &xieta[ichop][0], &xieta[ichop][1], &j);
    }

/* Take each chop state in turn. */
    for (ichop = 0; ichop < 3; ichop++) {

    /* Subtract the "star in" target xi/eta from the xi/eta for this */
    /* chop state, giving the nodded xi/eta for this chop state.     */
        xi = xieta[ichop][0] - xieta[nod][0];
        eta = xieta[ichop][1] - xieta[nod][1];

    /* Turn back into spherical coordinates. */
        slaDtp2s(xi, eta, a0, b0, &tar_p[0], &tar_p[1]);

    /* To pre-collimation Az/El. */
        PartA ( s_frame[0], tar_p,
                s_otm1[0], sst, cst, s_otm2[0],
                &xu, &yu, &zu, &xa, &ya, &za, &xh, &yh, &zh,
                &xm, &ym, &zm );

    /* To Chop B/C tracking frame. */
        PartAv ( s_frame[ichop], xm, ym, zm,
                 s_otm2_i[ichop], -sst, cst, s_otm1_i[ichop],
                 &xh, &yh, &zh, &xa, &ya, &za,
                 &xu, &yu, &zu );
        a = atan2 ( yu, s_frame[ichop] == AZEL_TOPO ? -xu : xu );
        b = atan2 ( zu, sqrt ( xu * xu + yu * yu ) );

    /* Apply the required offset-from-base. */
        s_tar_ob[ichop][0] = slaDrange(a - s_tar_pc[ichop][0] + 
                                       s_tar_ob[ichop][0]);
        s_tar_ob[ichop][1] = b - s_tar_pc[ichop][1] + s_tar_ob[ichop][1];

    }

/*
** Nod the pointing-origins
** ------------------------
*/

/* X then Y. */
    for (ixy = 0; ixy < 2; ixy++) {

    /* X or Y component of the offset from the "star in" */
    /* pointing-origin to the one for chop state A.      */
        w = s_por_p0[nod][ixy] - s_por_p0[0][ixy];

    /* Apply the offset component to all three chop states. */
        for (ichop = 0; ichop < 3; ichop++) {
            s_por_ob[ichop][ixy] = w;
        }
    }

/* Arm the catchup flags. */
    if ( f2_sc < 0 ) f2_sc *= -1;

/* Generate a new track identifier. */
    timeNow(&trackid);

    epicsMutexLock(TcsSemId);
    for ( ichop = 0; ichop < 3; ichop++) {
        for ( ixy = 0; ixy < 2; ixy++) {
            S_tar_ob[ichop][NODOB][ixy] = s_tar_ob[ichop][ixy];
            S_por_ob[ichop][NODOB][ixy] = s_por_ob[ichop][ixy];
        }
    }
    F2_sc = f2_sc;
    Trackid = trackid;
    Nod = nod;
    epicsMutexUnlock(TcsSemId);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsLimitTimes
 *
 *   Purpose:
 *   Computes times to various limits.
 *
 *   Description:
 *   The times to reach the elevation, airmass, azimuth wrap, rotator
 *   wrap and zenith blind spot are computed and written to the output
 *   links. A mask to indicate which limits are active (i.e. are liable
 *   to be reached and have valid times) is written to VALA and the
 *   invalid limits are set to -999.0.
 *
 *   Invocation:
 *   tcsLimitTimes(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   EPICS inputs :
 *
 *   a => Elevation limit (radians)
 *   b => Air mass limit
 *   c => High azimuth wrap limit (radians)
 *   d => Low azimuth wrap limit (radians)
 *   e => High rotator wrap limit (radians)
 *   f => Low rotator wrap limit (radians)
 *   g => Zenith at risk region size (radians)
 *   h => Turn on and off some diagnostics
 *
 *   EPICS outputs :
 *
 *   vala => Limit mask
 *   valb => Time to elevation limit
 *   valc => Time to air mass limit
 *   vald => Time to azimuth wrap limit
 *   vale => Time to rotator wrap limit
 *   valf => Time to zenith at risk region entry
 *   valg => Time to zenith at risk region exit
 *   valh => Elevation of air mass limit
 *   vali => P1 rotary table limit
 *   valj => P2 rotary table limit
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   External functions:
 *   tcsLimAzel2Hadec (tcsLimits)      Converts Az/El to HA/Dec
 *   tcsLimEl         (tcsLimits)      Computs time to elevation limit
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *   (>)   Tlat      (double)    observatory true latitude
 *   (>)   St        (double)    sidereal time
 *   (>)   Clat      (double)    cosine of latitude
 *   (>)   Slat      (double)    sine of latitude
 *   (>)   M_cosys   (FRAMETYPE) mount tracking frame
 *   (>)   M_tar_p   (double[])  mount target
 *   (>)   R_cosys   (FRAMETYPE  rotator tracking frame
 *   (>)   Ipa       (double)    instrument position angle
 *   (>)   Iaa       (double)    instrument alignment angle
 *   (>)   AzDef     (double)    current azimuth demand
 *   (>)   RmaDef    (double)    current rotator demand
 *
 *   Prior requirements:
 *   The TCS global database must have been initialized
 *
 *   Deficiencies:
 *   The effects of refraction are ignored.
 *
 *-
 */
/* *INDENT-ON* */

/* Sidereal radians to SI minutes */
#define ST2MIN (1.0 / UTST / S2R / 60.0)

long tcsLimitTimes(struct genSubRecord *pgsub)
{

/* Local copies of global variables */
    double tlat, clat, slat, ra, dec, curaz, curpa, ipa, iaa, st;
    FRAMETYPE m_frame, r_frame;

    long mask = 0;
    double pa, ha, az, rma, cdec, sdec, cha, sha;
    double ellim, amlim, azlolim, azhilim, rotlolim, rothilim, zlim;
    double sinEl, amel, curha, azhalo[2], azhahi[2], azttl=0.0;
    double rothalo[2], rothahi[2], rotttl=0.0;
    double p1ttl=0.0;                /* P1 time-to-limit (sidereal rad, *ST2MIN → min) */
    double p2ttl=0.0;                /* P2 time-to-limit (sidereal rad, *ST2MIN → min) */
    double x, y, a, r;
    double sqsz, cqsz;
    int i, j;
    int azlocount, azhicount, azhidone[2], azlodone[2], azvalid;
    int rotlocount, rothicount, rothidone[2], rotlodone[2], rotvalid;
    int p1valid;                     /* 1 = P1 limit reached in 24 h, 0 = no hit */
    int p2valid;                     /* 1 = P2 limit reached in 24 h, 0 = no hit */
    long p1Following, p2Following ;  /* probe following-mode flags (from tcsProbeLib) */
    double p1RTPosn, p2RTPosn ;      /* current rotary-table positions (degs)         */
    double p1RTHiLim, p1RTLoLim, p2RTHiLim, p2RTLoLim;  /* hw limits (degs)           */
    double pa0 ;                     /* current parallactic angle (rads)              */
    /* Variables removed in REL-4620 fix:
     *   dRTHiLim, dRTLoLim   — offsets passed to old tcsLimPa() call
     *   p1RT, p2RT           — accumulated-with-bug projected positions
     *   panew                — PA at each simulation step
     * All of the above are now local to the per-probe integration block. */
    long debug ;                     /* diagnostic-print enable (pgsub->h)           */
    static int dbgLevel = DBG_NONE;  /* debug level                                  */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsLimitTimes: Semaphore not created");
        return 0;
    }

/* Copy items from global database. */
    epicsMutexLock(TcsSemId);
    tlat = Tlat;
    clat = Clat;
    slat = Slat;
    st = St;
    ra = M_tar_p[0];
    dec = M_tar_p[1];
    m_frame = M_frame;
    r_frame = R_frame;
    ipa = Ipa;
    iaa = Iaa;
    curaz = AzDef;
    curpa = RmaDef;
    epicsMutexUnlock(TcsSemId);

/*  Fetch debug flag */
    debug = *(long *)pgsub->h ;

/* Set the valid flags */
    azvalid = rotvalid = 0;
    p1valid = p2valid = 0;

/* If sidereal tracking just do the airmass limit elevation. */
    if ( m_frame == AZEL_TOPO ) {
        if (debug) printf ("tcsLimitTimes: mount frame is AZEL_TOPO\n");
        amlim = *(double*)pgsub->b;
        amlim = amlim > 1.0 ? amlim : 1.0;
        sinEl = 0.9981833 / (amlim - 0.0018167) ;
        amel = asin(sinEl);
    } else {

        if (debug) printf ("tcsLimitTimes: mount frame is not AZEL_TOPO\n");
    /* Fetch current limits from EPICS links. */
        ellim = *(double*)pgsub->a;
        amlim = *(double*)pgsub->b;
        azhilim = *(double*)pgsub->c;
        azlolim = *(double*)pgsub->d;
        rothilim = *(double*)pgsub->e;
        rotlolim = *(double*)pgsub->f;
        zlim = *(double*)pgsub->g;

    /* Current hour angle and functions of declination. */
        curha = slaDrange(st - ra);
        cdec = cos( dec );
        sdec = sin( dec );

    /* Elevation limit. */
        if ( tcsLimEl( cdec, sdec, ellim, clat, slat, &ha) == 0 ) {
           *(double*)pgsub->valb = ( ha - curha ) * ST2MIN;
           mask |= 0x1;
        }

    /* Air mass limit. */
        amlim = amlim > 1.0 ? amlim : 1.0;
        sinEl = 0.9981833 / (amlim - 0.0018167) ;
        amel = asin(sinEl);

        if ( tcsLimEl( cdec, sdec, amel, clat, slat, &ha) == 0 ) {
           *(double*)pgsub->valc = ( ha - curha ) * ST2MIN;
           mask |= 0x2;
        }

    /* Azimuth and rotator wrap limits. */

    /* Hour angles at which azimuth limits are reached. */
        azlocount = tcsLimAz( cdec, sdec, azlolim,  clat, slat, azhalo);
        azhicount = tcsLimAz( cdec, sdec, azhilim,  clat, slat, azhahi);
        if (debug) {
          printf("tcsLimitTimes: Az lower limit HA's (mins): %f %f\n", 
                  azhalo[0]*ST2MIN, azhalo[1]*ST2MIN);
          printf("tcsLimitTimes: Az upper limit HA's (mins): %f %f\n", 
                  azhahi[0]*ST2MIN, azhahi[1]*ST2MIN);
        }

    /* Hour angles at which rotator limits (adjusted for the desired
       rotator angle) are reached. */
        pa =  PI - rotlolim + ipa - iaa;
        rotlocount = tcsLimPa( cdec, sdec, pa, clat, slat, rothalo);
        pa =  PI - rothilim + ipa - iaa;
        rothicount = tcsLimPa( cdec, sdec, pa, clat, slat, rothahi);
        if (debug) {
          printf("tcsLimitTimes: CR lower limit HA's (mins): %f %f\n", 
                  rothalo[0]*ST2MIN, rothalo[1]*ST2MIN);
          printf("tcsLimitTimes: CR upper limit HA's (mins): %f %f\n", 
                  rothahi[0]*ST2MIN, rothalo[1]*ST2MIN);
        }

    /* Hour angles at which P1 & P2 reach their limits if the rotator frame
     * is azel and the probes are tracking
     */
       tcsProbeGetFollowFlag(0, &p1Following);
       tcsProbeGetFollowFlag(1, &p2Following);
       tcsProbeGetRTPosns( &p1RTPosn, &p2RTPosn) ;
       tcsProbeGetRTLimits(&p1RTLoLim, &p1RTHiLim, &p2RTLoLim, &p2RTHiLim);
       if (debug) {
         printf("tcsLimitTimes: p1RTPosn = %f p2RTPosn = %f\n", p1RTPosn,
                 p2RTPosn);
         printf("tcsLimitTimes: p1RTHiLim = %f p1RTLoLim = %f\n", p1RTHiLim,
                 p1RTLoLim);
         printf("tcsLimitTimes: p2RTHiLim = %f p2RTLoLim = %f\n", p2RTHiLim,
                 p2RTLoLim);
       }
  
       pa0 = slaPa (curha, dec, tlat);
       if (debug) 
         printf("tcsLimitTimes: pa0 = %f\n", pa0*R2D);

    /* ============================================================
     * P1/P2 ROTARY TABLE TIME-TO-LIMIT  (REL-4620 fix)
     * ============================================================
     *
     * !!! STATUS 2026-04-24: NOT READY FOR PRODUCTION !!!
     *   On-sky validation showed two problems:
     *     (1) 5° step size gave 20-min granularity floor — fixed by
     *         reducing step to 0.25° (1 sidereal minute).
     *     (2) The 1:1 PA-to-probe-rotation accumulation below is
     *         WRONG.  Engineering-archive replay (2026-04-05 22:00
     *         UT MAROON-X) showed the probe's rotary table moves
     *         about 2.4× faster than the parallactic angle.  The
     *         scale factor depends on AG inverse-kinematics
     *         geometry (guide-star x,y on focal plane and probe
     *         arm angle).  This MUST be fixed before deployment.
     *   See `rel-4620.md` Section 13 for evidence and next steps.
     *
     * WHAT THIS COMPUTES
     *   How many minutes until the P1 or P2 guide probe's rotary
     *   table reaches its mechanical limit (hi or lo), assuming
     *   the telescope keeps tracking the current target.
     *
     *   The result is written to pgsub->vali (P1) / valj (P2) in
     *   minutes, and is displayed as a countdown on the TSD.
     *
     * WHY THE PROBE ROTATES
     *   When the mount frame is AZEL_TOPO (a.k.a. "fixed CRCS"),
     *   the Cass rotator is NOT compensating for field rotation.
     *   To keep a guide star fixed on the probe, the probe's
     *   rotary table has to rotate at the same rate the sky
     *   rotates over the telescope — which equals the rate of
     *   change of the parallactic angle (PA).
     *
     *   PA is the angle between "up" on the sky (toward the
     *   celestial pole) and "up" in the telescope (toward zenith).
     *   As a target moves across the sky its PA changes; the
     *   probe tracks by accumulating that change.
     *
     * METHOD: FORWARD INTEGRATION
     *   Starting from the current state (HA, probe position, PA),
     *   step the hour angle forward in small (0.25°) increments.
     *   At each step:
     *     1. Compute the new parallactic angle.
     *     2. Add its change to a running rotation total.
     *     3. Project where the probe would be.
     *     4. If the projected position crosses a limit, stop —
     *        that step's elapsed HA is the time-to-limit.
     *
     * WHY THIS REPLACED THE OLD CODE
     *   The old algorithm (lines 12928-12929 pre-fix) stepped
     *   HA forward in 90° chunks and accumulated PA changes via
     *   slaDrange(panew - pa).  Over a 90° HA step the PA can
     *   change so much that slaDrange's ±180° wrap produces a
     *   huge cumulative error in the projected probe position.
     *   Combined with a "180° proximity" sanity check, this
     *   produced chaotic output: VALJ jumped hundreds of minutes
     *   between 50 ms updates with constant inputs (REL-4620,
     *   GNFR-73941, GNFR-74131, GNFR-74132, GNFR-72665,
     *   GNFR-72825).
     *
     *   With 0.25° HA steps the per-step PA change is small
     *   (a fraction of a degree to a few degrees anywhere except
     *   near the zenith), so slaDrange never crosses its wrap
     *   boundary and the integration is smooth and stable.
     *
     * COMPUTATIONAL COST
     *   1440 iterations of one slaPa() call each — about 1.4 ms
     *   total per invocation, ~3% of the 50 ms update budget.
     *
     * PARAMETERS
     *   P12_HA_STEP   0.25° in radians, i.e. exactly 1 sidereal
     *                 minute of hour angle.  This is the countdown
     *                 quantization: the reported time-to-limit is
     *                 a multiple of 1 minute.  Small enough that
     *                 PA never jumps by more than a few degrees
     *                 per step, so slaDrange cannot wrap.
     *   P12_N_STEPS   1440, i.e. 0.25° × 1440 = 360° = 24 sidereal
     *                 hr, a full rotation of the sky.  If the
     *                 probe doesn't hit a limit in 24 h, the output
     *                 is marked invalid (-999 to the TSD).
     *
     * NOTE ON EARLIER REVISION
     *   An earlier version of this code used P12_HA_STEP = 5°, which
     *   is 20 sidereal minutes, not 20 seconds as originally commented.
     *   That gave a 20-minute granularity floor: the countdown could
     *   only be reported in 20-minute chunks (20, 40, 60, ...) and
     *   could never report less than 20 minutes even when the probe
     *   was physically seconds from the limit.  The current 0.25°
     *   step gives 1-minute granularity, which matches the TSD's
     *   display precision.
     * ============================================================ */
#define P12_HA_STEP  (0.25 * D2R)                /* 0.25° = 1 sidereal minute */
#define P12_N_STEPS  ((int)(PI2 / P12_HA_STEP))  /* 1440 steps = full circle = 24h */

       /* ---------------- P1 (PWFS-1) ---------------- */
       if (r_frame == AZEL_TOPO && p1Following) {
         /* Local loop variables kept local to avoid contaminating
          * the outer function's state. */
         double p1ha;      /* projected hour angle at this step (rad)       */
         double p1panew;   /* parallactic angle at p1ha (rad)               */
         double p1paLast;  /* PA at previous step — seed from current pa0  */
         double p1rot;     /* total accumulated probe rotation (deg)        */
         double p1pos;     /* projected probe position (deg)                */

         if (debug)
           printf ("tcsLimitTimes: P1 forward integration "
                   "(AZEL_TOPO, following)\n");

         /* Seed from the current state. */
         p1paLast = pa0;
         p1rot    = 0.0;

         for ( i = 0; i < P12_N_STEPS; i++ ) {
             /* Advance HA by one small step. */
             p1ha    = curha + (i + 1) * P12_HA_STEP;

             /* New PA at the projected HA. */
             p1panew = slaPa(p1ha, dec, tlat);

             /* Add the incremental PA change to our running total.
              * slaDrange keeps a single-step difference inside
              * (-180°, +180°) to handle the HA=±180° wrap gracefully.
              * Because p1ha advances by only 0.25° at a time, this
              * difference is always small and safe. */
             p1rot   += slaDrange(p1panew - p1paLast) * R2D;
             p1paLast = p1panew;

             /* Probe position = starting position + accumulated rotation. */
             p1pos    = p1RTPosn + p1rot;

             if (debug && (i % 12 == 0))
               printf("tcsLimitTimes: P1 step %d ha=%f pos=%f rot=%f\n",
                      i, p1ha*ST2MIN, p1pos, p1rot);

             /* LOW LIMIT crossing: probe rotated far enough CCW
              * to hit p1RTLoLim.  Record time-to-limit and stop. */
             if ( p1pos <= p1RTLoLim ) {
                 p1ttl   = (i + 1) * P12_HA_STEP;   /* elapsed HA (rad) */
                 p1valid = 1;
                 if (debug)
                   printf("tcsLimitTimes: P1 hits lo limit at step %d, "
                          "ttl = %f mins\n", i, p1ttl*ST2MIN);
                 break;
             }
             /* HIGH LIMIT crossing: probe rotated CW to p1RTHiLim. */
             if ( p1pos >= p1RTHiLim ) {
                 p1ttl   = (i + 1) * P12_HA_STEP;
                 p1valid = 1;
                 if (debug)
                   printf("tcsLimitTimes: P1 hits hi limit at step %d, "
                          "ttl = %f mins\n", i, p1ttl*ST2MIN);
                 break;
             }
         }
         /* If we fell out of the loop without hitting a limit, the
          * probe will not reach either limit in the next 24 h.
          * p1valid stays 0 → -999 ("no limit") will be reported below. */
         if (debug && !p1valid)
           printf("tcsLimitTimes: P1 does not reach a limit in 24h\n");
       }

       /* ---------------- P2 (PWFS-2) ----------------
        * Identical to P1 but operating on the P2 rotary table.
        * P2 is the probe used by MAROON-X in fixed-CRCS mode —
        * this is the path that exhibited the REL-4620 chaos. */
       if (r_frame == AZEL_TOPO && p2Following) {
         double p2ha, p2panew, p2paLast, p2rot, p2pos;

         if (debug)
           printf ("tcsLimitTimes: P2 forward integration "
                   "(AZEL_TOPO, following)\n");

         p2paLast = pa0;
         p2rot    = 0.0;

         for ( i = 0; i < P12_N_STEPS; i++ ) {
             p2ha    = curha + (i + 1) * P12_HA_STEP;
             p2panew = slaPa(p2ha, dec, tlat);
             p2rot  += slaDrange(p2panew - p2paLast) * R2D;
             p2paLast = p2panew;
             p2pos    = p2RTPosn + p2rot;

             if (debug && (i % 12 == 0))
               printf("tcsLimitTimes: P2 step %d ha=%f pos=%f rot=%f\n",
                      i, p2ha*ST2MIN, p2pos, p2rot);

             if ( p2pos <= p2RTLoLim ) {
                 p2ttl   = (i + 1) * P12_HA_STEP;
                 p2valid = 1;
                 if (debug)
                   printf("tcsLimitTimes: P2 hits lo limit at step %d, "
                          "ttl = %f mins\n", i, p2ttl*ST2MIN);
                 break;
             }
             if ( p2pos >= p2RTHiLim ) {
                 p2ttl   = (i + 1) * P12_HA_STEP;
                 p2valid = 1;
                 if (debug)
                   printf("tcsLimitTimes: P2 hits hi limit at step %d, "
                          "ttl = %f mins\n", i, p2ttl*ST2MIN);
                 break;
             }
         }
         if (debug && !p2valid)
           printf("tcsLimitTimes: P2 does not reach a limit in 24h\n");
       }

    /* Adjust limit hour angles to be greater than current. */
        for ( i = 0; i < azlocount; i++ ) {
           if ( azhalo[i] < curha ) azhalo[i] += PI2;
        }
        for ( i = 0; i < azhicount; i++ ) {
           if ( azhahi[i] < curha ) azhahi[i] += PI2;
        }
        for ( i = 0; i < rotlocount; i++ ) {
           if ( rothalo[i] < curha ) rothalo[i] += PI2;
        }
        for ( i = 0; i < rothicount; i++ ) {
           if ( rothahi[i] < curha ) rothahi[i] += PI2;
        }
        /* P1/P2 HA adjustments removed — REL-4620: P1/P2 limits are now
           computed by direct forward integration above, not by tcsLimPa. */
        if (debug) {
          printf("tcsLimitTimes: limits after adjustments\n");
          printf("tcsLimitTimes: current HA (mins) %f\n", curha*ST2MIN);
          printf("tcsLimitTimes: Az lower limit HA's (mins): %f %f\n", 
                  azhalo[0]*ST2MIN, azhalo[1]*ST2MIN);
          printf("tcsLimitTimes: Az upper limit HA's (mins): %f %f\n", 
                  azhahi[0]*ST2MIN, azhahi[1]*ST2MIN);
          printf("tcsLimitTimes: CR lower limit HA's (mins): %f %f\n", 
                  rothalo[0]*ST2MIN, rothalo[1]*ST2MIN);
          printf("tcsLimitTimes: CR upper limit HA's (mins): %f %f\n", 
                  rothahi[0]*ST2MIN, rothahi[1]*ST2MIN);
          /* P1/P2 HA debug removed — REL-4620: computed by forward integration */
        }

    /* Step the azimuth forward in 6 hour increments in order to track
       which azimuth cable wrap the telescope will go to. */
        az = curaz;
        rma = curpa;
        a = slaDrange( curaz );
        r = slaDrange( curpa );
        pa = pa0 ;
        ha = floor(curha/D90) * D90;
        for ( i = 0; i < 2; i++ ) {
            azlodone[i] = azhidone[i] = FALSE;
            rotlodone[i] = rothidone[i] = FALSE;
        }

        for ( i = 0; i < 6; i++)  {
            ha += D90;
            if (debug)
              printf("tcsLimitTimes: %d  ha (mins) = %f\n", i, ha*ST2MIN); 
        /* Azimuth at this hour angle. */
            cha = cos( ha );
            sha = sin( ha );
            x = - cha * cdec * slat + sdec * clat;
            y = - sha * cdec;
            a = ( x == 0.0 && y == 0.0) ? a : atan2( y, x);
            az += slaDrange( a - az);
            if (debug)
              printf("tcsLimitTimes: %d  az (degs) = %f\n", i, az*R2D); 
        /* Is the hour angle greater than any of the limits? */
            for ( j = 0; j < azlocount; j++ ) {
                if ( !azlodone[j] && azhalo[j] <= ha ) {
                    azlodone[j] = TRUE;

            /* Is the azimuth within 90 deg of this limit? */
                    if ( fabs( az - azlolim ) <= PI ) {
                        if ( !azvalid || (azhalo[j] - curha) < azttl ) {
                            azttl = azhalo[j] - curha;
                            azvalid = 1;
                        }
                    }
                }
            }

        /* Repeat for the high limit. */
            for ( j = 0; j < azhicount; j++ ) {
                if ( !azhidone[j] && azhahi[j] <= ha ) {
                    azhidone[j] = TRUE;
                    if ( fabs( az - azhilim ) <= PI ) {
                        if ( !azvalid || (azhahi[j] - curha) < azttl ) {
                            azttl = azhahi[j] - curha;
                            azvalid = 1;
                        }
                    }
                }
            }

        /* Rotator angle at this hour angle. */
            sqsz = clat * sha;
            cqsz = slat * cdec - clat * sdec * cha;
            r = ( sqsz != 0.0 || cqsz != 0.0 ) ? atan2 ( -sqsz, cqsz ) : r;
            r += PI + ( ipa - iaa);
            rma += slaDrange( r - rma);
            if (debug)
              printf("tcsLimitTimes: %d  rma (degs) = %f\n", i, rma*R2D); 

        /* Is the hour angle greater than any of the limits? */
            for ( j = 0; j < rotlocount; j++ ) {
                if ( !rotlodone[j] && rothalo[j] <= ha ) {
                    rotlodone[j] = TRUE;

            /* Is the rotator within 90 deg of this limit? */
                    if ( fabs( rma - rotlolim ) <= PI ) {
                        if ( !rotvalid || (rothalo[j] - curha) < rotttl ) {
                            rotttl = rothalo[j] - curha;
                            rotvalid = 1;
                        }
                    }
                }
            }

        /* Repeat for the high limit. */
            for ( j = 0; j < rothicount; j++ ) {
                if ( !rothidone[j] && rothahi[j] <= ha ) {
                    rothidone[j] = TRUE;
                    if ( fabs( rma - rothilim ) <= PI ) {
                        if ( !rotvalid || (rothahi[j] - curha) < rotttl ) {
                            rotttl = rothahi[j] - curha;
                            rotvalid = 1;
                        }
                    }
                }
            }

        /* P1/P2 parallactic angle accumulation and limit checks removed.
         * REL-4620: P1/P2 limits are now computed by direct forward
         * integration above this loop, eliminating the cumulative
         * slaDrange() error and the 180-degree proximity check. */
        }

    /* Copy azimuth limit to output links. */
        if (azvalid) {
            mask |= 0x4;
            *(double*)pgsub->vald = azttl * ST2MIN;
        } 

    /* Copy rotator limit to output links. */
        if (r_frame!=AZEL_MNT && r_frame != AZEL_TOPO) {
            if (rotvalid) {
                mask |= 0x8;
                *(double*)pgsub->vale = rotttl * ST2MIN;
            }
        } else {
          rotvalid = 0 ;
        }

    /* ---- Write P1 result to VALI.
     *   Units:  p1ttl is in sidereal radians; ST2MIN converts to minutes.
     *   Mask:   bit 0x20 set → "P1 limit time is valid and displayable".
     *   If r_frame isn't AZEL_TOPO or P1 isn't following, we don't write
     *   VALI at all — VALI defaults to -999 via the invalidation pass at
     *   the bottom of this function. */
        if (r_frame == AZEL_TOPO && p1Following) {
          if (debug)
            printf("tcsLimitTimes: CR is AZEL, p1 following %d \n", p1valid);
           if (p1valid) {
              mask |= 0x20 ;
              *(double *)pgsub->vali = p1ttl *ST2MIN;
              if (debug)
                printf("tcsLimitTimes: set vali to %f\n", p1ttl* ST2MIN);
           }
        } else {
          p1valid = 0 ;
        }

    /* ---- Write P2 result to VALJ. Same rules as P1 above. */
        if (r_frame == AZEL_TOPO && p2Following) {
           if (p2valid) {
              mask |= 0x40 ;
              *(double *)pgsub->valj = p2ttl *ST2MIN;
           }
        } else {
         p2valid = 0 ;
        }

    /* Zenith at risk area limits (don't display if we are past the region).
       If the limit isn't relevant also set the times to 1 day to prevent
       spurious alarms getting propagated. The zenith limit region is
       assumed to be a rectangle of aspect ratio 0.7 */
       if ( zlim * 0.7 > fabs( dec - tlat)) {
         *(double*)pgsub->valf = ( - zlim - curha ) * ST2MIN;
         *(double*)pgsub->valg = ( zlim - curha ) * ST2MIN;
       } else {
         *(double *)pgsub->valf = 1440.0;
         *(double *)pgsub->valg = 1440.0;
       }
       if ( zlim * 0.7 > fabs( dec - tlat )  && curha < zlim ) mask |= 0x10;
    }

/* Copy airmass elevation to output link. */
    *(double*)pgsub->valh = amel * R2D;
    
/* Copy mask to output link. */
   *(long*)pgsub->vala = ~mask & 0x7f;
   if (debug) {
     printf ("mask, vala  %lx, %lx\n", mask, *(long *)pgsub->vala);
   }

/* As an experiment, set all the limit times to -999 for the invalid
*  ones
*/
   if (!azvalid) *(double *)pgsub->vald = -999.0;
   if (!rotvalid) *(double *)pgsub->vale = -999.0;
   if (!p1valid) *(double *)pgsub->vali = -999.0;
   if (!p2valid) *(double *)pgsub->valj = -999.0;

   return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSetSadParams
 *
 *   Purpose:
 *   Update target SAD items when planet or orbit commands are given
 *
 *   Description:
 *   The planet and orbit commands are invoked with very different parameters
 *   than the target commands. For example the planet command is just
 *   given the planet name. It is necessary therefore to recreate the 
 *   parameters that would have been set into the SAD by the target commands
 *   for example the RA and Dec. If this is not done then when the SAD is
 *   accessed by the header collection task the values in there would refer
 *   to the last target and not the current planet or solar system body.
 *   This begs the question, why not always update the SAD from here ? The
 *   answer is simply historical. Originally only the target commands 
 *   existed and so it was easy just to update the SAD directly. In time
 *   perhaps all updates will happen from here but at the moment this 
 *   routine is only invoked when a planet or orbit command is issued.
 *
 *   Invocation:
 *   tcsSetSadParams(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   EPICS inputs :
 *   b => Number of virtual telescope
 *
 *   EPICS outputs :
 *   vala => RA (degs) 
 *   valb => Dec (degs) 
 *   valc => Frame 
 *   vald => Equinox 
 *   vale => Epoch 
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *-
 */
/* *INDENT-ON* */

long tcsSetSadParams(struct genSubRecord *pgsub)
{
   long vtnum ;                   /* Virtual telescope number */
   TELESCOPE tel;                 /* Virtual telescope */
   TCBDEFN tcb = CURRENT;         /* TCB to get data from */
   FRAMETYPE frame ;              /* Frame of coordinates */
   struct EPOCH eqx ;             /* Equinox of coords */
   double theta1, theta2 ;        /* Target coords */
   double dtheta1, dtheta2 ;       /* Differential track rates */
   double t0 ;                    /* t0 for differential rates */
   char sframe[8] ;               /* Frame as a string */
   char seqx[MAX_STRING_SIZE];    /* Equinox as a string */
   char sepoch[MAX_STRING_SIZE];  /* Epoch as a string */
   double traw ;                  /* Reference epoch as TAI */
   double ttref ;                 /* Reference epoch as TT */
   double pmRA = 0.0;             /* Proper motion in RA */
   double pmDec = 0.0;            /* Proper motion in Dec */
   double rv = 0.0 ;              /* Radial velocity */
   double parallax = 0.0 ;        /* Parallax */
   

/* Fetch virtual telescope number */
   vtnum = *(long *)pgsub->b ;
   switch (vtnum) {
     case 0:
       tel = MOUNT;
       break ;
     case 1:
       tel = SOURCE_A;
       break ;
     case 2:
       tel = SOURCE_B;
       break ;
     case 3:
       tel = SOURCE_C;
       break ;
     case 4:
       tel = PWFS1;
       break ;
     case 5:
       tel = PWFS2;
       break ;
     case 6:
       tel = OIWFS;
       break;
     case 7:
       tel = G1;
       break;
     case 8:
       tel = G2;
       break ;
     case 9:
       tel = G3;
       break ;
     case 10:
       tel = G4;
       break;
     default:
       tel = SOURCE_A;
   }

/* Fetch the data from the configuration block. Although we could potentially
*  work out the radial velocity we don't and instead set it to zero along
*  with the proper motion and parallax. If this routine is ever to be used
*  to update the SAD when a standard target command is given then we'll
*  have to fetch these items from the configuration block
*  Note we don't have to update the effective wavelength. Setting that
*  is a unique separate command (wavelSourceA) and so only changes when
*  that command is given explicitly.
*/
   tcsConfigGetTrack (tcb, tel, &frame, &eqx, &theta1, &theta2, &dtheta1,
                      &dtheta2, &t0);

/* Reference time as TT and epoch. */
    tcsConfigGetReftime(tcb, &traw);
    timeThenD(traw, TT, &ttref);
    sprintf(sepoch, "%c%f", 'J', slaEpj(ttref));

/* Set default frame to be Apparent and equinox to be blank */
   strcpy(sframe, "APPT");
   strcpy(seqx, "");
   if (frame == FK5) {
     strcpy(sframe, "FK5");
     sprintf(seqx, "%c%f", eqx.type, eqx.year);
   } else if (frame == FK4) {
     strcpy(sframe, "FK4") ;
     sprintf(seqx, "%c%f", eqx.type, eqx.year);
   } else if (frame == AZEL_MNT || frame == AZEL_TOPO) {
     strcpy(sframe, "AzEl");
   }

/* Copy data to output links. */
   *(double *)pgsub->vala = theta1*R2D ;
   *(double *)pgsub->valb = theta2*R2D ;
   strcpy(pgsub->valc, sframe);
   strcpy(pgsub->vald, seqx);
   strcpy(pgsub->vale, sepoch);
   *(double *)pgsub->valf = parallax ;
   *(double *)pgsub->valg = pmRA ;
   *(double *)pgsub->valh = pmDec ;
   *(double *)pgsub->vali = rv ;

   return 0;
}

/*+
 *   Function name:
 *   tcsKernelEnd
 *
 *   Purpose:
 *   Sets the fan out mask that determines the setting of the KernelC and
 *   InPosition flags and writes the kernel data required by the status
 *   display consoles to an output link.`
 *
 *   Description:
 *
 *   Invocation:
 *   tcsKernelEnd(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   EPICS inputs :
 *
 *   EPICS outputs :
 *
 *   vala => Fanout mask
 *   valb => Kernel data for source A
 *   valc => Kernel data for source B
 *   vald => Kernel data for source C
 *   vale => Kernel data for PWFS1
 *   valf => Kernel data for PWFS2
 *   valg => Kernel data for OIWFS 
 *   valh => Current nod beam A, B or C
 *   vali => Whether beam has changed (= 1) or not (= 0)
 *   valk => Kernel data for generic guider 1 
 *   vall => Kernel data for generic guider 2 
 *   valm => Kernel data for generic guider 3 
 *   valn => Kernel data for generic guider 4 
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   External functions:
 *
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long tcsKernelEnd(struct genSubRecord *pgsub)
{

    static char *beams[] = {"A", "B", "C"} ;
    static int prevNod = 9 ;                 /* Set an impossible value */
    static int prevInPosReason = -1 ;        /* Set an impossible value */
/* Local copies of global variables */
    double trackid;
    int inPosition, inPosReason;
    double s_tar_p0[3][2], s_tar_dt[3][2], s_tar_t0[3], s_tar_pc[3][2];
    double s_por_p0[3][2], s_por_pc[3][2];
    double g1_tar_p0[2], g1_tar_dt[2], g1_tar_t0, g1_tar_ob[3][2];
    double g2_tar_p0[2], g2_tar_dt[2], g2_tar_t0, g2_tar_ob[3][2];
    double g3_tar_p0[2], g3_tar_dt[2], g3_tar_t0, g3_tar_ob[3][2];
    double g1_tar_p[2], g2_tar_p[2], g3_tar_p[2];
    double g1_tar_oba[2], g2_tar_oba[2], g3_tar_oba[2];
    double gg1_tar_p0[2], gg1_tar_dt[2], gg1_tar_t0, gg1_tar_ob[3][2];
    double gg2_tar_p0[2], gg2_tar_dt[2], gg2_tar_t0, gg2_tar_ob[3][2];
    double gg3_tar_p0[2], gg3_tar_dt[2], gg3_tar_t0, gg3_tar_ob[3][2];
    double gg4_tar_p0[2], gg4_tar_dt[2], gg4_tar_t0, gg4_tar_ob[3][2];
    double gg1_tar_p[2], gg2_tar_p[2], gg3_tar_p[2], gg4_tar_p[2];
    double gg1_tar_oba[2], gg2_tar_oba[2], gg3_tar_oba[2], gg4_tar_oba[2];
    double tt;
    int c_mode[2];
    int g1_act[3], g2_act[3], g3_act[3], nod;
    int gg1_act[3], gg2_act[3], gg3_act[3], gg4_act[3]; 

    long mask = 0;
    static double lastid = 0.0;
    static int lastIp = 0;
    int i, j;
    double dt;
    double s_tar_p[3][2];
    double *valp[10];
    static int dbgLevel = DBG_NONE; /* debug level */

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsKernelEnd: Semaphore not created");
        return 0;
    }

/* Copy items from global database. */
    epicsMutexLock(TcsSemId);
    trackid = Trackid;
    inPosition = InPosition;
    inPosReason = InPosReason;
    nod = Nod;
    for ( i = 0; i < 3; i++ ) {
       for ( j = 0; j < 2; j++ ) {
          s_tar_p0[i][j] = S_tar_p0[i][j];
          s_tar_dt[i][j] = S_tar_dt[i][j];
          s_tar_pc[i][j] = S_tar_pc[i][j];
          s_por_p0[i][j] = S_por_p0[i][j];
          s_por_pc[i][j] = S_por_pc[i][j];
          g1_tar_ob[i][j] = G1_tar_ob[i][j];
          g2_tar_ob[i][j] = G2_tar_ob[i][j];
          g3_tar_ob[i][j] = G3_tar_ob[i][j];
          gg1_tar_ob[i][j] = GG1_tar_ob[i][j];
          gg2_tar_ob[i][j] = GG2_tar_ob[i][j];
          gg3_tar_ob[i][j] = GG3_tar_ob[i][j];
          gg4_tar_ob[i][j] = GG4_tar_ob[i][j];
       }
       s_tar_t0[i] = S_tar_t0[i];
       g1_act[i] = G1_act[nod][i];
       g2_act[i] = G2_act[nod][i];
       g3_act[i] = G3_act[nod][i];
       gg1_act[i] = GG1_act[nod][i];
       gg2_act[i] = GG2_act[nod][i];
       gg3_act[i] = GG3_act[nod][i];
       gg4_act[i] = GG4_act[nod][i];
    }
    for ( j = 0; j < 2; j++ ) {
       g1_tar_p0[j] = G1_tar_p0[j];
       g2_tar_p0[j] = G2_tar_p0[j];
       g3_tar_p0[j] = G3_tar_p0[j];
       gg1_tar_p0[j] = GG1_tar_p0[j];
       gg2_tar_p0[j] = GG2_tar_p0[j];
       gg3_tar_p0[j] = GG3_tar_p0[j];
       gg4_tar_p0[j] = GG4_tar_p0[j];
       g1_tar_dt[j] = G1_tar_dt[j];
       g2_tar_dt[j] = G2_tar_dt[j];
       g3_tar_dt[j] = G3_tar_dt[j];
       gg1_tar_dt[j] = GG1_tar_dt[j];
       gg2_tar_dt[j] = GG2_tar_dt[j];
       gg3_tar_dt[j] = GG3_tar_dt[j];
       gg4_tar_dt[j] = GG4_tar_dt[j];
    }
    g1_tar_t0 = G1_tar_t0;
    g2_tar_t0 = G2_tar_t0;
    g3_tar_t0 = G3_tar_t0;
    gg1_tar_t0 = GG1_tar_t0;
    gg2_tar_t0 = GG2_tar_t0;
    gg3_tar_t0 = GG3_tar_t0;
    gg4_tar_t0 = GG4_tar_t0;
    tt= Tt;
    c_mode[0] = C_mode[0];
    c_mode[1] = C_mode[1];
    epicsMutexUnlock(TcsSemId);

/* If trackid has changed set mask to set kernelC to IDLE */
    if ( trackid != lastid ) {
       mask += 1;
       lastid = trackid;
    }

/* If the in position flag has changed value set the appropriate bit in
   the mask */
    if ( inPosition != lastIp ) {
       if (inPosition) mask += 2;
       else mask +=4;
       lastIp = inPosition;
    }

/* Set nod bit in mask */
    if (prevNod != nod) {
       mask +=8;
    }
    prevNod = nod ;

/* Set in position reason bit in mask */
    if (prevInPosReason != inPosReason) {
       mask +=16;
    }
    prevInPosReason = inPosReason ;

/* Calculate target positions after application of differential tracking. */
    dt = tt - s_tar_t0[0];
    for ( j = 0; j < 2; j++ )
        s_tar_p[0][j] = s_tar_p0[0][j] + dt * s_tar_dt[0][j];
    for ( i = 1; i < 3; i++ ) {
       if (c_mode[i-1]) {
          for ( j = 0; j < 2; j++ )
              s_tar_p[i][j] = s_tar_p0[0][j];
       } else {
          dt = tt - s_tar_t0[i];
          for ( j = 0; j < 2; j++ )
              s_tar_p[i][j] = s_tar_p0[i][j] + dt * s_tar_dt[i][j];
       }
    }
    dt = tt - g1_tar_t0;
    for ( j = 0; j < 2; j++ )
        g1_tar_p[j] = g1_tar_p0[j] + dt * g1_tar_dt[j];
    dt = tt - g2_tar_t0;
    for ( j = 0; j < 2; j++ )
        g2_tar_p[j] = g2_tar_p0[j] + dt * g2_tar_dt[j];
    dt = tt - g3_tar_t0;
    for ( j = 0; j < 2; j++ )
        g3_tar_p[j] = g3_tar_p0[j] + dt * g3_tar_dt[j];
    dt = tt - gg1_tar_t0;
    for ( j = 0; j < 2; j++ )
        gg1_tar_p[j] = gg1_tar_p0[j] + dt * gg1_tar_dt[j];
    dt = tt - gg2_tar_t0;
    for ( j = 0; j < 2; j++ )
        gg2_tar_p[j] = gg2_tar_p0[j] + dt * gg2_tar_dt[j];
    dt = tt - gg3_tar_t0;
    for ( j = 0; j < 2; j++ )
        gg3_tar_p[j] = gg3_tar_p0[j] + dt * gg3_tar_dt[j];
    dt = tt - gg4_tar_t0;
    for ( j = 0; j < 2; j++ )
        gg4_tar_p[j] = gg4_tar_p0[j] + dt * gg4_tar_dt[j];

/* Pick out the offset from base for the currently active chop state for
   each of the WFSs. */
    for ( j = 0; j < 2; j++ ) {
        g1_tar_oba[j] = 0.0;
        g2_tar_oba[j] = 0.0;
        g3_tar_oba[j] = 0.0;
        gg1_tar_oba[j] = 0.0;
        gg2_tar_oba[j] = 0.0;
        gg3_tar_oba[j] = 0.0;
        gg4_tar_oba[j] = 0.0;
    }
    for ( i = 0; i < 3; i++ ) {
        if ( g1_act[i] ) {
            for ( j = 0; j < 2; j++ ) 
                g1_tar_oba[j] = g1_tar_ob[i][j];
            break;
        }
    }
    for ( i = 0; i < 3; i++ ) {
        if ( g2_act[i] ) {
            for ( j = 0; j < 2; j++ ) 
                g2_tar_oba[j] = g2_tar_ob[i][j];
            break;
        }
    }
    for ( i = 0; i < 3; i++ ) {
        if ( g3_act[i] ) {
            for ( j = 0; j < 2; j++ ) 
                g3_tar_oba[j] = g3_tar_ob[i][j];
            break;
        }
    }
    for ( i = 0; i < 3; i++ ) {
        if ( gg1_act[i] ) {
            for ( j = 0; j < 2; j++ ) 
                gg1_tar_oba[j] = gg1_tar_ob[i][j];
            break;
        }
    }
    for ( i = 0; i < 3; i++ ) {
        if ( gg2_act[i] ) {
            for ( j = 0; j < 2; j++ ) 
                gg2_tar_oba[j] = gg2_tar_ob[i][j];
            break;
        }
    }
    for ( i = 0; i < 3; i++ ) {
        if ( gg3_act[i] ) {
            for ( j = 0; j < 2; j++ ) 
                gg3_tar_oba[j] = gg3_tar_ob[i][j];
            break;
        }
    }
    for ( i = 0; i < 3; i++ ) {
        if ( gg4_act[i] ) {
            for ( j = 0; j < 2; j++ ) 
                gg4_tar_oba[j] = gg4_tar_ob[i][j];
            break;
        }
    }

/* Copy mask to output link. */
    *(long*)pgsub->vala = mask;

/* Copy kernel data to output links. */
    valp[0] = pgsub->valb;
    valp[1] = pgsub->valc;
    valp[2] = pgsub->vald;
    for (i = 0; i < 3; i++) {
       *(valp[i]++) = s_tar_p[i][0];
       *(valp[i]++) = s_tar_p[i][1];
       *(valp[i]++) = s_tar_pc[i][0] - s_tar_p[i][0];
       *(valp[i]++) = s_tar_pc[i][1] - s_tar_p[i][1];
       *(valp[i]++) = s_por_p0[i][0];
       *(valp[i]++) = s_por_p0[i][1];
       *(valp[i]++) = s_por_pc[i][0] - s_por_p0[i][0];
       *(valp[i]++) = s_por_pc[i][1] - s_por_p0[i][1];
    }
    valp[3] = pgsub->vale;
    *(valp[3]++) = g1_tar_p[0];
    *(valp[3]++) = g1_tar_p[1];
    *(valp[3]++) = g1_tar_oba[0];
    *(valp[3]++) = g1_tar_oba[1];
    valp[4] = pgsub->valf;
    *(valp[4]++) = g2_tar_p[0];
    *(valp[4]++) = g2_tar_p[1];
    *(valp[4]++) = g2_tar_oba[0];
    *(valp[4]++) = g2_tar_oba[1];
    valp[5] = pgsub->valg;
    *(valp[5]++) = g3_tar_p[0];
    *(valp[5]++) = g3_tar_p[1];
    *(valp[5]++) = g3_tar_oba[0];
    *(valp[5]++) = g3_tar_oba[1];
    valp[6] = pgsub->valk;
    *(valp[6]++) = gg1_tar_p[0];
    *(valp[6]++) = gg1_tar_p[1];
    *(valp[6]++) = gg1_tar_oba[0];
    *(valp[6]++) = gg1_tar_oba[1];
    valp[7] = pgsub->vall;
    *(valp[7]++) = gg2_tar_p[0];
    *(valp[7]++) = gg2_tar_p[1];
    *(valp[7]++) = gg2_tar_oba[0];
    *(valp[7]++) = gg2_tar_oba[1];
    valp[8] = pgsub->valm;
    *(valp[8]++) = gg3_tar_p[0];
    *(valp[8]++) = gg3_tar_p[1];
    *(valp[8]++) = gg3_tar_oba[0];
    *(valp[8]++) = gg3_tar_oba[1];
    valp[9] = pgsub->valn;
    *(valp[9]++) = gg4_tar_p[0];
    *(valp[9]++) = gg4_tar_p[1];
    *(valp[9]++) = gg4_tar_oba[0];
    *(valp[9]++) = gg4_tar_oba[1];

    strcpy (pgsub->valh, beams[nod]) ;

/* Write in position reason. */
    strcpy (pgsub->vali, iprreasons[inPosReason]);

   return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsKernelStatus
 *
 *   Purpose:
 *   Output general kernel status that is useful to the EPICS system
 *
 *   Description:
 *
 *   Invocation:
 *   tcsKernelStatus(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   EPICS inputs :
 *
 *   EPICS outputs :
 *
 *   vala => nod A / chop A flag
 *   valb => nod A / chop B flag
 *   valc => nod B / chop A flag
 *   vald => nod B / chop B flag
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *
 *-
 */
/* *INDENT-ON* */

long tcsKernelStatus(struct genSubRecord *pgsub)
{
    int i, j ;                         /* loop indices */
    static int dbgLevel = DBG_NONE; /* debug level */

/* Local copies of global variables */
    long g1_act[3][3], g2_act[3][3], g3_act[3][3];
    
    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsKernelStatus: Semaphore not created");
        return 0;
    }

/* Copy items from global database. */
    epicsMutexLock(TcsSemId);
       for (i = 0; i < 3; i++) {
         for (j = 0; j < 3; j++) {
           g1_act[i][j] = G1_act[i][j];
           g2_act[i][j] = G2_act[i][j];
           g3_act[i][j] = G3_act[i][j];
         }
       }
    epicsMutexUnlock(TcsSemId);

/* Copy kernel data to output links. */
   *(long *)pgsub->vala = g1_act[0][0] ;
   *(long *)pgsub->valb = g1_act[0][1] ;
   *(long *)pgsub->valc = g1_act[1][0] ;
   *(long *)pgsub->vald = g1_act[1][1] ;
   *(long *)pgsub->vale = g2_act[0][0] ;
   *(long *)pgsub->valf = g2_act[0][1] ;
   *(long *)pgsub->valg = g2_act[1][0] ;
   *(long *)pgsub->valh = g2_act[1][1] ;
   *(long *)pgsub->vali = g3_act[0][0] ;
   *(long *)pgsub->valj = g3_act[0][1] ;
   *(long *)pgsub->valk = g3_act[1][0] ;
   *(long *)pgsub->vall = g3_act[1][1] ;

   return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsKernelGGStatus
 *
 *   Purpose:
 *   Output generic guider kernel status that is useful to the EPICS system
 *
 *   Description:
 *
 *   Invocation:
 *   tcsKernelGGStatus(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   EPICS inputs :
 *
 *   EPICS outputs :
 *
 *   vala => nod A / chop A flag GG1
 *   valb => nod A / chop B flag GG1
 *   valc => nod B / chop A flag GG1
 *   vald => nod B / chop B flag GG1
 *   vale => nod A / chop A flag GG2
 *   valf => nod A / chop B flag GG2
 *   valg => nod B / chop A flag GG2
 *   valh => nod B / chop B flag GG2
 *   vali => nod A / chop A flag GG3
 *   valj => nod A / chop B flag GG3
 *   valk => nod B / chop A flag GG3
 *   vall => nod B / chop B flag GG4
 *   valm => nod A / chop A flag GG4
 *   valn => nod A / chop B flag GG4
 *   valo => nod B / chop A flag GG4
 *   valp => nod B / chop B flag GG4
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   External variables:
 *   (>)   TcsSemId  (int)       global memory protection semaphore
 *
 *-
 */
/* *INDENT-ON* */

long tcsKernelGGStatus(struct genSubRecord *pgsub)
{
    int i, j ;                         /* loop indices */
    static int dbgLevel = DBG_NONE; /* debug level */

/* Local copies of global variables */
    long gg1_act[3][3], gg2_act[3][3], gg3_act[3][3], gg4_act[3][3];

    if (!TcsSemId) {
        DBGMSG (DBG_NONE, "tcsKernelGGStatus: Semaphore not created");
        return 0;
    }

/* Copy items from global database. */
    epicsMutexLock(TcsSemId);
       for (i = 0; i < 3; i++) {
         for (j = 0; j < 3; j++) {
           gg1_act[i][j] = GG1_act[i][j];
           gg2_act[i][j] = GG2_act[i][j];
           gg3_act[i][j] = GG3_act[i][j];
           gg4_act[i][j] = GG4_act[i][j];
         }
       }
    epicsMutexUnlock(TcsSemId);

/* Copy kernel data to output links. */
   *(long *)pgsub->vala = gg1_act[0][0] ;
   *(long *)pgsub->valb = gg1_act[0][1] ;
   *(long *)pgsub->valc = gg1_act[1][0] ;
   *(long *)pgsub->vald = gg1_act[1][1] ;
   *(long *)pgsub->vale = gg2_act[0][0] ;
   *(long *)pgsub->valf = gg2_act[0][1] ;
   *(long *)pgsub->valg = gg2_act[1][0] ;
   *(long *)pgsub->valh = gg2_act[1][1] ;
   *(long *)pgsub->vali = gg3_act[0][0] ;
   *(long *)pgsub->valj = gg3_act[0][1] ;
   *(long *)pgsub->valk = gg3_act[1][0] ;
   *(long *)pgsub->vall = gg3_act[1][1] ;
   *(long *)pgsub->valm = gg4_act[0][0] ;
   *(long *)pgsub->valn = gg4_act[0][1] ;
   *(long *)pgsub->valo = gg4_act[1][0] ;
   *(long *)pgsub->valp = gg4_act[1][1] ;

   return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsTestOffLoad
 *
 *   Purpose:
 *   Check if data from SCS is valid
 *
 *   Description:
 *   The SCS provides a smoothed version of the tip/tilt demand it sends
 *   to the M2 hardware to the TCS so that the TCS can adjust the mount
 *   and so bring the mean tip/tilt demand to zero. If the SCS is flagged
 *   by the WFS that the data it is receiving is not valid then the SCS
 *   stops updating this smoothed signal. This routine checks that
 *   successive values read from the SCS are updating and if not substitutes
 *   a 0 for the demand. This zero is then sent to the input to the TCS
 *   integrator rather than the fixed value to prevent the mount being 
 *   driven off target.
 *
 *   Invocation:
 *   tcsTestOffLoad(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   EPICS inputs :
 *
 *   a => index, 0 = ca data, 1 = ce data
 *   b => xTiltGuide from SCS
 *   c => yTiltGuide from SCS
 *
 *   EPICS outputs :
 *
 *   vala => ca or ce demand to TCS integrator 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Deficiencies:
 *   Be careful of the static variables. This routine is called from two
 *   locations but never at the same time. The routine is only constructed
 *   this way to fit in with the previous design where it was believed
 *   that the SCS would do this check and put the data to zero. Given time
 *   constraints, it was not possible to rework the capfast schematics 
 *   and instead this routine had to fit in with what was already available.
 *   Since the code for the CA correction is called first, it does all
 *   the calculations when the code is called for CE it simply outputs
 *   the previously computed number.
 *
 *-
 */
/* *INDENT-ON* */

long tcsTestOffLoad(struct genSubRecord *pgsub)
{

#define CAFILT 0

   static double prevSCSCaValue = 0 ;
   static double prevSCSCeValue = 0 ;

   static double outca = 0.0 ;
   static double outce = 0.0;

   double currSCSCaValue ;
   double currSCSCeValue ;
   double dce, dca ;

   if (*(long *)pgsub->a == CAFILT) {

     currSCSCeValue = *(double *)pgsub->b ;
     currSCSCaValue = *(double *)pgsub->c ;

/* Found that it was neccessary to use a tolerance rather than check for
*  equality. Otherwise even though the SCS data wasn't changing, the values
*  read would flicker in the 16th decimal place
*/
     dce = currSCSCeValue - prevSCSCeValue ;
     dca = currSCSCaValue - prevSCSCaValue ;
     if (dca < 0.0) dca = -dca ;
     if (dce < 0.0) dce = -dce ;

     if ((dca < 1.e-6) && (dce < 1.e-6)) {
       outca = 0.0 ;
       outce = 0.0 ;
     } else {
       outca = currSCSCaValue ;
       outce = currSCSCeValue ;
     }

     prevSCSCaValue = currSCSCaValue ;
     prevSCSCeValue = currSCSCeValue ;
     *(double *)pgsub->vala = outca ;

   } else {
     *(double *)pgsub->vala = outce ;
   }

   return 0;
}

/* N.B. for negative declinations you must enter the minutes
*  with a negative sign as well
*/
void tcsTestAst(int ra, int decd, int decm)
{
  int status ;
  double rarads , decrads ;
  FRAMETYPE cosys ;
  struct EPOCH  equinox ;
  double wavelength ;
  int ichop ;
  double x,y ;
  struct WCS_CTX ctx ;

  cosys = FK5 ;
  equinox.type = 'J' ;
  equinox.year = 2000.0 ;
  wavelength = 0.5 ;
  ichop = 0 ;

  rarads = ra * 15 * D2R ;
  decrads = (decd + decm/60.0) * D2R ;

  printf ("ra = %d (%f)\n", ra, rarads);
  printf ("dec = %d %d (%f)\n", decd, decm, decrads);


  status = astS2xy ( rarads, decrads, cosys, equinox, wavelength, ichop,
                     &x, &y) ;
  if (!status) {
   printf ("x = %f y = %f\n", x, y);
  } else {
   printf ("status = %d\n", status) ;
  }

  status = astGetctx (&ctx) ;
  if (!status) {
   printf ("ab0[0]     %f\n", ctx.ab0[0]) ;
   printf ("ab0[1]     %f\n", ctx.ab0[1]) ;
   printf ("fl         %f\n", ctx.tel.fl);
   printf ("rma        %f\n", ctx.tel.rma);
   printf ("an         %f\n", ctx.tel.an);
   printf ("aw         %f\n", ctx.tel.aw);
   printf ("pnpae      %f\n", ctx.tel.pnpae);
   printf ("ca         %f\n", ctx.tel.ca);
   printf ("ce         %f\n", ctx.tel.ce);
   printf ("pox        %f\n", ctx.tel.pox);
   printf ("poy        %f\n", ctx.tel.poy);
   printf ("aoprms[0]  %f\n", ctx.aoprms[0]);
   printf ("aoprms[1]  %f\n", ctx.aoprms[1]);
   printf ("aoprms[2]  %f\n", ctx.aoprms[2]);
   printf ("aoprms[3]  %f\n", ctx.aoprms[3]);
   printf ("aoprms[4]  %f\n", ctx.aoprms[4]);
   printf ("aoprms[5]  %f\n", ctx.aoprms[5]);
   printf ("aoprms[6]  %f\n", ctx.aoprms[6]);
   printf ("aoprms[7]  %f\n", ctx.aoprms[7]);
   printf ("aoprms[8]  %f\n", ctx.aoprms[8]);
   printf ("aoprms[9]  %f\n", ctx.aoprms[9]);
   printf ("aoprms[10] %f\n", ctx.aoprms[10]);
   printf ("aoprms[11] %f\n", ctx.aoprms[11]);
   printf ("aoprms[12] %f\n", ctx.aoprms[12]);
   printf ("aoprms[13] %f\n", ctx.aoprms[13]);
   printf ("aoprms[14] %f\n", ctx.aoprms[14]);
   printf ("time       %f\n", ctx.time);
   printf ("m2xy[0]    %f %f \n", ctx.m2xy[0][0], ctx.m2xy[0][1]);
   printf ("m2xy[1]    %f %f \n", ctx.m2xy[1][0], ctx.m2xy[1][1]);
   printf ("m2xy[2]    %f %f \n", ctx.m2xy[2][0], ctx.m2xy[2][1]);
  } else {
   printf ("astGetctx: status = %d\n", status) ;
  }
}

epicsRegisterFunction(tcsKernelStatus);
epicsRegisterFunction(tcsModelAdjust);
epicsRegisterFunction(tcsEFastLoop);
epicsRegisterFunction(tcsDriveGG);
epicsRegisterFunction(tcsEMediumLoop);
epicsRegisterFunction(tcsNewConfig);
epicsRegisterFunction(tcsDriveCRS);
epicsRegisterFunction(tcsInitSource);
epicsRegisterFunction(tcsWritePointLog);
epicsRegisterFunction(tcsSlowProcess);
epicsRegisterFunction(tcsLimitTimes);
epicsRegisterFunction(tcsDriveM2S);
epicsRegisterFunction(tcsTelConfig);
epicsRegisterFunction(tcsGetDiffTrack);
epicsRegisterFunction(tcsSecProcess);
epicsRegisterFunction(tcsDriveMCS);
epicsRegisterFunction(tcsTestOffLoad);
epicsRegisterFunction(tcsESolsysLoop);
epicsRegisterFunction(tcsKernelEnd);
epicsRegisterFunction(tcsModel);
epicsRegisterFunction(tcsSetSadParams);
epicsRegisterFunction(tcsDriveAGS);
epicsRegisterFunction(tcsKernelGGStatus);
epicsRegisterFunction(tcsEMedFastLoop);
epicsRegisterFunction(tcsDriveECS);
epicsRegisterFunction(tcsDriveAOS);
epicsRegisterFunction(tcsUpdateAstCtx);
epicsRegisterFunction(tcsNullInit);

static const iocshFuncDef tcsModelInitFuncDef =
         {"tcsModelInit"};
	 
static void tcsModelInitCallFunc(const iocshArgBuf *args)
{
   tcsModelInit();
}

static void registerTcsModelInitCommands(void)
{
      iocshRegister(&tcsModelInitFuncDef, tcsModelInitCallFunc);
}
epicsExportRegistrar(registerTcsModelInitCommands);

static const iocshFuncDef tcsDumpFuncDef =
         {"tcsDump"};
	 
static void tcsDumpCallFunc(const iocshArgBuf *args)
{
   tcsDump();
}

static void registerTcsDumpCommands(void)
{
      iocshRegister(&tcsDumpFuncDef, tcsDumpCallFunc);
}
epicsExportRegistrar(registerTcsDumpCommands);

static const iocshFuncDef tcsGuiderDumpFuncDef =
         {"tcsGuiderDump"};
	 
static void tcsGuiderDumpCallFunc(const iocshArgBuf *args)
{
   tcsGuiderDump();
}

static void registerTcsGuiderDumpCommands(void)
{
      iocshRegister(&tcsGuiderDumpFuncDef, tcsGuiderDumpCallFunc);
}
epicsExportRegistrar(registerTcsGuiderDumpCommands);

static const iocshFuncDef tcsDumpWcsFuncDef =
         {"tcsDumpWcs"};
	 
static void tcsDumpWcsCallFunc(const iocshArgBuf *args)
{
   tcsDumpWcs();
}

static void registerTcsDumpWcsCommands(void)
{
      iocshRegister(&tcsDumpWcsFuncDef, tcsDumpWcsCallFunc);
}
epicsExportRegistrar(registerTcsDumpWcsCommands);

epicsExportAddress(int, cnt01 );
epicsExportAddress(int, cnt02 );
epicsExportAddress(int, cnt03 );
epicsExportAddress(int, cnt04 );
epicsExportAddress(int, cnt05 );
epicsExportAddress(int, cnt06 );
epicsExportAddress(int, cnt07 );
epicsExportAddress(int, cnt08 );
epicsExportAddress(int, cnt09 );
epicsExportAddress(int, cnt10 );
epicsExportAddress(int, cnt11 );
epicsExportAddress(int, cnt12 );
epicsExportAddress(int, cnt13 );
epicsExportAddress(int, cnt14 );
epicsExportAddress(double, tick0v);
epicsExportAddress(double, dtickv);
