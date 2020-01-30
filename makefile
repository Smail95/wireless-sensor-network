# Copy raspberry's directory content  into raspberry
# passwoerd : raspberry
# Browser: peri:8842

NAME = projet_peri
RPI = 22
NUM = 42
TOCOPY = raspberry/*

copy : $(TOCOPY)
	scp -P 2242  $^  pi@peri:$(NAME)
