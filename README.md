# Các lệnh để build 
mở UCRT64
cd /f/Document_Study_At_Ptit/Ptit4/Ky1/HTN/FreeRTOS_LED
make clean
make
st-info --probe
st-flash write main.bin 0x08000000
