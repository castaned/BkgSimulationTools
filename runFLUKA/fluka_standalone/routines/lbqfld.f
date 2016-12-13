      SUBROUTINE lbqfld ( XX, YY, ZZ, BTX, BTY, BTZ, B, NREG, IDISC )           
************************************************************************        
*  Subroutine for FLUKA to give the field in Tesla at the point        *        
*  XX,YY,ZZ                                                            *        
*  Set up for the Low-beta Quadrupole with the B-map of the 10T        *        
*  main-ring quadrupole.                                               *        
*  G. R. Stevenson, RP Group, CERN:  19th August 1992                  *        
*  Now includes D1 and D2  - GRS 10th March 1993                       *        
*  Simplified field in whole yoke of dipoles                           *        
************************************************************************        
      include '(DBLPRC)'                                                          
      include '(DIMPAR)'                                                          
      include '(IOUNIT)'                                                          
*                                                                               
*---Uses map of 10 T LHC quadrupole                                             
*  With the FLUKA geometry of x-vertical up, y-horizontal right and             
*  z in the beam direction away from the observer the field map                 
*  is for a horizontally focussing, F, quadrupole                               
*                                                                               
      COMMON/FMPX/BXMAP(97,97),BYMAP(97,97),DXBMAP,DYBMAP
*                                                                               
*  SCF is the scale factor to allow for the fact that the LBQD has an           
*  inner diameter of 70mm whereas the MR quad has an inner diameter             
*  of 56mm.    
*  Q1T and Q3T have inner bore of 85mm => SCFT
*                                                                               
*  The Low-Beta structure differs in sign in an odd or even crossing.           
*  Odd is FDDF while even is DFFD beam for the clockwise proton beam.           
*  N.B. The angle THETA in the SOURCE subroutine must also have the             
*  correct sign ---  Even crossings have positive THETA.                        
*  The direction of the field in D1 must be correctly chosen to deflect         
*  in the same direction as THETA, while D2 has a field of the opposite         
*  sign.                                                                        
*  Set XSING='ODD ' for an odd-numbered intersection,                           
*  Set XSING='EVEN' for an even-numbered intersection,                          
*                                                                               
*            
      BX=0.0D0                                                                  
      BY=0.0D0                                                                  
      BZ=0.0D0                        
      IX=INT(abs(XX)/DXBMAP)+1                                                  
      IY=INT(abs(YY)/DYBMAP)+1             
      if (IX.lt.1.or.IX.gt.97) goto 111    
      if (IY.lt.1.or.IY.gt.97) goto 111
      b=sqrt(BXMAP(IX,IY)**2+BYMAP(IX,IY)**2)
      IF (b.eq.0) b=1.D-10
      btx=BXMAP(IX,IY)/b                                  
      bty=BYMAP(IX,IY)/b
      IF(B.LT.0.99D-10) return                                       
      BTZ=0.0D0                                                              
      IF(XX.LT.0.0D0)BTY=-BTY                                               
      IF(YY.LT.0.0D0)BTX=-BTX                                               
      RETURN
 111  continue  
      call mhcosn(btx,bty,btz)
      if (b.le.1.d-10) then    
        b=-1.d-10
        btx=0.d0
        bty=1.d0
        btz=0.d0
      endif                                                                          
      END                                                                       
*                                                                               
