
# sudo insmod bonusmodule.ko REQUEST=1
# sudo rmmod bonusmodule
# dmesg | grep "Bonus1" >> req1

# sudo insmod bonusmodule.ko REQUEST=2
# sudo rmmod bonusmodule
# dmesg | grep "Bonus2" >> req2

# sudo insmod bonusmodule.ko REQUEST=3
# sudo rmmod bonusmodule
# dmesg | grep "Bonus3" >> req3

# sudo insmod bonusmodule.ko REQUEST=4
# sudo rmmod bonusmodule
# dmesg | grep "Bonus4" >> req4

sudo insmod bonusmodule.ko REQUEST=1
sudo rmmod bonusmodule
dmesg | grep "Bonus1"