@ECHO OFF

cd Bodies
dir /b /s *png > bodies.txt
echo "BODIES DONE!"

cd ..
cd Auras
dir /b /s *png > auras.txt
echo "AURAS DONE!"

cd ..
cd Cockpits
dir /b /s *png > cockpits.txt
echo "COCKPITS DONE!"

cd ..
cd Left_Wings
dir /b /s *png > left_wings.txt
echo "LEFT WINGS DONE!"

cd ..
cd Right_Wings
dir /b /s *png > right_wings.txt
echo "RIGHT WINGS DONE!"

pause