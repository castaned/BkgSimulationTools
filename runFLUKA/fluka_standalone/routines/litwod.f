*=== litwod ============================================================        
      SUBROUTINE LITWOD(XX,YY,FOUT,NX,NY,X,Y,F)                                 
************************************************************************        
*  Linearly interpolates a value from a two-dimensional mesh           *        
*  Set up for the Quadrupole B-map                                     *        
*  G. R. Stevenson, RP Group, CERN:  19th August 1992                  *        
************************************************************************        
* Choose one of the following declarations                                      
      include '(DBLPRC)'                                                          
*                                                                               
      DIMENSION X(31),Y(31),F(31,31)                                            
      FOUT=0.0D0                                                             
      IF(XX.LT.X(1).or.yy.lt.y(1)) RETURN                                                                 
      J1=NX-1                                                                   
      DO 10 IX=1,J1                                                             
         IF(XX.LE.X(IX+1)) GO TO 15                                             
   10 CONTINUE                                                                  
      RETURN                                                                    
   15 CONTINUE                                                                  
      J2=NY-1                                                                   
      DO 20 IY=1,J2                                                             
         IF(YY.LE.Y(IY+1)) GO TO 25                                             
   20 CONTINUE                                                                  
      RETURN                                                                    
   25 CONTINUE                                                                  
      F1=F(IX,IY)+(XX-X(IX))*(F(IX+1,IY)-F(IX,IY))/(X(IX+1)-X(IX))              
      F2=F(IX,IY+1)+(XX-X(IX))*                                                 
     1                (F(IX+1,IY+1)-F(IX,IY+1))/(X(IX+1)-X(IX))                 
      FOUT=F1+(YY-Y(IY))*(F2-F1)/(Y(IY+1)-Y(IY))                                
      RETURN                                                                    
      END                                                                       
