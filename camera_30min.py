#https://gist.github.com/ethan-nelson/81dade3d3659af5372d0a3dfd3a27b9e codigo original com horarios restritos
#https://stackoverflow.com/questions/10607688/how-to-create-a-file-name-with-the-current-date-time-in-python
#https://www.journaldev.com/23642/python-concatenate-string-and-int#using-operator
#https://howchoo.com/g/zjy0nwviodl/how-to-take-a-picture-with-your-raspberry-pi mostra codigo do preview
#https://picamera.readthedocs.io/en/release-1.12/recipes1.html documentação da biblioteca picamera
#https://stackoverflow.com/questions/10840395/python-loop-delay-without-time-sleep 
#https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/
#https://forum.openoffice.org/en/forum/viewtopic.php?f=20&t=63518 Upload via FTP
#https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/


from picamera import PiCamera
import time
import datetime

camera = PiCamera()

# And run forever
while True:
	camera.start_preview() #para melhorar a qualidade/foco da captura
	time.sleep(2)
	fullname = '/home/pi/Pictures/' + time.strftime("%Y%m%d-%H%M%S") + '.jpg'
	camera.capture(fullname)
	print(fullname)

	time.sleep(60*30)    #delay em segundos
	#break #para nao ficar em loop
