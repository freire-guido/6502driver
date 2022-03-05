# Communicate binary file line by line to the specified port.
dasm $1.asm -R -f3 -o$1.bin
stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
od -An -t u1 $1.bin > /dev/ttyACM0