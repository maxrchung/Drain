#!/bin/bash

echo 'Moving...'

#smbclient //192.168.86.100/drain -U rrysato@gmail.com -c 'put "ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb"'

mount /dev/sde1
cp 'ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb' ~/Mount/e/
umount /dev/sde1

echo 'Done.'

