#!/bin/bash

# -- Config --
echo "Reading configuration..."
source config

# -- Run Setup --
echo "Setup in progress..."
# robot agent: configure recources
DIR=./res/
sed -i 's#\(room_def_path *= *\).*#\1"'$DIR'room_final.dat"#' ./robot_agent/bin/res/config.ini
sed -i 's#\(tags_def_path *= *\).*#\1"'$DIR'tags_final.dat"#' ./robot_agent/bin/res/config.ini

sed -i 's#\(room_def_path *= *\).*#\1"'$DIR'room_final.dat"#' ./robot_agent/res/config.ini
sed -i 's#\(tags_def_path *= *\).*#\1"'$DIR'tags_final.dat"#' ./robot_agent/res/config.ini

# robot agent: configure robot and group port
sed -i "s/\(id *= *\).*/\1$ROBOT_ID/" ./robot_agent/bin/res/config.ini
sed -i "s/\(port *= *\).*/\1$LAB_GROUP_PORT/" ./robot_agent/bin/res/config.ini
sed -i "s/\(id *= *\).*/\1$ROBOT_ID/" ./robot_agent/res/config.ini
sed -i "s/\(port *= *\).*/\1$LAB_GROUP_PORT/" ./robot_agent/res/config.ini


ssh rescue@$ROBOT_IP mkdir /home/rescue/TDDD07
ssh rescue@$ROBOT_IP mkdir /home/rescue/TDDD07/LabGroup$LAB_GROUP

echo $ROBOT_IP

# mission control: configure app
sed -i "s/\(port *= *\).*/\1$LAB_GROUP_PORT/" ./mission_control/res/config.ini

echo "Setup done!"
