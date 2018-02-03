#/bin/sh
./ft_nm $1 > /tmp/a
nm $1 > /tmp/b
diff /tmp/a /tmp/b
