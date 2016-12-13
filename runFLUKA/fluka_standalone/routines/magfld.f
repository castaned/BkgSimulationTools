*$ CREATE MAGFLD.FOR
*COPY MAGFLD
*
*===magfld=============================================================*
*
      SUBROUTINE MAGFLD ( X, Y, Z, BTX, BTY, BTZ, B, NREG, IDISC )        
c===========================================================================
c     magfld                                            MH 4.10.96 CERN/PPE
c
c     magnetic field routine for the 00080 maps from Dick Loveless
c===========================================================================      
      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
      INCLUDE '(LTCLCM)'
      

*                                                                      *
*     Input variables:                                                 *
*            x,y,z = current position                                  *
*            nreg  = current region                                    *
*     Output variables:                                                *
*            btx,bty,btz = cosines of the magn. field vector           *
*            B = magnetic field intensity (Tesla)                      *
*            idisc = set to 1 if the particle has to be discarded      *
*                                                                      *
      parameter (nrmap=180,nzmap=320)
      common /cmsmap/ drmap,dzmap,rminma,zminma,
     & rmaxma,zmaxma,br(nrmap,nzmap),bz(nrmap,nzmap),btot(nrmap,nzmap)
      LOGICAL LFIRST
      SAVE LFIRST
      DATA LFIRST /.TRUE./
      IF (LFIRST) THEN
         write(*,*) 'This is magfld.f'
         LFIRST = .FALSE.
c         open(87,file='../magfld.out')
      ENDIF
      b=0.0d0
      IDISC = 0
c     field for Q1 magnet
      if (abs(z).gt.2280.d0) then
        rr2=x*x+y*y
        if (rr2.lt.324.d0) call lbqfld(X,Y,Z,BTX,BTY,BTZ,B,NREG,IDISC)
        goto 111
      endif        
      rr=sqrt(x*x+y*y)
      if (rr.le.0.d0) rr=1.0d-10
      if (rr.ge.rmaxma.or.abs(z).ge.zmaxma) goto 111
c     now start the real work on the map
c     get the r-cell we are in
      nrcell=int((rr-rminma)/drmap)+1     
c     get the z-cell we are in
      nzcell=int((abs(z)-zminma)/dzmap)+1 
      if (nzcell.lt.1.or.nzcell.gt.nzmap) goto 111    
      if (nrcell.lt.1.or.nrcell.gt.nrmap) goto 111    
      b=btot(nrcell,nzcell)
c     now take into account if we are in positive or negative half
c     also btz,btx,bty are only direction cosines and b gives magnitude
c !!! Btz doesn't need to be corrected anymore !!!
c     Solenoid field is pointing towards +Z direction
c     MLATTC.eq.1 = - Z
c     MLATTC.eq.0 = + Z
      if (MLATTC.eq.1) THEN
        btz=bz(nrcell,nzcell)/b                                  
        brr=-1.D0*br(nrcell,nzcell)/b
      elseif (MLATTC.eq.0) THEN
        btz=bz(nrcell,nzcell)/b                                  
        brr=br(nrcell,nzcell)/b
      endif
c     renormalize      
      if (dabs(brr).gt.1.d0) brr=1.0d0
c     now take the components
      xn=brr/rr
      btx=xn*x
      bty=xn*y
c
 111  continue  
      call mhcosn(btx,bty,btz)
      if (b.le.1.d-10) then    
        b=-1.d-10
        btx=0.d0
        bty=0.d0
        btz=1.d0
      endif      
c      write(*,*) 'MAGFLD :',x,y,z,b,btx,bty,btz  
      RETURN
      END 
