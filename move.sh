#!/bin/bash

echo 'Moving...'

#http://[2001:0:9d38:90d7:2c37:2f9d:bbfa:138b]
#smbclient //http://[2001:0:9d38:90d7:2c37:2f9d:bbfa:138b]/drain -U rrysato@gmail.com -c 'put "ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb"'
#smbclient //2001:0:9d38:90d7:2c37:2f9d:bbfa:138b/drain -U rrysato@gmail.com -c 'put "ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb"'
#smbclient //2001-0-9d38-90d7-2c37-2f9d-bbfa-138b.ipv6-literal.net/drain -U rrysato@gmail.com -c 'put "ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb"'

#smbclient //192.168.86.100/drain -U rrysato@gmail.com -c 'put "ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb"'
#smbclient //68.5.236.116/drain -U rrysato@gmail.com -c 'put "ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb"'

mount /dev/sde1
cp 'ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb' ~/Mount/e/
umount /dev/sde1

#"C\Users\rrysa\AppData\local\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-"

echo 'Done.'

