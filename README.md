git clone https://github.com/develone/zipcpu-dwt-lifting

cd zipcpu-dwt-lifting/src

./buildpi_lift.sh 

line 183 in lifting.c const int	LVLS = 3; the number of lvls/

The executable in cd zipcpu-dwt-lifting/host following 
./buildpi_lift.sh step. 
/* First parameter is used to tell the program which sub band to use 
 * 0 Red
 * 1 Green
 * 2 Blue
 * 2nd parameter is used to tell the program to compute the fwd lifting step only or fwd lifting then inv lifting step
 * 0 fwd lifting then inv lifting step
 * 1 fwd lifting step only
 * ./pi_jpeg 0 1 or ./pi_jpeg 0 0
 * ./pi_jpeg 1 1 or ./pi_jpeg 1 0
 * ./pi_jpeg 2 1 or ./pi_jpeg 2 0
 */