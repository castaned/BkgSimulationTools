*$ CREATE USRINI.FOR
*COPY USRINI
*
*=== usrini ===========================================================*
*
      SUBROUTINE USRGLO ( WHAT, SDUM )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
      DIMENSION WHAT (6)
      CHARACTER SDUM*8

      LOGICAL LFIRST
*
      SAVE LFIRST
      DATA LFIRST / .TRUE. /

      NOMORE = 0
*
* initializations
      IF ( LFIRST ) THEN
        CALL lbqfin()
        CALL fieldi()
        LFIRST=.FALSE.
        WRITE(*,*) "Field Maps initialized"
      ENDIF
*
      RETURN
*=== End of subroutine Usrein =========================================*
      END

