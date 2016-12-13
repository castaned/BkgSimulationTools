      SUBROUTINE lbqfin
************************************************************************        
*  Reads in a Poisson field-map for LHC quadrupoles                    *        
*  Cleaned up by G.R.Stevenson, RP Group, CERN                         *        
*  19th August 1992                                                    *        
*  modified for CMS use by Mika Huhtinen, CERN, 16.10.96
************************************************************************        
* Choose one of the following declarations                                      
      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*                                                                               
*  FMPX contains the field matrix B(IX,IY,IXY) on a point mesh                  
*  starting at (0,0) and of mesh size DXBMAP in x and DYBMAP in Y.              
*  x and y coordinates of mesh points in XBMAP and YBMAP                        
*  IX, IY are the X and Y bins, IXY=1 for BX, IXY=2 for BY                      
*  N.B. The input file only contains field data for the first                   
*  45 degrees of one quadrant.                                  
*
      COMMON/FMPX/BXMAP(97,97),BYMAP(97,97),DXBMAP,
     &            DYBMAP
      DIMENSION IB(97)                                                          
      write(*,*) 'This is lbqfin.f'
c    open(87,file='../magfld.out')
c    write(87,*) 'This is magfld.f'
c      CALL OAUXFI('../LBQ-KEK.MAP',98,'OLD',IERR)
      open(98,file='../LBQ-KEK.MAP',status='old')
      rewind(98)
      DXBMAP=0.25D0
      DYBMAP=0.25D0
      do 3 j=1, 97
         do 4 i=1,97
            read(98,*) x,y,BXMAP(i,j),BYMAP(i,j)
 4       continue
 3    continue
      do 5 j=1, 97
         do 6 i=1,97
            BXMAP(i,j)=BXMAP(i,j)/1.1D0
            BYMAP(i,j)=BYMAP(i,j)/1.1D0
 6       continue
 5    continue
      return
      END        
