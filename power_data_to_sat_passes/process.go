#!/bin/bash   
./findpassdata4chan listpowerfiles_Null3_0320 > listpowerfiles_Null3_0320.log
./findpassdata4chan listpowerfiles_Null3_0322 > listpowerfiles_Null3_0322.log
./findpassdata4chan listpowerfiles_Null3_0324 > listpowerfiles_Null3_0324.log
./findpassdata4chan listpowerfiles_Null3_0325 > listpowerfiles_Null3_0325.log

python satpassfiles2maps_null.py Null3_0320 > satpass_Null3_0320.log
python satpassfiles2maps_null.py Null3_0322 > satpass_Null3_0322.log
python satpassfiles2maps_null.py Null3_0324 > satpass_Null3_0324.log
python satpassfiles2maps_null.py Null3_0324 > satpass_Null3_0325.log

