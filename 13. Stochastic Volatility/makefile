heston: main_2.cpp heston_mc.o correlated_snd.o statistics.o option.o pay_off.o
	g++ -Wall -std=c++11 -o heston main_2.cpp heston_mc.cpp heston_mc.o correlated_snd.o statistics.o option.o pay_off.o -arch x86_64

heston_mc.o: heston_mc.cpp option.o
	g++ -Wall -std=c++11 -c heston_mc.cpp option.o -arch x86_64

correlated_snd.o: correlated_snd.cpp statistics.o
	g++ -Wall -std=c++11 -c correlated_snd.cpp statistics.o -arch x86_64

statistics.o: statistics.cpp
	g++ -Wall -std=c++11 statistics.cpp -arch x86_64

option.o: option.cpp pay_off.cpp
	g++ -Wall -std=c++11 -c option.cpp pay_off.o -arch x86_64

pay_off.o: pay_off.cpp
	g++ -Wall -std=c++11 -c pay_off.cpp -arch x86_64