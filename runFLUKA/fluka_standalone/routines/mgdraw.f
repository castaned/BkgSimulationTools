*$ CREATE MGDRAW.FOR
*COPY MGDRAW
*                                                                      *
*=== mgdraw ===========================================================*
*                                                                      *
      SUBROUTINE MGDRAW ( ICODE, MREG )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1990-2006      by        Alfredo Ferrari           *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     MaGnetic field trajectory DRAWing: actually this entry manages   *
*                                        all trajectory dumping for    *
*                                        drawing                       *
*                                                                      *
*     Created on   01 march 1990   by        Alfredo Ferrari           *
*                                              INFN - Milan            *
*     Last change  05-may-06       by        Alfredo Ferrari           *
*                                              INFN - Milan            *
*                                                                      *
*----------------------------------------------------------------------*
*
      INCLUDE '(CASLIM)'
      INCLUDE '(COMPUT)'
      INCLUDE '(SOURCM)'
      INCLUDE '(FHEAVY)'
      INCLUDE '(FLKSTK)'
      INCLUDE '(GENSTK)'
      INCLUDE '(MGDDCM)'
      INCLUDE '(PAPROP)'
      INCLUDE '(QUEMGD)'
      INCLUDE '(SUMCOU)'
      INCLUDE '(TRACKR)'
*
      DIMENSION DTQUEN ( MXTRCK, MAXQMG )
*
      CHARACTER*20 FILNAM
      CHARACTER REGIO1*8, REGIO2*8
      LOGICAL LFCOPE
      SAVE LFCOPE
      DATA LFCOPE / .FALSE. /
      RETURN


*============================================================
      ENTRY BXDRAW ( ICODE, MREG, NEWREG, XSCO, YSCO, ZSCO )
      IF ( .NOT. LFCOPE ) THEN
         LFCOPE = .TRUE.
         FILNAM = CFDRAW
         OPEN ( UNIT = IODRAW, FILE = FILNAM, STATUS = 'NEW', FORM =
     &          'FORMATTED' )
      END IF


      IF (JTRACK.GT.ZERZER) THEN 
        IF (ETRACK.GT.AM(JTRACK)) THEN


            CALL GEOR2N (MREG,REGIO1,IERR)
            CALL GEOR2N (NEWREG,REGIO2,IERR)


         IF (IERR .NE. 0 ) STOP 
     &         "Error in name conversion"
            IF((REGIO1(1:1).EQ.'R').AND.(REGIO2(1:1).EQ.'N')) THEN
	        WRITE( IODRAW,100) NCASE, JTRACK, ETRACK-AM(JTRACK),XSCO,YSCO,
     &           ZSCO,PTRACK,WTRACK,ATRACK, CMTRCK, CXTRCK,CYTRCK,CZTRCK
            ENDIF


	ENDIF      
      END IF  
  100 FORMAT(2i5,11e11.3)
      RETURN
*============================================================



      ENTRY EEDRAW ( ICODE )
      RETURN
      ENTRY ENDRAW ( ICODE, MREG, RULL, XSCO, YSCO, ZSCO )
      RETURN
      ENTRY SODRAW
      RETURN
      ENTRY USDRAW ( ICODE, MREG, XSCO, YSCO, ZSCO )
      RETURN
*=== End of subrutine Mgdraw ==========================================*
      END

