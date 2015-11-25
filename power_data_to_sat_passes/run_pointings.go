#./findpassdata4chan listpowerfiles_E01S00 > listpowerfiles_E01S00.log
#./findpassdata4chan listpowerfiles_E02S00 > listpowerfiles_E02S00.log
#./findpassdata4chan listpowerfiles_E03S00 > listpowerfiles_E03S00.log
#./findpassdata4chan listpowerfiles_W01S00 > listpowerfiles_W01S00.log
#./findpassdata4chan listpowerfiles_W02S00 > listpowerfiles_W02S00.log
./findpassdata4chan listpowerfiles_W03S00 > listpowerfiles_W03S00.log
./findpassdata4chan listpowerfiles_W04S01 > listpowerfiles_W04S01.log


#python satpassfiles2maps.py E01S00 > satpass_E01S00.log
#python satpassfiles2maps.py E02S00 > satpass_E02S00.log
#python satpassfiles2maps.py E03S00 > satpass_E03S00.log
#python satpassfiles2maps.py W01S00 > satpass_W01S00.log
#python satpassfiles2maps.py W02S00 > satpass_W02S00.log
python satpassfiles2maps.py W03S00 > satpass_W03S00.log
python satpassfiles2maps.py W04S01 > satpass_W04S01.log


