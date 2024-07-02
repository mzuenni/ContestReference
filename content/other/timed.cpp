int times = clock();
//run for 900ms
while (1000*(clock()-times)/CLOCKS_PER_SEC < 900) {...}
