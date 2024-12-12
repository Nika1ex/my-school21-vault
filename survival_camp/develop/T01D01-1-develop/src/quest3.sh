cd T01D01-1/src
./ai_door_management_module.sh
chmod +x ./ai_door_management_module.sh
./ai_door_management_module.sh
cp -r door_management_fi door_management_files
cd door_management_files
ls
mkdir door_configuration
mkdir door_map
mkdir door_logs
mv *.conf door_configuration
ls door_configuration
mv *.log door_logs
ls door_logs
mv door_map_1.1 door_map
ls door_map
cd ..
rm -r door_management_fi
./ai_door_management_module.sh
chmod +x ./ai_door_control.sh
./ai_door_management_module.sh



