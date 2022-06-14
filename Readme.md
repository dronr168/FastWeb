fastWeb - это компактный веб движок на c++

Для полной настройки используйте исходный код. 
Для компиляции проекта перейдите в главную директорию и выполните: make (требуется библиотека libssl-dev)
Если вы хотите установить программу после компиляции выполните: make install
Однако помните: Для корректной работы в директории как минимум должны быть файлы:
		index.html
		robots.txt(список разрешённых файлов, а не запрещённых, как обычно, пример в /build/bin)
	для работы по https протоколу понадабятся файлы:
		cert.pem
		key.pem
запуск производится командой: fastWeb <PORT> <nossl/ssl>
пример: fastWeb 80 nossl (помните для использования 80 и 443 порта требуются повышенные права)

также вы можете использовать в запуске конфигурационный файл: fastWeb -c <CONFIG_FILE>
пример fastWeb -c config
		где config:
			{80}
			{nossl}
			{js,application/x-javascript;gif,image/gif;png,image/png;jpg,image/jpg;css,text/css;mp3,mpeg/mp3;wav,audio/wav;mp4,video/mp4;avi,video/avi}
	в общем виде CONFIG_FILE:
			{<PORT>}
			{<nossl/ssl>}
			{<TYPE_FILE1>,<HEAD_TYPE1>;<TYPE_FILE2>,<HEAD_TYPE2>.......}

по умолчанию не ведутся логи, и не запускаются демоны
