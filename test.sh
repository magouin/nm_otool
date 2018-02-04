#/bin/sh
./ft_otool $1 > /tmp/a
otool -t $1 > /tmp/b
diff /tmp/a /tmp/b
