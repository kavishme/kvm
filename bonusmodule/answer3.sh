sudo insmod bonusmodule.ko REQUEST=3
sudo rmmod bonusmodule
dmesg | grep "Bonus3"