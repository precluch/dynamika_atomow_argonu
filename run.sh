#!/bin/bash

#make clean
#make
#clear
#echo Teraz robimy wykres V
#root -l -b -q V.C;
#
#echo
#echo
#echo Teraz liczymy test2
#./argon test2 HVT_test2.dat R_test2.dat;
#root -l -b -q 'wyk.C("test2", "HVT_test2.dat")';
#
#echo
#echo
#echo Teraz liczymy test3
#./argon test3 HVT_test3.dat R_test3.dat;
#root -l -b -q 'wyk.C("test3", "HVT_test3.dat")';
#
#echo
#echo
#echo Teraz liczymy test4
#./argon test4 HVT_test4.dat R_test4.dat;
#root -l -b -q 'wyk.C("test4", "HVT_test4.dat")';
#
#echo
#echo
#echo Teraz liczymy test5
#./argon test5 HVT_test5.dat R_test5.dat;
#root -l -b -q 'wyk.C("test5", "HVT_test5.dat")';

echo
echo
echo Teraz liczymy crystal
./argon crystal HVT_crystal.dat R_crystal.dat;
root -l -b -q 'wyk.C("crystal", "HVT_crystal.dat")';

echo
echo
echo Teraz liczymy T50
./argon T50 HVT_T50.dat R_T50.dat;
root -l -b -q 'wyk.C("T50", "HVT_T50.dat")';

echo
echo
echo Teraz liczymy T100
./argon T100 HVT_T100.dat R_T100.dat;
root -l -b -q 'wyk.C("T100", "HVT_T100.dat")';

echo
echo
echo Teraz liczymy T150
./argon T150 HVT_T150.dat R_T150.dat;
root -l -b -q 'wyk.C("T150", "HVT_T150.dat")';

echo
echo
echo Teraz liczymy T200
./argon T200 HVT_T200.dat R_T200.dat;
root -l -b -q 'wyk.C("T200", "HVT_T200.dat")';

echo
echo
echo Teraz liczymy T250
./argon T250 HVT_T250.dat R_T250.dat;
root -l -b -q 'wyk.C("T250", "HVT_T250.dat")';

echo
echo
echo Teraz liczymy T300
./argon T300 HVT_T300.dat R_T300.dat;
root -l -b -q 'wyk.C("T300", "HVT_T300.dat")';

echo
echo
echo Teraz liczymy G500
./argon G500 HVT_G500.dat R_G500.dat;
root -l -b -q 'wyk.C("G500", "HVT_G500.dat")';

echo
echo
echo Teraz liczymy G1000
./argon G1000 HVT_G1000.dat R_G1000.dat;
root -l -b -q 'wyk.C("G1000", "HVT_G1000.dat")';

echo
echo
echo Teraz liczymy G1500
./argon G1500 HVT_G1500.dat R_G1500.dat;
root -l -b -q 'wyk.C("G1500", "HVT_G1500.dat")';

echo
echo
echo Teraz liczymy G2000
./argon G2000 HVT_G2000.dat R_G2000.dat;
root -l -b -q 'wyk.C("G2000", "HVT_G2000.dat")';

echo
echo
echo Teraz liczymy G2500
./argon G2500 HVT_G2500.dat R_G2500.dat;
root -l -b -q 'wyk.C("G2500", "HVT_G2500.dat")';
